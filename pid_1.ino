#include <Servo.h>


Servo servo1;

// Servo pwm pin
int servo_pin = 9;


// Function that turns the servo to an angle final_angle
void pid_servo(int final_angle, int dt)
{
  
  //Initializing parameters

  //Errors
  int prev_error = final_angle;
  int curr_error = final_angle;
  
  // Instantaneous error differential
  float e_differential = final_angle;
  
  // Current position of the servo
  int pos = 0;

  // PID regulator parameters
  float kp = 0.3;
  float ki = 0.2;
  float kd = 3;


  // Integral of the errors at all instances of time till the present time
  float e_integral = e_differential*dt;
  float u = 0.0;
  float first_u = 0.0;


  int count = 0;

  int int_u = 0;
  int int_first_u = 0;

  int prev_mod = 0;
  int mod = 0;
  
  int actual_pos = 1;

  int actual_pos_increment = 0;



 
  
  while(actual_pos<final_angle)
  {
    // Delay
    delay(dt);

    // updating position
    pos +=1;

    // Updating actual angle
    actual_pos = actual_pos  + actual_pos_increment + 1;

    // Writing servo position depending on the control signal from the PID regulator output
    servo1.write(actual_pos);

    // Differential part
    prev_error = curr_error;
    curr_error = final_angle - pos;
    e_differential = ((curr_error - prev_error)/dt)*1000;

    // Integral part
    e_integral = e_integral + ((dt*curr_error)/1000);

    if(count)
    {
      prev_mod = int_u%int_first_u;
    }

    // Final control signal
    u = (kp*curr_error) + (kd*e_differential) + (ki*e_integral);

    int_u = (int)u;

    // Initializing first u
    if(!count)
    {
      first_u = u;
      count = 1;
    }
   

    int_first_u = (int)first_u;


    //Taking lowest value of u so that the mod computes correctly.
    if(int_u<int_first_u)
    {
      int_first_u = int_u;
    }

    mod = int_u%int_first_u;

    if(count)
    {
      if(mod>prev_mod)
      {
        actual_pos_increment = 1;
      }
      else if(mod<prev_mod)
      {
        actual_pos_increment = 0;
      }
    }



    

    // The control signal does not change the value of 'pos' directly. Instead, its value is added to the value that the servo must be turned to 
    // at that instant of time

    // For debugging
    Serial.print(u);
    Serial.print(", ");
    Serial.print(mod);
    Serial.print(", ");
    Serial.print(prev_mod);
    Serial.print(", ");
    Serial.print(actual_pos_increment);
    Serial.println();


  }
  
}

void setup()
{
  // Begin serial monitor for debugging purposes
  Serial.begin(9600);

  // Attaching the servo to the pwm pin
  servo1.attach(servo_pin);
  
  // Set initial angle to zero
  servo1.write(0);
  delay(2000);

  // PID control to turn the motor by an angle
  pid_servo(30, 15);
  
}

void loop()
{


}
