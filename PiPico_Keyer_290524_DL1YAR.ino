// ============================================================================
//  neuer Versuch Morsetaste
//  DL1YAR  29052024
//  Codierung mit Merker ergänzt
//  Arduino IDE settings:
//  board: Raspberry Pi Pico (Arduino-Pico)
//  Schaltung PiPico KeyerEmil.pdf
//  TX und V.Band dazu programmiert keine BU-Erkennung und Woab  !!!!!
//  https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
//  programmer: none
//
// ============================================================================


//#define DL8JJ

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "Keyboard.h"


//Textende lang gestalten alle Texte sind Endlosschleifen !!
char txt1[] = "cqcqcq de dl1yar dl1yar cq de dl1yar pse k                                     ";
char txt2[] = "my name is winni winni qth is recklinghausen recklinghausen dok n18 n18        ";
char txt3[] = "tnx qso my qsl is sure via buero vy73 de dl1yar sk                             ";
char txt4[] = "test ";

//------Pinbelegung----------------------------

const int PKT      = 15  ;// GPIO15 Paddle
const int STR      = 14  ;// GPIO14 Paddle

const int M_Ton   =  16   ; // GPIO16 Mithörton Piezo
const int Cw_Tx   =  17   ; // GPIO15   Morsetaste zum TX

int SpeedPin =    A0  ; // // AD-Wandler eingang(Poti)

//--Betriebsart--------
const int Tx       = 13  ;// GPIO11   "richtiger" Tx
const int Speed    = 12  ;// GPIO12   Mode_A = Jumper
const int MtonOff  = 11  ;// GPIO13   PaddleReverse Jumper Mithörton aus 
const int V_Band   = 10  ;// GPIO12   V-Band Internett

//Texteauswahl
const int TXT1 = 5 ;//GPIO 5 für Text1
const int TXT2 = 4 ;//GPIO 4 für Text2
const int TXT3 = 3 ;//GPIO 3 für Text3
const int TXT4 = 2 ;//GPIO 5 für Text4
//---------------------------------


const int TooglePin = 21 ;  // zum Messen der Hauptschleife
bool looptoggle    = true;   // Merker Punkt 1= nicht gedrückt

//---------------------------------
int zeit = 0;           // für die Pausenzeit
int i,ii,txt_loop = 0;  // allgemeine Zähler
//---------------------------------

int8_t Merker = 0;
int PKT_m     = 0;   // Merker Punkt 1= nicht gedrückt
int STR_m     = 1;   // Merker Strich
int Zz_m      = 2;   // Merker für Zeichenzähler  4
int Wo_ab_m   = 3;   // Merker Wortabstand  8

 
int16_t Tempo = 888 ;
uint16_t Hz  = 850 ; // frequenz Mithörton                                   130524




int8_t Z_z   = 0 ;    //Zeichenzaehler
int8_t Cod   = 0;     //Codemuster
byte BuCoZ   = 0;    // zur schnelle Ausgabe 170524

