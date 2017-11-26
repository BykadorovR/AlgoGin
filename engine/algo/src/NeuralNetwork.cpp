#include "NeuralNetwork.h"
#include <cassert>
#include <algorithm>


float Relu::funcResult(vector<float> values, int current) {
	return current;
}

float SoftMax::funcResult(vector<float> values, int current) {
	vector<float> expValues = values;
	for (int i = 0; i < expValues.size(); i++) {
		expValues[i] = exp(expValues[i]);
	}
	float expSum = 0;
	for (auto& expValue : expValues)
		expSum += expValue;

	return expValues[current] / expSum;
}

float CrossEntropy::funcDerivResult(float current, float expected) {
	return current - expected;
}

float CrossEntropy::funcResult(vector<float> current, vector<float> expected) {
	float result = 0;
	for (int i = 0; i < current.size(); i++) {
		result += expected[i] * log(current[i]);
	}
	return -result;
}

Neuron::Neuron(shared_ptr<ActivationFunc> _func) {
	value = 0;
	func = _func;
}

Neuron::~Neuron() {
	value = 0;
	in.clear();
	out.clear();
}

void Neuron::setValue(float _value) {
	value = _value;
}

float Neuron::getValue() {
	return value;
}

shared_ptr<ActivationFunc> Neuron::getFunc() {
	return func;
}

float Neuron::getAdj() {
	return adjustment;
}

void Neuron::setAdj(float _adjustment) {
	adjustment = _adjustment;
}

Layer::Layer(layerType _type) {
	type = _type;
	bias = 0;
}

//for hidden and output layers
void Layer::initNeurons(int _nodesCount, shared_ptr<ActivationFunc> _func) {
	for (int i = 0; i <  _nodesCount; i++) {
		nodes.push_back(make_shared<Neuron>(_func));
	}

}

//apply func for all neurons
void Layer::applyFunc() {
	vector<float> values;
	//some functions need to do normalization
	for (auto& current : nodes) {
		values.push_back(current->getValue());
	}
	for (int i = 0; i < nodes.size(); i++) {
		auto activationFunc = nodes[i]->getFunc();
		if (activationFunc == nullptr)
			continue;
		nodes[i]->setValue(activationFunc->funcResult(values, i));
	}
}

void Layer::propagateValuesFrom(shared_ptr<Layer> previousLayer) {
	for (auto current = nodes.begin(); current != nodes.end(); ++current) {
		for (auto previous = (*current)->in.begin(); previous != (*current)->in.end(); ++previous) {
			shared_ptr<Neuron> previousNeuron = (*previous).first;
			(*current)->setValue((*current)->getValue() + previousNeuron->getValue() * (*previous).second->weight);
		}
		(*current)->setValue((*current)->getValue() + previousLayer->bias);
	}
}

layerType Layer::getType() {
	return type;
}

void Layer::setNeuronValues(vector<float> _values) {
	assert(_values.size() == nodes.size());
	for (int nodeIndex = 0; nodeIndex <  nodes.size(); ++nodeIndex) {
		nodes[nodeIndex]->setValue(_values[nodeIndex]);
		if (type == inputLayer)
			nodes[nodeIndex]->setValue(_values[nodeIndex]);
	}
}

Layer::~Layer() {
	nodes.clear();
}

float Layer::getBias() {
	return bias;
}

void Layer::setBias(float _bias) {
	bias = _bias;
}

//init weights with random
void initWeights(shared_ptr<Layer> _layer1, shared_ptr<Layer> _layer2) {
	RandomWeights<float>& generator = RandomWeights<float>::getInstance();
	for (auto node1 = _layer1->nodes.begin(); node1 != _layer1->nodes.end(); ++node1) {
		for (auto node2 = _layer2->nodes.begin(); node2 != _layer2->nodes.end(); ++node2) {
			shared_ptr<Weight> randomWeight = make_shared<Weight>(generator.get());
			(*node1)->out.push_back(pair<shared_ptr<Neuron>, shared_ptr<Weight> >(*node2, randomWeight));
			(*node2)->in.push_back(pair<shared_ptr<Neuron>, shared_ptr<Weight> >(*node1, randomWeight));
		}
	}
	//bias has to be initialized for all layers instead of output
	_layer1->setBias(generator.get());
}

LayerBinder::LayerBinder(vector<shared_ptr<Layer> > _layers) {
	layers = _layers;
	//init to and out neurons for every neuron
	for (auto layer = _layers.begin() + 1; layer != _layers.end(); ++layer) {
		initWeights(*(layer -1), *layer);
	}
}

