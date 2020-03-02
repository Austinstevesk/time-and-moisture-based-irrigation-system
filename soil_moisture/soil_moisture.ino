int percentval;
int Relay = 6;
void setup() {
  // put your setup code here, to run once:

   pinMode(Relay,OUTPUT);
   Serial.begin(9600);
   Serial.println("Reading From the Sensor ...");
  
 

}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorval = analogRead(A0);
  percentval = map(sensorval, 1023, 0, 0, 100);
  Serial.println("\nPercentval: ");
  Serial.println(percentval);
  /*if(percentval<30){
  digitalWrite(Relay,HIGH);
  Serial.println("Pump on");;;
     }
  else{
    digitalWrite(Relay,LOW);
    Serial.println("pump off");
     }*/
  delay(1000);
}
