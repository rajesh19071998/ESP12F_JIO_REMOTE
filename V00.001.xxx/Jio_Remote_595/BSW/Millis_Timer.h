#ifndef _MILLIS_TIMER_H
#define _MILLIS_TIMER_H

//#define MAX_TIMERS 10 // Header_files.h file
//#define _TIMER_DEBUG

typedef struct
{
  unsigned long previousMillis;
  unsigned long delayMillis;

  bool timeout;
  bool active;
}MillisTimer;

MillisTimer Timer[MAX_TIMERS] = {0};

void init_timer_delay_sec(byte timer_num , unsigned int seconds )
{
  unsigned long millis = ( seconds * 1000 ) ; // 1000 millis = 1 second
  if(timer_num < MAX_TIMERS )
  {
    Timer[timer_num].delayMillis = millis;
  }
}

bool is_timer_timeout(byte timer_num)
{
  bool timeout_status = 0; // 0 No , 1 YES
  if(timer_num < MAX_TIMERS )
  {
    if(Timer[timer_num].timeout == 1)
    {
      timeout_status = 1;
      Timer[timer_num].timeout = 0;    
    }
  }  
  return timeout_status ;
}



void activate_timer(byte timer_num)
{
  if(timer_num < MAX_TIMERS )
  {
    Timer[timer_num].active = 1;
    Timer[timer_num].timeout = 0;
    Timer[timer_num].previousMillis = millis();
#ifdef _TIMER_DEBUG
    Serial.println(Timer[timer_num].previousMillis);
    Serial.print("Timer Activated in Millis Timer = ");
    Serial.println(timer_num);
#endif
  } 
}

void deactivate_timer(byte timer_num)
{
  if(timer_num < MAX_TIMERS )
  {
    Timer[timer_num].active = 0;
    Timer[timer_num].timeout = 0;
#ifdef _TIMER_DEBUG
    Serial.print("Timer Deactivated in Millis Timer = ");
    Serial.println(timer_num);
#endif
  }
}

void Timer_loop()
{
  for(byte i = 0 ; i < MAX_TIMERS ; i++)
  {
    
    if(Timer[i].active == 1)
    {
      if( ( Timer[i].previousMillis + Timer[i].delayMillis ) <= millis() )
      {
        Timer[i].timeout = 1;
        Timer[i].previousMillis = millis();

#ifdef _TIMER_DEBUG
          Serial.print( (Timer[i].delayMillis) / 1000 );
          Serial.println(" Sec");
         // Serial.println(Timer[i].previousMillis);
        
          Serial.print("Timer : ");
          Serial.print(i);
          Serial.println(" Expired..!");
#endif
      }
    }

  }



}


















#endif //_MILLIS_TIMER_H
