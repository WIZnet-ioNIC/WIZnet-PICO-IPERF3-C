set(TARGET_NAME wizchip_iperf_toe)

add_executable(${TARGET_NAME}
        ${TARGET_NAME}.c
        )

target_sources(${TARGET_NAME} PRIVATE
        ./../cJSON.c
        ./../iperf.c
        )

target_include_directories(${TARGET_NAME} PRIVATE
        ./../
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
