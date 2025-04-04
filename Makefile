##########################################################################################################################
# File automatically-generated by tool: [projectgenerator] version: [4.5.0-B34] date: [Thu Apr 03 20:31:12 CST 2025] 
##########################################################################################################################

# ------------------------------------------------
# Generic Makefile (based on gcc)
#
# ChangeLog :
#	2017-02-10 - Several enhancements + project update mode
#   2015-07-22 - first version
# ------------------------------------------------
SHELL =cmd.exe
######################################
# target
######################################
TARGET = 743zit6


######################################
# building variables
######################################
# debug build?
DEBUG = 1
# optimization
OPT = -Og


#######################################
# paths
#######################################
# Build path
BUILD_DIR = build

######################################
# source
######################################
# C sources
C_SOURCES =  \
Core/Src/main.c \
Core/Src/gpio.c \
Core/Src/adc.c \
Core/Src/fmc.c \
Core/Src/i2c.c \
Core/Src/ad7606.c \
Core/Src/sdram.c \
Core/Src/httpd_cgi_ssi.c \
Core/Src/quadspi.c \
Core/Src/rtc.c \
Core/Src/sdmmc.c \
Core/Src/spi.c \
Core/Src/tim.c \
Core/Src/usart.c \
Core/Src/usb_otg.c \
Core/Src/stm32h7xx_it.c \
Core/Src/stm32h7xx_hal_msp.c \
Core/Src/stm32h7xx_hal_timebase_tim.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_adc.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_adc_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_hsem.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mdma.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_exti.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_eth.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_eth_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_fmc.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sram.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sdram.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_qspi.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rtc.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rtc_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_sdmmc.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_delayblock.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sd.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_sd_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_spi.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_spi_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pcd.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pcd_ex.c \
Drivers/STM32H7xx_HAL_Driver/Src/stm32h7xx_ll_usb.c \
Core/Src/system_stm32h7xx.c \
Core/Src/freertos.c \
FATFS/Target/bsp_driver_sd.c \
FATFS/Target/sd_diskio.c \
FATFS/Target/fatfs_platform.c \
FATFS/App/fatfs.c \
LWIP/Target/ethernetif.c \
LWIP/App/lwip.c \
Drivers/BSP/Components/lan8742/lan8742.c \
Middlewares/Third_Party/FatFs/src/diskio.c \
Middlewares/Third_Party/FatFs/src/ff.c \
Middlewares/Third_Party/FatFs/src/ff_gen_drv.c \
Middlewares/Third_Party/FatFs/src/option/syscall.c \
Middlewares/Third_Party/FreeRTOS/Source/croutine.c \
Middlewares/Third_Party/FreeRTOS/Source/event_groups.c \
Middlewares/Third_Party/FreeRTOS/Source/list.c \
Middlewares/Third_Party/FreeRTOS/Source/queue.c \
Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c \
Middlewares/Third_Party/FreeRTOS/Source/tasks.c \
Middlewares/Third_Party/FreeRTOS/Source/timers.c \
Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c \
Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c \
Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/auth.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/ccp.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/chap_ms.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/chap-md5.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/chap-new.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/demand.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/eap.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/eui64.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/fsm.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/ipcp.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/ipv6cp.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/lcp.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/magic.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/mppe.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/multilink.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/ppp.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/pppapi.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/pppcrypt.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/pppoe.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/pppol2tp.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/pppos.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/upap.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/utils.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/vj.c \
Middlewares/Third_Party/LwIP/src/netif/bridgeif.c \
Middlewares/Third_Party/LwIP/src/netif/bridgeif_fdb.c \
Middlewares/Third_Party/LwIP/src/netif/ethernet.c \
Middlewares/Third_Party/LwIP/src/netif/lowpan6.c \
Middlewares/Third_Party/LwIP/src/netif/lowpan6_ble.c \
Middlewares/Third_Party/LwIP/src/netif/lowpan6_common.c \
Middlewares/Third_Party/LwIP/src/netif/slipif.c \
Middlewares/Third_Party/LwIP/src/netif/zepif.c \
Middlewares/Third_Party/LwIP/src/netif/ppp/ecp.c \
Middlewares/Third_Party/LwIP/src/apps/http/httpd.c \
Middlewares/Third_Party/LwIP/src/apps/http/fs.c \
Middlewares/Third_Party/LwIP/src/api/api_lib.c \
Middlewares/Third_Party/LwIP/src/api/api_msg.c \
Middlewares/Third_Party/LwIP/src/api/err.c \
Middlewares/Third_Party/LwIP/src/api/if_api.c \
Middlewares/Third_Party/LwIP/src/api/netbuf.c \
Middlewares/Third_Party/LwIP/src/api/netdb.c \
Middlewares/Third_Party/LwIP/src/api/netifapi.c \
Middlewares/Third_Party/LwIP/src/api/sockets.c \
Middlewares/Third_Party/LwIP/src/api/tcpip.c \
Middlewares/Third_Party/LwIP/src/core/altcp.c \
Middlewares/Third_Party/LwIP/src/core/altcp_alloc.c \
Middlewares/Third_Party/LwIP/src/core/altcp_tcp.c \
Middlewares/Third_Party/LwIP/src/core/def.c \
Middlewares/Third_Party/LwIP/src/core/dns.c \
Middlewares/Third_Party/LwIP/src/core/inet_chksum.c \
Middlewares/Third_Party/LwIP/src/core/init.c \
Middlewares/Third_Party/LwIP/src/core/ip.c \
Middlewares/Third_Party/LwIP/src/core/mem.c \
Middlewares/Third_Party/LwIP/src/core/memp.c \
Middlewares/Third_Party/LwIP/src/core/netif.c \
Middlewares/Third_Party/LwIP/src/core/pbuf.c \
Middlewares/Third_Party/LwIP/src/core/raw.c \
Middlewares/Third_Party/LwIP/src/core/stats.c \
Middlewares/Third_Party/LwIP/src/core/sys.c \
Middlewares/Third_Party/LwIP/src/core/tcp.c \
Middlewares/Third_Party/LwIP/src/core/tcp_in.c \
Middlewares/Third_Party/LwIP/src/core/tcp_out.c \
Middlewares/Third_Party/LwIP/src/core/timeouts.c \
Middlewares/Third_Party/LwIP/src/core/udp.c \
Middlewares/Third_Party/LwIP/src/core/ipv4/autoip.c \
Middlewares/Third_Party/LwIP/src/core/ipv4/dhcp.c \
Middlewares/Third_Party/LwIP/src/core/ipv4/etharp.c \
Middlewares/Third_Party/LwIP/src/core/ipv4/icmp.c \
Middlewares/Third_Party/LwIP/src/core/ipv4/igmp.c \
Middlewares/Third_Party/LwIP/src/core/ipv4/ip4.c \
Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_addr.c \
Middlewares/Third_Party/LwIP/src/core/ipv4/ip4_frag.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/dhcp6.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/ethip6.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/icmp6.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/inet6.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/ip6.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_addr.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_frag.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/mld6.c \
Middlewares/Third_Party/LwIP/src/core/ipv6/nd6.c \
Middlewares/Third_Party/LwIP/system/OS/sys_arch.c \
Middlewares/Third_Party/LwIP/src/apps/mqtt/mqtt.c \
User/FFT/dsp_fft.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_bitreversal.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_cfft_f32.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_cfft_q15.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_cfft_q31.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix2_f32.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_f32.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_q15.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix2_init_q31.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix2_q15.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix2_q31.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix4_f32.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_f32.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_q15.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix4_init_q31.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix4_q15.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix4_q31.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_cfft_radix8_f32.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_dct4_f32.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_dct4_init_f32.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_dct4_init_q15.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_dct4_q15.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_dct4_init_q31.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_dct4_q31.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_rfft_f32.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_rfft_fast_f32.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_rfft_fast_init_f32.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_rfft_init_f32.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_rfft_init_q15.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_rfft_init_q31.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_rfft_q15.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_rfft_q31.c \
Drivers/CMSIS/DSP/Source/CommonTables/arm_common_tables.c \
Drivers/CMSIS/DSP/Source/CommonTables/arm_const_structs.c \
Drivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/src/TransformFunctions/bitreversal.c \
Drivers/CMSIS/DSP/Source/ComplexMathFunctions/arm_cmplx_conj_f32.c \
Drivers/CMSIS/DSP/Source/ComplexMathFunctions/arm_cmplx_conj_q15.c \
Drivers/CMSIS/DSP/Source/ComplexMathFunctions/arm_cmplx_conj_q31.c \
Drivers/CMSIS/DSP/Source/ComplexMathFunctions/arm_cmplx_dot_prod_f32.c \
Drivers/CMSIS/DSP/Source/ComplexMathFunctions/arm_cmplx_dot_prod_q15.c \
Drivers/CMSIS/DSP/Source/ComplexMathFunctions/arm_cmplx_dot_prod_q31.c \
Drivers/CMSIS/DSP/Source/ComplexMathFunctions/arm_cmplx_mag_q15.c \
Drivers/CMSIS/DSP/Source/ComplexMathFunctions/arm_cmplx_mag_f32.c \
Drivers/CMSIS/DSP/Source/ComplexMathFunctions/arm_cmplx_mag_q31.c \
Drivers/CMSIS/DSP/Source/ComplexMathFunctions/arm_cmplx_mag_squared_f32.c \
Drivers/CMSIS/DSP/Source/ComplexMathFunctions/arm_cmplx_mag_squared_q15.c \
Drivers/CMSIS/DSP/Source/ComplexMathFunctions/arm_cmplx_mag_squared_q31.c \
Drivers/CMSIS/DSP/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_f32.c \
Drivers/CMSIS/DSP/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q15.c \
Drivers/CMSIS/DSP/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q31.c \
Drivers/CMSIS/DSP/Source/ComplexMathFunctions/arm_cmplx_mult_real_f32.c \
Drivers/CMSIS/DSP/Source/ComplexMathFunctions/arm_cmplx_mult_real_q15.c \
Drivers/CMSIS/DSP/Source/ComplexMathFunctions/arm_cmplx_mult_real_q31.c \
Drivers/CMSIS/DSP/Source/TransformFunctions/arm_bitreversal2.c \
User/LCD/lcd.c \
lvgl/porting/lv_port_disp.c \
lvgl/porting/lv_port_fs.c \
lvgl/porting/lv_port_indev.c \
lvgl/src/core/lv_disp.c \
lvgl/src/core/lv_event.c \
lvgl/src/core/lv_group.c \
lvgl/src/core/lv_indev.c \
lvgl/src/core/lv_indev_scroll.c \
lvgl/src/core/lv_obj.c \
lvgl/src/core/lv_obj_class.c \
lvgl/src/core/lv_obj_draw.c \
lvgl/src/core/lv_obj_pos.c \
lvgl/src/core/lv_obj_scroll.c \
lvgl/src/core/lv_obj_style.c \
lvgl/src/core/lv_obj_style_gen.c \
lvgl/src/core/lv_obj_tree.c \
lvgl/src/core/lv_refr.c \
lvgl/src/core/lv_theme.c \
lvgl/src/draw/lv_draw.c \
lvgl/src/draw/lv_draw_arc.c \
lvgl/src/draw/lv_draw_img.c \
lvgl/src/draw/lv_draw_label.c \
lvgl/src/draw/lv_draw_line.c \
lvgl/src/draw/lv_draw_mask.c \
lvgl/src/draw/lv_draw_rect.c \
lvgl/src/draw/lv_draw_triangle.c \
lvgl/src/draw/lv_img_buf.c \
lvgl/src/draw/lv_img_cache.c \
lvgl/src/draw/lv_img_decoder.c \
lvgl/src/draw/nxp/lv_gpu_nxp.c \
lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.c \
lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.c \
lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.c \
lvgl/src/draw/nxp/vglite/lv_draw_vglite_arc.c \
lvgl/src/draw/nxp/vglite/lv_draw_vglite_blend.c \
lvgl/src/draw/nxp/vglite/lv_draw_vglite_rect.c \
lvgl/src/draw/nxp/vglite/lv_gpu_nxp_vglite.c \
lvgl/src/draw/sdl/lv_draw_sdl.c \
lvgl/src/draw/sdl/lv_draw_sdl_arc.c \
lvgl/src/draw/sdl/lv_draw_sdl_bg.c \
lvgl/src/draw/sdl/lv_draw_sdl_composite.c \
lvgl/src/draw/sdl/lv_draw_sdl_img.c \
lvgl/src/draw/sdl/lv_draw_sdl_label.c \
lvgl/src/draw/sdl/lv_draw_sdl_line.c \
lvgl/src/draw/sdl/lv_draw_sdl_mask.c \
lvgl/src/draw/sdl/lv_draw_sdl_polygon.c \
lvgl/src/draw/sdl/lv_draw_sdl_rect.c \
lvgl/src/draw/sdl/lv_draw_sdl_stack_blur.c \
lvgl/src/draw/sdl/lv_draw_sdl_texture_cache.c \
lvgl/src/draw/sdl/lv_draw_sdl_utils.c \
lvgl/src/draw/stm32_dma2d/lv_gpu_stm32_dma2d.c \
lvgl/src/draw/sw/lv_draw_sw.c \
lvgl/src/draw/sw/lv_draw_sw_arc.c \
lvgl/src/draw/sw/lv_draw_sw_blend.c \
lvgl/src/draw/sw/lv_draw_sw_dither.c \
lvgl/src/draw/sw/lv_draw_sw_gradient.c \
lvgl/src/draw/sw/lv_draw_sw_img.c \
lvgl/src/draw/sw/lv_draw_sw_letter.c \
lvgl/src/draw/sw/lv_draw_sw_line.c \
lvgl/src/draw/sw/lv_draw_sw_polygon.c \
lvgl/src/draw/sw/lv_draw_sw_rect.c \
lvgl/src/extra/layouts/flex/lv_flex.c \
lvgl/src/extra/layouts/grid/lv_grid.c \
lvgl/src/extra/libs/bmp/lv_bmp.c \
lvgl/src/extra/libs/ffmpeg/lv_ffmpeg.c \
lvgl/src/extra/libs/freetype/lv_freetype.c \
lvgl/src/extra/libs/fsdrv/lv_fs_fatfs.c \
lvgl/src/extra/libs/fsdrv/lv_fs_posix.c \
lvgl/src/extra/libs/fsdrv/lv_fs_stdio.c \
lvgl/src/extra/libs/fsdrv/lv_fs_win32.c \
lvgl/src/extra/libs/gif/gifdec.c \
lvgl/src/extra/libs/gif/lv_gif.c \
lvgl/src/extra/libs/png/lodepng.c \
lvgl/src/extra/libs/png/lv_png.c \
lvgl/src/extra/libs/qrcode/lv_qrcode.c \
lvgl/src/extra/libs/qrcode/qrcodegen.c \
lvgl/src/extra/libs/rlottie/lv_rlottie.c \
lvgl/src/extra/libs/sjpg/lv_sjpg.c \
lvgl/src/extra/libs/sjpg/tjpgd.c \
lvgl/src/extra/lv_extra.c \
lvgl/src/extra/others/gridnav/lv_gridnav.c \
lvgl/src/extra/others/monkey/lv_monkey.c \
lvgl/src/extra/others/snapshot/lv_snapshot.c \
lvgl/src/extra/themes/basic/lv_theme_basic.c \
lvgl/src/extra/themes/default/lv_theme_default.c \
lvgl/src/extra/themes/mono/lv_theme_mono.c \
lvgl/src/extra/widgets/analogclock/lv_analogclock.c \
lvgl/src/extra/widgets/animimg/lv_animimg.c \
lvgl/src/extra/widgets/calendar/lv_calendar.c \
lvgl/src/extra/widgets/calendar/lv_calendar_header_arrow.c \
lvgl/src/extra/widgets/calendar/lv_calendar_header_dropdown.c \
lvgl/src/extra/widgets/carousel/lv_carousel.c \
lvgl/src/extra/widgets/chart/lv_chart.c \
lvgl/src/extra/widgets/colorwheel/lv_colorwheel.c \
lvgl/src/extra/widgets/dclock/lv_dclock.c \
lvgl/src/extra/widgets/imgbtn/lv_imgbtn.c \
lvgl/src/extra/widgets/keyboard/lv_keyboard.c \
lvgl/src/extra/widgets/keyboard/lv_zh_keyboard.c \
lvgl/src/extra/widgets/led/lv_led.c \
lvgl/src/extra/widgets/list/lv_list.c \
lvgl/src/extra/widgets/menu/lv_menu.c \
lvgl/src/extra/widgets/meter/lv_meter.c \
lvgl/src/extra/widgets/msgbox/lv_msgbox.c \
lvgl/src/extra/widgets/radiobtn/lv_radiobtn.c \
lvgl/src/extra/widgets/span/lv_span.c \
lvgl/src/extra/widgets/spinbox/lv_spinbox.c \
lvgl/src/extra/widgets/spinner/lv_spinner.c \
lvgl/src/extra/widgets/tabview/lv_tabview.c \
lvgl/src/extra/widgets/tileview/lv_tileview.c \
lvgl/src/extra/widgets/win/lv_win.c \
lvgl/src/font/lv_font.c \
lvgl/src/font/lv_font_dejavu_16_persian_hebrew.c \
lvgl/src/font/lv_font_fmt_txt.c \
lvgl/src/font/lv_font_loader.c \
lvgl/src/font/lv_font_montserrat_10.c \
lvgl/src/font/lv_font_montserrat_12.c \
lvgl/src/font/lv_font_montserrat_12_subpx.c \
lvgl/src/font/lv_font_montserrat_14.c \
lvgl/src/font/lv_font_montserrat_16.c \
lvgl/src/font/lv_font_montserrat_18.c \
lvgl/src/font/lv_font_montserrat_20.c \
lvgl/src/font/lv_font_montserrat_22.c \
lvgl/src/font/lv_font_montserrat_24.c \
lvgl/src/font/lv_font_montserrat_26.c \
lvgl/src/font/lv_font_montserrat_28.c \
lvgl/src/font/lv_font_montserrat_28_compressed.c \
lvgl/src/font/lv_font_montserrat_30.c \
lvgl/src/font/lv_font_montserrat_32.c \
lvgl/src/font/lv_font_montserrat_34.c \
lvgl/src/font/lv_font_montserrat_36.c \
lvgl/src/font/lv_font_montserrat_38.c \
lvgl/src/font/lv_font_montserrat_40.c \
lvgl/src/font/lv_font_montserrat_42.c \
lvgl/src/font/lv_font_montserrat_44.c \
lvgl/src/font/lv_font_montserrat_46.c \
lvgl/src/font/lv_font_montserrat_48.c \
lvgl/src/font/lv_font_montserrat_8.c \
lvgl/src/font/lv_font_simsun_16_cjk.c \
lvgl/src/font/lv_font_unscii_16.c \
lvgl/src/font/lv_font_unscii_8.c \
lvgl/src/hal/lv_hal_disp.c \
lvgl/src/hal/lv_hal_indev.c \
lvgl/src/hal/lv_hal_tick.c \
lvgl/src/misc/lv_anim.c \
lvgl/src/misc/lv_anim_timeline.c \
lvgl/src/misc/lv_area.c \
lvgl/src/misc/lv_async.c \
lvgl/src/misc/lv_bidi.c \
lvgl/src/misc/lv_color.c \
lvgl/src/misc/lv_fs.c \
lvgl/src/misc/lv_gc.c \
lvgl/src/misc/lv_ll.c \
lvgl/src/misc/lv_log.c \
lvgl/src/misc/lv_lru.c \
lvgl/src/misc/lv_math.c \
lvgl/src/misc/lv_mem.c \
lvgl/src/misc/lv_printf.c \
lvgl/src/misc/lv_style.c \
lvgl/src/misc/lv_style_gen.c \
lvgl/src/misc/lv_templ.c \
lvgl/src/misc/lv_timer.c \
lvgl/src/misc/lv_tlsf.c \
lvgl/src/misc/lv_txt.c \
lvgl/src/misc/lv_txt_ap.c \
lvgl/src/misc/lv_utils.c \
lvgl/src/widgets/lv_arc.c \
lvgl/src/widgets/lv_bar.c \
lvgl/src/widgets/lv_btn.c \
lvgl/src/widgets/lv_btnmatrix.c \
lvgl/src/widgets/lv_canvas.c \
lvgl/src/widgets/lv_checkbox.c \
lvgl/src/widgets/lv_dropdown.c \
lvgl/src/widgets/lv_img.c \
lvgl/src/widgets/lv_label.c \
lvgl/src/widgets/lv_line.c \
lvgl/src/widgets/lv_objx_templ.c \
lvgl/src/widgets/lv_roller.c \
lvgl/src/widgets/lv_slider.c \
lvgl/src/widgets/lv_switch.c \
lvgl/src/widgets/lv_table.c \
lvgl/src/widgets/lv_textarea.c \
generated/events_init.c \
generated/guider_fonts/lv_font_arial_16.c \
generated/guider_fonts/lv_font_arial_30.c \
generated/guider_fonts/lv_font_arial_32.c \
generated/guider_fonts/lv_font_montserratMedium_12.c \
generated/guider_fonts/lv_font_simsun_12.c \
generated/guider_fonts/lv_font_simsun_16.c \
generated/gui_guider.c \
generated/images/_f7b64978f5bff1ff9d8a4bf8f3d4d9d6_alpha_520x340.c \
generated/setup_scr_wave_model.c \
generated/widgets_init.c \
custom/custom.c \
User/screenshot/screenshot.c \
User/sdcard/sdcard_test.c \
User/task/task_page1.c \
Core/Src/sysmem.c \
Core/Src/syscalls.c


