#pragma once
#include "wx/wx.h"
#include "NeuralModel.h"

class eventableStaticBitmap : public wxStaticBitmap
{
public:
	eventableStaticBitmap(wxWindow* parent, wxWindowID id, const wxBitmap& label, const wxPoint& pos, const wxSize& size, long style, const wxString& name);
	~eventableStaticBitmap();
	void OnLeftClick(wxMouseEvent& evt);
	void OnLeftUp(wxMouseEvent& evt);
	void OnTimer(wxTimerEvent& evt);
	int greater(unsigned char one, int two);
	void setPixel(unsigned char* drawing_image_data, int xPosition, int yPosition);
	void BresenhamLine(float x1, float y1, float x2, float y2, unsigned char* drawing_image_data);
	wxImage* drawing;

	int xPosition;
	int yPosition;

	int oldxPosition;
	int oldyPosition;
private:
	wxTimer* m_timer;
	wxDECLARE_EVENT_TABLE();
};

