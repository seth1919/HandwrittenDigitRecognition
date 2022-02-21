#include <string>
#include "wx/wx.h"
#include "NeuronLayer.h"
#include <vector>
#include <filesystem>
#include <random>
#include <algorithm>
#include <math.h>

using namespace std;

#pragma once
class NeuralModel
{
public:
	NeuralModel();
	NeuralModel(wxString fileNameCopy);
	NeuralModel(NeuralModel& copy);
	NeuralModel(NeuralModel& copy, bool zeroes);
	~NeuralModel();
	bool saveModel(wxString fileNameCopy);
	wxString recognize(vector<long double>& image, long double& confidence);
	NeuralModel& operator = (const NeuralModel& copy);

	vector<wxString> categories;
	vector<string> fileNames;
	vector<NeuronLayer> layers;
	wxString fileName = "DefaultName";
	vector<vector<vector<long double>>> trainingSample;
	vector<vector<vector<long double>>> trainingWhole;
	vector<NeuralModel*> mutants;
	vector<wxString> correctlyIdentified;
	long double accuracy = 0;
	long double previousAverageCostFunction = 50;
	long double averageCostFunction = 50;


	long double costFunction(NeuralModel* active_Model, vector<long double>& trainingImage, int correctIndex);
	void createTrainingSample();
	void createMutants();
	void SelectMutants();
	void destroyMutants();
	void createTrainingWhole();
	void evaluateTrainingAccuracy();
	void createMiniBatches(vector<vector<vector<long double>>>& miniBatches);
	void averageGradients(NeuralModel& averageDeltaModel, vector<vector<vector<long double>>>& minibatches);
	void updateModel();

	//for mutant training:
	//currently using 100 training images of each category
	//currently using 100 mutant neural networks




	//python translation starts here

	//def __init__(self, sizes):
	//variables for this function
	int num_layers = 0;
	vector<int> sizes;
	vector<vector<long double>> biases;
	vector<vector<vector<long double>>> weights;
	NeuralModel(vector<int> sizes) {
		num_layers = sizes.size();
		this->sizes = sizes;
		//for every layer except the first
		for (int i = 1; i < num_layers; i++) {
			//create a new matrix of biases for this layer
			vector<long double> newMatrix;
			//initialize the matrix
			random_device rd;
			mt19937 gen(rd());
			normal_distribution<long double> d(0, 1);
			for (int j = 0; j < sizes[i]; j++) {
				newMatrix.push_back(d(gen));
			}
			//add the matrix of biases to the list of biases
			biases.push_back(newMatrix);
		}
		//for every layer except the first
		for (int i = 1; i < num_layers; i++) {
			//create a new 2d matrix [neuron, weight] for the layer
			vector<vector<long double>> newLayer;
			//initialize the 2d matrix
			for (int j = 0; j < sizes[i]; j++) {
				//create a 1d matrix of weights for this neuron
				vector<long double> thisNeuronWeights;
				random_device rd;
				mt19937 gen(rd());
				normal_distribution<long double> d(0, 1);
				for (int k = 0; k < sizes[i - 1]; k++) {
					//populate the 1d matrix
					thisNeuronWeights.push_back(d(gen));
				}
				//add the 1d matrix of weights for this neuron
				newLayer.push_back(thisNeuronWeights);
			}
			//add the 2d matrix of weights to the list of weights
			weights.push_back(newLayer);
		}
	}

	//def feedforward(self, a):
	vector<long double> feedforward(vector<long double> a) {
		//for every layer, apply the weight matrix to the activations, add the bias, apply the sigmoid
		//(equation 25 in chapter 2)
		for (int i = 0; i < num_layers - 1; i++) {
			//new activation vector
			vector<long double> aPrime;
			//for every row of this layer's weight vector (neuron)
			for (int j = 0; j < weights[i].size(); j++) {
				long double dotSum = 0;
				//for every column of the row (weight on the neuron)
				for (int k = 0; k < weights[i][j].size(); k++) {
					dotSum += (weights[i][j][k] * a[k]);
				}
				dotSum += biases[i][j];
				aPrime.push_back(dotSum);
			}
			a = sigmoid(aPrime);
		}
		return a;
	}

	//training_data structure
	struct training_data_type {
		vector<long double> activations;
		vector<long double> correct_answer;
	};

