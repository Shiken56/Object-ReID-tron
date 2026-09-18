@echo off
set SIGNING_TOOL="C:\Program Files\STMicroelectronics\STM32Cube\STM32CubeProgrammer\bin\STM32_SigningTool_CLI.exe"

if not exist %SIGNING_TOOL% (
    echo Error: STM32_SigningTool_CLI.exe not found at %SIGNING_TOOL%
    exit /b 1
)

echo ===================================================
echo 1. Signing FSBL Binary...
echo ===================================================
%SIGNING_TOOL% -bin "FSBL\Debug\mtk3bsp2_stm32n657_FSBL.bin" -nk -hv 2.3 -s -o "FSBL\Debug\mtk3bsp2_stm32n657_FSBL_signed.bin"

echo.
echo ===================================================
echo 2. Signing Appli Binary...
echo ===================================================
%SIGNING_TOOL% -bin "Appli\Debug\mtk3bsp2_stm32n657_Appli.bin" -nk -hv 2.3 -s -o "Appli\Debug\mtk3bsp2_stm32n657_Appli_signed.bin"

echo.
echo ===================================================
echo Signing complete!
echo   [1] FSBL:  FSBL\Debug\mtk3bsp2_stm32n657_FSBL_signed.bin
echo   [2] Appli: Appli\Debug\mtk3bsp2_stm32n657_Appli_signed.bin
echo ===================================================
