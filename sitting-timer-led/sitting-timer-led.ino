//set sitting time in secounds(CHANGE TO MINUTES):
int sitTime = 30;
//set rest time in secounds(CHANGE TO MINUTES):
int restTime = 10;
//set Max brightness:
int maxBrightness = 150;
//set ledCount:
int ledCount = 7;

//sitTime=sitTime*60; //change to secounds
//restTime=restTime*60; //change to secounds
int unit = maxBrightness / ledCount; //unit for calculating brightness

int leds[] = {5, 2, 3, 6, 7, 8, 11};   // LEDs from right to left connected to these pins
int buttonPin = 12;          // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status

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
  
  Serial.print("Bright "); Serial.println(pin); Serial.println(": "); Serial.println(bright);
  return bright;
}

// functions for animation:
void onAll()
{
  for (int i = ledCount; i > -1; i--)
  {
  analogWrite(leds[i], 255);
  }
}

void offAll()
{
  for (int i = ledCount; i > -1; i--)
  {
    analogWrite(leds[i], 0);
  }
}

void LtoR()
{
  for (int i = ledCount; i > -1; i--)
  {
    analogWrite(leds[i], 255);
    delay(60);
    analogWrite(leds[i], 0);
  }
}

void RtoL()
{
  for (int i = 0; i < ledCount; i++)
  {
    analogWrite(leds[i], 255);
    delay(60);
    analogWrite(leds[i], 0);
  }
}

void charge()
{
  for (int i = ledCount; i > -1; i--)
  {
    analogWrite(leds[i], 255);
    delay(100);
  }
}

void setup() {

  Serial.begin(9600);

  //sitTime=sitTime*1000; //CHANGE TO MINUTES
  //restTime=restTime*1000; //CHANGE TO MINUTES

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  // initialize digital pin for leds as an output.
  for (int i = 0; i < ledCount; i++)
  {
    pinMode(leds[i], OUTPUT);
  }

  //Starting animation:
  //left to right
  LtoR();
  delay(100);

  //right to left
  RtoL();
 
  //charging left to right
  charge();
  delay(100);

  //off all
  offAll();
  delay(100);

  //on all
  onAll();
  delay(100);

}

void loop() {

  //off all
  for (int i = ledCount; i > -1; i--)
  {
    analogWrite(leds[i], 0);
  }

  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  //start timer:
  while (buttonState == LOW)
  {
    //blink:
    for (int i = ledCount; i > -1; i--)
    {
      analogWrite(leds[i], 255);
    } 

    //delay while checking button:
    for (int i = 0; i<500; i++)
    {
      buttonState = digitalRead(buttonPin);
      if (buttonState == HIGH)
      {
        break;
      }
      delay(1);
    } 
    
    for (int i = ledCount; i > -1; i--)
    {
      analogWrite(leds[i], 0);
    }     

    //delay while checking button:
    for (int i = 0; i<500; i++)
    {
      buttonState = digitalRead(buttonPin);
      if (buttonState == HIGH)
      {
        break;
      }
      delay(1);
    }
    
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
