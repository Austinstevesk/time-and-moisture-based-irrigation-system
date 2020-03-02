#include <LiquidCrystal.h> //LCD library
#include <Wire.h>
#include <DS3231.h>

DS3231  rtc(SDA, SCL);
//Relay pin
int Relay = 8;
int percentval;
int state;

//Setting up the time when we need the the pump on and off
Time t;

int OnHour = 14;
int OnMin1 = 16;
int OnMin2 = 18;

int i;
//for(i=0;i<20;i++){
  //OnMin += i
//}

LiquidCrystal lcd(2,3,4,5,6,7);//RS, E, D4, D5, D6, D7


void setup() {
  Serial.begin(9600);
  pinMode(Relay,OUTPUT);
  // Uncomment the next line if you are using an Arduino Leonardo
  //while (!Serial) {}
  
  // Initialize the rtc object
  rtc.begin();
  lcd.begin(16,2);
  lcd.setCursor(6,0);
  // The following lines can be uncommented to set the date and time
  //rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(18, 06, 00);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(26, 2, 2020);   // Set the date to January 1st, 2014
  //lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the 
                    //dimensions (width and height) of the display } 
                   
  


}

void loop() {
  // put your main code here, to run repeatedly:
  // Send Day-of-Week
  /*
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  
  // Send date
  lcd.setCursor(1,0);
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");
  lcd.print(rtc.getDateStr());
  lcd.print("--");
  */
  
  // Send time
  t = rtc.getTime();
  String T = rtc.getTimeStr();
  Serial.print(t.hour);
  Serial.print(" hour(s), ");
  Serial.print(t.min);
  Serial.print(" minute(s)");
  Serial.println(" ");
  
  
  // Wait one second before repeating
  int sensorval = analogRead(A0);

    Serial.println("\n\nAnalogValue: ");
    Serial.println(sensorval);
    percentval = map(sensorval, 1023, 200, 0, 100);
    Serial.println("\nPercentval: ");
    Serial.println(percentval);
  
  
  if(t.hour == OnHour && t.min == OnMin1 || t.min == OnMin2 && percentval<30){
        digitalWrite(Relay, LOW);
        Serial.print("Pump on");
      }
  else{
      digitalWrite(Relay, HIGH);
      Serial.print("Pump off");
        
       
      }
    
  delay (1000);
   lcd.setCursor(3,0);
   lcd.print(T);
   lcd.setCursor(7,1);
   lcd.print(percentval);
   
}
