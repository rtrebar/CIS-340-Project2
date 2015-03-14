#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include "flop.h"


#define str(x) #x

enum Command { fmount, fumount, structure, traverse, showsector, showfat, quit, help };

int main(void)
{
    
    while (1) {
        printf("flop: ");
        char cmd[50];
	char argument[50];
		
	scanf("%s", cmd);
	if (strcmp(str(quit), cmd) == 0) {
		printf("Exiting the floppy disk shell...");
		return EXIT_SUCCESS;
	} else if (strcmp(str(help), cmd) == 0) {
            help(); 
        } else if (strcmp(str(fmount), cmd) == 0) {
            scanf("%s", argument);
            fmount(argument);
        } else if (strcmp(str(fumount), cmd) == 0) {
            fumount(fd);
        } else if (strcmp(str(structure), cmd) == 0) {
            structure();
        } else if (strcmp(str(traverse), cmd) == 0) {
            scanf("%s", argument);
            traverse(argument);
        } else if (strcmp(str(showsector), cmd) == 0) {
            scanf("%s", argument);
            show_sector(atoi(argument));
        } else if (strcmp(str(showfat), cmd) == 0) {
            show_fat();
        } else {
            printf("Error: invalid command\n");
        }
    }

    return 0;
}
