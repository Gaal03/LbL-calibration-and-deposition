#include <String.h>

int x;
int n = 140; // número de bicamadas

const int b_up = 6;       //botao subida
const int b_down = 5;     //botao descida
const int b_rig = 9;     //botão girar direita
const int b_lef = 8;      //botão girar esquerda
const int button = 7;    //botao rotina

int up = 0;               //controla a ativacao do botao subida
int down = 0;             //controla a ativacao do botao descida
int right = 0;            //controla ativação botão girar direita
int left = 0;             //controla ativação botão girar esquerda
int val = 0;              //controla a ativacao do botao rotina

int v1 = 10;              //  velocidade de subida em mm/min
int v2 = 60;              //   velocidade de descida em mm/min

int vx = 5;

int angulo = 81;          //esses dois têm que ser iguais aqui (é o ângulo real)

float d1 = 56;            // deslocamento vertical em mm 

long tempo_imerso = 480000;   // tempo de imersao da rotina
long tempo_emerso = 2000;   // tempo de emersao da rotina
long tempo_lavagem = 2000;  // tempo de lavagem da rotina

long passos = 1600;          // # passos por volta 

    //CUIDADO! O # de voltas deve ser sempre inteiro.
float voltas1 = (d1/0.8);    // # voltas para deslocamento d1
float voltas2 = 1;           // para o giro

double t1 = (24E6)/(v1*passos);  // controla a velocidade de subida
double t2 = (24E6)/(v2*passos);  // controla a velocidade de descida


double t_x = (24E6)/(vx*passos);  // velocidade para girar

void setup(){
  Serial.begin(9600);
  pinMode(13,OUTPUT); // enable motor de cima
  pinMode(12,OUTPUT); //step motor de cima
  pinMode(11,OUTPUT); //dir motor de cima
  pinMode(2,OUTPUT);  //enable motor de baixo
  pinMode(3,OUTPUT);  //step motor de baixo
  pinMode(4,OUTPUT);  // dir motor de baixo
  pinMode(5,INPUT);   //botao descida
  pinMode(6,INPUT);   // botao subida 
  pinMode(7,OUTPUT);  // botao rotina
  digitalWrite(13,HIGH);        //Desliga o motor do carro
  digitalWrite(2,HIGH);}      //Desliga o motor do bracinho

void loop(){}


