/*
  Maquina de Turing
  Lucas Prado
*/

#include <LiquidCrystal.h> //Inclui a biblioteca
#include <string.h>

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;//Pinos para ligar o display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);//Define os pinos que serão usados para ligar o display
int contador = 0; //Travar o reset
int tamanho = 8;
char palavra[8];
char copia[8];
int posicao_in =0;
int estado = 1;
int pino = 0;// cabecote


void setup() {
  lcd.begin(16, 2);//Define o número de colunas e linhas do display
  lcd.setCursor(0, 0);//Define o cursor para a coluna 0, linha 0
  lcd.print("MAQUINA TURING");
  lcd.setCursor(0, 1);//Define o cursor para a coluna 0, linha 1
  lcd.print("INSERIR 1 + = .");
  Serial.begin(9600);
}

//Função turing
void turing(){
  strcpy(copia, palavra);
  lcd.setCursor(0, 0);//Define o cursor para a coluna 0, linha 0
  lcd.write("-");
  lcd.setCursor(0, 1);
  lcd.print(palavra);
  delay(2000);
  while(true){
    if(palavra[pino] == '1' && estado == 1){
      pino++;
      lcd.clear();
      lcd.setCursor(pino, 0);
      lcd.write("-");
      lcd.setCursor(0, 1);
      lcd.print(palavra);
      delay(2000);
    }else if(palavra[pino] == '+' && estado == 1){
      palavra[pino] = '1';
      pino++;
      lcd.clear();
      lcd.setCursor(pino, 0);
      lcd.write("-");
      lcd.setCursor(0, 1);
      lcd.print(palavra);
      estado = 2;
      delay(2000);
    }else if(palavra[pino] == '+' && estado == 2){
      lcd.setCursor(0 , 0);
      lcd.print(copia);
      lcd.setCursor(0, 1);//Define o cursor para a coluna 0, linha 0
      lcd.print("REJEITA :(");
      return;
    }else if(palavra[pino] == '1' && estado == 2){
      pino++;
      lcd.clear();
      lcd.setCursor(pino, 0);
      lcd.write("-");
      lcd.setCursor(0, 1);
      lcd.print(palavra);
      delay(2000);
    }else if(palavra[pino] == '=' && estado == 2){
      palavra[pino] = '.';
      pino++;
      lcd.clear();
      lcd.setCursor(pino, 0);
      lcd.write("-");
      lcd.setCursor(0, 1);
      lcd.print(palavra);
      estado = 3;
      delay(2000);
    }else if(palavra[pino] != '\0' && estado == 3){
      lcd.setCursor(0 , 0);
      lcd.print(copia);
      lcd.setCursor(0, 1);//Define o cursor para a coluna 0, linha 0
      lcd.print("REJEITA :(");
      return;
    }else if(palavra[pino] == '\0' && estado == 3){
      pino--;
      lcd.clear();
      lcd.setCursor(pino, 0);
      lcd.write("-");
      lcd.setCursor(0, 1);
      lcd.print(palavra);
      estado = 4;
      delay(2000);
    }else if(estado == 4){
      lcd.setCursor(0 , 0);
      lcd.print(copia);
      lcd.setCursor(0, 1);//Define o cursor para a coluna 0, linha 0
      lcd.print("ACEITA :)");
    }else{
      pino++;
      lcd.clear();
      lcd.setCursor(pino, 0);
      lcd.write("-");
      lcd.setCursor(0, 1);
      lcd.print(palavra);
      delay(2000);
    }
  }
  return;
}


void loop() {
  delay(250);

  if(((analogRead(0)) < 800 && (analogRead(0)) > 700) && posicao_in < tamanho){
    palavra[posicao_in] = '1';
    lcd.clear();
    lcd.setCursor(0, 0);//Define o cursor para a coluna 0, linha 0
    lcd.print(palavra);
    posicao_in++;
  }

  if(((analogRead(0)) < 600 && (analogRead(0)) > 400) && posicao_in < tamanho){
    palavra[posicao_in] = '+';
    lcd.clear();
    lcd.setCursor(0, 0);//Define o cursor para a coluna 0, linha 0
    lcd.print(palavra);
    posicao_in++;
  }

  if(((analogRead(0)) < 400 && (analogRead(0)) > 200) && posicao_in < tamanho){
    palavra[posicao_in] = '=';
    lcd.clear();
    lcd.setCursor(0, 0);//Define o cursor para a coluna 0, linha 0
    lcd.print(palavra);
    posicao_in++;
  }

  if(((analogRead(0)) < 80) && posicao_in < tamanho){
    lcd.clear();
    delay(2000);
    lcd.setCursor(0, 1);//Define o cursor para a coluna 0, linha 1
    lcd.print(palavra);
    palavra[posicao_in]='\0';
    turing();
  }
}