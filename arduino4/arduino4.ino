// Controlador4 do presépio pelo Vixen
// Implementado na sede dos Arautos do Evangelho em Recife
// Desenvolvido para maior glória de Jesus, José e Maria
// Sketch para arduino MEGA

// Cadastro com COM5 no PC e COM16 no notebook

#include "VA.h"
#include <AFMotor.h>
#include <FastLED.h>

//Definição do FastLED
// Leds rgb conectados em dois caminhos
#define NUM_LEDS1 25
CRGB leds1[NUM_LEDS1];
#define DATA_PIN1 21
#define NUM_LEDS2 25
CRGB leds2[NUM_LEDS2];
#define DATA_PIN2 20
#define LED_COLOR 0xf7Ac13
// Definição dos pinos
// - Para acionamento dos motores, usando a shield de 4 motores
AF_DCMotor RessurreicaoNSJC(1);
AF_DCMotor Caravana(2);
AF_DCMotor Gruta(3);
AF_DCMotor Anjos(4);

// - leds1
#define ceiaI 23
#define ceiaN 2
#define torreI 21
#define torreN 2
#define NsaSraI 18
#define NsaSraN 3
#define cameloI 0
#define cameloN 2
#define reisI 2
#define reisN 8
#define jerusalemI 10
#define jerusalemN 5
#define JoseI 15
#define JoseN 3

const int inicios1[] = {ceiaI, torreI, NsaSraI, cameloI, reisI, jerusalemI, JoseI};
const int quants1[] = {ceiaN, torreN, NsaSraN, cameloN, reisN, jerusalemN, JoseN};
#define n_leds1 7

// - leds2
#define grutaI 0
#define grutaN 2
#define pastoresI 2
#define pastoresN 10
#define lagoI 12
#define lagoN 4
#define salaI 16
#define salaN 2
#define cachoeiraI 18
#define cachoeiraN 2
#define cesarI 20
#define cesarN 2
#define anjoI 22
#define anjoN 2

const int inicios2[] = {grutaI, pastoresI, lagoI, salaI, cachoeiraI, cesarI, anjoI};
const int quants2[] = {grutaN, pastoresN, lagoN, salaN, cachoeiraN, cesarN, anjoN};
#define n_leds2 7

#define n_motores 4
int potencias[n_motores];
//#define n_pinos 3  // n_dimmers

const int n_vars = 22;// 2*n_motores + n_leds1 + n_leds2
int vars[n_vars];
int cnt; // contador
int estado;
int proximoEstado;
long int commTimer;

void setup() {
  FastLED.addLeds<WS2811, DATA_PIN1, RGB>(leds1, NUM_LEDS1);
  FastLED.addLeds<WS2811, DATA_PIN2, RGB>(leds2, NUM_LEDS2);
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
    Caravana.setSpeed(potencias[1]);
    Caravana.run(FORWARD);
  } else {
    Caravana.setSpeed(-potencias[1]);
    Caravana.run(BACKWARD);
  }
  if (potencias[2]>0){
    Gruta.setSpeed(potencias[2]);
    Gruta.run(FORWARD);
  } else {
    Gruta.setSpeed(-potencias[2]);
    Gruta.run(BACKWARD);
  }
  if (potencias[3]>0){
    Anjos.setSpeed(potencias[3]);
    Anjos.run(FORWARD);
  } else {
    Anjos.setSpeed(-potencias[3]);
    Anjos.run(BACKWARD);
  }
}
void atualizaLeds(){
  for(int i=0; i<n_leds1; i++){
    leds1[inicios1[i]] = LED_COLOR;
    leds1[inicios1[i]] %= vars[8+i];
    for(int k=1;k<quants1[i];k++){
      leds1[inicios1[i]+k] = leds1[inicios1[i]];
    }
  }
  for(int i = 0; i<n_leds2; i++){
    leds2[inicios2[i]] = LED_COLOR;
    leds2[inicios2[i]] %= vars[15+i];
    for(int k=1;k<quants2[i];k++){
      leds2[inicios2[i]+k] = leds2[inicios2[i]];
    }
  }
  FastLED.show();

}

void loop(){
  va_comunica();
  if(estado == FIM){
    for(int i = 0; i<n_motores; i++){
      potencias[i] = vars[2*i]-vars[2*i+1];
    }
    atualizaMotores();
    atualizaLeds();
  }
}
