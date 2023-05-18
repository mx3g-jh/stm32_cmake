## Setup cross-compile toolchain 
set(CROSS_COMPILE_PREFIX arm-none-eabi-)
include(${STM32_CMAKE_DIR}/cmake/gcc-arm-none-eabi.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/target-def.cmake)

## auto-set variables from user input
set(MCU_FLAGS "${CPU} -mthumb ${FPU} ${FLOAT_ABI}")
set(LINK_FLAGS "${MCU_FLAGS} -Wl,--gc-sections")
set(EXTRA_LINK_FLAGS "-Wl,-Map=${PROJECT_NAME}.map,--cref,--no-warn-mismatch -specs=nano.specs -specs=nosys.specs")
include(${STM32_CMAKE_DIR}/cmake/stm32-gcc-flags.cmake)

# print summary of configurations
message(STATUS "MCU_FAMILY: ${MCU_FAMILY}")
message(STATUS "MCU_NAME: ${MCU_NAME}")
message(STATUS "Specified C compiler: ${CMAKE_C_COMPILER}")
message(STATUS "Linker script: ${LINKER_SCRIPT}")
message(STATUS "Use LL library: ${USE_LL_LIB}")
message(STATUS "Use HAL library: ${USE_HAL_LIB}")
message(STATUS "Use Segger SystemView library: ${USE_SYSTEM_VIEW}")

