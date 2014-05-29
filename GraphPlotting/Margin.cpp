// Margin.cpp 
#include "pch.h" 
#include "Margin.h" 
	
	Margin::Margin(float left, float right, float top, float bottom, 
	D2D1::ColorF color, MarginStyle style) : m_color(0) { 

	 // Save the parameters for the create resources methods
	this->m_color = color; m_style = style; this->m_left = left; this->m_right = right; 
	this->m_top = top; this->m_bottom = bottom; 
} 
 
	void Margin::CreateWindowSizeDependentResources( 
	Microsoft::WRL::ComPtr<ID2D1DeviceContext> context) { 
	
	// If the sizes of the margin passed were percentages of the screen 
	
	// we have to multiply the values before creating the rectangles: 
	if(m_style == MarginStyle::WindowSizeDependent) { 
	m_left = context->GetSize().width * m_left; 
	m_right = context->GetSize().width * m_right; 
	m_top = context->GetSize().height * m_top; 
	m_bottom = context->GetSize().height * m_bottom; 
 } 
 
	// Left rectangle 
	m_leftRect.left = 0; m_leftRect.right = m_left; 
	m_leftRect.top = 0; m_leftRect.bottom = context->GetSize().height; 
  
	// Right rectangle 
	m_rightRect.left = context->GetSize().width - m_right; 
	m_rightRect.right = context->GetSize().width; 
	m_rightRect.top = 0; m_rightRect.bottom = context->GetSize().height; 
  
	// Top margin 
	m_topRect.left = m_left; 
	m_topRect.right = context->GetSize().width - m_right; 
	m_topRect.top = 0; m_topRect.bottom = m_top; 
 
	// Bottom margin 
	m_bottomRect.left = m_left; 
	m_bottomRect.right = context->GetSize().width - m_right; 
	m_bottomRect.top = context->GetSize().height - m_bottom; 
	m_bottomRect.bottom = context->GetSize().height; 
} 
 
	void Margin::CreateDeviceDependentResources 
	(Microsoft::WRL::ComPtr<ID2D1DeviceContext> context) { 
	
	// Create the brush 
	DX::ThrowIfFailed(context->CreateSolidColorBrush(m_color, &m_solidBrush)); 
} 
 
	void Margin::Render(Microsoft::WRL::ComPtr<ID2D1DeviceContext> context) { 
	
	// Draw the left margin 
	context->FillRectangle(m_leftRect, m_solidBrush); 
	
	// Draw the right margin 
	context->FillRectangle(m_rightRect, m_solidBrush); 
	
	// Draw the top margin 
	context->FillRectangle(m_topRect, m_solidBrush); 
	
	// Draw the bottom margin 
	context->FillRectangle(m_bottomRect, m_solidBrush); 
} 