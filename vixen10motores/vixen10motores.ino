// Controlador de 10 motores CC pelo Vixen
// Sketch para arduino MEGA
// desenvolvido para maior glória de Jesus, José e Maria

// Biblioteca necessária para PWM em outros pinos
#include <SoftPWM.h>



// Define os pinos utilizados para para cada motor são 12 em hardPWM
#define m01p 13
#define m01n 12
#define m02p 11
#define m02n 10
#define m03p 9
#define m03n 8
#define m04p 7
#define m04n 6
#define m05p 5
#define m05n 4
#define m06p 3
#define m06n 2
// e mais 8 em softPWM
SOFTPWM_DEFINE_CHANNEL(0, DDRA, PORTA, PORTA6);  //Arduino pin 0
#define m07p 28 // PA6
SOFTPWM_DEFINE_CHANNEL(1, DDRC, PORTC, PORTC7);  //Arduino pin 1
#define m07n 30 // PC7
SOFTPWM_DEFINE_CHANNEL(2, DDRC, PORTC, PORTC5);  //Arduino pin 2
#define m08p 32 // PC5
SOFTPWM_DEFINE_CHANNEL(3, DDRC, PORTC, PORTC3);  //Arduino pin 3
#define m08n 34 // PC3
SOFTPWM_DEFINE_CHANNEL(4, DDRL, PORTL, PORTL3);  //Arduino pin 4
#define m09p 46 // PL3
SOFTPWM_DEFINE_CHANNEL(5, DDRL, PORTL, PORTL1);  //Arduino pin 5
#define m09n 48 // PL1
SOFTPWM_DEFINE_CHANNEL(6, DDRB, PORTB, PORTB3);  //Arduino pin 6
#define m10p 50 // PB3
SOFTPWM_DEFINE_CHANNEL(7, DDRB, PORTB, PORTB1);  //Arduino pin 7
#define m10n 52 // PB1

SOFTPWM_DEFINE_OBJECT(8);

const int motores[] = {m01p,m01n,m02p,m02n,m03p,m03n,m04p,m04n,m05p,m05n,m06p,m06n,m07p,m07n,m08p,m08n,m09p,m09n,m10p,m10n};

// Valores das potências dos motores
int potencias[] = {0,0,0,0,0,0,0,0,0,0};

// Algumas variaveis para recebimento dos dados
// pacote da forma:
// '<',m01p,m01n,...,m10p,m10n
// enviado pelo vixen a 115,2 kbps
int cnt = 0; // contador
#define INICIO 0 // esperando inicio
#define VALORP 1  // esperando valor positivo de motor
#define VALORN 2  // esperando valor negativo de motor
int estado = INICIO;
int proximoEstado;
long int commTimer;
const long int commTimeOut = 300;

void setup() {
  // Todos os pinos dos motores são saídas
  for(int i = 0; i<20; i++){
    pinMode(motores[i],OUTPUT);
  }
  // Iniciando o softPWM
  Palatis::SoftPWM.begin(255);
  // Using pin 53 for debug, with a led that lights up when receiving a package
  pinMode(53,OUTPUT);
  Serial.begin(115200);
  commTimer = millis();
}

void atualizaMotores(){
  // If potencia is positive, actuate the motor via positive pin,
  // if negative, via negative pin.

  // The first 6 motors use analogWrite
  for(int i=0; i<6; i++){
    if(potencias[i]>=0){
      analogWrite(motores[2*i+1],0);
      analogWrite(motores[2*i],potencias[i]);
    } else {
      analogWrite(motores[2*i],0);
      analogWrite(motores[2*i+1],-potencias[i]);
    }
  }
  // The last 4 motors use SoftPWM
  for(int i=0; i<4; i++){
    if(potencias[i]>=0){
      Palatis::SoftPWM.set(2*i+1,0);
      Palatis::SoftPWM.set(2*i,potencias[i]);
    } else {
      Palatis::SoftPWM.set(2*i,0);
      Palatis::SoftPWM.set(2*i+1,-potencias[i]);
    }
  }
}

//Main loop
void loop() {
  if(Serial.available()){ // Se tem um dado na serial
    int data = Serial.read(); //leia-o
    switch(estado){ // Dependendo do estado
    case INICIO: if (data == '<'){ // Se chegar o começo do pacote
        digitalWrite(53,HIGH);     // Liga o led indicador (pode não estar conectado)
        proximoEstado = VALORP;     // Passa a esperar os valores dos motores
        cnt = 0;                   // a começar do 0
      } else {
        proximoEstado = INICIO;
      }
      break;
    case VALORP: potencias[cnt] = data;
      proximoEstado = VALORN;
      break;
    case VALORN: potencias[cnt] = potencias[cnt] - data; // potencia fica como valorP-valorN
      cnt++;
      if(cnt>=10){ // Se recebu 10 potências
        proximoEstado = INICIO;
        commTimer = millis();
        digitalWrite(53,LOW); // desliga o led indicador
        atualizaMotores();
      } else { // se ainda não recebeu 10 valores
        proximoEstado = VALORP;
      }
      break;
    }
    estado = proximoEstado;
  }
  // Timeout check
  if (millis-commTimer>commTimeOut){ //communication lost
    estado = INICIO;
    digitalWrite(53,LOW); // desliga o led indicador
    while(Serial.available() > 0) { // flush the incoming serial buffer
      char t = Serial.read();
    }
    Serial.end(); // Restart the serial communication
    Serial.begin(115200);
    commTimer = millis();
  }
}
