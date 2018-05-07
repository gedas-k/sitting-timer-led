//set sitting time in secounds(CHANGE TO MINUTES):
int sitTime = 20;
//set rest time in secounds(CHANGE TO MINUTES):
int restTime = 5;
//set Max brightness:
//int maxBrightness = 150;
//set ledCount:
int ledCount = 7;
// secounds for one LED:
int ledTime = 10;
// pulsing speed:
int dimSpeed = 2;

//sitTime=sitTime*60; //change to secounds
//restTime=restTime*60; //change to secounds

int leds[] = {5, 2, 3, 6, 7, 8, 11};   // LEDs from right to left connected to these pins
int buttonPin = 12;          // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status
int potPin = A0;             // potentiometer pin
int wins = 0, loses = 0;    // for counting score in minigame

// function for max brightness:
int maxBrightness()
{
  int maxBrightness = analogRead(A0);
  maxBrightness = map(maxBrightness, 50, 1000, 10, 255);
  
  if (maxBrightness > 255)
  {
    maxBrightness = 255;
  }
  else if (maxBrightness < 10)
  {
    maxBrightness = 10;
  }
  
  return maxBrightness;
}

//Brightness function:   
int brightness(int pin, int brightX, int maxBrig)
{
  int unit = maxBrig / ledCount;                   //unit for calculating brightness
  int bright = ledCount*(brightX-(unit*(pin+1))+unit);
  if (bright > maxBrig)
  {
    bright = maxBrig;
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

void RtoL(int pause)
{
  for (int i = ledCount-1; i >= 0; i--)
  {
    analogWrite(leds[i], 255);
    delay(pause);
    analogWrite(leds[i], 0);
  }
}

void LtoR(int pause)
{
  for (int i = 0; i < ledCount; i++)
  {
    analogWrite(leds[i], 255);
    delay(pause);
    analogWrite(leds[i], 0);
  }
}

void chargeL(int pause)
{
  for (int i = 0; i < ledCount; i++)
  {
    analogWrite(leds[i], 255);
    delay(pause);
  }
  offAll();
}

void chargeR(int pause)
{
  for (int i = ledCount-1; i > -1; i--)
  {
    analogWrite(leds[i], 255);
    delay(pause);
  }
  offAll();
}

bool win()
{
  offAll();
  chargeL(50);
  offAll();
  wins = wins + 1;  //counts score

  //show score:
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < wins; j++)
    {
      analogWrite(leds[j], 255);
    }
    for (int j = 1; j <= loses; j++)
    {
      analogWrite(leds[ledCount-j], 255);
    }
    delay(500);
    for (int j = 0; j < wins; j++)
    {
      analogWrite(leds[j], 0);
    }
    for (int j = 1; j <= loses; j++)
    {
      analogWrite(leds[ledCount-j], 0);
    }
    delay(500);
  }

  //finishes game:
  if (wins < 3)
  {
    return true;
  }
  else if (wins == 3)
  {
    return false;
  }
}

bool lost()
{
  offAll();
  chargeR(100);
  offAll();
  loses = loses + 1; //counts score

  //show score:
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < wins; j++)
    {
      analogWrite(leds[j], 255);
    }
    for (int j = 1; j <= loses; j++)
    {
      analogWrite(leds[ledCount-j], 255);
    }
    delay(500);
    for (int j = 0; j < wins; j++)
    {
      analogWrite(leds[j], 0);
    }
    for (int j = 1; j <= loses; j++)
    {
      analogWrite(leds[ledCount-j], 0);
    }
    delay(500);
  }

  //finishes game:
  if (loses < 3)
  {
    return true;
  }
  else if (loses == 3)
  {
    return false;
  }
}

