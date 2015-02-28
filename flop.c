#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "flop.h"

void help(void)
{
    printf("The available commands are:\n");
    printf("    help                  - display a list of available commands.\n");
    printf("    fmount file_name      - mount the specified image file\n");
    printf("    fumount file_name     - unmount the specified image file\n");
    printf("    structure             - list the structure of the floppy disk image.\n");
    printf("    traverse [-l]         - list the contents in the root directory. Optional -l flag\n");
    printf("                            gives a long listing of the root directory.\n");
    printf("    showsector sector_num - show the content of the given sector.\n");
    printf("    showfat               - show the content of the FAT table.\n");
}

int fmount(char *file)
{
    int fd = open((const char *)file, O_RDONLY);
    if (fd == -1) {
        printf("Error: unable to mount\n");
    } else {
        printf("mount successful\n");
    }
    return fd;
}

void fumount(int fd)
{
    if (close(fd) == -1) {
        printf("Error: unable to unmount\n");
    } else {
        printf("unmounted\n");
    }
}

void structure(int fd)
{
    printf("structure\n");
}

void traverse(int fd, char flag)
{
    if (flag == 'l') { //long traverse
        printf("        *****************************\n");
        printf("        ** FILE ATTRIBUTE NOTATION **\n");
        printf("        **                         **\n");
        printf("        ** R ------ READ ONLY FILE **\n");
        printf("        ** S ------ SYSTEM FILE    **\n");
        printf("        ** H ------ HIDDEN FILE    **\n");
        printf("        ** A ------ ARCHIVE FILE   **\n");
        printf("        *****************************\n\n");
    } else { //short traverse
    }
}

void show_sector(int fd, int sector)
{
    printf("show sector %d\n", sector);
}

void show_fat(int fd)
{
    printf("show fat\n");
}
