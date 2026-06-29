#ifndef _APPLICATION_VARIABLES_H
#define _APPLICATION_VARIABLES_H


String APPL_VER = "V00.001.002"; // 29 - 06 - 2026

/* init Timers */
#if 0
 #define MAX_TIMERS 4  ( increment this macro in PIN_CONFIG.h)
 #endif
/*0 to 3 reserved , so use from 4 */
#define REMOTE_PRESS_TIMER 4

/* timer delay in seconds */
/*if fixed value use macro , else use variable */

int REMOTE_PRESS_DELAY = 5 ; // 5 sec



/********  variables   ********************/

int JIO_REMOTE_ON_OFF_PIN_addr = 1; //EEPROM
int JIO_REMOTE_ON_OFF_PIN_state = 0; //OFF

int tv_switch_state = 1;
int tv_switch_state_old = -1;

String Channel = "";

int Mi_remote_select = 0 ;
//int Mi_remote_select2 = 0;
int youtube_playing = 0;
bool youtube_init = 0;

long int tatasky_remote_select = 0;

int State_machine = 255 ; // invalid state




/************* cmd **************************/
const String MIT_Appl_cmd = 
"Appl CMD's  xx.xx.xx.xx/A?\n"
"==========================\n"

#if defined(ESP8266)  // Because of Low RAM
 "\nr ETV"
 "\ng"
 "\ny"
 "\nb"
 "\n1"
 "\n2"
 "\n3"
 "\n4"
 "\n5"
 "\n6"
 "\n7"
 "\n8"
 "\n9"
 "\n0"
 "\nsta current Chan"
 
 "\n\njon JioRemote ON"
 "\njoff JioRemote OFF"
 "\njiopair"
 "\njtv jioTV"
 "\njh Home"
 "\njb Back"
 "\nju up"
 "\njd Down"
 "\njl Left"
 "\njr Right"
 "\njk OK"
 "\njvu Vol+"
 "\njvd Vol-"
 "\njy youtube"

  "\n\nmp -> MI TV Power ON/OFF"
  "\njiohdmi"
  "\npchdmi"
  "\ncctvhdmi"
  "\n\ninit"
#endif  // Esp 8266

#if defined(ESP32)
 "\n r -> ETV"
 "\n g -> ETV_Plus "
 "\n y -> ETV_Cinima"
 "\n b -> Gemini_Comedy"
 "\n 1 -> TV9"
 "\n 2 -> Shakshi"
 "\n 3 -> Ntv"
 "\n 4 -> Tv5"
 "\n 5 -> ABN"
 "\n 6 -> GeminiMovies"
 "\n 7 -> ZeeCinima"
 "\n 8 -> StarMaaMovies"
 "\n 9 -> ZeeTelugu"
 "\n 0 -> Gemini"
 "\n\n JIO REMOTE \n--------------------------\n"
 "\n jon -> Jio Remote ON"
 "\n joff -> Jio Remote OFF"
 "\n jiopair -> jio remote will pair"
 "\n jtv -> jio TV"
 "\n jh -> jio Home"
 "\n jb -> jio Back"
 "\n ju -> jio up"
 "\n jd -> jio Down"
 "\n jl -> jio Left"
 "\n jr -> jio Right"
 "\n jk -> jio OK"
 "\n jvu -> jio Volume up"
 "\n jvd -> jio Volume Down"
 "\n jy -> jio Youtube Recent video Play"

  "\n\n MI TV REMOTE \n--------------------------\n"
  "\n mp -> MI TV Power ON/OFF"
  "\n jiohdmi -> Jio HDMI will Select"
  "\n pchdmi -> PC HDMI will Select"
  "\n cctvhdmi -> CCTV HDMI will Select"
  "\n\n init -> Remote init steps for ETV Select and tv ON"
#endif // ESP32

"\n";





#endif //_APPLICATION_VARIABLES_H