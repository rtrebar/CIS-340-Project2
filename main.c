#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include "flop.h"

#define str(x) #x

enum Command { fmount, fumount, structure, traverse, showsector, showfat, quit, help };

int main(void)
{
    char input[100], img[50], cmd[20], flag[2];
    int fd, sector;

    while (1) {
        printf("flop: ");
        fgets(input, 20, stdin); //read line
        sscanf(input, "%s", cmd); //separate out first arg

        if (strcmp(str(help), cmd) == 0) {
            help(); 
        } else if (strcmp(str(fmount), cmd) == 0) {
            sscanf(input, "%s %s", cmd, img);
            fd = fmount(img);
        } else if (strcmp(str(fumount), cmd) == 0) {
            fumount(fd);
        } else if (strcmp(str(structure), cmd) == 0) {
            structure(fd);
        } else if (strcmp(str(traverse), cmd) == 0) {
            sscanf(input, "%s %s", cmd, flag);
            traverse(fd, flag[1]);
            flag[1] = ' '; //clear flag
        } else if (strcmp(strcmp(str(showsector), cmd) == 0) {
            sscanf(input, "%s %d", cmd, &sector);
            show_sector(fd, sector);
        } else if (strcmp(str(showfat), cmd) == 0) {
            show_fat(fd);
        } else if (strcmp(str(quit), cmd) == 0) {
            exit(0);
        } else {
            printf("Error: invalid command\n");
        }
    }

    return 0;
}
