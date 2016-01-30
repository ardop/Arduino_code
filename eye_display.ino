//Code for the display system composed of 8 5*7 led arrays (4 for each eye)
// Shift registers are used to control all the LED's (By implementing persistence of vision)

// Data, latch and clock pins for the eyes and shorted cathodes (3 each)

// Array index 0 --> Data pin
// Array index 1 --> latch pin
// Array index 2 --> clock pin

int left[] = {1, 2, 3};
int right[] = {4, 5, 6};
int cathode[] = {7, 8, 9};

// Default eye pattern (batch led)
int eye_batch_reg_1[] = {0, 0, 3, 7, 15, 15, 7, 3, 0, 0};
int eye_batch_reg_2[] = {0, 0, 0, 128, 192, 192, 128, 0, 0, 0};




// Writes numbers to the left register pair
void regLeftWrite(int num1, int num2)
{
  digitalWrite(left[1], LOW);
  shiftOut(left[0], left[2], LSBFIRST, num2);
  shiftOut(left[0], left[2], LSBFIRST, num1);
  digitalWrite(left[1], HIGH);
}

// Writes numbers to the right register pair
void regRightWrite(int num1, int num2)
{
  digitalWrite(right[1], LOW);
  shiftOut(right[0], right[2], LSBFIRST, num2);
  shiftOut(right[0], right[2], LSBFIRST, num1);
  digitalWrite(right[1], HIGH);
}

// Writes numbers to the cathode register pairs
void regCathodeWrite(int num1, int num2)
{
  digitalWrite(cathode[1], LOW);
  shiftOut(cathode[0], cathode[2], LSBFIRST, num2);
  shiftOut(cathode[0], cathode[2], LSBFIRST, num1);
  digitalWrite(cathode[1], HIGH);
}

// Lights the led given by the x and y coordinates

void lightLeftLed(int x, int y)
{
  digitalWrite(left[1], LOW);
  digitalWrite(cathode[1], LOW);
  int c = 0;
  
  // Finding value for cathode
  if(y>8)
  {
    c = (int)pow(2, 16-y);
    shiftOut(cathode[0], cathode[2], LSBFIRST, c);
    shiftOut(cathode[0], cathode[2], LSBFIRST, 0);
  }
  else
  {
    c = (int)pow(2, 8-y);
    shiftOut(cathode[0], cathode[2], LSBFIRST, 0);
    shiftOut(cathode[0], cathode[2], LSBFIRST, c);
  }

  // Finding value of anode
  if(x>8)
  {
    c = (int)pow(2, 16-x);
    shiftOut(left[0], left[2], LSBFIRST, c);
    shiftOut(left[0], left[2], LSBFIRST, 0);
  }
  else
  {
    c = (int)pow(2, 8-x);
    shiftOut(left[0], left[2], LSBFIRST, 0);
    shiftOut(left[0], left[2], LSBFIRST, c);
  }

  digitalWrite(left[1], HIGH);
  digitalWrite(cathode[1], HIGH);
  
}

void lightRightLed(int x, int y)
{
  digitalWrite(right[1], LOW);
  digitalWrite(cathode[1], LOW);
  int c = 0;
  
  // Finding value for cathode
  if(y>8)
  {
    c = (int)pow(2, 16-y);
    shiftOut(cathode[0], cathode[2], LSBFIRST, c);
    shiftOut(cathode[0], cathode[2], LSBFIRST, 0);
  }
  else
  {
    c = (int)pow(2, 8-y);
    shiftOut(cathode[0], cathode[2], LSBFIRST, 0);
    shiftOut(cathode[0], cathode[2], LSBFIRST, c);
  }

  // Finding value of anode
  if(x>8)
  {
    c = (int)pow(2, 16-x);
    shiftOut(right[0], right[2], LSBFIRST, c);
    shiftOut(right[0], right[2], LSBFIRST, 0);
  }
  else
  {
    c = (int)pow(2, 8-x);
    shiftOut(right[0], right[2], LSBFIRST, 0);
    shiftOut(right[0], right[2], LSBFIRST, c);
  }

  digitalWrite(right[1], HIGH);
  digitalWrite(cathode[1], HIGH);
  
}

