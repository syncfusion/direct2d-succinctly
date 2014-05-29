// BitmapBackground.cpp 

#include "pch.h" 
#include "BitmapBackground.h" 

// This constructor must be called at some point after the 
// WIC factory is initialized! 
BitmapBackground::BitmapBackground() { }

BitmapBackground::~BitmapBackground()
{ 
m_bmp->Release(); 
}  

void BitmapBackground::CreateDeviceDependentResources  (Microsoft::WRL::ComPtr<ID2D1DeviceContext> context, IWICImagingFactory2 *wicFactory, LPCWSTR filename) 
{ 
	// Create a WIC decoder 
	IWICBitmapDecoder *pDecoder;   

	// Decode a file, make sure you've added the file to the project first:
	DX::ThrowIfFailed(wicFactory->CreateDecoderFromFilename(filename,  nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecoder));  

	// Read a frame from the file (png, jpg, bmp etc. images only have one frame so 
	// the index is always 0): 
	IWICBitmapFrameDecode *pFrame = nullptr; 
	DX::ThrowIfFailed(pDecoder->GetFrame(0, &pFrame));  

	// Create format converter to ensure data is the correct format despite the 
	// file's format. 
	// It's likely the format is already perfect but we can't be sure: 
	IWICFormatConverter *m_pConvertedSourceBitmap; 
	DX::ThrowIfFailed(wicFactory->CreateFormatConverter(&m_pConvertedSourceBitmap)); 
	DX::ThrowIfFailed(m_pConvertedSourceBitmap->Initialize(  pFrame, GUID_WICPixelFormat32bppPRGBA,  WICBitmapDitherTypeNone, nullptr,  0.0f, WICBitmapPaletteTypeCustom));  

	// Create a Direct2D bitmap from the converted source 
	DX::ThrowIfFailed(context->CreateBitmapFromWicBitmap( m_pConvertedSourceBitmap, &m_bmp));  

	// Release the dx objects we used to create the bmp 
	pDecoder->Release(); 
	pFrame->Release(); 
	m_pConvertedSourceBitmap->Release(); 
}  

void BitmapBackground::CreateWindowSizeDependentResources( Microsoft::WRL::ComPtr<ID2D1DeviceContext> context)
{ 
	// Save a rectangle the same size as the area to draw the background 
	m_screenRectangle = D2D1::RectF(0, 0, context->GetSize().width, context->GetSize().height); 
}  

void BitmapBackground::Render(Microsoft::WRL::ComPtr<ID2D1DeviceContext> context) 
{ 
	context->DrawBitmap(m_bmp, &m_screenRectangle); 
} 