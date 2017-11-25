/*********************************************
Programa: SensorDistanciaServo
Prof. Luis Fernando
Data: ___/___/____
 Ligação do sensor HC-SR04 1:
 VCC no Arduino 5v       GND no Arduino GND 
 Echo no Arduino pino 7  Trig no Arduino pino 8

 Ligação do sensor HC-SR04 2:
 VCC no Arduino 5v       GND no Arduino GND 
 Echo no Arduino pino 5  Trig no Arduino pino 6 
 
 
 Ligação do servo Motor:
 Fio Marron   no Arduino GND
 Fio Vermelho no Arduino 5v
 Fio Laranja/Amarelo no pino 9
 /*
1=E12440BF
2=E12428D7
3=E1246897
4=E124B847
source=E12448B7
mute=E124609F

/*
Ligação: 5V ---> 5V
         GND ---> GND
         OUT ---> Pino 11
*/

 
#define echoPin1 7 // Echo Pino
#define trigPin1 8 // Trigger Pino
#define echoPin2 5 // Echo Pino
#define trigPin2 6 // Trigger Pino

#include <IRremote.h>                //inclui a Biblioteca 
 
int RECV_PIN = 11;                   // Pino que recebe o sinal
IRrecv irrecv(RECV_PIN); 
decode_results results; 
const int LED1 = 13;               // Pino para acionar o LED


#include <Servo.h> 
Servo servoMotor;

int AlcanceMax1 = 200;    // alcance Maximo
int AlcanceMin1 = 0;      // alcance Mínimo
long duracao1, distancia1; // Duração usado para calcular a distância

int Ligar=0;              //ligar ou desligar a função de movimento
int AlcanceMax2 = 200;    // alcance Maximo
int AlcanceMin2 = 0;      // alcance Mínimo
long duracao2, distancia2; // Duração usado para calcular a distância


void setup() 
{


  Serial.begin(9600); 
  irrecv.enableIRIn(); 
  pinMode(LED1,OUTPUT);           //LED será de Saída

 servoMotor.attach(9);   // Motor no Pino 9
 pinMode(trigPin1, OUTPUT);
 pinMode(echoPin1, INPUT);
 pinMode(trigPin2, OUTPUT);
 pinMode(echoPin2, INPUT);

}

void loop() 
{
  
  if (irrecv.decode(&results))             // Se receber algum sinal
  { 
    Serial.println(results.value, HEX);   //mostrar o sinal recebido
    irrecv.resume();  

     if (results.value==0xE12440BF ) //tecla 1 OBS: Cada tecla possui um código,
    {                                //             deve-se adicionar 0x
       digitalWrite(LED1, HIGH); 
    }
    if (results.value==0xE12428D7 ) //tecla 2
    { 
       digitalWrite(LED1, LOW); 
    }
    if (results.value==0xE12448B7 ) //source desligar os sensores
    { 
       Ligar=0; 
    }
   if (results.value==0xE124609F ) //mute ligar os sensores
    { 
       Ligar=1; 
    }

  }
if (Ligar==0)
{
 /* Os seguintes trigPin/echoPin são usados para determinar a distância do objeto */ 
 digitalWrite(trigPin1, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin1, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin1, LOW);
 duracao1 = pulseIn(echoPin1, HIGH);
 
 //Calcula a distância (em cm) baseado na velocidade do som
 distancia1 = duracao1/58.2;  
 
 //Aguarda 50ms antes da próxima leitura
 delay(500);
 
 /* Os seguintes trigPin/echoPin são usados para determinar a distância do objeto */ 
 digitalWrite(trigPin2, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin2, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin2, LOW);
 duracao2 = pulseIn(echoPin2, HIGH);
 
 //Calcula a distância (em cm) baseado na velocidade do som
 distancia2 = duracao2/58.2;
 
 Serial.print("2:");
 Serial.println(distancia2);

 if (distancia1<=20 && distancia1 <  distancia2 )      
 {
       servoMotor.write(45);
 }
 else if (distancia2 <=20 &&   distancia2 <  distancia1 )      
 {
      servoMotor.write(140);
      
 }
 else
 {
      servoMotor.write(80);
     
 }
 
 //Aguarda 50ms antes da próxima leitura
 delay(1500);
  
}
} 

