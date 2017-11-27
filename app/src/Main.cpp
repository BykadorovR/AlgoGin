#include "NeuralNetwork.h"
//const int nodesCount = 3;
const double speed = 0.4; // must be in [0,1]
int main() {
	shared_ptr<Layer> input = make_shared<Layer>(inputLayer);
	shared_ptr<Layer> hidden = make_shared<Layer>(hiddenLayer);
	shared_ptr<Layer> output = make_shared<Layer>(outputLayer);

	shared_ptr<Sigmoida> func_name_1 = make_shared<Sigmoida>();
	shared_ptr<ActivationFunc> func_name_2 = make_shared<SoftMax>();
	
	input->initNeurons(2);
	hidden->initNeurons(15, func_name_1);
	output->initNeurons(4, func_name_2);

	vector<shared_ptr<Layer> > layers = { input, hidden, output };
	LayerBinder digitalRecognition(layers);

	vector<vector<double> > inputValues;
	vector<double> v1 = { 5, 1 };
	vector<double> v2 = { 2, 2 };
	vector<double> v3 = { 9, 9 };
	vector<double> v4 = { 2, 12 };
	inputValues.push_back(v1);
	inputValues.push_back(v2);
	inputValues.push_back(v3);
	inputValues.push_back(v4);
	vector<vector<double> > outputValues;
	vector<double> o1 = { 1, 0, 0, 0 };
	vector<double> o2 = { 0, 1, 0, 0 };
	vector<double> o3 = { 0, 0, 1, 0 };
	vector<double> o4 = { 0, 0, 0, 1 };
	outputValues.push_back(o1);
	outputValues.push_back(o2);
	outputValues.push_back(o3);
	outputValues.push_back(o4);
	float generalError = 1;
	while (generalError > 0.1) {
		generalError = 0;
		for (int i = 0; i < inputValues.size(); i++) {
			digitalRecognition.ForwardPhase(inputValues[i]);
			generalError += digitalRecognition.BackwardPhase(outputValues[i], speed) / 4;
		}
		printf("Error: %f\n", generalError);
	}
		
	//Create layer and say how many nodes in every layer
	//default function for all nodes and opportunity to change for 
	//every node. Call LayerBinder, it init all links between nodes
	//and after pass X and Y to LayerBinder
	return 0;
}