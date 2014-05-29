//
// BlankPage.xaml.h
// Declaration of the BlankPage.xaml class.
//

#pragma once

#include "DirectXPage.g.h"
#include "GraphRenderer.h"
#include "BasicTimer.h"

namespace GraphPlotting
{
	/// <summary>
	/// A DirectX page that can be used on its own.  Note that it may not be used within a Frame.
	/// </summary>
    [Windows::Foundation::Metadata::WebHostHidden]
	public ref class DirectXPage sealed
	{
	public:
		DirectXPage();

	private:
		void OnPointerMoved(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args);
		void OnPointerReleased(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args);
		void OnWindowSizeChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::WindowSizeChangedEventArgs^ args);
		void OnLogicalDpiChanged(Platform::Object^ sender);
		void OnOrientationChanged(Platform::Object^ sender);
		void OnDisplayContentsInvalidated(Platform::Object^ sender);
		void OnRendering(Object^ sender, Object^ args);

		Windows::Foundation::EventRegistrationToken m_eventToken;

		GraphRenderer^ m_renderer;
		bool m_renderNeeded;

		Windows::Foundation::Point m_lastPoint;
		bool m_lastPointValid;
		
		BasicTimer^ m_timer;
		void btnEditLine_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnPointerWheelChanged(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
	};
}
