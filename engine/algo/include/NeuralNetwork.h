#pragma once
#include <vector>

using std::vector;

enum layerType {
	inputLayer,
	hiddenLayer,
	outputLayer
};

class ActivationFunc {
public:
	ActivationFunc(float _nodesSum);
	//Calc func, func derivation results
	virtual float funcResult(int mode);
	virtual ~ActivationFunc();
private:
	float nodesSum;
};

class SoftMax : public ActivationFunc {
public:
	SoftMax(float _nodesSum);
	float funcResult(int mode);
	SoftMax();
};


class Layer {
public:
	Layer(layerType _type, int _nodesCount);
	Layer(layerType _type, int _nodesCount, ActivationFunc& _func);
	//initial nodes values + bias (can be interpreted as x0)
	void Init();
	//count of nodes
	int getSize();
	void applyFunc(int nodeId);
	~Layer();
	float operator[](int index);
private:
	ActivationFunc func;
	layerType type;
	int nodesCount;
	vector<float> nodes;
};

class LayerBinder {
public:
	//init binds and weights between layers
	LayerBinder(vector<Layer> _layers);
	~LayerBinder();
	//calculate new values of nodes using functions
	void ForwardPhase();
private:
	vector<Layer> layers;
	vector<vector<float> > weights;
};