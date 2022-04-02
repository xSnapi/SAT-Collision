-- premake5.lua
workspace "Collision with SAT"
   startproject "SAT"
   architecture "x64"
   configurations {
      "Debug", 
      "Release" 
   }

   filter { "platforms:Win64" }
      system "Windows"
      
include "SAT"