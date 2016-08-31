
uint8_t latchCom = 2;//common
uint8_t clockCom = 3;
uint8_t dataCom = 1;

uint8_t i;


uint8_t latchLeft = 5;//left
uint8_t clockLeft = 6;
uint8_t dataLeft = 4;

uint8_t latchRight = 8;//right
uint8_t clockRight= 9;
uint8_t dataRight = 7;

uint8_t plx = 0;
uint8_t ply = 0;
uint8_t prx = 0;
uint8_t pry = 0;

uint8_t frame1[] = {7,2,6,3,7,3,8,3,5,4,6,4,7,4,8,4,9,4,5,5,6,5,7,5,8,5,9,5,6,6,7,6,8,6,7,7,4,8,5,8,9,8,10,8,5,9,6,9,7,9,8,9,9,9};
uint8_t frame2[] = {7,3,6,4,7,4,8,4,6,5,7,5,8,5,7,6,4,8,5,8,9,8,10,8,5,9,6,9,7,9,8,9,9,9};
uint8_t frame3[] = {6,4,7,4,8,4,6,5,7,5,8,5,4,8,5,8,9,8,10,8,5,9,6,9,7,9,8,9,9,9};

uint8_t normal_blink1[] = {7, 9, 8, 9, 6, 8, 7, 8, 8, 8, 9, 8, 5, 7, 6, 7, 7, 7, 8, 7, 9, 7, 10, 7, 5, 6, 6, 6, 7, 6, 8, 6, 9, 6, 10, 6, 5, 5, 6, 5, 7, 5, 8, 5, 9, 5, 10, 5, 5, 4, 6, 4, 7, 4, 8, 4, 9, 4, 10, 4, 6, 3, 7, 3, 8, 3, 9, 3, 7, 2, 8, 2};
uint8_t normal_blink2[] = {5, 7, 6, 7, 7, 7, 8, 7, 9, 7, 10, 7, 5, 6, 6, 6, 7, 6, 8, 6, 9, 6, 10, 6, 5, 5, 6, 5, 7, 5, 8, 5, 9, 5, 10, 5, 5, 4, 6, 4, 7, 4, 8, 4, 9, 4, 10, 4};
uint8_t normal_blink3[] = {5, 6, 6, 6, 7, 6, 8, 6, 9, 6, 10, 6, 5, 5, 6, 5, 7, 5, 8, 5, 9, 5, 10, 5};
uint8_t happy[] = {6, 9, 7, 9, 8, 9, 9, 9, 5, 8, 6, 8, 7, 8, 8, 8, 9, 8, 10, 8, 4, 7, 5, 7, 10, 7, 11, 7, 3, 6, 4, 6, 11, 6, 12, 6, 3, 5, 4, 5, 11, 5, 12, 5};
uint8_t emoless[] = {4, 6, 5, 6, 6, 6, 7, 6, 8, 6, 9, 6, 10, 6, 11, 6, 4, 5, 5, 5, 6, 5, 7, 5, 8, 5, 9, 5, 10, 5, 11, 5};

uint8_t angry_left[] = {6, 9, 7, 9, 8, 9, 9, 9, 7, 8, 8, 8, 9, 8, 10, 8, 9, 7, 10, 7, 11, 7, 10, 6, 11, 6, 12, 6, 12, 5, 13, 5};
uint8_t angry_right[] = {6, 9, 7, 9, 8, 9, 9, 9, 5, 8, 6, 8, 7, 8, 8, 8, 4, 7, 5, 7, 6, 7, 3, 6, 4, 6, 5, 6, 2, 5, 3, 5};

uint8_t sad_left[] = {9, 9, 10, 9, 11, 9, 12, 9, 8, 8, 9, 8, 10, 8, 11, 8, 7, 7, 8, 7, 9, 7, 6, 6, 7, 6, 8, 6, 5, 5, 6, 5, 5, 4};
uint8_t sad_right[] = {3, 9, 4, 9, 5, 9, 6, 9, 4, 8, 5, 8, 6, 8, 7, 8, 6, 7, 7, 7, 8, 7, 7, 6, 8, 6, 9, 6, 9, 5, 10, 5, 10, 4};


