#include <gtest/gtest.h>
#include "Dictionary.h"

TEST(Dictionary, Insert) {
	algogin::Dictionary<int, int> dictionary;
	dictionary.insert(3, 10);
	dictionary.insert(21, 11);
	dictionary.insert(32, 12);
	dictionary.insert(17, 13);
}