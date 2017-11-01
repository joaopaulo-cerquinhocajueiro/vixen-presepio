// Controlador4 do presépio pelo Vixen
// Implementado na sede dos Arautos do Evangelho em Recife
// Desenvolvido para maior glória de Jesus, José e Maria
// Sketch para arduino MEGA

#include "VA.h"
#include <AFMotor.h>
#include <FastLED.h>

//Definição do FastLED
#define NUM_LEDS 50
#define DATA_PIN 2
CRGB leds[NUM_LEDS];
#define DATA_PIN 21
#define LED_COLOR 0xf7Ac13
// Definição dos pinos
// - Para acionamento dos motores, usando a shield de 4 motores
AF_DCMotor RessurreicaoNSJC(1);
AF_DCMotor Caravana(2);
AF_DCMotor Gruta(3);
AF_DCMotor Anjos(4);
// - para FastLED (era no dimmer)
#define VitraisSantaCeia 47	//48 e 49
#define Ressurreicao	44 // 45 e 46
#define LuzFinal2	41 // 42 e 43

#define n_motores 4
int potencias[n_motores];
#define n_dimmers 3
#define n_pinos 3  // n_dimmers
const int dimmers[] = { VitraisSantaCeia, Ressurreicao, LuzFinal2 };

const int n_vars = 11;// 2*n_motores + n_dimmers
int vars[n_vars];
int cnt; // contador
int estado;
int proximoEstado;
long int commTimer;

void setup() {
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
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
    for(int i = 0; i<n_dimmers; i++){
      leds[dimmers[i]] = LED_COLOR;
      leds[dimmers[i]] %= vars[8+i];
      leds[dimmers[i]+1] = leds[dimmers[i]];
    }
    FastLED.show();
  }
}
