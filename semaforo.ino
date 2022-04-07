int GT = 10000;
int Y = 5000;
float GA;
float GB;

int pins[2][3] = {{6, 5, 4}, {11, 10, 9}};
int pedestrian[2][2] = {{7, 8},{12, 13}};
int potentiometer = A0;

float calc_time(int value) {

  int Tlow  = 200;
  int Thigh = 500;
  int _low = 0;
  int _high = 341;


  if (value > 341) {
    Tlow = 500;
    Thigh = 667;
    _low = 342;
    _high = 1023;
  }
  
  float r = (map(value, _low, _high, Tlow, Thigh) / 1000.0);
  Serial.print("Tempo: ");
  Serial.println(r);
  return r;

}

void change_pin(boolean group, char color) {
  switch (color) {
    case 'R':	
      digitalWrite(pedestrian[group][0], HIGH);
      digitalWrite(pedestrian[group][1], LOW);
      digitalWrite(pins[group][0], HIGH);   // R
      digitalWrite(pins[group][1], LOW);    // Y
      digitalWrite(pins[group][2], LOW);    // G

      break;
    case 'Y':

      digitalWrite(pins[group][0], LOW);   // R
      digitalWrite(pins[group][1], HIGH);  // Y
      digitalWrite(pins[group][2], LOW);   // G

      break;
    default:

      digitalWrite(pedestrian[group][0], LOW);
      digitalWrite(pedestrian[group][1], HIGH);
      digitalWrite(pins[group][0], LOW);   // R
      digitalWrite(pins[group][1], LOW);  // Y
      digitalWrite(pins[group][2], HIGH);   // G
      break;
  }
  Serial.print(group);
  Serial.println(color);
}
void setup() {
  Serial.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(2), interrupt_0, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), interrupt_0, FALLING);
  pinMode(potentiometer, INPUT);
  
  for (int i=2; 14 > i; i++) {
  	pinMode(i, OUTPUT);
  }
  Serial.println("Start");
}


void interrupt_0(){
   delay(GA/2);
   change_pin(0, 'R');
   change_pin(1, 'R');
   delay(GA/2);
}

void loop() {
  //XXXXXXXXX
  //GGGGYYRRR
  //RRRRRRGYY


  GA = GT*calc_time(analogRead(potentiometer));
  GB = GT-GA;
  change_pin(0, 'G');
  change_pin(1, 'R');

  delay(GA);
  change_pin(0, 'Y');
  delay(Y);
  change_pin(0, 'R');
  change_pin(1, 'G');
  delay(GB);
  change_pin(1, 'Y');
  delay(Y);

}