	//def SGD(self, training_data, epochs, mini_batch_size, eta, test_data=None):
	void SGD(vector<training_data_type> training_data, int epochs, int mini_batch_size, long double eta, vector<training_data_type> test_data) {
		//int n_test = test_data.size();
		int n = training_data.size();
		auto rd = random_device{};
		auto rng = default_random_engine{ rd() };
		for (int i = 0; i < epochs; i++) {
			//shuffle the training_data
			shuffle(begin(training_data), end(training_data), rng);
			vector<vector<training_data_type>> mini_batches;
			int training_data_index = 0;
			while (training_data_index + mini_batch_size < n) {
				vector<training_data_type> mini_batch;
				for (int j = 0; j < mini_batch_size; j++) {
					mini_batch.push_back(training_data[training_data_index]);
					training_data_index++;
				}
				mini_batches.push_back(mini_batch);
			}
			for (int j = 0; j < mini_batches.size(); j++) {
				update_mini_batch(mini_batches[j], eta);
			}
			//print the progress
		}
	}

	//def update_mini_batch(self, mini_batch, eta):
	void update_mini_batch(vector<training_data_type> mini_batch, long double eta) {
		vector<vector<long double>> nabla_b;
		for (int i = 0; i < biases.size(); i++) {
			vector<long double> newVector;
			for (int j = 0; j < biases[i].size(); j++) {
				newVector.push_back(0.0);
			}
			nabla_b.push_back(newVector);
		}
		vector<vector<vector<long double>>> nabla_w;
		for (int i = 0; i < weights.size(); i++) {
			vector<vector<long double>> newVectorVector;
			for (int j = 0; j < weights[i].size(); j++) {
				vector<long double> newVector;
				for (int k = 0; k < weights[i][j].size(); k++) {
					newVector.push_back(0.0);
				}
				newVectorVector.push_back(newVector);
			}
			nabla_w.push_back(newVectorVector);
		}
		//for every single example in mini_batch, pass the x and y to packprop
		for (int i = 0; i < mini_batch.size(); i++) {
			vector<vector<long double>> delta_nabla_b;
			vector<vector<vector<long double>>> delta_nabla_w;
			backprop(mini_batch[i].activations, mini_batch[i].correct_answer, delta_nabla_b, delta_nabla_w);
			//add delta_nabla_b to nabla_b
			for (int j = 0; j < nabla_b.size(); j++) {
				for (int k = 0; k < nabla_b[j].size(); k++) {
					nabla_b[j][k] += delta_nabla_b[j][k];
				}
			}
			//add delta_nabla_w to nabla_w
			for (int j = 0; j < nabla_w.size(); j++) {
				for (int k = 0; k < nabla_w[j].size(); k++) {
					for (int l = 0; l < nabla_w[j][k].size(); l++) {
						nabla_w[j][k][l] += delta_nabla_w[j][k][l];
					}
				}
			}
		}
		for (int i = 0; i < biases.size(); i++) {
			for (int j = 0; j < biases[i].size(); j++) {
				biases[i][j] = biases[i][j] - (eta / (long double)mini_batch.size()) * nabla_b[i][j];
			}
		}
		for (int i = 0; i < weights.size(); i++) {
			for (int j = 0; j < weights[i].size(); j++) {
				for (int k = 0; k < weights[i][j].size(); k++) {
					weights[i][j][k] = weights[i][j][k] - (eta / (long double)mini_batch.size()) * nabla_w[i][j][k];
				}
			}
		}
	}

