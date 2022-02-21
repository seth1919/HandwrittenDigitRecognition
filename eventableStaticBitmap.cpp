#include "eventableStaticBitmap.h"

wxBEGIN_EVENT_TABLE(eventableStaticBitmap, wxStaticBitmap)
EVT_LEFT_DOWN(eventableStaticBitmap::OnLeftClick)
EVT_LEFT_UP(eventableStaticBitmap::OnLeftUp)
EVT_TIMER(10009, eventableStaticBitmap::OnTimer)
wxEND_EVENT_TABLE()

eventableStaticBitmap::eventableStaticBitmap(wxWindow* parent, wxWindowID id, const wxBitmap& label, const wxPoint& pos, const wxSize& size, long style, const wxString& name) : wxStaticBitmap(parent, id, label, pos, size, style, name)
{
	m_timer = new wxTimer(this, 10009);
	drawing = new wxImage(28, 28);
}

eventableStaticBitmap::~eventableStaticBitmap()
{
	delete drawing;
	delete m_timer;
}

void eventableStaticBitmap::OnLeftClick(wxMouseEvent& evt)
{
	//drawing = new wxImage(28, 28);
	m_timer->Start(50);

	wxPoint position = ScreenToClient(wxGetMousePosition());
	xPosition = position.x / 10.71428;
	yPosition = position.y / 10.71428;

	//display the current drawing
	wxImage finished(*drawing);
	finished.Rescale(300, 300, wxIMAGE_QUALITY_NEAREST);
	this->SetBitmap(finished);
}

void eventableStaticBitmap::OnLeftUp(wxMouseEvent& evt)
{
	//stop the timer
	m_timer->Stop();

	//add white pixels to the image
	unsigned char* drawing_image_data = drawing->GetData();

	wxPoint position = ScreenToClient(wxGetMousePosition());
	oldxPosition = xPosition;
	oldyPosition = yPosition;
	xPosition = position.x / 10.71428;
	yPosition = position.y / 10.71428;

	BresenhamLine(oldxPosition, oldyPosition, xPosition, yPosition, drawing_image_data);


	//display the current drawing
	wxImage finished(*drawing);
	finished.Rescale(300, 300, wxIMAGE_QUALITY_NEAREST);
	this->SetBitmap(finished);
}

void eventableStaticBitmap::OnTimer(wxTimerEvent& evt)
{
	//add white pixels to the image
	unsigned char* drawing_image_data = drawing->GetData();

	wxPoint position = ScreenToClient(wxGetMousePosition());
	oldxPosition = xPosition;
	oldyPosition = yPosition;
	xPosition = position.x / 10.71428;
	yPosition = position.y / 10.71428;

	BresenhamLine(oldxPosition, oldyPosition, xPosition, yPosition, drawing_image_data);

	//display the current drawing
	wxImage finished(*drawing);
	finished.Rescale(300, 300, wxIMAGE_QUALITY_NEAREST);
	this->SetBitmap(finished);
}

int eventableStaticBitmap::greater(unsigned char one, int two) {
	if (one > two) {
		return one;
	}
	else {
		return two;
	}
}

