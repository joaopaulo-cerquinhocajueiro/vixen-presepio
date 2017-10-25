#include <Servo.h>

// disparador de cenas comandadas pelo Vixen
// Sketch para arduino
// desenvolvido para maior glória de Jesus, José e Maria

// cada canal definido no vixen dispara uma cena
// um temporizador sincroniza os movimentos/luzes a partir do momento que o canal aciona
#define N_CENAS 5
int cenas[N_CENAS];
long int tempoCenas[N_CENAS];
long int tempoInicioCenas[N_CENAS];

// Variáveis de exemplo
Servo bdDomBosco;
Servo beDomBosco;
const int pinoLuz = 46;
const int pinoDimmer = 7;
const int pinobdDomBosco = 9;
const int pinobeDomBosco = 11;

// Algumas variaveis para recebimento dos dados
// pacote da forma:
// '<',CENA0,CENA1,...,CENAn
// enviado pelo vixen a 115,2 kbps
#define BAUD_RATE 115200
#define SOF '<'
int cnt = 0; // contador
#define INICIO 0 // esperando inicio
#define CENA 1  // esperando valor positivo de motor
int estado = INICIO;
int proximoEstado;
long int commTimer;
const long int commTimeOut = 300;

void setup() {
  // Using pin 53 for debug, with a led that lights up when receiving a package
  pinMode(53,OUTPUT);
  Serial.begin(115200);
  commTimer = millis();
  bdDomBosco.attach(pinobdDomBosco);
  beDomBosco.attach(pinobeDomBosco);

}

void comunica(){
  if(Serial.available()){ // Se tem um dado na serial
    int data = Serial.read(); //leia-o
    switch(estado){ // Dependendo do estado
    case INICIO: if (data == '<'){ // Se chegar o começo do pacote
        digitalWrite(53,HIGH);     // Liga o led indicador (pode não estar conectado)
        proximoEstado = CENA;     // Passa a esperar os valores dos motores
        cnt = 0;                   // a começar do 0
      } else {
        proximoEstado = INICIO;
      }
      break;
    case CENA: switch(cenas[cnt]){
        case 0:cenas[cnt] = data==0?0:1;
        break;
        case 1:cenas[cnt] = data==0?-1:2;
        break;
        case 2:cenas[cnt] = data==0?-1:2;
        break;
        case -1:cenas[cnt] = data==0?0:1;
        break;
      }
      cnt++;
      if(cnt>=N_CENAS){ // Se recebu todo o pacote
        proximoEstado = INICIO;
        commTimer = millis();
        digitalWrite(53,LOW); // desliga o led indicador
      } else { // se ainda não recebeu todos valores
        proximoEstado = CENA;
      }
      break;
    }
    estado = proximoEstado;
  }
  // Timeout check
  if (millis()-commTimer>commTimeOut){ //communication lost
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

void atualiza(){
  comunica();
  // Checa o estado de cada cena e ajusta o tempo desde que cada cena iniciou
  for(int i=0;i<N_CENAS;i++){
    switch(cenas[i]){
      case  1: tempoInicioCenas[i] = millis();
               break;
      case  2: tempoCenas[i] = millis()-tempoInicioCenas[i];
               break;
      case -1: tempoCenas[i] = 0;
               break;
    }
  }
}

void loop() {
  atualiza(); // faz a comunicação e atualiza as variáveis de cada cena.

  /////Exemplos/////
  // Na cena 0, servo1 vai de 0 a 180 em 1s e volta a 0 em 3s.
  if(cenas[0]>0){
    // configuração do braço direito
    if(tempoCenas[0]<1000){
        bdDomBosco.write(map(tempoCenas[0],0,1000,0,180));
    } else if (tempoCenas[0]<4000){
      bdDomBosco.write(map(tempoCenas[0],1000,4000,180,0));
    } else if(tempoCenas[0]<5000){
      bdDomBosco.write(map(tempoCenas[0],4000,5000,0,90));
    } else if(tempoCenas[0]<5500){
    } else if(tempoCenas[0]<6000){
      bdDomBosco.write(map(tempoCenas[0],5500,6000,90,45));
    }
    // configuração do braço esquerdo
    if(tempoCenas[0]<500){
      beDomBosco.write(map(tempoCenas[0],0,500,20,40));
    } else if (tempoCenas[0]<1500){
      beDomBosco.write(map(tempoCenas[0],500,1500,40,90));
    } else if(tempoCenas[0]<5000){
      beDomBosco.write(map(tempoCenas[0],1500,5000,90,30));
    } else if(tempoCenas[0]<5500){
    } else if(tempoCenas[0]<6000){
      beDomBosco.write(map(tempoCenas[0],5500,6000,30,45));
    }
   }
  // Na cena 1, acende-se uma luz enquanto ela estiver ativa
  if(cenas[1]==1){ // 1 marca o início da cena
    digitalWrite(pinoLuz,HIGH);
  } else if(cenas[1]==-1){ // -1 marca o final da cena
    digitalWrite(pinoLuz,LOW);
  }
  // Ainda cena 1, variando a intensidade de uma luz 
  if(cenas[1]>0){ // 1 marca o início da cena
    if(tempoCenas[1]<2000){
      analogWrite(pinoDimmer,map(tempoCenas[1],000,2000,0,255));
    } else if(tempoCenas[1]<6000){
      analogWrite(pinoDimmer,255);
    }else if(tempoCenas[1]<8000){
      analogWrite(pinoDimmer,map(tempoCenas[1],6000,8000,255,0));
    }
  }

}
