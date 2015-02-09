#define outputSelector A3
#define CS A4
#define WR A5
#include <AcceleroMMA7361.h>
byte sine[] = {127, 134, 142, 150, 158, 166, 173, 181, 188, 195, 201, 207, 213, 219, 224, 229, 234, 238, 241, 245, 247, 250, 251, 252, 253, 254, 253, 252, 251, 250, 247, 245, 241, 238, 234, 229, 224, 219, 213, 207, 201, 195, 188, 181, 173, 166, 158, 150, 142, 134, 127, 119, 111, 103, 95, 87, 80, 72, 65, 58, 52, 46, 40, 34, 29, 24, 19, 15, 12, 8, 6, 3, 2, 1, 0, 0, 0, 1, 2, 3, 6, 8, 12, 15, 19, 24, 29, 34, 40, 46, 52, 58, 65, 72, 80, 87, 95, 103, 111, 119,};
AcceleroMMA7361 accelero;
int xTone;
int x;
int y;
int z;

void setup(){
  //set digital pins 0-7 as outputs
  for (int i=0;i<8;i++){
    pinMode(i,OUTPUT);
  }

  Serial.begin(9600);
  accelero.begin(13, 12, 11, 10, A0, A1, A2);
  accelero.setARefVoltage(5);                   //sets the AREF voltage to 3.3V
  accelero.setSensitivity(LOW);                   //sets the sensitivity to +/-6G
  accelero.calibrate();
  pinMode(outputSelector,OUTPUT);
  pinMode(CS,OUTPUT);
  pinMode(WR,OUTPUT);
  digitalWrite(outputSelector,LOW);
  digitalWrite(CS,LOW);
  digitalWrite(WR,LOW);

  }


void loop(){
  x = accelero.getXAccel();
  Serial.print("\nx: ");
  Serial.print(x);
  if (x > 70  && x < 300){
    xTone = map(x, 70, 300, 10, 100);   
    for (int Rep = 0; Rep<50; Rep++){
      for (int t=0;t<100;t++){
        PORTD = sine[t];
        delayMicroseconds(xTone);
      }
    }
  }
  if (x < 0  && x > -300){
    xTone = map(x, -300, 0, 100, 10);   
    for (int Rep = 0; Rep<50; Rep++){
      for (int t=0;t<100;t++){
        PORTD = sine[t];
        delayMicroseconds(xTone);
      }
    }
  }
}


/* frequency ranges 
x    -300    300    1     200     - produces a bassy and crystaline sound
x    -300    300    10    100     - produces a flat bassy noise
x    -300    300    10    50      - produces an interesting electronic, musical noise
x    -300    300    1     50      - produces a brighter sound 
x    -300    300    1     30      - produces a high whining noise 
x    -300    300    1     50      - with the ranges broken = chirping computer sound annoying. 
*/
