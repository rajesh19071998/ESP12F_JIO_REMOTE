@echo off
setlocal enabledelayedexpansion

REM clone to Base_code folder
REM git submodule add https://github.com/rajesh19071998/Basic_code_for_Esp12F_Esp32.git Base_code
REM git submodule init
REM git submodule update
echo Cloning Basic_code_for_Esp12F_Esp32 Repo
git clone https://github.com/rajesh19071998/Basic_code_for_Esp12F_Esp32.git Base_code

IF NOT %3==master (
cd Base_code
git checkout %3
git pull
cd /d %~dp0
)

REM set bsw_version=V00.003.000
set bsw_version=V+
REM set selected_version=V+
set selected_version=%2
echo %bsw_version%
REM ******** Base_code Latest Version Folder Search **********************************************

  cd Base_code

  set folderCnt=0
  for /f "eol=: delims=" %%F in ('dir /b /ad *') do (
    set /a folderCnt+=1
    set "folder!folderCnt!=%%F"
  )

  set bsw_version=!folder%folderCnt%!

REM ************************************************************************************
REM **** GOTO Batch file located path *****
cd /d %~dp0

REM set bsw_version=V00.000.001

IF NOT %selected_version%==V+ (
set bsw_version=%selected_version%
)
echo Selected BSW vesion = %bsw_version%

IF NOT EXIST "*.ino" (
echo INO file was not availbale so creating %1 New project
REM copy all files to current folder includeing folders
xcopy "Base_code\%bsw_version%\Src\Basic_code_for_Esp12f_Esp32" "%1" /E /I /H /C /Y

cd %1
REN *.ino %1.ino

echo %1 New Project Base was Created....!
cd /d %~dp0
REM delete Base_code folder in base location
RD /S /Q Base_code
pause
Exit
)

IF EXIST "Base_code\%bsw_version%\Src\Basic_code_for_Esp12f_Esp32\BSW" (
REM Delete BSW folder
RD BSW
echo Deleted Existing BSW folder...!

mkdir BSW
xcopy "Base_code\%bsw_version%\Src\Basic_code_for_Esp12f_Esp32\BSW" "BSW" /E /I /H /C /Y

echo Only BSW folder was updated...!

REM delete Base_code folder in base location
RD /S /Q Base_code
) ELSE (
echo BSW folder was not Available in Base_code\%bsw_version%\Src\Basic_code_for_Esp12f_Esp32 Location ......!
)
pause