void lightCathode(int y)
{
  digitalWrite(cathode[1], LOW);
  int c = 0;
  
  // Finding value for cathode
  if(y>8)
  {
    c = (int)pow(2, 16-y);
    shiftOut(cathode[0], cathode[2], LSBFIRST, c);
    shiftOut(cathode[0], cathode[2], LSBFIRST, 0);
  }
  else
  {
    c = (int)pow(2, 8-y);
    shiftOut(cathode[0], cathode[2], LSBFIRST, 0);
    shiftOut(cathode[0], cathode[2], LSBFIRST, c);
  }

  digitalWrite(cathode[1], HIGH);
}

void normalBatchBothEyes()
{
  // Persistence of vision to display the eyes (10 ms second between each row)
  for(int i=1;i<=10;i++)
  {
    lightCathode(i);
    regLeftWrite(eye_batch_reg_1[i-1], eye_batch_reg_2[i-1]);
    regRightWrite(eye_batch_reg_1[i-1], eye_batch_reg_2[i-1]);
    delay(1); // To ensure persistence of vision
  }
}

void displayBothEyes(int eye_1[], int eye_2[])
{
  // displays with arrays as batch reference
  for(int i=1;i<=10;i++)
  {
    lightCathode(i);
    regLeftWrite(eye_1[i-1], eye_2[i-1]);
    regRightWrite(eye_1[i-1], eye_2[i-1]);
    delay(1); // To ensure persistence of vision
  }
}


// Generic functions for diminishing and expanding the eye while blinking

void diminishEye(int a[], int b[], int c)
{
  // Diminishes a and b matrices by one stage (removing middle 2 rows)
  for(int i=0;i<c;i++)
  {
    // Diminish eye height by 2 layers (middle rows)
    a[5-i-1] = a[5-i-2];
    a[5+i] = a[5+i+1];
    b[5-i-1] = b[5-i-2];
    b[5+i] = b[5+i+1];
  }
}

void expandEye(int a[], int b[], int aa[], int bb[], int c, int d)
{
  // Expands the diminished portion
  // Here a, b are the changing batch values
  // aa and bb are the actual eye batch values which is used for reconstruction
  for(int i=0;i<c;i++)
  {
    // Reconstruction logic can be understood from the sheets
    
    a[5-i-2] = a[5-i-1];
    a[5+i+1] = a[5+i];
    b[5-i-2] = b[5-i-1];
    b[5+i+1] = b[5+i];

    a[4] = aa[d];
    a[5] = aa[d];
    b[4] = bb[d];
    b[5] = bb[d];
    
  }
}


void blinkBothEyes(int eye_batch_reg_1[], int eye_batch_reg_2[])
{
  int eye_1[10];
  int eye_2[10];

  // Blinking action by taking away the middle 2 led rows at a time and collapsing
  for(int i=0;i<10;i++)
  {
    eye_1[i] = eye_batch_reg_1[i];
    eye_2[i] = eye_batch_reg_2[i];
  }

  // Closing eyes
  for(int i=0;i<3;i++)
  {
    diminishEye(eye_1, eye_2, 3);
    int start_time = millis();
    while(millis()-start_time<50)
    {
     displayBothEyes(eye_1, eye_2);
    }

  // Opening eyes
  }
  for(int i=0;i<3;i++)
  {
    expandEye(eye_1, eye_2, eye_batch_reg_1, eye_batch_reg_2, i+1, i+2);
    int start_time = millis();
    while(millis()-start_time<50)
    {
      displayBothEyes(eye_1, eye_2);
    }
    
  }
}



void setup()
{
  // Initializing the pins as output pins
  for(int i=0;i<3;i++)
  {
    pinMode(left[i], OUTPUT);
    pinMode(right[i], OUTPUT);
    pinMode(cathode[i], OUTPUT);
  }


  //Serial monitor for Debugging
  Serial.begin(9600);
  
}

void loop()
{

}