void eventableStaticBitmap::setPixel(unsigned char* drawing_image_data, int xPosition, int yPosition)
{
	//top left
	if (xPosition - 1 > -1 && yPosition - 1 > -1) {
		drawing_image_data[(xPosition - 1 + (28 * (yPosition - 1))) * 3] = greater(drawing_image_data[(xPosition - 1 + (28 * (yPosition - 1))) * 3], 190);
		drawing_image_data[((xPosition - 1 + (28 * (yPosition - 1))) * 3) + 1] = greater(drawing_image_data[((xPosition - 1 + (28 * (yPosition - 1))) * 3) + 1], 190);
		drawing_image_data[((xPosition - 1 + (28 * (yPosition - 1))) * 3) + 2] = greater(drawing_image_data[((xPosition - 1 + (28 * (yPosition - 1))) * 3) + 2], 190);
	}
	

	//top middle
	if (yPosition - 1 > -1) {
		drawing_image_data[(xPosition + (28 * (yPosition - 1))) * 3] = greater(drawing_image_data[(xPosition + (28 * (yPosition - 1))) * 3], 255);
		drawing_image_data[((xPosition + (28 * (yPosition - 1))) * 3) + 1] = greater(drawing_image_data[((xPosition + (28 * (yPosition - 1))) * 3) + 1], 255);
		drawing_image_data[((xPosition + (28 * (yPosition - 1))) * 3) + 2] = greater(drawing_image_data[((xPosition + (28 * (yPosition - 1))) * 3) + 2], 255);
	}

	//top right
	/*
	if (xPosition + 1 < 28 && yPosition - 1 > -1) {
		drawing_image_data[(xPosition + 1 + (28 * (yPosition - 1))) * 3] = greater(drawing_image_data[(xPosition + 1 + (28 * (yPosition - 1))) * 3], 127);
		drawing_image_data[((xPosition + 1 + (28 * (yPosition - 1))) * 3) + 1] = greater(drawing_image_data[((xPosition + 1 + (28 * (yPosition - 1))) * 3) + 1], 127);
		drawing_image_data[((xPosition + 1 + (28 * (yPosition - 1))) * 3) + 2] = greater(drawing_image_data[((xPosition + 1 + (28 * (yPosition - 1))) * 3) + 2], 127);
	}
	*/

	//middle left
	if (xPosition - 1 > -1) {
		drawing_image_data[(xPosition - 1 + (28 * yPosition)) * 3] = greater(drawing_image_data[(xPosition - 1 + (28 * yPosition)) * 3], 255);
		drawing_image_data[((xPosition - 1 + (28 * yPosition)) * 3) + 1] = greater(drawing_image_data[((xPosition - 1 + (28 * yPosition)) * 3) + 1], 255);
		drawing_image_data[((xPosition - 1 + (28 * yPosition)) * 3) + 2] = greater(drawing_image_data[((xPosition - 1 + (28 * yPosition)) * 3) + 2], 255);
	}

	//middle pixel
	drawing_image_data[(xPosition + (28 * yPosition)) * 3] = greater(drawing_image_data[(xPosition + (28 * yPosition)) * 3], 210);
	drawing_image_data[((xPosition + (28 * yPosition)) * 3) + 1] = greater(drawing_image_data[((xPosition + (28 * yPosition)) * 3) + 1], 210);
	drawing_image_data[((xPosition + (28 * yPosition)) * 3) + 2] = greater(drawing_image_data[((xPosition + (28 * yPosition)) * 3) + 2], 210);

	//middle right
	if (xPosition + 1 < 28) {
		drawing_image_data[(xPosition + 1 + (28 * yPosition)) * 3] = greater(drawing_image_data[(xPosition + 1 + (28 * yPosition)) * 3], 0);
		drawing_image_data[((xPosition + 1 + (28 * yPosition)) * 3) + 1] = greater(drawing_image_data[((xPosition + 1 + (28 * yPosition)) * 3) + 1], 0);
		drawing_image_data[((xPosition + 1 + (28 * yPosition)) * 3) + 2] = greater(drawing_image_data[((xPosition + 1 + (28 * yPosition)) * 3) + 2], 0);
	}

	//bottom left
	/*
	if (xPosition - 1 > -1 && yPosition + 1 < 28) {
		drawing_image_data[(xPosition - 1 + (28 * (yPosition + 1))) * 3] = greater(drawing_image_data[(xPosition - 1 + (28 * (yPosition + 1))) * 3], 127);
		drawing_image_data[((xPosition - 1 + (28 * (yPosition + 1))) * 3) + 1] = greater(drawing_image_data[((xPosition - 1 + (28 * (yPosition + 1))) * 3) + 1], 127);
		drawing_image_data[((xPosition - 1 + (28 * (yPosition + 1))) * 3) + 2] = greater(drawing_image_data[((xPosition - 1 + (28 * (yPosition + 1))) * 3) + 2], 127);
	}
	*/

	//bottom middle
	if (yPosition + 1 < 28) {
		drawing_image_data[(xPosition + (28 * (yPosition + 1))) * 3] = greater(drawing_image_data[(xPosition + (28 * (yPosition + 1))) * 3], 0);
		drawing_image_data[((xPosition + (28 * (yPosition + 1))) * 3) + 1] = greater(drawing_image_data[((xPosition + (28 * (yPosition + 1))) * 3) + 1], 0);
		drawing_image_data[((xPosition + (28 * (yPosition + 1))) * 3) + 2] = greater(drawing_image_data[((xPosition + (28 * (yPosition + 1))) * 3) + 2], 0);
	}

	//bottom right
	/*
	if (xPosition + 1 < 28 && yPosition + 1 < 28) {
		drawing_image_data[(xPosition + 1 + (28 * (yPosition + 1))) * 3] = greater(drawing_image_data[(xPosition + 1 + (28 * (yPosition + 1))) * 3], 127);
		drawing_image_data[((xPosition + 1 + (28 * (yPosition + 1))) * 3) + 1] = greater(drawing_image_data[((xPosition + 1 + (28 * (yPosition + 1))) * 3) + 1], 127);
		drawing_image_data[((xPosition + 1 + (28 * (yPosition + 1))) * 3) + 2] = greater(drawing_image_data[((xPosition + 1 + (28 * (yPosition + 1))) * 3) + 2], 127);
	}
	*/
}

void eventableStaticBitmap::BresenhamLine(float x1, float y1, float x2, float y2, unsigned char* drawing_image_data)
{
	// Bresenham's line algorithm
	const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
	if (steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	const float dx = x2 - x1;
	const float dy = fabs(y2 - y1);

	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	const int maxX = (int)x2;

	for (int x = (int)x1; x <= maxX; x++)
	{
		if (steep)
		{
			setPixel(drawing_image_data, y, x);
		}
		else
		{
			setPixel(drawing_image_data, x, y);
		}

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}
