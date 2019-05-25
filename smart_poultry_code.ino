#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define SSD1306_LCDHEIGHT 64
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
#include "DHT.h"
#include <Servo.h>
#define  DHTPIN D0
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);
int temp_led=D7;
#define echopin D3
#define trigpin D4
Servo myservo;

void setup() {
Serial.begin(9600);
dht.begin();
pinMode(temp_led,OUTPUT);
pinMode(D3,INPUT);
pinMode(D4,OUTPUT);
myservo.attach(D2);
display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
display.clearDisplay();
//display a line of text
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(10,10);
display.print("poultry farm");
Serial.println("poultry farm");
// update display with all of the above graphics
display.display();
}

void loop() {

//gas sensor start
int analogSensor = analogRead(A0);
Serial.print("Pin A0: ");
Serial.println(analogSensor);
delay(500);
  if (analogSensor >45)
{
 display.clearDisplay();
// display a line of text
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(10,10);
display.print("Please switch on the Exhaust fans");
Serial.println("Please switch on the Exhaust fans");
}
else
{

}
delay(100);
//gas sensor end
//dht11 start
float t = dht.readTemperature();
Serial.println(t);
delay(500);
if(t>35)
{
 display.clearDisplay();
// display a line of text
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(10,10);
display.print("Temperature is HIGH");
Serial.println("Temperature is HIGH");
digitalWrite(temp_led,HIGH); //Red
delay(200);
}
else if(t<25)
{
 display.clearDisplay();
// display a line of text
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(10,10);
display.print("Temperature is LOW");
Serial.println("Temperature is LOW");
}
else
{
digitalWrite(temp_led,LOW);
}
//dht11 end
//ultrasoinc start
digitalWrite(D4,HIGH);
delay(1000);
digitalWrite(D4,LOW);
int duration = pulseIn(echopin,HIGH);
int distance = (duration/2)*0.0343;
Serial.println(distance);
delay(500);
if(distance<5)
{
display.clearDisplay();
// display a line of text
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(10,10);
display.print("Please fill the water tubs for Hens");
Serial.println("Please fill the water tubs for Hens");
delay(500);
}
else if(distance>10)
{
display.clearDisplay();
// display a line of text
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(10,10);
display.print("Water overflow");
Serial.println("Water overflow");
delay(500);
}
else
{
}
//ultrasoinc end
//servo start
myservo.write(90);
delay(2000);
myservo.write(0);                           
//servo end
delay(100);

}
