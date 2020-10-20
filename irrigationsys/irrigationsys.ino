#include <LiquidCrystal.h> //LCD library
#include <Wire.h>
#include <DS3231.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); //Tx, RX
int _timeout;
String _buffer;


DS3231  rtc(SDA, SCL);
//Relay pin
int Relay = 8;
int percentval=10;
int state;

//Setting up the time when we need the the pump on and off
Time t;

int OnHour = 21;
int OnHour1 = 21;
int OnMin = 30;
int OnMin1 = 30;

bool pumping = false;


LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //RS, E, D4, D5, D6, D7


void setup() {
  Serial.begin(9600);
  _buffer.reserve(50);
  Serial.println("System Started...");
  mySerial.begin(9600);
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, HIGH);
 // Uncomment the next line if you are using an Arduino Leonardo
  //while (!Serial) {}

  // Initialize the rtc object
  rtc.begin();
  lcd.begin(16, 2);
  lcd.setCursor(6, 0);
  delay(5000); //delay for 100 milliseconds to make sure the modules get the signal
  // The following lines can be uncommented to set the date and time
  //rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setTime(18, 13, 00);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(26, 2, 2020);   // Set the date to January 1st, 2014




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


  if ( OnHour == 21 && OnMin == 30  && percentval < 20) {
    pumping = true;
    pumpOnMessage();
    digitalWrite(Relay, LOW);
    Serial.print("Pump on");
  }

   if (t.hour == OnHour1 && t.min == OnMin1  && percentval < 20) {
    pumping = true;
    pumpOnMessage();
    digitalWrite(Relay, LOW);
    Serial.print("Pump on");
  }
  if (pumping == true && percentval > 40) {
    digitalWrite(Relay, HIGH);
    Serial.print("Pump off");
    pumpOffMessage();
    pumping = false;

  }

  delay (1000);
  lcd.setCursor(3, 0);
  lcd.print(T);
  lcd.setCursor(7, 1);
  lcd.print(percentval);
  
  if (mySerial.available() > 0)
    Serial.write(mySerial.read());

}

void pumpOnMessage() {
  Serial.println("Sending Message");
  mySerial.println("AT+CMGF=1"); // Sets the GSM Module in Text Mode
  delay(1000); // Delay pf 1 second
  mySerial.println("AT+CMGS+\"+254743070455\"\r");
  delay(1000);
  mySerial.println("Pump on. Moisture content is "+percentval); //The sms you want to send
  delay(100);
  mySerial.println((char)26); // ASCII code of CTRL+Z
  delay(1000);
}

void pumpOffMessage() {
  Serial.println("Sending Message");
  mySerial.println("AT+CMGF=1"); // Sets the GSM Module in Text Mode
  delay(1000); // Delay pf 1 second
  mySerial.println("AT+CMGS+\"+254743070455\"\r");
  delay(1000);
  mySerial.println("Pump off. Moisture content is "+percentval); //The sms you want to send
  delay(100);
  mySerial.println((char)26); // ASCII code of CTRL+Z
  delay(1000);
}

    String _readSerial() {
      _timeout = 0;
      while  (!mySerial.available() && _timeout < 12000  )
      {
        delay(13);
        _timeout++;
      }
      if (mySerial.available()) {
        return mySerial.readString();
        Serial.print("sms sent");
      }
    }
