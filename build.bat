@echo off
if exist run.exe ( del run.exe )
g++ -o run.exe main.cpp
if exist run.exe ( run.exe )