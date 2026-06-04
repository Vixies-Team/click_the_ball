#include <stdio.h>

#include "../utils/utils.h"

#include "../../vendor/vxpck/vxpck.h"
#include "../../vendor/raylib/include/raylib.h"
#include "../../vendor/tinyfiledialogs/tinyfiledialogs.h"

void AssetsInit(const char* name_file);

Sound Assets_LoadAudio(const char* name_file); 
Texture Assets_LoadTexture(const char* name_file);
Font Assets_LoadFont(const char* name_file, int fontSize, const int *codepoints, int codepointCount);

void AssetsUnload();