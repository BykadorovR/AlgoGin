#pragma once
#include <iostream>
#include <stdio.h>
#include <stdarg.h>

enum l_sts {
	SUCCESS,
	NOT_FOUND,
	EMPTY,
	BOUNDS,
	UNKNOWN,
	WRONG_ARGS
};

l_sts getWorst(l_sts first, l_sts second) {
	return first < second ? first : second;
}