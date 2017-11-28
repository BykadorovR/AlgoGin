#include "NeuralNetwork.h"
#include "mnist_reader.h"
#include <cmath>
#include <algorithm>

const double speed = 0.1; // must be in [0,1]
int main(int argc, char* argv[]) {
	string filenameTrainData = "../mnist/train-images-idx3-ubyte";
	int imageSize = 28 * 28;
	//read MNIST iamge into double vector
	vector<vector<double> > trainData;
	read_Mnist(filenameTrainData, trainData);

	string filenameTrainLabel = "../mnist/train-labels-idx1-ubyte";
	//read MNIST label into double vector
	vector<vector<double> > trainLabel;
	read_Mnist_Label(filenameTrainLabel, trainLabel);

	string filenameTestData = "../mnist/t10k-images-idx3-ubyte";
	//read MNIST iamge into double vector
	vector<vector<double> > testData;
	read_Mnist(filenameTestData, testData);

	string filenameTestLabel = "../mnist/t10k-labels-idx1-ubyte";
	//read MNIST label into double vector
	vector<vector<double> > testLabel;
	read_Mnist_Label(filenameTestLabel, testLabel);

	shared_ptr<Layer> input = make_shared<Layer>(inputLayer);
	shared_ptr<Layer> hidden = make_shared<Layer>(hiddenLayer);
	shared_ptr<Layer> output = make_shared<Layer>(outputLayer);

	shared_ptr<Sigmoida> func_name_1 = make_shared<Sigmoida>();
	shared_ptr<ActivationFunc> func_name_2 = make_shared<SoftMax>();
	input->initNeurons(imageSize);
	hidden->initNeurons(atoi(argv[1]), func_name_1);
	output->initNeurons(10, func_name_2);

	vector<shared_ptr<Layer> > layers = { input, hidden, output };
	LayerBinder digitalRecognition(layers);

	//Teaching stage
	int epoch = 0;
	int epochThreshold = atoi(argv[3]);
	float generalError = 1;
	printf("Hidden layers: %d,  Accuracy %f, Epoch threshold\n", atoi(argv[1]), atof(argv[2]), epochThreshold);
	fflush(stdout);
	while (generalError > atof(argv[2]) || epoch < epochThreshold) {
		printf("Error: %f, epoch N %d\n", generalError, epoch);
		fflush(stdout);
		generalError = 0;
		for (int i = 0; i < trainData.size(); i++) {
			digitalRecognition.ForwardPhase(trainData[i]);
			generalError += digitalRecognition.BackwardPhase(trainLabel[i], speed) / (trainData.size());
		}
		epoch++;
	}

	//train results
	int equalTrain = 0;
	int notEqualTrain = 0;
	for (int i = 0; i < trainData.size(); i++) {
		digitalRecognition.ForwardPhase(trainData[i]);
		auto answer = digitalRecognition.getAnswer();
		float result = distance(answer.begin(), max_element(answer.begin(), answer.end()));
		float resultReal = distance(trainLabel[i].begin(), max_element(trainLabel[i].begin(), trainLabel[i].end()));
		if (result == resultReal) {
			equalTrain++;
		}
		else {
			//printf("Predicted index: %f, predicted value %f; Real index: %f\n", result, answer[result], resultReal);
			notEqualTrain++;
		}
	}
	printf("TRAIN: Number equal: %d, number not equal: %d\n", equalTrain, notEqualTrain);
	fflush(stdout);

	int equalTest = 0;
	int notEqualTest = 0;
	for (int i = 0; i < testData.size(); i++) {
		digitalRecognition.ForwardPhase(testData[i]);
		auto answer = digitalRecognition.getAnswer();
		float result = distance(answer.begin(), max_element(answer.begin(), answer.end()));
		float resultReal = distance(testLabel[i].begin(), max_element(testLabel[i].begin(), testLabel[i].end()));
		if (result == resultReal) {
			equalTest++;
		}
		else {
			//printf("Predicted index: %f, predicted value %f; Real index: %f\n", result, answer[result], resultReal);
			notEqualTest++;
		}
	}
	printf("TEST: Number equal: %d, number not equal: %d\n", equalTest, notEqualTest);
	fflush(stdout);
	return 0;
}