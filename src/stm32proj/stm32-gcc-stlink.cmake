# name of targets
set(BIN_TARGET ${PROJECT_NAME}.bin)
set(HEX_TARGET ${PROJECT_NAME}.hex)
set(MAP_TARGET ${PROJECT_NAME}.map)
set(LSS_TARGET ${PROJECT_NAME}.lss)

# flash
add_custom_target(stlink_flash 
    DEPENDS ${ELF_TARGET} 
    COMMAND openocd -f /usr/local/share/openocd/scripts/interface/stlink-v2.cfg -f /usr/local/share/openocd/scripts/target/stm32h7x.cfg -c init -c 'reset halt' -c 'flash write_image erase ${PROJECT_NAME}.elf' -c 'reset run' -c exit
)