int game(int diff)
{
  bool goal = false;
  analogWrite(leds[0], 255);
  delay(diff);
  analogWrite(leds[0], 0);
  while (goal == false)
  {
    //Left to right:
    for (int i = 1; i <= ledCount; i++)
    {
      //moves:
      if (i < (ledCount-1))
      {
        analogWrite(leds[i], 255);
        delay(diff);
        analogWrite(leds[i], 0);
      }
      //checks if bloked:
      else
      {
        analogWrite(leds[i], 255);
        delay(diff);
        analogWrite(leds[i], 0);
        
        int block = random(10);
        if (block < 9) // 90% block chance
        {
          break;
        }
        //if not bloked:
        else
        {
          delay(diff);
          goal = true;
          return win();
        }
      }

    }

    //Right to left:
    bool forth = false;
    for (int i = (ledCount - 2); i >= -1; i--)
    {
      //moves and checks if button pressed
      if (i > 0)
      {
        analogWrite(leds[i], 255);
        for (int j = 0; j < 100; j++)
        {
          buttonState = digitalRead (buttonPin);
          //if pressed to early:
          if (buttonState == HIGH)
          {
            goal = true;
            return lost();
          }
          delay(diff/100);
        }
        analogWrite(leds[i], 0);
      }
      //actions on last LED:
      else if (i == 0)
      {
        analogWrite(leds[i], 255);
        //checks button state:
        for (int j=0; j < 100; j++)
        {
          buttonState = digitalRead (buttonPin);
          if (buttonState == HIGH)
          {
            diff = diff - (diff/5);
            //continue dalay for smooter action:
            for (; j < 100; j++)
            {
              delay(diff/100);
            }
            analogWrite(leds[i], 0);
            forth = true;
          }
          delay(diff/100);
        }
      }
      //if button pressed:
      if (forth == true)
      {
        break;
      }
      //if button not pressed:
      else if (i == -1)
      {
        goal == true;
        return lost();
      }
    }
  
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
  LtoR(60);
  delay(100);

  //right to left
  RtoL(60);
 
  //charging left to right
  chargeL(100);
  delay(100);

  //off all
  offAll();
  delay(100);

  //on all
  onAll();
  delay(100);
  
  //time selector:
  while (buttonState == LOW)
  {
    int potVal = analogRead(potPin);
    int allTimeLED = map (potVal, 50, 1000, 1, ledCount); // potentiometer range reduced
    int i = 0;
    
    for (; i < allTimeLED; i++)
    {
      analogWrite (leds[i], 255);
    }
    for (; i < ledCount; i++)
    {
      analogWrite (leds[i], 0);
    }
    
    int allTime = allTimeLED * ledTime;
    sitTime = allTime * 0.92;
    restTime = allTime - sitTime;
    buttonState = digitalRead (buttonPin);
    
  }
}

void loop() {

/*
  //DELETE:  ///////////////////////////////////////////////////////////////////////////
  while (buttonState == LOW)
  {
    buttonState = digitalRead (buttonPin);
  }

  offAll();
  delay(1000);

  int gaming = true;
  int score = 0;
  int diff = 400; // difficulty
  while (gaming == true)
  {
    gaming = game(diff);
  }

  //TILL HERE
*/
  //off all
  offAll();

  delay (500);

  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  //start timer:
  while (buttonState == LOW)
  {
    int maxBrig = maxBrightness();
    //blink:
    /*
    for (int i = ledCount; i > -1; i--)
    {
      analogWrite(leds[i], maxBrig);
    } 
*/
    //delay while checking button:
    for (int i = 0; i<800; i++)
    {
      maxBrig = maxBrightness();
      
        for (int i = ledCount; i > -1; i--)
      {
        analogWrite(leds[i], maxBrig);
      } 
      
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
    for (int i = 0; i<200; i++)
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
    int maxBrig = maxBrightness();
    int brightX = map(i, 0, sitTime, 0, maxBrig); //maping for brighten

    //Turn on what needs to be on:
    for (int j=0; j<ledCount; j++)
    {
      analogWrite(leds[j], brightness(j, brightX, maxBrig));
    }
    delay(1000);
    
  }

  //Wait for button press:
  buttonState = digitalRead(buttonPin);
  while (buttonState == LOW)
  {
    buttonState = digitalRead(buttonPin);
    //Add animation to stop sitting: /////////////////////////////////////////////
    onAll();
    delay(10);
    offAll();
    delay(10);
  }

  delay(1000);
  
  //Ping pong mini game to distract from work:
  int gaming = true;
  int score = 0;
  int diff = 400; // difficulty
  while (gaming == true)
  {
    gaming = game(diff);
  }
  
  //Brake:
  // pulsing:
  bool fade;
  int pulse = 11;
  for (int i = 0; i < (restTime*100); i++)
  {
    if (pulse <= (10+dimSpeed))
    {
      fade = false;
      pulse = 11;
    }
    else if (pulse >= (256-dimSpeed))
    {
      fade = true;
      pulse = 255;
    }

    if (fade == false)
    {
      pulse = pulse + dimSpeed;;
    }
    else
    {
      pulse = pulse - dimSpeed;
    }

    for (int j = ledCount; j > -1; j--)
    {
      analogWrite(leds[j], pulse);
    }
    delay(10);
    //buttonState = digitalRead(buttonPin); //Add kill
  }
}
