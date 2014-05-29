// SolidBackground.h 

#pragma once 
#include "DirectXBase.h" 

// Defines a background consisting of a solid color 
class SolidBackground
{ 
private: 
	D2D1::ColorF color; // The color of this background 
public: 
 // Creates a new SolidBackground set to the specified color 
 SolidBackground(D2D1::ColorF color); 

 // Draw the background 
 void Render(Microsoft::WRL::ComPtr<ID2D1DeviceContext> context); 

};

