#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILE_CHUNK 8192

void remove_z_from_d_attributes(char *content) {
    char *p = content;

    while ((p = strstr(p, "d=\"")) != NULL) {
        p += 3;
        char *end = strchr(p, '"');
        if (!end) break;

        for (char *q = p; q < end; ++q) {
            if (*q == 'Z' || *q == 'z') {
                *q = ' ';
            }
        }
    }
}

char *read_file(const char *filename, long *filesize) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) return NULL;

    fseek(fp, 0, SEEK_END);
    *filesize = ftell(fp);
    rewind(fp);

    char *buffer = malloc(*filesize + 1);
    if (!buffer) {
        fclose(fp);
        return NULL;
    }

    fread(buffer, 1, *filesize, fp);
    buffer[*filesize] = '\0';
    fclose(fp);
    return buffer;
}

int write_file(const char *filename, const char *data, long size) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) return 0;

    fwrite(data, 1, size, fp);
    fclose(fp);
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s input.svg output.svg\n", argv[0]);
        return 1;
    }

    long size = 0;
    char *content = read_file(argv[1], &size);
    if (!content) {
        perror("Failed to read input file");
        return 1;
    }

    remove_z_from_d_attributes(content);

    if (!write_file(argv[2], content, size)) {
        perror("Failed to write output file");
        free(content);
        return 1;
    }

    printf("Successfully removed Z/z from d attributes and saved to %s\n", argv[2]);
    free(content);
    return 0;
}
