# WIZnet-PICO-IPERF3-C

This project demonstrates high-speed Ethernet communication performance testing using **RP2040**, **RP2350**, and **WIZnet Ethernet chips** with the **iperf3** tool.

The system acts as an iperf3 server, allowing you to measure upload and download throughput between your PC and the board over Ethernet.

---

- [Development Environment Configuration](#development-environment-configuration)
- [Hardware Requirements](#hardware-requirements)
- [Example Structure](#example-structure)
- [Example Testing](#example-testing)

---

## Development Environment Configuration

This project supports the following boards:

- WIZnet Ethernet HAT
- W5100S-EVB-Pico
- W5500-EVB-Pico
- W55RP20-EVB-Pico
- W6100-EVB-Pico
- W6300-EVB-Pico
- W5100S-EVB-Pico2
- W5500-EVB-Pico2
- W6100-EVB-Pico2
- W6300-EVB-Pico2

> The development environment was tested on **Windows** using **Visual Studio Code**. Please refer to the official Raspberry Pi Pico SDK guide for setup instructions.

## Hardware Requirements

The project is compatible with the following WIZnet boards:

| Board/Module Name | MCU | Ethernet Chip | Interface | Socket # | TX/RX Buffer | Notes |
|:---|:---|:---|:---|:---|:---|:---|
| WIZnet Ethernet HAT |  | W5100S | SPI | 4 | 16KB | RP Pico-compatible |
| W5100S-EVB-Pico | RP2040 | W5100S | SPI | 4 | 16KB |  |
| W5500-EVB-Pico | RP2040 | W5500 | SPI | 8 | 32KB |  |
| W55RP20-EVB-Pico | RP2040 | W5500 | SPI (PIO) | 8 | 32KB | SiP: RP2040 + W5500 |
| W6100-EVB-Pico | RP2040 | W6100 | SPI | 8 | 32KB | Supports IPv4/IPv6 |
| W6300-EVB-Pico | RP2040 | W6300 | QSPI (PIO) | 8 | 64KB | Supports IPv4/IPv6 |
| W5100S-EVB-Pico2 | RP2350 | W5100S | SPI | 4 | 16KB |  |
| W5500-EVB-Pico2 | RP2350 | W5500 | SPI | 8 | 32KB |  |
| W6100-EVB-Pico2 | RP2350 | W6100 | SPI | 8 | 32KB | Supports IPv4/IPv6 |
| W6300-EVB-Pico2 | RP2350 | W6300 | QSPI (PIO) | 8 | 64KB | Supports IPv4/IPv6 |

## Example Structure

The example directory is organized as follows:

```
WIZnet-PICO-IPERF3-C
┣ examples
    ┗ WIZ_iperf3
```

Only the **WIZ_iperf3** example is provided, specifically designed for Ethernet speed testing using iperf3.

## Example Testing

### 1. Clone the Project

Clone the project along with its submodules:

```cmd
cd [your desired directory]
git clone --recurse-submodules https://github.com/[your-repository]/WIZnet-PICO-IPERF3-C.git
```

### 2. Configure the Board

Open the **CMakeLists.txt** file and set the correct board name. Example:

```cmake
# Set board
set(BOARD_NAME W5500_EVB_PICO)
```

For W6300-EVB-Pico QSPI mode settings:

```cmake
# Set QSPI MODE for W6300
add_definitions(-D_WIZCHIP_QSPI_MODE_=QSPI_QUAD_MODE)
```

### 3. Build and Flash

Build the project and flash the firmware onto your board using Visual Studio Code or command-line tools.

### 4. Testing with iperf3

Open a PowerShell or Command Prompt, move to the iperf3 installation directory, and run:

```cmd
.\iperf3 -c 192.168.11.2 -t 10
```

- This command starts a 10-second iperf3 communication test.
- Make sure your board's IP address is correctly set to **192.168.11.2**.

---

# Notes

- The **WIZnet ioLibrary_Driver** is used for Ethernet chip drivers.
- The **pico-sdk** must be configured properly before building.
- Ensure Ethernet cables and network environment are properly set up to avoid performance bottlenecks.

---

Thank you for using WIZnet products for your high-speed Ethernet communication projects!