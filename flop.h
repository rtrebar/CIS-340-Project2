#ifndef __FLOP_H__
#define __FLOP_H__

int fd;
unsigned short bytes_per_sector;
unsigned short num_of_sectors;
unsigned short fatbytes;
unsigned short cluster;
char *fat_buffer;

void help(void);
void fmount(const char *);
void fumount();
void structure();
void traverse(char*);
void show_sector();
void show_fat();
void output_redirection(int new_fd, char redir_symbol[1], char* comd[], void (*func)());
void output_redirection2(int new_fd, char redir_symbol[1], char* comd[], void (*func)(char*));
void output_redirection3(int new_fd, char redir_symbol[1], char* comd[], void (*func)(int));
void trim(char*);
void print_files(char*, char*, char*);
void print_directories(unsigned short, char*, unsigned short, unsigned short, unsigned short, char*);

#endif
