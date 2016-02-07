#include <Servo.h>

// array of 2 elements to store the x and y coordinates of the current position
// of the face in the frame. This data is given through uart
int coord[2];

bool first_iter = true;

// Stores the previous coordinates
int prev_coord[2];

// Variables to parse the data from the serial input
String string_temp_input = "";
int temp_input;
int pos = 0;

// Servos
Servo hor, ver;

// starting positions of the servos
int hor_start_angle = 90;
int ver_start_angle = 80;

// current angles of the servos
int hor_curr_angle = 90;
int ver_curr_angle = 80;

// distance mapping constant
float mk = 0.035;

// servo movement
float hor_mov = 0.0;
float ver_mov = 0.0;

// threshold value to center the face
int thresh = 30;

// head driving
void drive_head(int a, int b)
{


if(a>180)
{
  a = 180;
}
if(a<0)
{
  a = 0;
}
if(b>150)
{
  b = 150;
}
if(b<0)
{
  b = 0;
}

//  for(int i=hor.read();i<a;i++)
//  {
//    hor.write(i);
//    delay(10);
//  }
//  for(int i=ver.read();i<b;i++)
//  {
//    ver.write(i);
//    delay(10);
//  }

  hor.write(a);
  ver.write(b);
 
}
void setup() 
{
  pinMode(13, OUTPUT);
  
  hor.attach(11);
  ver.attach(3);
  
  Serial.begin(57600);

  hor.write(hor_start_angle);
  ver.write(ver_start_angle);
  delay(1000);
}

void loop()
{
  // Taking the uart input
  String input = "";

  while(Serial.available()>0)
  {
    delay(1);
    input = input + (char)Serial.read();
  }

    // updating the previous coordinate parameter. Other than the first iteration
    if(!first_iter)
    {
       prev_coord[0] = coord[0];
       prev_coord[1] = coord[1];
    }

  if(input!="")
  {
    int len = input.length();
    for(int k=0;k<len;k++)
    {
      char c = input.charAt(k);

      if(c=='_')
      {
        temp_input = string_temp_input.toInt();
        coord[pos] = temp_input;
        string_temp_input = "";
        pos++;
      }
      else if(c=='a')
      {
        pos = 0;
        string_temp_input = "";

        Serial.println(coord[0]);
        Serial.println(coord[1]);
        
      }

      else
      {
        string_temp_input+=c;
      }
    }

    // for the first iteration
    if(first_iter)
    {
      prev_coord[0] = coord[0];
      prev_coord[1] = coord[1];
      first_iter = false;
    }

    float dist = sqrt(pow((coord[0]-prev_coord[0]), 2) + pow((coord[1]-prev_coord[1]), 2));
    int int_dist = (int)dist;

    hor_mov = mk*dist;
    ver_mov = mk*dist;

    Serial.println(hor_mov);
    Serial.println(ver_mov);

    if(coord[0] < 300-thresh)
    {
      hor_curr_angle += hor_mov;
    }
    else if(coord[0] > 300+thresh)
    {
      hor_curr_angle -= hor_mov;
    }

    if(coord[1]<220 - thresh)
    {
      ver_curr_angle -= ver_mov;
    }
    else if(coord[1] > 220+thresh)
    {
      ver_curr_angle += ver_mov;
    }

    drive_head(hor_curr_angle, ver_curr_angle);
   

    


  }

}
