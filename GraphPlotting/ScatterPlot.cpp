// ScatterPlot.cpp

#include "pch.h" 
#include "ScatterPlot.h"

using namespace D2D1; 
using namespace DirectX; 

ScatterPlot::ScatterPlot(float* x, float* y, float nodeSize,  
						 D2D1::ColorF nodeColor, NodeShape nodeShape, int count):   
						m_NodeColor(0), GraphVariable(x, y, count) { 
// Save half the node size. The nodes are drawn with
// the point they're representing at the middle of the shape. 
this->m_HalfNodeSize = nodeSize / 2;  

this->m_NodeShape = nodeShape;

this->m_NodeColor = nodeColor; 

} 

void ScatterPlot::Render( 
	Microsoft::WRL::ComPtr<ID2D1DeviceContext> context){ 
		switch(m_NodeShape) {

			// Draw as circle nodes
		case NodeShape::Circle:   
			for(int i = 0; i < m_nodeCount; i++) {   
				context->FillEllipse(D2D1::Ellipse(m_points[i], m_HalfNodeSize,     m_HalfNodeSize), m_brush);   
			}   
			break;    
			
			// Draw as square nodes  
		case NodeShape::Square:   
			for(int i = 0; i < m_nodeCount; i++) {    
				context->FillRectangle(D2D1::RectF(m_points[i].x -      m_HalfNodeSize,    m_points[i].y - m_HalfNodeSize, m_points[i].x + m_HalfNodeSize,    m_points[i].y + m_HalfNodeSize), m_brush);   
			}   
			break; 

		// Additional shapes could follow  
		default:   
			break;  
		} 
}  

void ScatterPlot::CreateDeviceDependentResources  (Microsoft::WRL::ComPtr<ID2D1DeviceContext> context) { 
	// Create a brush of the specified color for painting the nodes 
	DX::ThrowIfFailed(context->CreateSolidColorBrush(ColorF(m_NodeColor),  &m_brush)); 
}

