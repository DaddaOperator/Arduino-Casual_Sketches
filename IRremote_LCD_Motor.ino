/*
 * HW: IR remote control, red led, LCD monitor with his trigger, Stepper motor with driver.
 * 
 * Logic: 2 possible states, State1 is engaged with button 1 on the controller
 * is pressed; State2 is engaged with button 2 on the controller button. 
 * When state1 is active, motor starts to rotate clockwise. If button2 on the controller is
 * pressed entering the state2, motor stops and system is blocked.
 * It is possible to change the rotation speed of the motor at any time using "+" and "-" buttons on the controller.
 * Current status of the system and actual speed is reported in the LCD display monitor.
 * 
 * Davide Reverberi 
 */

#include <LiquidCrystal.h>
#include <IRremote.h>
#include <Stepper.h>

int ledPin = 7;
int servoPin = 8;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
int v = 50;
int state = 0;

IRrecv IR(6);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Stepper motor(200, 44, 48, 46, 50);


void setup() {
  // put your setup code here, to run once:
  IR.enableIRIn();
  motor.setSpeed(v);   //Initial Stepper speed
  pinMode(ledPin, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("DaRev Machine: ");
  Serial.begin(9600);
}

/* Each button has his hexademical code to distinguish */

void loop() {
  lcd.setCursor(15,1);
  lcd.print(" ");
  lcd.setCursor(6,1);
  lcd.print("Speed: ");
  lcd.setCursor(13,1);
  lcd.print(v);
  lcd.setCursor(0,1);

  if(IR.decode()){
    Serial.println(IR.decodedIRData.decodedRawData, HEX);
    if(IR.decodedIRData.decodedRawData == 0xF30CFF00){ //Button 1 is pressed
      digitalWrite(ledPin, HIGH);
      lcd.print("High"); //State1
      state = 1;
    }
    if(IR.decodedIRData.decodedRawData == 0xE718FF00){ //Button 2 is pressed
      digitalWrite(ledPin, LOW);
      lcd.print("Low "); //State2
      state = 0;
    }
    if(IR.decodedIRData.decodedRawData == 0xEA15FF00){    //"+" button is pressed
      if(v == 100){
          Serial.print("Top Speed Reached");
      }else{
        v += 10;
        motor.setSpeed(v);
      }
    }
    if(IR.decodedIRData.decodedRawData == 0xF807FF00){    //"-" button is pressed
      if(v == 10){
          Serial.print("Lower Speed Reached");
      }else{
        v -= 10;
        motor.setSpeed(v);
      }
    }
    IR.resume();
  }
  Serial.println(state);
  Serial.println(v);
  if(state == 1){
    motor.step(1);
  }
  delay(20);
  

} 
