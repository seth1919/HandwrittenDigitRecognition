#include "NeuralModel.h"
#include "PerlinNoise.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

#include <filesystem>

namespace fs = std::filesystem;

NeuralModel::NeuralModel()
{
    //set all values to defaults

    //for the first layer
    //create a new layer
    NeuronLayer firstLayer;
    //for every neuron in the layer
    for (int j = 0; j < 784; j++) {
        //create a new neuron
        Neuron newNeuron;
        //for every weight on the neuron
        for (int i = 0; i < 1; i++) {
            //create a new weight
            long double weight;
            weight = 0;
            //add the weight to the neuron
            newNeuron.weights.push_back(weight);
        }
        //create a new bias
        long double bias;
        bias = 0;
        //add the bias to the neuron
        newNeuron.bias = bias;
        //add the neuron to the model
        firstLayer.neurons.push_back(newNeuron);
    }
    //add the layer to the model
    layers.push_back(firstLayer);

    //for all middle layers (2)
    for (int k = 0; k < 2; k++) {
        //create a new layer
        NeuronLayer newLayer;
        //for all neurons on the layer (16)
        for (int j = 0; j < 16; j++) {
            //create a new neuron
            Neuron newNeuron;
            //for all the neuron's weights
            for (int i = 0; i < layers[k].neurons.size(); i++) {
                //create a new weight
                long double newWeight;
                newWeight = 0;
                //add the weight to the neuron
                newNeuron.weights.push_back(newWeight);
            }
            //create a new bias
            long double bias;
            bias = 0;
            //add the bias to the neuron
            newNeuron.bias = bias;
            //add the neuron to the layer
            newLayer.neurons.push_back(newNeuron);
        }
        //add the layer to the model
        layers.push_back(newLayer);
    }

    //for the last layer
    //create a new layer
    NeuronLayer lastLayer;
    //for every neuron in the layer
    for (int i = 0; i < categories.size(); i++) {
        //create a new neuron
        Neuron newNeuron;
        //for all the neuron's weights
        for (int j = 0; j < 16; i++) {
            //create a new weight
            long double weight;
            weight = 0;
            //add the weight to the neuron
            newNeuron.weights.push_back(weight);
        }
        //create a new bias
        long double bias;
        bias = 0;
        //add the bias to the neuron
        newNeuron.bias = bias;
        //add the neuron to the layer
        lastLayer.neurons.push_back(newNeuron);
    }
    //add the layer to the model
    layers.push_back(lastLayer);
    
    //truly random variance
    //for every layer
    for (int i = 0; i < layers.size(); i++) {
        //for every neuron in the layer
        for (int j = 0; j < layers[i].neurons.size(); j++) {
            long double change;
            int changeChance = rand() % 3;
            if (changeChance == 2) {
                change = 0.5;
            }
            else if (changeChance == 1) {
                change = 0.8;
            }
            else if (changeChance == 0) {
                change = 0.3;
            }
            //for every weight on the neuron
            for (int k = 0; k < layers[i].neurons[j].weights.size(); k++) {
                //assign a random value in range
                layers[i].neurons[j].weights[k] = ((double)4 / layers[i].neurons[j].weights.size()) * (((static_cast <long double> (rand()) / static_cast <long double> (RAND_MAX)) - change) * (double)2);
            }
            //for the bias
            layers[i].neurons[j].bias = rand() % 2;
        }
    }

    //perlin noise variance
    /*
    //for every neuron in layers[1]
    for (int k = 0; k < layers[1].neurons.size(); k++) {
        long double change;
        int changeChance = rand() % 3;
        if (changeChance == 2) {
            change = 0.5;
        }
        else if (changeChance == 1) {
            change = 0.8;
        }
        else if (changeChance == 0) {
            change = 0.3;
        }
        //create a new noisy image
        //create a perlin Noise vector
        vector<double> fullImage;
        // Define the size of the image
        unsigned int width = 60, height = 60;
        // Create a PerlinNoise object with the reference permutation vector
        PerlinNoise pn(rand());
        // Visit every pixel of the image and assign a color generated with Perlin noise
        for (unsigned int i = 0; i < height; ++i) {     // y
            for (unsigned int j = 0; j < width; ++j) {  // x
                double x = (double)j / ((double)width);
                double y = (double)i / ((double)height);

                // Typical Perlin noise
                double n = pn.noise(10 * x, 10 * y, 0.8);

                // Wood like structure
                //n = 20 * pn.noise(x, y, 0.8);
                //n = n - floor(n);

                // Map the values to the [0, 255] interval, for simplicity we use 
                // tones of grey
                fullImage.push_back(n);
            }
        }
        //loop through the first 28x28 doubles in the image
        int weightIndex = 0;
        for (int i = 0; i < 28; i++) {
            for (int j = 0; j < 28; j++) {
                //assign the next weight on the neuron the adjusted double
                layers[1].neurons[k].weights[weightIndex] = ((double)4 / layers[1].neurons[k].weights.size()) * ((fullImage[i * 28 + j] - change) * 2);
                weightIndex++;
            }
        }
    }
    //for every neuron in layers[2] and layers[3]
    for (int k = 0; k < layers[2].neurons.size(); k++) {
        long double change;
        int changeChance = rand() % 3;
        if (changeChance == 2) {
            change = 0.5;
        }
        else if (changeChance == 1) {
            change = 0.8;
        }
        else if (changeChance == 0) {
            change = 0.3;
        }
        //for every weight on the neuron
        for (int i = 0; i < layers[2].neurons[k].weights.size(); i++) {
            //assign a random value in range
            layers[2].neurons[k].weights[i] = ((double)4 / layers[2].neurons[k].weights.size()) * (((static_cast <long double> (rand()) / static_cast <long double> (RAND_MAX)) - change) * (double)2);
        }
    }
    for (int k = 0; k < layers[3].neurons.size(); k++) {
        //for every weight on the neuron
        long double change;
        int changeChance = rand() % 3;
        if (changeChance == 2) {
            change = 0.5;
        }
        else if (changeChance == 1) {
            change = 0.8;
        }
        else if (changeChance == 0) {
            change = 0.3;
        }
        for (int i = 0; i < layers[3].neurons[k].weights.size(); i++) {
            //assign a random value in range
            layers[3].neurons[k].weights[i] = ((double)4 / layers[3].neurons[k].weights.size()) * (((static_cast <long double> (rand()) / static_cast <long double> (RAND_MAX)) - change) * (double)2);
        }
    }
    */
}

