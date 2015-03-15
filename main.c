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
    int new_fd;
    while (1) {
        printf("flop: ");
        char input[50], command[50], arg[50], redir_symbol[1], redir_filename[50];

	fgets(input, 50, stdin); //read line
	sscanf(input, "%s", command); //separate out first arg
	if (strcmp("quit", command) == 0) {
		printf("\n Exiting the floppy disk shell... \n");
		return EXIT_SUCCESS;
	} else if (strcmp("help", command) == 0) {
			help();
        } else if (strcmp("fmount", command) == 0) {
            sscanf(input, "%s %s", command, arg);
            fmount((const char*) arg);
        } else if (strcmp("fumount", command) == 0) {
            fumount(fd);
        } else if (strcmp("structure", command) == 0) {
            structure();
        } else if (strcmp("traverse", command) == 0) {
            sscanf(input, "%s %s", command, arg);
            traverse(arg);
        } else if (strcmp("showsector", command) == 0) {
            sscanf(input, "%s %s", command, arg);
            show_sector(atoi(arg));
        } else if (strcmp("showfat", command) == 0) {
        	if (strchr(input, '>') == NULL) {
			show_fat();
		}
		else {
			sscanf(input, "%s %s %s", command, redir_symbol, redir_filename);
			char* comd[] = {command, NULL, redir_filename};
			if (strchr(redir_symbol, '>') != NULL) {
				if ((new_fd = open(comd[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
					printf("error creating redirect file\n");
					exit(1);
				}
				if (fork() == 0) {
				  /* Child process: stdout redirection */
					if (strchr(redir_symbol, '>') != NULL) {
						close(1);
						dup(new_fd);
						close(new_fd);
					}
				  /* Child process: exec other program */
					show_fat();
					exit(0);
				}
				close(new_fd);
			}
			else
				printf("invalid commmand, please try again.\n");
		}
        } else {
            printf("Error: invalid command\n");
        }
    }

    return 0;
}
