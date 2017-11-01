// Controlador4 do presépio pelo Vixen
// Implementado na sede dos Arautos do Evangelho em Recife
// Desenvolvido para maior glória de Jesus, José e Maria
// Sketch para arduino MEGA

#include "VA.h"
#include <AFMotor.h>

// Definição dos pinos
// - Para acionamento dos motores, usando a shield de 4 motores
AF_DCMotor RessurreicaoNSJC(1);
AF_DCMotor Caravana(2);
AF_DCMotor Gruta(3);
AF_DCMotor Anjos(4);
// - para dimmer (PWM)
#define VitraisSantaCeia	44
#define Ressurreicao	45
#define LuzFinal2	46

#define n_motores 4
int potencias[n_motores];
#define n_dimmers 3
#define n_pinos 3  // n_dimmers
const int pinos[] = { VitraisSantaCeia, Ressurreicao, LuzFinal2 };

const int n_vars = 11;// 2*n_motores + n_dimmers
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

  va_init();
}

void atualizaMotores(){
  if (potencias[0]>0){
    RessurreicaoNSJC.setSpeed(potencias[0]);
    RessurreicaoNSJC.run(FORWARD);
  } else {
    RessurreicaoNSJC.setSpeed(-potencias[0]);
    RessurreicaoNSJC.run(BACKWARD);
  }
  if (potencias[1]>0){
    Caravana.setSpeed(potencias[0]);
    Caravana.run(FORWARD);
  } else {
    Caravana.setSpeed(-potencias[0]);
    Caravana.run(BACKWARD);
  }
  if (potencias[2]>0){
    Gruta.setSpeed(potencias[0]);
    Gruta.run(FORWARD);
  } else {
    Gruta.setSpeed(-potencias[0]);
    Gruta.run(BACKWARD);
  }
  if (potencias[3]>0){
    Anjos.setSpeed(potencias[0]);
    Anjos.run(FORWARD);
  } else {
    Anjos.setSpeed(-potencias[0]);
    Anjos.run(BACKWARD);
  }
}

void loop(){
  va_comunica();
  if(estado == FIM){
    for(int i = 0; i<n_motores; i++){
      potencias[i] = vars[2*i]-vars[2*i+1];
    }
    atualizaMotores();
    for(int i = 0; i<n_pinos; i++){
      analogWrite(pinos[i],vars[i+8]);
    }
  }
}
