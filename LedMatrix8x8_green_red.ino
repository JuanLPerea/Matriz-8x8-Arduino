/*
 * 
 * Controlar una matriz de leds de 8x8 bicolor (rojo y verde)
 * mediante 3 shift registers 74HC595 y un transistor darlington UDN2981A
 * 
 */

const int NUM_ROWS = 8;
const int NUM_COLS = 8;

const int dataPin = 8;      // Row data line
const int clockPin = 9;     // Clock sequence
const int latchPin = 10;    // Latch Pin

int gdataset[13][8] = {{3,6,12,24,48,96,192,96} , {6,12,24,48,96,192,96,48} ,
{12,24,48,96,192,96,48,0} ,{24,48,96,192,96,48,0,12} ,
{48,96,192,96,48,0,12,6} ,{96,192,96,48,0,12,6,3} ,
  {192,96,48,0,12,6,3,6} , {96,48,0,12,6,3,6,12} ,
  {48,0,12,6,3,6,12,24} , {0,12,6,3,6,12,24,48} ,
  {12,6,3,6,12,24,48,96} , {6,3,6,12,24,48,96,192} , {3,6,12,24,48,96,192,128}};


int rdataset[13][8] = {{192,96,48,0,12,6,3,6} , {96,48,0,12,6,3,6,12} ,
  {48,0,12,6,3,6,12,24} , {0,12,6,3,6,12,24,48} ,
  {12,6,3,6,12,24,48,96} , {6,3,6,12,24,48,96,192} , 
  {3,6,12,24,48,96,192,96} , {6,12,24,48,96,192,96,48} ,
  {12,24,48,96,192,96,48,0} , {24,48,96,192,96,48,0,12} ,
  {48,96,192,96,48,0,12,6} , {96,192,96,48,0,12,6,3} ,{3,6,12,24,48,96,192,128}};
 
 

void setup() {
  
 // Serial.begin(9600);
  
  // put your setup code here, to run once:
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
}

void loop() {
  
  int i=0;
  while(true) {
    displayPixels(i,20);  
    i++;
    if (i == 11) {i=0;}
   //Serial.println(i); 
  }
  
}

void displayPixels(int val, int espera) {
  for (int i=0; i < espera ; i++) {
    for (int row = 0 ; row < NUM_ROWS ; row++) {
        int rcur = rdataset[val][row];
        int gcur = gdataset[val][row];
        shiftOut(dataPin, clockPin, MSBFIRST, 255 - rcur);
        shiftOut(dataPin, clockPin, MSBFIRST, 255 - gcur);
        shiftOut(dataPin, clockPin, MSBFIRST, B00000001 << row);
        digitalWrite(latchPin, HIGH);
        digitalWrite(latchPin, LOW);
        delayMicroseconds(1000);
        shiftOut(dataPin, clockPin, MSBFIRST, 255);
        shiftOut(dataPin, clockPin, MSBFIRST, 255);
        shiftOut(dataPin, clockPin, MSBFIRST, B00000001 << row);
        digitalWrite(latchPin, HIGH);
        digitalWrite(latchPin, LOW);
    }
  }
}