# ASM sources
ASM_SOURCES =  \
startup_stm32h743xx.s


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m7

# fpu
FPU = -mfpu=fpv5-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 

LDLIBS += -lm

# C defines
C_DEFS =  \
-DUSE_HAL_DRIVER \
-DSTM32H743xx


# AS includes
AS_INCLUDES = 

# C includes
C_INCLUDES =  \
-ICore/Inc \
-IDrivers/STM32H7xx_HAL_Driver/Inc \
-IDrivers/STM32H7xx_HAL_Driver/Inc/Legacy \
-IDrivers/CMSIS/Device/ST/STM32H7xx/Include \
-IDrivers/CMSIS/Include \
-IFATFS/Target \
-IFATFS/App \
-ILWIP/App \
-ILWIP/Target \
-IMiddlewares/Third_Party/LwIP/src/include \
-IMiddlewares/Third_Party/LwIP/system \
-IMiddlewares/Third_Party/FreeRTOS/Source/include \
-IMiddlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS \
-IMiddlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F \
-IMiddlewares/Third_Party/FatFs/src \
-IDrivers/BSP/Components/lan8742 \
-IMiddlewares/Third_Party/LwIP/src/include/netif/ppp \
-IMiddlewares/Third_Party/LwIP/src/apps/http \
-IMiddlewares/Third_Party/LwIP/src/include/lwip \
-IMiddlewares/Third_Party/LwIP/src/include/lwip/apps \
-IMiddlewares/Third_Party/LwIP/src/include/lwip/priv \
-IMiddlewares/Third_Party/LwIP/src/include/lwip/prot \
-IMiddlewares/Third_Party/LwIP/src/include/netif \
-IMiddlewares/Third_Party/LwIP/src/include/compat/posix \
-IMiddlewares/Third_Party/LwIP/src/include/compat/posix/arpa \
-IMiddlewares/Third_Party/LwIP/src/include/compat/posix/net \
-IMiddlewares/Third_Party/LwIP/src/include/compat/posix/sys \
-IMiddlewares/Third_Party/LwIP/src/include/compat/stdc \
-IMiddlewares/Third_Party/LwIP/system/arch \
-IUser/FFT \
-IDrivers/CMSIS/DSP/Include \
-IDrivers/CMSIS/DSP/DSP_Lib_TestSuite/RefLibs/inc \
-IUser/LCD \
-Icustom \
-Igenerated \
-Igenerated/guider_fonts \
-Igenerated/images \
-Ilvgl/porting \
-Ilvgl/src/core \
-Ilvgl/src/draw \
-Ilvgl/src/draw/nxp \
-Ilvgl/src/draw/nxp/pxp \
-Ilvgl/src/draw/nxp/vglite \
-Ilvgl/src/draw/sdl \
-Ilvgl/src/draw/stm32_dma2d \
-Ilvgl/src/draw/sw \
-Ilvgl/src/extra \
-Ilvgl/src/extra/layouts/flex \
-Ilvgl/src/extra/layouts/grid \
-Ilvgl/src/extra/libs/bmp \
-Ilvgl/src/extra/libs/ffmpeg \
-Ilvgl/src/extra/libs/freetype \
-Ilvgl/src/extra/libs/fsdrv \
-Ilvgl/src/extra/libs/gif \
-Ilvgl/src/extra/libs/png \
-Ilvgl/src/extra/libs/qrcode \
-Ilvgl/src/extra/libs/rlottie \
-Ilvgl/src/extra/libs/sjpg \
-Ilvgl/src/extra/others/gridnav \
-Ilvgl/src/extra/others/monkey \
-Ilvgl/src/extra/others/snapshot \
-Ilvgl/src/extra/themes/basic \
-Ilvgl/src/extra/themes/default \
-Ilvgl/src/extra/themes/mono \
-Ilvgl/src/extra/widgets/analogclock \
-Ilvgl/src/extra/widgets/animimg \
-Ilvgl/src/extra/widgets/calendar \
-Ilvgl/src/extra/widgets/carousel \
-Ilvgl/src/extra/widgets/chart \
-Ilvgl/src/extra/widgets/colorwheel \
-Ilvgl/src/extra/widgets/dclock \
-Ilvgl/src/extra/widgets/imgbtn \
-Ilvgl/src/extra/widgets/keyboard \
-Ilvgl/src/extra/widgets/led \
-Ilvgl/src/extra/widgets/list \
-Ilvgl/src/extra/widgets/menu \
-Ilvgl/src/extra/widgets/meter \
-Ilvgl/src/extra/widgets/msgbox \
-Ilvgl/src/extra/widgets/radiobtn \
-Ilvgl/src/extra/widgets/span \
-Ilvgl/src/extra/widgets/spinbox \
-Ilvgl/src/extra/widgets/spinner \
-Ilvgl/src/extra/widgets/tabview \
-Ilvgl/src/extra/widgets/tileview \
-Ilvgl/src/extra/widgets/win \
-Ilvgl/src/font \
-Ilvgl/src/hal \
-Ilvgl/src/misc \
-Ilvgl/src/widgets \
-Ilvgl \
-IUser/screenshot \
-IUser/sdcard \
-IUser/task


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"


#######################################
# LDFLAGS
#######################################
# link script
LDSCRIPT = STM32H743ZITx_FLASH.ld

# libraries
LIBS = -lc -lm -lnosys 
LIBDIR = 
LDFLAGS = $(MCU) -specs=nano.specs -u _printf_float -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
