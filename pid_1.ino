#include <Servo.h>

Servo servo1;

// Servo pwm pin
int servo_pin = 9;


// Function that turns the servo to an angle final_angle
void pid_servo(int final_angle)
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

  // Slice of time taken
  float dt = 15.0;

  // Integral of the errors at all instances of time till the present time
  float e_integral = e_differential*dt;
  float u = 0.0;
 
  
  while(curr_error!=0)
  {
    // Delay
    delay(dt);

    // updating position
    pos +=1;

    // Writing servo position depending on the control signal from the PID regulator output
    servo1.write(pos+((int)u%(300)/(int)dt));

    // Differential part
    prev_error = curr_error;
    curr_error = final_angle - pos;
    e_differential = ((curr_error - prev_error)/dt)*1000;

    // Integral part
    e_integral = e_integral + ((dt*curr_error)/1000);

    // Final control signal
    u = (kp*curr_error) + (kd*e_differential) + (ki*e_integral);

    // The control signal does not change the value of 'pos' directly. Instead, its value is added to the value that the servo must be turned to 
    // at that instant of time

    // For debugging
    Serial.println(u);


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
  pid_servo(180);
  
}

void loop()
{


}
