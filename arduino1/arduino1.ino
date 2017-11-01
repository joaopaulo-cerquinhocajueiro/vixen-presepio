// Controlador1 do presépio pelo Vixen
// Implementado na sede dos Arautos do Evangelho em Recife
// Desenvolvido para maior glória de Jesus, José e Maria
// Sketch para arduino MEGA

#include "VA.h"

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

#define n_reles 13
#define n_leds  12
#define n_dimmers 3
#define n_pinos 28  // n_reles + n_leds + n_dimmers
const int pinos[] = {Cortina1, Cortina2, CeuEstrelas1, CeuEstrelas2, SalaDomBosco, FocoBelem, BelemFimDeCurso, MotorCachoeira, FocoAnjos, FogueiraPastores, FocoRessurreicao, FumacaRessurreicao, FocoGruta, RomanosCesar, RomanosTrompetes, RomanosArauto, CasaBelem1, CasaBelem2, CasaBelem3, CasaBelemAlto4, CasaBelemAlto5, CaminhoBelem, GrutaNSra, GrutaSaoJose, LuzCachoeira, LuzSalao, SalaDomBosco, PortaisBelem
};

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
  va_init();
}

void loop(){
  va_comunica();
  if(estado = FIM){
    for(int i = 0; i<n_reles; i++){
      digitalWrite(pinos[i],vars[i]);
    }
    for(int i = n_reles; i < (n_reles + n_leds + n_dimmers); i++){
      analogWrite(pinos[i], vars[i]);
    }
  }
}
