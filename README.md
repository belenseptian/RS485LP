# RS485LP (Low Power RS485 Node)

[](https://www.gnu.org/licenses/gpl-3.0)
[](https://platformio.org/)

**RS485LP** is a specialized hardware and software solution designed for low-power, long-distance communication. This project provides a custom PCB design and optimized firmware for RS485 nodes, making it ideal for battery-powered industrial sensors or remote monitoring systems.

🔗 **Official Project Website:** [https://belenseptian.github.io/RS485LP/](https://belenseptian.github.io/RS485LP/)

-----

## 🚀 Features

  * **Low Power Design:** Optimized for deep-sleep modes and minimal current draw during idle.
  * **RS485 Protocol:** Reliable differential signaling for long-range data transmission.
  * **PlatformIO Integrated:** Easy-to-compile and upload firmware using VS Code.
  * **Compact Form Factor:** Small PCB footprint suitable for tight enclosures.

-----

## 🛠 Hardware Fabrication

### 1\. Obtain Gerber Files

To manufacture the PCB, you need the Gerber files located in the `hardware/` directory of this repository.

1.  Download the `Gerber_RS485LP.zip` file.
2.  If you want to modify the design, source files for [KiCad/EasyEDA] are also provided.

### 2\. Ordering from PCBWay (or similar)

1.  Go to [PCBWay](https://www.pcbway.com/) and select **PCB Instant Quote**.
2.  Click **Add Gerber File** and upload the `.zip` folder.
3.  Use the following standard settings:
      * **Material:** FR-4
      * **Thickness:** 1.6mm
      * **Copper Weight:** 1oz
      * **Solder Mask:** [Choose your color]
4.  Submit the order and wait for delivery.

-----

## 💻 Software Setup

This project uses **PlatformIO** inside **Visual Studio Code**.

### Prerequisites

  * **VS Code:** [Download here](https://code.visualstudio.com/)
  * **PlatformIO IDE Extension:** Install this via the VS Code Extensions marketplace.

### Project Installation

1.  Clone the repository:
    ```bash
    git clone https://github.com/belenseptian/RS485LP.git
    ```
2.  Open VS Code.
3.  Go to **PlatformIO Home** \> **Open Project**.
4.  Navigate to the folder where you cloned the repo and select it.

-----

## 📤 Uploading Testing Code

1.  **Connect Hardware:** Connect your board to your computer using a USB-to-Serial adapter.
2.  **Configure Environment:** Check the `platformio.ini` file to ensure the `board` and `framework` match your hardware version.
3.  **Build:** Click the **Checkmark (✅)** icon in the bottom status bar to compile the firmware.
4.  **Upload:** Click the **Arrow (➡️)** icon to flash the code to the board.
5.  **Monitor:** Open the **Serial Monitor (🔌)** to view debug output. Set the baud rate to `115200` (or as specified in the code).

-----

## 🔌 Wiring Diagram

| Pin Name | Description | Connection |
| :--- | :--- | :--- |
| **VCC** | Power Input | 3.3V / 5V (Depends on Version) |
| **GND** | Ground | Ground |
| **A** | RS485 Data+ | Connect to Bus A |
| **B** | RS485 Data- | Connect to Bus B |

-----

## 📂 Project Structure

```text
RS485LP/
├── firmware/           # PlatformIO project files
│   ├── src/            # Main application code
│   └── platformio.ini  # Project configuration
├── hardware/           # PCB design files and Gerbers
├── docs/               # Datasheets and additional documentation
└── README.md           # This file
```

-----

## 📜 License

This project is licensed under the **GNU General Public License v3.0** - see the [LICENSE](https://www.google.com/search?q=LICENSE) file for details.

## 🤝 Contributing

Contributions are welcome\! If you have suggestions for power optimization or new features, feel free to open an **Issue** or submit a **Pull Request**.

-----

**Developed by [Belen Septian](https://www.google.com/search?q=https://github.com/belenseptian)**
