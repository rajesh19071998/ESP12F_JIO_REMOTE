#ifndef _APPLICATION_FUNCTIONS_H
#define _APPLICATION_FUNCTIONS_H

// This file related Macros , variables , structures must be declared in  "Application_var.h" file

//#define APPL_DEBUG // for debug


void remote_power_setup()
{
   No_click(); // for 74hc595 ic
   delay(100);

   pinMode(JIO_REMOTE_ON_OFF_PIN, OUTPUT);
   pinMode(TV_SWITCH , INPUT_PULLUP);// manual TV switch

   JIO_REMOTE_ON_OFF_PIN_state = EEPROM.read(JIO_REMOTE_ON_OFF_PIN_addr);
   digitalWrite(JIO_REMOTE_ON_OFF_PIN, JIO_REMOTE_ON_OFF_PIN_state); // Remote in OFF State
   delay(1000);
}
void Application_Setup()
{
  remote_power_setup();
  MI_TV_setup();
  TataSky_Remote_Setup();

  if(OTA_flag == DISABLE)
  { 
   #ifdef _ADD_WEB_SITE
      web_site_setup();
   #endif
  }
  init_timer_delay_sec( SLEEP_TIMER1 , SLEEP1_DELAY_SEC ); // 5 sec
  
  /* Appliction files setups */
  State_machine = 0 ;
  REMOTE_PRESS_DELAY = 5; // 5 sec
  init_timer_delay_sec( REMOTE_PRESS_TIMER , REMOTE_PRESS_DELAY );
  activate_timer(REMOTE_PRESS_TIMER); Serial.println(" INIT timer Activated"); // rjv
  
} //Application_Setup



void All_sleep()
{
  activate_timer(SLEEP_TIMER1);
  Appl_mit_DATA = "Sleep Activated in 5 sec...!";
}


void check_jio_remote_is_on()
{
  if(JIO_REMOTE_ON_OFF_PIN_state == 0 )
  {
   JioRemote_OnOff(1);
   Serial.println("Jio Remote Powered ON");
  }
}

void intial_channel_set()
{
  Channel = "init started don't press any KEY";

 if( State_machine == 0 ) // turn ON TV // 5 sec
 {
   check_jio_remote_is_on();
   REMOTE_PRESS_DELAY = 15 ; // 15 seconds
   init_timer_delay_sec( REMOTE_PRESS_TIMER , REMOTE_PRESS_DELAY );
   MITV_Power_ON_OFF(); // turn ON TV
 }
 else if( (State_machine >= 1) && (State_machine <= 4) ) // 1 , 2 , 3 , 4 -> 4*15 = 60 sec
 {
  Button_click( Jio_OK );
  Button_click( Jio_HOME );
  Serial.println("JIO_OK  JIO_HOME");
 }
 else if( State_machine == 5 )
 {
  REMOTE_PRESS_DELAY = 5; // 5 sec
  init_timer_delay_sec( REMOTE_PRESS_TIMER , REMOTE_PRESS_DELAY );
  Button_click( Jio_TV );
  Serial.println("JIO_TV");
 }
 else if(State_machine == 6)
 {
  REMOTE_PRESS_DELAY = 15; // 15 sec
  init_timer_delay_sec( REMOTE_PRESS_TIMER , REMOTE_PRESS_DELAY );
  Etv();
 }

  else if(State_machine == 7)
 {
  Etv();
 }
  else if(State_machine >= 8)
 {
  REMOTE_PRESS_DELAY = 5; // 5 sec
  init_timer_delay_sec( REMOTE_PRESS_TIMER , REMOTE_PRESS_DELAY );
  State_machine = -1; // reset statemachine

  //Serial.println("Timer Deactivated");
  deactivate_timer(REMOTE_PRESS_TIMER); // state machine stoped
  Channel = "ETV";
 }

  State_machine = State_machine + 1 ;
}


/**************************************************************/
void Timer_timeout_check()
{

  if(is_timer_timeout( SLEEP_TIMER1 )) // 5 sec timer
  {
    deactivate_timer(SLEEP_TIMER1);
#ifdef APPL_DEBUG    
    Serial.println("SLEEP Timer 1 Expired! Going to Sleep...!");
#endif    
    delay(1000);
    ESP.deepSleep(0); 
  } 

  if(is_timer_timeout( REMOTE_PRESS_TIMER )) // 5 sec timer
  {
    //Serial.print("StateMachine : "); Serial.println(State_machine); 
     intial_channel_set();
     
  }

}






