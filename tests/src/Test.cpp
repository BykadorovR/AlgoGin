#define GMOCK_DEBUG

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
//	::testing::GTEST_FLAG(filter) = "Pointer.Callstack";
	return RUN_ALL_TESTS();
	std::getchar(); // keep console window open until Return keystroke
}