//---------------------------------
void Bu_a(){
  ////Serial.print("Bu_a");;
 // neue Codierung 170524
        if ((Cod == 56) && (Z_z == 9 )){
            //Serial.print("  PiPico Keyer 290524 DL8JJ (C)DL1YAR");    //#pppsssppp
            Keyboard.print("  PiPico Kezer 290524 ");
            //  Keyboard.print("DL8JJ ");
            Keyboard.write(42);
            Keyboard.print("C");
            Keyboard.write(40);
             Keyboard.print("DL1ZAR  ");
        }
        else {
          BuCoZ = Z_z<<5;     //150524
          BuCoZ = BuCoZ |Cod; //150524
          switch (BuCoZ){
            case 66:
              Keyboard.print("A");break;
            case 129:
              Keyboard.print("B");break;
            case 133:
              Keyboard.print("C");break;
            case 97:
              Keyboard.print("D");break;
            case 32:
              Keyboard.print("E");break;
            case 132:
              Keyboard.print("F");break;
            case 99:
              Keyboard.print("G");break;
            case 128:
              Keyboard.print("H");break;
            case 64:
              Keyboard.print("I");break;
            case 142:
              Keyboard.print("J");break;
            case 101:
              Keyboard.print("K");break;
            case 130:
              Keyboard.print("L");break;
            case 67:
              Keyboard.print("M");break;
            case 65:
              Keyboard.print("N");break;
            case 103:
              Keyboard.print("O");break;
            case 134:
              Keyboard.print("P");break;
            case 139:
              Keyboard.print("Q");break;
            case 98:
              Keyboard.print("R");break;
            case 96:
              Keyboard.print("S");break;
            case 33:
              Keyboard.print("T");break;
            case 100:
              Keyboard.print("U");break;
            case 136:
              Keyboard.print("V");break;
            case 102:
              Keyboard.print("W");break;
            case 137:
              Keyboard.print("X");break;
            case 141:
              Keyboard.print("Z");break;
            case 131:
              Keyboard.print("Y");break;
            case 190:
              Keyboard.print("1");break;
             case 188:
              Keyboard.print("2");break;
            case 184:
              Keyboard.print("3");break;
            case 176:
              Keyboard.print("4");break;
            case 160:
              Keyboard.print("5");break;
            case 161:
              Keyboard.print("6");break;
            case 163:
              Keyboard.print("7");break;
            case 167:
              Keyboard.print("8");break;
            case 175:
              Keyboard.print("9");break;
             case 191:
              Keyboard.print("0");break;
             case 169:
              Keyboard.write(38);break;//("/")
            case 234:
              Keyboard.print(".");break;
            case 243:
              Keyboard.print(",");break;
            case 204:
              Keyboard.write('_');break;// ? Keyboardlayout
            case 213:
              Keyboard.print(";");break;
            case 245:
              Keyboard.print("!");break;
            case 173:
              Keyboard.write(42);break;// ( Keyboardlayout
            case 237:
              Keyboard.write(40);break;// ) Keyboardlayout
            case 199:
              Keyboard.print(":");break;// 
            case 227:
              Keyboard.print("=");break;// 
            break;
          }
        }

  //Serial.print(" ");;      //Zur Codeanzeige
  //Serial.print(Cod,BIN );  //Zur Codeanzeige
  //Serial.print(" ");;      //Zur Codeanzeige
  //Serial.print(Cod,DEC );  //Zur Codeanzeige
  //Serial.print(" ");;      //Zur Codeanzeige
  //Serial.println(Z_z,DEC );//Zur Codeanzeige
        Z_z = 0;
        Cod   = 0 ;//#Codemuster
       bitClear(Merker,Zz_m);  // zum schnelleren kodieren
        //--------------------------------290524-------
        zeit=(analogRead(SpeedPin));
         zeit = 1024-zeit;  //Poti drehrichtung umkehr
          ////Serial.print(zeit);//Serial.print(" Zeit");
          for(i= 0;i <= (zeit*3); i++){
             ////Serial.print("PAUSE");
              if (digitalRead(PKT) == LOW) {bitSet(Merker, PKT_m);i =(zeit*3)+1;}
              if (digitalRead(STR) == LOW) {bitSet(Merker, STR_m);i =(zeit*3)+1;}
              delayMicroseconds(Tempo);        // -----Tempo  ---------- 280524
        }
        //---------------------------------------
       if(Merker ==0) Keyboard.write(' ');
}

//---------------------------------
void Pause(){
  zeit=(analogRead(SpeedPin));
  zeit = 1024-zeit;  //Poti drehrichtung umkehr
  ////Serial.print(zeit);//Serial.print(" Zeit");
    for(i= 0;i <= zeit; i++){
      ////Serial.print("PAUSE");
      if (digitalRead(PKT) == LOW) bitSet(Merker, PKT_m);
      if (digitalRead(STR) == LOW) bitSet(Merker, STR_m);
      delayMicroseconds(Tempo);        // -----Tempo  ---------- 130524
        }
} 

//---------------------------------
void Strich(){
  ////Serial.print("Strich");
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on 
  if(digitalRead(Tx)== LOW){digitalWrite(Cw_Tx, HIGH);}          // Tx wird getastet                   090524
  if(digitalRead(V_Band)== LOW){Keyboard.press(KEY_LEFT_CTRL) ;} // V_Band press und halten LEFT_CTRL  090524
  if(digitalRead(MtonOff) == HIGH) {tone(M_Ton,Hz);} 
   tone(M_Ton,Hz);
      Pause(); Pause(); Pause();                                 // Strich
   noTone(M_Ton);                                                //Mithörton aus                       130524
  digitalWrite(Cw_Tx, LOW);                                      // Tx wird enttastet  HIHI            090524 
  if(digitalRead(V_Band)== LOW){Keyboard.releaseAll(); ;}        // V_Band alle Tasten lösen           090524 
  digitalWrite(LED_BUILTIN, LOW);                                // turn the LED off 
  Pause();
  Cod = Cod |(1 << Z_z);                                         //# Bit setzen
  Z_z =Z_z+1;  // Zeichenzähler
  bitSet(Merker,Zz_m);                                           // zum schnelleren kodieren
  bitClear(Merker,STR_m);
  bitClear(Merker,Wo_ab_m);                                        // immer letze Aktion
}
      
