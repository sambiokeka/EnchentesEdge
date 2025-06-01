#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define col 16
#define lin 2
#define ende 0x27

LiquidCrystal_I2C lcd1(39, 16, 2); 
LiquidCrystal_I2C lcd2(38, 16, 2);  

const int sensor = 7;

int ledVerde = 11;
int ledAmarelo = 12;
int ledVermelho = 13;

int buzzer = 10;
long duracao;
float altura;

char buffer1[16];
char buffer2[16];
  
int estadoDisplay = 0;

String textoAnteriorLinha1 = "";
String textoAnteriorLinha2 = "";
String textoAnteriorLinha3 = "";
String textoAnteriorLinha4 = "";

unsigned long tempoDisplayAnterior = 0;
unsigned long intervaloSerial = 500;
unsigned long tempoAnterior = 0;

String casoAtualUMIDADE = "";
String casoAtualALTURA = "";

float umidadeBuffer[5] = {0};
float alturaBuffer[5] = {0};
int umidadeIndex = 0;
int alturaIndex = 0;

float microsegundosParaCentimetros(long microsegundos) {
  return microsegundos / 29.0 / 2.0;
}

void inicializaBuffers() {
  for (int i = 0; i < 5; i++) {
    umidadeBuffer[i] = map(analogRead(A2), 0, 1023, 0, 100);
    alturaBuffer[i] = 0;
  }
}

float calculaMedia(float buffer[], int tamanho) {
  float soma = 0;
  for (int i = 0; i < tamanho; i++) {
    soma += buffer[i];
  }
  return soma / tamanho;
}

void atualizaMedias(float umidade, float altura, float &umidadeMedia, float &alturaMedia) {
  umidadeBuffer[umidadeIndex] = umidade;
  umidadeIndex = (umidadeIndex + 1) % 5;

  alturaBuffer[alturaIndex] = altura;
  alturaIndex = (alturaIndex + 1) % 5;

  umidadeMedia = calculaMedia(umidadeBuffer, 5);
  alturaMedia = calculaMedia(alturaBuffer, 5);
}

void setup() {
  lcd1.init();
  lcd1.backlight();
  lcd1.clear();

  lcd2.init();
  lcd2.backlight();
  lcd2.clear();
  
  Serial.begin(9600);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);

  inicializaBuffers();
  
}

void processaUMIDADE(float umidadeMedia) {
  if (umidadeMedia < 80) {
    casoAtualUMIDADE = "1";
  } else {
    casoAtualUMIDADE = "3";
  }
}

void processaALTURA(float alturaMedia) {
  if (alturaMedia < 10) {
    casoAtualALTURA = "1";
  } else if (alturaMedia < 30) {
    casoAtualALTURA = "2";
  } else {
    casoAtualALTURA = "3";
  }
}

void atualizaDisplay(float altura, float umidadeMedia) {
  unsigned long agora = millis();

  if (agora - tempoDisplayAnterior >= 5000) {
    tempoDisplayAnterior = agora;
    estadoDisplay = (estadoDisplay + 1) % 2;
  }

  String linha1, linha2, linha3, linha4;

  switch (estadoDisplay) {
    case 0:
      dtostrf(altura, 4, 1, buffer1);
      linha1 = "Nivel da agua:";
      linha2 = String(buffer1) + " cm";

      linha3 = "Grau de perigo:";
      linha4 = (casoAtualALTURA == "1") ? "Baixo" :
               (casoAtualALTURA == "2") ? "Medio" :
               "Alto";
      break;

    case 1:
      dtostrf(umidadeMedia, 4, 1, buffer2);
      linha1 = "Umidade:";
      linha2 = String(buffer2) + "%";

      linha3 = "Previsao:";
      linha4 = (casoAtualUMIDADE == "1") ? "Diminuir" : "Aumentar";
      break;
  }

  if (linha1 != textoAnteriorLinha1) {
    lcd1.setCursor(0, 0); lcd1.print("                ");
    lcd1.setCursor(0, 0); lcd1.print(linha1);
    textoAnteriorLinha1 = linha1;
  }

  if (linha2 != textoAnteriorLinha2) {
    lcd1.setCursor(0, 1); lcd1.print("                ");
    lcd1.setCursor(0, 1); lcd1.print(linha2);
    textoAnteriorLinha2 = linha2;
  }

  if (linha3 != textoAnteriorLinha3) {
    lcd2.setCursor(0, 0); lcd2.print("                ");
    lcd2.setCursor(0, 0); lcd2.print(linha3);
    textoAnteriorLinha3 = linha3;
  }

  if (linha4 != textoAnteriorLinha4) {
    lcd2.setCursor(0, 1); lcd2.print("                ");
    lcd2.setCursor(0, 1); lcd2.print(linha4);
    textoAnteriorLinha4 = linha4;
  }
}


void loop() {
  unsigned long tempoAtual = millis();

  if (tempoAtual - tempoAnterior >= intervaloSerial) {
    tempoAnterior = tempoAtual;

    pinMode(sensor, OUTPUT);
    digitalWrite(sensor, LOW);
    delayMicroseconds(2);
    digitalWrite(sensor, HIGH);
    delayMicroseconds(10);
    digitalWrite(sensor, LOW);
    
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);

    if (casoAtualALTURA == "1") {
      digitalWrite(ledVerde, HIGH);
	  noTone(buzzer);
    } else if (casoAtualALTURA == "2") {
      digitalWrite(ledAmarelo, HIGH);
      tone(buzzer, 200);
    } else if (casoAtualALTURA == "3") {
      digitalWrite(ledVermelho, HIGH);
      tone(buzzer, 400);
    }

    pinMode(sensor, INPUT);
    duracao = pulseIn(sensor, HIGH);

    altura = microsegundosParaCentimetros(duracao);

    int umidade = analogRead(A0);
    int umidadeAjustada = map(constrain(umidade, 0, 1023), 0, 1023, 0, 100);

    float umidadeMedia, alturaMedia;
    atualizaMedias(umidadeAjustada, altura, umidadeMedia, alturaMedia);

    processaUMIDADE(umidadeMedia);
    processaALTURA(alturaMedia);

    atualizaDisplay(alturaMedia, umidadeMedia);
  }
}
