#include "NeuralNetwork.h"
#include <cassert>
#include <algorithm>

Relu::Relu() {
	nodesSum = 0;
}

float Relu::funcResult(float value, funcCalcMode mode) {
	float output = 0;
	switch (mode) {
	case funcValue:
		output = value;
		break;
	case derivValue:
		break;
	}
	return output;
}

float SoftMax::funcResult(float value, funcCalcMode mode) {
	float output = 0;
	switch (mode) {
	case funcValue:
		output = value;
		break;
	case derivValue:
		break;
	}
	return output;
}

SoftMax::SoftMax() {
	nodesSum = 0;
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
	for (auto current = nodes.begin(); current != nodes.end(); ++current) {
		auto currentFunc = (*current)->getFunc();
		(*current)->setValue(currentFunc->funcResult((*current)->getValue(), funcValue));
	}
}

void Layer::propagateValuesFrom(shared_ptr<Layer> previousLayer) {
	for (auto current = nodes.begin(); current != nodes.end(); ++current) {
		for (auto previous = (*current)->in.begin(); previous != (*current)->in.end(); ++previous) {
			shared_ptr<Neuron> previousNeuron = (*previous).first;
			float weightBetween = (*previous).second;
			(*current)->setValue((*current)->getValue() + previousNeuron->getValue() * weightBetween);
		}
		(*current)->setValue((*current)->getValue() + bias);
	}
}

layerType Layer::getType() {
	return type;
}

void Layer::setNeuronValues(vector<float> _values) {
	assert(_values.size() != nodes.size());
	for (int nodeIndex = 0; nodeIndex <  nodes.size(); ++nodeIndex) {
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
			(*node1)->out.push_back(pair<shared_ptr<Neuron>, float>(*node2, generator.generate()));
			(*node2)->in.push_back(pair<shared_ptr<Neuron>, float>(*node1, generator.generate()));
		}
	}
	//bias has to be initialized for all layers instead of output
	_layer1->setBias(generator.generate());
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
						printf("%.2f ", (*node).second);
					else
						printf("%c ", "-");
				}
			}
			if ((*layer)->nodes.size() > i) {
				printf("| %.2f | ", (*layer)->nodes[i]->getValue());
			}
			else {
				printf("| %c | ", "-");
			}
		}
		printf("\n");
	}
}

void LayerBinder::ForwardPhase(vector<float> x, vector<float> y) {
	assert(layers.size() > 0);
	layers[0]->setNeuronValues(x);
	for (size_t i = 1; i < layers.size(); i++) {
		layers[i]->propagateValuesFrom(layers[i-1]);
		layers[i]->applyFunc();
	}
}

void LayerBinder::BackwardPhase() {

}