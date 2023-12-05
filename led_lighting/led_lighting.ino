#include <LiquidCrystal.h>
#include <Wire.h>
#define esclavo 9

#include <Arduino.h>

struct ObjetoPreguntas {
    String pregunta;
    String respuesta1;
    String respuesta2;
    String respuesta3;
    String respuesta4;
    int respuestaElegida;
    int respuestaCorrecta;
};

ObjetoPreguntas preguntas[] = {
  {"Cuantos decimales tiene pi?", "Dos", "Cien", "Infinitos", "Mil", 0, 3},
  {"Que elementos forman la sal?", "Sodio y potasio", "Sodio y cloro", "Sodio y carbono", "Potasio y cloro", 0, 2},
  {"Quien pinto la obra 'Guernica'?", "Paul Cezanne", "Pablo Picasso", "Diego Rivera", "Salvador Dali", 0, 3},
  {"La frase Carpe diem significa:", "Un movimiento cientifico", "Un movimiento telurico", "Un movimiento espiritual", "Aprovecha el dia", 0, 3},
  {"Pais ganador del Mundial 2010?", "Portugal", "Argentina", "Espana", "El Salvador", 0, 3}
};

LiquidCrystal lcd (13,12,11,10,9,8);

String response = "";

int intIndexPreguntas = 0;

bool changedFlag = true;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  Wire.begin(esclavo);
  Wire.onReceive(Recibir);
  lcd.setCursor(0,0);
  lcd.print("Bienvenido");

  pinMode(0, INPUT);
  pinMode(1, INPUT);
}

void Recibir(){
  changedFlag = true;
  response = "";
  int intResponse = 0;
  while( Wire.available() ){
    intResponse = Wire.read();
  }
  switch (intResponse) {
    case 1:
      response = preguntas[intIndexPreguntas].respuesta1;
      preguntas[intIndexPreguntas].respuestaElegida = intResponse;
      break;
    case 2:
      response = preguntas[intIndexPreguntas].respuesta2;
      preguntas[intIndexPreguntas].respuestaElegida = intResponse;
      break;
    case 3:
      response = preguntas[intIndexPreguntas].respuesta3;
      preguntas[intIndexPreguntas].respuestaElegida = intResponse;
      break;
    case 4:
      response = preguntas[intIndexPreguntas].respuesta4;
      preguntas[intIndexPreguntas].respuestaElegida = intResponse;
      break;
    case 5:
      if (intIndexPreguntas != 0){
        intIndexPreguntas--;
        lcd.clear();
        delay(500);
      }
      break;
    case 6:
      size_t arrayLength = sizeof(preguntas) / sizeof(preguntas[0]);

      if (intIndexPreguntas != arrayLength - 1){
        intIndexPreguntas++;
        lcd.clear();
        delay(500);
      }
      break;
    default:
      response = "";
      break;
  }

  if (intResponse > 4){
    switch (preguntas[intIndexPreguntas].respuestaElegida) {
      case 0:
        response = "";
        break;
      case 1:
        response = preguntas[intIndexPreguntas].respuesta1;
        break;
      case 2:
        response = preguntas[intIndexPreguntas].respuesta2;
        break;
      case 3:
        response = preguntas[intIndexPreguntas].respuesta3;
        break;
      case 4:
        response = preguntas[intIndexPreguntas].respuesta4;
        break;
    }
  } 
}

void loop() {
  // put your main code here, to run repeatedly:
  if (changedFlag){
    changedFlag = false;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(preguntas[intIndexPreguntas].pregunta);
    lcd.setCursor(0,1);
    lcd.print(response);
  }
}
