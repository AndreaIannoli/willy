# 🐳 Willy - Open Source NFC/RFID Reader/Writer/Wallet

![Willy Mascot - Killer Whale](./img/willy_logo.png)

**Willy** is an open-source, homemade NFC/RFID reader and writer that supports both **high frequency (13.56 MHz)** and **low frequency (125 kHz)** tags. Willy enables you to copy, write, and store tag data on a microSD card, allowing you to use it wherever and whenever you want.

## ✨ Features
- 🌀 **Dual Frequency Support**: Read and write tags at both 13.56 MHz and 125 kHz.
- 📂 **Standalone Functionality**: Store tag data on an SD card for portable use.
- 🔋 **Compact Design**: Powered by a rechargeable 16340 battery with integrated charging and voltage regulation.
- 🎛️ **User-Friendly Interface**: Includes buttons and an on/off switch for intuitive operation.

## 🛠️ Hardware Components
- 📡 **ESP-32 WROOM**: The core microcontroller for the project.
- 🎮 **GWIOT-7941W**: Dual-frequency NFC/RFID module. [Custom library repository](https://github.com/AndreaIannoli/GWIOT-7941w).
- 💾 **MicroSD Reader/Writer Module**: For storing tag data.
- 🔋 **16340 Battery**: Rechargeable power source.
- 🔌 **16340 Battery Module**: Provides 3.3V and 5V outputs with charging functionality.
- 🔘 **Buttons and Switches**: For user interaction and power control.

## 💻 Software
Willy is powered by a custom-written library for the GWIOT-7941W module, ensuring reliable communication with NFC/RFID tags. The project firmware is written in C++ using PlatformIO.

## 🚀 Getting Started
### 📋 Prerequisites
- PlatformIO plugin installed on your IDE.
- Basic understanding of flashing firmware onto the ESP32.

### 🛠️ Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/AndreaIannoli/willy.git
   ```
2. Navigate to the project directory and open it in your IDE
3. Build and flash the firmware

### 📊 Wiring Diagram
(Insert your wiring diagram or provide a link to it.)

## 🏃‍♂️ Usage
- 🔛 Turn on Willy using the switch.
- 🕹️ Use the buttons to navigate options (e.g., read, write, wallet).
- 💾 Insert a microSD card to save tag data.

## 🛣️ Roadmap
- ➕ Add support for more tag types.
- 🌐 Implement an hybrid BLE app for tag management (both android and iOS).
- ⚡ Explore additional power optimization techniques (such as deep sleeping).

## 🤝 Contributing
Contributions are welcome! Please fork the repository and submit a pull request.

## 📜 License
This project is licensed under the Apache 2.0 License. See the [LICENSE](LICENSE) file for details.

---

### 🌊 About the Name
Willy is named after the killer whale mascot that represents the project (straight outta the '90 movie). Just like Willy, this device is powerful, versatile, and free!

---

CHEERS!🍻
