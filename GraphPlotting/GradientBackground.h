// GradientBackground.h 

#pragma once 
#include "DirectXBase.h" 

// Gradient background 
class GradientBackground
{ 
private: 
	D2D1_COLOR_F *colors; // The colors in the gradient 
	float *stops;// Positions of the colors 
	int count; // The number of different colors used 
	D2D1_RECT_F m_ScreenRectangle; // The size of the rectangle we're filling 

	// The linear gradient brush performs the painting 
	Microsoft::WRL::ComPtr<ID2D1LinearGradientBrush> m_linearGradientBrush;  
public: 
 // Creates a new gradient background 
 GradientBackground(D2D1_COLOR_F colors[], float stops[], int count); 

 // Release dynamic memory 
 ~GradientBackground(); 

 void CreateWindowSizeDependentResources   (Microsoft::WRL::ComPtr<ID2D1DeviceContext> context); 

 void Render(Microsoft::WRL::ComPtr<ID2D1DeviceContext> context); 

};