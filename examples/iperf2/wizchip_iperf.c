/**
    Copyright (c) 2021 WIZnet Co.,Ltd

    SPDX-License-Identifier: BSD-3-Clause
*/

/**
    ----------------------------------------------------------------------------------------------------
    Includes
    ----------------------------------------------------------------------------------------------------
*/
#include <stdio.h>
#include <string.h>
#include "port_common.h"

#include "wizchip_conf.h"
#include "wizchip_spi.h"

#include "socket.h"

/**
    ----------------------------------------------------------------------------------------------------
    Macros
    ----------------------------------------------------------------------------------------------------
*/
/* Buffer */
#define ETHERNET_BUF_MAX_SIZE (1024 * TX_RX_MAX_SIZE )

/* Socket */
#define SOCKET_IPERF 0

/* Port */
#define PORT_IPERF 5001

/**
    ----------------------------------------------------------------------------------------------------
    Variables
    ----------------------------------------------------------------------------------------------------
*/
/* Network */
static wiz_NetInfo g_net_info = {
    .mac = {0x00, 0x08, 0xDC, 0x12, 0x34, 0x56}, // MAC address
    .ip = {192, 168, 11, 2},                     // IP address
    .sn = {255, 255, 255, 0},                    // Subnet Mask
    .gw = {192, 168, 11, 1},                     // Gateway
    .dns = {8, 8, 8, 8},                         // DNS server
#if _WIZCHIP_ > W5500
    .lla = {
        0xfe, 0x80, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x02, 0x08, 0xdc, 0xff,
        0xfe, 0x57, 0x57, 0x25
    },             // Link Local Address
    .gua = {
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    },             // Global Unicast Address
    .sn6 = {
        0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    },             // IPv6 Prefix
    .gw6 = {
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    },             // Gateway IPv6 Address
    .dns6 = {
        0x20, 0x01, 0x48, 0x60,
        0x48, 0x60, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x88, 0x88
    },             // DNS6 server
    .ipmode = NETINFO_STATIC_ALL
#else
    .dhcp = NETINFO_STATIC
#endif
};

/* iperf */
static uint8_t g_iperf_buf[ETHERNET_BUF_MAX_SIZE * 2] = {
    0,
};

/**
    ----------------------------------------------------------------------------------------------------
    Functions
    ----------------------------------------------------------------------------------------------------
*/

/**
    ----------------------------------------------------------------------------------------------------
    Main
    ----------------------------------------------------------------------------------------------------
*/
int main() {
    uint8_t memsize[2][8] = {{TX_RX_MAX_SIZE, 0, 0, 0, 0, 0, 0, 0},
        {TX_RX_MAX_SIZE, 0, 0, 0, 0, 0, 0, 0}
    };

    /* Initialize */
    int retval = 0;
    uint32_t pack_len = 0;

    stdio_init_all();
    sleep_ms(3000);

    printf("system clock: %d MHz\n", clock_get_hz(clk_sys) / 1000000);
    wizchip_spi_initialize();
    wizchip_cris_initialize();

    wizchip_reset();
    wizchip_initialize_whitout_buffer_set();

    if (ctlwizchip(CW_INIT_WIZCHIP, (void *)memsize) == -1) {
        printf("wizchip initialized fail\n");
    }

    wizchip_check();

    network_initialize(g_net_info);

    /* Get network information */
    print_network_information(g_net_info);
    while (1) {
        switch (getSn_SR(SOCKET_IPERF)) {
        case SOCK_ESTABLISHED :
            while (1) {
                getsockopt(SOCKET_IPERF, SO_RECVBUF, &pack_len);
                if (pack_len > 0) {
                    recv(SOCKET_IPERF, (uint8_t *)g_iperf_buf, ETHERNET_BUF_MAX_SIZE - 1);
                }
            }
        case SOCK_CLOSE_WAIT :
            disconnect(SOCKET_IPERF);
            break;
        case SOCK_INIT :
            listen(SOCKET_IPERF);
            break;
        case SOCK_CLOSED:
            socket(SOCKET_IPERF, Sn_MR_TCP, PORT_IPERF, 0x20);
            break;
        default:
            break;
        }
    }
}


/**
    ----------------------------------------------------------------------------------------------------
    Functions
    ----------------------------------------------------------------------------------------------------
*/
