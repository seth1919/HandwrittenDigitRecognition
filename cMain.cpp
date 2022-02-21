#pragma once
#include "cMain.h"
#include <fstream>

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_MENU(10001, cMain::OnMenuNew)
EVT_MENU(10002, cMain::OnMenuOpen)
EVT_MENU(10003, cMain::OnMenuSave)
EVT_MENU(10004, cMain::OnMenuExit)
EVT_MENU(10005, cMain::OnMenuSaveAs)
EVT_BUTTON(10006, cMain::OnButtonClicked)
EVT_BUTTON(10007, cMain::OnUploadButtonClicked)
EVT_BUTTON(10008, cMain::OnDrawNewButtonClicked)
EVT_BUTTON(10009, cMain::OnCollectDataButtonClicked)
EVT_BUTTON(10010, cMain::OnClearImageButtonClicked)
EVT_BUTTON(10011, cMain::OnTrainButtonClicked)
EVT_BUTTON(10013, cMain::OnTrainForTimeButtonClicked)
EVT_BUTTON(10014, cMain::OnEvaluateAccuracyButton)
EVT_BUTTON(10015, cMain::OnLoadDataButton)
wxEND_EVENT_TABLE()

using namespace std::chrono;

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Neural Network", wxPoint(30, 30), wxSize(1100, 1000))
{
	//Add a menu bar
	m_MenuBar = new wxMenuBar();
	this->SetMenuBar(m_MenuBar);

	// Add Menu for file operations
	wxMenu* menuFile = new wxMenu();
	menuFile->Append(10001, "New");
	menuFile->Append(10002, "Open");
	//menuFile->Append(10003, "Save");
	//menuFile->Append(10005, "Save As...");
	menuFile->Append(10004, "Exit");

	// Add File Menu to Menu Bar
	m_MenuBar->Append(menuFile, "File");

	// Add a toolbar for palette
	/*
	m_ToolBar = this->CreateToolBar(wxTB_HORIZONTAL, wxID_ANY);

	wxColour palette[16];
	palette[0] = wxColour(0, 0, 0);
	palette[1] = wxColour(0, 0, 128);
	palette[2] = wxColour(0, 128, 0);
	palette[3] = wxColour(0, 128, 128);
	palette[4] = wxColour(128, 0, 0);
	palette[5] = wxColour(128, 0, 128);
	palette[6] = wxColour(128, 128, 0);
	palette[7] = wxColour(192, 192, 192);
	palette[8] = wxColour(128, 128, 128);
	palette[9] = wxColour(0, 0, 225);
	palette[10] = wxColour(0, 255, 0);
	palette[11] = wxColour(0, 255, 255);
	palette[12] = wxColour(255, 0, 0);
	palette[13] = wxColour(255, 0, 255);
	palette[14] = wxColour(255, 255, 0);
	palette[15] = wxColour(255, 255, 255);

	for (int i = 0; i < 16; i++) {
		wxButton* b = new wxButton(m_ToolBar, 10100 + i, "", wxDefaultPosition, wxSize(40, 24), 0);
		b->SetBackgroundColour(palette[i]);
		b->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::OnSelectColour), nullptr, this);
		m_ToolBar->AddControl(b);
	}

	wxButton* b = new wxButton(m_ToolBar, 10100 + 16, "ALPHA", wxDefaultPosition, wxDefaultSize, 0);
	b->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(cMain::OnSelectColour), nullptr, this);

	
	m_ToolBar->AddControl(b);
	
	m_ToolBar->Realize();
	*/

	int height_difference = -30;

	//text entry box, add button, list box
	m_btn1 = new wxButton(this, 10006, "Add Category", wxPoint(630, 150 + height_difference), wxSize(300, 30));
	m_txt1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(630, 110 + height_difference), wxSize(300, 30));
	m_list1 = new wxListBox(this, wxID_ANY, wxPoint(10, 110 + height_difference), wxSize(300, 300));
	m_list2 = new wxListBox(this, wxID_ANY, wxPoint(320, 110 + height_difference), wxSize(300, 300));
	//removeLastItem = new wxButton(this, 10016, "Remove Last Category", wxPoint(630, 190 + height_difference), wxSize(300, 30));

	//layers entry list


	//title
	//title = new wxTextCtrl(this, wxID_ANY, "No Network Open", wxPoint(10, 10), wxSize(300, 30));

	//upload button and image
	uploadButton = new wxButton(this, 10007, "Load Image", wxPoint(320, 450 + height_difference), wxSize(300, 30));
	//drawPanel = new wxPanel(this, wxID_ANY, wxPoint(10, 490), wxSize(300, 300), wxTAB_TRAVERSAL, "Name");

	//upload result text box
	recognition_Result = new wxTextCtrl(this, wxID_ANY, "Result: ", wxPoint(320, 610 + height_difference), wxSize(300, 30), wxTE_READONLY);
	confidence_Result_Display = new wxTextCtrl(this, wxID_ANY, "Confidence: ", wxPoint(320, 650 + height_difference), wxSize(300, 30), wxTE_READONLY);

	//image that is being evaluated
	uploadedImage = new wxBitmap(300, 300);
	evaluatedImage = new eventableStaticBitmap(this, wxID_ANY, *uploadedImage, wxPoint(10, 450 + height_difference), wxSize(300, 300), 0, "Evaluated Image");

	//button for drawing new image
	draw_new_image_button = new wxButton(this, 10008, "Recognize Image", wxPoint(320, 530 + height_difference), wxSize(300, 30));
	clear_image_button = new wxButton(this, 10010, "Clear Image", wxPoint(320, 490 + height_difference), wxSize(300, 30));
	
	//debug output
	//collect_data_button = new wxButton(this, 10009, "Add drawing to the collection", wxPoint(10, 760 + height_difference), wxSize(300, 30));
	//debug = new wxTextCtrl(this, wxID_ANY, "Add this drawing to the collection: ", wxPoint(10, 800 + height_difference), wxSize(300, 30), wxTE_READONLY);
	srand(time(0));

	//button and text for training
	//trainModelButton = new wxButton(this, 10011, "Train for one gradient step", wxPoint(10, 880 + height_difference), wxSize(300, 30));
	//trainTime = new wxTextCtrl(this, wxID_ANY, "Step train time: ", wxPoint(10, 920 + height_difference), wxSize(300, 30));
	trainForTimeButton = new wxButton(this, 10013, "Train for 30 epochs", wxPoint(10, 760 + height_difference), wxSize(300, 30));
	trainAccuracy = new wxTextCtrl(this, wxID_ANY, "Accuracy: ", wxPoint(10, 800 + height_difference), wxSize(300, 30));
	evaluateAccuracyButton = new wxButton(this, 10014, "Evaluate Accuracy", wxPoint(10, 840 + height_difference), wxSize(300, 30));
	loadData = new wxButton(this, 10015, "Load Data", wxPoint(320, 760 + height_difference), wxSize(300, 30));

	//trainTimeGet = new wxTextCtrl(this, wxID_ANY, "", wxPoint(320, 920 + height_difference), wxSize(300, 30));
	srand(time(0));
}

