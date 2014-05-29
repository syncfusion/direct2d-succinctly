// GraphVariable.h

#pragma once  
#include "DirectXBase.h"  

	// This class represents a generic plottable variable
	// It is the base class for the ScatterPlot and the LineChart
	// classes.
	class GraphVariable abstract 
	{
		protected:  D2D1_POINT_2F* m_points; // These are the x and y values of each node  
					int m_nodeCount; // This is a record of the total number of nodes

		// Record of smallest point  
					float m_minX, m_minY; // Used to auto pan 
	
		public:  // Getters for min values  
			float GetMinX() { return m_minX; }  
			float GetMinY() { return m_minY; }  

			GraphVariable(float* x, float* y, int count);  

			virtual void CreateDeviceDependentResources (Microsoft::WRL::ComPtr<ID2D1DeviceContext> context) = 0;
			virtual void Render(Microsoft::WRL::ComPtr<ID2D1DeviceContext> context)  = 0; 

}; 