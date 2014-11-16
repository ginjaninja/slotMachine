/**
/*  Slot Machine Crucible Project from Open Source Hardware Group: 
/*  https://opensourcehardwaregroup.com/module-5/control-section-crucible-challenge/
/*  Turns 3 rows of 3 leds into a slot machine game.
/*  Uses pins 2-10 for leds and pin 11 for button to trigger game start.
/*  Author: Shannon McAvoy
**/


//led pins
const int ledPin[] = {2,3,4,5,6,7,8,9,10};
// num of pins
const int pinCount = 9;
// num of pins in each arr
const int arrSize = 3;

//led cols
const int col1[] = {2,5,8};
const int col2[] = {3,6,9};
const int col3[] = {4,7,10};

//button pin
const int buttonPin = 11;
//delay time
const int delayTime = 200;

//initalize buttonPin
int buttonState = 0;

//positions to stop on
int pos1 = 0;
int pos2 = 0;
int pos3 = 0;

void setup(){
  /*using randomSeed ensures that you don't have the same
    random number sequence everytime you play the game */
  randomSeed(analogRead(0));
  
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  
  // setup LED pins
  for(int i; i < pinCount; i++){
    pinMode(ledPin[i], OUTPUT);
  }
  
  // setup button pin
  pinMode(11, INPUT);
}

void loop(){
  // read button state (0 or 1 if pressed)
  buttonState = digitalRead(buttonPin);
  
  // when button is pressed, turn lights on
  if(buttonState == HIGH){
    
    // determine which row in each col will stop
    pos1 = rand();
    pos2 = rand();
    pos3 = rand();
    
    Serial.println(pos1);
    Serial.println(pos2);
    Serial.println(pos3);
    
    // cascade rows 3 times to simulate rows spinning
    for(int i = 0; i < 3; i++){
      ledBlink(col1, col2, col3, arrSize);
    }
    
    // slow down lights left to right to stop in position
    // slow col 1
    for(int i = 2; i >= 0; i--){
      digitalWrite(col1[i], HIGH);
      ledBlink(col2, col3, arrSize);
      digitalWrite(col1[i], LOW);
    }
    // light up pos 1
    digitalWrite(col1[pos1], HIGH);
    Serial.println(col1[pos1]);
    
    // slow col 2
    for(int i = 2; i >= 0; i--){
      digitalWrite(col2[i], HIGH);
      ledBlink(col3, arrSize);
      digitalWrite(col2[i], LOW);
    }
    // light up pos 2
    digitalWrite(col2[pos2], HIGH);
    Serial.println(col2[pos2]);
    
    // slow col3
    for(int i = 2; i >= 0; i--){
      digitalWrite(col3[i], HIGH);
      delay(150);
      digitalWrite(col3[i], LOW);
    }
    // light up pos 3
    digitalWrite(col3[pos3], HIGH);
    Serial.println(col3[pos3]);
  
    delay(1000);
    
    // do we have a matching row?
    if(!matchRow(pos1, pos2, pos3)){
      ledOff(col1, col2, col3); 
      // no match, flash x
      for(int i = 0; i < 3; i++){
        flashX(col1, col2, col3); 
      }
    }  
  }
  
  delay(1);
}


// turn on 3 arrays of led pins 1 at a time
void ledBlink(const int* arr1, const int* arr2, const int* arr3, int arrSize){
  for(int i = arrSize-1; i >= 0; i--){
    Serial.println(arrSize);
    digitalWrite(arr1[i], HIGH);
    digitalWrite(arr2[i], HIGH);
    digitalWrite(arr3[i], HIGH);
    delay(75);
    
    digitalWrite(arr1[i], LOW);
    digitalWrite(arr2[i], LOW);
    digitalWrite(arr3[i], LOW);
    delay(75);
  }
}

// turn on 2 arrays of led pins 1 at a time
void ledBlink(const int* arr1, const int* arr2, int arrSize){
  for(int i = arrSize-1; i >= 0; i--){
    Serial.println(arrSize);
    digitalWrite(arr1[i], HIGH);
    digitalWrite(arr2[i], HIGH);
    delay(75);
    
    digitalWrite(arr1[i], LOW);
    digitalWrite(arr2[i], LOW);
    delay(75);
  }
}

// turn on array of led pins 1 at a time
void ledBlink(const int* arr1, int arrSize){
  for(int i = arrSize-1; i >= 0; i--){
    Serial.println(arrSize);
    digitalWrite(arr1[i], HIGH);
    delay(75);
    
    digitalWrite(arr1[i], LOW);
    delay(75);
  }
}

//check if 3 ints match
boolean matchRow(int a, int b, int c){
  if(a == b && a == c){
    return true;
  }else{
    return false;
  } 
}

// flash x
void flashX(const int* arr1, const int* arr2, const int* arr3){
  makeX(arr1, arr2, arr3);
  delay(100);
  ledOff(arr1, arr2, arr3);
  delay(100);
}

// make X
void makeX(const int* arr1, const int* arr2, const int* arr3){
  digitalWrite(arr1[0], HIGH);
  digitalWrite(arr1[2], HIGH);
  digitalWrite(arr2[1], HIGH);
  digitalWrite(arr3[0], HIGH);
  digitalWrite(arr3[2], HIGH);
}

// turn all leds off
void ledOff(const int* arr1, const int* arr2, const int* arr3){
  for(int i = 0; i < 3; i++){
    digitalWrite(arr1[i], LOW);
    digitalWrite(arr2[i], LOW);
    digitalWrite(arr3[i], LOW);
  }
}


// return random int between 0 and 3
int rand(){
  return random(3); 
}