## version information
set(VERSION_MAJOR 0 CACHE STRING "Project major version number.")
set(VERSION_MINOR 1 CACHE STRING "Project minor version number.")
set(VERSION_PATCH 0 CACHE STRING "Project patch version number.")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/cubemx/Core/Inc 
    # ${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/cubemx/Middlewares/Third_Party/FreeRTOS/Source/include 
    # ${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/cubemx/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 
    # ${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/cubemx/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
    # ${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/app/ILI9341
    ${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/app/ili9341
    # ${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/app/ssd1306
    ${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/lib/lvgl/drivers
    ${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos
    ${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/widgets
    ${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music
    ${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/benchmark
    ${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/stress
    ${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/lib/lvgl/lvgl 
    )

if(USE_SYSTEM_VIEW)
add_definitions("-DENABLE_SYSTEMVIEW")
endif()

## add project components
set(ELF_TARGET ${PROJECT_NAME}.elf)
set(PROJ_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/libraries)

# project-specific modules
# add_subdirectory(driver)

# common libraries
add_subdirectory(${PROJ_LIB_PATH}/CMSIS ${CMAKE_BINARY_DIR}/libraries/CMSIS)
add_subdirectory(${PROJ_LIB_PATH}/STM32H7xx_HAL_Driver ${CMAKE_BINARY_DIR}/libraries/STM32H7xx_HAL_Driver)

# STM32CubeMX generated source files
set(CUBEMX_SRC
    ${STM32_PROJ_FOLDER}/cubemx/Core/Src/gpio.c
    ${STM32_PROJ_FOLDER}/cubemx/Core/Src/main.c
    ${STM32_PROJ_FOLDER}/cubemx/Core/Src/spi.c
    ${STM32_PROJ_FOLDER}/cubemx/Core/Src/dma.c
    ${STM32_PROJ_FOLDER}/cubemx/Core/Src/tim.c
    ${STM32_PROJ_FOLDER}/cubemx/Core/Src/stm32h7xx_it.c
    ${STM32_PROJ_FOLDER}/cubemx/Core/Src/stm32h7xx_hal_msp.c
    ${STM32_PROJ_FOLDER}/cubemx/Core/Src/system_stm32h7xx.c
    ${STM32_PROJ_FOLDER}/cubemx/startup_stm32h743xx.s
    # ${STM32_PROJ_FOLDER}/cubemx/Core/Src/freertos.c
    # ${STM32_PROJ_FOLDER}/cubemx/Core/Src/stm32h7xx_hal_timebase_tim.c
    # ${STM32_PROJ_FOLDER}/cubemx/Middlewares/Third_Party/FreeRTOS/Source/croutine.c
    # ${STM32_PROJ_FOLDER}/cubemx/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c
    # ${STM32_PROJ_FOLDER}/cubemx/Middlewares/Third_Party/FreeRTOS/Source/list.c
    # ${STM32_PROJ_FOLDER}/cubemx/Middlewares/Third_Party/FreeRTOS/Source/queue.c
    # ${STM32_PROJ_FOLDER}/cubemx/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c
    # ${STM32_PROJ_FOLDER}/cubemx/Middlewares/Third_Party/FreeRTOS/Source/tasks.c
    # ${STM32_PROJ_FOLDER}/cubemx/Middlewares/Third_Party/FreeRTOS/Source/timers.c
    # ${STM32_PROJ_FOLDER}/cubemx/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.c
    # ${STM32_PROJ_FOLDER}/cubemx/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
    # ${STM32_PROJ_FOLDER}/cubemx/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
)

# drivers generated source files
set(DRIVERS_SRC
    # ${STM32_PROJ_FOLDER}/app/ILI9341/ILI9341_GFX.c
    # ${STM32_PROJ_FOLDER}/app/ILI9341/ILI9341_STM32_Driver.c
    # ${STM32_PROJ_FOLDER}/app/ILI9341/ILI9341_Touchscreen.c
    ${STM32_PROJ_FOLDER}/app/ili9341/fonts.c
    ${STM32_PROJ_FOLDER}/app/ili9341/ili9341_touch.c
    ${STM32_PROJ_FOLDER}/app/ili9341/ili9341.c
    # ${STM32_PROJ_FOLDER}/app/ssd1306/ssd1306_fonts.c
    # ${STM32_PROJ_FOLDER}/app/ssd1306/ssd1306_tests.c
    # ${STM32_PROJ_FOLDER}/app/ssd1306/ssd1306.c
)

set(LIBS_SRC
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/core/lv_group.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/core/lv_refr.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/core/lv_obj_scroll.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/core/lv_obj_style_gen.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/core/lv_obj_tree.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/core/lv_theme.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/core/lv_indev_scroll.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/core/lv_obj.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/core/lv_obj_draw.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/core/lv_obj_class.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/core/lv_disp.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/core/lv_event.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/core/lv_obj_style.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/core/lv_indev.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/core/lv_obj_pos.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/misc/lv_area.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/misc/lv_anim.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/misc/lv_color.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/misc/lv_txt.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/misc/lv_math.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/misc/lv_style_gen.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/misc/lv_log.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/misc/lv_anim_timeline.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/misc/lv_async.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/misc/lv_lru.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/misc/lv_txt_ap.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/misc/lv_style.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/misc/lv_timer.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/misc/lv_printf.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/misc/lv_utils.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/misc/lv_templ.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/misc/lv_tlsf.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/misc/lv_fs.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/misc/lv_bidi.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/misc/lv_mem.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/misc/lv_ll.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/misc/lv_gc.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/hal/lv_hal_disp.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/hal/lv_hal_indev.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/hal/lv_hal_tick.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/widgets/lv_dropdown.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/widgets/lv_table.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/widgets/lv_slider.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/widgets/lv_roller.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/widgets/lv_arc.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/widgets/lv_textarea.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/widgets/lv_line.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/widgets/lv_btn.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/widgets/lv_canvas.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/widgets/lv_img.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/widgets/lv_bar.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/widgets/lv_objx_templ.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/widgets/lv_btnmatrix.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/widgets/lv_label.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/widgets/lv_checkbox.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/widgets/lv_switch.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_montserrat_26.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_montserrat_34.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_montserrat_8.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_montserrat_18.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_montserrat_16.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_montserrat_32.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_simsun_16_cjk.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_montserrat_28.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_montserrat_36.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_montserrat_44.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_montserrat_30.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_montserrat_24.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_montserrat_28_compressed.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_montserrat_42.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_montserrat_22.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_montserrat_40.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_montserrat_46.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_montserrat_10.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_montserrat_48.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_fmt_txt.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_montserrat_38.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_loader.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_montserrat_14.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_dejavu_16_persian_hebrew.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_montserrat_12.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_unscii_16.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_unscii_8.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_montserrat_20.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/font/lv_font_montserrat_12_subpx.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/others/snapshot/lv_snapshot.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/others/ime/lv_ime_pinyin.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/others/monkey/lv_monkey.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/others/imgfont/lv_imgfont.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/others/gridnav/lv_gridnav.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/others/msg/lv_msg.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/others/fragment/lv_fragment_manager.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/others/fragment/lv_fragment.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/themes/mono/lv_theme_mono.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/themes/default/lv_theme_default.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/themes/basic/lv_theme_basic.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/layouts/grid/lv_grid.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/layouts/flex/lv_flex.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/widgets/list/lv_list.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/widgets/imgbtn/lv_imgbtn.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/widgets/calendar/lv_calendar_header_dropdown.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/widgets/calendar/lv_calendar_header_arrow.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/widgets/calendar/lv_calendar.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/widgets/win/lv_win.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/widgets/colorwheel/lv_colorwheel.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/widgets/tileview/lv_tileview.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/widgets/tabview/lv_tabview.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/widgets/span/lv_span.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/widgets/animimg/lv_animimg.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/widgets/keyboard/lv_keyboard.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/widgets/meter/lv_meter.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/widgets/spinner/lv_spinner.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/widgets/menu/lv_menu.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/widgets/chart/lv_chart.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/widgets/led/lv_led.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/widgets/msgbox/lv_msgbox.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/widgets/spinbox/lv_spinbox.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/libs/bmp/lv_bmp.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/libs/sjpg/tjpgd.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/libs/sjpg/lv_sjpg.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/libs/gif/gifdec.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/libs/gif/lv_gif.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/libs/freetype/lv_freetype.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/libs/fsdrv/lv_fs_win32.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/libs/fsdrv/lv_fs_stdio.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/libs/fsdrv/lv_fs_fatfs.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/libs/fsdrv/lv_fs_posix.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/libs/ffmpeg/lv_ffmpeg.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/libs/png/lodepng.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/libs/png/lv_png.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/libs/qrcode/qrcodegen.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/libs/qrcode/lv_qrcode.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/libs/rlottie/lv_rlottie.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/extra/lv_extra.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/lv_draw.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/swm341_dma2d/lv_gpu_swm341_dma2d.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/lv_draw_mask.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/lv_draw_arc.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/nxp/pxp/lv_draw_pxp.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_line.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_buf.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_blend.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/nxp/vglite/lv_vglite_utils.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_arc.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/nxp/vglite/lv_draw_vglite_rect.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/stm32_dma2d/lv_gpu_stm32_dma2d.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/lv_draw_layer.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/lv_draw_line.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sdl/lv_draw_sdl_texture_cache.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sdl/lv_draw_sdl_rect.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sdl/lv_draw_sdl_label.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sdl/lv_draw_sdl_layer.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sdl/lv_draw_sdl_mask.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sdl/lv_draw_sdl_composite.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sdl/lv_draw_sdl_line.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sdl/lv_draw_sdl_utils.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sdl/lv_draw_sdl_bg.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sdl/lv_draw_sdl_img.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sdl/lv_draw_sdl_stack_blur.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sdl/lv_draw_sdl_arc.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sdl/lv_draw_sdl.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sdl/lv_draw_sdl_polygon.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/lv_draw_rect.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/lv_draw_transform.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/lv_img_buf.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/arm2d/lv_gpu_arm2d.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/lv_draw_img.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/lv_draw_label.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/lv_img_decoder.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/lv_img_cache.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sw/lv_draw_sw_layer.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sw/lv_draw_sw_blend.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sw/lv_draw_sw.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sw/lv_draw_sw_letter.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sw/lv_draw_sw_transform.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sw/lv_draw_sw_img.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sw/lv_draw_sw_line.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sw/lv_draw_sw_arc.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sw/lv_draw_sw_gradient.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sw/lv_draw_sw_dither.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sw/lv_draw_sw_polygon.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/sw/lv_draw_sw_rect.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/src/draw/lv_draw_triangle.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/stress/lv_demo_stress.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/benchmark/lv_demo_benchmark.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/benchmark/assets/img_benchmark_cogwheel_rgb565a8.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/benchmark/assets/lv_font_bechmark_montserrat_16_compr_az.c.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/benchmark/assets/img_benchmark_cogwheel_alpha16.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/benchmark/assets/img_benchmark_cogwheel_indexed16.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/benchmark/assets/lv_font_bechmark_montserrat_28_compr_az.c.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/benchmark/assets/img_benchmark_cogwheel_argb.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/benchmark/assets/img_benchmark_cogwheel_rgb.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/benchmark/assets/lv_font_bechmark_montserrat_12_compr_az.c.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/benchmark/assets/img_benchmark_cogwheel_chroma_keyed.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/widgets/lv_demo_widgets.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/widgets/assets/img_clothes.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/widgets/assets/img_demo_widgets_avatar.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/widgets/assets/img_lvgl_logo.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/lv_demo_music_main.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/lv_demo_music.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/lv_demo_music_list.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_cover_2_large.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_icon_1_large.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_slider_knob.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_corner_left.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_corner_right_large.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_btn_loop.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_btn_prev.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_corner_left_large.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_icon_4.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_cover_3_large.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_btn_pause_large.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_btn_next.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_btn_corner_large.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_btn_play_large.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_cover_1.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_icon_3.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_corner_right.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_wave_bottom_large.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_btn_play.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_icon_1.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_cover_3.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_logo.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_wave_bottom.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_btn_list_pause.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_list_border_large.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_wave_top.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_slider_knob_large.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_btn_list_play.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_icon_2.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_icon_3_large.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_btn_prev_large.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_btn_rnd.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_btn_next_large.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_btn_list_pause_large.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_cover_1_large.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_icon_2_large.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_icon_4_large.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_cover_2.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_btn_list_play_large.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_btn_pause.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_btn_loop_large.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_wave_top_large.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_list_border.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/music/assets/img_lv_demo_music_btn_rnd_large.c
    # ${STM32_PROJ_FOLDER}/lib/lvgl/lvgl/demos/keypad_encoder/lv_demo_keypad_encoder.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/drivers/lv_port_indev.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/drivers/lv_port_disp.c
    ${STM32_PROJ_FOLDER}/lib/lvgl/drivers/lv_port_fs.c
)

add_executable(${ELF_TARGET} ${CUBEMX_SRC} ${DRIVERS_SRC} ${LIBS_SRC})
target_compile_definitions(${ELF_TARGET} PUBLIC -D${MCU_FAMILY})
target_link_libraries(${ELF_TARGET} PUBLIC cmsis stm32h7xx_hal -lc -lm -lnosys)
target_link_libraries(${ELF_TARGET} PRIVATE -T${LINKER_SCRIPT} ${EXTRA_LINK_FLAGS})

target_include_directories(${ELF_TARGET} PUBLIC
    $<BUILD_INTERFACE:
    ${CMAKE_CURRENT_SOURCE_DIR}/cubemx/Core/Inc 
    # ${CMAKE_CURRENT_SOURCE_DIR}/cubemx/Middlewares/Third_Party/FreeRTOS/Source/include 
    # ${CMAKE_CURRENT_SOURCE_DIR}/cubemx/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 
    # ${CMAKE_CURRENT_SOURCE_DIR}/cubemx/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F 
    # ${CMAKE_CURRENT_SOURCE_DIR}/app/ILI9341
    ${CMAKE_CURRENT_SOURCE_DIR}/app/ili9341
    # ${CMAKE_CURRENT_SOURCE_DIR}/app/ssd1306
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/lvgl/drivers
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/lvgl/lvgl/demos
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/lvgl/lvgl/demos/widgets
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/lvgl/lvgl/demos/music
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/lvgl/lvgl/demos/benchmark
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/lvgl/lvgl/demos/stress
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/lvgl/lvgl>
)

## add post-build targets
include(${STM32_CMAKE_DIR}/cmake/stm32-gcc-postbuild.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/stm32-gcc-jlink.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/${STM32_PROJ_FOLDER}/stm32-gcc-stlink.cmake)