void Punkt(){
  ////Serial.print("Punkt");
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on 
  if(digitalRead(Tx)== LOW){digitalWrite(Cw_Tx, HIGH);}          // Tx wird getastet                   090524
  if(digitalRead(V_Band)== LOW){Keyboard.press(KEY_LEFT_CTRL) ;} // V_Band press und halten LEFT_CTRL  090524
  if(digitalRead(MtonOff) == HIGH) {tone(M_Ton,Hz);}  
    tone(M_Ton,Hz);
      Pause();                                                   // Punkt
     noTone(M_Ton);                                              //Mithörton aus                       130524
  digitalWrite(Cw_Tx, LOW);                                      // Tx wird enttastet  HIHI            090524 
  if(digitalRead(V_Band)== LOW){Keyboard.releaseAll(); ;}        // V_Band alle Tasten lösen           090524 
  digitalWrite(LED_BUILTIN, LOW);                                // turn the LED off #endif
  Pause();
  //  Cod = Cod & ~(1 << Z_z);                                     //#Bit loeschen  test 280524
  Z_z =Z_z+1;                                                    // Zeichenzähler
  bitSet(Merker,Zz_m);                                           // zum schnelleren kodieren
  bitClear(Merker,PKT_m);                                        // immer letze Aktion Punktmerker löschen
  bitClear(Merker,Wo_ab_m);
}

//-------------------------------------------------------------------------------------------------