void setup()
{

  //set pins to output so you can control the shift register
  pinMode(latchCom, OUTPUT);//common
  pinMode(clockCom, OUTPUT);
  pinMode(dataCom, OUTPUT);

  pinMode(latchLeft, OUTPUT);//left 
  pinMode(dataLeft, OUTPUT);
  pinMode(clockLeft, OUTPUT);

  pinMode(latchRight, OUTPUT);//right 
  pinMode(dataRight, OUTPUT);
  pinMode(clockRight, OUTPUT);

}

void row(uint8_t a,uint8_t b)
{
      shiftOutc(a); 
      shiftOutc(b); 
}

void right(uint8_t a,uint8_t b)
{
    shiftOutr(a); 
    shiftOutr(b); 
}

void left(uint8_t a,uint8_t b)
{
      shiftOutl(a);
      shiftOutl(b);
}

void clear_left()
{

  delatch();
  left(0,0);
  latch();

}

void clear_right()
{

  delatch();
  right(0,0);
  latch();

}


void clear_all()
{

  delatch();
  left(0,0);
  right(0,0);
  latch();

}

uint8_t power(uint8_t x, uint8_t y)
{
  if (y==0)
    return(1);
 
  else
    return(power(x,y-1)*x);
}

void light_led_left(uint8_t x, uint8_t y)
{

  uint8_t ya = 0;
  uint8_t yb = 0;
  uint8_t xa = 0;
  uint8_t xb = 0;
  
  //First we map the y coordinates

  if(y<=8)
  {
    ya = 255;
    yb = power(2, y-1)^255;
  }
  else
  {
    yb = 255;
    y = y-8;
    ya = power(2, y-1)^255;
    
  }

  // Mapping the x coordinates
  if(x<=8)
  {
    xb = 0;
    xa = power(2, 8-x);
  }
  else
  {
    xa = 0;
    x = x-8;
    xb = power(2, 8-x);
  }

  //Lighting up
  delatch();
  row(ya, yb);
  left(xb, xa);
  latch();

}


void light_led_right(uint8_t x, uint8_t y)
{

  uint8_t ya = 0;
  uint8_t yb = 0;
  uint8_t xa = 0;
  uint8_t xb = 0;
  
  //First we map the y coordinates

  if(y<=8)
  {
    ya = 255;
    yb = power(2, y-1)^255;
  }
  else
  {
    yb = 255;
    y = y-8;
    ya = power(2, y-1)^255;
    
  }

  // Mapping the x coordinates
  if(x<=8)
  {
    xb = 0;
    xa = power(2, 8-x);
  }
  else
  {
    xa = 0;
    x = x-8;
    xb = power(2, 8-x);
  }

  //Lighting up
  delatch();
  row(ya, yb);
  right(xb, xa);
  latch();

}

void light_led(uint8_t x, uint8_t y)
{

  uint8_t ya = 0;
  uint8_t yb = 0;
  uint8_t xa = 0;
  uint8_t xb = 0;
  
  //First we map the y coordinates

  if(y<=8)
  {
    ya = 255;
    yb = power(2, y-1)^255;
  }
  else
  {
    yb = 255;
    y = y-8;
    ya = power(2, y-1)^255;
    
  }

  // Mapping the x coordinates
  if(x<=8)
  {
    xb = 0;
    xa = power(2, 8-x);
  }
  else
  {
    xa = 0;
    x = x-8;
    xb = power(2, 8-x);
  }

  //Lighting up
  delatch();
  row(ya, yb);
  left(xb, xa);
  right(xb,xa);
  latch();

}


void delatch()//original
  {
    PORTD=PORTD & B11011011;
    PORTB=PORTB & B11111110;
  }

