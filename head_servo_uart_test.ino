#include <Servo.h>

Servo hor, ver;

int hor_curr_pos = 90;
int ver_curr_pos = 80;

int servo_input[2];
String string_temp_input = "";
int temp_input;

int pos = 0;



void drive_servos(int a, int b)
{
  int hor_inc = 0;
  int ver_inc = 0;
  
  if(a==0)
  {
    hor_inc = 1;
  }
  if(a==1)
  {
    hor_inc = -1;
  }
  if(b==0)
  {
    ver_inc = -1;
  }
  if(b==1)
  {
    ver_inc = 1;
  }

  for(int i=0;i<3;i++)
  {
    if(hor_curr_pos>0 && hor_curr_pos<180)
    {
      hor_curr_pos += hor_inc;
    }
    if(ver_curr_pos>0 && ver_curr_pos<150 && i!=2)
    {
      ver_curr_pos += ver_inc;
    }

    hor.write(hor_curr_pos);
    ver.write(ver_curr_pos);
//
//    if(i==0 || i==2)
//      delay(50);
//    else
//      delay(35);

//    delay(15);
    if(i==0 || i==2)
    {
      delay(5);  
    }
    
  }
}

void setup() 
{
  hor.attach(6);
  ver.attach(3);

  Serial.begin(57600);

  hor.write(hor_curr_pos);
  ver.write(ver_curr_pos);
  delay(1000);

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

    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);

    
    int len = input.length();
    for(int k=0;k<len;k++)
    {
      char c = input.charAt(k);

      if(c=='_')
      {
        temp_input = string_temp_input.toInt();
        servo_input[pos] = temp_input;
        string_temp_input="";
        pos++;
      }
      else if(c=='a')
      {
        pos = 0;
        string_temp_input = "";

        Serial.println(servo_input[0]);
        Serial.println(servo_input[1]);

        drive_servos(servo_input[0], servo_input[1]);

        
      }
      else
      {
        string_temp_input+=c;
      }
        
        
      }
    }
  }
