// GraphRenderer.cpp 

#include "pch.h" 
#include <string> 
#include "GraphRenderer.h"  

using namespace D2D1; 
using namespace DirectX; 
using namespace Microsoft::WRL; 
using namespace Windows::Foundation; 
using namespace Windows::Foundation::Collections; 
using namespace Windows::UI::Core;

GraphRenderer::GraphRenderer():
	m_zoomX(1.0f), 
	m_zoomY(1.0f) 
{ 
	// Solid Background Renderer
	//m_solidBackground = new SolidBackground(D2D1::ColorF::Bisque); 

	// Gradient Background
		D2D1_COLOR_F colors[] = { 
		D2D1::ColorF(ColorF::PaleGoldenrod), 
		D2D1::ColorF(ColorF::PaleTurquoise), 
		D2D1::ColorF(0.7f, 0.7f, 1.0f, 1.0f) 
		}; 

	float stops[] = { 
		0.0f, 
		0.5f, 
		1.0f 
		};  

	m_gradientBackground = new GradientBackground(colors, stops, 3);

	// Number of Gradient Background
		/*const int count = 500;  
		D2D1_COLOR_F *cols = new D2D1_COLOR_F[count]; 
		float* stops = new float[count];  
		for(int i = 0; i < count; i++) { 
		cols[i] = D2D1::ColorF( 
		0.75f+(float)(rand()%192)/192.0f, // Random pastels 
		0.75f+(float)(rand()%192)/192.0f,  
		0.75f+(float)(rand()%192)/192.0f); 
		stops[i] = (float)i / (count - 1); 
		} 
  
	m_gradientBackground = new GradientBackground(cols, stops, count);*/

	//Bitmap Background
	//m_bitmapBackground = new BitmapBackground();

	// Create the scatter plot: 
	const int count = 25; // Create 500 nodes 
	float* x = new float[count]; 
	float* y = new float[count]; 

	// Create random points to plot, these 
	// would usually be read from some data source: 
	for(int i = 0; i < count; i++) 
	{ 
		x[i] = (float)((rand() % 2000) - 1000); 
		y[i] = (float)((rand() % 1000) - 500);  
	}  

	m_graphVariable = new ScatterPlot(x, y, 10.0f,  D2D1::ColorF::Chocolate,  NodeShape::Circle, count); 
	//m_scatterPlot = new ScatterPlot(x, y, 10.0f,  D2D1::ColorF::Chocolate,  NodeShape::Circle, count); 
	// Create the line chart
	m_lineChart = new LineChart(x, y, count, D2D1::ColorF::Chocolate, 5.0f);

	delete[] x; 
	delete[] y;

	// Create the Axes 
	m_axes = new Axes(D2D1::ColorF::Black, 5.0f, 0.75f); 

	// Create the margin
	m_margin = new Margin(0.1f, 0.1f, 0.1f, 0.1f, // 10% of window size 
	D2D1::ColorF(0.38f, 0.66f, 0.74f, 1.0f),
	MarginStyle::WindowSizeDependent); 


	// Line Scotter Plots
	/*const int count = 500; // Create 500 nodes 
	float* x = new float[count]; 
	float* y = new float[count];

	for(int i = 0; i < count; i++) {  
		x[i] = i; 
		y[i] = i;  
	}  */

	/*m_graphVariable = new ScatterPlot(x, y, 10.0f,  
		D2D1::ColorF::Chocolate, 
		NodeShape::Circle, count
		);*/


}  

void GraphRenderer::CreateDeviceIndependentResources() 
{ 
	DirectXBase::CreateDeviceIndependentResources(); 
	DX::ThrowIfFailed( 
	m_dwriteFactory->CreateTextFormat( 
    L"Segoe UI", 
    nullptr, 
    DWRITE_FONT_WEIGHT_NORMAL, 
	DWRITE_FONT_STYLE_NORMAL, 
	DWRITE_FONT_STRETCH_NORMAL, 
	42.0f, 
	L"en-US", 
	&m_textFormat 
	) 
	);	
}  

void GraphRenderer::CreateDeviceResources() 
{ 
	DirectXBase::CreateDeviceResources(); 
	// Create the brush for the scatter plot: 
	//m_scatterPlot->CreateDeviceDependentResources(m_d2dContext); 
	
	// Call the create device resources for our graph variable 
	m_graphVariable->CreateDeviceDependentResources(m_d2dContext);
 
	// Create device resources for the line chart
	m_lineChart->CreateDeviceDependentResources(m_d2dContext);

	// Create the brush for the Axes 
	m_axes->CreateDeviceDependentResources(m_d2dContext); 
 
	// Bitmap Background
	// Load the bitmap for our background 
	/* m_bitmapBackground->CreateDeviceDependentResources( 
	m_d2dContext, 
	m_wicFactory.Get(), 
	L"background5.jpg");*/

	

	// Create the solid brush for the text
	DX::ThrowIfFailed(
	m_d2dContext->CreateSolidColorBrush(ColorF(ColorF::Black),&m_blackBrush)); 

	// Create the margin's device dependent resources
	m_margin->CreateDeviceDependentResources(m_d2dContext); 


}

