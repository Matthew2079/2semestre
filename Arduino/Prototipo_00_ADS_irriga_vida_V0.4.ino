/* Irriga Vida - Projeto Integrador 2º Semestre ADS - Irrigador Automático*/

#include <LiquidCrystal.h> //INCLUSÃO DE BIBLIOTECA DO DISPLAY LCD 16x2

// LiquidCrystal(RS, E, D4, D5, D6, D7) - Declaração do Pinos do Display
LiquidCrystal lcd(9, 8, 4, 5, 6, 7); 

#include <Keypad.h> //INCLUSÃO DE BIBLIOTECA DO TECLADO MATRICIAL 4X4

const byte qtdLinhas = 4; //QUANTIDADE DE LINHAS DO TECLADO.
const byte qtdColunas = 4; //QUANTIDADE DE COLUNAS DO TECLADO.

/*//CONSTRUÇÃO DA MATRIZ DE CARACTERES
char matriz_teclas[qtdLinhas][qtdColunas] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};*/

//CONSTRUÇÃO DA MATRIZ DE CARACTERES
char matriz_teclas[qtdLinhas][qtdColunas]{
  {1,  2, 3,  12},
  {4,  5, 6,  13},
  {7,  8, 9,  14},
  {10, 16, 11, 15}
}; // Definição Matricial dos Botões do Teclado 4x4.

byte PinosqtdLinhas[qtdLinhas] = {22, 23, 24, 25}; //PINOS UTILIZADOS PELAS LINHAS.
byte PinosqtdColunas[qtdColunas] = {26, 27, 28, 29}; //PINOS UTILIZADOS PELAS COLUNAS.

//INICIALIZAÇÃO DO TECLADO
Keypad keyboard = Keypad( makeKeymap(matriz_teclas), PinosqtdLinhas, PinosqtdColunas, qtdLinhas, qtdColunas);
//Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// Varaivéis de processamento
int keypress; // Variável que armazena teclas digitadas ou lidas.
int ValAnalogIn; // Variável que armazena o valor do sensor.
String umidade; // Variável que armazena o status do sistema.

// Variavéis de Controle
int umidadebaixa=0; // Variável que armazena a contagem de quantas vezes esteve abaixo do valor esperado.
int umidadealta=0; // Variável que armazena a contagem de quantas vezes esteve alta.

// Variavéis para o Excel
int linha = 0; // Variável que se refere as linhas do excel.
int LABEL = 1; // Rótulo das colunas no Execel.

//Definição dos pinos do Projeto
#define pinoAnalog A0 // Define o pino A0 como "pinoAnalog" - SENSOR DE UMIDADE.
//#define pino5V 10 // Define o pino 7 como "pino5V" - ALIMENTAÇÃO SENSOR.
#define pinoRele 12 // Define o pino 8 como "pinoRele" - PINO DE ENTRADA DE SINAL MÓDULO RELE.
#define pinoBuzzer 13 // Define o pino 11 como BUZZER - EFEITO SONORO.

