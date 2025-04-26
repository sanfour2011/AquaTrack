# AquaTrack

**AquaTrack** is an ESP32-based smart water tracking system that measures daily water consumption using a 5kg load cell and HX711 sensor. The system logs data, converts weight into milliliters, and optionally uploads it to Garmin Connect.

## Features

- ✅ **Accurate Weight Measurement**: Uses HX711 and a 5kg load cell.
- ⏳ **Real-Time Data Processing**: Converts weight into milliliters with calibration support.
- ⚡ **Interrupt-Driven Measurement**: Automatically detects changes in weight.
- ⏱ **Time Synchronization**: Uses RTC with NTP fallback.
- 📂 **Logging System**: Saves data to an SD card (CSV or SQLite).
- 🌍 **Garmin Connect Integration**: Uploads water intake data.
- 🛠 **Modular Architecture**: Easily extendable components.

## Folder Structure

```plaintext
AquaTrack/
│-- src/
│   │-- main.cpp  # Main program logic
│   │-- modules/
│   │   │-- ScaleManager.cpp  # Handles weight measurement
│   │   │-- DataProcessor.cpp  # Converts weight to ml
│   │   │-- RTCManager.cpp  # Time management
│   │   │-- SDLogger.cpp  # Logs data to storage
│   │   │-- GarminUploader.cpp  # Uploads data to Garmin
│-- include/
│   │-- ScaleManager.h
│   │-- DataProcessor.h
│   │-- RTCManager.h
│   │-- SDLogger.h
│   │-- GarminUploader.h
│-- lib/  # External libraries
│-- test/  # Unit tests
│-- platformio.ini  # ESP32 configuration
```

## Installation

1. Install [PlatformIO](https://platformio.org/).
2. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/AquaTrack.git
   ```
3. Open the project in VS Code with PlatformIO.
4. Upload the firmware to ESP32:
   ```sh
   pio run --target upload
   ```

## Usage

- 🏺 Place the water container on the load cell.
- 🛠 Press the tare button to calibrate.
- 🔄 The system will log and upload water intake automatically.

## Contributing

Feel free to contribute by submitting issues or pull requests! 🚀

## License

📜 MIT License