void GraphRenderer::CreateWindowSizeDependentResources()
{ 
	DirectXBase::CreateWindowSizeDependentResources();

	// Gradient Background
	m_gradientBackground->CreateWindowSizeDependentResources(m_d2dContext);

	//Bitmap Background
	//m_bitmapBackground->CreateWindowSizeDependentResources(m_d2dContext);

	// Set the initial pan value so the lowest node is visible in the corner 
	m_pan.X = -m_graphVariable->GetMinX(); 
	//m_pan.Y = -m_d2dContext->GetSize().height - m_graphVariable->GetMinY(); 
	m_pan.Y = m_graphVariable->GetMinY();

	// Create window size dependent resources for the margin
	m_margin->CreateWindowSizeDependentResources(m_d2dContext); 
}  

void GraphRenderer::Update(float timeTotal, float timeDelta)
{ 

	static int fpsCounter = -1;// Start at -1 so frame 0 updates timers 
	fpsCounter++; 
	if((fpsCounter & 15) == 0) { // Update every 16 frames 
	// Record the times for displaying: 
	m_timeDelta = timeDelta; 
	m_timeTotal = timeTotal; 
	}  
}

void GraphRenderer::Render()
{
	m_d2dContext->BeginDraw();
	m_d2dContext->Clear(ColorF(ColorF::CornflowerBlue));

	// Reset the transform matrix so our gradient does not pan 
	//m_d2dContext->SetTransform(m_orientationTransform2D);	

	// Pan the chart 
	/*Matrix3x2F panMatrix = Matrix3x2F::Translation(m_pan.X, m_pan.Y); 
	m_d2dContext->SetTransform(panMatrix*m_orientationTransform2D);*/

	//Flipped Scottor plot with Tranformations
	/*Matrix3x2F scale = Matrix3x2F::Scale(1.0f, -1.0f, D2D1::Point2F(0.0f, 0.0f));*/
	
	// The scale matrix inverts the y-axis 
	Matrix3x2F scale = Matrix3x2F::Scale(1.0f * m_zoomX, // Multiply by x-axis zoom 
	-1.0f * m_zoomY, // Flip and multiply by y-axis zoom 
	D2D1::Point2F(0.0f, 0.0f)); 
	Matrix3x2F panMatrix = Matrix3x2F::Translation(m_pan.X, m_pan.Y +  m_d2dContext->GetSize().height);
	m_d2dContext->SetTransform(scale*panMatrix*m_orientationTransform2D);

	// Draw the axes 
	m_axes->Render(m_d2dContext, m_pan.X, m_pan.Y, m_zoomX*1.0f, m_zoomY*-1.0f);
	 
	// Solid Background
	//m_solidBackground->Render(m_d2dContext);

	//Gradient Background
	m_gradientBackground->Render(m_d2dContext);

	//Bitmap Background
	//m_bitmapBackground->Render(m_d2dContext);

	// Render the graph variable
	m_lineChart->Render(m_d2dContext); 
	m_graphVariable->Render(m_d2dContext);
	
	//m_scatterPlot->Render(m_d2dContext); 

	// Reset the transform matrix so the time and FPS does not pan or zoom 
	m_d2dContext->SetTransform(m_orientationTransform2D);

	// Render the margin
	m_margin->Render(m_d2dContext); 

	// Set up the string to print:
	std::wstring s = std::wstring(
	L"Total Time: ") + std::to_wstring(m_timeTotal) + 
	std::wstring(L" FPS: ") + std::to_wstring(
	(int)(0.5f+1.0f/m_timeDelta)); // FPS rounded to nearest int
	// Render the string in the top left corner
	m_d2dContext->DrawText(s.c_str(), s.length(), m_textFormat.Get(),
	D2D1::RectF(0, 0, 600, 32), m_blackBrush.Get()); 
 
	// Ignore D2DERR_RECREATE_TARGET error

	HRESULT hr = m_d2dContext->EndDraw();
	if (hr != D2DERR_RECREATE_TARGET)
	{
		DX::ThrowIfFailed(hr);
	} 

}

void GraphRenderer::Zoom(float amount) { 
// Multiply the zooms 
m_zoomX *= amount; 
m_zoomY *= amount; 
 
// Make sure the new zooms are still within the limits: 
if(m_zoomX < MIN_ZOOM) m_zoomX = MIN_ZOOM; 
else if(m_zoomX > MAX_ZOOM) m_zoomX = MAX_ZOOM; 
 
if(m_zoomY < MIN_ZOOM) m_zoomY = MIN_ZOOM; 
else if(m_zoomY > MAX_ZOOM) m_zoomY = MAX_ZOOM; 
}

void GraphRenderer::PointerMoved(Windows::Foundation::Point point) 
{ 
	// Allow the user to set the current pan value with the mouse or pointer 
	m_pan.X += point.X; 
	m_pan.Y += point.Y; 
}