void ausgabe(char* text){
  int i;
   txt_loop=0;
   do{
    for (i =0;i<=(strlen(text));i++){ 
      if (digitalRead(STR) == LOW) {i= strlen(text) ;txt_loop = 1;} //Textabbruch txt_loop = 1
      if (digitalRead(PKT) == LOW) {i= strlen(text) ;txt_loop = 1;} //Textabbruch txt_loop = 1
          switch(int(text[i])){
           case 32 :Pause();Pause();Pause();Pause();Pause();Pause();break;                       //Wortabstand(Space)
           case 40 :Strich();Punkt();Strich(),Strich();Punkt();Pause();Pause();break;         // (
           case 41 :Strich();Punkt();Strich(),Strich();Punkt();Strich();Pause();Pause();break;// )
           case 43 :Punkt();Strich();Punkt();Strich();Punkt();Pause();Pause();break;          // +
           case 44 :Strich();Strich();Punkt();Punkt();Strich();Strich();Pause();Pause();break;// ,  
           case 45 :Strich();Punkt();Punkt();Punkt();Strich();Pause();Pause();break;          // -
           case 46 :Punkt();Strich();Punkt();Strich();Punkt();Strich();Pause();Pause();break; // .
           case 47 :Strich();Punkt();Punkt();Strich();Punkt();Pause();Pause();break;          // /
           case 48 :Strich();Strich();Strich();Strich();Strich();Pause();Pause();break;       //0 
           case 49 :Punkt();Strich();Strich();Strich();Strich();Pause();Pause();break;        //1
           case 50 :Punkt();Punkt();Strich();Strich();Strich();Pause();Pause();break;         //2
           case 51 :Punkt();Punkt();Punkt();Strich();Strich();Pause();Pause();break;          //3
           case 52 :Punkt();Punkt();Punkt();Punkt();Strich();Pause();Pause();break;           //4
           case 53 :Punkt();Punkt();Punkt();Punkt();Punkt();Pause();Pause();break;            //5
           case 54 :Strich();Punkt();Punkt();Punkt();Punkt();Pause();Pause();break;           //6
           case 55 :Strich();Strich();Punkt();Punkt();Punkt();Pause();Pause();break;          //7
           case 56 :Strich();Strich();Strich();Punkt();Punkt();Pause();Pause();break;         //8
           case 57 :Strich();Strich();Strich();Strich();Punkt();Pause();Pause();break;        //9
     
           case 59 :Strich();Punkt();Strich();Punkt();Strich();Punkt();Pause();Pause();break; // ;
           case 61 :Strich();Punkt();Punkt();Punkt();Strich();Pause();Pause();break;          // =
           case 63 :Punkt();Punkt();Strich();Strich();Punkt();Punkt();Pause();Pause();break;  // ?
           
           case 97  :Punkt();Strich();Pause();Pause();break;                          //a 
           case 98  :Strich();Punkt();Punkt();Punkt();Pause();Pause();break;          //b 
           case 99  :Strich();Punkt();Strich();Punkt();Pause();Pause();break;         //c 
           case 100 :Strich();Punkt();Punkt();Pause();Pause();break;                  //d 
           case 101 :Punkt();Pause();Pause();break;                                   //e 
           case 102 :Punkt();Punkt();Strich();Punkt();Pause();Pause();break;          //f 
           case 103 :Strich();Strich();Punkt();Pause();Pause();break;                 //g
           case 104 :Punkt();Punkt();Punkt();Punkt();Pause();Pause();break;           //h  
           case 105 :Punkt();Punkt();Pause();Pause();break;                           //i 
           case 106 :Punkt();Strich();Strich();Strich();Pause();Pause();break;        //j
           case 107 :Strich();Punkt();Strich();Pause();Pause();break;                 //k
           case 108 :Punkt();Strich();Punkt();Punkt();Pause();Pause();break;          //l 
           case 109 :Strich();Strich();Pause();Pause();break;                         //m
           case 110 :Strich();Punkt();Pause();Pause();break;                          //n  
           case 111 :Strich();Strich();Strich();Pause();Pause();break;                //o 
           case 112 :Punkt();Strich();Strich();Punkt();Pause();Pause();break;         //p
           case 113 :Strich();Strich();Punkt();Strich();Pause();Pause();break;        //q
           case 114 :Punkt();Strich();Punkt();Pause();Pause();break;                  //r
           case 115 :Punkt();Punkt();Punkt();Pause();Pause();break;                   //s
           case 116 :Strich();Pause();Pause();break;                                  //t
           case 117 :Punkt();Punkt();Strich();Pause();Pause();break;                  //u 
           case 118 :Punkt();Punkt();Punkt();Strich();Pause();Pause();break;          //v 
           case 119 :Punkt();Strich();Strich();Pause();Pause();break;                 //w
           case 120 :Strich();Punkt();Punkt();Strich();Pause();Pause();break;         //x
           case 121 :Strich();Punkt();Strich();Strich();Pause();Pause();break;        //y
           case 122 :Strich();Strich();Punkt();Punkt();Pause();Pause();break;         //z
           case 123 :Punkt();Punkt();Punkt();Punkt();Punkt();Punkt();Punkt();Punkt();Pause();Pause();break; //irrung
         default: Pause();Pause();break;
          }         
       }
         
    }while(txt_loop == 0);  //Dauerschleife
}


//---------------------------------

//---------------------------------

void setup() {
  // put your setup code here, to run once:
  pinMode(PKT,     INPUT_PULLUP);
  pinMode(STR,     INPUT_PULLUP);
 
  pinMode(TXT1,     INPUT_PULLUP);
  pinMode(TXT2,     INPUT_PULLUP);
  pinMode(TXT3,     INPUT_PULLUP);
  pinMode(TXT4,     INPUT_PULLUP);

  pinMode(Tx,       INPUT_PULLUP);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(M_Ton, OUTPUT);
  pinMode(Cw_Tx, OUTPUT);
  pinMode(TooglePin, OUTPUT);
  
  //Serial.begin(115200);
}
//#########################################
//-#########-Hauptschleife-##########-----
void loop() {
  ////Serial.print("loop");//Serial.print(ii);
  
  if(bitRead(Merker,PKT_m)){ Punkt();}
  if(bitRead(Merker,STR_m)){Strich();}
  if (digitalRead(PKT) == LOW) bitSet(Merker, PKT_m);
  if (digitalRead(STR) == LOW) bitSet(Merker, STR_m);
  if (digitalRead(Tx)== HIGH){  if((Merker ==4)){Bu_a();};}                            //Kein Paddledruck  Buchstabenerkennung
  
  //digitalWrite(TooglePin,(looptoggle =!looptoggle));

}