//Ciclo de Inicialização
void setup() { //Início do Setup.
  // put your setup code here, to run once:
 Serial.begin(9600); // Begin the Serial at 9600 Baud.
 lcd.begin(16,2); // Inicializa o display LCD.
 pinMode(pinoRele, OUTPUT); // Define a porta motor como saída.

 lcd.setCursor(1, 0); // Seta cursor no display coluna 1, linha 0.
 lcd.print("Efeito Sonoro?"); // Printa texto.
 lcd.setCursor(0, 1); // Seta cursor no display coluna 0, linha 1.
 lcd.print("*Sim        #Nao"); // Printa texto.
 
    keypress=99;  // Atribui a variável key um valor fixo. 
     while (keypress<10 || keypress>11) // Enquanto selecionada Tecla # ou * for menor que as condições key=99, executa as linhas do mesmo.
         {
             keypress = keyboard.getKey(); //Armazena o novo valor de key para testar as próximas condições.
             Serial.println(keypress); // Printa texto no monitor serial.
             delay (1000); // Espera 1s ou 1000 milisegundos.
          } 
         
              switch (keypress)
                   { // SWITCH keypress
                    
                      case 10:         
                             pinMode(pinoBuzzer, OUTPUT); // Define a porta buzzer como saída.
                             lcd.clear(); // Apaga o contéudo do display.
                             lcd.setCursor(2, 0); // Seta cursor no display coluna 0, linha 1.
                             lcd.print("Efeito Sonoro"); // Printa texto.
                             lcd.setCursor(3, 1); // Seta cursor no display coluna 3, linha 1.
                             lcd.print("Habilitado"); // Printa texto.
                             delay(3000); // Espera 3s ou 3000 milisegundos.
                      break;

                      default:
                             lcd.clear(); // Apaga o contéudo do display.
                             lcd.setCursor(2, 0); // Seta cursor no display coluna 0, linha 1.
                             lcd.print("Efeito Sonoro"); // Printa texto.
                             lcd.setCursor(2, 1); // Seta cursor no display coluna 2, linha 1.
                             lcd.print("Desabilitado"); // Printa texto.
                             delay(3000); // Espera 3s ou 3000 milisegundos.
                    }
 
 // Comunicação com Excel
 Serial.println("CLEARDATA"); // Reset da comunicação serial.
 Serial.println("LABEL,Hora,Porcento,Umidade"); // Nomeia as colunas.

 lcd.clear(); // Apaga o contéudo do display.
 lcd.setCursor(5, 0); // Seta cursor no display coluna 5, linha 0.
 lcd.print(" Fatec "); // Printa texto.
 lcd.setCursor(2, 1); // Seta cursor no display coluna 2, linha 1.
 lcd.print(" 18/06/2021 "); // Printa texto.
 delay(2000); // Espera 2000ms ou 2s.
 lcd.setCursor(2, 1); // Seta cursor no display coluna 2, linha 1.
 lcd.print(" Irriga Vida "); // Printa texto.
 delay(1000); // Espera 1000ms ou 1s.
} // Término do Setup.

