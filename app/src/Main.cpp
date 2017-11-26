#include "NeuralNetwork.h"
const int nodesCount = 3;
const double speed = 0.4; // must be in [0,1]
int main() {
	shared_ptr<Layer> input = make_shared<Layer>(inputLayer);
	shared_ptr<Layer> hidden = make_shared<Layer>(hiddenLayer);
	shared_ptr<Layer> output = make_shared<Layer>(outputLayer);

	shared_ptr<Sigmoida> func_name_1 = make_shared<Sigmoida>();
	shared_ptr<ActivationFunc> func_name_2 = make_shared<SoftMax>();
	
	input->initNeurons(nodesCount);
	hidden->initNeurons(nodesCount, func_name_1);
	output->initNeurons(nodesCount, func_name_2);

	vector<shared_ptr<Layer> > layers = { input, hidden, output };
	LayerBinder digitalRecognition(layers);

	vector<double> inputValues = { 0.1, 0.7, 0.4 };
	vector<double> responceValues = { 0.2, 0.1, 0.7};
	double error = 1;
	double expectedError = 0.8;
	while (abs(error) > expectedError) {
		digitalRecognition.ForwardPhase(inputValues);
		error = digitalRecognition.BackwardPhase(responceValues, speed, expectedError);
	}
	//Create layer and say how many nodes in every layer
	//default function for all nodes and opportunity to change for 
	//every node. Call LayerBinder, it init all links between nodes
	//and after pass X and Y to LayerBinder
	return 0;
}