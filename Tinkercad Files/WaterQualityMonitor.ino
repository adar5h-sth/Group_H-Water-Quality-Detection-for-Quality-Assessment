#include <LiquidCrystal.h>

// Initializing the LCD with the appropriate pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Defining the buzzer pin
const int buzzerPin = 8; // Using pin 8 for the buzzer

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(buzzerPin, OUTPUT); // Set the buzzer pin as an output
  pinMode(A0, INPUT); // Set A0 as input for the light sensor
}

void loop() {
  // Simulated turbidity measurement using light sensor
  int lightLevel = analogRead(A0); // Reading light level from A0
  
  // Mapping the light level to a range of 0-100, where low light = high turbidity
  int turbidityLevel = map(lightLevel, 471, 0, 0, 100); 
  
  // Printing "turbidity" value to Serial Monitor
  Serial.print("Simulated Turbidity: "); 
  Serial.println(turbidityLevel);

  // Determining water status based on "turbidity" (light level)
  String waterStatus;
  if (turbidityLevel < 10) {
    waterStatus = "Clear";
    noTone(buzzerPin); // Turn off the buzzer
  } else if (turbidityLevel < 30) {
    waterStatus = "Slightly Cloudy";
    noTone(buzzerPin); // Turn off the buzzer
  } else if (turbidityLevel < 50) {
    waterStatus = "Cloudy";
    tone(buzzerPin, 220, 100); // Buzzer on for "Cloudy"
  } else {
    waterStatus = "Harmful";
    tone(buzzerPin, 250, 500); // Buzzer on for "Harmful"
  }

  // Displaying simulated turbidity and water status on LCD
  lcd.clear(); // Clear the display
  lcd.setCursor(0, 0);
  lcd.print("Turbidity: ");
  lcd.print(turbidityLevel);
  
  lcd.setCursor(0, 1);
  lcd.print(waterStatus); 

  delay(2000); // Update every 2 seconds
}
