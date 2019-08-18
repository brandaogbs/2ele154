#include <Arduino.h>

#define PIN_BUTTON  3
#define PIN_GREEN   4
#define PIN_RED     2

#define PIN_A 5
#define PIN_B 6
#define PIN_C 7
#define PIN_D 8
#define PIN_E 9
#define PIN_F 10
#define PIN_G 11


void setDisplayDigit(int digit)
{
  if(digit!=1 && digit != 4)
  digitalWrite(PIN_A,HIGH);

  if(digit != 5 && digit != 6)
  digitalWrite(PIN_B,HIGH);

  if(digit !=2)
  digitalWrite(PIN_C,HIGH);

  if(digit != 1 && digit !=4 && digit !=7)
  digitalWrite(PIN_D,HIGH);

  if(digit == 2 || digit ==6 || digit == 8 || digit==0)
  digitalWrite(PIN_E,HIGH);

  if(digit != 1 && digit !=2 && digit!=3 && digit !=7)
  digitalWrite(PIN_F,HIGH);

  if (digit!=0 && digit!=1 && digit !=7)
  digitalWrite(PIN_G,HIGH);
}

void turnDisplayOff()
{
  digitalWrite(PIN_A,LOW);
  digitalWrite(PIN_B,LOW);
  digitalWrite(PIN_C,LOW);
  digitalWrite(PIN_D,LOW);
  digitalWrite(PIN_E,LOW);
  digitalWrite(PIN_F,LOW);
  digitalWrite(PIN_G,LOW);
}

void setDisplayOn()
{
  int i;
  for(i=0; i<10; i++)
  {
    setDisplayDigit(i);
    delay(1000);
    turnDisplayOff();
  }
}

void setup() 
{  

  Serial.begin(9600);

  pinMode(PIN_BUTTON, INPUT);
 
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_RED, OUTPUT);

  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_D, OUTPUT);
  pinMode(PIN_E, OUTPUT);
  pinMode(PIN_F, OUTPUT);
  pinMode(PIN_G, OUTPUT);

}

void loop2()
{
   // Se o botao for pressionado
  if(digitalRead(PIN_BUTTON) == HIGH)
  {
    // Contagem 
    setDisplayDigit(9);
    delay(1000);
    turnDisplayOff();

    setDisplayDigit(8);
    delay(1000);
    turnDisplayOff();

    setDisplayDigit(7);
    delay(1000);
    turnDisplayOff();

    setDisplayDigit(6);
    delay(1000);
    turnDisplayOff();

    setDisplayDigit(5);
    delay(1000);
    turnDisplayOff();

    setDisplayDigit(4);
    delay(1000);
    turnDisplayOff();

    setDisplayDigit(3);
    delay(1000);
    turnDisplayOff();

    setDisplayDigit(2);
    delay(1000);
    turnDisplayOff();

    setDisplayDigit(1);
    delay(1000);
    turnDisplayOff();

    setDisplayDigit(0);
    delay(1000);
    turnDisplayOff();



    // Liga vermelho
    digitalWrite(PIN_RED, HIGH);
    
    // Desliga verde
    digitalWrite(PIN_GREEN, LOW);
    delay(1000);

  }
  
  // Se nao for pressionado
  else
  {
    // Apaga Display
    turnDisplayOff();

    // Desliga vermelho
    digitalWrite(PIN_RED, LOW);
    
    // Liga verde
    digitalWrite(PIN_GREEN, HIGH);
    delay(100);
    digitalWrite(PIN_GREEN, LOW);
    delay(100);
  }  

}

void loop() 
{
 
  if(Serial.available())
  {
    char c = Serial.read();
    
    if(c == 'l')
    {
      digitalWrite(PIN_GREEN, HIGH);
    }
    else
    {
      digitalWrite(PIN_GREEN, LOW);
    }
  
  }

}
