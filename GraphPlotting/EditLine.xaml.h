//
// EditLine.xaml.h
// Declaration of the EditLine class
//

#pragma once

#include "EditLine.g.h"
#include "LineChart.h" 

namespace GraphPlotting
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	
	public ref class EditLine sealed
	{
	
	public:
		

	internal:
		EditLine(Windows::UI::Xaml::UIElement^ myParent, LineChart* myLine);

	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		
	private: 
		Windows::UI::Xaml::UIElement^ m_myParent;
		LineChart* m_myLine;
		void btnBack_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
