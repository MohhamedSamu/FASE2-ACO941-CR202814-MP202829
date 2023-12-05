#include <Wire.h>
#include <LiquidCrystal.h>
#define esclavo 9
int codeToSend = 0;

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

int intIndexPreguntas = 0;

bool modoRevision = false;

LiquidCrystal lcd (13,12,11,10,9,8);

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);

  lcd.begin(16, 2);
}

void loop() {

  if (digitalRead(4) == HIGH){
    if (codeToSend < 5 && codeToSend > 0){
      Wire.beginTransmission(esclavo);
      Wire.write(codeToSend);
      Wire.endTransmission();
      preguntas[intIndexPreguntas].respuestaElegida = codeToSend;
      delay(200);
    }
  }

  if (digitalRead(0) == HIGH){
    codeToSend = 1;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(preguntas[intIndexPreguntas].respuesta1);
    delay(50);
  }

  if (digitalRead(1) == HIGH){
    codeToSend = 2;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(preguntas[intIndexPreguntas].respuesta2);
    delay(50);
  }

  if (digitalRead(2) == HIGH){
    codeToSend = 3;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(preguntas[intIndexPreguntas].respuesta3);
    delay(50);
  }

  if (digitalRead(3) == HIGH){
    codeToSend = 4;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(preguntas[intIndexPreguntas].respuesta4);
    delay(50);
  }

  if (digitalRead(5) == HIGH){
    if (intIndexPreguntas != 0){
      intIndexPreguntas--;
      codeToSend = 5;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ESPACIO DE RESPUESTAS PARA ");
      lcd.setCursor(0,1);
      lcd.print("PREGUNTA # ");
      lcd.setCursor(11,1);
      lcd.print(intIndexPreguntas + 1);
      Wire.beginTransmission(esclavo);
      Wire.write(codeToSend);
      Wire.endTransmission();
      delay(200);
    }
  }

  if (digitalRead(6) == HIGH){
    size_t arrayLength = sizeof(preguntas) / sizeof(preguntas[0]);
    if (intIndexPreguntas != arrayLength - 1){
      intIndexPreguntas++;
      codeToSend = 6;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ESPACIO DE RESPUESTAS PARA ");
      lcd.setCursor(0,1);
      lcd.print("PREGUNTA # ");
      lcd.setCursor(11,1);
      lcd.print(intIndexPreguntas + 1);
      Wire.beginTransmission(esclavo);
      Wire.write(codeToSend);
      Wire.endTransmission();
      delay(200);
    }
  }

  if (digitalRead(7) == LOW){
    if (modoRevision){
      modoRevision = false;
      codeToSend = 0;
      lcd.clear();
    }
    if (codeToSend == 0){
      lcd.setCursor(0,0);
      lcd.print("ESPACIO DE RESPUESTAS PARA ");
      lcd.setCursor(0,1);
      lcd.print("PREGUNTA # ");
      lcd.setCursor(11,1);
      lcd.print(intIndexPreguntas + 1);
      lcd.setCursor(13,1);
      lcd.print("-> MODO ELECCION");
    }
  } else {
    if (!modoRevision){
      modoRevision = true;
      lcd.clear();
    }
    lcd.setCursor(0,0);
    lcd.print("MODO REVISION -> LA RESPUESTA:");
    lcd.setCursor(0,1);
    if (preguntas[intIndexPreguntas].respuestaElegida == 0){
      lcd.print("(7_7) - AUN NO SE ELIGE - (-_-)");
    } else if (preguntas[intIndexPreguntas].respuestaElegida == preguntas[intIndexPreguntas].respuestaCorrecta){
      lcd.print("=D - ES CORRECTA - :D");
    } else {
      lcd.print("X - ES INCORRECTA - X");
    }
  }
}
