# Target-specific flags
set(MCU_ARCH ARMCM7)
set(MCU_FAMILY STM32H743xx)
set(MCU_NAME STM32H743VI)

# You can find the following values from ./cubemx/Makefile
set(CPU "-mcpu=cortex-m7")
set(FPU "-mfpu=fpv5-d16")
set(FLOAT_ABI "-mfloat-abi=hard")

set(LINKER_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/cubemx/STM32H743VITx_FLASH.ld)

option(USE_LL_LIB "Enable LL library" ON)
option(USE_HAL_LIB "Enable HAL library" ON)

option(USE_SYSTEM_VIEW "Enable Segger SystemView library" OFF)