//update from SAnwandter

#define ROW_1 2
#define ROW_2 3
#define ROW_3 4
#define ROW_4 5
#define ROW_5 6
#define ROW_6 7
#define ROW_7 8
#define ROW_8 9

#define COL_1 10
#define COL_2 11
#define COL_3 12
#define COL_4 13
#define COL_5 A0
#define COL_6 A1
#define COL_7 A2
#define COL_8 A3

#define LF 0x0A
#define frase_len 200
char frase[frase_len];
int last_char = 0;

const byte rows[] = {
    ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8
};
const byte col[] = {
  COL_1,COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8
};

// The display buffer
// It's prefilled with a smiling face (1 = ON, 0 = OFF)
byte NONE[] = {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};
byte ALL[] = {B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111};
byte EX[] = {B00000000,B00010000,B00010000,B00010000,B00010000,B00000000,B00010000,B00000000};
byte A[] = {B00000000,B00111100,B01100110,B01100110,B01111110,B01100110,B01100110,B01100110};
byte B[] = {B01111000,B01001000,B01001000,B01110000,B01001000,B01000100,B01000100,B01111100};
byte C[] = {B00000000,B00011110,B00100000,B01000000,B01000000,B01000000,B00100000,B00011110};
byte D[] = {B00000000,B00111000,B00100100,B00100010,B00100010,B00100100,B00111000,B00000000};
byte E[] = {B00000000,B00111100,B00100000,B00111000,B00100000,B00100000,B00111100,B00000000};
byte F[] = {B00000000,B00111100,B00100000,B00111000,B00100000,B00100000,B00100000,B00000000};
byte G[] = {B00000000,B00111110,B00100000,B00100000,B00101110,B00100010,B00111110,B00000000};
byte H[] = {B00000000,B00100100,B00100100,B00111100,B00100100,B00100100,B00100100,B00000000};
byte I[] = {B00000000,B00111000,B00010000,B00010000,B00010000,B00010000,B00111000,B00000000};
byte J[] = {B00000000,B00011100,B00001000,B00001000,B00001000,B00101000,B00111000,B00000000};
byte K[] = {B00000000,B00100100,B00101000,B00110000,B00101000,B00100100,B00100100,B00000000};
byte L[] = {B00000000,B00100000,B00100000,B00100000,B00100000,B00100000,B00111100,B00000000};
byte M[] = {B00000000,B00000000,B01000100,B10101010,B10010010,B10000010,B10000010,B00000000};
byte N[] = {B00000000,B00100010,B00110010,B00101010,B00100110,B00100010,B00000000,B00000000};
byte O[] = {B00000000,B00111100,B01000010,B01000010,B01000010,B01000010,B00111100,B00000000};
byte P[] = {B00000000,B00111000,B00100100,B00100100,B00111000,B00100000,B00100000,B00000000};
byte Q[] = {B00000000,B00111100,B01000010,B01000010,B01000010,B01000110,B00111110,B00000001};
byte R[] = {B00000000,B00111000,B00100100,B00100100,B00111000,B00100100,B00100100,B00000000};
byte S[] = {B00000000,B00111100,B00100000,B00111100,B00000100,B00000100,B00111100,B00000000};
byte T[] = {B00000000,B01111100,B00010000,B00010000,B00010000,B00010000,B00010000,B00000000};
byte U[] = {B00000000,B01000010,B01000010,B01000010,B01000010,B00100100,B00011000,B00000000};
byte V[] = {B00000000,B00100010,B00100010,B00100010,B00010100,B00010100,B00001000,B00000000};
byte W[] = {B00000000,B10000010,B10010010,B01010100,B01010100,B00101000,B00000000,B00000000};
byte X[] = {B00000000,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B00000000};
byte Y[] = {B00000000,B01000100,B00101000,B00010000,B00010000,B00010000,B00010000,B00000000};
byte Z[] = {B00000000,B00111100,B00000100,B00001000,B00010000,B00100000,B00111100,B00000000};

float timeCount = 0;

void setup() 
{
    // Open serial port
    Serial.begin(9600);
    
    // Set all used pins to OUTPUT
    // This is very important! If the pins are set to input
    // the display will be very dim.
    for (byte i = 2; i <= 13; i++)
        pinMode(i, OUTPUT);
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
    pinMode(A5, OUTPUT);
}

