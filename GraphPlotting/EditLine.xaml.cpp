//
// EditLine.xaml.cpp
// Implementation of the EditLine class
//

#include "pch.h"
#include "EditLine.xaml.h"

using namespace GraphPlotting;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

EditLine::EditLine(Windows::UI::Xaml::UIElement^ myParent, LineChart* myLine)
{
	InitializeComponent();
	this->m_myParent = myParent; 
	this->m_myLine = myLine; 
	this->sldLineThickness->Value = (int)myLine->GetLineThickness(); 
}

/// <summary>
/// Invoked when this page is about to be displayed in a Frame.
/// </summary>
/// <param name="e">Event data that describes how this page was reached.  The Parameter
/// property is typically used to configure the page.</param>
void EditLine::OnNavigatedTo(NavigationEventArgs^ e)
{
	(void) e;	// Unused parameter
}


void GraphPlotting::EditLine::btnBack_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	m_myLine->SetLineThickness((float)sldLineThickness->Value);
	Window::Current->Content = m_myParent; // Give the parent the focus 
	Window::Current->Activate();

}
