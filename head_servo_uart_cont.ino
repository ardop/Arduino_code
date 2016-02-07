#include <Servo.h>

int coord[2];
Servo hor,ver;

int hor_mov = 1;
int ver_mov = 1;

// starting positions of the servos
int hor_start_angle = 90;
int ver_start_angle = 80;

// current angles of the servos
int hor_curr_angle = 90;
int ver_curr_angle = 80;

int thresh = 30;

bool read_serial()
{
  String input = "";
 

  String string_temp_input = "";
  int temp_input;
  int pos = 0;

  while(Serial.available()>0)
  {
    delay(1);
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
    return true;
  }

  else
  {
    return false;
  }



  
}

void setup() 
{
  hor.attach(11);
  ver.attach(3);
  
  Serial.begin(57600);

  hor.write(hor_start_angle);
  ver.write(ver_start_angle);
  delay(1000);

   read_serial();
   Serial.println(coord[0]);
   Serial.println(coord[1]);

  



}

void loop()
{
  
   bool res = read_serial();

   if(res)
   {

    if(coord[0] < 300-thresh)
    {
      hor_curr_angle+=hor_mov;
      hor.write(hor_curr_angle);
    }
    else if(coord[0] > 300+thresh)
    {
      hor_curr_angle-=hor_mov;
      hor.write(hor_curr_angle);
    }

    if(coord[1]<220 - thresh)
    {
      ver_curr_angle-=ver_mov;
      ver.write(ver_curr_angle);
    }
    else if(coord[1] > 220+thresh)
    {
      ver_curr_angle+=ver_mov;
      ver.write(ver_curr_angle);
    }
   }

    

}
