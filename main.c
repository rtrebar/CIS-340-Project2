#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flop.h"

int main(void)
{
    const char *img = "imagefile.img";
    //help();
    fmount(img);
    //structure();
    //traverse('s');
    //traverse('l');
    //show_sector(4);
    //show_fat();
    fumount(img);

    /*
    char cmd[20];

    while (1) {
        printf("flop: ");
        fgets(cmd, 20, stdin);
        //scanf("%s", cmd);

        if (strcmp(cmd, "help") == 0) {
            help(); 
        } else if (strcmp(cmd, "fmount") == 0) {
            fmount("");
        } else if (strcmp(cmd, "fumount") == 0) {
            fumount("");
        } else if (strcmp(cmd, "structure") == 0) {
            structure();
        } else if (strcmp(cmd, "traverse") == 0) {
            traverse('s');
        } else if (strcmp(cmd, "traverse -l") == 0) {
            traverse('l');
        } else if (strcmp(cmd, "showsector") == 0) {
            show_sector(4);
        } else if (strcmp(cmd, "showfat") == 0) {
            show_fat();
        } else if (strcmp(cmd, "quit") == 0) {
            exit(0);
        } else {
            printf("Error: invalid command");
        }
    }
    */
    return 0;
}
