#include <Servo.h>

Servo hor;
Servo ver;

bool hor_status = false;
bool ver_status = false;

int hor_curr_delay = 50;
int ver_curr_delay = 50;

int hor_curr_pos = 90;
int ver_curr_pos = 0;

int servo_input[2];
String string_temp_input = "";
int temp_input;

int pos = 0;

void drive_both(int a, int b)
{
  hor_status = true;
  ver_status = true;

  int status_a = 1;
  int status_b = 1;

  status_a = (a>0?1:-1);
  status_b = (b>0?1:-1);

  for(int i=0;i<5;i++)
  {
    if(hor_curr_pos<180 && hor_curr_pos>0)
      hor_curr_pos += status_a;
    if(ver_curr_pos<90 && ver_curr_pos>0)
      ver_curr_pos += status_b;
      
      hor.write(hor_curr_pos);
      delay(hor_curr_delay);
      ver.write(ver_curr_pos);
      delay(ver_curr_delay);

      hor_curr_delay-=2;
      ver_curr_delay-=2;

      if(hor_curr_delay<15)
        hor_curr_delay = 15;
      if(ver_curr_delay<15)
        ver_curr_delay = 15;
        
    }
  }


void drive_servos(int a, int b)
{
  if(a!=2 && b!=2)
  {
    //Stopping
    if(a==2 && b==2)
    {
      
    }
  }
  else
  {
    drive_both(a, b);
  }
}

void setup() 
{
  hor.attach(1);
  ver.attach(2);

  Serial.begin(9600);

}

void loop()
{
  String input = "";

  while(Serial.available()>0)
  {
    delay(10);

    input = input + (char)Serial.read();
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
        servo_input[pos] = temp_input;
        pos++;
      }
      else if(c=='a')
      {
        pos = 0;
        string_temp_input = "";
        drive_servos(servo_input[0], servo_input[1]);
      }
      else
      {
        string_temp_input+=c;
      }
        
        
      }
    }
  }


