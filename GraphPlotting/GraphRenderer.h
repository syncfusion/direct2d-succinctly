// GraphRenderer.h 

#pragma once
#include "DirectXBase.h" 
//#include "SolidBackground.h"
#include "GradientBackground.h"
//#include "BitmapBackground.h"
#include "ScatterPlot.h"
#include "LineChart.h" 
#include "Axes.h" 
#include "Margin.h" 


// 
// Additional headers for graph objects here 
//  
// This class represents a graph 

ref class GraphRenderer sealed : public DirectXBase
{ 
public: 
	
	// Public constructor 
	GraphRenderer(); 

	 // DirectXBase methods. 
	virtual void CreateDeviceIndependentResources() override; 
	virtual void CreateDeviceResources() override; 
	virtual void CreateWindowSizeDependentResources() override; 
	virtual void Render() override;  

	// Capture the pointer movements so the user can pan the chart
	void PointerMoved(Windows::Foundation::Point point);

	// Method for updating time-dependent objects. 
	void Update(float timeTotal, float timeDelta); 
	
internal:
	
	LineChart* GetLine() {
	return (LineChart*) m_lineChart; 
	}
	
	// Zooming method 
	void Zoom(float amount); 

private:	
	
	// Global pan value for moving the chart with the mouse 
	Windows::Foundation::Point m_pan; 

	// Member variables for displaying FPS 
	float m_timeDelta; // Time since last update call 
	float m_timeTotal; // Total time of application 

	// Member variables and constants for zooming 
	#define MIN_ZOOM (0.01f) // Smallest zoom value is 1% 
	#define MAX_ZOOM (100.0f) // Largest zoom value is 10,000% 
	float m_zoomX; // The amount the x-axis is scaled by 
	float m_zoomY; // The amount the y-axis is scaled by 

	Microsoft::WRL::ComPtr<IDWriteTextFormat> m_textFormat; 
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_blackBrush; 
 
	// Solid Background Renderer
	//SolidBackground* m_solidBackground; 

	// Gradian Background Renderer
	GradientBackground* m_gradientBackground; 

	// Axes 
	Axes* m_axes; 

	// Margin 
	Margin* m_margin; 
 
	// Data 
	//ScatterPlot* m_scatterPlot; 

	// Bitmap Background
	//BitmapBackground* m_bitmapBackground;

	// Plottable data 
	GraphVariable* m_graphVariable;
	GraphVariable* m_lineChart;

};