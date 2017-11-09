// Controlador3 do presépio pelo Vixen
// Implementado na sede dos Arautos do Evangelho em Recife
// Desenvolvido para maior glória de Jesus, José e Maria
// Sketch para arduino MEGA

// Cadastro com COM6 no PC e COM14 no notebook

// O controlador 3 usa um shield com 5 l293d para comando dos motores

// Biblioteca necessária para PWM em outros pinos
#include <SoftPWM.h>
#include "VA.h"

// Definição dos pinos
// - Para motores CC
#define BelemCasa1p 9
#define BelemCasa1n 8
#define BelemCasa2p 7
#define BelemCasa2n 6
#define BelemCasa3p 5
#define BelemCasa3n 4
#define BelemTrilhop 3
#define BelemTrilhon 2
#define BelemMoinhop 28
#define BelemMoinhon 30
#define Cruzp 32
#define Cruzn 34
#define SantaCeiap 46
#define SantaCeian 48
#define RessurreicaoPedrap 50
#define RessurreicaoPedran 52
SOFTPWM_DEFINE_CHANNEL(0, DDRA, PORTA, PORTA6);  //pin 28 - BelemMoinhop
SOFTPWM_DEFINE_CHANNEL(1, DDRC, PORTC, PORTC7);  //pin 30 - BelemMoinhon
SOFTPWM_DEFINE_CHANNEL(2, DDRC, PORTC, PORTC5);  //pin 32 - Cruzp
SOFTPWM_DEFINE_CHANNEL(3, DDRC, PORTC, PORTC3);  //pin 34 - Cruzn
SOFTPWM_DEFINE_CHANNEL(4, DDRL, PORTL, PORTL3);  //pin 46 - SantaCeiap
SOFTPWM_DEFINE_CHANNEL(5, DDRL, PORTL, PORTL1);  //pin 48 - SantaCeian
SOFTPWM_DEFINE_CHANNEL(6, DDRB, PORTB, PORTB3);  //pin 50 - RessurreicaoPedrap
SOFTPWM_DEFINE_CHANNEL(7, DDRB, PORTB, PORTB1);  //pin 52 - RessurreicaoPedran

SOFTPWM_DEFINE_OBJECT(8);
//SOFTPWM_DEFINE_EXTERN_OBJECT_WITH_PWM_LEVELS(8, 256);

// - para dimmer (PWM)
// #define Livre	45

#define n_pinos 16
const int pinos[] = {BelemCasa1p, BelemCasa1n, BelemCasa2p, BelemCasa2n, BelemCasa3p, BelemCasa3n, BelemTrilhop, BelemTrilhon, BelemMoinhop , BelemMoinhon , Cruzp , Cruzn , SantaCeiap , SantaCeian , RessurreicaoPedrap , RessurreicaoPedran };

#define n_motores 8
int potencias[n_motores];

const int n_vars = n_pinos;
int vars[n_vars];
int cnt; // contador
int estado;
int proximoEstado;
long int commTimer;

void setup() {
  // define os pinos como saídas
  for(int i=0; i<n_pinos; i++){
    pinMode(pinos[i],OUTPUT);
  }
  Palatis::SoftPWM.begin(200);
  va_init();
}

void atualizaMotores(){
  // If potencia is positive, actuate the motor via positive pin,
  // if negative, via negative pin.

  // The first 4 motors use analogWrite
  for(int i=0; i<4; i++){
    if(potencias[i]>=0){
      analogWrite(pinos[2*i+1],0);
      analogWrite(pinos[2*i],potencias[i]);
    } else {
      analogWrite(pinos[2*i],0);
      analogWrite(pinos[2*i+1],-potencias[i]);
    }
  }
  // The last 4 motors use SoftPWM
  for(int i=0; i<4; i++){
    if(potencias[i+4]>=0){ // potencias 4 a 7
      Palatis::SoftPWM.set(2*i+1,0);
      Palatis::SoftPWM.set(2*i,potencias[i+4]);
    } else {
      Palatis::SoftPWM.set(2*i,0);
      Palatis::SoftPWM.set(2*i+1,-potencias[i+4]);
    }
  }
}

void loop(){
  va_comunica();
  if(estado == FIM){
    for(int i = 0; i<n_motores; i++){
      potencias[i] = vars[2*i]-vars[2*i+1];
    }
    atualizaMotores();
  }

}
