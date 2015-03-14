#ifndef __FLOP_H__
#define __FLOP_H__

unsigned short bytes_per_sector;
unsigned short num_of_sectors;
unsigned short fatbytes;
unsigned short cluster;
char *fat_buffer;

void help(void);
int fmount(char *);
void fumount(int);
void structure(int);
void traverse(int, char);
void show_sector(int, int);
void show_fat(int);

#endif
