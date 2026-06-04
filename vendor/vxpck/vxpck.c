#include "vxpck.h"

void CopyFile(FILE *src, FILE *dst) {
    char buffer[8192];

    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes_read, dst);
    }
}

static void PackDirectory(FILE *out, const char *base_path, const char *current_path, uint32_t *file_count) {
    DIR *dir = opendir(current_path);
    if (!dir) return;

    struct dirent *entry;
    char filepath[1024];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

        snprintf(filepath, sizeof(filepath), "%s/%s", current_path,entry->d_name);

        struct stat st;
        if (stat(filepath, &st) != 0) continue;

        if (S_ISDIR(st.st_mode)) PackDirectory(out, base_path, filepath, file_count);
        else if (S_ISREG(st.st_mode)) {
            FILE *fp = fopen(filepath, "rb");
            if (!fp) continue;

            fseek(fp, 0, SEEK_END);
            uint32_t size = (uint32_t)ftell(fp);
            fseek(fp, 0, SEEK_SET);

            const char *relative = filepath + strlen(base_path);
            if (*relative == '/' || *relative == '\\') relative++;

            VXPCK_File file = {
                .path_len = (uint32_t)strlen(relative),
                .original_size = size
            };

            fwrite(&file, sizeof(file), 1, out);
            fwrite(relative, 1, file.path_len, out);

            CopyFile(fp, out);
            fclose(fp);
            (*file_count)++;

            printf("Packed: %s (%u bytes)\n", relative, size);
        }
    }

    closedir(dir);
}

void VXPCK_Pack(const char *output, const char *folder_path) {
    FILE *out = fopen(output, "wb");
    if (!out) {
        printf("Failed to create %s\n", output);
        return;
    }

    fwrite("VXPCK", 1, 5, out);

    long count_pos = ftell(out);

    uint32_t file_count = 0;

    fwrite(&file_count, sizeof(file_count), 1, out);
    
    PackDirectory(out, folder_path, folder_path, &file_count);

    fseek(out, count_pos, SEEK_SET);
    fwrite(&file_count, sizeof(file_count), 1, out);

    fclose(out);

    printf("Packed %u files\n", file_count);
}

VXPCK_Status VXPCK_Load(VXPCK** vxpck, const char* filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        *vxpck = NULL;
        return VXPCK_FILE_NOT_FOUND;
    }

    char magic[6] = {0};
    fread(magic, 1, 5, fp);
    magic[5] = '\0';

    if (strcmp(magic, "VXPCK") != 0) {
        fclose(fp);
        *vxpck = NULL;
        return VXPCK_INVALID_FILE;
    }

    *vxpck = calloc(1, sizeof(VXPCK));
    if (!*vxpck) {
        fclose(fp);
        return VXPCK_INVALID_FILE;
    }

    (*vxpck)->fp = fp;

    fread(&(*vxpck)->file_count, sizeof((*vxpck)->file_count), 1, fp);

    (*vxpck)->files = calloc((*vxpck)->file_count, sizeof(VXPCK_Entry));
    if (!(*vxpck)->files) {
        fclose(fp);
        free(*vxpck);
        *vxpck = NULL;
        return VXPCK_INVALID_FILE;
    }

    for (uint32_t i = 0; i < (*vxpck)->file_count; i++) {
        VXPCK_File header;
        fread(&header, sizeof(header), 1, fp);

        (*vxpck)->files[i].path = malloc(header.path_len + 1);
        fread((*vxpck)->files[i].path, 1, header.path_len, fp);
        (*vxpck)->files[i].path[header.path_len] = '\0';

        (*vxpck)->files[i].size = header.original_size;
        (*vxpck)->files[i].offset = ftell(fp);

        fseek(fp, header.original_size, SEEK_CUR);
    }

    return VXPCK_OK;
}
void* VXPCK_ReadFile(VXPCK* vxpck, const char* filename, uint32_t* size) {
    if (!vxpck) return NULL;

    for (uint32_t i = 0; i < vxpck->file_count; i++) {
        VXPCK_Entry* file = &vxpck->files[i];

        if (strcmp(file->path, filename) == 0) {
            void* buffer = malloc(file->size);
            
            fseek(vxpck->fp, file->offset, SEEK_SET);
            fread(buffer, 1, file->size, vxpck->fp);

            if (size) *size = file->size;

            return buffer;
        }
    }

    return NULL;
}

void VXPCK_Unload(VXPCK* vxpck) {
    if (!vxpck) return;

    for (uint32_t i = 0; i < vxpck->file_count; i++) free(vxpck->files[i].path);

    free(vxpck->files);
    fclose(vxpck->fp);
    free(vxpck);
}