# How to Test WIZ_iPerf3 Example



## Step 1: Prepare software

The following serial terminal program is required for iPerf3 example test, download and install from below link.

- [**Tera Term**][link-tera_term]
- [**iperf 3**][link-iperf]

## Step 2: Prepare hardware

If you are using WIZnet's PICO board, you can skip '1. Combine...'

1. If you are using WIZnet Ethernet HAT, Combine it with Raspberry Pi Pico.

2. Connect ethernet cable to your PICO board ethernet port.

3. Connect your PICO board to desktop or laptop using USB cable. 



## Step 3: Setup WIZ_iPerf3 Example

To test the WIZ_iPerf3 example, minor settings shall be done in code.

1. Setup SPI port and pin in 'wizchip_spi.h' in 'WIZnet-PICO-IPERF3-C/port/ioLibrary_Driver/' directory.

Setup the SPI interface you use.

### For **W55RP20-EVB-PICO**:
If you are using the **W55RP20-EVB-PICO**, enable `USE_PIO` and configure as follows:

```cpp
#if (DEVICE_BOARD_NAME == W55RP20_EVB_PICO)

#define USE_PIO

#define PIN_SCK   21
#define PIN_MOSI  23
#define PIN_MISO  22
#define PIN_CS    20
#define PIN_RST   25
#define PIN_IRQ   24

```

---

### For **W6300-EVB-PICO** or **W6300-EVB-PICO2**:
If you are using the **W6300-EVB-PICO** or **W6300-EVB-PICO2**, use the following pinout and SPI clock divider configuration:

```cpp
#elif (DEVICE_BOARD_NAME == W6300_EVB_PICO || DEVICE_BOARD_NAME == W6300_EVB_PICO2)
#define USE_PIO

#define PIO_IRQ_PIN             15
#define PIO_SPI_SCK_PIN         17
#define PIO_SPI_DATA_IO0_PIN    18
#define PIO_SPI_DATA_IO1_PIN    19
#define PIO_SPI_DATA_IO2_PIN    20
#define PIO_SPI_DATA_IO3_PIN    21
#define PIN_CS                  16
#define PIN_RST                 22


```

---

### For other generic SPI boards
If you are not using any of the above boards, you can fall back to a default SPI configuration:

```cpp
#else

#define SPI_PORT spi0

#define SPI_SCK_PIN  18
#define SPI_MOSI_PIN 19
#define SPI_MISO_PIN 16
#define SPI_CS_PIN   17
#define RST_PIN      20

#endif
```

Make sure you are **not defining `USE_PIO`** in your setup when using DMA:

```cpp
// #define USE_PIO
```

2. Setup network configuration such as IP in 'WIZ_iPerf3.c' which is the iperf3 example in 'WIZnet-PICO-IPERF3-C/examples/WIZ_iPerf3/' directory.

Setup IP and other network settings to suit your network environment.

```cpp
/* Network */
static wiz_NetInfo g_net_info =
    {
        .mac = {0x00, 0x08, 0xDC, 0x12, 0x34, 0x56}, // MAC address
        .ip = {192, 168, 11, 2},                     // IP address
        .sn = {255, 255, 255, 0},                    // Subnet Mask
        .gw = {192, 168, 11, 1},                     // Gateway
        .dns = {8, 8, 8, 8},                         // DNS server
        #if _WIZCHIP_ > W5500
        .lla = {0xfe, 0x80, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00,
                0x02, 0x08, 0xdc, 0xff,
                0xfe, 0x57, 0x57, 0x25},             // Link Local Address
        .gua = {0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00},             // Global Unicast Address
        .sn6 = {0xff, 0xff, 0xff, 0xff,
                0xff, 0xff, 0xff, 0xff,
                0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00},             // IPv6 Prefix
        .gw6 = {0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00},             // Gateway IPv6 Address
        .dns6 = {0x20, 0x01, 0x48, 0x60,
                0x48, 0x60, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x88, 0x88},             // DNS6 server
        .ipmode = NETINFO_STATIC_ALL
#else
        .dhcp = NETINFO_STATIC        
#endif
};
```

3. Setup iperf3 configuration in 'WIZ_iPerf3.c' in 'WIZnet-PICO-IPERF3-C/examples/WIZ_iPerf3/' directory.



## Step 4: Build

1. After completing the iperf3 example configuration, click 'build' in the status bar at the bottom of Visual Studio Code or press the 'F7' button on the keyboard to build.

2. When the build is completed, 'WIZ_iPerf3.uf2' is generated in 'WIZnet-PICO-IPERF3-C/build/examples/WIZ_iPerf3/' directory.



## Step 5: Upload and Run

1. While pressing the BOOTSEL button of the Pico power on the board, the USB mass storage 'RPI-RP2' or 'RP2350' is automatically mounted.

![][link-raspberry_pi_pico_usb_mass_storage]

2. Drag and drop 'WIZ_iPerf3.uf2' onto the USB mass storage device 'RPI-RP2' or 'RP2350'.

3. Connect to the serial COM port of the pico with Tera Term.

![][link-connect_to_serial_com_port]

4. Reset your board.

![][link-connect_to_serial_com_port2]

5. Open a PowerShell or Command Prompt window, navigate to the directory where iperf3 is installed, and enter the command:

```cmd
.\iperf3 -c 192.168.11.2 -t 10
```

This will allow you to perform iperf3 communication as shown below.
In my case, I set the PICO board’s IP address to 192.168.11.2 in the pico iperf project.


![][link-iperf3_2]



<!--
Link
-->

[link-tera_term]: https://osdn.net/projects/ttssh2/releases/
[link-iperf3]: https://iperf.fr/iperf-download.php
[link-raspberry_pi_pico_usb_mass_storage]: https://github.com/WIZnet-ioNIC/WIZnet-PICO-IPERF3-C/blob/main/static/images/WIZ_iperf3/raspberry_pi_pico_usb_mass_storage.png
[link-connect_to_serial_com_port]: https://github.com/WIZnet-ioNIC/WIZnet-PICO-IPERF3-C/blob/main/static/images/WIZ_iperf3/connect_to_serial_com_port.png
[link-connect_to_serial_com_port2]: https://github.com/WIZnet-ioNIC/WIZnet-PICO-IPERF3-C/blob/main/static/images/WIZ_iperf3/connect_to_serial_com_port2.png
[link-iperf3_2]: https://github.com/WIZnet-ioNIC/WIZnet-PICO-IPERF3-C/blob/main/static/images/WIZ_iperf3/iperf3_2.png