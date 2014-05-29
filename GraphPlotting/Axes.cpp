// Axes.cpp
#include "pch.h" 
#include "Axes.h"
using namespace D2D1;
using namespace DirectX; 
Axes::Axes(D2D1::ColorF col, float thickness = 3.0f, float opacity = 1.0f):
m_color(0)
{
// Save these settings to member variables so
// they can create the brush later: 
this->m_color = col;
this->m_lineThickness = thickness;
this->m_opacity = opacity;
} 

void Axes::CreateDeviceDependentResources(
Microsoft::WRL::ComPtr<ID2D1DeviceContext> context){
// Create the solid color brush 
	DX::ThrowIfFailed(context->CreateSolidColorBrush(
 m_color, D2D1::BrushProperties(m_opacity), &m_solidBrush)); 
}

void Axes::Render(Microsoft::WRL::ComPtr<ID2D1DeviceContext> context, float
panX, float panY, float scaleX, float scaleY) {
// Draw infinite vertical line with 0.0f as the x-coordinate 
context->DrawLine(
 D2D1::Point2F(
  0.0f,   // Horizontal axis
  (-context->GetSize().height - panY) / scaleY // Top of the screen 
  ),
 D2D1::Point2F(
  0.0f,   // Horizontal axis
  (-panY) / scaleY // Bottom of the screen
  ), 
 m_solidBrush,
 m_lineThickness/scaleX);

// Draw infinite horizontal line with 0.0f as the y-coordinate 
context->DrawLine(
 D2D1::Point2F(
  -(panX)/scaleX, // Left side of screen
  0.0f     // Vertical axis
  ), 
 D2D1::Point2F(
  (context->GetSize().width - panX)/scaleX, // Right side of screen
  0.0f     // Vertical axis
  ), 
 m_solidBrush,
 m_lineThickness/scaleY);
} 