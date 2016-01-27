#include <Servo.h>

Servo servo1;

int servo_pin = 9;



void pid_servo(int servo_pin, int final_angle)
{
  

  int prev_error = final_angle;
  int curr_error = final_angle;
  float e_differential = final_angle;
  int pos = 0;
  float kp = 0.3;
  float ki = 0.2;
  float kd = 3;
  float dt = 15.0;
  float e_integral = e_differential*dt;
  float e_diff = 0.0;
  float u = 0.0;
 
  
  while(curr_error!=0)
  {
    delay(dt);
    pos +=1;
    servo1.write(pos+((int)u%(300)/(int)dt));

    // Differential part
    prev_error = curr_error;
    curr_error = final_angle - pos;
    e_differential = ((curr_error - prev_error)/dt)*1000;

    // Integral part
    e_integral = e_integral + ((dt*curr_error)/1000);

    // Final control signal
    u = (kp*curr_error) + (kd*e_differential) + (ki*e_integral);

    // Adjusting pos with control signal
//    pos = pos + int(floor(((int)u%600)/dt));

    
    Serial.println(u);


  }
  
}

void setup()
{
  Serial.begin(9600);
  servo1.attach(servo_pin);
  // Set initial angle to zero
  servo1.write(0);
  delay(2000);
  pid_servo(9, 180);
  
}

void loop()
{


}