NeuralModel::NeuralModel(wxString fileNameCopy)
{
    // setup
    fileName = fileNameCopy;
    ifstream modelFile;
    modelFile.open(fileNameCopy.mb_str());
    string input;
    wxString wxInput;

    //until the "categoryFiles" flag, add each line to the category list
    while(true){
        //take in the next input and check if it is the flag for the next section
        //or the eof
        modelFile >> input;
        wxInput = input;
        if (modelFile.eof() == true) {
            break;
        }
        if (input == "categoryFiles") {
            break;
        }
        categories.push_back(wxInput);
    }
    
    //until the "collectionSizes" flag, add each line to the fileNames list
    while (true) {
        //take in the next input and check if it is the flag for the next section
        //or the eof
        modelFile >> input;
        if (modelFile.eof() == true) {
            break;
        }
        if (input == "startOfModel") {
            break;
        }
        fileNames.push_back(input);
    }

    //get the number of Layers
    int numberOfLayers = 0;
    modelFile >> numberOfLayers;

    //get the number of neurons for each layer
    vector<int> layerSizes;
    //for every layer
    for (int i = 0; i < numberOfLayers; i++) {
        //get the size of the layer
        int sizeOfLayer = 0;
        modelFile >> sizeOfLayer;
        layerSizes.push_back(sizeOfLayer);
    }

    //last layerSize should equal categories.size();
    assert (layerSizes[numberOfLayers - 1] == categories.size());

    //iterate through every layer, neuron, weight/bias
    //for every layer
    for (int i = 0; i < numberOfLayers; i++) {
        //create a new layer
        NeuronLayer newLayer;

        //for every neuron
        for (int j = 0; j < layerSizes[i]; j++) {
            //create a new neuron
            Neuron newNeuron;

            //if this is not the first layer
            if (i != 0){
                //for every weight
                for (int k = 0; k < layerSizes[i - 1]; k++) {
                    //create a new weight
                    long double weight;
                    modelFile >> weight;

                    //add the new weight
                    newNeuron.weights.push_back(weight);
                }
                //create a new bias
                long double bias;
                modelFile >> bias;

                //add the new bias
                newNeuron.bias = bias;
            }
            else {
                //first layer, add dummy weights and biases
                //for every weight on the neuron (1)
                for (int i = 0; i < 1; i++) {
                    //create a new weight
                    long double weight;
                    weight = 0;

                    //add the weight to the neuron
                    newNeuron.weights.push_back(weight);
                }
                //create a new bias
                long double bias;
                bias = 0;

                //add the bias to the neuron
                newNeuron.bias = bias;
            }

            //add the new neuron
            newLayer.neurons.push_back(newNeuron);
        }

        //add the new layer
        layers.push_back(newLayer);
    }

    modelFile.close();
}

