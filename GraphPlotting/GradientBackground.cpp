// GradientBackground.cpp 

#include "pch.h" 
#include "GradientBackground.h"  

GradientBackground::GradientBackground(D2D1_COLOR_F colors[], float stops[], int count)
{ 
// The constructor just saves the colors and stops 
this->count = count; 
this->colors = new D2D1_COLOR_F[count]; 
this->stops = new float[count]; 
  
	for(int i = 0; i < count; i++) 
	{ 
		this->colors[i] = D2D1_COLOR_F(colors[i]); 
		this->stops[i] = stops[i]; 
	} 
} 

void GradientBackground::CreateWindowSizeDependentResources  (Microsoft::WRL::ComPtr<ID2D1DeviceContext> context) 
{ 
// Create a gradient stops array from the colors and stops 
	D2D1_GRADIENT_STOP *gradientStops = new D2D1_GRADIENT_STOP[count]; 

	for(int i = 0; i < count; i++) { 
		gradientStops[i].color = colors[i]; 
		gradientStops[i].position = stops[i]; 
		}

// Create a Stop Collection from this using the 
// context's create method: 
ID2D1GradientStopCollection *gradientStopsCollection; 

DX::ThrowIfFailed( context->CreateGradientStopCollection (   
	gradientStops, // Stops 
	count,   // How many? 
	&gradientStopsCollection // Output object 
  ));

// Create a linear gradient brush from this: 
DX::ThrowIfFailed( 
 context->CreateLinearGradientBrush( 
 D2D1::LinearGradientBrushProperties ( 
  D2D1::Point2F(0, 0),// Start point of gradient 
  D2D1::Point2F( // Finish point of gradient 
   context->GetSize().width, 
   context->GetSize().height 
   )), 
 gradientStopsCollection, 
 &m_linearGradientBrush));  

// Also save the rectangle we're filling 
m_ScreenRectangle = D2D1::RectF(0, 0, context->GetSize().width, 
context->GetSize().height); 

}

void GradientBackground::Render(Microsoft::WRL::ComPtr<ID2D1DeviceContext> context) { 
// The fill the whole screen with the gradient 
	context->FillRectangle(&m_ScreenRectangle, m_linearGradientBrush.Get()); 
}

GradientBackground::~GradientBackground() { 
delete[] colors; 
delete[] stops; 
} 