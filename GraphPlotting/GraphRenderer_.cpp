// GraphRenderer.cpp 

#include "pch.h" 
#include "GraphRenderer.h"  

using namespace D2D1; 
using namespace DirectX; 
using namespace Microsoft::WRL; 
using namespace Windows::Foundation; 
using namespace Windows::Foundation::Collections; 
using namespace Windows::UI::Core;

GraphRenderer::GraphRenderer() 
{ 
}  

void GraphRenderer::CreateDeviceIndependentResources() 
{ 
DirectXBase::CreateDeviceIndependentResources(); 
}  

void GraphRenderer::CreateDeviceResources() 
{ 
DirectXBase::CreateDeviceResources(); 
}

void GraphRenderer::CreateWindowSizeDependentResources()
{ 
DirectXBase::CreateWindowSizeDependentResources(); 
}  

void GraphRenderer::Update(float timeTotal, float timeDelta)
{ 
}  

void GraphRenderer::PointerMoved(Windows::Foundation::Point point) 
{ 
// Allow the user to set the current pan value with the mouse or pointer 
m_pan.X += point.X; 
m_pan.Y += point.Y; 
}