//Ciclo Principal
void loop() { // If loop principal
  // put your main code here, to run repeatedly:
  
 keypress = keyboard.getKey(); //Armazena o novo valor de key para testar as próximas condições.
 //key = keypad.getKey();
 
 /*if (keypress)
 { //SE ALGUMA TECLA FOR PRESSIONADA, FAZ
    Serial.print("Tecla pressionada : "); //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.println(keypress); //IMPRIME NO MONITOR SERIAL A TECLA PRESSIONADA
  }

}*/
        ValAnalogIn = analogRead(pinoAnalog); // Função de leitura do Pino Analógico e armazena em uma variável.
        int Porcento = map(ValAnalogIn, 1023, 0, 0, 100); // Relaciona o valor analógico à porcentagem.
        linha++; // Incrementador de linhas no excel.

        Serial.print("DATA,TIME,"); // Inicia a impressão de dados, sempre iniciando...
        Serial.print(Porcento); // Imprime o valor em Porcento no monitor Serial.
        Serial.print(","); // Separador de informações no excel.
        //Serial.print(umidade);
        //Serial.println("%"); // Imprime o símbolo junto ao valor encontrado.
        //Serial.println(linha); // Printa na linha atual do incremento.

        if (linha>100) // Laço para limitar a quantidade de dados.
        {
          linha=0; // Reseta contador de linhas.
          Serial.println("ROW,SET,2"); // Alimentação das linhas com os dados sempre iniciando...
        }
          delay(2000); // Espera 2000ms ou 2s - Tempo para próxima leitura e lançamento na planilha.
        
          if (Porcento <= 65) // Se a porcentagem for menor ou igual à
            { // if porcento
              //Serial.println("Irrigando..."); // Imprime a frase no monitor serial.
              umidade="Baixo"; // Armazena o status da umidade.
              Serial.println(umidade); // Printa o estado de umidade BAIXO.
              umidadebaixa=umidadebaixa+1; // Contador de leituras no estado BAIXO.
              //Serial.println(umidadebaixa); // Printa o contador de umidade baixa.
              digitalWrite(pinoRele, HIGH); // Altera o estado do pinoRele para nível Alto.
              digitalWrite(pinoBuzzer, HIGH); // Altera o estado do pinoBuzzer para acionado.
              delay (2000); // Espera 2000ms ou 2s
              lcd.clear(); // Apaga o contéudo do display.
              lcd.setCursor(6, 1); // Seta cursor no display coluna 6, linha 1.
              lcd.print(Porcento); // Printa o conteúdo em percentual.
              lcd.print("%"); // Printa o símobolo.
              lcd.setCursor(0, 0); // Seta cursor no display coluna 0, linha 0.
              lcd.print("....Irrigando..."); // Printa texto.
            } // if porcento
 
          else // Se não ...
            { // else porcento
               //Serial.println("Planta Irrigada ..."); // Imprime a frase no monitor serial.
               umidade="Alto"; // Armazena o status da umidade.
               Serial.println(umidade); // Printa o estado de umidade ALTO.
               umidadealta=umidadealta+1; // Contador de leituras no estado ALTO.
               //Serial.println(umidadealta); // Printa o contador de umidade Alta.
               digitalWrite(pinoRele, LOW); // Altera o estado do pinoRele para nível baixo.
               digitalWrite(pinoBuzzer, LOW); // Altera o estado do pinoBuzzer para desacionado.
               delay (2000); // Espera 2000ms ou 2s.
               lcd.clear(); // Apaga o contéudo do display.
               lcd.setCursor(6, 1); // Seta cursor no display coluna 6, linha 1.
               lcd.print(Porcento); // Printa o conteúdo em percentual.
               lcd.print("%"); // Printa o símobolo.
               lcd.setCursor(1, 0); // Seta cursor no display coluna 1, linha 0.
               lcd.print("Planta Irrigada"); // Printa texto.
            } // else porcento
    
            //delay (1000); // Estabelece o tempo de 1s para reinicializar a leitura*/

          // Tela de Status umidade no período.
          if (keypress==12)
             {
                Serial.print("Tecla pressionada : "); // Imprime o texto no monitor serial.
                Serial.println(keypress); //Imprime no monitor serial a tecla pressionada.

                lcd.clear(); // Apaga o contéudo do display.
                lcd.setCursor(3, 0); // Seta cursor no display coluna 3, linha 0.
                lcd.print("Relatorio"); // Printa texto.
                lcd.setCursor(0, 1); // Seta cursor no display coluna 0, linha 1.
                lcd.print("de Nivel Umidade"); // Printa texto.
                delay(3000); // Espera 3000ms ou 3s.
                lcd.clear(); // Apaga o contéudo do display.
                lcd.setCursor(0, 0); // Seta cursor no display coluna 0, linha 0.
                lcd.print("Umid. Baixa:"); // Printa texto.
                lcd.setCursor(13, 0); // Seta cursor no display coluna 0, linha 0.
                lcd.print(umidadebaixa); // Printa texto.
                lcd.setCursor(0, 1); // Seta cursor no display coluna 0, linha 0.
                lcd.print("Umid. Alta:"); // Printa texto.
                lcd.setCursor(13, 1); // Seta cursor no display coluna 0, linha 0.
                lcd.print(umidadealta); // Printa texto.
                delay(3000); // Espera 3000ms ou 3s.
             }

          // Tela Manutenção.
          if (keypress==16)
            { // If keypress Manutenção.

              Serial.print("Tecla pressionada : "); // Imprime o texto no monitor serial.
              Serial.println(keypress); //Imprime no monitor serial a tecla pressionada.
              
              digitalWrite(pinoRele, LOW); // Altera o estado do pinoRele para nível baixo.
              digitalWrite(pinoBuzzer, LOW); // Altera o estado do pinoBuzzer para desacionado.
               
              lcd.clear(); // Apaga o contéudo do display.
              lcd.setCursor(3, 0); // Seta cursor no display coluna 3, linha 0.
              lcd.print("Manutencao"); // Printa texto.
              delay(3000);  // Espera 3000ms ou 3s.
              lcd.setCursor(3, 0); // Seta cursor no display coluna 3, linha 0.
              lcd.print("1-Dosadora"); // Printa texto.
              //delay(2000);
              lcd.setCursor(3, 1); // Seta cursor no display coluna 3, linha 1.
              lcd.print("2-Buzzer  "); // Printa texto.
              //delay (2000);
              
              keypress=99;  // Atribui a variável key um valor fixo. 
              while (keypress<1 || keypress>2) // Enquanto selecionada Tecla 1 ou 2 for menor que as condições key=99, executa as linhas do mesmo.
                 {
                   keypress = keyboard.getKey(); //Armazena o novo valor de key para testar as próximas condições.
                   Serial.println(keypress); // Printa texto no monitor serial.
                   delay (1000); // Espera 1s ou 1000 milisegundos.
                 } 
         
              switch (keypress)
                   { // SWITCH keypress Manutenção.
                    
                      case 1:         
                           lcd.clear(); // Apaga o contéudo do display.
                           lcd.setCursor(0, 0); // Seta cursor no display coluna 0, linha 0.
                           lcd.print("Testando........"); // Printa texto.
                           lcd.setCursor(0, 1); // Seta cursor no display coluna 0, linha 1.
                           lcd.print("Dosadora........"); // Printa texto.
                           delay(2000); // Espera 2000ms ou 2s.
                           digitalWrite(pinoRele,HIGH); // Altera o estado do pinoRele para nível Alto.
                           lcd.setCursor(0, 1); // Seta cursor no display coluna 0, linha 1.
                           lcd.print("....Aguarde....."); // Printa texto.
                           delay (5000); // Espera 5000ms ou 5s.
                           digitalWrite(pinoRele,LOW); // Altera o estado do pinoRele para nível baixo.
                      break;

                      case 2:         
                           lcd.clear(); // Apaga o contéudo do display.
                           lcd.setCursor(0, 0); // Seta cursor no display coluna 0, linha 0.
                           lcd.print("Testando........"); // Printa texto.
                           lcd.setCursor(0, 1); // Seta cursor no display coluna 0, linha 1.
                           lcd.print("Buzzer.........."); // Printa texto.
                           delay(2000); // Espera 2000ms ou 2s.
                           digitalWrite(pinoBuzzer,HIGH); // Altera o estado do pinoBuzzer para acionado.
                           lcd.setCursor(0, 1); // Seta cursor no display coluna 0, linha 1.
                           lcd.print("....Aguarde....."); // Printa texto. 
                           delay (5000); // Espera 5000ms ou 5s.
                           digitalWrite(pinoBuzzer,LOW); // Altera o estado do pinoBuzzer para desacionado.
                      break;
         
                      defalut:
                      Serial.println(keypress); // Imprime a telca pressionada no serial monitor.
                   } // SWITCH keypress Manutenção.
            } // If keypress Manutenção.
            
} // If loop principal Término

