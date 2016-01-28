#include <Servo.h>

Servo servo1;

// Servo pwm pin
int servo_pin = 9;

void servo_smooth(int final_angle, int smooth_percent_start, int smooth_percent_end, int dt)
{
  int start_smooth = (int)((smooth_percent_start/100.0)*final_angle);
  int end_smooth = (int)((smooth_percent_end/100.0)*final_angle);


  int pos = 0;

  while(pos!=final_angle)
  {
    if(pos<=start_smooth)
    {
      pos++;
    }
    else if(pos>=(final_angle-end_smooth))
    {
      pos++;
    }
    else
    {
      pos+=2;
    }
  

    servo1.write(pos);
    delay(dt);

    Serial.print(start_smooth);
    Serial.print(", ");
    Serial.print(end_smooth);
    Serial.print(", ");
    Serial.print(pos);
    Serial.println();
    
  }

}

void setup()
{
  Serial.begin(9600);
  servo1.attach(servo_pin);
  servo1.write(0);
  delay(2000);

  servo_smooth(180, 20.0, 5.0, 15);
  
}


void loop()
{

}
