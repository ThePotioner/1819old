#include <Stepper.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <swRTC.h>

swRTC rtc;  //클래스 개체 선언

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int stepsPerRevolution = 64; 
int flag = 0;
int btnA = 7;
int buz = 6;
Stepper myStepper(stepsPerRevolution, 11,9,10,8);
int cds = A0;
const int TriggerPin = 12, EchoPin = 13;

long Dist = 0;

void setup()
{
    rtc.stopRTC();            //정지
    rtc.setTime(9, 00, 00);  //시, 분, 초
    rtc.setDate(23, 11, 2019); //일, 월, 년
    rtc.startRTC();           //시작
  
    // LCD Init
    lcd.init();
    lcd.backlight();
    Serial.begin(9600);

  // Motor Init
    myStepper.setSpeed(300);

    pinMode(btnA, INPUT_PULLUP);
    pinMode(buz,OUTPUT);
}

long Distance(long time)
{
    // Calculates the Distance in mm
    // ((time)*(Speed of sound))/ toward and backward of object) * 10

    long DistanceCalc; // Calculation variable
    DistanceCalc = ((time / 2.9) / 2); // Actual calculation in mm
    //DistanceCalc = time / 74 / 2; // Actual calculation in inches
    return DistanceCalc; // return calculated value
}

void banggule(int where)
{
    if (where == 1)
    {
      // Motor Rotate -> Right
      for(int i = 0; i < 8; i++)
      {
        myStepper.step(-stepsPerRevolution);
      }
    }
    else if (where == -1)
    {
      // Motor Rotate -> Left
      for(int i = 0; i < 8; i++)
      {
        myStepper.step(stepsPerRevolution);
      }
    }
}

long digitS()
{
    digitalWrite(TriggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(TriggerPin, HIGH); // Trigger pin to HIGH
    delayMicroseconds(10); // 10us high
    digitalWrite(TriggerPin, LOW); // Trigger pin to HIGH

    Dist = pulseIn(EchoPin, HIGH); // Waits for the echo pin to get high
    // returns the Duration in microseconds

    long Distance_mm = Distance(Dist); // Use function to calculate the distance
    return Distance_mm;
}

void loop()
{
    // Analog Read
    int cdsVal = analogRead(cds);

    // LCD Cursor Set + Light Level Print
    lcd.setCursor(0, 0);
    lcd.print(cdsVal);
    if (flag == 1 && cdsVal > 500) {
        lcd.print(" - Li Lv Low");
        banggule(-1);
        flag = 0;
    }
    else if(flag == 0 && cdsVal > 500)
    {
      lcd.print(" - Li Lv Low");
      banggule(1);
      flag = 1;
    }
    else lcd.print(" - Li Lv High");
    
    // Second Line
    lcd.setCursor(0, 1);
    lcd.print(rtc.getHours());
    lcd.print(rtc.getMinutes());
    lcd.print(rtc.getSeconds());
    lcd.print(rtc.getYear());
    lcd.print(rtc.getMonth());
    lcd.print(rtc.getDay());

    if(digitalRead(btnA) == LOW)
    {
      rtc.setTime(21, 00, 00);
    }

    if(digitS() > 0 && digitS() < 200 && rtc.getHours() > 20)
    {
      tone(buz,956);
    }

    // Delay 0.6sec
    delay(600);
    
    lcd.clear(); // Clear
}