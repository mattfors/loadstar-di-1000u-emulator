String inputBuffer = "";  // String to store the incoming data
unsigned long lastTime = 0;  // Store the last time `WC` was sent
bool wcActive = false;  // Flag to check if `WC` should be sent every 10ms

void setup() {
  Serial.begin(9600);
  while (!Serial);
}

void loop() {
  if (Serial.available() > 0) {
    char receivedChar = Serial.read(); // Read the incoming byte
    wcActive = false;
    if (receivedChar == '\r') {
      processCommand(inputBuffer);
      inputBuffer = "";
    } else {
      inputBuffer += receivedChar;
    }
  }
  
  if (wcActive && millis() - lastTime >= 100) { 
    Serial.println("3.04");
    lastTime = millis();
  }
}

// Function to process the received command
void processCommand(String command) {
  if (command == "") {
    Serial.println("A");
  }
  else if (command == "MODEL") {
    Serial.println("FCM DI-1000");
  }
  else if (command == "ID") {
    Serial.println("SENSOR 1");
  }
  else if (command == "W") {
    Serial.println("3.04");
  }
  else if (command == "WC") {
    wcActive = true;
    Serial.println("3.04");
    lastTime = millis();
  }
  else {
    Serial.println("E");
  }
}