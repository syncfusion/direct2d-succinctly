// LineChart.cpp

#include "pch.h"
#include "LineChart.h"
#include <vector> 
#include <algorithm>

using namespace D2D1;
using namespace DirectX;

	// Comparison method used by the stable-sort below 
	bool ComparePoints(D2D1_POINT_2F a, D2D1_POINT_2F b) {
	return a.x < b.x; // Sort on x values
	}
 
LineChart::LineChart(float* x, float *y, int count, D2D1::ColorF col, float thickness = 3.0f): m_color(0), GraphVariable(x,
y, count) {
	// Save these settings to member variables to
	// create the brush later: 
	this->m_color = col;
	this->m_lineThickness = thickness;

	// Sort the data by the x-axis 
	SortData();
	}

void LineChart::SortData()
{ 
	// Sort the data by the x-axis
	std::vector<D2D1_POINT_2F> sortedNodes(m_points, m_points + m_nodeCount);

	// Note the use of the stable sort, using an unstable sort 
	// like Quicksort will produce unexpected results!
	std::stable_sort(sortedNodes.begin(), sortedNodes.end(), ComparePoints);

	// Copy the sorted points back to the m_pointsArray
	int counter = 0; 
	for(std::vector<D2D1_POINT_2F>::iterator nodeIterator = sortedNodes.begin();
	nodeIterator != sortedNodes.end(); nodeIterator++, counter++) 
	{
	m_points[counter].x = (*nodeIterator).x;
	m_points[counter].y = (*nodeIterator).y; 
	}
}

void LineChart::CreateDeviceDependentResources(	Microsoft::WRL::ComPtr<ID2D1DeviceContext> context) 
{ 
	// Create the solid color brush
	DX::ThrowIfFailed(context->CreateSolidColorBrush(
	m_color, D2D1::BrushProperties(1.0f), &m_solidBrush));
} 

void LineChart::Render(Microsoft::WRL::ComPtr<ID2D1DeviceContext> context)
{
}