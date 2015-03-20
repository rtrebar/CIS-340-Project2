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
    char list_arg = "-l";
    while (1) {
        printf("flop: ");
        char input[50], command[50], arg[50], redir_symbol[1], redir_filename[50];

        fgets(input, 50, stdin); //read line
        sscanf(input, "%s", command); //separate out first arg, consider using strtok() instead of sscanf()
        if (strcmp("quit", command) == 0) {
            printf("\n Exiting the floppy disk shell... \n");
            return EXIT_SUCCESS;
        } else if (strcmp("help", command) == 0) {
            if (strchr(input, '>') == NULL) {
                help();
            }
            else {
                sscanf(input, "%s %s %s", command, redir_symbol, redir_filename);
                char* comd[] = {command, NULL, redir_filename};
                if (strchr(redir_symbol, '>') != NULL) {
                    void (*func);
                    func = &help;
                    output_redirection(new_fd, redir_symbol, comd, func);
                }
                else {
                    printf("invalid commmand, please try again.\n");
                }
            }
        } else if (strcmp("fmount", command) == 0) {
            sscanf(input, "%s %s", command, arg);
            fmount((const char*) arg);
        } else if (strcmp("fumount", command) == 0) {
            fumount(fd);
        } else if (strcmp("structure", command) == 0) {
            if (strchr(input, '>') == NULL) {
                structure();
            }
            else {
                sscanf(input, "%s %s %s", command, redir_symbol, redir_filename);
                char* comd[] = {command, NULL, redir_filename};
                if (strchr(redir_symbol, '>') != NULL) {
                    void (*func);
                    func = &structure;
                    output_redirection(new_fd, redir_symbol, comd, func);
                }
                else {
                    printf("invalid commmand, please try again.\n");
                }
            }
        } else if (strcmp("traverse", command) == 0) {
            if (strchr(input, '>') == NULL) {
                if (strchr(input, list_arg) == NULL) {
                    traverse(command);
                }
                else if (strchr(input, list_arg) != NULL) {
                    sscanf(input, "%s %s", command, arg);
                    traverse(arg);
                }
                else {
                    printf("Error invalid argument, please try again! \n");
                }
            }
            else {
                if (strchr(input, list_arg) == NULL) {
                    sscanf(input, "%s %s %s", command, redir_symbol, redir_filename);
                    char* comd[] = {command, redir_symbol, redir_filename};
                    if (strchr(redir_symbol, '>') != NULL) {
                        void (*func)(char*);
                        func = &traverse;
                        output_redirection2(new_fd, redir_symbol, comd, func);
                    }
                    else {
                        printf("invalid commmand, please try again.\n");
                    }
                }
                else if (strchr(input, list_arg) != NULL) {
                    sscanf(input, "%s %s %s %s", command, arg, redir_symbol, redir_filename);
                    char* comd[] = {command, arg, redir_filename};
                    if (strchr(redir_symbol, '>') != NULL) {
                        void (*func)(char*);
                        func = &traverse;
                        output_redirection2(new_fd, redir_symbol, comd, func);
                    }
                    else {
                        printf("invalid commmand, please try again.\n");
                    }
                }
                else {
                    printf("Error invalid argument, please try again! \n");
                }
            }
        } else if (strcmp("showsector", command) == 0) {
            if (strchr(input, '>') == NULL) {
                sscanf(input, "%s %s", command, arg);
                show_sector(atoi(arg));
            }
            else {
                sscanf(input, "%s %s %s %s", command, arg, redir_symbol, redir_filename);
                char* comd[] = {command, arg, redir_filename};
                if (strchr(redir_symbol, '>') != NULL) {
                    void (*func)(int);
                    func = &show_sector;
                    output_redirection3(new_fd, redir_symbol, comd, func);
                }
                else {
                    printf("invalid commmand, please try again.\n");
                }
            }
        } else if (strcmp("showfat", command) == 0) {
            if (strchr(input, '>') == NULL) {
                show_fat();
            }
            else {
                sscanf(input, "%s %s %s", command, redir_symbol, redir_filename);
                char* comd[] = {command, NULL, redir_filename};
                if (strchr(redir_symbol, '>') != NULL) {
                    void (*func);
                    func = &show_fat;
                    output_redirection(new_fd, redir_symbol, comd, func);
                }
                else {
                    printf("invalid commmand, please try again.\n");
                }
            }
        } else {
            printf("Error: invalid command\n");
        }
    }

    return 0;
}
