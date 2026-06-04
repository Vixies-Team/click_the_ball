#ifndef UTILS_H
#define UTILS_H

#include "../../vendor/raylib/include/raylib.h"
#include "../../vendor/tinyfiledialogs/tinyfiledialogs.h"

float GetRandomFloat(float min, float max);
void ShowErrorDialog(const char* message);
#endif // UTILS_H