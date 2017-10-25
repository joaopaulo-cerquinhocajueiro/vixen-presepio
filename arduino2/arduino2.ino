// Controlador2 do presépio pelo Vixen
// Implementado na sede dos Arautos do Evangelho em Recife
// Desenvolvido para maior glória de Jesus, José e Maria
// Sketch para arduino MEGA

#include <Servo.h>
#include "VC.h"

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

#define n_pinos 42
const int pinos[] = {pinbdDomBosco, pinbeDomBosco, pinCabecaDomBosco, pinCorpoDomBosco, pinMenino1Gira, pinMenino1Pula, pinMenino2Gira, pinMenino2Pula, pinMenino3Gira, pinMenino3Pula, pinMenino4Pula, pinCabecaNSCruz, pinRomaTrombeta1, pinRomaTrombeta2, pinRomaTrombeta3, pinRomaTrombeta4, pinRomaTrombeta5, pinRomaTrombeta6, pinRomaArauto, pinCarpintaria1, pinCarpintaria2, pinPadaria1, pinPadaria2, pinAnjoPastores, pinReiMago1, pinReiMago2, pinReiMago3, PastoresNaFogueira, LuzAnjoPastores, CaminhoCaravana, EstrelaDeBelem, SantaCeia1, SantaCeia2, Carpintaria, Padaria, Calvario, RaioCalvario, FocoCalvario, LuzFinal1, VitraisGruta, PastoresNaGruta, ReisNaGruta };

Servo bdDomBosco;
Servo beDomBosco;
Servo CabecaDomBosco;
Servo CorpoDomBosco;
Servo Menino1Gira;
Servo Menino1Pula;
Servo Menino2Gira;
Servo Menino2Pula;
Servo Menino3Gira;
Servo Menino3Pula;
Servo Menino4Pula;
Servo CabecaNSCruz;
Servo RomaTrombeta1;
Servo RomaTrombeta2;
Servo RomaTrombeta3;
Servo RomaTrombeta4;
Servo RomaTrombeta5;
Servo RomaTrombeta6;
Servo RomaArauto;
Servo Carpintaria1;
Servo Carpintaria2;
Servo Padaria1;
Servo Padaria2;
Servo AnjoPastores;
Servo ReiMago1;
Servo ReiMago2;
Servo ReiMago3;

// cada canal definido no vixen dispara uma cena
// um temporizador sincroniza os movimentos/luzes a partir do momento que o canal aciona
#define CenaAbertura 0
#define CenaDomBosco1 1
#define CenaBelem 2
#define CenaPastores 3
#define CenaRessureicao 4
#define CenaRomanos 5
#define CenaBelem 6
#define CenaGruta 7
#define CenaFechamento 8
#define N_CENAS 8
int n_cenas = N_CENAS;
// Arrays das cenas, para não complicar muito
int cenas[N_CENAS];
long int tempoCenas[N_CENAS];
long int tempoInicioCenas[N_CENAS];
int cnt; // contador
int estado;
int proximoEstado;
long int commTimer;

void setup() {
  // define os pinos como saídas
  for(int i=0; i<n_pinos; i++){
    pinMode(pinos[i],OUTPUT);
  }
  bdDomBosco.attach(pinbdDomBosco);
  beDomBosco.attach(pinbeDomBosco);
  CabecaDomBosco.attach(pinCabecaDomBosco);
  CorpoDomBosco.attach(pinCorpoDomBosco);
  Menino1Gira.attach(pinMenino1Gira);
  Menino1Pula.attach(pinMenino1Pula);
  Menino2Gira.attach(pinMenino2Gira);
  Menino2Pula.attach(pinMenino2Pula);
  Menino3Gira.attach(pinMenino3Gira);
  Menino3Pula.attach(pinMenino3Pula);
  Menino4Pula.attach(pinMenino4Pula);
  CabecaNSCruz.attach(pinCabecaNSCruz);
  RomaTrombeta1.attach(pinRomaTrombeta1);
  RomaTrombeta2.attach(pinRomaTrombeta2);
  RomaTrombeta3.attach(pinRomaTrombeta3);
  RomaTrombeta4.attach(pinRomaTrombeta4);
  RomaTrombeta5.attach(pinRomaTrombeta5);
  RomaTrombeta6.attach(pinRomaTrombeta6);
  RomaArauto.attach(pinRomaArauto);
  Carpintaria1.attach(pinCarpintaria1);
  Carpintaria2.attach(pinCarpintaria2);
  Padaria1.attach(pinPadaria1);
  Padaria2.attach(pinPadaria2);
  AnjoPastores.attach(pinAnjoPastores);
  ReiMago1.attach(pinReiMago1);
  ReiMago2.attach(pinReiMago2);
  ReiMago3.attach(pinReiMago3);

  vc_init();
}

void loop(){
  vc_atualiza();
  if(cenas[CenaAbertura]>0){ // enquanto a cena estiver ativa

  }
  if(cenas[CenaAbertura]==1){ // 1 marca o início da cena
    digitalWrite(Padaria,HIGH);
  } else if(cenas[CenaAbertura]==-1){ // -1 marca o final da cena
    digitalWrite(Padaria,LOW);
  }

}
