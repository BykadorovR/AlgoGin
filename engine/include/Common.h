#pragma once
#include <iostream>

namespace algogin {
	enum class ALGOGIN_ERROR : uint8_t {
		OK,
		OUT_OF_BOUNDS,
		NOT_FOUND,
		UNKNOWN_ERROR
	};
}