void LayerBinder::printNetwork() {
	//get maximum count of nodes between all layers
	int maxNodes = 0;
	for (auto current = layers.begin(); current != layers.end(); ++current) {
		maxNodes = (*current)->nodes.size() > maxNodes ? (*current)->nodes.size() : maxNodes;
	}
	//iterate through all nodes layer by layer
	for (int i = 0; i < maxNodes; i++) {
		for (auto layer = layers.begin(); layer != layers.end(); ++layer) {
			if ((*layer)->getType() != inputLayer) {
				int j = (*layer)->nodes.size() > i ? i : (*layer)->nodes.size() - 1;
				//take all nodes from previous layer which enter to this node
				for (auto node = (*layer)->nodes[j]->in.begin(); node != (*layer)->nodes[j]->in.end(); ++node) {
					//print weghts bettween all nodes from previous layer and node from this layer
					if ((*layer)->nodes.size() > i)
						printf("%6.3f ", (*node).second->weight);
					else
						printf("%6.3s ", "-");
				}
			}
			if ((*layer)->nodes.size() > i) {
				printf("| %6.3f | ", (*layer)->nodes[i]->getValue());
			}
			else {
				printf("| %6.3s | ", "-");
			}
		}
		printf("\n");
	}
	//print bias for all layers exclude last
	for (auto layer = layers.begin(); layer != layers.end(); ++layer) {
		printf("b %6.3f | ", (*layer)->getBias());
		if ((*layer)->getType() != outputLayer) {
			for (int i = 0; i < (*layer)->nodes.size(); i++) {
				printf("%6.3s ", "-");
			}
		}
	}
	printf("\n");
	printf("\n");
}

void LayerBinder::ForwardPhase(vector<float> x) {
	assert(layers.size() > 0);
	printf("Start\n");
	printNetwork();
	layers[0]->setNeuronValues(x);
	printf("Initial values are applied\n");
	printNetwork();
	for (size_t i = 1; i < layers.size(); i++) {
		layers[i]->propagateValuesFrom(layers[i-1]);
		printf("Values for layer %d were propagated from layer %d\n", i, i-1);
		printNetwork();
		layers[i]->applyFunc();
		printf("Activation func was appliad to layer %d\n", i);
		printNetwork();
	}
}

float LayerBinder::BackwardPhase(vector<float> y, float speed, float error) {
	shared_ptr<Layer> lastLayer = layers[layers.size() - 1];
	vector<float> nodesValue;
	vector<float> errorFuncDerivative;
	CrossEntropy crossFunction;

	//lets fill nodeValue array
	for (int i = 0; i < lastLayer->nodes.size(); i++) {
		nodesValue.push_back(lastLayer->nodes[i]->getValue());
	}

	float result = crossFunction.funcResult(nodesValue, y);
	if (result > 0 && result < error)
		return result;

	//iterate through output nodes
	for (int j = 0; j < lastLayer->nodes.size(); j++) { // j = arg
		float adjustment = crossFunction.funcDerivResult(lastLayer->nodes[j]->getValue(),y[j]);
		lastLayer->nodes[j]->setAdj(adjustment);
	}

	//lets calculate error for all hidden layers (not input, not output)
	for (int i = layers.size() - 2; i > 0; i--) { // i = layer
		for (int j = 0; j < layers[i]->nodes.size(); j++) { //j = current node in hidden layer
			float adjustment = 0;
			for (int k = 0; k < layers[i]->nodes[j]->out.size(); k++) { // k = all nodes in next layer related to this one
				//we don't calculate func due to linear dependencies
				adjustment += layers[i]->nodes[j]->out[k].first->getAdj()*layers[i]->nodes[j]->out[k].second->weight;
			}
			layers[i]->nodes[j]->setAdj(adjustment);
		}
	}

	//fix edges using calculated adjustments and biases!!!
	for (int i = layers.size() - 2; i >= 0; i--) { // i = layer
		for (int j = 0; j < layers[i]->nodes.size(); j++) { // j = current node in layer
			for (int k = 0; k < layers[i]->nodes[j]->out.size(); k++) { // k = node in next layer
				layers[i]->nodes[j]->out[k].second->weight += -speed * layers[i]->nodes[j]->out[k].first->getAdj()*layers[i]->nodes[j]->getValue();
			}
		}
		//bias
		for (int k = 0; k < layers[i + 1]->nodes.size(); k++) {
			layers[i]->setBias(layers[i]->getBias() - (speed * layers[i + 1]->nodes[k]->getAdj() * 1));
		}
	}
	printNetwork();
	return result;
}