#include <LiquidCrystal.h>
#include <TinyGPS.h>
TinyGPS gps;
float flat=0, flon=0;
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 =12, d7 =13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int vhs=0;
int vs=7;
int k;
int buz=A5;
int m1=A0;
int m2=A1;
int m3=A2;
int m4=A3;
void read_gps()
{
    bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial.available())
    {
      char c = Serial.read();
      if (gps.encode(c)) 
        newData = true;
    }
  }

  if (newData)
  {

    unsigned long age;
    gps.f_get_position(&flat,&flon,&age);

  }
}
int aval;
void setup()
{ 
  Serial.begin(9600);
  pinMode(vs,INPUT);
  pinMode(buz,OUTPUT);
  pinMode(m1,OUTPUT);
  pinMode(m2,OUTPUT);
  pinMode(m3,OUTPUT);
  pinMode(m4,OUTPUT);
  lcd.begin(16, 2);  
  lcd.print("  WELCOME");
  lcd.setCursor(0,1);
  lcd.print("INITIALIZING");
  lcd.clear();
  lcd.print("INITIALIZED");
   Serial.println("AT");
  delay(1500);
  Serial.println("AT+CMGF=1");
  delay(500);  
}
void loop()
{   
 int vval=digitalRead(vs);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print(" V:"+String(vval));
 delay(300);
 if(vval==0)
  {   
     digitalWrite(m1,0);
     digitalWrite(m2,0);
     digitalWrite(m3,0);
     digitalWrite(m4,0);
      lcd.clear();
      lcd.print("ACCIDENT OCCURED");
      lcd.setCursor(0,1);
      lcd.print("SENDING INFO");
      digitalWrite(buz,1);
      send_sms(1);   
    Serial.println("Caling..      ");
    Serial.println("AT");
    delay(1000);
    Serial.println("AT+CMGF=1");
    delay(2000);
    Serial.println("ATD9052252287                                                                  ;");
    delay(20000); 
      while(1);
}
else
{
   digitalWrite(m1,1);
   digitalWrite(m2,0);
    digitalWrite(m3,1);
     digitalWrite(m4,0);
}
}
  void send_sms(int k)
  {
   read_gps();  
Serial.println("Sending SMS...");
Serial.println("AT");    
delay(1000);  
Serial.println("ATE0");    
delay(1000);  
Serial.println("AT+CMGF=1");    
delay(1000);  
Serial.print("AT+CMGS=\"7013071313\"\r\n");// Replace x with mobile number
delay(1000);
if(k==1)
Serial.print("Vehicle stopped due to ACCIDENT, at");
Serial.println("https://www.google.com/maps/search/?api=1&query=" + String("16.4971")+ "," + String("80.4992"));
delay(500);
Serial.print(char(26));
delay(2000); 
  }