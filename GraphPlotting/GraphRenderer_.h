// GraphRenderer.h 

#pragma once 
#include "DirectXBase.h" 

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

private: 
 // Global pan value for moving the chart with the mouse 
 Windows::Foundation::Point m_pan; 

};