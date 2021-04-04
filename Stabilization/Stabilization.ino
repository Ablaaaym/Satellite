#define PIN_ENA 9 // Вывод управления скоростью вращения мотора №1
#define PIN_IN1 10 // Вывод управления направлением вращения мотора №1
#define PIN_IN2 11 // Вывод управления направлением вращения мотора №1
#define PIN_Left 7 //вход с расбери для  скорости
#define PIN_Right 12 //вход с расбери для скорости
#define PIN_speed 4 // вход с расбери для скорости
#define PIN_return 13 //вход с расбери о прекращении работы алгоритма стабилизации
int detection = 0; // был ли обнаружен объект
int obgon = 0; // был обгон или отставание

   uint8_t power = 105; // Значение ШИМ (или скорости вращения)

   void setup() {

     // Установка всех управляющих пинов в режим выхода и входа
     pinMode(PIN_ENA, OUTPUT);
     pinMode(PIN_IN1, OUTPUT);
     pinMode(PIN_IN2, OUTPUT);
     pinMode(PIN_Left, INPUT);
     pinMode(PIN_Right, INPUT);
     pinMode(PIN_speed, INPUT);
     pinMode(PIN_return,INPUT);
   // Команда остановки двум моторам

     digitalWrite(PIN_IN1, LOW);
     digitalWrite(PIN_IN2, LOW);
   }


 void loop() {
   
int       valLeft = digitalRead(PIN_Left);
int       valRight = digitalRead(PIN_Right);
int       valspeed = digitalRead(PIN_speed);
int runprog = digitalRead(PIN_return);

if(runprog == 1)
{

if((detection == 0)and ((valLeft == 1)or(valRight == 1) or(valspeed ==1))) //определение
{
       detection = 1;
}

if((valLeft == 1)or(valRight == 1) or(valspeed ==1))//видно
  {
    if ( (valLeft == 0) and (valRight == 0) and (valspeed == 1))//догоняющая 1 скорость 
    {
     analogWrite (PIN_ENA, 150);
     digitalWrite(PIN_IN1, HIGH);
     digitalWrite(PIN_IN2, LOW);
     obgon = 1;
    }
  
  
    if ( (valLeft == 0) and (valRight == 1) and (valspeed == 0))//догоняющая 2 скорость 
    {
     analogWrite (PIN_ENA, 120);
     digitalWrite(PIN_IN1, HIGH);
     digitalWrite(PIN_IN2, LOW);
     obgon = 1;
    }

  
    if ( (valLeft == 0) and (valRight == 1) and (valspeed == 1))// догоняющая 3 скорость 
    {
     analogWrite (PIN_ENA, 100);
     digitalWrite(PIN_IN1, HIGH);
     digitalWrite(PIN_IN2, LOW);
     obgon = 1;
    }
  
  if ( (valLeft == 1) and (valRight == 0) and (valspeed == 1))// нормальное состояние
     {
     analogWrite (PIN_ENA, 0); 
     digitalWrite(PIN_IN1, LOW);
     digitalWrite(PIN_IN2, LOW);
     obgon = 0;
     }
  
  if ( (valLeft == 1) and (valRight == 0) and (valspeed == 0))// обратная 3 скорость
     {
     analogWrite (PIN_ENA, 100); 
     digitalWrite(PIN_IN1, LOW);
     digitalWrite(PIN_IN2, HIGH);
     obgon = 0;
     }
  if ( (valLeft == 1) and (valRight == 1) and (valspeed == 0))//обратная 2 скорость
     {
     analogWrite (PIN_ENA, 120); 
     digitalWrite(PIN_IN1, LOW);
     digitalWrite(PIN_IN2, HIGH);
     obgon = 0;
     }
  if ( (valLeft == 1) and (valRight == 1) and (valspeed == 1))//обратная 1 скорость
     {
     analogWrite (PIN_ENA, 150); 
     digitalWrite(PIN_IN1, LOW);
     digitalWrite(PIN_IN2, HIGH);
     obgon = 0;
     }
  }

if(detection==1)// если объект был обнаружен
 {

  if ((valLeft == 0) and (valRight == 0) and (valspeed == 0))// объект не находится в зоне видимости
  {
 
    if( (obgon == 0)) // отстал
    {
    analogWrite(PIN_ENA, 200); // догоняющее движение со скоростью 200
       digitalWrite(PIN_IN1, HIGH); 
       digitalWrite(PIN_IN2, LOW);
    }

    if((obgon == 1)) // обогнал
    {
    analogWrite(PIN_ENA, 200); // обратное движение со скоростью 200
       digitalWrite(PIN_IN1, LOW);
       digitalWrite(PIN_IN2, HIGH);
    }
  


  
 }
 }

}

if(runprog == 0)  // отключение для будущего поиска новых объектов
{
   digitalWrite(PIN_IN1, LOW);
     digitalWrite(PIN_IN2, LOW);
     detection = 0;
}

}
