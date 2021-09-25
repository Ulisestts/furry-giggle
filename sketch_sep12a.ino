#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <EEPROM.h>
const int alarmsil=2;
const int sysrst=3;
const int ack=4;
//inidcators
const int systrbl=5;
const int silenceled=6;
const int alarmled=7;
const int zone1=8; // zone 1 
const int zone2=9; // zone 2
const int piezo=10; 
const int nac1=11;// nac 1
const int nac2=12; //nac 2
byte devicetype1="PULL STATION";
unsigned int resetcounter=0;
int  silenced=0;
int  silencedmsg=0;
int  generalalarm1 = 0;// realarm
int  generalalarm2 = 0;// realarm
int  generalalarm = 0;
int  notacked = 0;
long zone1verificationtime;
int  scrolltime2 = 8000;
int  scrolltime1 = 4000;
int  scrolltime3 = 12000;
unsigned long timenow = 0;
unsigned long previoustime2=0;
unsigned long previoustime1=0;
unsigned long previoustime3=0;
int  zone1value = LOW;
int  oldzone1value = LOW;
long zone2verificationtime;
int  zone2value = LOW;
int  oldzone2value = LOW;
byte customChar[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};




void setup() {
 resetcounter=EEPROM.read(0);
 lcd.begin();
 lcd.createChar(0, customChar);
 lcd.backlight();
 lcd.setCursor(0,0);
 lcd.print("INITALIZING");
 lcd.setCursor(0,1);
 lcd.print("#9200 9/12/21");
 pinMode(alarmsil,INPUT_PULLUP);
 pinMode(sysrst,INPUT_PULLUP);
 pinMode(ack,INPUT_PULLUP);
 pinMode(zone1,INPUT_PULLUP);
 pinMode(zone2,INPUT_PULLUP);
 pinMode(nac1,OUTPUT);
 pinMode(nac2,OUTPUT);
 pinMode(piezo,OUTPUT);
 pinMode(systrbl,OUTPUT);
 pinMode(silenceled,OUTPUT);
 pinMode(alarmled,OUTPUT);
 digitalWrite(alarmled,HIGH);
 digitalWrite(silenceled,HIGH);
 digitalWrite(systrbl,HIGH);
 tone(piezo,4000);
 delay(60);
 noTone(piezo);
 delay(60);
 tone(piezo,4000);
 delay(60);
 noTone(piezo);
 delay(60);
 tone(piezo,4000);
 delay(60);
 noTone(piezo);
 delay(60);
 tone(piezo,4000);
 delay(60);
 noTone(piezo);
 delay(60);
 tone(piezo,4000);
 delay(60);
 noTone(piezo);
 delay(60);
 tone(piezo,4000);
 delay(60);
 noTone(piezo);
 delay(60);
 tone(piezo,4000);
 delay(60);
 noTone(piezo);
 delay(60);
 tone(piezo,4000);
 delay(60);
 noTone(piezo);
 delay(60);
 tone(piezo,4000);
 delay(60);
 noTone(piezo);
 delay(500);
 digitalWrite(alarmled,LOW);
 digitalWrite(silenceled,LOW);
 digitalWrite(systrbl,LOW);
 delay(2000);
 systemnormal();
}

void loop() {
  scanbuttons();
  checkstateonzone1();
  checkstateonzone2();
  delay(20);

}

void systemnormal(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("");
  lcd.setCursor(0,1);
  lcd.print("SYSTEM NORMAL");
}



void checkstateonzone1() {
  if (generalalarm1==0){
  zone1value = digitalRead(zone1);
  if ( zone1value == LOW )
  {
    if (zone1value != oldzone1value)
    {
      zone1verificationtime = millis() + 1200;

    }
    else {
      if ( millis() >= zone1verificationtime )
      {
        alarm1();
        generalalarm1 = 1;
        generalalarm = 1;
        zone1verificationtime = millis() + 1100;

      }

    }

  }
  oldzone1value = zone1value;
}
}

