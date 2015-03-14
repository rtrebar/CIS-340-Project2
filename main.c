#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flop.h"

int main(void)
{
    char input[100], img[50], cmd[20], flag[2];
    int fd, sector;

    while (1) {
        printf("flop: ");
        fgets(input, 20, stdin); //read line
        sscanf(input, "%s", cmd); //separate out first arg

        if (strcmp(cmd, "help") == 0) {
            help(); 
        } else if (strcmp(cmd, "fmount") == 0) {
            sscanf(input, "%s %s", cmd, img);
            fd = fmount(img);
        } else if (strcmp(cmd, "fumount") == 0) {
            fumount(fd);
        } else if (strcmp(cmd, "structure") == 0) {
            structure(fd);
        } else if (strcmp(cmd, "traverse") == 0) {
            sscanf(input, "%s %s", cmd, flag);
            traverse(fd, flag[1]);
            flag[1] = ' '; //clear flag
        } else if (strcmp(cmd, "showsector") == 0) {
            sscanf(input, "%s %d", cmd, &sector);
            show_sector(sector);
        } else if (strcmp(cmd, "showfat") == 0) {
            show_fat(fd);
        } else if (strcmp(cmd, "quit") == 0) {
            exit(0);
        } else {
            printf("Error: invalid command\n");
        }
    }

    return 0;
}
