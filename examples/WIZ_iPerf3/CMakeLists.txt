set(TARGET_NAME WIZ_iPerf3)

add_executable(${TARGET_NAME}
        ${TARGET_NAME}.c
        cJSON.c
        iperf.c
        )

target_link_libraries(${TARGET_NAME}
        pico_stdlib
        hardware_spi
        hardware_dma
        ETHERNET_FILES
        IOLIBRARY_FILES
        PORT_COMMON_FILES
        )


pico_enable_stdio_usb(${TARGET_NAME} 1)
pico_enable_stdio_uart(${TARGET_NAME} 0)

pico_add_extra_outputs(${TARGET_NAME})
