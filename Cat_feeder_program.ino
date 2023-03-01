const int endSwitch=6;
const int chargingLed=5;
const int automaticLed=4;
const int stepperButton=9;
const int modeChanger=8;
const int dirPin=2;
const int stepPin=3;
const int MS1=12;
const int MS2=11;
const int MS3=10;
const int buzzer=7;
bool endSwitchState=0;
bool stepperButtonState=0;
bool modeChangerState=0;
unsigned long oneHour=3600000;
unsigned long delayHours=6;
unsigned long delayHoursSum=delayHours*oneHour;
int stepNum=0;
bool mode=0;

void setup() {
Serial.begin(9600);
pinMode(endSwitch, INPUT_PULLUP);
pinMode(stepperButton,INPUT_PULLUP);
pinMode(modeChanger,INPUT_PULLUP);
pinMode(dirPin,OUTPUT);
pinMode(stepPin,OUTPUT);
pinMode(buzzer,OUTPUT);
pinMode(MS1, OUTPUT);
pinMode(MS2, OUTPUT);
pinMode(MS3, OUTPUT);
homeFeeder();
motorOff();
delay(500);
digitalWrite (MS1,HIGH);
digitalWrite (MS2,HIGH);
digitalWrite (MS3,HIGH);
digitalWrite (dirPin,HIGH);

modeChangerState = digitalRead(modeChanger);

if (modeChangerState == 1){
  digitalWrite(automaticLed, HIGH);
  digitalWrite(chargingLed, LOW);
  mode=1;
  stepNum=0;
  Serial.print(mode);
  Serial.print(stepNum);
  }
if(modeChangerState == 0){
  digitalWrite(chargingLed, HIGH);
  digitalWrite(automaticLed, LOW);
  mode=0;
  stepNum=0;
  Serial.print(mode);
  Serial.print(stepNum);
  }
}

void loop() {

if(mode==0 && stepNum<16){
stepperButtonState = digitalRead(stepperButton);
if(stepperButtonState == LOW){
  for(int i =0; i<500; i++){
  digitalWrite(stepPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(stepPin,LOW);
  delayMicroseconds(1000);
    }
    stepNum = stepNum + 1;
    }
}

if(mode==0 && stepNum==16){
  modeChangerState = digitalRead(modeChanger);
  if(modeChangerState == 1){
  mode = 1;
  stepNum = 0;
  digitalWrite(chargingLed, LOW);
  digitalWrite(automaticLed, HIGH);
  }
}

if (mode==1 && stepNum<16){
  for (int x=0; x< 16; x++){
    delay(delayHoursSum); //if you want to change the delay hours, just change the delayHours variable
    tone(buzzer, 370); //if you want to use the buzzer, just delete the comment signs
    delay(1000);
    for(int i =0; i<500; i++){
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(1000);
    }
    stepNum = stepNum+1;  
    }
}

if (mode==1 && stepNum==16){
  modeChangerState = digitalRead(modeChanger);
  if(modeChangerState == 0){
  stepNum = 0;
  mode = 0;
  digitalWrite(chargingLed, HIGH);
  digitalWrite(automaticLed, LOW);
  Serial.print("3 feeding ");
  Serial.println(stepNum);
  }
}
}

void homeFeeder(){
  digitalWrite (MS1,HIGH);
  digitalWrite (MS2,HIGH);
  digitalWrite (MS3,HIGH);
  digitalWrite(dirPin,HIGH);
  do {
  digitalWrite(stepPin,HIGH);
  delayMicroseconds(1000);
  digitalWrite(stepPin,LOW);
  delayMicroseconds(1000);
  }while(digitalRead(endSwitch)!=LOW);
}

void motorOff(){
  digitalWrite(stepPin,LOW);
}
