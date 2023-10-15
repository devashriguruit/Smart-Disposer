#include <Servo.h>
#include <SoftwareSerial.h>

Servo myservo;
int TX = 11;
int RX = 10;
SoftwareSerial bluetooth(TX, RX);

int servoPosition = 0;
int targetPosition = 0; // Desired position for the servo
const int increment = 1; // Increment for smoother movement

void setup() {
  myservo.attach(9);
  Serial.begin(9600);
  bluetooth.begin(9600);
  myservo.write(servoPosition);
}

void loop() {
  if (bluetooth.available() > 1) {
    String command = bluetooth.readString();

    if (command == "open" || command == "Open") {
      Serial.println("Opening...");
      targetPosition = 180; // Set the desired position
    }  
    else if (command == "close" || command == "Close") {
      Serial.println("Closing...");
      targetPosition = 0; // Set the desired position
    }
  }

  // Gradually move the servo toward the target position
  if (servoPosition < targetPosition) {
    servoPosition += increment;
  } else if (servoPosition > targetPosition) {
    servoPosition -= increment;
  }

  // Update the servo position
  myservo.write(servoPosition);

  // Add a small delay to control the speed of movement
  delay(10);
}
