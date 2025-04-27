# Robo-Connect

Robo-Connect is an Android application designed for real-time monitoring of sensor data using a REST-based API. This project integrates an ESP32 microcontroller to collect data from various sensors and display it on the Android app. The app provides a user-friendly interface to monitor sensor readings such as temperature, humidity, sound levels, and knock detection.

## Features

- **Real-Time Sensor Monitoring**: Displays live data from sensors connected to the ESP32 microcontroller.
- **REST API Integration**: Fetches sensor data from the ESP32 server using HTTP requests.
- **Knock Detection**: Monitors and displays knock events.
- **Sound Level Monitoring**: Displays sound levels in decibels.
- **Temperature and Humidity Monitoring**: Displays temperature in Celsius and humidity in percentage.
- **User-Friendly Interface**: Simple and intuitive UI for easy monitoring.

## Project Structure

### Android Application (`IOT APP`)

- **MainActivity.java**: Handles the initial connection setup by allowing the user to input the ESP32 server's IP address.
- **MainActivity2.java**: Fetches and displays real-time sensor data from the ESP32 server.
- **Layouts**:
  - `activity_main.xml`: UI for entering the ESP32 server's IP address.
  - `activity_main2.xml`: UI for displaying sensor data.
- **Resources**:
  - `strings.xml`: Contains app text resources.
  - `colors.xml`: Defines the color scheme for the app.
  - `themes.xml`: Configures the app's theme.

### ESP32 API Server (`ESP32_API_SERVER`)

- **ESP32_API_SERVER.ino**: Arduino sketch for the ESP32 microcontroller. It:
  - Connects to a Wi-Fi network.
  - Hosts a web server to serve sensor data via a REST API.
  - Reads data from sensors (e.g., knock sensor, sound sensor).
  - Formats sensor data as JSON and serves it to the Android app.
- **DHT11_ESP32.h**: Custom library for reading temperature and humidity data from a DHT11 sensor.

## How It Works

1. **ESP32 Setup**:
   - The ESP32 connects to a Wi-Fi network and starts a web server.
   - It reads data from connected sensors (e.g., knock sensor, sound sensor).
   - The data is served as a JSON response via the REST API.

2. **Android App**:
   - The user enters the ESP32 server's IP address in the app.
   - The app fetches sensor data from the ESP32 server at regular intervals.
   - The data is displayed in a user-friendly interface.

## Prerequisites

### Hardware
- ESP32 microcontroller.
- Sensors:
  - Knock sensor.
  - Sound sensor.
  - DHT11 temperature and humidity sensor.

### Software
- Android Studio for building and running the Android app.
- Arduino IDE for programming the ESP32.

## Setup Instructions

### ESP32 API Server
1. Open `ESP32_API_SERVER.ino` in the Arduino IDE.
2. Update the Wi-Fi credentials (`ssid` and `password`) in the code.
3. Connect the sensors to the ESP32 as per the pin configuration in the code.
4. Upload the sketch to the ESP32.
5. Note the IP address displayed in the serial monitor after the ESP32 connects to Wi-Fi.

### Android App
1. Open the `IOT APP` folder in Android Studio.
2. Build and run the app on an Android device.
3. Enter the ESP32 server's IP address in the app and click "Connect".
4. View real-time sensor data on the app.

## Dependencies

### Android App
- [Android Volley](https://developer.android.com/training/volley) for HTTP requests.
- AndroidX libraries for UI components.

### ESP32 API Server
- [ArduinoJson](https://arduinojson.org/) for JSON handling.
- [WiFi](https://www.arduino.cc/en/Reference/WiFi) library for Wi-Fi connectivity.

## Screenshots

### Main Screen
- Allows the user to input the ESP32 server's IP address.

### Sensor Data Screen
- Displays real-time sensor data, including:
  - Temperature.
  - Humidity.
  - Knock detection status.
  - Sound levels.

## Future Enhancements

- Add support for more sensors.
- Implement secure communication between the app and the ESP32 server.
- Add data logging and visualization features.

## License

This project is licensed under the Apache License 2.0. See the `LICENSE` file for details.
