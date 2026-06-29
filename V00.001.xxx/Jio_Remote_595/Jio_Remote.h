#ifndef _JIO_REMOTE_H
#define _JIO_REMOTE_H



/******* JIO REMOTE start*/


void JioRemote_OnOff(int OnOff)
{
  if(OnOff) // ON
  {
    JIO_REMOTE_ON_OFF_PIN_state = 1;
  }
  else //OFF
  {
    JIO_REMOTE_ON_OFF_PIN_state = 0;
  }

  EEPROM.write(JIO_REMOTE_ON_OFF_PIN_addr, JIO_REMOTE_ON_OFF_PIN_state);
  EEPROM.commit();
  delay(100);
  digitalWrite(JIO_REMOTE_ON_OFF_PIN, JIO_REMOTE_ON_OFF_PIN_state); // Remote in OFF State
}





void Etv()//k
{
  Channel = "ETV";
  Button_click(Jio_TV);
  delay(500);
  Button_click(1);
  Button_click(4);
  Button_click(1);
  Button_click(1);
}

void tv9()//k
{
  Channel = "TV9";
  Button_click(Jio_TV);
  delay(500);
  Button_click(1);
  Button_click(4);
  Button_click(5);
  Button_click(9);
  
}

void GeminiMovies()//k
{
  Channel = "Gemini Movies";
  Button_click(Jio_TV);
  delay(500);
  Button_click(1);
  Button_click(4);
  Button_click(3);
  Button_click(0);
  delay(2000);
  Button_click(Jio_OK);
  
}

void Gemini()//k
{
  Channel = "Gemini";
  Button_click(Jio_TV);
  delay(500);
  Button_click(1);
  Button_click(4);
  Button_click(0);
  Button_click(5);
  delay(2000);
  Button_click(Jio_OK);
  
}

void GeminiComedy()//k
{
  Channel = "Gemini_Comedy";
  Button_click(Jio_TV); delay(500);
  Button_click(1);
  Button_click(4);
  Button_click(4);
  Button_click(2);
  delay(2000);
  Button_click(Jio_OK);
  
}

void ZTelugu() //k
{
  Channel = "Zee Telugu";
  Button_click(Jio_TV); delay(500);
  Button_click(1);
  Button_click(4);
  Button_click(0);
  Button_click(3);
  delay(2000);
  Button_click(Jio_OK);
  
}

void EtvCinema()
{
  Channel = "Etv Cinema";
  Button_click(Jio_TV); delay(500);
  Button_click(1);
  Button_click(4);
  Button_click(6);
  Button_click(9);
  
}

void Sakshi()
{
  Channel = "Sakshi";
  Button_click(Jio_TV); delay(500);
  Button_click(1);
  Button_click(4);
  Button_click(5);
  Button_click(6);
  
}

void ABN()
{
  Channel = "ABN";
  Button_click(Jio_TV); delay(500);
  Button_click(1);
  Button_click(4);
  Button_click(6);
  Button_click(1);
  
}

void EtvPlus()
{
  Channel = "Etv Plus";
  Button_click(Jio_TV); delay(500);
  Button_click(1);
  Button_click(4);
  Button_click(1);
  Button_click(7);
  
}

void ZCinema()
{
  Channel = "Zee Cinema";
  Button_click(Jio_TV); delay(500);
  Button_click(1);
  Button_click(4);
  Button_click(3);
  Button_click(7);
  delay(2000);
  Button_click(Jio_OK);
  
}

void Ntv()
{
  Channel = "NTV";
  Button_click(Jio_TV); delay(500);
  Button_click(1);
  Button_click(4);
  Button_click(6);
  Button_click(0);
  
}

void tv5()
{
  Channel = "TV5";
  Button_click(Jio_TV); delay(500);
  Button_click(1);
  Button_click(4);
  Button_click(5);
  Button_click(8);
  
}

void StarMaMovies()
{
  Channel = "Star Maa Movies";
  Serial.println(Channel);
  Button_click(Jio_TV); delay(500);
  Button_click(1);
  Button_click(4);
  Button_click(3);
  Button_click(2);
  delay(2000);
  Button_click(Jio_OK);
}


void jio_youtube_play()
{
  byte ms = 1100; // ok
  byte ms1 = 150; // scroll

    Channel = "YOUTUBE";

    if(youtube_playing)
    {
      Button_click( Jio_BACK );delay(ms1); Button_click( Jio_BACK ); delay(ms1); // back
      Button_click( Jio_OK ); delay(ms); Button_click( Jio_OK ); delay(ms);// ok
    }
    else // need to cross chek for first youtube set was not working , 2 nd time only working
    {
     Button_click( Jio_HOME ); delay(ms);
     Button_click( Jio_UP ); delay(ms1); Button_click( Jio_UP ); delay(ms1); Button_click( Jio_UP );delay(ms1); Button_click( Jio_UP ); delay(ms1);// up  // for starting point
     Button_click( Jio_DOWN );delay(ms1); Button_click( Jio_DOWN );delay(ms1); Button_click( Jio_DOWN );delay(ms1); Button_click( Jio_DOWN );delay(ms1); //down
     Button_click( Jio_Right );delay(ms1); Button_click( Jio_Right ); delay(ms1);Button_click( Jio_Right );delay(ms1); // right
     if(youtube_init)
     {
      Button_click( Jio_OK ); delay(ms);
      youtube_init = 0;
     }
     Button_click( Jio_OK ); delay(ms); // k ( need 1 more OK, will check)
     Button_click( Jio_Left );delay(ms1); Button_click( Jio_Left );delay(ms1); Button_click( Jio_Left );delay(ms1);Button_click( Jio_Left );delay(ms1);Button_click( Jio_Left );delay(ms1);Button_click( Jio_Left );delay(ms1);// left
     Button_click( Jio_DOWN ); delay(ms1);Button_click( Jio_DOWN ); delay(ms1);Button_click( Jio_DOWN ); delay(ms1);Button_click( Jio_DOWN );delay(ms1); Button_click( Jio_DOWN ); delay(ms1);//down
     Button_click( Jio_Right );delay(ms1); // right
     Button_click( Jio_OK );delay(ms); Button_click( Jio_OK );delay(ms); //ok
     youtube_playing = 1;
    }

}

 /******* JIO REMOTE end*/


