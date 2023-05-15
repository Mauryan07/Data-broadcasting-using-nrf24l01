#include <SPI.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

RF24 radio(7, 8);  // (CE,CSN) 
const int ledPin = 2;
String receivedString = "";
String prevString = "";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, 0xF0F0F0F0E1LL);  // Set the reading pipe address
  radio.startListening();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  // Logo splash screen
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setTextWrap(false);
  display.setCursor(10, 10);
  display.println("Data Broadcasting");
  display.setCursor(45, 20);
  display.println("System");
  display.display();
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setTextWrap(false);
  display.setCursor(0, 0);
  display.println("Receiver");
  display.display();
  delay(2000);
  display.clearDisplay();

  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (radio.available()) {
    char rxData[32]; 
    radio.read(&rxData, sizeof(rxData));

    receivedString = String(rxData);
    Serial.println(receivedString);

    if (receivedString != prevString) {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setTextWrap(true);
      display.setCursor(0, 0);
      display.println(receivedString);
      display.display();
      prevString = receivedString;
    }

    receivedString.toLowerCase();
    if (receivedString.indexOf("danger") != -1 || receivedString.indexOf("cautious") != -1) {
      blinkLED();
    }
  }
}

void blinkLED() {
  digitalWrite(ledPin, HIGH);
  delay(15);
  digitalWrite(ledPin, LOW);
  delay(15);
}
