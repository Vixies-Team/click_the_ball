#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
#include "../vendor/dirent.h"
#else
#include <dirent.h>
#endif

typedef enum {
    VXPCK_OK,
    VXPCK_FILE_NOT_FOUND,
    VXPCK_INVALID_FILE
} VXPCK_Status;

typedef struct {
    uint32_t path_len;
    uint32_t original_size;
} VXPCK_File;

typedef struct {
    char* path;
    uint32_t size;
    uint64_t offset;
} VXPCK_Entry;

typedef struct {
    FILE* fp;
    uint32_t file_count;
    VXPCK_Entry* files;
} VXPCK;

void VXPCK_Pack(const char *output, const char *folder_path);

VXPCK_Status VXPCK_Load(VXPCK** vxpck, const char* filename);
void* VXPCK_ReadFile(VXPCK* vxpck, const char* filename, uint32_t* size);
void VXPCK_Unload(VXPCK* vxpck);