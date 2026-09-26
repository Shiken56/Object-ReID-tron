#include "app_od.h"
#include <tk/tkernel.h>
#include <tm/tmonitor.h>
#include <string.h>

#include "stm32n6xx_hal.h"
#include "stai_od_model.h"

#define PRINT(fmt, ...) tm_printf((const UB *)(fmt), ##__VA_ARGS__)

/* ML buffer from camera */
extern uint8_t ml_buffer[];
#define ML_WIDTH 256
#define ML_HEIGHT 256

/* Semaphore for OD task */
ID sem_od_frame_ready = -1;

/* Static AI context */
STAI_NETWORK_CONTEXT_DECLARE(od_network, STAI_OD_MODEL_CONTEXT_SIZE);

LOCAL void od_task(INT stacd, void *exinf)
{
  (void)stacd;
  (void)exinf;

  PRINT("[OD] Starting OD Task...\r\n");

  /* Create Semaphore */
  T_CSEM csem = {.exinf = NULL, .sematr = TA_TFIFO, .isemcnt = 0, .maxsem = 1};
  sem_od_frame_ready = tk_cre_sem(&csem);
  if (sem_od_frame_ready <= 0) {
    PRINT("[OD ERROR] Failed to create OD semaphore\r\n");
    tk_ext_tsk();
    return;
  }

  /* Enable Clocks */
  __HAL_RCC_CACHEAXI_CLK_ENABLE();
  __HAL_RCC_NPU_CLK_ENABLE();

  /* Init Model */
  stai_return_code ret = stai_od_model_init(od_network);
  if (ret != STAI_SUCCESS) {
    PRINT("[OD ERROR] Model Init Failed: %d\r\n", ret);
    tk_ext_tsk();
    return;
  }
  PRINT("[OD] Model Initialized successfully!\r\n");

  stai_ptr inputs[1];
  stai_size num_inputs;
  stai_od_model_get_inputs(od_network, inputs, &num_inputs);
  
  stai_ptr outputs[1];
  stai_size num_outputs;
  stai_od_model_get_outputs(od_network, outputs, &num_outputs);

  while (1) {
    /* Wait for frame */
    tk_wai_sem(sem_od_frame_ready, 1, TMO_FEVR);

    /* Copy frame to NPU input */
    memcpy(inputs[0], ml_buffer, ML_WIDTH * ML_HEIGHT * 3);

    /* Run Inference */
    uint32_t start_time = HAL_GetTick();
    stai_od_model_run(od_network, STAI_MODE_SYNC);
    uint32_t end_time = HAL_GetTick();

    /* Print results */
    float *bboxes = (float *)outputs[0];
    
    // Just print the first box values (if any logic is added later to decode properly, do it here)
    PRINT("[OD] Inference time: %lu ms | Box[0]: %f %f %f %f\r\n",
          (unsigned long)(end_time - start_time), bboxes[0], bboxes[1], bboxes[2], bboxes[3]);
  }
}

LOCAL ID tskid_od;
LOCAL T_CTSK ctsk_od = {
  .itskpri    = 12,
  .stksz      = 8192,
  .task       = od_task,
  .tskatr     = TA_HLNG | TA_RNG0,
};

void start_od_task(void) {
  tskid_od = tk_cre_tsk(&ctsk_od);
  if (tskid_od > 0) {
    tk_sta_tsk(tskid_od, 0);
  } else {
    PRINT("[OD ERROR] Failed to create OD task: %d\r\n", tskid_od);
  }
}
