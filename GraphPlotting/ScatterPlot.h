// ScatterPlot.h 

#pragma once  
#include "DirectXBase.h" 
#include "GraphVariable.h"

// Two different example shapes
enum NodeShape { Circle, Square }; 

// This class represents data to be drawn as a scatter plot 
class ScatterPlot: public GraphVariable
{ 
	float m_HalfNodeSize;
	// Half size of the nodes 
	D2D1::ColorF m_NodeColor; 
	// The color of the nodes 
	ID2D1SolidColorBrush* m_brush;
	// Solid brush for painting nodes  
	NodeShape m_NodeShape; 
	// The shape of the nodes 

	public:  
		// Public constructor  
		ScatterPlot(float* x, float* y, float nodeSize,   D2D1::ColorF nodeColor, NodeShape nodeShape, int count);

		virtual void CreateDeviceDependentResources(Microsoft::WRL::ComPtr<ID2D1DeviceContext> context) override;

		virtual void Render(Microsoft::WRL::ComPtr<ID2D1DeviceContext> context) override; 

};