void serialEvent() {
      int function = Serial.parseInt();
      
      int v_up = Serial.parseInt();
      int v_down = Serial.parseInt();
      
      int length_z = Serial.parseInt();
      
      int t_i = Serial.parseInt();   // tempo de imersao da rotina
      int t_r = Serial.parseInt();  // tempo de lavagem da rotina
      
      int bicamadas = Serial.parseInt();  // número de bicamadas

      int vx = 60;
      double t_x = (24E6)/(vx*passos);  // velocidade para girar
      float voltas2 = 1;           // para o giro
      int angulo = 81;          //esses dois têm que ser iguais aqui (é o ângulo real)
      long passos = 1600;          // # passos por volta

      
      voltas1 = (length_z/0.8);
      int voltasx = 40;
      
      
      int t_up = (24E4)/(v_up*16);;
      int t_down = (24E4)/(v_down*16);;
      
      long tempo_imerso = (t_i*60000);   // tempo de imersao da rotina
      long tempo_lavagem = (t_r*1000);  // tempo de lavagem da rotina


        if (function==1){
          Up_function(t_up, voltas1);
          Serial.println("ok");    
        }
        
        if (function==2){
          Down_function(t_down, voltas1);
          Serial.println("ok");
        }


        if(function==3){
          right_function(t_x, voltasx);
          Serial.println("ok");
          }
          
        if(function==4){
          left_function(t_x, voltasx);
          Serial.println("ok");
        }
       if(function==5){
          Down_function(t_down, voltas1);
          delay(tempo_imerso);
          Up_function(t_up, voltas1);
          delay(1000);
          left_function(t_x, voltasx);
          delay(1000);
          Down_function(t_down, voltas1);
          delay(tempo_lavagem);
          Up_function(t_up, voltas1);
          delay(1000);
         
          Serial.println("ok");
        }
        
        if(function==6){
          left_function(t_x, voltasx);
          delay(1000);
          Down_function(t_down, voltas1);
          delay(tempo_imerso);
          Up_function(t_up, voltas1);
          delay(1000);
          left_function(t_x, voltasx);
          delay(1000);
          Down_function(t_down, voltas1);
          delay(tempo_lavagem);
          Up_function(t_up, voltas1);
          delay(1000);
          Serial.println("ok");
        }
        
        if(function==7){
          return_function(t_x, voltasx);
             
          Serial.println("ok");
        }

      if(function==10){
        for (int i  = 1; i <= bicamadas; i++){
          Down_function(t_down, voltas1);
          delay(tempo_imerso);
          Up_function(t_up, voltas1);
          delay(1000);
          left_function(t_x, voltasx);
          delay(1000);
          Down_function(t_down, voltas1);
          delay(tempo_lavagem);
          Up_function(t_up, voltas1);
          delay(1000);

          
          left_function(t_x, voltasx);
          delay(1000);
          Down_function(t_down, voltas1);
          delay(tempo_imerso);
          Up_function(t_up, voltas1);
          delay(1000);
          left_function(t_x, voltasx);
          delay(1000);
          Down_function(t_down, voltas1);
          delay(tempo_lavagem);
          Up_function(t_up, voltas1);
          delay(1000);
          return_function(t_x, voltasx);
            }
        }
}
  
  
void Up_function(int t_up, int voltas1){
         digitalWrite(2,LOW);  //Liga o motor do braço 
         for(int k=0;k<voltas1;k++){  
          digitalWrite(4,LOW);//SOBE COM LOW
            for(x=0;x<passos;x++){
            digitalWrite(3,HIGH);
            delayMicroseconds(t_up);
            digitalWrite(3,LOW);
            delayMicroseconds(t_up);
            }
          }
          digitalWrite(2,HIGH);  //Desliga o motor do braço
        }
        
void Down_function(int t_down, int voltas1){  
          digitalWrite(2,LOW);  //Liga o motor do braço
          for(int k=0;k<voltas1;k++){  
          digitalWrite(4,HIGH);//SOBE COM LOW
            for(x=0;x<passos;x++){
            digitalWrite(3,HIGH);
            delayMicroseconds(t_down);
            digitalWrite(3,LOW);
            delayMicroseconds(t_down);
            }
          }
          digitalWrite(2,HIGH);  //Desliga o motor do braço
        }
        
void right_function(int t_x, int voltasx){
          digitalWrite(13,LOW);        //Liga o motor do carro
          for(int k=0;k<voltasx;k++){  
          digitalWrite(11,HIGH);//SOBE COM LOW
            for(x=0;x<(passos);x++){
            digitalWrite(12,HIGH);
            delayMicroseconds(t_x);
            digitalWrite(12,LOW);
            delayMicroseconds(t_x);
            }
          }
          digitalWrite(13,HIGH);    //Desliga o motor do carro
        }
        
void left_function(int t_x, int voltasx){  
          digitalWrite(13,LOW);        //Liga o motor do carro
          for(int k=0;k<voltasx;k++){  
          digitalWrite(11,LOW);//SOBE COM LOW
            for(x=0;x<(passos);x++){
            digitalWrite(12,HIGH);
            delayMicroseconds(t_x);
            digitalWrite(12,LOW);
            delayMicroseconds(t_x);
            }
          }
          digitalWrite(13,HIGH);      // DEsliga o motor do carro
        }
        
void return_function(int t_x, int voltasx){  
          digitalWrite(13,LOW);        //Liga o motor do carro
          for(int k=0;k<(3*voltasx);k++){  
          digitalWrite(11,HIGH);//SOBE COM LOW
            for(x=0;x<(passos);x++){
            digitalWrite(12,HIGH);
            delayMicroseconds(t_x);
            digitalWrite(12,LOW);
            delayMicroseconds(t_x);
            }
          }
          digitalWrite(13,HIGH);    //Desliga o motor do carro
        }
