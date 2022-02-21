#pragma once
#include "wx/wx.h"

#include "cEditorFrame.h"
#include "eventableStaticBitmap.h"
#include "NeuralModel.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();


public:
	//wxToolBar* m_ToolBar = nullptr;
	wxMenuBar* m_MenuBar = nullptr;

	//text entry box, add button, list box
	wxButton* m_btn1 = nullptr;
	wxTextCtrl* m_txt1 = nullptr;
	wxListBox* m_list1 = nullptr;
	wxListBox* m_list2 = nullptr;
	wxButton* removeLastItem = nullptr;

	//layers entry
	wxButton* addLayer = nullptr;
	wxTextCtrl* layer = nullptr;
	wxListBox* layersList = nullptr;
	wxButton* removeLastLayer = nullptr;

	//title
	wxTextCtrl* title = nullptr;

	//upload image button and display
	wxButton* uploadButton = nullptr;
	wxBitmap* uploadedImage = nullptr;
	eventableStaticBitmap* evaluatedImage = nullptr;

	//upload image result text box
	wxTextCtrl* recognition_Result = nullptr;
	wxTextCtrl* confidence_Result_Display = nullptr;

	//draw new image, clear image, collect data button
	wxButton* draw_new_image_button = nullptr;
	wxButton* collect_data_button = nullptr;
	int collect_index = -1;
	wxButton* clear_image_button = nullptr;

	//train model button and info
	wxButton* trainModelButton = nullptr;
	wxTextCtrl* trainTime = nullptr;
	wxTextCtrl* trainTimeGet = nullptr;
	wxButton* trainForTimeButton = nullptr;
	wxTextCtrl* trainAccuracy = nullptr;
	wxButton* evaluateAccuracyButton = nullptr;
	wxButton* loadData = nullptr;

	//temporary debug text
	wxTextCtrl* debug = nullptr;

	//Neural Model
	NeuralModel* activeModel = nullptr;

	void OnMenuNew(wxCommandEvent& evt);
	void OnMenuOpen(wxCommandEvent& evt);
	void OnMenuSave(wxCommandEvent& evt);
	void OnMenuExit(wxCommandEvent& evt);
	void OnMenuSaveAs(wxCommandEvent& evt);
	void OnMenuUpload(wxCommandEvent& evt);
	void OnMenuDraw(wxCommandEvent& evt);
	void OnUploadButtonClicked(wxCommandEvent& evt);
	void OnDrawNewButtonClicked(wxCommandEvent& evt);
	void OnCollectDataButtonClicked(wxCommandEvent& evt);
	void OnClearImageButtonClicked(wxCommandEvent& evt);
	void OnTrainButtonClicked(wxCommandEvent& evt);
	void OnButtonClicked(wxCommandEvent& evt);
	void OnSelectColour(wxCommandEvent& evt);
	void OnTrainForTimeButtonClicked(wxCommandEvent& evt);
	void OnEvaluateAccuracyButton(wxCommandEvent& evt);
	void OnLoadDataButton(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