/*------------------ MATERIAL DE APOIO ------------------

  if (tecla_pressionada){ //SE ALGUMA TECLA FOR PRESSIONADA, FAZ
    Serial.print("Tecla pressionada : "); //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.println(tecla_pressionada); //IMPRIME NO MONITOR SERIAL A TECLA PRESSIONADA
  }

  #define pot 0 // define A0 = pot entrada analógica 0 para receber leitura do sensor
  
  int motor=2; // nomeia a porta 2 para o motor.
  int buzzer=3; // nomeia a porta 3 para o buzzer.
  pinMode(motor, OUTPUT); // define a porta motor como saída
  pinMode(buzzer, OUTPUT); // define a porta buzzer como saída
*/

/*for (int x = 0; x < 25; x++) 
   {
     lcd.scrollDisplayLeft(); 
     delay(200);
   }*/

// Tabela ASCII 

//DEC 48 Char 0
//DEC 49 Char 1
//DEC 50 Char 2
//DEC 51 Char 3
//DEC 52 Char 4
//DEC 53 Char 5
//DEC 54 Char 6
//DEC 55 Char 7
//DEC 56 Char 8
//DEC 57 Char 9
//DEC 65 Char A
//DEC 66 Char B
//DEC 67 Char C
//DEC 68 Char D
//DEC 42 Char *
//DEC 35 Char #

//Significado de comandos Usuais:
//lcd.clear(); - Utilizado para apagar informações no visor.
//lcd.setCursor(0,0); - Utilizado para indicar qual linha e coluna se inicia escrita de informações (Coluna,Linha).
//lcd.print(" ----- "); - Utilizado para imprimir no visor o que esta dentro das aspas.
//delay(2500); - Utilizado para estabelecer um tempo de espera base em milisegundos ex: para 2,5 ssegundos se coloca em parenteses 2500, pois 2500x10e-3= 2,5s.