	//def backprop(self, x, y)
	void backprop(vector<long double> x, vector<long double> y, vector<vector<long double>>& nabla_b, vector<vector<vector<long double>>>& nabla_w) {
		nabla_b.clear();
		for (int i = 0; i < biases.size(); i++) {
			vector<long double> newVector;
			for (int j = 0; j < biases[i].size(); j++) {
				newVector.push_back(0.0);
			}
			nabla_b.push_back(newVector);
		}
		nabla_w.clear();
		for (int i = 0; i < weights.size(); i++) {
			vector<vector<long double>> newVectorVector;
			for (int j = 0; j < weights[i].size(); j++) {
				vector<long double> newVector;
				for (int k = 0; k < weights[i][j].size(); k++) {
					newVector.push_back(0.0);
				}
				newVectorVector.push_back(newVector);
			}
			nabla_w.push_back(newVectorVector);
		}
		vector<long double> activation = x;
		vector<vector<long double>> activations;
		vector<long double> newVector;
		for (int i = 0; i < x.size(); i++) {
			newVector.push_back(x[i]);
		}
		activations.push_back(newVector);
		vector<vector<long double>> zs;
		for (int i = 0; i < biases.size(); i++) {
			vector<long double> z;
			//for every neuron
			for (int j = 0; j < weights[i].size(); j++) {
				long double zSum = 0;
				//for every weight on the neuron
				for (int k = 0; k < weights[i][j].size(); k++) {
					zSum += weights[i][j][k] * activation[k];
				}
				zSum += biases[i][j];
				z.push_back(zSum);
			}
			zs.push_back(z);
			activation = sigmoid(z);
			activations.push_back(activation);
		}
		vector<long double> delta = cost_derivative(activations[activations.size() - 1], y);
		vector<long double> zsSigmoid_Prime = sigmoid_prime(zs[zs.size() - 1]);
		for (int j = 0; j < delta.size(); j++) {
			delta[j] *= zsSigmoid_Prime[j];
		}
		nabla_b[nabla_b.size() - 1] = delta;
		vector<vector<long double>> nabla_wNew;
		for (int i = 0; i < delta.size(); i++) {
			vector<long double> neuronDeltaWeights;
			for (int j = 0; j < activations[activations.size() - 2].size(); j++) {
				neuronDeltaWeights.push_back(delta[i] * activations[activations.size() - 2][j]);
			}
			nabla_wNew.push_back(neuronDeltaWeights);
		}
		nabla_w[nabla_w.size() - 1] = nabla_wNew;
		for (int l = 2; l < num_layers; l++) {
			vector<long double> z = zs[zs.size() - l];
			vector<long double> sp = sigmoid_prime(z);
			vector<long double> deltaNew;
			//for every of the 30 weights
			for (int i = 0; i < weights[weights.size() - l].size(); i++) {
				long double dotSum = 0;
				//for every of the 10 neurons in the previous row and 10 delta
				for (int j = 0; j < weights[weights.size() - l + 1].size(); j++) {
					dotSum += weights[weights.size() - l + 1][j][i] * delta[j];
				}
				deltaNew.push_back(dotSum);
			}
			/*
			for (int i = 0; i < weights[weights.size() - l + 1].size(); i++) {
				long double dotSum = 0;
				for (int j = 0; j < weights[weights.size() - l + 1][i].size(); j++) {
					dotSum += weights[weights.size() - l + 1][i][j] * delta[j];
				}
				deltaNew.push_back(dotSum);
			}
			*/
			for (int i = 0; i < deltaNew.size(); i++) {
				deltaNew[i] *= sp[i];
			}
			delta = deltaNew;
			nabla_b[nabla_b.size() - l] = delta;
			vector<vector<long double>> nabla_wNewNew;
			for (int i = 0; i < delta.size(); i++) {
				vector<long double> vector_unique;
				for (int j = 0; j < activations[activations.size() - l - 1].size(); j++) {
					vector_unique.push_back(delta[i] * activations[activations.size() - l - 1][j]);
				}
				nabla_wNewNew.push_back(vector_unique);
			}
			nabla_w[nabla_w.size() - l] = nabla_wNewNew;
		}
	}

	vector<long double> sigmoid(vector<long double> z) {
		for (int i = 0; i < z.size(); i++) {
			z[i] = 1.0 / (1.0 + exp(-(z[i])));
		}
		return z;
	}

	vector<long double> cost_derivative(vector<long double> output_activations, vector<long double> y) {
		for (int i = 0; i < output_activations.size(); i++) {
			output_activations[i] -= y[i];
		}
		return output_activations;
	}

	vector<long double> sigmoid_prime(vector<long double> z) {
		vector<long double> sigmoid_Z = sigmoid(z);
		vector<long double> oneMinusSigmoid_Z = z;
		for (int i = 0; i < oneMinusSigmoid_Z.size(); i++) {
			oneMinusSigmoid_Z[i] = 1.0 - sigmoid_Z[i];
		}
		for (int i = 0; i < z.size(); i++) {
			z[i] = sigmoid_Z[i] * oneMinusSigmoid_Z[i];
		}
		return z;
	}

	vector<training_data_type> training_data;
	vector<training_data_type> test_data;

