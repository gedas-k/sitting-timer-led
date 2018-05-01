//set sitting time in secounds(CHANGE TO MINUTES):
int sitTime = 10;
//set rest time in secounds(CHANGE TO MINUTES):
int restTime = 10;
//set Max brightness:
int maxBrightness = 255;
//set ledCount:
int ledCount = 7;

//sitTime=sitTime*60; //change to secounds
//restTime=restTime*60; //change to secounds
int unit = maxBrightness / ledCount; //unit for calculating brightness

// LEDs from right to left connected to these pins
int leds[] = {5, 2, 3, 6, 7, 8, 11};
//int Bright[] = {0, 1, 2, 3, 4, 5, 6};

//Brightness function:   
int brightness(int pin, int brightX)
{
  int bright = ledCount*(brightX-(unit*(pin+1))+unit);
  if (bright > maxBrightness)
  {
    bright = maxBrightness;
  }
  else if (bright < 0)
  {
    bright = 0;
  }
  return bright;
}

void setup() {

  //sitTime=sitTime*1000; //CHANGE TO MINUTES
  //restTime=restTime*1000; //CHANGE TO MINUTES



  // initialize digital pin for leds as an output.
  for (int i = 0; i < ledCount; i++)
  {
    pinMode(leds[i], OUTPUT);
  }

  //Starting animation
  // LEDs from right to left 5, 2, 3, 6, 7, 8, 11
  //left to right
  for (int i = ledCount; i > -1; i--)
  {
    analogWrite(leds[i], 255);
    delay(60);
    analogWrite(leds[i], 0);
  }

  delay(100);

  //right to left
  for (int i = 0; i < ledCount; i++)
  {
    analogWrite(leds[i], 255);
    delay(60);
    analogWrite(leds[i], 0);
  }

  //charging left to right
  for (int i = ledCount; i > -1; i--)
  {
    analogWrite(leds[i], 255);
    delay(100);
  }

  delay(100);

  //off all
  for (int i = ledCount; i > -1; i--)
  {
    analogWrite(leds[i], 0);
  }

  delay(100);

  //on all
  for (int i = ledCount; i > -1; i--)
  {
    analogWrite(leds[i], 255);
  }

  delay(100);

}

void loop() {

  //off all
  for (int i = ledCount; i > -1; i--)
  {
    analogWrite(leds[i], 0);
  }

  //Loop for sitting:
  for (int i = 0; i < sitTime; i++)
  {
    int brightX = map(i, 0, sitTime, 0, maxBrightness); //maping for brighten

    //Turn on what needs to be on:
    for (int j=0; j<ledCount; j++)
    {
      analogWrite(leds[j], brightness(j, brightX));
    }

    delay(1000);
  }
    
  //Loop for resting:
  for (int j = 0; j < restTime; j++)
  {
    //Flash while resting:
    //Off:
    for (int i = ledCount; i > -1; i--)
    {
      analogWrite(leds[i], 0);
    }
    
    delay(500);

    //On:
    for (int i=ledCount; i>-1; i--)
    {
      analogWrite(leds[i], 255);
    }
  
    delay(500);
  }
}
