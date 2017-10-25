// Controlador1 do presépio pelo Vixen
// Implementado na sede dos Arautos do Evangelho em Recife
// Desenvolvido para maior glória de Jesus, José e Maria
// Sketch para arduino MEGA

#include "VC.h"

// Definição dos pinos
// - Para acionamento dos relês
#define Cortina1	24
#define Cortina2	25
#define CeuEstrelas1	26
#define CeuEstrelas2	27
#define SalaDomBosco	28
#define FocoBelem	29
#define BelemFimDeCurso	30
#define MotorCachoeira	31
#define FocoAnjos	32
#define FogueiraPastores	33
#define FocoRessurreicao	34
#define FumacaRessurreicao	35
#define FocoGruta	36
// #define Livre	37
// #define Livre	38
// #define Livre	39
// - para leds PWM
#define RomanosCesar	2
#define RomanosTrompetes	3
#define RomanosArauto	4
#define CasaBelem1	5
#define CasaBelem2	6
#define CasaBelem3	7
#define CasaBelemAlto4	8
#define CasaBelemAlto5	9
#define CaminhoBelem	10
#define GrutaNSra	11
#define GrutaSaoJose	12
#define LuzCachoeira	13
// - para dimmer (PWM)
#define LuzSalao	44
#define SalaDomBosco	45
#define PortaisBelem	46

#define n_pinos 28
const int pinos[] = {Cortina1, Cortina2, CeuEstrelas1, CeuEstrelas2, SalaDomBosco, FocoBelem, BelemFimDeCurso, MotorCachoeira, FocoAnjos, FogueiraPastores, FocoRessurreicao, FumacaRessurreicao, FocoGruta, RomanosCesar, RomanosTrompetes, RomanosArauto, CasaBelem1, CasaBelem2, CasaBelem3, CasaBelemAlto4, CasaBelemAlto5, CaminhoBelem, GrutaNSra, GrutaSaoJose, LuzCachoeira, LuzSalao, SalaDomBosco, PortaisBelem
};

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
  vc_init();
}

void loop(){
  vc_atualiza();
  if(cenas[CenaAbertura]>0){ // enquanto a cena estiver ativa

  }
  if(cenas[CenaAbertura]==1){ // 1 marca o início da cena
    digitalWrite(Cortina1,HIGH);
  } else if(cenas[CenaAbertura]==-1){ // -1 marca o final da cena
    digitalWrite(LuzSalao,LOW);
  }

}
