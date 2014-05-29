// SolidBackground.cpp 

#include "pch.h" 
#include "SolidBackground.h"  

SolidBackground::SolidBackground(D2D1::ColorF col): color(col) { }  

void SolidBackground::Render(  Microsoft::WRL::ComPtr<ID2D1DeviceContext> context)
{ 
context->Clear(color); // Clear the screen to the color 
} 