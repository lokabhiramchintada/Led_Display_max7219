#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

// WiFi credentials
const char *ssid = "myssid";
const char *password = "11111111";

// LED Matrix settings
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CLK_PIN   4
#define DATA_PIN  15
#define CS_PIN    2
MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// Scrolling settings
uint8_t scrollSpeed = 70;
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_LEFT;
uint16_t scrollPause = 2000;

// Message to display
String payload = "Send a message to me!";
char displayMsg[100];

// Web server on port 80
WebServer server(80);

void wifi_init() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nWiFi connected.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// Serve the HTML page with input box
void handleRoot() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <title>ESP32 LED Display</title>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <style>
        body { font-family: Arial; text-align: center; margin-top: 50px; }
        input[type="text"] { width: 60%; padding: 10px; font-size: 18px; }
        button { padding: 10px 20px; font-size: 18px; }
      </style>
    </head>
    <body>
      <h2>Send Message to ESP32 LED Matrix</h2>
      <input type="text" id="msg" placeholder="Enter your message here">
      <button onclick="sendMsg()">Send</button>
      <p id="response"></p>

      <script>
        function sendMsg() {
          let msg = document.getElementById("msg").value;
          fetch('/post_data', {
            method: 'POST',
            headers: { 'Content-Type': 'application/x-www-form-urlencoded' },
            body: 'message=' + encodeURIComponent(msg)
          })
          .then(response => response.text())
          .then(data => {
            document.getElementById("response").innerText = data;
          });
        }
      </script>
    </body>
    </html>
  )rawliteral";

  server.send(200, "text/html", html);
}

// Handle incoming POST request
void handlePost() {
  if (server.hasArg("message")) {
    payload = server.arg("message");
    Serial.println("Received POST message: " + payload);

    payload.toCharArray(displayMsg, sizeof(displayMsg));  // Update message buffer
    P.displayText(displayMsg, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
    P.displayReset();

    server.send(200, "text/plain", "✅ Message displayed: " + payload);
  } else {
    server.send(400, "text/plain", "⚠️ Missing 'message' parameter!");
  }
}

void setup() {
  Serial.begin(115200);
  wifi_init();

  P.begin();
  payload.toCharArray(displayMsg, sizeof(displayMsg));
  P.displayText(displayMsg, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
  P.displayReset();

  // Set up server routes
  server.on("/", HTTP_GET, handleRoot);
  server.on("/post_data", HTTP_POST, handlePost);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();

  if (P.displayAnimate()) {
    P.displayText(displayMsg, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
    P.displayReset();
  }
}
