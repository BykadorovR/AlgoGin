#define GMOCK_DEBUG

#include <gtest/gtest.h>
#include "Container.h"

int main(int argc, char *argv[])
{
	algogin::List<int> list;
	//std::shared_ptr<algogin::List> list = std::make_shared<algogin::List>();
	testing::InitGoogleTest(&argc, argv);
//	::testing::GTEST_FLAG(filter) = "Pointer.Callstack";
	return RUN_ALL_TESTS();
}