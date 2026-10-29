@echo off
 g++ -std=c++17 -Wall -Wextra main.cpp -o main.exe
 if errorlevel 1 pause & exit /b 1
 main.exe
 pause
