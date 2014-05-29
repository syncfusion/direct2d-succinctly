// LineChart.h
#pragma once
#include "DirectXBase.h"
#include "GraphVariable.h"
#include <wrl.h>
#include <wrl\module.h>
using namespace Microsoft::WRL;

	// This class represents a variable rendered as a line
	class LineChart: public GraphVariable {
	ID2D1SolidColorBrush* m_solidBrush; // Brush to draw with
	float m_lineThickness; // Thickness in pixels 
	D2D1::ColorF m_color; // The color of the line

	// Method to stable-sort the data by the x-axis
	void SortData(); 

	public:
	
	// Public constructor
	LineChart(float* x, float *y, int count, D2D1::ColorF col, float
	thickness); 

	// Create the solid brush to draw with
	virtual void CreateDeviceDependentResources
	(Microsoft::WRL::ComPtr<ID2D1DeviceContext> context) override; 
 
	// The main render method of the line class
	virtual void Render(Microsoft::WRL::ComPtr<ID2D1DeviceContext> context) override; 
	
	// Getters and setters for line thickness
	void SetLineThickness(float newThickness) {
	m_lineThickness = newThickness;
	 }
 
	float GetLineThickness() {
	return m_lineThickness; 
	} 
};