// disparador de cenas comandadas pelo Vixen
// Sketch para arduino
// desenvolvido para maior glória de Jesus, José e Maria

// cada canal definido no vixen dispara uma cena
// um temporizador sincroniza os movimentos/luzes a partir do momento que o canal aciona
#define N_CENAS 5
int cenas[N_CENAS];
long int tempoCenas[N_CENAS];
long int tempoInicioCenas[N_CENAS];

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
    case CENA: switch(senas[cnt]){
        case 0:senas[cnt] = data==0?0:1;
        break;
        case 1:senas[cnt] = data==0?-1:2;
        break;
        case 2:senas[cnt] = data==0?-1:2;
        break;
        case -1:senas[cnt] = data==0?0:1;
        break;
      }
      cnt++;
      if(cnt>=N_CENAS){ // Se recebu todo o pacote
        proximoEstado = INICIO;
        commTimer = millis();
        digitalWrite(53,LOW); // desliga o led indicador
        atualizaMotores();
      } else { // se ainda não recebeu todos valores
        proximoEstado = CENA;
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
    if(tempoCenas[0]<1000){
      servo1.write(map(tempoCenas[0],0,1000,0,180));
    } else if (tempoCenas[0]<4000){
      servo1.write(map(tempoCenas[0],1000,4000,180,0));
    }
  }
  // Na cena 1, acende-se uma luz enquanto ela estiver ativa
  if(cenas[0]==1){ // 1 marca o início da cena
    digitalWrite(pinoLuz,HIGH);
  } else if(cenas[0]==-1){ // -1 marca o final da cena
    digitalWrite(pinoLuz,LOW);
  }
}
