
#define velaBoa 9
#define velaMa 10
#define lado A0

int forcaBoa;
int forcaMa;

void setup() {
  // put your setup code here, to run once:
pinMode(velaBoa,OUTPUT);
pinMode(velaMa,OUTPUT);
pinMode(lado,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
delay(50);
forcaBoa = analogRead(lado)>>2;
forcaMa = 255-forcaBoa;
analogWrite(velaBoa,forcaBoa);
}
