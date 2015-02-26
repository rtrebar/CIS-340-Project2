#include <stdio.h>
#include "flop.h"

void help(void)
{
    printf("The available commands are:\n");
    printf("    help                - display a list of available commands.\n");
    printf("    fmount [file]       - mount the specified image file\n");
    printf("    fumount [file]      - unmount the specified image file\n");
    printf("    structure           - list the structure of the floppy disk image.\n");
    printf("    traverse (-l)       - list the contents in the root directory. Optional -l flag\n");
    printf("                          gives a long listing of the root directory.\n");
    printf("    showsector [sector] - show the content of the given sector.\n");
    printf("    showfat             - show the content of the FAT table.\n");
}

void fmount(char *file)
{
    printf("fmount\n");
}

void fumount(char *file)
{
    printf("fumount\n");
}

void structure(void)
{
    printf("structure\n");
}

void traverse(char flag)
{
    if (flag == 's') {
        printf("traverse short\n");
    } else if (flag == 'l') {
        printf("traverse long\n");
    }
}

void show_sector(int sector)
{
    printf("show sector %d\n", sector);
}

void show_fat(void)
{
    printf("show fat\n");
}
