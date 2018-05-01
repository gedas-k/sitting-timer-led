//set sitting time in secounds(CHANGE TO MINUTES):
int sitTime=10;
//set rest time in secounds(CHANGE TO MINUTES):
int restTime=3;

// LEDs from right to left connected to these pins
int leds[] = {5, 2, 3, 6, 7, 8, 11};
int ledCount = 7;

void setup() {
  
  // initialize digital pin for leds as an output.
  for (int i=0; i<ledCount; i++)
  {
    pinMode(leds[i], OUTPUT);
  }

  //Starting animation
  // LEDs from right to left 5, 2, 3, 6, 7, 8, 11
  //left to right
  for (int i=ledCount; i>-1; i--)
  { 
    analogWrite(leds[i], 255);
    delay(60);
    analogWrite(leds[i], 0);
  }  

  delay(100);
  
  //right to left
  for (int i=0; i<ledCount; i++)
  { 
    analogWrite(leds[i], 255);
    delay(60);
    analogWrite(leds[i], 0);
  }

  //charging left to right
  for (int i=ledCount; i>-1; i--)
  { 
    analogWrite(leds[i], 255);
    delay(100);
  }  

  delay(100);

  //off all
  for (int i=ledCount; i>-1; i--)
  { 
    analogWrite(leds[i], 0);
  }  
  
  delay(100);

  //on all
  for (int i=ledCount; i>-1; i--)
  { 
    analogWrite(leds[i], 255);
  }  
  
  delay(100);

}

void loop() {
  // put your main code here, to run repeatedly:

  //off all
  for (int i=ledCount; i>-1; i--)
  { 
    analogWrite(leds[i], 0);
  } 

  for (int i=0; i<sitTime; i++)
    {
      analogWrite(7, 255);
      delay(1000);
      analogWrite(7, 0);
    }

  //on all
  for (int i=ledCount; i>-1; i--)
  { 
    analogWrite(leds[i], 255);
  }  
  
  delay(5000);

}