cMain::~cMain()
{
	delete uploadedImage;
	delete activeModel;
}

void cMain::OnMenuNew(wxCommandEvent& evt)
{
	vector<int> sizes;
	sizes.push_back(784);
	sizes.push_back(30);
	sizes.push_back(10);
	activeModel = new NeuralModel(sizes);
	/*
	if (activeModel == nullptr) {
		//create a new model
		activeModel = new NeuralModel();
	}
	else {
		// idea: prompt the user if they want to save the current model first
		delete activeModel;

		//create a new model
		activeModel = new NeuralModel();
	}

	// TODO: update the on-screen information about the model
	m_list1->Clear();
	*/
}

void cMain::OnMenuOpen(wxCommandEvent& evt)
{
	//set title to be the title of the neural network from the file
	wxFileDialog dlg(this, "Open txt File", "", "", ".txt Files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (dlg.ShowModal() == wxID_OK)
	{
		if (activeModel == nullptr) {
			vector<int> sizes;
			sizes.push_back(784);
			sizes.push_back(30);
			sizes.push_back(10);
			activeModel = new NeuralModel(sizes);

			//set all the weights and biases to be equal to the file
			wxString fileName = dlg.GetPath();
			ifstream modelFile;
			modelFile.open(fileName.ToStdString());

			for (int i = 0; i < activeModel->weights.size(); i++) {
				for (int j = 0; j < activeModel->weights[i].size(); j++) {
					for (int k = 0; k < activeModel->weights[i][j].size(); k++) {
						modelFile >> activeModel->weights[i][j][k];
					}
				}
			}

			for (int i = 0; i < activeModel->biases.size(); i++) {
				for (int j = 0; j < activeModel->biases[i].size(); j++) {
					modelFile >> activeModel->biases[i][j];
				}
			}

			for (int i = 0; i < 10000; i++) {
				NeuralModel::training_data_type newEntry;
				//for every activation (784)
				for (int j = 0; j < 784; j++) {
					float input = 0;
					modelFile >> input;
					newEntry.activations.push_back(input);
				}

				//for every answer (10)
				for (int j = 0; j < 10; j++) {
					float input = 0;
					modelFile >> input;
					newEntry.correct_answer.push_back(input);
				}
				activeModel->training_data.push_back(newEntry);
			}
		}
	}

	/*
	wxFileDialog dlg(this, "Open txt File", "", "", ".txt Files (*.txt)|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (dlg.ShowModal() == wxID_OK)
	{
		if (activeModel == nullptr) {
			//create a new model
			activeModel = new NeuralModel(dlg.GetPath());
		}
		else {
			// idea: prompt the user if they want to save the current model first
			delete activeModel;

			//create a new model
			activeModel = new NeuralModel(dlg.GetPath());
		}

		//initialize the data collection system
		collect_index = rand() % activeModel->categories.size();
		debug->Clear();
		*debug << "Add this drawing to the data: " << activeModel->categories[collect_index];

		// TODO: update the on-screen information about the model
		//list of category names
		m_list1->Clear();
		for (int i = 0; i < activeModel->categories.size(); i++) {
			m_list1->AppendString(activeModel->categories[i]);
		}

		//list of category folders
		m_list2->Clear();
		for (int i = 0; i < activeModel->fileNames.size(); i++) {
			m_list2->AppendString(activeModel->fileNames[i]);
		}
	}
	*/

	evt.Skip();
}

void cMain::OnMenuSave(wxCommandEvent& evt)
{
	//get the title of the model from title->GetValue()
	if (activeModel != nullptr) {
		if (activeModel->fileName != "DefaultName") {
			// Automatically Save File
			activeModel->saveModel(activeModel->fileName);
		}
		else {
			// Save with dialogue
			wxFileDialog dlg(this, "Save txt File", "", "", ".txt Files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
			if (dlg.ShowModal() == wxID_OK)
			{
				activeModel->saveModel(dlg.GetPath());
			}
		}
	}
}

void cMain::OnMenuExit(wxCommandEvent& evt)
{
	Close();
	evt.Skip();
}

void cMain::OnMenuSaveAs(wxCommandEvent& evt)
{
	if (activeModel != nullptr) {
		// Save with dialogue
		wxFileDialog dlg(this, "Save txt File", "", "", ".txt Files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
		if (dlg.ShowModal() == wxID_OK)
		{
			activeModel->saveModel(dlg.GetPath());
		}
	}
}

void cMain::OnMenuUpload(wxCommandEvent& evt)
{
}

void cMain::OnMenuDraw(wxCommandEvent& evt)
{
}

void cMain::OnUploadButtonClicked(wxCommandEvent& evt)
{
	if (activeModel != nullptr) {
		wxFileDialog dlg(this, "Open image File", "", "", "*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
		if (dlg.ShowModal() == wxID_OK)
		{
			wxInitAllImageHandlers();

			// read the image into the activation vector
			vector<float> image_activation;
			wxImage input_Image;
			input_Image.LoadFile(dlg.GetPath());

			//rescale the image to a width and height of 28
			input_Image.Rescale(28, 28, wxIMAGE_QUALITY_NEAREST);
			assert(input_Image.GetWidth() == 28);
			assert(input_Image.GetHeight() == 28);

			int RGB = 1;
			float R = 0;
			float G = 0;
			float B = 0;
			float GrayScale = 0;
			unsigned char* input_Image_Data = input_Image.GetData();
			for (int i = 0; i < input_Image.GetWidth() * input_Image.GetHeight() * 3; i++) {


				int value = input_Image_Data[i];
				switch (RGB) {
				case 1:
					R = value;
					RGB++;
					break;
				case 2:
					G = value;
					RGB++;
					break;
				case 3:
					B = value;
					GrayScale = (R + G + B) / 3;
					input_Image_Data[i - 2] = GrayScale;
					input_Image_Data[i - 1] = GrayScale;
					input_Image_Data[i] = GrayScale;
					image_activation.push_back(GrayScale / 255);

					RGB = 1;
					break;
				}
			}

			//pass this data to the drawing
			*(evaluatedImage->drawing) = input_Image;

			//rescale the image to a width and height of 300
			input_Image.Rescale(300, 300, wxIMAGE_QUALITY_NEAREST);
			assert(input_Image.GetWidth() == 300);
			assert(input_Image.GetHeight() == 300);

			//display the image to the screen
			wxBitmap input_Image_Bitmap(input_Image);
			evaluatedImage->SetBitmap(input_Image_Bitmap);
		}
	}
	evt.Skip();
}

void cMain::OnSelectColour(wxCommandEvent& evt)
{
	int colour = evt.GetId() - 10100;
}

void cMain::OnButtonClicked(wxCommandEvent& evt) {
	//Add the category to the list
	if (m_txt1->GetValue() != "") {
		if (activeModel != nullptr) {
			activeModel->categories.push_back(m_txt1->GetValue());
			//Select the directory that corresponds to the category
			wxDirDialog dlg(this, _("Choose a folder that contains images of the category"), "", 0, wxDefaultPosition);
			if (dlg.ShowModal() == wxID_OK)
			{
				std::string stlstring = std::string(dlg.GetPath().mb_str());
				activeModel->fileNames.push_back(stlstring);

			}
			//list of category names
			m_list1->Clear();
			for (int i = 0; i < activeModel->categories.size(); i++) {
				m_list1->AppendString(activeModel->categories[i]);
			}
			//list of category folders
			m_list2->Clear();
			for (int i = 0; i < activeModel->fileNames.size(); i++) {
				m_list2->AppendString(activeModel->fileNames[i]);
			}
			/*
			if (activeModel->categories.size() == 1) {
				//update the data collection system
				collect_index = rand() % activeModel->categories.size();
				debug->Clear();
				*debug << "Add this drawing to the data: " << activeModel->categories[collect_index];
			}
			*/
		}
	}

	evt.Skip();
}

void cMain::OnDrawNewButtonClicked(wxCommandEvent& evt) {
	if (activeModel != nullptr) {
		if (activeModel->categories.size() != 0) {
			// read the image into the activation vector
			vector<long double> image_activation;
			wxImage input_Image(*(evaluatedImage->drawing));

			//rescale the image to a width and height of 28
			input_Image.Rescale(28, 28, wxIMAGE_QUALITY_NEAREST);
			assert(input_Image.GetWidth() == 28);
			assert(input_Image.GetHeight() == 28);

			int RGB = 1;
			float R = 0;
			float G = 0;
			float B = 0;
			float GrayScale = 0;
			unsigned char* input_Image_Data = input_Image.GetData();
			for (int i = 0; i < input_Image.GetWidth() * input_Image.GetHeight() * 3; i++) {


				int value = input_Image_Data[i];
				switch (RGB) {
				case 1:
					R = value;
					RGB++;
					break;
				case 2:
					G = value;
					RGB++;
					break;
				case 3:
					B = value;
					GrayScale = (R + G + B) / 3;
					input_Image_Data[i - 2] = GrayScale;
					input_Image_Data[i - 1] = GrayScale;
					input_Image_Data[i] = GrayScale;
					image_activation.push_back(GrayScale / 255);

					RGB = 1;
					break;
				}
			}

			// TODO: update the on-screen information about the model
			float confidence_Result = 0;
			//recognition_Result->ChangeValue(activeModel->recognize(image_activation, confidence_Result));
			recognition_Result->Clear();
			vector<long double> feedForwardResult;
			feedForwardResult = activeModel->feedforward(image_activation);
			//find the most activated element in feedForwardResult
			//use it's index to get the index of the category wxString
			int highestIndex = 0;
			float highestActivation = 0;
			for (int i = 0; i < feedForwardResult.size(); i++) {
				if (feedForwardResult[i] > highestActivation) {
					highestIndex = i;
					highestActivation = feedForwardResult[i];
				}
			}
			(*recognition_Result) << "Result: " << activeModel->categories[highestIndex]; 
			//(*recognition_Result) << "Result: " << activeModel->recognize(image_activation, confidence_Result);
			confidence_Result_Display->Clear();
			(*confidence_Result_Display) << "Confidence: " << highestActivation;
		}
	}
}

void cMain::OnCollectDataButtonClicked(wxCommandEvent& evt) {
	//save the image held in drawing under the correct folder
	wxInitAllImageHandlers();
	wxString saveName = activeModel->fileNames[collect_index];
	milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	saveName << "\\" << "Colection" << ms.count() << ".png";
	evaluatedImage->drawing->SaveFile(saveName, wxBITMAP_TYPE_PNG);

	//clear the image
	evaluatedImage->drawing->Clear();
	wxImage finished = evaluatedImage->drawing->Scale(300, 300, wxIMAGE_QUALITY_NEAREST);
	evaluatedImage->SetBitmap(finished);
	
	//update the data collection system
	collect_index = rand() % activeModel->categories.size();
	debug->Clear();
	*debug << "Add this drawing to the collection: " << activeModel->categories[collect_index];
}

void cMain::OnClearImageButtonClicked(wxCommandEvent& evt)
{
	evaluatedImage->drawing->Clear();
	wxImage finished = evaluatedImage->drawing->Scale(300, 300, wxIMAGE_QUALITY_NEAREST);
	evaluatedImage->SetBitmap(finished);
}

void cMain::OnTrainButtonClicked(wxCommandEvent& evt) {

	/*
	milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	activeModel->updateModel();
	milliseconds msPrime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	trainTime->Clear();
	*trainTime << "Step train time: " << (int)(msPrime.count() - ms.count());
	*/
	/*
	milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	activeModel->createTrainingSample();
	activeModel->createMutants();
	activeModel->SelectMutants();
	activeModel->destroyMutants();
	milliseconds msPrime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	trainTime->Clear();
	*trainTime << "Gen train time: " << (int)(msPrime.count() - ms.count());
	*/
}

void cMain::OnTrainForTimeButtonClicked(wxCommandEvent& evt) {
	if (activeModel->training_data.size() == 0) {
		vector<NeuralModel::training_data_type> validation_data;
		activeModel->load_data_wrapper(activeModel->training_data, validation_data, activeModel->test_data);
		activeModel->SGD(activeModel->training_data, 30, 10, 3.0, activeModel->test_data);
	}
	else {
		activeModel->SGD(activeModel->training_data, 30, 10, 3.0, activeModel->test_data);
	}

	/*
	unsigned long long int millisecondsTimer = 0;
	if (trainTimeGet->GetValue() == "") {
		return;
	}
	if ((trainTimeGet->GetValue()).ToULongLong(&millisecondsTimer) == false) {
		return;
	}
	millisecondsTimer = millisecondsTimer * 60 * 1000;
	if (activeModel != nullptr) {
		milliseconds startTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

		while (true) {
			milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			if (ms.count() - startTime.count() > millisecondsTimer) {
				break;
			}
			activeModel->updateModel();
			milliseconds msPrime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			trainTime->Clear();
			*trainTime << "Step train time: " << (int)(msPrime.count() - ms.count());
			//trainAccuracy->Clear();
			//*trainAccuracy << "Accuracy: " << activeModel->accuracy;
		}
	}
	*/
	/*
	unsigned long long int millisecondsTimer = 0;
	if (trainTimeGet->GetValue() == "") {
		return;
	}
	if ((trainTimeGet->GetValue()).ToULongLong(&millisecondsTimer) == false) {
		return;
	}
	millisecondsTimer = millisecondsTimer * 60 * 1000;
	if (activeModel != nullptr) {
		milliseconds startTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

		while (true) {
			milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			if (ms.count() - startTime.count() > millisecondsTimer) {
				break;
			}
			activeModel->createTrainingSample();
			activeModel->createMutants();
			activeModel->SelectMutants();
			activeModel->destroyMutants();
			milliseconds msPrime = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			trainTime->Clear();
			*trainTime << "Gen train time: " << (int)(msPrime.count() - ms.count());
			trainAccuracy->Clear();
			*trainAccuracy << "Accuracy: " << activeModel->accuracy;
		}
	}
	*/
}

void cMain::OnEvaluateAccuracyButton(wxCommandEvent& evt) {
	if (activeModel != nullptr) {
		if (activeModel->training_data.size() == 0) {
			vector<NeuralModel::training_data_type> validation_data;
			activeModel->load_data_wrapper(activeModel->training_data, validation_data, activeModel->test_data);
			trainAccuracy->Clear();
			float answer = activeModel->evaluate(activeModel->test_data);
			*trainAccuracy << "Accuracy: " << answer;
		}
		else {
			trainAccuracy->Clear();
			float answer = activeModel->evaluate(activeModel->test_data);
			*trainAccuracy << "Accuracy: " << answer;
		}
	}

	/*
	activeModel->createTrainingWhole();
	activeModel->evaluateTrainingAccuracy();
	//calling evaluateTrainingAccuracy() will automatically delete the trainingWhole
	trainAccuracy->Clear();
	*trainAccuracy << "Accuracy: " << activeModel->accuracy;
	*trainAccuracy << " Cost: " << activeModel->averageCostFunction;
	*/
}

void cMain::OnLoadDataButton(wxCommandEvent& evt) {
	if (activeModel->training_data.size() == 0) {
		vector<NeuralModel::training_data_type> validation_data;
		activeModel->load_data_wrapper(activeModel->training_data, validation_data, activeModel->test_data);
	}
}
