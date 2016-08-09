#include <AFMotor.h>
#include <Ultrasonic.h>

/*************** PORTAS MOTORES ***********************/
AF_DCMotor MFrontal(1); //Frontal M1
AF_DCMotor MAtras(2);   //Atras M2

AF_DCMotor MDireita(3); //Direito M3 
AF_DCMotor MEsquerda(4);//Esquerdo M4

/*************** FIM PORTAS MOTORES ***********************/

/*************** PORTAS SENSORES***********************/
const int trigCentral = A5; //Central Trig - cabo preto
const int echoCentral = A4; //Central Echo - cabo verde

const int trigEsquerda = A3; //Esquerdo Trig - cabo preto 
const int echoEsquerda = A2; //Esquerdo Echo - cabo verde

const int trigDireita = A1; //Direito Trig - cabo preto
const int echoDireita = A0; //Direito Echo - cabo verde

/*************** FIM PORTAS SENSORES***********************/

/*************** AVARIAVEIS DE DISTANCIA***********************/
int distanciaFrente;
int distanciaEsquerda;
int distanciaDireita;

/*************** PORTA LED***********************/
const int led = 2;

/*************** SETUP ***********************/
void setup()
{
    /*==== SERIAL ====*/
    Serial.begin(9600); 

    /*==== SENSORES SAIDA E ENTRADA ====*/
    //TRIG
    pinMode(trigCentral, OUTPUT);    
    pinMode(trigEsquerda, OUTPUT);   
    pinMode(trigDireita, OUTPUT);
    
    //ECHO
    pinMode(echoCentral, INPUT);
    pinMode(echoEsquerda, INPUT);
    pinMode(echoDireita, INPUT);
    /*==== FIM SENSORES SAIDA E ENTRADA ====*/

    /*==== VELOCIDADE MOTORES ====*/
    /* velocidade maxima = 255
     *  velocidade minima para rodar 100
     */
    MFrontal.setSpeed(170); //traseiro
    MAtras.setSpeed(150); //frontal
    
    MDireita.setSpeed(200); //Direito 
    MEsquerda.setSpeed(130); //Esquerdo 
    /*==== FIM VELOCIDADE MOTORES ====*/
    
    /*==== SAIDA LED ====*/
    pinMode(led,OUTPUT);
}
/*************** FIM SETUP ***********************/

/*************** FUNCTION SENSORES ***********************/
/*==== CENTRAL ====*/
int sensorCentral()
{
    digitalWrite(trigCentral, LOW);
    delayMicroseconds(2);
    digitalWrite(trigCentral, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigCentral, LOW);

    unsigned long duracaoFrente = pulseIn(echoCentral, HIGH);
    distanciaFrente = duracaoFrente/58;
  
    Serial.print("SensorFrente: ");
    Serial.println(distanciaFrente);

    return distanciaFrente;
}
/*==== FIM CENTRAL ====*/


/*==== ESQUERDO ====*/
int sensorEsquerdo()
{
    digitalWrite(trigEsquerda, LOW);
    delayMicroseconds(2);
    digitalWrite(trigEsquerda, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigEsquerda, LOW);

    unsigned long duracaoEsquerda = pulseIn(echoEsquerda, HIGH);
    distanciaEsquerda = duracaoEsquerda/58;
  
    Serial.print("------------SensorEsquerda: ");
    Serial.println(distanciaEsquerda);
  
    return distanciaEsquerda;
}
/*==== FIM ESQUERDO ====*/


/*==== DIREITO ====*/
int sensorDireito()
{
    digitalWrite(trigDireita, LOW);
    delayMicroseconds(2);
    digitalWrite(trigDireita, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigDireita, LOW);

    unsigned long duracaoDireita = pulseIn(echoDireita, HIGH);
    distanciaDireita = duracaoDireita/58;
 
    Serial.print("-------------------------------SensorDireita: ");
    Serial.println(distanciaDireita);
  
    return distanciaDireita;
}
/*==== FIM DIREITO ====*/
/*************** FIM FUNCTION SENSORES ***********************/



/*************** FUNCTION LED ***********************/
void Leds()
{
  //Acendendo os Leds para msotrar que ta ligado o robô
  digitalWrite(led,HIGH);  
}
/*************** FIM FUNCTION LED ***********************/




/*************** FUNCTION MOTORES ***********************/
/*==== ANDAR PARA A FRENTE ====*/
void andaFrente(){
MDireita.run(RELEASE);
MEsquerda.run(RELEASE);
MFrontal.run(RELEASE);
MAtras.run(RELEASE);
delay(150);
MDireita.run(BACKWARD);
MEsquerda.run(FORWARD);
}

/*========ANDA FRENTE CONTINUA======== */
void andaFrenteC(){
MDireita.run(BACKWARD);
MEsquerda.run(FORWARD);
}

/*==== ANDAR PARA A ESQUERDA ====*/
void andaEsquerda(){
MDireita.run(RELEASE);
MEsquerda.run(RELEASE);
MFrontal.run(RELEASE);
MAtras.run(RELEASE);
delay(150);
MFrontal.run(FORWARD);
MAtras.run(BACKWARD);
}

/* ===== ANDA ESQUERDA CONTINUA===== */
void andaEsquerdaC(){
MFrontal.run(FORWARD);
MAtras.run(BACKWARD);
}

/*==== ANDAR PARA A DIREITA ====*/
void andaDireita(){
MDireita.run(RELEASE);
MEsquerda.run(RELEASE);
MFrontal.run(RELEASE);
MAtras.run(RELEASE);
delay(150);
MFrontal.run(BACKWARD);
MAtras.run(FORWARD);
}

/*=====ANDAR DIREITA CONTINUA ====== */
void andaDireitaC(){
MFrontal.run(BACKWARD);
MAtras.run(FORWARD);
}
/*************** FIM FUNCTION MOTORES ***********************/





/*************** FUNCTION PRINCIPAL ***********************/
void loop()
{
  /*==LIGANDO LED==*/
  Leds();

  /*==VARIAVEIS SENSORES==*/
  int sc = sensorCentral();
  int se = sensorEsquerdo();
  int sd = sensorDireito();

    /*==EXECUTANDO SENSOR COM MOTOR==*/


    if (sc >= 30 && sc >= se && sc >= sd ){
      int c=0;
      do{
        if(c == 0){
          andaFrente();
          c=1;
        }else{
          andaFrenteC();
        }
        sc = sensorCentral();
      }while(sc >= 30);     
    }
    else if (se >= 30 && se >= sd){
        int c=0;
        do{
          if(c == 0){
            andaEsquerda();
            c=1;
          }else{
            andaEsquerdaC();
          }
          se = sensorEsquerdo();
        }while(se >= 30);               
    }
    else if(sd >= 30 ){
        int c=0;
        do{
          if(c==0){
            andaDireita();
            c=1;
          }else{
            andaDireitaC();
          }
          sd = sensorDireito();
       }while(sd >=30);
    }
}

/*************** FIM FUNCTION PRINCIPAL ***********************/




