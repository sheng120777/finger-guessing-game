#include <Servo.h>
#include <Arduino.h>

Servo servothumb;          
Servo servoindex;          
Servo servomiddle;
Servo servoring;
Servo servopinky;


char number[50];
char c;
int state=0;
String myStringRec;
int stringCounter=0;
bool stringCounterStart=false;
String myRevivedString;
int stringLength=6;

int servoPinky,servoMiddle,servoIndex,servoThumb,servoRing;
int myVals[]={0,0,0,0,0} ;

int myButton= 1;
bool portable;


void allON(){  
    servopinky.write(180);
    delay(1000);
    servoindex.write(180);
    delay(1000);
    servomiddle.write(180);
    delay(1000);
    servothumb.write(180);
    delay(1000);
    servoring.write(180);  
}


void allOFF(){    
    servopinky.write(0);
    delay(1000);
    servoindex.write(0);
    delay(1000);
    servomiddle.write(0);
    delay(1000);
    servothumb.write(0);
    delay(1000);
    servoring.write(0);
}

void setup(){
    Serial.begin(9600);
    servothumb.attach(3);  
    servoindex.attach(5);
    servomiddle.attach(6);
    servoring.attach(10);  
    servopinky.attach(11);
    delay(500);
    allOFF();
    delay(100);
    allON();
}

void receiveData(){
    while(Serial.available()){
        char c=Serial.read();
    
        if (c=='$'){
            stringCounterStart=true;
        }
        if(stringCounterStart==true){
            if(stringCounter<stringLength){
                myRevivedString=String(myRevivedString+c);
                stringCounter++;
            }
            if(stringCounter>=stringLength){
                stringCounter=0;
                stringCounterStart=false;
                servoPinky=myRevivedString.substring(1, 2).toInt();
                servoRing=myRevivedString.substring(2, 3).toInt();
                servoMiddle=myRevivedString.substring(3, 4).toInt();
                servoIndex=myRevivedString.substring(4, 5).toInt();
                servoThumb=myRevivedString.substring(5, 6).toInt();
    //        Serial.print(servoPinky);
    //        Serial.print(" ");
    //        Serial.print(servoRing);
    //        Serial.print(" ");
    //        Serial.print(servoMiddle);
    //        Serial.print(" ");
    //        Serial.print(servoIndex);
    //        Serial.print(" ");
    //        Serial.println(servoThumb);       
            myRevivedString = "";
            }
        }   
    }
}

void loop() {

    receiveData();
    if(servoPinky ==1){
        servopinky.write(180);
    }
    else{
        servopinky.write(0);
    }

    if(servoIndex ==1){
        servoindex.write(180);
    }
    else{
        servoindex.write(0);
    }

    if(servoMiddle ==1){
        servomiddle.write(180);
    }
    else{
        servomiddle.write(0);
    }

    if(servoThumb ==1){
        servothumb.write(180);
    }
    else{
        servothumb.write(30);
    }

    if(servoRing ==1){
        servoring.write(150);
    }
    else{
        servoring.write(0);
    }
}
