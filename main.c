#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <utils.h>
#include <general_part.h>
#include <print.h>
#include <head.h>

int main(int argc, const char** argv) {
    if (argc != 2) {
        return -1;
    }
    const char* path_to_eml = argv[1];
    data_t data = { NULL, NULL, NULL, NULL};
    int count = 1;
    int file = open(path_to_eml, O_RDONLY);
    struct stat sb;
    if (fstat(file, &sb) == -1) {
        close(file);
        perror("cannot get file size");
        return 0;
    }
    char *memory = (char *)mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, file, 0);
    memset(&data, 0, sizeof(data));
    char *len_sp;
    int cut = 4;
    if (!(len_sp = strstr(memory, "\r\n\r\n"))) {
        len_sp = strstr(memory, "\n\n");
        cut = 2;
    }
    head(memory, &data, len_sp);
    general_part(cut, len_sp, &data, &count);
    print(&data, count);
    munmap(memory, sb.st_size);
    close(file);
    return 0;
}
