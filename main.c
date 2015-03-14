#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include "flop.h"

int main(void)
{
    
    while (1) {
        printf("flop: ");
        char cmd[50];
	char argument[50];

	scanf("%s", cmd);
	if (strcmp("quit", cmd) == 0) {
		printf("\n Exiting the floppy disk shell...");
		return EXIT_SUCCESS;
	} else if (strcmp("help", cmd) == 0) {
			help();
        } else if (strcmp("fmount", cmd) == 0) {
            scanf("%s", argument);
            fmount(argument);
        } else if (strcmp("fumount", cmd) == 0) {
            fumount(fd);
        } else if (strcmp("structure", cmd) == 0) {
            structure();
        } else if (strcmp("traverse", cmd) == 0) {
            scanf("%s", argument);
            traverse(argument);
        } else if (strcmp("showsector", cmd) == 0) {
            scanf("%s", argument);
            show_sector(atoi(argument));
        } else if (strcmp("showfat", cmd) == 0) {
            show_fat();
        } else {
            printf("Error: invalid command\n");
        }
    }

    return 0;
}
