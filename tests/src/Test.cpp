#define GMOCK_DEBUG

#include <gtest/gtest.h>

#include "NeuralNetwork.h"

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
//	::testing::GTEST_FLAG(filter) = "Pointer.Callstack";
	return RUN_ALL_TESTS();
	std::getchar(); // keep console window open until Return keystroke
}

TEST(Sigmoida, Value_Deriv) {
	Sigmoida sigm;
	vector<double> values(10);
	for (int i = 0; i < values.size(); i++)
		values[i] = i;

	double result = sigm.funcResult(values, 1);
	EXPECT_NEAR(result, 0.88079, 0.00001);

	result = sigm.derivResult(12);
	EXPECT_NEAR(result, -264, 0.00001);
}

TEST(SoftMax, Value) {
	SoftMax soft;
	vector<double> values(10);
	for (int i = 0; i < values.size(); i++)
		values[i] = i;

	double result = soft.funcResult(values, 5);
	EXPECT_NEAR(result, 0.01157, 0.00001);
}

TEST(CrossEntropy, Value_Deriv) {
	CrossEntropy cross;
	vector<double> values(10);
	vector<double> expected(10);
	for (int i = 0; i < values.size(); i++) {
		values[i] = 10 * static_cast<double>(i+1);
		expected[i] = static_cast<double>(i+1);
	}

	double result = cross.funcResult(values, expected);
	EXPECT_NEAR(result, -228.72501, 0.00001);

	result = cross.funcDerivResult(values[2], expected[2]);
	EXPECT_NEAR(result, 27, 0.00001);
}

class General : public ::testing::Test {
protected:
	void SetUp()
	{
		int nodesCount = 3;
		shared_ptr<Layer> input = make_shared<Layer>(inputLayer);
		shared_ptr<Layer> hidden = make_shared<Layer>(hiddenLayer);
		shared_ptr<Layer> output = make_shared<Layer>(outputLayer);

		shared_ptr<Sigmoida> func_name_1 = make_shared<Sigmoida>();
		shared_ptr<ActivationFunc> func_name_2 = make_shared<SoftMax>();
		input->initNeurons(nodesCount);
		hidden->initNeurons(nodesCount - 1, func_name_1);
		output->initNeurons(nodesCount, func_name_2);
		vector<shared_ptr<Layer> > layers = { input, hidden, output };
		digitalRecognition = make_shared<LayerBinder>(layers);
		x = { 1, 2, 3 };
		y = { 0.1, 0.8, 0.1 };
	}
	shared_ptr<LayerBinder> digitalRecognition;
	vector<double> x;
	vector<double> y;
};

TEST_F(General , Forward) {
	digitalRecognition->ForwardPhase(x);
	auto lastLayer = digitalRecognition->getAnswer();
	EXPECT_NEAR(lastLayer[0], 0.333684, 0.000001);
	EXPECT_NEAR(lastLayer[1], 0.333766, 0.000001);
	EXPECT_NEAR(lastLayer[2], 0.332548, 0.000001);
	digitalRecognition->printNetwork();
}

TEST_F(General, Backward) {
	for (int i = 0; i < 10; i++) {
		digitalRecognition->BackwardPhase(y, 0.1);
		digitalRecognition->ForwardPhase(x);
	}
	auto lastLayer = digitalRecognition->getAnswer();
	EXPECT_NEAR(lastLayer[0], 0.157266, 0.000001);
	EXPECT_NEAR(lastLayer[1], 0.686031, 0.000001);
	EXPECT_NEAR(lastLayer[2], 0.156701, 0.000001);
	digitalRecognition->printNetwork();
}
