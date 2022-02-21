#include <vector>

using namespace std;

#pragma once
class Neuron
{
public:
	float activation;
	float weightedSum;

	vector<float> weights;
	float bias;
};

