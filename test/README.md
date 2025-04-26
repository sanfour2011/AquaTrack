# AquaTrack Test Suite

This directory contains the test suite for the AquaTrack project, organized to ensure thorough and reliable testing of all components.

## Structure Overview

The test suite is divided into three main categories:

* **`unit/`**: Contains unit tests that verify the functionality of individual modules in isolation. These tests utilize Google Mock for mocking dependencies and can be run without hardware.
* **`hardware/`**: Contains hardware tests that verify the functionality of the system with actual hardware components.
* **`integration/`**: Contains integration tests that verify the interaction between different modules.
* **`fixtures/`**: Contains shared test fixtures used across unit and integration tests.

## Directory Breakdown

### `Native/`

This directory houses unit tests, which are designed to test individual components of the system in isolation.

* **`scale/`**:
    * `test_calibration.cpp`: Tests the calibration functionality of the scale.
    * `test_tare.cpp`: Tests the tare functionality of the scale.
    * `test_ml_conversion.cpp`: Tests the conversion of weight to milliliters.
    * `mocks/`: Contains Google Mock classes for the HX711 sensor (`mock_hx711.h`).
    * `fixtures/`: Contains helper classes for setting up scale tests (`scale_test_fixture.h`).
* **`data/`**:
    * `test_csv_write.cpp`: Tests the functionality of writing data to CSV files.
    * `test_sqlite_write.cpp`: Tests the functionality of writing data to SQLite databases.
    * `test_data_retrieval.cpp`: Tests the retrieval of data from storage.
    * `data/`: Contains example test data (`test_data.csv`).
* **`EventDispatcher/`**:
    * `test_EventDispatcher.cpp`: Tests the functionality of the intermodule communication 
* **`rtc/`**:
    * `test_time_conversion.cpp`: Tests the conversion of time formats.
    * `mocks/`: Contains Google Mock classes for the RTC module (`mock_rtc.h`).
    * `fixtures/`: Contains helper classes for setting up RTC tests (`rtc_test_fixture.h`).
* **`connectivity/`**:
    * `test_garmin_upload_mock.cpp`: Simulates the upload of data to Garmin Connect using PC-based WiFi.
    * `test_http_request.cpp`: Tests HTTP request functionality.
    * `test_error_handling.cpp`: Tests error handling within the connectivity module.
    * `mocks/`: Contains Google Mock classes for network operations (`mock_network.h`).
    * `fixtures/`: Contains helper classes for setting up network tests (`network_test_fixture.h`).
* `README.md`: Provides an overview of the unit tests.

### `hardware/`

This directory contains tests that require actual hardware to be present.

* **`scale/`**:
    * `test_hx711.cpp`: Tests the functionality of the HX711 sensor.
    * `test_real_measurement.cpp`: Tests real-world weight measurements.
* **`rtc/`**:
    * `test_ntp_sync.cpp`: Tests NTP time synchronization.
    * `test_battery_backup.cpp`: Tests the battery backup functionality of the RTC.
* **`connectivity/`**:
    * `test_wifi_connection.cpp`: Tests the WiFi connection on the ESP32.
    * `test_garmin_upload_hw.cpp`: Tests the upload of data to Garmin Connect directly from the ESP32.
* **`display/`**:
    * `test_eink_init.cpp`: Tests the initialization of the E-Ink display.
    * `test_eink_render.cpp`: Tests the rendering of text and graphics on the E-Ink display.
    * `test_eink_power.cpp`: Tests the power-saving modes of the E-Ink display.
* `README.md`: Provides an overview of the hardware tests.

### `integration/`

This directory contains tests that verify the interaction between different modules.

* `test_scale_data_flow.cpp`: Tests the data flow from the scale to the data processing modules.
* `test_rtc_data_logging.cpp`: Tests the integration of the RTC with the data logging modules.
* `README.md`: Provides an overview of the integration tests.

### `fixtures/`

This directory contains shared test fixtures used across unit and integration tests.

* `test_setup.h`: Contains common setup routines for tests.

### Configuration

* `unity_config.cpp`: Configuration file for the Unity test framework.
* `unity_config.h`: Header file for the Unity test framework configuration.

## Running Tests

To run the tests, use the PlatformIO test command. Ensure that the necessary hardware is connected for hardware tests.

```bash
pio test
```