NeuralModel::NeuralModel(NeuralModel& copy){
    //copy categories
    for (int i = 0; i < copy.categories.size(); i++) {
        categories.push_back(copy.categories[i]);
    }

    //copy fileNames
    for (int i = 0; i < copy.fileNames.size(); i++) {
        fileNames.push_back(copy.fileNames[i]);
    }

    //copy layers
    for (int i = 0; i < copy.layers.size(); i++) {
        //create a new layer
        NeuronLayer newLayer;

        //for every neuron on the layer
        for (int j = 0; j < copy.layers[i].neurons.size(); j++) {
            //create a new neuron
            Neuron newNeuron;

            //if this is not the first layer
            if (i != 0){
                //for every weight (for every neuron in the previous layer)
                for (int k = 0; k < copy.layers[i].neurons[j].weights.size(); k++) {
                    //create a new weight
                    long double weight;
                    weight = copy.layers[i].neurons[j].weights[k];

                    //add the new weight
                    newNeuron.weights.push_back(weight);
                }
                //create a new bias
                long double bias;
                bias = copy.layers[i].neurons[j].bias;

                //add the new bias
                newNeuron.bias = bias;
            }
            else {
                //first layer, add dummy weights and biases
                //for every weight on the neuron (1)
                for (int i = 0; i < 1; i++) {
                    //create a new weight
                    long double weight;
                    weight = 0;

                    //add the weight to the neuron
                    newNeuron.weights.push_back(weight);
                }
                //create a new bias
                long double bias;
                bias = 0;

                //add the bias to the neuron
                newNeuron.bias = bias;
            }

            //add the new neuron
            newLayer.neurons.push_back(newNeuron);
        }

        //add the new layer
        layers.push_back(newLayer);
    }

    //copy fileName
    fileName = copy.fileName;
}

NeuralModel::NeuralModel(NeuralModel& copy, bool zeroes) {
    //copy categories
    for (int i = 0; i < copy.categories.size(); i++) {
        categories.push_back(copy.categories[i]);
    }

    //copy fileNames
    for (int i = 0; i < copy.fileNames.size(); i++) {
        fileNames.push_back(copy.fileNames[i]);
    }

    //copy layers
    for (int i = 0; i < copy.layers.size(); i++) {
        //create a new layer
        NeuronLayer newLayer;

        //for every neuron on the layer
        for (int j = 0; j < copy.layers[i].neurons.size(); j++) {
            //create a new neuron
            Neuron newNeuron;

            //if this is not the first layer
            if (i != 0) {
                //for every weight (for every neuron in the previous layer)
                for (int k = 0; k < copy.layers[i].neurons[j].weights.size(); k++) {
                    //create a new weight
                    long double weight;
                    weight = 0;

                    //add the new weight
                    newNeuron.weights.push_back(weight);
                }
                //create a new bias
                long double bias;
                bias = 0;

                //add the new bias
                newNeuron.bias = bias;
            }
            else {
                //first layer, add dummy weights and biases
                //for every weight on the neuron (1)
                for (int i = 0; i < 1; i++) {
                    //create a new weight
                    long double weight;
                    weight = 0;

                    //add the weight to the neuron
                    newNeuron.weights.push_back(weight);
                }
                //create a new bias
                long double bias;
                bias = 0;

                //add the bias to the neuron
                newNeuron.bias = bias;
            }

            //add the new neuron
            newLayer.neurons.push_back(newNeuron);
        }

        //add the new layer
        layers.push_back(newLayer);
    }

    //copy fileName
    fileName = copy.fileName;
}

NeuralModel::~NeuralModel()
{
    //destroyMutants();
}

