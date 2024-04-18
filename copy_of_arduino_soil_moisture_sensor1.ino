#include <LiquidCrystal.h>

// Declare variables for pins
const int sensorpin = A0;
const int sensorpower = 8;
const int GREEN = 2;
const int RED = 4;
int sensorReading;
float celsius;
int temp = A1;
int ldr = A3;	
int light;

// Initialize the LCD library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Delay time between sensor readings (milliseconds)
const int delayTime = 2500; // Change delay time to 5000 milliseconds (5 seconds)

// "wet" and "dry" thresholds - these require calibration
int wetThreshold;
int dryThreshold;
int temperatureThreshold = 20;

// Timer variables for incrementing sensor value
int decrementAmount = 100;

void setup() {
  // Set pins as outputs
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(sensorpower, OUTPUT);
  pinMode(ldr, INPUT);
  
if (temperatureThreshold > 15) {
  wetThreshold = 1000;
  dryThreshold = 500;
  sensorReading = 1500;
} else {
  wetThreshold = 2000;
  dryThreshold = 1500;
  sensorReading = 2500;
}

  // Initialize the LCD
  lcd.begin(16, 2);

  // Clear the LCD
  lcd.clear();

  // Display an initial message
  lcd.print("Smart Irrigation");
  lcd.setCursor(0, 1);
  lcd.print("Temperature: 10*");

  delay(1500);

  lcd.clear();

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  //Temperature sensor.
  //celsius = analogRead(temp)*0.004882814;
  //celsius = (celsius - 0.5) * 100.0;  	
  //lcd.setCursor(0,1);
  //lcd.print("Temp: ");
  //lcd.print(celsius);
  //lcd.print(" C");
  //delay(5000);
  
  //Light sensor which can give sunlight intensity
  //light = analogRead(ldr);
  //Serial.println(light);
  
  while (sensorReading > 100) {
    sensorReading -= decrementAmount;

    // Print sensor reading
    Serial.println(sensorReading);

    if (sensorReading > dryThreshold) {
        digitalWrite(RED, LOW);
        digitalWrite(GREEN, HIGH);
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Moisture: High");
        Serial.println("PUMP OFF"); 
        Serial.println(".............................\n"); 
    }  
    else if (sensorReading < dryThreshold) {
        digitalWrite(GREEN, LOW);
        digitalWrite(RED, HIGH);
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("Moisture: Low");
        Serial.println("PUMP ON");
        Serial.println(".............................\n"); 
    }
    // Wait before taking the next reading
    delay(delayTime); // Delay for 2500 milliseconds (5 seconds)
  }
}
