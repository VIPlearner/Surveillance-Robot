/*pins for the motor*/
#define enableleft 6
#define leftin1 7
#define leftin2 5
#define rightin1 4
#define rightin2 2
#define enableright 3

#define echofront 8 // attach pin D3 Arduino to pin Echo of HC-SR04
#define trigfront 9 //attach pin D4 Arduino to pin Trig of HC-SR04
#define echoleft 10 // attach pin D5 Arduino to pin Echo of HC-SR04
#define trigleft 11 //attach pin D6 Arduino to pin Trig of HC-SR04
#define echoright 12 // attach pin D7 Arduino to pin Echo of HC-SR04
#define trigright 13 //attach pin D8 Arduino to pin Trig of HC-SR04

long duration;
int distance;
int frontDist, leftDist, rightDist;
int defaultspeed = 150;

void forward(uint8_t speed1)
{
	analogWrite(enableleft , speed1);
 analogWrite(enableright , speed1);
   digitalWrite (leftin1, LOW);
   digitalWrite (leftin2, HIGH);
   digitalWrite (rightin1, HIGH);
   digitalWrite (rightin2, LOW); 
 }

 void backward(uint8_t speed1)
 {
	 analogWrite(enableleft , speed1/2);
   analogWrite(enableright , speed1/2);
    digitalWrite (leftin2, LOW);
    digitalWrite (leftin1,HIGH);
    digitalWrite (rightin2, HIGH);
    digitalWrite (rightin1,LOW);  
 }

void rightback(uint8_t speed1)
 {
  analogWrite(enableright , speed1/2);
	 analogWrite(enableleft , speed1/2);
    digitalWrite (leftin2,LOW);
    digitalWrite (leftin1,LOW);
    digitalWrite (rightin2, HIGH);
    digitalWrite (rightin1,LOW);  
 }

 void leftback(uint8_t speed1)
 {
  analogWrite(enableright , speed1/2);
	 analogWrite(enableleft , speed1/2);
    digitalWrite (leftin2, LOW);
    digitalWrite (leftin1,HIGH);
    digitalWrite (rightin2,LOW);
    digitalWrite (rightin1,LOW);  
 }

 void rightfront(uint8_t speed1)
 {
  analogWrite(enableright , speed1/2);
	 analogWrite(enableleft , speed1/2);
    digitalWrite (leftin1,LOW);
    digitalWrite (leftin2,LOW);
    digitalWrite (rightin1, HIGH);
    digitalWrite (rightin2,LOW);  
  }
  
 void leftfront(uint8_t speed1)
 {
  analogWrite(enableright , speed1/2);
	 analogWrite(enableleft , speed1/2);
    digitalWrite (leftin1, LOW);
    digitalWrite (leftin2,HIGH);
    digitalWrite (rightin1,LOW);
    digitalWrite (rightin2,LOW);  
 }
 
 void stopit()
 {
	analogWrite(enableright , 0);
   analogWrite(enableleft , 0);
  }

int getDist(int trigPin, int echoPin)
{
 digitalWrite(trigPin, LOW); 
  delayMicroseconds(5);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  int distance = (duration / 2)/29.1; // Speed of sound wave divided by 2 (go and back)
  return distance;
}

void compDist()
  {
  frontDist=getDist(trigfront, echofront);
  rightDist=getDist(trigright, echoright);
  leftDist=getDist(trigleft, echoleft);
  if(leftDist > rightDist && leftDist>=5){
    leftfront(defaultspeed);
    while(frontDist<20){
      frontDist=getDist(trigfront, echofront);
      }
  }
  else if(rightDist > leftDist && rightDist>=5){
     rightfront(defaultspeed);
     while(frontDist<20){
      frontDist=getDist(trigfront, echofront);
      }
  }
    else
   { 
     backward(defaultspeed);
     while(frontDist<20){
      frontDist=getDist(trigfront, echofront);
      }
 } 

}

void setup() {
  //Serial.begin(9600);
  pinMode(trigfront, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echofront, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigleft, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoleft, INPUT); // Sets the echoPin as an INPUT
  pinMode(trigright, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoright, INPUT); // Sets the echoPin as an INPUT
  pinMode(enableleft, OUTPUT);
  pinMode(enableright, OUTPUT); 
  pinMode(leftin1, OUTPUT); 
  pinMode(leftin2, OUTPUT); 
  pinMode(rightin1, OUTPUT);
  pinMode(rightin2, OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  frontDist=getDist(trigfront, echofront);
  // Serial.println(frontDist);
  if(frontDist>=20){
    forward(defaultspeed);
  }
  else{
    stopit(); 
    delay(200);
    compDist();
  }
}
