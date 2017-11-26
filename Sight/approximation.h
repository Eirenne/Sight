#pragma once
#include <math.h>

bool approximatelyEqual(float a, float b, float epsilon);

bool essentiallyEqual(float a, float b, float epsilon);

bool definitelyGreaterThan(float a, float b, float epsilon);

bool definitelyLessThan(float a, float b, float epsilon);