	//def load_data_wrapper():
	void load_data_wrapper(vector<training_data_type>& training_data, vector<training_data_type>& validation_data, vector<training_data_type>& test_data) {
		training_data.clear();
		validation_data.clear();
		test_data.clear();
		wxInitAllImageHandlers();

		//for each category
		for (int i = 0; i < biases[biases.size() - 1].size(); i++) {
			//create a vector of all the file names in the category
			vector<wxString> names;
			copyFileNames(fileNames[i], names);
			//select x random indexes with no duplicates
			vector<int> indices;
			for (int j = 0; j < names.size(); j++) {
				indices.push_back(j);
			}
			for (int j = 0; j < indices.size(); j++) {
				int swapIndex = rand() % indices.size();
				int temp = indices[j];
				indices[j] = indices[swapIndex];
				indices[swapIndex] = temp;
			}
			//open those x random indices and read the image into an activation vector
			for (int j = 0; j < 3000; j++) {
				vector<long double> image_activation;
				wxImage input_Image;
				wxString fileName1 = fileNames[i];
				fileName1 << "\\" << names[indices[j]];
				input_Image.LoadFile(fileName1);
				//rescale the image to a width and height of 28
				input_Image.Rescale(28, 28, wxIMAGE_QUALITY_NEAREST);
				assert(input_Image.GetWidth() == 28);
				assert(input_Image.GetHeight() == 28);
				int RGB = 1;
				long double R = 0;
				long double G = 0;
				long double B = 0;
				long double GrayScale = 0;
				unsigned char* input_Image_Data = input_Image.GetData();
				for (int k = 0; k < input_Image.GetWidth() * input_Image.GetHeight() * 3; k++) {


					int value = input_Image_Data[k];
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
						input_Image_Data[k - 2] = GrayScale;
						input_Image_Data[k - 1] = GrayScale;
						input_Image_Data[k] = GrayScale;
						image_activation.push_back(GrayScale / 255);

						RGB = 1;
						break;
					}
				}
				//create a training_data_type with the image_activation vector
				//for the activation and the category (i) for the correct answer
				training_data_type newData;
				newData.activations = image_activation;
				//for every category
				vector<long double> correctData;
				for (int k = 0; k < biases[biases.size() - 1].size(); k++) {
					if (k == i) {
						correctData.push_back(1.0);
					}
					else {
						correctData.push_back(0.0);
					}
				}
				newData.correct_answer = correctData;
				training_data.push_back(newData);
			}
			for (int j = 0; j < 700; j++) {
				vector<long double> image_activation;
				wxImage input_Image;
				wxString fileName1 = fileNames[i];
				fileName1 << "\\" << names[indices[j + 3000]];
				input_Image.LoadFile(fileName1);
				//rescale the image to a width and height of 28
				input_Image.Rescale(28, 28, wxIMAGE_QUALITY_NEAREST);
				assert(input_Image.GetWidth() == 28);
				assert(input_Image.GetHeight() == 28);
				int RGB = 1;
				long double R = 0;
				long double G = 0;
				long double B = 0;
				long double GrayScale = 0;
				unsigned char* input_Image_Data = input_Image.GetData();
				for (int k = 0; k < input_Image.GetWidth() * input_Image.GetHeight() * 3; k++) {


					int value = input_Image_Data[k];
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
						input_Image_Data[k - 2] = GrayScale;
						input_Image_Data[k - 1] = GrayScale;
						input_Image_Data[k] = GrayScale;
						image_activation.push_back(GrayScale / 255);

						RGB = 1;
						break;
					}
				}
				//create a training_data_type with the image_activation vector
				//for the activation and the category (i) for the correct answer
				training_data_type newData;
				newData.activations = image_activation;
				//for every category
				vector<long double> correctData;
				for (int k = 0; k < biases[biases.size() - 1].size(); k++) {
					if (k == i) {
						correctData.push_back(1.0);
					}
					else {
						correctData.push_back(0.0);
					}
				}
				newData.correct_answer = correctData;
				test_data.push_back(newData);
			}
		}
		//still need to do validation_data and test_data to be
		//technically complete
	}

	int copyFileNames(wxString path, vector<wxString>& names)
	{
		std::vector<std::string> v;
		std::string file_name = path.ToStdString();
		read_directory(file_name, v);
		//fill names with the strings from v
		for (int i = 0; i < v.size(); i++) {
			wxString nextString = v[i];
			names.push_back(nextString);
		}
		return 0;
	}

	struct path_leaf_string
	{
		std::string operator()(const std::filesystem::directory_entry& entry) const
		{
			return entry.path().filename().string();
		}
	};

	void read_directory(const std::string& name, std::vector<std::string>& v)
	{
		std::filesystem::path p(name);
		std::filesystem::directory_iterator start(p);
		std::filesystem::directory_iterator end;
		std::transform(start, end, std::back_inserter(v), path_leaf_string());
	}

	//def evaluate(self, test_data):
	long double evaluate(vector<training_data_type> test_data) {
		long double number_of_correct_identifications = 0;
		//for all the test_data
		for (int i = 0; i < test_data.size(); i++) {
			vector<long double> feedForwardResult;
			feedForwardResult = feedforward(test_data[i].activations);
			//find the most activated element in feedForwardResult
			//use it's index to get the index of the category wxString
			int highestIndex = 0;
			long double highestActivation = 0;
			for (int j = 0; j < feedForwardResult.size(); j++) {
				if (feedForwardResult[j] > highestActivation) {
					highestIndex = j;
					highestActivation = feedForwardResult[j];
				}
			}
			int correct_index = 0;
			long double correctActivation = 0;
			//for every element in the correct answer vector
			for (int j = 0; j < test_data[i].correct_answer.size(); j++) {
				//if the activation is greater than the current greatest
				if (test_data[i].correct_answer[j] > correctActivation) {
					correctActivation = test_data[i].correct_answer[j];
					correct_index = j;
				}
			}
			if (highestIndex == correct_index) {
				number_of_correct_identifications++;
			}
		}
		return (number_of_correct_identifications / (long double)test_data.size());
	}
};