void latch()
  {
    PORTD=PORTD | B00100100;
    PORTB=PORTB | B00000001;
  }


  
  void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val)
{
    uint8_t i;

    for (i = 0; i < 8; i++)  {
        if (bitOrder == LSBFIRST)
            digitalWrite(dataPin, !!(val & (1 << i)));
        else    
            digitalWrite(dataPin, !!(val & (1 << (7 - i))));

        digitalWrite(clockPin, HIGH);
        digitalWrite(clockPin, LOW);        
    }
}

  void shiftOutc(uint8_t val)
{
    uint8_t i;

    for (i = 0; i < 8; i++)  {
      if(!!(val & (1 << (7 - i))))
      PORTD=PORTD|B00000010;
      else 
      PORTD=PORTD&B11111101;
        PORTD=PORTD|B00001000;  
        delayMicroseconds(1);    
        PORTD=PORTD&B11110111;    
    }
}

  void shiftOutl(uint8_t val)
{
    uint8_t i;

    for (i = 0; i < 8; i++)  {
        if (!!(val & (1 << i)))
            PORTD=PORTD|B00010000;
        else 
            PORTD=PORTD&B11101111;
        PORTD=PORTD|B01000000;  
        delayMicroseconds(1);    
        PORTD=PORTD&B10111111;       
    }
}

  void shiftOutr(uint8_t val)
{
    uint8_t i;

    for (i = 0; i < 8; i++)  {
        if (!!(val & (1 << i)))
        PORTD=PORTD|B10000000;
        else 
        PORTD=PORTD&B01111111;
        PORTB=PORTB|B00000010;  
        delayMicroseconds(1);    
        PORTB=PORTB&B11111101; 
        
    }
}

void normal_blink_emotion()
{
   int r = random(1, 13);
   int del_a = 0;
   if(r>=1&&r<=3)
   {
      del_a = 500;
   }
   if(r>=4&&r<=9)
   {
      del_a = 3000;
   }
   if(r>=10&&r<=12)
   {
      del_a = 6000;
   }

   int del_b = 50;
   int del_c = 20;

   
   int start_time = millis();
    while(1)
    {
      for(i=0;i<sizeof(normal_blink1)/sizeof(uint8_t);i=i+2)
        {
    
          light_led(normal_blink1[i],normal_blink1[i+1]);
          clear_all();
        }
          int curr_time = millis();
          int del = curr_time - start_time;
          if(del>del_a)
            break;
    }
    
    
    start_time = millis();
    while(1)
    {
      for(i=0;i<sizeof(normal_blink2)/sizeof(uint8_t);i=i+2)
        {  
          light_led(normal_blink2[i],normal_blink2[i+1]);
          clear_all();
        }
          int curr_time = millis();
          int del = curr_time - start_time;
          if(del>del_b)
            break;
    }
    
    start_time = millis();
    while(1)
    {
      for(i=0;i<sizeof(normal_blink3)/sizeof(uint8_t);i=i+2)
        {
          light_led(normal_blink3[i],normal_blink3[i+1]);
          clear_all();
        }
          int curr_time = millis();
          int del = curr_time - start_time;
          if(del>del_c)
            break;
    }
  
}

void happy_emotion()
{
  
    for(i=0;i<sizeof(happy)/sizeof(uint8_t);i=i+2)
    {
      light_led(happy[i],happy[i+1]);
      clear_all();
    }
 
}

void emotionless_emotion()
{
  
    for(i=0;i<sizeof(emoless)/sizeof(uint8_t);i=i+2)
    {
      light_led(emoless[i],emoless[i+1]);
      clear_all();
    }
 
}

void angry_emotion()
{
  
    for(i=0;i<sizeof(angry_left)/sizeof(uint8_t);i=i+2)
    {
      light_led_left(angry_left[i], angry_left[i+1]);
      clear_all();
    }

    for(i=0;i<sizeof(angry_right)/sizeof(uint8_t);i=i+2)
    {
      light_led_right(angry_right[i], angry_right[i+1]);
      clear_all();
    }
 
}

void sad_emotion()
{
  
    for(i=0;i<sizeof(sad_left)/sizeof(uint8_t);i=i+2)
    {
      light_led_left(sad_left[i], sad_left[i+1]);
      clear_all();
    }

    for(i=0;i<sizeof(sad_right)/sizeof(uint8_t);i=i+2)
    {
      light_led_right(sad_right[i], sad_right[i+1]);
      clear_all();
    }
 
}

void loop() 
{
//    normal_blink_emotion();
//    happy_emotion();
//    emotionless_emotion();
//    angry_emotion();
//    sad_emotion();
}
  
 