void loop() {
  delay(5);
  timeCount += 3;
  readSerial();
  delay(1000);
  drawMsg(frase);
}

void readSerial() { //sideeffects
  int idx = 0;
  while(true) {
    if (Serial.available() > 0) {
      frase[idx] = Serial.read();
      if (frase[idx] == LF) {
          frase[idx-1] = 0; //remove CR
          last_char=idx+1;
          return;
      }
      idx++;
    }
  }
}

void blinkTwice() {
  for(int j=30;j>0; j--) {
    drawScreen(ALL);
  }
  delay(100);
  for(int j=30;j>0; j--) {
    drawScreen(ALL);
  }
  delay(500);
}

void drawMsg(char* msg) {
  blinkTwice();
  for(int i=0;i<last_char; i++) {
    int chartime = 100;
    while(chartime>0) {
      if(chartime>20) {
        switch(msg[i]) {
          case 'a':
            drawScreen(A);
            break;
          case 'b':
            drawScreen(B);
            break;
          case 'c':
            drawScreen(C);
            break;
          case 'd':
            drawScreen(D);
            break;
          case 'e':
            drawScreen(E);
            break;
          case 'f':
            drawScreen(F);
            break;
          case 'g':
            drawScreen(G);
            break;
          case 'h':
            drawScreen(H);
            break;
          case 'i':
            drawScreen(I);
            break;
          case 'j':
            drawScreen(J);
            break;
          case 'k':
            drawScreen(K);
            break;
          case 'l':
            drawScreen(L);
            break;
          case 'm':
            drawScreen(M);
            break;
          case 'n':
            drawScreen(N);
            break;
          case 'o':
            drawScreen(O);
            break;
          case 'p':
            drawScreen(P);
            break;
          case 'q':
            drawScreen(Q);
            break;
          case 'r':
            drawScreen(R);
            break;
          case 's':
            drawScreen(S);
            break;
          case 't':
            drawScreen(T);
            break;
          case 'u':
            drawScreen(U);
            break;
          case 'v':
            drawScreen(V);
            break;
          case 'w':
            drawScreen(W);
            break;
          case 'x':
            drawScreen(X);
            break;
          case 'y':
            drawScreen(Y);
            break;
          case 'z':
            drawScreen(Z);
            break;
          case ' ':
            drawScreen(NONE);
            break;
          default:
            //do nothing
            break;
        }
      }
      else delay(4);
      chartime-=1;
    }
  }
}

void  drawScreen(byte buffer2[])
 { 
   // Turn on each row in series
    for (byte i = 0; i < 8; i++)        // count next row
     {
        digitalWrite(rows[i], HIGH);    //initiate whole row
        for (byte a = 0; a < 8; a++)    // count next row
        {
          // if You set (~buffer2[i] >> a) then You will have positive
          digitalWrite(col[a], (~buffer2[i] >> a) & 0x01); // initiate whole column
          
          delayMicroseconds(100);       // uncoment deley for diferent speed of display
          //delayMicroseconds(1000);
          //delay(10);
          //delay(100);
          
          digitalWrite(col[a], 1);      // reset whole column
        }
        digitalWrite(rows[i], LOW);     // reset whole row
        // otherwise last row will intersect with next row
    }
}
// 
  /* this is siplest resemplation how for loop is working with each row.
    digitalWrite(COL_1, (~b >> 0) & 0x01); // Get the 1st bit: 10000000
    digitalWrite(COL_2, (~b >> 1) & 0x01); // Get the 2nd bit: 01000000
    digitalWrite(COL_3, (~b >> 2) & 0x01); // Get the 3rd bit: 00100000
    digitalWrite(COL_4, (~b >> 3) & 0x01); // Get the 4th bit: 00010000
    digitalWrite(COL_5, (~b >> 4) & 0x01); // Get the 5th bit: 00001000
    digitalWrite(COL_6, (~b >> 5) & 0x01); // Get the 6th bit: 00000100
    digitalWrite(COL_7, (~b >> 6) & 0x01); // Get the 7th bit: 00000010
    digitalWrite(COL_8, (~b >> 7) & 0x01); // Get the 8th bit: 00000001
}*/
