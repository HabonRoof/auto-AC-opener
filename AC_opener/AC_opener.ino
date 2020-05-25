/*
Auther: HabonRoof 2020/05/25
instagram: https://www.instagram.com/habonroof/
youtube channel: https://www.youtube.com/channel/UCIQcFEKPII4MRJ2YsRaiMAQ
This software can be use for anyone but not for buiness.
If you want to use this software for bussiness, please contect me with johnson35762@gmail.com
*/

//Include the necessary libraries for IR remote ------------------------------------------------------------------------------------------------------------------------------------------

#include <IRremote.h>
IRsend irsend;

int khz = 38;     //The carrier wave frequency for your IR remoter, the most common is 38kHz

//Change the IR signals for your custom device, like Air-con or any IR remotable devices
//The RAW data can be get by using "IRrecvdump_v2.ino" demo in the IR Remote library
//To turn the AC, using irSignal_turnOn[], to turn off the AC, using irSignal_turnOff[]

unsigned int irSignal_turnOn[] = {3000,3000, 450,500, 500,550, 450,500, 500,1550, 450,550, 450,550, 450,550, 450,550, 450,550, 450,550, 450,1550, 450,550, 450,550, 450,1550, 450,1550, 450,1550, 450,550, 450,550, 450,550, 450,550, 500,500, 500,500, 500,1500, 450,550, 500,500, 500,500, 500,500, 500,550, 450,550, 450,550, 450,500, 500,550, 450,550, 450,550, 450,550, 450,550, 450,550, 500,500, 500,500, 450,550, 500,500, 500,500, 500,500, 500,500, 450};
unsigned int irSignal_turnOff[] = {3000,3000, 450,550, 450,550, 450,500, 500,1550, 450,550, 450,550, 450,550, 450,550, 450,550, 450,550, 450,1550, 450,550, 450,550, 450,1550, 450,1550, 450,1550, 450,550, 450,550, 450,550, 450,550, 500,500, 500,500, 500,500, 450,550, 500,500, 500,550, 450,500, 500,550, 450,550, 450,550, 450,550, 450,550, 450,550, 450,550, 450,550, 450,550, 500,500, 500,500, 500,500, 500,550, 450,550, 450,550, 450,500, 500,500, 450};

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Define the hall sensors pin
//The IR transmitter and reciever doesn't need to define, because the transmitter can ONLY use in D3 pin, and the receiver ONLY use in D11 pin.
//This is importand because the library use the internal timer only can hook up in this two pins.

byte hallsensor1 = A0;
byte hallsensor2 = A1;

//These flags can be usefun when you want the IR and serial port only print or teansmit once.

bool openflag = false;
bool closeflag = false;
bool IRtransmitted = false;

//doorCount is for counting how many times the person open and close thr door, it also means that is there is a person in the room or not

int doorCount = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  
  //The analogRead value will change depending which pole of magnetic is facing to the hall sensorm please read the datasheet of your sensor and choose a suitable value for the if statement. 
  if (analogRead(hallsensor1) > 700 && openflag == false) {
    while (analogRead(hallsensor2) > 700 )
      //If the first sensor detect the magnectic field, wait for the second sensor's detection, the whole process will stock in the while loop if the second sensor not detect anything
      delay(1);     
    Serial.println("Door OPEN");
    openflag = true;      //means the door opened
    closeflag = false;    //means the door is NOT close, reset the closeflag
  }
  else if (analogRead(hallsensor2) > 700 && closeflag == false) {
    //Same as the first if statement, but the sensor is reverse
    while (analogRead(hallsensor1) > 700 )
      delay(1);
    Serial.println("Door CLOSE");
    doorCount ++;           //doorCount only add 1 if the door open and close once
    IRtransmitted = false;  //reset the IRtransmitted flag for another transmittion
    closeflag = true;       //means the door is closed
    openflag = false;       //means the door is NOT open, reset the open flag
  }
  if((doorCount % 2 == 0) && IRtransmitted == false){
    Serial.println("IR send off"); 
    //Send the IR signal three times ensure the data will arrived to the device
    irsend.sendRaw(irSignal_turnOff, sizeof(irSignal_turnOff) / sizeof(irSignal_turnOff[0]), khz);
    irsend.sendRaw(irSignal_turnOff, sizeof(irSignal_turnOff) / sizeof(irSignal_turnOff[0]), khz);
    irsend.sendRaw(irSignal_turnOff, sizeof(irSignal_turnOff) / sizeof(irSignal_turnOff[0]), khz);
    //Seet the IR transmitted flag, so in the next loop, IR LED will not send the data again.
    IRtransmitted = true;
  }
  else if((doorCount % 2 == 1) && IRtransmitted == false){
    Serial.println("IR send on");
    irsend.sendRaw(irSignal_turnOn, sizeof(irSignal_turnOn) / sizeof(irSignal_turnOn[0]), khz);
    irsend.sendRaw(irSignal_turnOn, sizeof(irSignal_turnOn) / sizeof(irSignal_turnOn[0]), khz);
    irsend.sendRaw(irSignal_turnOn, sizeof(irSignal_turnOn) / sizeof(irSignal_turnOn[0]), khz);
    IRtransmitted = true;
  }
}
// turn off 4B74A0DE
//3000,3000, 450,550, 450,550, 450,500, 500,1550, 450,550, 450,550, 450,550, 450,550, 450,550, 450,550, 450,1550, 450,550, 450,550, 450,1550, 450,1550, 450,1550, 450,550, 450,550, 450,550, 450,550, 500,500, 500,500, 500,500, 450,550, 500,500, 500,550, 450,500, 500,550, 450,550, 450,550, 450,550, 450,550, 450,550, 450,550, 450,550, 450,550, 500,500, 500,500, 500,500, 500,550, 450,550, 450,550, 450,500, 500,500, 450//turn on F9B26EFC
//turn on F9B26EFC
//3000,3000, 450,500, 500,550, 450,500, 500,1550, 450,550, 450,550, 450,550, 450,550, 450,550, 450,550, 450,1550, 450,550, 450,550, 450,1550, 450,1550, 450,1550, 450,550, 450,550, 450,550, 450,550, 500,500, 500,500, 500,1500, 450,550, 500,500, 500,500, 500,500, 500,550, 450,550, 450,550, 450,500, 500,550, 450,550, 450,550, 450,550, 450,550, 450,550, 500,500, 500,500, 450,550, 500,500, 500,500, 500,500, 500,500, 450
