#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "flop.h"

void help(void)
{
    printf("The available commands are:\n");
    printf("\t help \t - display a list of available commands.\n");
    printf("\t fmount file_name \t - mount the specified image file\n");
    printf("\t fumount \t - umount the mounted floppy disk. \n");
    printf("\t structure \t - list the structure of the floppy disk image.\n");
    printf("\t traverse [-l] \t - list the contents in the root directory. Optional -l flag gives a long listing of the root directory.\n");
    printf("\t showsector [sector_num] \t - show the content of the given sector.\n");
    printf("\t showfat \t - show the content of the FAT table.\n");
    printf("\t quit \t - quit the floppy shell \n");
}

void fmount(const char* filename)
{
    if ((fd = open(filename, O_RDONLY)) >= 0) {
        printf("%s has been mounted. \n", filename);
    } else {
        printf("The floppy disk was not mounted, check location and filename and try again.");
    }
}

void fumount()
{
    if ((close(fd)) < 0) {
        printf("There was an error un-mounting the floppy disk\n");
    } else {
        printf("The floppy was unmounted successfully.\n");
    }
}

void structure()
{
    unsigned short bytes_per_sector;
    unsigned char sectors_per_cluster;
    unsigned char num_of_fats;
    unsigned short max_root_dir;
    unsigned short total_sectors;
    unsigned short sectors_per_fat;
    int dir_entries_per_sector = 16;
    int count = 0;
    printf("Structure of the floppy image: \n"); 

    lseek(fd,11,SEEK_SET); //skip ignored bytes
    read(fd, &bytes_per_sector, 2);
    read(fd, &sectors_per_cluster, 1);
    lseek(fd,2,SEEK_CUR); //skip reserved sectors
    read(fd, &num_of_fats, 1);
    read(fd, &max_root_dir, 2);
    read(fd, &total_sectors, 2);
    lseek(fd,1,SEEK_CUR); //skip ignored byte
    read(fd, &sectors_per_fat,2);

    printf("\nnumber of fats: \t%d", num_of_fats);
    printf("\nsectors used by fat: \t%d", sectors_per_fat);
    printf("\nsectors per cluster: \t%d", sectors_per_cluster);
    printf("\nnumber of ROOT Entries: \t%d", max_root_dir);
    printf("\nnumber of bytes per sector: \t%d", bytes_per_sector);
    printf("\n---Sector #---     ---Sector Types---");
    printf("\n       %d                  BOOT        ", count);
    for(count = 0;count<num_of_fats;count++){
        printf("\n    %02d -- %02d              FAT%d", (count * sectors_per_fat) + 1,(1 + count)*sectors_per_fat,count + 1);
    }
    printf("\n    %d -- %d              ROOT DIRECTORY",sectors_per_fat*num_of_fats+1, max_root_dir/dir_entries_per_sector + num_of_fats*sectors_per_fat);
}

void traverse(char* flag)
{
    if (strcmp("-l", flag) == 0) { //long traverse
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

void show_sector(int sec){

    int i;
    unsigned char hex[512];
    printf("\nhex dump of sector : %d", sec);

    // set up horizontal entry hex values
    printf("\n");
    printf("\t 0 \t 1 \t 2 \t 3 \t 4 \t 5 \t 6 \t 7 \t 8 \t 9 \t A \t B \t C \t D \t E \t F");

    lseek(fd,sec*512,SEEK_SET);
    for(i=0;i<512;i++) {
        read(fd,&hex[i],1);
        if(i % 16 == 0){
            printf("\n %x ",i);
        }
        printf("\t %x ", hex[i]);
    }
    printf("\n");
}

void show_fat()
{
    unsigned short low, high;
    char buf[32];
    size_t nbytes;
    ssize_t bytes_read;
    nbytes = sizeof(buf);
    off_t offset;

    offset = lseek(fd, SEEK_SET, SEEK_SET);
    if (offset == -1) {
        printf("There was an issue reading beginning of floppy.");
        exit(1);
    }

    bytes_read = read(fd, buf, nbytes);
    if (bytes_read != nbytes) {
        printf("There was an issue reading the floppy.");
        exit(1);
    }

    low = ((unsigned short) buf[11]) & 0xff;
    high = ((unsigned short) buf[12]) & 0xff;
    bytes_per_sector = low | (high << 8);

    low = ((unsigned short) buf[22]) & 0xff;
    high = ((unsigned short) buf[23]) & 0xff;
    num_of_sectors = low | (high << 8);

    fatbytes = bytes_per_sector * num_of_sectors;

    fat_buffer = (char *) malloc(fatbytes);
    offset = lseek(fd, bytes_per_sector, 0);
    if (offset != bytes_per_sector) {
        printf("There was an issue setting the cursor");
        exit(1);
    }

    if ((bytes_read = read(fd, fat_buffer, fatbytes)) != fatbytes) {
        printf("There was an issue reading the sector");
        exit(1);
    }

    // set up horizontal entry hex values
    printf("\n");
    for (int i=0;i<16;i++) {
        printf("\t %x", i);
    }

    printf("\n \t \t"); // first two entries are reserved
    for (int x = 2; x < fatbytes*2/3; x++) {
        unsigned short low, high;
        unsigned short temp = (unsigned short) x;
        // print the vertical hex entry values
        if ((x%16) == 0) {
            printf("\n %x", x);
        }

        if (temp%2) {
            low = (((unsigned short) fat_buffer[(3*temp - 1)/2])>>4) & 0x000f;
            high = (((unsigned short) fat_buffer[(3*temp + 1)/2])<<4) & 0x0ff0;
        } else {
            low = ((unsigned short) fat_buffer[3*temp/2]) & 0x00ff;
            high = (((unsigned short) fat_buffer[(3*temp + 2)/2])<<8) & 0x0f00;
        }
        cluster = low | high;

        if (cluster) {
            printf("\t %x", cluster);
        } else {
            printf("\t FREE");
        }
    }

    printf("\n");
    free(fat_buffer);
}

void output_redirection(int new_fd, char redir_symbol[1], char* comd[], void (*func)()) 
{
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
        func();
        exit(0);
    }
    close(new_fd);
}

void output_redirection2(int new_fd, char redir_symbol[1], char* comd[], void (*func)(char*)) 
{
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
        func(comd[1]);
        exit(0);
    }
    close(new_fd);
}

void output_redirection3(int new_fd, char redir_symbol[1], char* comd[], void (*func)(int)) 
{
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
        func(atoi(comd[1]));
        exit(0);
    }
    close(new_fd);
}
