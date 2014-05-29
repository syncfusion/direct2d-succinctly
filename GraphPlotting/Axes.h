// Axes.h

#pragma once
#include "DirectXBase.h"

// This class represents a graph's axes as two perpendicular lines 
class Axes {
 ID2D1SolidColorBrush* m_solidBrush; // Brush to draw with
 float m_lineThickness; // Thickness in pixels
 float m_opacity;  // Opacity, 0.0f is invisible 1.0f is solid 
 D2D1::ColorF m_color; // The color of the lines

public:
 // Public constructor
 Axes(D2D1::ColorF col, float thickness, float opacity); 

 // Create the solid brush to draw with
 void CreateDeviceDependentResources
  (Microsoft::WRL::ComPtr<ID2D1DeviceContext> context); 
 
 // The render method needs to know the panning and scaling
 void Render(Microsoft::WRL::ComPtr<ID2D1DeviceContext> context,
  float panX, float panY, float scaleX, float scaleY);

};
