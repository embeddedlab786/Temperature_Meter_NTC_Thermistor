#include <LiquidCrystal.h> //Libraries
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Arduino pins to lcd

#define ThermistorPin A0 // for Arduino microcontroller
long ADC_Value;
float R1 = 10000; // value of R1 on board
float logR2, R2, T;

//steinhart-hart coeficients for thermistor
float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741;  
float temp_c, temp_f;

#define G_led 8 
#define R_led 9 
#define buzzer 13
  
void setup(){
pinMode(ThermistorPin, INPUT);

pinMode(R_led,OUTPUT); // declare Red LED as output
pinMode(G_led,OUTPUT); // declare Green LED as output
pinMode(buzzer,OUTPUT); // declare Buzzer as output 

lcd.begin(16, 2); // Configura lcd numero columnas y filas
lcd.clear();
lcd.setCursor (0,0);
lcd.print("   Welcome To   ");
lcd.setCursor (0,1);
lcd.print("Temperature NTC"); 
delay(2000);
lcd.clear();
}
 
void loop(){
ADC_Value=0;
for(int i=0; i< 50; i++) {
ADC_Value = ADC_Value+analogRead(ThermistorPin);
delay(1);
}

ADC_Value=ADC_Value/50;
R2 = R1 * (1023.0 / (float)ADC_Value - 1.0); //calculate resistance on thermistor
logR2 = log(R2);
temp_c = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); // temperature in Kelvin
temp_c = temp_c - 273.15; //convert Kelvin to Celcius
temp_f = (temp_c * 9.0)/ 5.0 + 32.0; //convert Celcius to Fahrenheit

lcd.setCursor(0,0);
lcd.print("  Temperature   ");
   
lcd.setCursor(0,1);
lcd.print(temp_c, 1);
lcd.write(0xdf); // to display °
lcd.print("C  ");

lcd.setCursor(9,1);
lcd.print(temp_f,1); 
lcd.write(0xdf);
lcd.print("F  ");

if(temp_f>100){ 
digitalWrite(buzzer, HIGH);
digitalWrite(G_led, LOW); // Turn LED off.   
digitalWrite(R_led, HIGH);  // Turn LED on.
delay(300);
}else{  
digitalWrite(G_led, HIGH); // Turn LED on.  
digitalWrite(R_led, LOW);  // Turn LED off.
}
  
digitalWrite(buzzer, LOW);
delay(500); 
}

/* The easy circuit:
 *                  Analog pin 0
 *                        |
 *    5V |-----/\/\/\-----+-----/\/\/\-----| GND
 *               ^                ^ 
 *        10K thermistor     10K resistor
 */
