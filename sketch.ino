#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

#define SCREEN_WIDTH 2128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Servo myServo;

const int button1Pin = 2;
const int button2Pin = 3;
const int redLedPin = 6;
const int greenLedPin = 7;
const int buzzerPin = 8;
const int servoPin = 9;

void setup() {
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  myServo.attach(servoPin);
  myServo.write(0);

  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    for(;;); // Don't proceed, loop forever if allocation fails
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println(F("System Initialized"));
  display.display();
  delay(2000);
}

void loop() {
  int btn1State = digitalRead(button1Pin);
  int btn2State = digitalRead(button2Pin);

  display.clearDisplay();
  display.setCursor(0,0);
  display.println(F("Project Dashboard"));
  display.drawFastHLine(0, 10, 128, SSD1306_WHITE);

  if (btn1State == LOW) { // Button 1 pressed
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
    tone(buzzerPin, 1000, 100);
    myServo.write(90); // Move servo to 90 degrees
    
    display.setCursor(0, 20);
    display.println(F("Status: MODE 1 (Active)"));
    display.setCursor(0, 35);
    display.println(F("Servo @ 90 Deg"));
  } 
  else if (btn2State == LOW) { // Button 2 pressed
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    tone(buzzerPin, 1500, 100);
    myServo.write(180); // Move servo to 180 degrees
    
    display.setCursor(0, 20);
    display.println(F("Status: MODE 2 (Alert)"));
    display.setCursor(0, 35);
    display.println(F("Servo @ 180 Deg"));
  } 
  else {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, LOW);
    myServo.write(0); // Reset servo
    
    display.setCursor(0, 20);
    display.println(F("Status: IDLE"));
    display.setCursor(0, 35);
    display.println(F("Waiting for input..."));
  }

  display.display();
  delay(50);
}

