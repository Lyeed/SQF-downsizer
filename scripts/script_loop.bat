@echo off

rem This shell script can be use to create a duplicate of your project's folder
rem The new folder will be loop through : .sqf and .hpp files size will be reduced
rem The final stage consist of building the folder with AddonBuider and here you have your mission or addon 
rem .git will also be removed from the final folder

rem Path of your source folder.
rem This folder will not be modified
set source_folder="test_folder"

rem New folder name. It will be created and modified.
rem Pack this folder after process to obtain a clean pbo
set dest_folder="test_pbo"

rem Path to the downsize's executable
rem If you place it in the same folder as the bat script just put 'downsize.exe' otherwise put the full path
set exe_file="C:/path/full/to/exec/downsize.exe"
rem set exe_file="downsize.exe"

rem #########
rem DO NOT EDIT BELOW UNLESS YOU KNOW WHAT YOU ARE DOING
rem #########

if exist %dest_folder% (rmdir /Q /S %dest_folder%)

xcopy %source_folder% %dest_folder% /E /Y /I

if exist "%dest_folder%/.git" (rmdir /Q /S "%dest_folder%/.git/")

FORFILES /p "%dest_folder%" /m "config.cpp" /s /C "cmd /c %exe_file% @path @path"
FORFILES /p "%dest_folder%" /m "description.ext" /s /C "cmd /c %exe_file% @path @path"
FORFILES /p "%dest_folder%" /m "*.hpp" /s /C "cmd /c %exe_file% @path @path"
FORFILES /p "%dest_folder%" /m "*.sqf" /s /C "cmd /c %exe_file% @path @path"
