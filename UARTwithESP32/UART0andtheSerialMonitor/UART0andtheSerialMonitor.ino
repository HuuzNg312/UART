// A basic example that shows a two-way communication between the ESP32 and the Serial Monitor

String receivedMessage = "";
void setup() {
  Serial.begin(115200); //Start the Serial Monitor at a bound rate of 115200

   Serial.println("ESP32 is ready. Please enter a message:");  // Print an initial message to the Serial Monitor
}

void loop() {
  while (Serial.available()) {
    char incomingChar = Serial.read(); // Read each character from the buffer

    if(incomingChar == '\n') { // Check if the user pressed Enter (new line character)
        //Print the message
        Serial.print("You sent: ");
        Serial.println(receivedMessage);

        //clear the message buffer for the next input
        receivedMessage = "";      
    } else {
        //Append the character to the message string
        receivedMessage += incomingChar;
      }
  }
}
