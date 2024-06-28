#include "WiFiS3.h"
#include "arduino_secrets.h" 

// Your network SSID (name)
char ssid[] = "";        
// Your network password (use for WPA, or use as key for WEP)
char pass[] = "";    
int keyIndex = 0;            

int status = WL_IDLE_STATUS;
const int numButtons = 9;
int buttonPins[numButtons] = {2, 3, 4, 5, 6, 7, 8, 9, 10}; // Example pin numbers
int buttonState[numButtons];
int lastButtonState[numButtons] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
unsigned long lastDebounceTime[numButtons] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
unsigned long debounceDelay = 50; 
unsigned long cooldownPeriod = 5000;
unsigned long lastPressTime[numButtons] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
// Server details
char server[] = "192.168.31.36";  // Replace with your server's address
int port = 3000;  // Use the correct port for your server, usually 80 for HTTP

String owner = "Basia";

WiFiClient client;

void setup() {
  Serial.begin(9600);

  while (!Serial) ; // wait for serial port to connect
  // Initialize buttons as inputs
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT);
  }
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  // Check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true); // Don't continue
  }
  
  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }
  
  // Attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network
    delay(10000); // Wait 10 seconds for connection
  }
  printWifiStatus();
}

void loop() {
for (int i = 0; i < numButtons; i++) {
    int reading = digitalRead(buttonPins[i]);
    if (reading != lastButtonState[i]) {
      lastDebounceTime[i] = millis();
    }
    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      if (reading != buttonState[i]) {
        buttonState[i] = reading;
        if (buttonState[i] == HIGH && (millis() - lastPressTime[i] > cooldownPeriod)) {
          handleButtonPress(i + 1); // +1 to avoid sending 0
          lastPressTime[i] = millis(); // Update last press time
        }
      }
    }
    lastButtonState[i] = reading;
  }
}

void handleButtonPress(int buttonNumber) {
  // Your existing code to connect to server and send data
  // Use 'buttonNumber' as the data to be sent
  if (client.connected()) {
      makeRequest(owner,buttonNumber);
      client.flush();
  } else {
    Serial.println("\nStarting connection to server...");
      if (client.connect(server, port)) {
      Serial.println("Connected to server");
      makeRequest(owner,buttonNumber);
    } else {
      Serial.println("Connection failed");
    }
  }
  // Connect to server and send data
}

void printWifiStatus() {
  // Print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // Print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // Print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void makeRequest(String name, int number) {
  Serial.println("Making a POST request to the server...");
  String json = "{";
  json += "\"name\": \"" + String(name) + "\", ";
  json += "\"number\": " + String(number);
  json += "}";
  Serial.println(json);
  client.println("POST /api/alert HTTP/1.1");
  client.println("Host: your-server-address.com");
  client.println("Content-Type: application/json");
  client.print("Content-Length: ");
  client.println(json.length());
  client.println();
  client.println(json);
}

String getMessage(int pinNum){
  switch(pinNum){
    case 1: return "Jestem głodny";
    case 2: return "Chcę pić";
    case 3: return "Potrzebuję do toalety";
    case 4: return "Potrzebuję pomocy";
    case 5: return "Chcę się pobawić";
    case 6: return "Chcę iść na spacer";
    case 7: return "Coś mnie boli";
    case 8: return "Stresuję się";
    case 9: return "Jest za głośno";
    default: return "Error";
  }
}
