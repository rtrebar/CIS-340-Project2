#include <stdio.h>
#include <stddef.h>
#include <sys/mount.h>
#include "flop.h"

void help(void)
{
    printf("The available commands are:\n");
    printf("    help                - display a list of available commands.\n");
    printf("    fmount [file]       - mount the specified image file\n");
    printf("    fumount [file]      - unmount the specified image file\n");
    printf("    structure           - list the structure of the floppy disk image.\n");
    printf("    traverse [-l]       - list the contents in the root directory. Optional -l flag\n");
    printf("                          gives a long listing of the root directory.\n");
    printf("    showsector [sector] - show the content of the given sector.\n");
    printf("    showfat             - show the content of the FAT table.\n");
}

void fmount(const char *file)
{
    const char *target = "/media/floppy/";
    const char *filesystem = "msdos";
    unsigned long flags = MS_RDONLY;
    const void *data = NULL; 
    if (mount(file, target, filesystem, flags, data) == -1) {
        printf("Error: unable to mount %s\n", file);
    } else {
        printf("%s mounted at %s\n", file, target);
    }
}

void fumount(const char *file)
{
    const char *target = "/media/floppy/";
    if (umount(target) == -1) {
        printf("Error: unable to unmount %s\n", file);
    } else {
        printf("unmounted %s\n", file);
    }
}

void structure(void)
{
    printf("structure\n");
}

void traverse(char flag)
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

void show_sector(int sector)
{
    printf("show sector %d\n", sector);
}

void show_fat(void)
{
    printf("show fat\n");
}
