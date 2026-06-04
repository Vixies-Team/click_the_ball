#include "utils.h"

float GetRandomFloat(float min, float max) {
    return min + ((float)GetRandomValue(0, 1000000) / 1000000.0f) * (max - min);
}

void ShowErrorDialog(const char* message) {
    tinyfd_messageBox("Error", message, "ok", "error", 1);
}