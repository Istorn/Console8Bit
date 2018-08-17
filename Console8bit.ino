/*
  8-Bit Console 2018 Lorenzo Neri - Istorn
  

*/


#include "LedControl.h"



LedControl lc=LedControl(12,11,10,1);

byte smile[8]={B00100000,B01000000,B10000110,B10000110,B10000000,B10000110,B01000110,B00100000};
byte sad[8]={B10000000,B01000000,B00100110,B00100110,B00100000,B00100110,B01000110,B10000000};
byte one[7]={B01000000,B11000000,B01000000,B01000000,B01000000,B01000000,B11100000};
byte two[7]={B11100000,B00100000,B00100000,B11100000,B10000000,B10000000,B11100000};
byte three[7]={B11100000,B00100000,B00100000,B11100000,B10000000,B10000000,B11100000};
byte four[7]={B10100000,B11100000,B00100000,B00100000,B00100000,B00100000,B00100000};
byte five[7]={B11100000,B10000000,B10000000,B11100000,B00100000,B00100000,B11100000};
byte six[7]={B11100000,B10000000,B10000000,B11100000,B10 100000,B10100000,B11100000};
byte seven[7]={B11100000,B00100000,B00100000,B00100000,B00100000,B00100000,B00100000};
byte eight[7]={B11100000,B10100000,B10100000,B11100000,B10100000,B10100000,B11100000};
byte nine[7]={B11100000,B10100000,B10100000,B11100000,B00100000,B00100000,B11100000};
byte zero[7]={B11100000,B10100000,B10100000,B10100000,B10100000,B10100000,B11100000};



int proiettileX=0,proiettileY=0,leftPlayer=0,leftMonsterY=0,leftMonsterX=0,score=0;
int waiter=0;
bool shoot=false;


void setup() {
  Serial.begin(9600);
lc.shutdown(0,false);
 pinMode(4,INPUT);
 pinMode(5,INPUT);
 pinMode(6,INPUT);
 pinMode(7,INPUT);
 lc.shutdown(0,false);
 lc.setIntensity(0,5);
 lc.clearDisplay(0);
 //Mostriamo la faccia sorridente
 for (int i=0;i<8;i++){
  lc.setRow(0,i,smile[i]);
   delay(50);
 }
 delay(1500);
 lc.clearDisplay(0);
 
 leftPlayer=2;
 //Posizioniamo il giocatore
 lc.setColumn(0,0,B00000111<<(leftPlayer+1));
 //Creiamo un mostro casualmente
 leftMonsterX=7;
     leftMonsterY=random(1,8);
 
  lc.setLed(0,leftMonsterY,leftMonsterX,true);
  lc.setLed(0,leftMonsterY,leftMonsterX-1,true);
  lc.setLed(0,leftMonsterY-1,leftMonsterX,true);
  lc.setLed(0,leftMonsterY-1,leftMonsterX-1,true);
  Serial.println(leftMonsterY);
  Serial.println(leftMonsterX);
}

