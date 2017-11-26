#include "NeuralNetwork.h"
const int nodesCount = 2;
const float speed = 0.4f; // must be in [0,1]
int main() {
	shared_ptr<Layer> input = make_shared<Layer>(inputLayer);
	shared_ptr<Layer> hidden = make_shared<Layer>(hiddenLayer);
	shared_ptr<Layer> output = make_shared<Layer>(outputLayer);

	shared_ptr<ActivationFunc> func_name_2 = make_shared<SoftMax>();
	
	input->initNeurons(nodesCount);
	hidden->initNeurons(nodesCount+1);
	output->initNeurons(nodesCount, func_name_2);

	vector<shared_ptr<Layer> > layers = { input, hidden, output };
	LayerBinder digitalRecognition(layers);

	vector<float> inputValues = { 0.05f, 0.1f };
	vector<float> responceValues = { 0.1f, 0.99f };
	digitalRecognition.ForwardPhase(inputValues);
	digitalRecognition.BackwardPhase(responceValues, speed);
	//Create layer and say how many nodes in every layer
	//default function for all nodes and opportunity to change for 
	//every node. Call LayerBinder, it init all links between nodes
	//and after pass X and Y to LayerBinder
	return 0;
}