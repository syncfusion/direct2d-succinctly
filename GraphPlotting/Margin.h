// Margin.h 
#pragma once 
#include "DirectXBase.h" 
enum MarginStyle { Absolute, WindowSizeDependent }; 
 
class Margin { 
	ID2D1SolidColorBrush* m_solidBrush; // Brush to draw margin 
	D2D1::ColorF m_color; // The color of the margin  
	D2D1_RECT_F m_leftRect; // Rectangles which make the margin 
	D2D1_RECT_F m_rightRect; 
	D2D1_RECT_F m_topRect; 
	D2D1_RECT_F m_bottomRect;  
	MarginStyle m_style; // Style is Absolute or Window size dependent 
 
	// The size of the margin 
	float m_left, m_right, m_top, m_bottom; 
	
public: 

	// Public constructor 
	Margin(float left, float right, float top, float bottom, 
	D2D1::ColorF color, MarginStyle style); 
	
	// Create the rectangles to draw the margin 
	void CreateWindowSizeDependentResources 
	(Microsoft::WRL::ComPtr<ID2D1DeviceContext> context); 
 
	// Create the solid brush to draw with 
	void CreateDeviceDependentResources 
	(Microsoft::WRL::ComPtr<ID2D1DeviceContext> context); 
  
	// The render method needs to know the panning and scaling 
	void Render(Microsoft::WRL::ComPtr<ID2D1DeviceContext> context); 
 }; 