const int ledforward = 12; //przednie swiatla
const int ledbackward = 13; //swiatla tylne/stop
//piny obslugujace silnik A
const int ENA = 9;
const int IN1 = 5;
const int IN2 = 6;
//piny obslugujace silnik B
const int ENB = 11;
const int IN3 = 7;
const int IN4 = 8;
int driving = 0; //1 przod, -1 tyl
int steering = 0; //-1 lewo, 1 prawo
int motorL = 0; //predkosc silnika A
int motorR = 0; //predkosc silnika B
int const sensorPin = A5;
int sensorValue = 0;
char state; //zmienna pobierajaca z portu szeregowego
void setup() {
  Serial.begin(9600);
  pinMode(ledbackward,OUTPUT);
  pinMode(ledforward,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  
  pinMode(ENB,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  delay(500);
  //zatrzymanie silnikow
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() 
{
  sensorValue = analogRead(sensorPin);
    //-------------------------jazda do tylu w razie wykrycia zderzenia---------------------
    if ((sensorValue > 250)&&(driving == 1))
    {
      driving = -1;
      steering = 0;
      motorL = 50;
      motorR = 50;
    }
  if (Serial.available()) 
  {
    state = Serial.read();
    //-------------------------obsluga jazdy do przodu-----------------------------------
    if((state == 'w')&&(driving == 0))
    {
     driving = 1;
     motorL = 50;
     motorR = 50;
    }
    else if((state == 'w')&&(driving == 1)&&(motorL < 250)&&(motorR < 250))
    {
     motorL += 50;
     motorR += 50;
    }
     else if((state == 'w')&&(driving == -1))
    {
     motorL -= 50;
     motorR -= 50;
      if ((motorL == 0)&&(motorR == 0))
      {
        driving = 0;
      }
    }
  //-------------------------obsluga jazdy do tylu-----------------------------------
  if((state == 's')&&(driving == 0))
    {
     driving = -1;
     motorL = 50;
     motorR = 50;
    }
    else if((state == 's')&&(driving == -1)&&(motorL < 250)&&(motorR < 250))
    {
     motorL += 50;
     motorR += 50;
    }
     else if((state == 's')&&(driving == 1))
    {
     motorL -= 50;
     motorR -= 50;
      if ((motorL == 0)&&(motorR == 0))
      {
        driving = 0;
      }
    }
    //-------------------------obsluga skrecania-----------------------------------
    else if((state == 'a')&&(steering > -1))
    {
      steering = steering - 1;
    }
    else if((state == 'd')&&(steering < 1))
    {
      steering = steering + 1;
    }
    //-------------------------obsluga przycisku zatrzymania-----------------------------------
    else if(state == '0')
    {
      driving = 0;
      steering = 0;
      motorL = 0;
      motorR = 0;
    }
    //-------------------------obsluga przycisku turbo-----------------------------------
    else if(state == '1')
    {
      driving = 1;
      steering = 0;
      motorL = 250;
      motorR = 250;
    }
  }
 Serial.print("Wartosc sensora: ");
 Serial.println(sensorValue);
 //pojazd stoi
 if ((driving == 0)&&(steering == 0))
  {
    //swiatla
     digitalWrite(ledforward, HIGH);
    digitalWrite(ledbackward, HIGH);
    //silniki
    analogWrite(ENA, 0);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);

    analogWrite(ENB, 0);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  //pojazd skreca w miejscu w LEWO
  else if ((driving == 0)&&(steering == -1))
  {
    //swiatla
    digitalWrite(ledforward, HIGH);
    digitalWrite(ledbackward, LOW);
    //silniki
    analogWrite(ENA, 75);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    analogWrite(ENB, 75);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
    //pojazd skreca w miejscu w PRAWO
  else if ((driving == 0)&&(steering == 1))
  {
    //swiatla
     digitalWrite(ledforward, HIGH);
    digitalWrite(ledbackward, LOW);
    //silniki
    analogWrite(ENA, 75);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    analogWrite(ENB, 75);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  //pojazd jedzie do PRZODU
  else if ((driving == 1)&&(steering == 0))
  {
    //swiatla
     digitalWrite(ledforward, HIGH);
    digitalWrite(ledbackward, LOW);
    //silniki
    analogWrite(ENA, motorL);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    analogWrite(ENB, motorR);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
   //pojazd jedzie do TYLU
  else if ((driving == -1)&&(steering == 0))
  {
    //swiatla
     digitalWrite(ledforward, LOW);
    digitalWrite(ledbackward, HIGH);
    //silniki
    analogWrite(ENA, motorL);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    analogWrite(ENB, motorR);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
    //pojazd skreca w LEWO w trakcie JAZDY do PRZODU
  else if ((driving == 1)&&(steering == -1))
  {
    //swiatla
     digitalWrite(ledforward, HIGH);
    digitalWrite(ledbackward, LOW);
    //silniki
    analogWrite(ENA, 255);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);

    analogWrite(ENB, 100);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
      //pojazd skreca w PRAWO w trakcie JAZDY do PRZODU
  else if ((driving == 1)&&(steering == 1))
  {
    //swiatla
     digitalWrite(ledforward, HIGH);
    digitalWrite(ledbackward, LOW);
    //silniki
    analogWrite(ENA, 100);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    analogWrite(ENB, 255);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
  }
    //pojazd skreca w LEWO w trakcie JAZDY do TYLU
  else if ((driving == -1)&&(steering == -1))
  {
    //swiatla
     digitalWrite(ledforward, LOW);
    digitalWrite(ledbackward, HIGH);
    //silniki
    analogWrite(ENA, 255);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);

    analogWrite(ENB, 100);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
      //pojazd skreca w PRAWO w trakcie JAZDY do TYLU
  else if ((driving == -1)&&(steering == 1))
  {
    //swiatla
     digitalWrite(ledforward, LOW);
    digitalWrite(ledbackward, HIGH);
    //silniki
    analogWrite(ENA, 100);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    analogWrite(ENB, 255);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
  }

}