void checkstateonzone2() {
  if (generalalarm2==0);{
  zone2value = digitalRead(zone2);
  if ( zone2value == LOW )
  {
    if (zone2value != oldzone2value)
    {
      zone2verificationtime = millis() + 1100;

    }
    else {
      if ( millis() >= zone2verificationtime )
      {
        alarm2();
        generalalarm2 = 1;
        generalalarm = 1;
        zone2verificationtime = millis() + 1200;

      }

    }

  }
  oldzone2value = zone2value;
}
}


void alarm1() {
  if (generalalarm1==0){
    if (generalalarm==0){
      lcd.clear();
    }
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("ALARM ZONE 1  ");
    lcd.setCursor(0, 1);
    lcd.print("PULL STATION Z1");;                                     // DEVICE TYPE
    digitalWrite(nac2, HIGH);
    digitalWrite(nac1, HIGH);
    digitalWrite(alarmled, HIGH);
    tone(piezo,4000);
    digitalWrite(silenceled, LOW);
    generalalarm = 1;
    notacked = 1;
    silencedmsg=0;
    silenced=0;
}
}


void alarm2() {
  if (generalalarm2==0){
    if (generalalarm==0){
      lcd.clear();
    }
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("ALARM ZONE 2  ");
    lcd.setCursor(0, 1);
    lcd.print("PULL STATION Z2");;                                     // DEVICE TYPE
    digitalWrite(nac2, HIGH);
    digitalWrite(nac1, HIGH);
    digitalWrite(alarmled, HIGH);
    tone(piezo,4000);
    digitalWrite(silenceled, LOW);
    generalalarm = 1;
    notacked = 1;
    silencedmsg=0;
    silenced=0;
}
}

void scanbuttons(){
  if ( digitalRead(sysrst) == LOW && digitalRead(alarmsil) == HIGH&&digitalRead(ack)==HIGH){
 zone1value = HIGH;
 oldzone1value = HIGH;
 zone2value = HIGH;
 oldzone2value = HIGH;
 generalalarm1 = 0;
 generalalarm2 = 0;
 generalalarm = 0;
 notacked = 0;
 silenced =0;
 silencedmsg=0;
 resetcounter=EEPROM.read(0);
 resetcounter++;
 EEPROM.write(0,resetcounter);
 digitalWrite(alarmled,HIGH);
 digitalWrite(silenceled,HIGH);
 digitalWrite(systrbl,HIGH);
 tone(piezo,1500);
 lcd.clear();
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.setCursor(0,1);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 lcd.write(0);
 delay(500);
 noTone(piezo);
 digitalWrite(nac1,LOW);
 digitalWrite(nac2,LOW);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("EVENTS:");
 lcd.setCursor(7,0);
 lcd.print(resetcounter);
 lcd.setCursor(0,1);
 lcd.print("RESET IN SYSTEM");
 delay(1500);
 digitalWrite(alarmled,LOW);
 digitalWrite(silenceled,LOW);
 digitalWrite(systrbl,LOW);
 delay(2000);
 systemnormal();
  }
  if (digitalRead(ack)==LOW&&digitalRead(alarmsil)==HIGH&&digitalRead(sysrst)==HIGH){
    if (notacked == 1 && digitalRead(ack) == LOW) {
    noTone(piezo);
  }
  }
  if (digitalRead(alarmsil)==LOW){
    if (generalalarm == 1 && digitalRead(alarmsil) == LOW&&digitalRead(sysrst)==HIGH&&digitalRead(ack)==HIGH) {
    notacked=0;
    silencedmsg=1;
    silenced=1;
    lcd.setCursor(0, 0);
    lcd.print("ALARM SILENCED");
    digitalWrite(nac1, LOW);
    noTone(piezo);
    digitalWrite(silenceled, HIGH);
  }
  }
   if (digitalRead(alarmsil)==LOW&&digitalRead(sysrst)==LOW){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("EVENT COUNTER");
    lcd.setCursor(0,1);
    lcd.print("CLEARED!");
    EEPROM.write(0,0);
    delay(3000);
    systemnormal();
  }
  
}
