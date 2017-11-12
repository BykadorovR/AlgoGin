#include "NeuralNetwork.h"


Neuron::Neuron(float _value) {
	value = _value;
}

Neuron::Neuron(shared_ptr<ActivationFunc> _func, float _value) {
	value = _value;
	func = _func;
}

Neuron::~Neuron() {
	value = 0;
	to.clear();
	out.clear();
}

float Neuron::getValue() {
	return value;
}

Layer::Layer(int _nodesCount, layerType _type) {
	nodesCount = _nodesCount;
	type = _type;
}

void Layer::InitNeurons(shared_ptr<ActivationFunc> _func) {
	vector<shared_ptr<Neuron> >::iterator itNodes;
	for (itNodes = nodes.begin(); itNodes != nodes.end(); itNodes++) {
		(*itNodes) = make_shared<Neuron>(_func);
	}
}

float Layer::operator[](int index) {

}

Layer::~Layer() {
	nodes.clear();
}