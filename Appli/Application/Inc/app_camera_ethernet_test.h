#ifndef APP_CAMERA_ETHERNET_TEST_H
#define APP_CAMERA_ETHERNET_TEST_H

#include <stdint.h>

/* Initialize the UDP connection */
void Ethernet_Streamer_Init(void);

/* Stream a frame over UDP */
void Ethernet_Streamer_SendFrame(uint8_t *frame_buffer, uint32_t width, uint32_t height);

#endif // APP_CAMERA_ETHERNET_TEST_H