bool NeuralModel::saveModel(wxString fileNameCopy)
{
    // setup
    fileName = fileNameCopy;
    ofstream modelFile;
    modelFile.open(fileNameCopy.mb_str(), ios::trunc);
    string output;
    wxString wxOutput;
    
    //for every category name, add it to the file
    for (int i = 0; i < categories.size(); i++) {
        wxOutput = categories[i];
        output = wxOutput;
        modelFile << output;
        modelFile << endl;
    }

    //for every category file name, add it to the file
    modelFile << "categoryFiles" << endl;
    for (int i = 0; i < fileNames.size(); i++) {
        modelFile << fileNames[i];
        modelFile << endl;
    }

    //add the flag for the start of the model
    modelFile << "startOfModel" << endl;

    //add the number of layers
    modelFile << layers.size() << endl;

    //for each layer, add the size of the layer to the file
    for (int i = 0; i < layers.size(); i++) {
        modelFile << layers[i].neurons.size() << endl;
    }

    //for each layer except the first
    for (int i = 1; i < layers.size(); i++) {
        //for each neuron in the layer
        for (int j = 0; j < layers[i].neurons.size(); j++) {
            //for each weight on the neuron
            for (int k = 0; k < layers[i].neurons[j].weights.size(); k++) {
                //add the weight
                modelFile << layers[i].neurons[j].weights[k] << endl;
            }
            //add the bias
            modelFile << layers[i].neurons[j].bias << endl;
        }
    }

    modelFile.close();
    return true;
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

NeuralModel& NeuralModel::operator=(const NeuralModel& copy)
{
    //clear and copy the categories vector
    categories.clear();
    for (int i = 0; i < copy.categories.size(); i++) {
        categories.push_back(copy.categories[i]);
    }

    //clear and copy the fileNames vector
    fileNames.clear();
    for (int i = 0; i < copy.fileNames.size(); i++) {
        fileNames.push_back(copy.fileNames[i]);
    }

    //clear and copy the layers vector
    layers.clear();
    for (int i = 0; i < copy.layers.size(); i++) {
        //create a new layer
        NeuronLayer newLayer;

        //for every neuron on the layer
        for (int j = 0; j < copy.layers[i].neurons.size(); j++) {
            //create a new neuron
            Neuron newNeuron;

            //if this is not the first layer
            if (i != 0) {
                //for every weight (for every neuron in the previous layer)
                for (int k = 0; k < copy.layers[i].neurons[j].weights.size(); k++) {
                    //create a new weight
                    long double weight;
                    weight = copy.layers[i].neurons[j].weights[k];

                    //add the new weight
                    newNeuron.weights.push_back(weight);
                }
                //create a new bias
                long double bias;
                bias = copy.layers[i].neurons[j].bias;

                //add the new bias
                newNeuron.bias = bias;
            }
            else {
                //first layer, add dummy weights and biases
                //for every weight on the neuron (1)
                for (int i = 0; i < 1; i++) {
                    //create a new weight
                    long double weight;
                    weight = 1;

                    //add the weight to the neuron
                    newNeuron.weights.push_back(weight);
                }
                //create a new bias
                long double bias;
                bias = 1;

                //add the bias to the neuron
                newNeuron.bias = bias;
            }

            //add the new neuron
            newLayer.neurons.push_back(newNeuron);
        }

        //add the new layer
        layers.push_back(newLayer);
    }

    //clear and copy the fileName
    fileName.clear();
    fileName = copy.fileName;

    //return the copied NeuralModel
    return *this;
}

long double NeuralModel::costFunction(NeuralModel* active_Model, vector<long double>& trainingImage, int correctIndex)
{
    long double confidence = 0;
    
    long double cost = 0.0;

    //for every category
    for (int i = 0; i < active_Model->categories.size(); i++) {
        //if the category is correct
        if (i == correctIndex) {
            cost = cost + (pow(active_Model->layers[layers.size() - 1].neurons[i].activation - 1.0, 2)) * active_Model->categories.size();
            // * active_Model->categories.size()
        }
        else {
            cost = cost + pow(active_Model->layers[layers.size() - 1].neurons[i].activation - 0.0, 2);
        }
    }

    return cost;
}

void NeuralModel::createTrainingSample() {
    //clear the previous data
    trainingSample.clear();
    wxInitAllImageHandlers();

    //for each category
    for (int i = 0; i < categories.size(); i++) {
        //create a vector to hold all the images in the category
        vector<vector<long double>> category_training_data;
        //create a vector of all the file names in the category
        vector<wxString> names;
        copyFileNames(fileNames[i], names);
        //select 100 random indexes with no duplicates
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
        //open those 100 random indices and read the image into an activation vector
        for (int j = 0; j < 50; j++) {
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

            //add the activation vector to the list
            category_training_data.push_back(image_activation);
        }
        //add the category vector to the trainingSample vector
        trainingSample.push_back(category_training_data);
    }
}

void NeuralModel::createMutants() {
    //create 100 copy neural networks
    for (int i = 0; i < 500; i++) {
        mutants.push_back(new NeuralModel(*this));
    }

    // CHANGE HERE
    //make the mutants differ by some perlin noise

    //make random changes to each of the networks
    //for 1/2 of the networks
    for (int i = 0; i < mutants.size() / 2; i++) {
        long double changeScale = 0;
        long double changeScaleChance = rand() % 3;
        if (changeScaleChance == 2) {
            changeScale = 2;
        }
        else if (changeScaleChance == 1) {
            changeScale = 8;
        }
        else if (changeScaleChance == 0) {
            changeScale = 20;
        }
        int variance = (rand() % 5) + 1;
        //for every layer except the first
        for (int j = 1; j < mutants[i]->layers.size(); j++) {
            //for every neuron in the layer
            for (int k = 0; k < mutants[i]->layers[j].neurons.size(); k++) {
                //for every weight on the neuron
                for (int l = 0; l < mutants[i]->layers[j].neurons[k].weights.size(); l++) {
                    if (rand() % 5 < variance) {
                        //add (positive or negative) ((1 / weights.size) / 10)
                        mutants[i]->layers[j].neurons[k].weights[l] += (((1.0 / mutants[i]->layers[j].neurons[k].weights.size()) / changeScale) * ((rand() % 3) + -1));
                    }
                }
                //for the bias on the neuron
                //for now, the bias will always be 0
                mutants[i]->layers[j].neurons[k].bias = 0;
            }
        }
    }
    //for the other 1/2 of the networks
    for (int l = mutants.size() / 2; l < mutants.size(); l++) {
        long double changeScale = 0;
        long double changeScaleChance = rand() % 3;
        if (changeScaleChance == 2) {
            changeScale = 2;
        }
        else if (changeScaleChance == 1) {
            changeScale = 8;
        }
        else if (changeScaleChance == 0) {
            changeScale = 20;
        }
        //for every neuron in layers[1]
        for (int k = 0; k < mutants[l]->layers[1].neurons.size(); k++) {
            long double change;
            int changeChance = rand() % 3;
            if (changeChance == 2) {
                change = 0.5;
            }
            else if (changeChance == 1) {
                change = 0.8;
            }
            else if (changeChance == 0) {
                change = 0.3;
            }
            //create a new noisy image
            //create a perlin Noise vector
            vector<double> fullImage;
            // Define the size of the image
            unsigned int width = 60, height = 60;
            // Create a PerlinNoise object with the reference permutation vector
            PerlinNoise pn(rand());
            // Visit every pixel of the image and assign a color generated with Perlin noise
            for (unsigned int i = 0; i < height; ++i) {     // y
                for (unsigned int j = 0; j < width; ++j) {  // x
                    double x = (double)j / ((double)width);
                    double y = (double)i / ((double)height);

                    // Typical Perlin noise
                    double n = pn.noise(10 * x, 10 * y, 0.8);

                    // Wood like structure
                    //n = 20 * pn.noise(x, y, 0.8);
                    //n = n - floor(n);

                    // Map the values to the [0, 255] interval, for simplicity we use 
                    // tones of grey
                    fullImage.push_back(floor(n));
                }
            }
            //loop through the first 28x28 doubles in the image
            int weightIndex = 0;
            for (int i = 0; i < 28; i++) {
                for (int j = 0; j < 28; j++) {
                    //assign the next weight on the neuron the adjusted double
                    mutants[l]->layers[1].neurons[k].weights[weightIndex] += (((double)4 / mutants[l]->layers[1].neurons[k].weights.size()) * ((fullImage[i * 28 + j] - change) * 2)) / (double)changeScale;
                    weightIndex++;
                }
            }
        }
        //for every neuron in layers[2] and layers[3]
        for (int k = 0; k < mutants[l]->layers[2].neurons.size(); k++) {
            long double change;
            int changeChance = rand() % 3;
            if (changeChance == 2) {
                change = 0.5;
            }
            else if (changeChance == 1) {
                change = 0.8;
            }
            else if (changeChance == 0) {
                change = 0.3;
            }
            //for every weight on the neuron
            for (int i = 0; i < mutants[l]->layers[2].neurons[k].weights.size(); i++) {
                //assign a random value in range
                mutants[l]->layers[2].neurons[k].weights[i] += (((double)4 / mutants[l]->layers[2].neurons[k].weights.size()) * (((static_cast <double> (rand()) / static_cast <double> (RAND_MAX)) - change) * 2)) / (double)changeScale;
            }
        }
        for (int k = 0; k < mutants[l]->layers[3].neurons.size(); k++) {
            long double change;
            int changeChance = rand() % 3;
            if (changeChance == 2) {
                change = 0.5;
            }
            else if (changeChance == 1) {
                change = 0.8;
            }
            else if (changeChance == 0) {
                change = 0.3;
            }
            //for every weight on the neuron
            for (int i = 0; i < mutants[l]->layers[3].neurons[k].weights.size(); i++) {
                //assign a random value in range
                mutants[l]->layers[3].neurons[k].weights[i] += (((double)4 / mutants[l]->layers[3].neurons[k].weights.size()) * (((static_cast <double> (rand()) / static_cast <double> (RAND_MAX)) - change) * 2)) / (double)changeScale;
            }
        }
    }
}

void NeuralModel::SelectMutants()
{
    //evaluate the current network
    double sumCost = 0;
    accuracy = 0;
    //for every category
    for (int i = 0; i < trainingSample.size(); i++) {
        //for every image in the category
        for (int j = 0; j < trainingSample[i].size(); j++) {
            //calculate the cost of the model upon the current image, add it to the sum
            sumCost = sumCost + costFunction(this, trainingSample[i][j], i);
        }
    }
    double averageCost = sumCost / (trainingSample[0].size() * trainingSample.size());
    accuracy = accuracy / (trainingSample.size() * trainingSample[0].size());

    //evaluate the mutated networks
    vector<double> averageMutatedCost;
    //for every model
    for (int k = 0; k < mutants.size(); k++) {
        mutants[k]->accuracy = 0;
        double MutatedsumCost = 0;
        //for every category
        for (int i = 0; i < trainingSample.size(); i++) {
            //for every image in the category
            for (int j = 0; j < trainingSample[i].size(); j++) {
                //calculate the cost of the model upon the current image, add it to the sum
                MutatedsumCost = MutatedsumCost + costFunction(mutants[k], trainingSample[i][j], i);
            }
        }
        averageMutatedCost.push_back(MutatedsumCost / (trainingSample[0].size() * trainingSample.size()));
        mutants[k]->accuracy = mutants[k]->accuracy / (trainingSample.size() * trainingSample[0].size());
    }

    //search for the best performing network
    double lowestCost = averageMutatedCost[0];
    NeuralModel* bestModel = nullptr;
    for (int i = 0; i < mutants.size(); i++) {
        //if the averageMutatedCost[i] is less than the lowestCost, make
        //the lowestCost = averageMutatedCost[i]
        if (averageMutatedCost[i] < lowestCost) {
            lowestCost = averageMutatedCost[i];
            bestModel = mutants[i];
        }
    }
    if (averageCost < lowestCost) {
        lowestCost = averageCost;
        bestModel = this;
    }

    //replace the current network with the best performing network
    (*this) = (*bestModel);
}

void NeuralModel::destroyMutants()
{
    for (int i = 0; i < mutants.size(); i++) {
        delete mutants[i];
    }
    mutants.clear();
}

//calling evaluateTrainingAccuracy() will automatically delete the trainingWhole
void NeuralModel::createTrainingWhole() {
    //clear the previous data
    trainingWhole.clear();
    wxInitAllImageHandlers();

    //for each category
    for (int i = 0; i < categories.size(); i++) {
        //create a vector to hold all the images in the category
        vector<vector<long double>> category_training_data;
        //create a vector of all the file names in the category
        vector<wxString> names;
        copyFileNames(fileNames[i], names);
        //select 100 random indexes with no duplicates
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
        //open those 100 random indices and read the image into an activation vector
        for (int j = 0; j < 700; j++) {
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

            //add the activation vector to the list
            category_training_data.push_back(image_activation);
        }
        //add the category vector to the trainingSample vector
        trainingWhole.push_back(category_training_data);
    }
}

void NeuralModel::evaluateTrainingAccuracy() {
    //evaluate the current network
    accuracy = 0;
    averageCostFunction = 0;
    //for every category
    for (int i = 0; i < trainingWhole.size(); i++) {
        //for every image in the category
        for (int j = 0; j < trainingWhole[i].size(); j++) {
            //calculate the cost of the model upon the current image, add it to the sum
            long double confidence1 = 0;
            if (recognize(trainingWhole[i][j], confidence1) == categories[i]) {
                accuracy++;
            }
            //add the cost function to the averageCostFunction REMOVE
            averageCostFunction = averageCostFunction + costFunction(this, trainingWhole[i][j], i);
        }
    }
    averageCostFunction = averageCostFunction / (trainingWhole.size() * trainingWhole[0].size());
    accuracy = accuracy / (trainingWhole.size() * trainingWhole[0].size());
    trainingWhole.clear();
}

void NeuralModel::createMiniBatches(vector<vector<vector<long double>>>& miniBatches) {
    //clear the previous data
    miniBatches.clear();
    wxInitAllImageHandlers();

    //for each category
    for (int i = 0; i < categories.size(); i++) {
        //create a vector to hold all the images in the category
        vector<vector<long double>> category_training_data;
        //create a vector of all the file names in the category
        vector<wxString> names;
        copyFileNames(fileNames[i], names);
        //select 100 random indexes with no duplicates
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
        //open those 100 random indices and read the image into an activation vector
        for (int j = 0; j < 500; j++) {
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

            //add the activation vector to the list
            category_training_data.push_back(image_activation);
        }
        //add the category vector to the trainingSample vector
        miniBatches.push_back(category_training_data);
    }
}

void NeuralModel::averageGradients(NeuralModel& averageDeltaModel, vector<vector<vector<long double>>>& minibatches) {
    //for every category in the miniBatch
    for (int o = 0; o < minibatches.size(); o++) {
        //for every image in the category
        for (int p = 0; p < minibatches[o].size(); p++) {
            //test the model on one miniBatch
            long double confidence = 0;
            recognize(minibatches[o][p], confidence);
            
            //add the cost function to the averageCostFunction REMOVE
            //averageCostFunction = averageCostFunction + costFunction(this, minibatches[o][p], o);

            //for the neurons in the last layer
            for (int i = 0; i < layers[3].neurons.size(); i++) {
                long double y = 0;
                if (i == o) {
                    y = 1.00;
                }
                double coefficient = 2;
                if (i == o) {
                    coefficient = 20;
                }
                //for the weights on the neuron
                for (int j = 0; j < layers[3].neurons[i].weights.size(); j++) {
                    averageDeltaModel.layers[3].neurons[i].weights[j] += layers[2].neurons[j].activation * (0.5 / (pow((1 + abs(layers[3].neurons[i].weightedSum)), 2))) * coefficient * (layers[3].neurons[i].activation - (double)y);
                }
                //for the bias on the neuron
                averageDeltaModel.layers[3].neurons[i].bias += 1 * (0.5 / (pow((1 + abs(layers[3].neurons[i].weightedSum)), 2))) * coefficient * (layers[3].neurons[i].activation - (double)y);
                //for each of the neurons in the previous layer
                for (int j = 0; j < layers[2].neurons.size(); j++) {
                    //calculate this (last layer) neuron's thoughts on how much the neuron in the previous layer should change
                    //save the values in averageDeltaModel.layers[].neurons[].activation
                    averageDeltaModel.layers[2].neurons[j].activation += layers[3].neurons[i].weights[j] * (0.5 / (pow((1 + abs(layers[3].neurons[i].weightedSum)), 2))) * coefficient * (layers[3].neurons[i].activation - (double)y);
                }
            }
            //for every previous layer except the first
            for (int i = 2; i > 0; i--) {
                //for every neuron on the layer
                for (int j = 0; j < layers[i].neurons.size(); j++) {
                    //for the weights on the neuron
                    for (int k = 0; k < layers[i].neurons[j].weights.size(); k++) {
                        averageDeltaModel.layers[i].neurons[j].weights[k] += layers[i - 1].neurons[k].activation * (0.5 / (pow((1 + abs(layers[i].neurons[j].weightedSum)), 2))) * layers[i].neurons[j].activation;
                    }
                    //for the bias on the neuron
                    averageDeltaModel.layers[i].neurons[j].bias += 1 * (0.5 / (pow((1 + abs(layers[i].neurons[j].weightedSum)), 2))) * layers[i].neurons[j].activation;
                    //for each of the neurons in the previous layer
                    for (int k = 0; k < layers[i - 1].neurons.size(); k++) {
                        averageDeltaModel.layers[i - 1].neurons[k].activation += layers[i].neurons[j].weights[k] * (0.5 / (pow((1 + abs(layers[i].neurons[j].weightedSum)), 2))) * layers[i].neurons[j].activation;
                    }
                }
            }

            //after adding the gradient for this image (must finish every layer) to the sum (averageDeltaModel) reset all of the neuron activations in averageDeltaModel to 0
            //for every layer
            for (int i = 0; i < averageDeltaModel.layers.size(); i++) {
                //for every neuron in the layer
                for (int j = 0; j < averageDeltaModel.layers[i].neurons.size(); j++) {
                    //for the activation on the neuron
                    averageDeltaModel.layers[i].neurons[j].activation = 0;
                }
            }
        }
    }

    //after finishing every image, average out the averageDeltaModel by dividing all the values by the number of batches tested
    //for every layer
    for (int i = 0; i < averageDeltaModel.layers.size(); i++) {
        //for every neuron on the layer
        for (int j = 0; j < averageDeltaModel.layers[i].neurons.size(); j++) {
            //for every weight on the neuron
            for (int k = 0; k < averageDeltaModel.layers[i].neurons[j].weights.size(); k++) {
                averageDeltaModel.layers[i].neurons[j].weights[k] = averageDeltaModel.layers[i].neurons[j].weights[k] / (minibatches.size() * minibatches[0].size());
            }
            //for the bias
            averageDeltaModel.layers[i].neurons[j].bias = averageDeltaModel.layers[i].neurons[j].bias / (minibatches.size() * minibatches[0].size());
        }
    }

    //divide the averageCostFunction by the number of images REMOVE
    //averageCostFunction = averageCostFunction / (minibatches.size() * minibatches[0].size());
}

void NeuralModel::updateModel() {
    //create the miniBatches
    vector<vector<vector<long double>>> miniBatches;	//category image long double
    createMiniBatches(miniBatches);

    //save the current averageCostFunction REMOVE
    //previousAverageCostFunction = averageCostFunction;

    //compute the average gradient with the miniBatches
    NeuralModel averageDeltaModel(*this, true);
    averageGradients(averageDeltaModel, miniBatches);

    /*
    //check if the current averageCostFunction is > previousaverageCostFunction REMOVE
    if (averageCostFunction > previousAverageCostFunction){//averageCostFunction - previousAverageCostFunction > 0.0005) {
        cout << "PROBLEM" << endl;
    }
    */

    long double stepSize = 0.1;
    //multiply the step size by the gradient
    //for every layer
    for (int i = 0; i < averageDeltaModel.layers.size(); i++) {
        //for every neuron in the layer
        for (int j = 0; j < averageDeltaModel.layers[i].neurons.size(); j++) {
            //for every weight on the neuron
            for (int k = 0; k < averageDeltaModel.layers[i].neurons[j].weights.size(); k++) {
                averageDeltaModel.layers[i].neurons[j].weights[k] = averageDeltaModel.layers[i].neurons[j].weights[k] * stepSize;
            }
            //for the bias
            averageDeltaModel.layers[i].neurons[j].bias = averageDeltaModel.layers[i].neurons[j].bias * stepSize;
        }
    }

    /*
    //normalize the averageDeltaModel so the absolute value of the highest value is the step size
    //find the largest value of all the weights and biases in averageDeltaModel
    long double largestValue = 0;
    //for every layer except the first
    for (int i = 0; i < averageDeltaModel.layers.size(); i++) {
        //for every neuron in the layer
        for (int j = 0; j < averageDeltaModel.layers[i].neurons.size(); j++) {
            //for every weight on the neuron
            for (int k = 0; k < averageDeltaModel.layers[i].neurons[j].weights.size(); k++) {
                if (abs(averageDeltaModel.layers[i].neurons[j].weights[k]) > largestValue) {
                    largestValue = abs(averageDeltaModel.layers[i].neurons[j].weights[k]);
                }
            }
            //for the bias
            if (abs(averageDeltaModel.layers[i].neurons[j].bias) > largestValue) {
                largestValue = abs(averageDeltaModel.layers[i].neurons[j].bias);
            }
        }
    }
    //divide every value in averageDeltaModel by the largestValue and multiply by the step size
    //for every layer
    for (int i = 0; i < averageDeltaModel.layers.size(); i++) {
        //for every neuron in the layer
        for (int j = 0; j < averageDeltaModel.layers[i].neurons.size(); j++) {
            //for every weight on the neuron
            for (int k = 0; k < averageDeltaModel.layers[i].neurons[j].weights.size(); k++) {
                averageDeltaModel.layers[i].neurons[j].weights[k] = (averageDeltaModel.layers[i].neurons[j].weights[k] * stepSize) / largestValue;
            }
            //for the bias
            averageDeltaModel.layers[i].neurons[j].bias = (averageDeltaModel.layers[i].neurons[j].bias * stepSize) / largestValue;
        }
    }
    */

    //add the averageDeltaMode to the current model
    //for every layer except the first
    for (int i = 1; i < layers.size(); i++) {
        //for every neuron on the layer
        for (int j = 0; j < layers[i].neurons.size(); j++) {
            //for every weight on the neuron
            for (int k = 0; k < layers[i].neurons[j].weights.size(); k++) {
                //add the averageDeltaModel's value to the current model
                layers[i].neurons[j].weights[k] += averageDeltaModel.layers[i].neurons[j].weights[k];
            }
            //for the bias
            layers[i].neurons[j].bias += averageDeltaModel.layers[i].neurons[j].bias;
        }
    }
}

long double sigmoid1(long double input) {
    return 0.5 * ((input / (1.0 + abs(input))) + 1.0);
}

wxString NeuralModel::recognize(vector<long double>& image, long double& confidence)
{
    //set the activation of the first layer according to the image
    //for each of the neurons in the first layer
    for (int i = 0; i < layers[0].neurons.size(); i++) {
        layers[0].neurons[i].activation = image[i];
    }

    //iterate through the neurons to compute the activation of the output layer
    //for each of the neuron layers except the first
    for (int i = 1; i < layers.size(); i++) {
        //for each of the neurons in the layer
        for (int j = 0; j < layers[i].neurons.size(); j++) {
            long double sum = 0;
            //for each of the weights in that neuron
            for (int k = 0; k < layers[i].neurons[j].weights.size(); k++) {
                sum = sum + (layers[i].neurons[j].weights[k] * layers[i - 1].neurons[k].activation);
            }
            layers[i].neurons[j].weightedSum = sum + layers[i].neurons[j].bias;
            long double CalculatedActivation = sigmoid1(layers[i].neurons[j].weightedSum);
            layers[i].neurons[j].activation = CalculatedActivation;
        }
    }

    //find the most activated neuron in the output layer; return its index 
    int highestIndex = 0;
    long double highestActivation = 0;
    //for every neuron in the last layer
    for (int i = 0; i < categories.size(); i++) {
        if (layers[3].neurons[i].activation > highestActivation) {
            highestIndex = i;
            highestActivation = layers[3].neurons[i].activation;
        }
    }

    confidence = highestActivation;
    return categories[highestIndex];
}