void tatasky_remote_function(long int op) // int op
{
  if(op == RED) // || tatasky_remote_select == RED
  {
    youtube_playing = 0;
    Etv();
  }
  else if(op == GREEN)
  {
    youtube_playing = 0;
    EtvPlus();
  }
  else if(op == YELLOW)
  {
    youtube_playing = 0;
    EtvCinema(); //not
  }
  else if(op == BLUE)
  {
   youtube_playing = 0;
    GeminiComedy();
  }
  else if(op == ONE)
  {
    youtube_playing = 0;
    tv9();
  }
  else if(op == TWO)
  {
    youtube_playing = 0;
    Sakshi();   
  }
  else if(op == THREE)
  {
    youtube_playing = 0;
    Ntv();
  }
  else if(op == FOUR)
  {
    tv5(); youtube_playing = 0;
  }
  else if(op == FIVE)
  {
    ABN(); youtube_playing = 0;
  }
  else if(op == SIX)
  {
    GeminiMovies(); youtube_playing = 0;
  }
  else if(op == SEVEN)
  {
    ZCinema(); youtube_playing = 0;
  }
  else if(op == EIGHT)
  {
    StarMaMovies(); youtube_playing = 0;
  }
  else if(op == NINE)
  {
    ZTelugu(); youtube_playing = 0;
  }
  else if(op == ZERO)
  {
    Gemini(); youtube_playing = 0;
  }
  else if(op == FAV)
  {
    jio_youtube_play();
  }



  else if(op == VOL_PLUS)
  {
    Fast_Button_click(Jio_Vol_Up);
  }
  else if(op == VOL_MINUS)
  {
    Fast_Button_click(Jio_Vol_Down);
  }
  else if(op == OK)
  {
    Fast_Button_click( Jio_OK );
  }
  else if(op == UP)
  {
    Fast_Button_click( Jio_UP );
  }
  else if(op == DOWN)
  {
    Fast_Button_click( Jio_DOWN );
  }
  else if(op == LEFT)
  {
    Fast_Button_click( Jio_Left );
  }
  else if(op == RIGTH)
  {
    Fast_Button_click( Jio_Right );
  }
  else if(op == TV)
  {
    Fast_Button_click( Jio_TV );
  }
  else if(op == HOME)
  {
    Fast_Button_click( Jio_HOME ); youtube_playing = 0;
  }
  else if(op == BACK)
  {
    Fast_Button_click( Jio_BACK ); 
  }
  else if(op == i_button)
  {
    pair_remote(); youtube_playing = 0;
  }
  


  else if(op == POWER)
  {
    if(JIO_REMOTE_ON_OFF_PIN_state) // if it ON the turn OFF
     {
    //  Serial.println("JIO_Remote OFF");
       JioRemote_OnOff(0);
     }
     else
     {
     // Serial.println("JIO_Remote_ON");
       JioRemote_OnOff(1);
     }
    
    
  }
  



}

void tatasky_remote_function_loop()
{
  if(results.value > 0)
  {
    tatasky_remote_function( results.value );
    results.value = 0;
  }
  if( tatasky_remote_select > 0 )
  {
    tatasky_remote_function( tatasky_remote_select );
    tatasky_remote_select = 0;
  }
}

/************************* MI Remote Function ***************/


void mi_remote_function(int op)
{
  /*
    if      (  _MI_UP == op ) {       MI_UP();   } 
    else if (  _MI_DOWN == op ) {     MI_DOWN();  }
    else if (  _MI_RIGHT == op ) {    MI_RIGHT();  }
    else if (  _MI_LEFT == op ) {     MI_LEFT();  }
    else if (  _MI_OK == op ) {       MI_OK();   }

    else*/ if (  _MI_POWER == op ) {    MITV_Power_ON_OFF(); } 
    else if (  _JIO_HDMI == op ) {    MITV_HDMI_Input_TATASKY_Selection(); }
    else if (  _PC_HDMI == op ) {     MITV_HDMI_Input_PC_Selection(); }
    else if (  _CCTV_HDMI == op ) {   MITV_HDMI_Input_CCTV_Selection(); }
  
}

#if 0
void mi_remote_function_2(int op)
{
     if     (  _MI_BACK == op ) {     MI_BACK();  }
    else if (  _MI_HOME == op ) {     MI_HOME();  }
    else if (  _MI_VOL_UP == op ) {   MI_VOL_UP();  }
    else if (  _MI_VOL_DOWN == op ) { MI_VOL_DOWN(); }

}
#endif

void mi_remote_function_loop()
{
  if( Mi_remote_select != 0 )
  {

     mi_remote_function( Mi_remote_select );

      Mi_remote_select = 0 ; 
  }
}

#if 0
void mi_remote_function_loop_2()
{
    if( Mi_remote_select2 != 0 )
  {
     mi_remote_function_2( Mi_remote_select2 );
     Mi_remote_select2 = 0 ; 
  }
}
#endif


#endif //_JIO_REMOTE_H