void loop() {
  if (leftMonsterX<=1){
    //Morto
    lc.clearDisplay(0);
    delay(200);
    //Faccia triste
    for (int i=0;i<8;i++){
      lc.setRow(0,i,sad[i]);
       delay(50);
     }
     delay(1000);
     
     delay(1500);
     lc.clearDisplay(0);
     //Mostriamo punteggio
     Serial.println(score);
     printScore(score);
     delay(3000);
     
     lc.clearDisplay(0);
      //Faccia felice
        for (int i=0;i<8;i++){
      lc.setRow(0,i,smile[i]);
       delay(50);
     }
     score=0;
     
     //Refresh del gioco
     lc.clearDisplay(0);
     leftPlayer=2;
     leftMonsterX=7;
     leftMonsterY=random(1,8);
      lc.setLed(0,leftMonsterY,leftMonsterX,true);
      lc.setLed(0,leftMonsterY,leftMonsterX-1,true);
      lc.setLed(0,leftMonsterY-1,leftMonsterX,true);
      lc.setLed(0,leftMonsterY-1,leftMonsterX-1,true);
     lc.setColumn(0,0,B00000111<<(leftPlayer+1));
      
        Serial.println("Morte");
        
        delay(1500);
  }else{
    //Siamo in gioco
    
      
        if ((proiettileY==leftMonsterX-1) && ((proiettileX==leftMonsterY) || (proiettileX==leftMonsterY-1))){
          //Il proiettile ha colpito il mostro
          cleanScreen();
          delay(50);
          score++;
          //Creiamo un nuovo alieno
          leftMonsterX=7;
          
          leftMonsterY=random(1,8);
          
          lc.setLed(0,proiettileX,proiettileY,false);
          proiettileY=1;
          proiettileX=leftPlayer+1;  
          
          shoot=false;
          lc.setLed(0,leftMonsterY,leftMonsterX,true);
          lc.setLed(0,leftMonsterY,leftMonsterX-1,true);
          lc.setLed(0,leftMonsterY-1,leftMonsterX,true);
          lc.setLed(0,leftMonsterY-1,leftMonsterX-1,true);
          Serial.println("Preso");
          
      
      
    }else{
      //Controlliamo se ha premuto tasti movimento
      if (digitalRead(4)==HIGH){
          //Movimento a destra
          if (leftPlayer<6){
            leftPlayer++;
            lc.setColumn(0,0,B00000000);
            lc.setLed(0,leftPlayer,0,true);
            lc.setLed(0,leftPlayer+1,0,true);
            lc.setLed(0,leftPlayer+2,0,true);
            Serial.println(leftPlayer);
          }
      }
      else if (digitalRead(5)==HIGH){
        //Movimento a sinistra
        if (leftPlayer>0){
            leftPlayer--;
            lc.setColumn(0,0,B00000000);
            lc.setLed(0,leftPlayer,0,true);
            lc.setLed(0,leftPlayer+1,0,true);
            lc.setLed(0,leftPlayer+2,0,true);
            Serial.println(leftPlayer);
          }
      }
      else if (digitalRead(6)==HIGH){
        //Sparo
        if (!(shoot)){
          proiettileY=1;
          proiettileX=leftPlayer+1;  
          shoot=true;
          lc.setLed(0,proiettileX,proiettileY,true);
        }
        
      }
      else{
        //Routine di controllo generica
        if (shoot){
          if (proiettileY>=6){
              
              //Distruggiamo il proiettile
              lc.setLed(0,proiettileX,proiettileY,false);
              proiettileY=1;
              proiettileX=leftPlayer+1;  
          
              shoot=false;
            }
            else{
              //Spostiamo il proiettile
              lc.setLed(0,proiettileX,proiettileY,false);
              proiettileY++;
              lc.setLed(0,proiettileX,proiettileY,true);
              Serial.println("MoProiettile moto");
              Serial.println(proiettileX);
              Serial.println(proiettileY);
            }
        }
        
       
      }
    }
     if (waiter==5){
          waiter=0;
        }
        waiter++;
        delay(150);
        
    if (score<5){
      if (waiter%4==0){
        moveAlien();  
      }
      
    }
    else if (score<10){
      if (waiter%3==0){
        moveAlien();  
      }
    }
    else if (score<20){
      if (waiter%2==0){
        moveAlien();  
      }
    }
    else if (score<45){
      moveAlien(); 
    }
    //In base al punteggio, la velocità di movimento del mostro è più lenta o più bassa
    
    
  }

}



//Pulisce schermo da proiettili e mostri
void cleanScreen(){
  lc.clearDisplay(0);
  lc.setLed(0,leftPlayer,0,true);
            lc.setLed(0,leftPlayer+1,0,true);
            lc.setLed(0,leftPlayer+2,0,true);
}



//Muove il mostro
void moveAlien(){
  
  lc.setLed(0,leftMonsterY,leftMonsterX,false);
  lc.setLed(0,leftMonsterY-1,leftMonsterX,false);
  leftMonsterX--;
  lc.setLed(0,leftMonsterY,leftMonsterX-1,true);
  lc.setLed(0,leftMonsterY-1,leftMonsterX-1,true);
  
  
  
}


//Stampa del punteggio
void printScore(int punteggio){
  switch (punteggio){
      case 1:
        for (int i=0;i<7;i++){
          lc.setColumn(0,i,one[i]);
        };break;


        case 2:
        for (int i=0;i<7;i++){
          lc.setColumn(0,i,two[i]);
        };break;

        case 3:
        for (int i=0;i<7;i++){
          lc.setColumn(0,i,three[i]);
        };break;
        case 4:
        for (int i=0;i<7;i++){
          lc.setColumn(0,i,four[i]);
        };break;
        case 5:
        for (int i=0;i<7;i++){
          lc.setColumn(0,i,five[i]);
        };break;
        case 6:
        for (int i=0;i<7;i++){
          lc.setColumn(0,i,six[i]);
        };break;
        case 7:
        for (int i=0;i<7;i++){
          lc.setColumn(0,i,seven[i]);
        };break;
        case 8:
        for (int i=0;i<7;i++){
          lc.setColumn(0,i,eight[i]);
        };break;
        case 9:
        for (int i=0;i<7;i++){
          lc.setColumn(0,i,nine[i]);
        };break;
     }
}





