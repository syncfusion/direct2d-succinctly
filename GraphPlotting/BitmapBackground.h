// BitmapBackground.h 
#pragma once 
#include "DirectXBase.h"  
// Defines a background consisting of a bitmap image 
class BitmapBackground { 
private: 
 ID2D1Bitmap * m_bmp; // The image to draw 
 D2D1_RECT_F m_screenRectangle; // Destination rectangle 
  
public: 
 // Constructor for bitmap backgrounds 
 BitmapBackground(); 
  
 // Release dynamic memory 
 ~BitmapBackground(); 

 void CreateDeviceDependentResources   (Microsoft::WRL::ComPtr<ID2D1DeviceContext> context, 	 IWICImagingFactory2 *wicFactory, LPCWSTR filename); 

 void CreateWindowSizeDependentResources( Microsoft::WRL::ComPtr<ID2D1DeviceContext> context); 

 void Render(Microsoft::WRL::ComPtr<ID2D1DeviceContext> context); 

}; 
