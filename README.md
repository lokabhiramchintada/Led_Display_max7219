# Led_Display_max7219


---


# ESP32 LED Matrix Web Display

This project allows you to control an LED Matrix display (using MAX7219 modules) via a web interface hosted on an ESP32. You can send custom scrolling messages to the LED display in real-time over WiFi.

## 📦 Features

- ESP32 hosts a simple HTML page with an input box.
- Sends user input to the ESP32 using HTTP POST.
- Displays the message on a scrolling LED matrix (MAX7219).
- Real-time updates via browser without restarting the ESP32.

## 🧰 Hardware Requirements

- ESP32 Dev Board
- MAX7219-based LED Matrix display (4-in-1 or more)
- Jumper wires
- Breadboard (optional)

## 🔌 Wiring (change pins if needed)

| ESP32 Pin | MAX7219 Pin |
|-----------|-------------|
| GPIO 15   | DIN         |
| GPIO 4    | CLK         |
| GPIO 2    | CS          |
| 3.3V or 5V| VCC         |
| GND       | GND         |

> Note: This setup uses `MD_Parola` and `MD_MAX72xx` libraries to control the display.

## 📲 Web Interface

Once the ESP32 connects to WiFi, it hosts a web page at its IP address (e.g., `http://192.168.1.xxx`). Open it in a browser on the same network to:

- Type a message in the input box
- Click **Send**
- Watch your message scroll on the LED matrix!

## 🔧 Installation & Setup

1. **Install Arduino Libraries:**
   - `MD_Parola`
   - `MD_MAX72xx`
   - `WiFi` (built-in for ESP32)
   - `WebServer` (built-in for ESP32)

2. **Update WiFi Credentials:**
   Replace these lines in the code with your WiFi SSID and password:

   ```
   const char *ssid = "myssid";
   const char *password = "11111111";
   ```

3. **Upload Code to ESP32:**
   - Use Arduino IDE or PlatformIO.
   - Select correct board and port.
   - Upload the code.

4. **Find IP Address:**
   - Open Serial Monitor (baud rate 115200).
   - Wait for "WiFi connected" message and note the IP.

5. **Open in Browser:**
   - Go to the displayed IP in your browser.
   - Enter a message and hit send.



## 🧪 Troubleshooting

- **LED Matrix not working?**
  - Double-check wiring (DIN, CLK, CS).
  - Ensure power is sufficient (some matrices need 5V).
- **Can't connect to WiFi?**
  - Ensure credentials are correct.
  - Use a 2.4GHz WiFi network (ESP32 doesn't support 5GHz).
- **Display not scrolling?**
  - Make sure `MD_Parola` and `MD_MAX72xx` libraries are installed correctly.

## 📜 License

MIT License

---

Made with ❤️ using ESP32, MD_Parola, and some JavaScript magic.