void tv_switch_check_loop()
{
  tv_switch_state = digitalRead(TV_SWITCH);

  if(tv_switch_state != tv_switch_state_old)
  {
    if(tv_switch_state == 0 ) // switch is ON
    {
      activate_timer(REMOTE_PRESS_TIMER); // activate timer
      //Update_IP_On_Google_Sheet(); // for login time
      G_sheet_send( G_UPDATE_IP );
      youtube_init = 1;
      //Serial.println("Update G IP 2");
    }
    else  // Switch is OFF
    {
      //Update_LogOutTime_On_Google_Sheet(); // only one time6
      G_sheet_send( G_UPDATE_LOGOUT );
    }
    tv_switch_state_old = tv_switch_state;
  }
}




void Application_loop()
{
  // keep watching the push button:
#ifdef _ADD_WEB_SITE  
   web_site_loop();
#endif

  Timer_timeout_check();

 /* Application loops */
//  mi_remote_function_loop_2();
  tv_switch_check_loop();
  TataSky_Remote_loop();
  tatasky_remote_function_loop();
  mi_remote_function_loop();

}





void mit_commn(String request)
{
  MIT_flag = 2; 
  #ifdef APPL_DEBUG 
  Serial.println(request); 
  #endif 
}

void mit_app_requist_process(AsyncWebServerRequest *web) // refer MIT_APP.h
{
  MIT_flag = DISABLE;
  int paramsNr = web->params(); // number of param

  if(web->params() == 0){return;}
  String request = web->getParam(0)->name(); // first param only // http://192.168.31.146/A?Sleep  // /A?Sleep=1  // /A?Sleep=1&l1on=2
  
  // Serial.print("Parm num : ");Serial.println(web->params());Serial.print("Request : ");Serial.println(request);

  if      ( request == "sleep" ) {mit_commn(request); All_sleep(); }

    else if(request == "sta" )  { mit_commn(request); Appl_mit_DATA = "Current Channel = "+Channel;if(tv_switch_state == 0) Appl_mit_DATA = Appl_mit_DATA + "\nTV is ON"; else Appl_mit_DATA = Appl_mit_DATA + "\nTV is OFF"; }
    else if(request == "init" ) { mit_commn(request); activate_timer(REMOTE_PRESS_TIMER); Appl_mit_DATA = "Init"; }
    else if(request == "r" )  { mit_commn(request); tatasky_remote_select = RED;     Appl_mit_DATA = "ETV"; }
    else if(request == "y" )  { mit_commn(request); tatasky_remote_select = YELLOW;  Appl_mit_DATA = "ETV Cenema";}
    else if(request == "b" )  { mit_commn(request); tatasky_remote_select = BLUE;    Appl_mit_DATA = "GEMENI Comedy"; }
    else if(request == "g" )  { mit_commn(request); tatasky_remote_select = GREEN;    Appl_mit_DATA = "ETV Plus"; }
    else if(request == "1" )  { mit_commn(request); tatasky_remote_select = ONE;     Appl_mit_DATA = "TV9"; }
    else if(request == "2" )  { mit_commn(request); tatasky_remote_select = TWO;     Appl_mit_DATA = "Sakshi"; }
    else if(request == "3" )  { mit_commn(request); tatasky_remote_select = THREE;   Appl_mit_DATA = "NTV"; }
    else if(request == "4" )  { mit_commn(request); tatasky_remote_select = FOUR;    Appl_mit_DATA = "TV5"; }
    else if(request == "5" )  { mit_commn(request); tatasky_remote_select = FIVE;    Appl_mit_DATA = "ABN"; }
    else if(request == "6" )  { mit_commn(request); tatasky_remote_select = SIX;     Appl_mit_DATA = "GEMINI Movies"; }
    else if(request == "7" )  { mit_commn(request); tatasky_remote_select = SEVEN;   Appl_mit_DATA = "Zee Cenema"; }
    else if(request == "8" )  { mit_commn(request); tatasky_remote_select = EIGHT;   Appl_mit_DATA = "Star Maa Movies"; }
    else if(request == "9" )  { mit_commn(request); tatasky_remote_select = NINE;    Appl_mit_DATA = "Zee Telugu"; }
    else if(request == "0" )  { mit_commn(request); tatasky_remote_select = ZERO;    Appl_mit_DATA = "GEMINI"; }

      //Channel
    
    else if(request == "ju" )  { mit_commn(request); tatasky_remote_select = UP;          Appl_mit_DATA = "Jio UP"; }
    else if(request == "jd" )  { mit_commn(request); tatasky_remote_select = DOWN;        Appl_mit_DATA = "Jio DOWN"; }
    else if(request == "jr" )  { mit_commn(request); tatasky_remote_select = RIGTH;       Appl_mit_DATA = "Jio RIGHT"; }
    else if(request == "jl" )  { mit_commn(request); tatasky_remote_select = LEFT;        Appl_mit_DATA = "Jio LEFT"; }
    else if(request == "jb" )  { mit_commn(request); tatasky_remote_select = BACK;        Appl_mit_DATA = "Jio BACK"; }
    else if(request == "jk" )  { mit_commn(request); tatasky_remote_select = OK;          Appl_mit_DATA = "Jio OK"; }
    else if(request == "jh" )  { mit_commn(request); tatasky_remote_select = HOME;        Appl_mit_DATA = "Jio Home"; }
    else if(request == "jtv" )  { mit_commn(request); tatasky_remote_select = TV;         Appl_mit_DATA = "Jio_TV"; }
    else if(request == "jvu" )  { mit_commn(request); tatasky_remote_select = VOL_PLUS;   Appl_mit_DATA = "Jio Vol+"; }
    else if(request == "jvd" )  { mit_commn(request); tatasky_remote_select = VOL_MINUS;  Appl_mit_DATA = "Jio Vol-"; }

    else if(request == "jy" )  { mit_commn(request); tatasky_remote_select = FAV;  Appl_mit_DATA = "Jio Youtube"; }
   
    else if(request == "jon" )  { mit_commn(request); JioRemote_OnOff(1); Appl_mit_DATA = "Jio Remote Poewer ON "; }
    else if(request == "joff" )  { mit_commn(request); JioRemote_OnOff(0); Appl_mit_DATA = "Jio Remote Poewer OFF "; }
    else if(request == "jiopair" )  { mit_commn(request); tatasky_remote_select = i_button;  Appl_mit_DATA = "Jio Remote Pairing it will take 5 min"; } 

    else if(request == "mp" )  { mit_commn(request); Mi_remote_select = _MI_POWER;     Appl_mit_DATA = "MI TV Power ON/OFF";  }

#if 0    
    else if(request == "mu" )  { mit_commn(request); Mi_remote_select = _MI_UP;        Appl_mit_DATA = "MI_TV UP";  }
    else if(request == "md" )  { mit_commn(request); Mi_remote_select = _MI_DOWN;      Appl_mit_DATA = "MI_TV DOWN";  }
    else if(request == "mr" )  { mit_commn(request); Mi_remote_select = _MI_RIGHT;     Appl_mit_DATA = "MI_TV RIGHT";  }
    else if(request == "ml" )  { mit_commn(request); Mi_remote_select = _MI_LEFT;      Appl_mit_DATA = "MI_TV LEFT";  }
    else if(request == "mb" )  { mit_commn(request); Mi_remote_select2 = _MI_BACK;      Appl_mit_DATA = "MI_TV BACK";  }
    else if(request == "mk" )  { mit_commn(request); Mi_remote_select = _MI_OK;        Appl_mit_DATA = "MI_TV OK";  }
    else if(request == "mh" )  { mit_commn(request); Mi_remote_select2 = _MI_HOME;      Appl_mit_DATA = "MI_TV HOME";  }
    else if(request == "mvu" )  { mit_commn(request); Mi_remote_select2 = _MI_VOL_UP;   Appl_mit_DATA = "MI_TV Vol+";  }
    else if(request == "mvd" )  { mit_commn(request);  Mi_remote_select2 = _MI_VOL_DOWN; Appl_mit_DATA = "MI_TV Vol-";  }
#endif

    else if(request == "jiohdmi" )  { mit_commn(request); Mi_remote_select = _JIO_HDMI ;  Appl_mit_DATA = "Jio HDMI";  }
    else if(request == "pchdmi" )  { mit_commn(request);  Mi_remote_select = _PC_HDMI ;   Appl_mit_DATA = "PC HDMI";  }
    else if(request == "cctvhdmi" )  { mit_commn(request); Mi_remote_select = _CCTV_HDMI; Appl_mit_DATA = "CCTV Camera HDMI";  }

}




#endif //_APPLICATION_FUNCTIONS_H
