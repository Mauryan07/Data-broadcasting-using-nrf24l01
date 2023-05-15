#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <RF24.h>
#include <EEPROM.h>

const char* ssid = "MyNodeMCU";
const char* password = "myPassword";

ESP8266WebServer server(80);

RF24 radio(2, 4);

String inputString = "";
bool sendMessage = false;

int address = 0; // EEPROM starting address 

void setup() {
  Serial.begin(9600);

  WiFi.softAP(ssid, password);
  Serial.print("Access Point IP address: ");
  Serial.println(WiFi.softAPIP());

  radio.begin();
  radio.openWritingPipe(0xF0F0F0F0E1LL);  

  EEPROM.begin(512); // Initialize EEPROM
  char storedData[512];
  int i;
  for (i = 0; i < 512; ++i) {
    storedData[i] = EEPROM.read(address + i); // Read stored data from EEPROM
    if (storedData[i] == '\0') {
      break; 
    }
  }
  EEPROM.end(); // Release EEPROM resources

  inputString = storedData; 

 server.on("/", [](){
    String html = "<html><head>";
    html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
    html += "<style>";
    html += "body {";
    html += "  background-color: #f1f1f1;";
    html += "  font-family: Arial, sans-serif;";
    html += "  padding: 20px;";
    html += "}";

    html += "h1 {";
    html += "  text-align: center;";
    html += "  color: #333333;";
    html += "}";

    html += "form {";
    html += "  margin-top: 20px;";
    html += "  text-align: center;";
    html += "}";

    html += "input[type=\"text\"] {";
    html += "  width: 100%;";
    html += "  padding: 10px;";
    html += "  font-size: 18px;";
    html += "  margin-bottom: 10px;";
    html += "}";

    html += "input[type=\"submit\"] {";
    html += "  width: 100%;";
    html += "  padding: 10px;";
    html += "  font-size: 18px;";
    html += "  background-color: #4CAF50;";
    html += "  color: white;";
    html += "  border: none;";
    html += "  cursor: pointer;";
    html += "}";

    html += "p {";
    html += "  text-align: center;";
    html += "  margin-top: 10px;";
    html += "}";

    html += "</style>";
    html += "</head><body>";
    html += "<h1>Data Broadcasting System</h1>";
    html += "<form method=\"get\" action=\"/submit\">";
    html += "<input type=\"text\" name=\"input\" placeholder=\"Enter your message\">";
    html += "<br>";
    html += "<input type=\"submit\" value=\"Submit\">";
    html += "</form>";
    html += "<br>";
    html += "<br>";
    html += "<p>Made by: </p>";
    html += "<p>Chandraprakash Maurya</p>";
    html += "<p>&</p>";
    html += "<p>Alvin</p>";
    html += "</body></html>";
    server.send(200, "text/html", html);
});



  server.on("/submit", [](){
    inputString = server.arg("input");
    EEPROM.begin(512); 
    for (int i = 0; i < inputString.length(); ++i) {
      EEPROM.write(address + i, inputString[i]); // Store character in EEPROM
    }
    EEPROM.write(address + inputString.length(), '\0'); 
    EEPROM.commit();
    EEPROM.end(); 
    server.sendHeader("Location", String("/"), true);
    server.send(302, "text/plain", ""); 
    sendMessage = true; // indicate that message should be sent
  });

  server.begin();
}

void loop() {
  server.handleClient();

  if (sendMessage || inputString.length() > 0) {
    radio.write(inputString.c_str(), inputString.length() + 1);
    Serial.println("Data sent: " + inputString);
    sendMessage = false; // indicate that message has been sent
    delay(500); 
  }

  // Check for new messages to update inputString
  if (Serial.available()) {
    String newString = Serial.readStringUntil('\n');
    newString.trim(); 
    if (newString.length() > 0) {
      inputString = newString;
      EEPROM.begin(512); 
      for (int i = 0; i < inputString.length(); ++i) {
        EEPROM.write(address + i, inputString[i]); 
      }
      EEPROM.write(address + inputString.length(), '\0'); 
      EEPROM.commit(); 
            EEPROM.end(); 
      server.sendHeader("Location", String("/"), true);
      server.send(302, "text/plain", ""); 
      sendMessage = true; 
    }
  }

  // Retransmit stored string from EEPROM repeatedly
  if (!sendMessage && inputString.length() == 0) {
    EEPROM.begin(512); 
    char storedData[512];
    int i;
    for (i = 0; i < 512; ++i) {
      storedData[i] = EEPROM.read(address + i); 
      if (storedData[i] == '\0') {
        break; 
      }
    }
    EEPROM.end(); // Release EEPROM resources

    if (i > 0) {
      inputString = storedData; 
      sendMessage = true; 
    }
  }
}

