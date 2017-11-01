// Controlador2 do presépio pelo Vixen
// Implementado na sede dos Arautos do Evangelho em Recife
// Desenvolvido para maior glória de Jesus, José e Maria
// Sketch para arduino MEGA

#include <Servo.h>
#include "VA.h"

// Definição dos pinos
// - Para servos
#define pinbdDomBosco	22
#define pinbeDomBosco	23
#define pinCabecaDomBosco	24
#define pinCorpoDomBosco	25
#define pinMenino1Gira	26
#define pinMenino1Pula	27
#define pinMenino2Gira	28
#define pinMenino2Pula	29
#define pinMenino3Gira	30
#define pinMenino3Pula	31
#define pinMenino4Pula	32
#define pinCabecaNSCruz	33
#define pinRomaTrombeta1	34
#define pinRomaTrombeta2	35
#define pinRomaTrombeta3	36
#define pinRomaTrombeta4	37
#define pinRomaTrombeta5	38
#define pinRomaTrombeta6	39
#define pinRomaArauto	40
#define pinCarpintaria1	41
#define pinCarpintaria2	42
#define pinPadaria1	43
#define pinPadaria2	47
#define pinAnjoPastores	48
#define pinReiMago1	49
#define pinReiMago2	50
#define pinReiMago3	51
// - para leds PWM
#define PastoresNaFogueira	2
#define LuzAnjoPastores	3
#define CaminhoCaravana	4
#define EstrelaDeBelem	5
#define SantaCeia1	6
#define SantaCeia2	7
#define Carpintaria	8
#define Padaria	9
#define Calvario	10
#define RaioCalvario	11
#define FocoCalvario	12
#define LuzFinal1	13
// - para dimmer (PWM)
#define VitraisGruta	44
#define PastoresNaGruta	45
#define ReisNaGruta	46

#define n_servos  27
#define n_leds    12
#define n_dimmers  3
#define n_pinos   42
const int pinos[] = {pinbdDomBosco, pinbeDomBosco, pinCabecaDomBosco, pinCorpoDomBosco, pinMenino1Gira, pinMenino1Pula, pinMenino2Gira, pinMenino2Pula, pinMenino3Gira, pinMenino3Pula, pinMenino4Pula, pinCabecaNSCruz, pinRomaTrombeta1, pinRomaTrombeta2, pinRomaTrombeta3, pinRomaTrombeta4, pinRomaTrombeta5, pinRomaTrombeta6, pinRomaArauto, pinCarpintaria1, pinCarpintaria2, pinPadaria1, pinPadaria2, pinAnjoPastores, pinReiMago1, pinReiMago2, pinReiMago3, PastoresNaFogueira, LuzAnjoPastores, CaminhoCaravana, EstrelaDeBelem, SantaCeia1, SantaCeia2, Carpintaria, Padaria, Calvario, RaioCalvario, FocoCalvario, LuzFinal1, VitraisGruta, PastoresNaGruta, ReisNaGruta };

Servo servos[n_servos];
// Servo bdDomBosco;
// Servo beDomBosco;
// Servo CabecaDomBosco;
// Servo CorpoDomBosco;
// Servo Menino1Gira;
// Servo Menino1Pula;
// Servo Menino2Gira;
// Servo Menino2Pula;
// Servo Menino3Gira;
// Servo Menino3Pula;
// Servo Menino4Pula;
// Servo CabecaNSCruz;
// Servo RomaTrombeta1;
// Servo RomaTrombeta2;
// Servo RomaTrombeta3;
// Servo RomaTrombeta4;
// Servo RomaTrombeta5;
// Servo RomaTrombeta6;
// Servo RomaArauto;
// Servo Carpintaria1;
// Servo Carpintaria2;
// Servo Padaria1;
// Servo Padaria2;
// Servo AnjoPastores;
// Servo ReiMago1;
// Servo ReiMago2;
// Servo ReiMago3;

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
  for(int i = 0; i<n_servos; i++){
    servos[i].attach(pinos[i]);
  }
  va_init();
}

void loop(){
  va_comunica();
  if(estado = FIM){
    for(int i = 0; i<n_servos; i++){
      servos[i].write(vars[i]);
    }
    for(int i = n_servos; i < (n_servos + n_leds + n_dimmers); i++){
      analogWrite(pinos[i], vars[i]);
    }

  }

}
