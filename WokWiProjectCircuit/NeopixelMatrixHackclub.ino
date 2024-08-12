#include <WiFi.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>

#define PIN            5 
#define MATRIX_WIDTH   32
#define MATRIX_HEIGHT  8

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(MATRIX_WIDTH, MATRIX_HEIGHT, PIN, 
                                              NEO_MATRIX_TOP   + NEO_MATRIX_LEFT +
                                              NEO_MATRIX_ROWS  + NEO_MATRIX_ZIGZAG,
                                              NEO_GRB + NEO_KHZ800);

const char* ssid = "Wokwi-GUEST";
const char* host = "raw.githubusercontent.com";
const char* url = "/YeetTheAnson/NeopixelMatrixHackclub/main/orpheusflagleft.bmp";

void setup() {
  Serial.begin(115200);

  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.show();
  WiFi.begin(ssid);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");

  fetchAndDisplayBMP(host, url);
}

void loop() {
  //Haha you found me, and empty loop :p
}

void fetchAndDisplayBMP(const char* host, const char* url) {
  WiFiClient client;

  if (!client.connect(host, 80)) {
    Serial.println("Connection failed");
    return;
  }

  // DISCLAIMER: THIS SECTION IS GENERATED BY CHATGPT
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");

  // Wait for the response
  while (!client.available()) {
    delay(100);
  }

  // Skip headers
  while (client.available()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break; // End of headers
    }
  }

  //END OF CHATGPT SECTION
  parseAndDisplayBMP(client);
}

  matrix.show();
}
