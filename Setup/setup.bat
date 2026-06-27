@echo off
REM Choose one of the following Redistributable files to install
::vc_redist.x86.exe    REM remove leading :: to install Redistributable for x86
vc_redist.x64.exe    REM remove leading :: to install Redistributable for x64
::vc_redist.arm64.exe  REM remove leading :: to install Redistributable for ARM64
mkdir "C:\Program Files\bonk_game"

copy bonk_game.exe "C:\Program Files\bonk_game"