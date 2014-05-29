// GraphVariable.cpp 

#include "pch.h"
#include "GraphVariable.h"

GraphVariable::GraphVariable(float* x, float* y, int count) 
{ 
	this->m_nodeCount = count;

	// Assume the minimum is the first value 
	m_minX = x[0]; m_minY = y[0];

	// Create an array of points from the *x and *y. 
	// We can't assume that the *x and *y are permanent so 
	// allocate seperate heap space for a copy of the data 
	// as D2D1::Point2F's: 
	m_points = new D2D1_POINT_2F[count]; 
	for(int i = 0; i < count; i++)  
	{  
		m_points[i] = D2D1::Point2F(x[i], y[i]); 

	 // Check if the point is lower than the current minimum  
		if(x[i] < m_minX) m_minX = x[i];  if(y[i] < m_minY) m_minY = y[i]; 
	} 

} 