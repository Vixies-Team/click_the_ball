#include "assets.h"

VXPCK* assets = NULL;

static int IsValidData(void* data, uint32_t size) {
    return (data != NULL && size > 0);
}

void AssetsInit(const char* name_file) {
    switch (VXPCK_Load(&assets, name_file)) {
        case VXPCK_FILE_NOT_FOUND: {
            ShowErrorDialog(
                "Unable to locate required file: data.vxpck\n\n"
                "Please ensure the game installation is complete."
            );
            exit(0);
            break;
        }
        case VXPCK_INVALID_FILE: {
            ShowErrorDialog(
                "The file data.vxpck is corrupted or invalid.\n\n"
                "Try reinstalling the game or restoring the file."
            );
            exit(0);
            break;
        }
        case VXPCK_OK: {
            break;
        }
    }
}

Sound Assets_LoadSound(const char* name_file) {
    uint32_t size;
    void* data = VXPCK_ReadFile(assets, name_file, &size);

    if (!IsValidData(data, size)) {
        ShowErrorDialog("Audio Load Failed\n\nFile missing or corrupted");
        exit(0);
    }

    Wave wave = LoadWaveFromMemory(GetFileExtension(name_file), data, size);

    if (wave.frameCount == 0 || wave.data == NULL) {
        ShowErrorDialog("Audio Decode Failed\n\nInvalid audio format");
        free(data);
        exit(0);
    }

    Sound sound = LoadSoundFromWave(wave);

    UnloadWave(wave);
    free(data);

    return sound;
}

Texture Assets_LoadTexture(const char* name_file) {
    uint32_t size;
    void* data = VXPCK_ReadFile(assets, name_file, &size);

    if (!IsValidData(data, size)) {
        ShowErrorDialog("Texture Load Failed\n\nFile missing or corrupted");
        exit(0);
    }

    Image image = LoadImageFromMemory(GetFileExtension(name_file), data, size);

    if (image.data == NULL || image.width == 0 || image.height == 0) {
        ShowErrorDialog("Texture Decode Failed\n\nInvalid image format");
        free(data);
        exit(0);
    }

    Texture texture = LoadTextureFromImage(image);

    UnloadImage(image);
    free(data);

    return texture;
}

Font Assets_LoadFont(const char* name_file, int fontSize, const int *codepoints, int codepointCount) {
    uint32_t size;
    void* data = VXPCK_ReadFile(assets, name_file, &size);

    if (!IsValidData(data, size)) {
        ShowErrorDialog("Font Load Failed\n\nFile missing or corrupted");
        exit(0);
    }

    Font font = LoadFontFromMemory(GetFileExtension(name_file), data, size, fontSize, codepoints, codepointCount);

    if (font.texture.id == 0) {
        ShowErrorDialog("Font Decode Failed\n\nInvalid font file");
        free(data);
        exit(0);
    }

    free(data);
    
    return font;
}

void* Assets_LoadFile(const char* name_file, uint32_t* file_size) {
    void* data = VXPCK_ReadFile(assets, name_file, file_size);

    if (!IsValidData(data, *file_size)) {
        ShowErrorDialog("File Load Failed\n\nFile missing or corrupted");
        exit(0);
    }

    return data;
}

void AssetsUnload() {
    VXPCK_Unload(assets);
}