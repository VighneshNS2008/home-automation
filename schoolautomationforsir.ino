#include <EEPROM.h>

#include <SoftwareSerial.h>

String Grsp;


SoftwareSerial mySerial(A3, A2); //SIM800L Tx & Rx is connected to Arduino #3 & #2

void setup()
{
  if (EEPROM.read(0)==1)
  {
  digitalWrite(13,LOW);
  } if (EEPROM.read(0)==0)
  {
  digitalWrite(13,HIGH);
  }
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);

  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  mySerial.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CNMI=1,2,0,0,0"); // Decides how newly arrived SMS messages should be handled
  updateSerial();
Serial.println(EEPROM.read(0));

}

void loop()
{
  updateSerial();


}

void updateSerial()
{

  delay(500);
  while (Serial.available())
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port

  }
  while (mySerial.available())
  {
    //Serial.write(mySerial.read());
    String sms = mySerial.readString();
    Serial.println(sms);
    sms.toLowerCase();
if (sms.indexOf("off")>-1){
  digitalWrite(13,HIGH);
  EEPROM.update(0,0);
}
if (sms.indexOf("on")>-1){
  digitalWrite(13,LOW);
    EEPROM.update(0,1);

}

if (sms.indexOf("test")>-1){
  digitalWrite(13,LOW);delay(500);
  digitalWrite(13,HIGH);delay(500);
  digitalWrite(13,LOW);delay(500);
  digitalWrite(13,LOW);delay(500);
  digitalWrite(13,HIGH);delay(500);
  digitalWrite(13,LOW);delay(500);
}


  }
}
