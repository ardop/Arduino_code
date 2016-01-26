int latch_left = 8;
int latch_right = 11;

int clk_left = 9;
int clk_right = 12;

// Data pins to the right and left eyes
int dat_left = 10;
int dat_right = 13;

// The rows (c's) of the right and left eyes are shorted
// The left eye has 3 registers --> for the anodes and cathodes
// As the c's are shorted, the right eye has only 2 registers to control the 14 anodes

//Stores the current values in the registers
int num_reg1 = 0;
int num_reg2 = 0;
int num_reg3 = 0;
int num_reg4 = 0;
int num_reg5 = 0;

void setup()
{
  pinMode(latch_left, OUTPUT);
  pinMode(latch_right, OUTPUT);
  pinMode(clk_left, OUTPUT);
  pinMode(clk_right, OUTPUT);
  pinMode(dat_left, OUTPUT);
  pinMode(dat_right, OUTPUT);

}

// Function to write into a shift register
void write_register(int reg_number, int value)
{
  // reg_number is the register number
  if(reg_number<=3)
  {
    //left eye
    digitalWrite(latch_left, LOW);
    shiftOut(dat_left, clk_left, LSBFIRST, value);
    digitalWrite(latch_left, HIGH);
  }
  else
  {
    digitalWrite(latch_right, LOW);
    shiftOut(dat_right, clk_right, LSBFIRST, value);
    digitalWrite(latch_right, HIGH);
  }

  // Updating the values of the current registers
}

void loop() {
  

}
