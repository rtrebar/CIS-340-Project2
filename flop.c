#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include "flop.h"

void help(void)
{
    printf("The available commands are:\n");
    printf("    help                    - display a list of available commands.\n");
    printf("    fmount <file_name>      - mount the specified image file\n");
    printf("    fumount                 - umount the mounted floppy disk. \n");
    printf("    structure               - list the structure of the floppy disk image.\n");
    printf("    traverse [-l]           - list the contents in the root directory. Optional -l flag gives a long listing of the root directory.\n");
    printf("    showsector <sector_num> - show the content of the given sector.\n");
    printf("    showfat                 - show the content of the FAT table.\n");
    printf("    quit                    - quit the floppy shell \n");
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
    printf("\n    %d -- %d              ROOT DIRECTORY \n",sectors_per_fat*num_of_fats+1, max_root_dir/dir_entries_per_sector + num_of_fats*sectors_per_fat);
}

void trim(char *str)
{
    int i;
    int begin = 0;
    int end = strlen(str) - 1;

    while (isspace(str[begin]))
        begin++;

    while ((end >= begin) && isspace(str[end]))
        end--;

    // Shift all characters back to the start of the string array.
    for (i = begin; i <= end; i++)
        str[i - begin] = str[i];

    str[i - begin] = '\0'; // Null terminate string.
}

void print_files(char *buf, char *directory, char *flag) {
    char filename[256], file[9], extension[4];
    unsigned short date, time;
    unsigned short month, day,  year, hour, minute, second;
    char attributes[] = "----";
    unsigned filesize;

    //dir_cluster = (((unsigned short) buf[26]) & 0xff) | (((unsigned short) buf[27]) & 0x0f)<<8;
    strncpy(file, buf, 8);
    strncpy(extension, buf+8, 3);
    file[8] = '\0';
    extension[3] = '\0';
    trim(file);
    trim(extension);
    strcpy(filename, directory);
    strcat(filename, file);
    if (extension[0] != '\0') {
        strcat(filename, ".");
        strcat(filename, extension);
    }

    if (strcmp("-l", flag) == 0) {
        time = ((unsigned short) buf[22]&0xff) | ((unsigned short) buf[23]&0xff)<<8;
        date = ((unsigned short) buf[24]&0xff) | ((unsigned short) buf[25]&0xff)<<8;
        second = (time & 0x1f) % 60;
        minute = time>>5 & 0x3f;
        hour = time>>11 & 0x1f;
        day = date & 0x1f;
        month = date>>5 & 0xf;
        year = (date>>9 & 0x7f) + 1980;
        if (buf[11]&0x1) attributes[1] = 'R';
        if (buf[11]&0x2) attributes[2] = 'H';
        if (buf[11]&0x4) attributes[3] = 'S';
        if (buf[11]&0x20) attributes[0] = 'A';

        printf("-%-9s", attributes);
        printf("%2.2d/%2.2d/%4d %2.2d:%2.2d:%-10.2d", month, day, year, hour, minute, second);
        if (buf[11]&0x10) {
            printf("%-10s     ", "<DIR>");
        } else {
            filesize = (buf[31]&0xff) << 24 | (buf[30] & 0xff) << 16 | (buf[29]&0xff) << 8 | (buf[28] & 0xff);
            printf("%10d     ", filesize);
        }
        printf("%-40s", filename);
        printf("%10d\n", cluster);
    } else {
        printf("%-40s", filename);
        if (buf[11]&0x10) {
            printf("\t%s", "<DIR>");
        }
        printf("\n");
    }
}

void print_directories(unsigned short cluster, char *directory,
    unsigned short filebytes, unsigned short num_of_sectors,
    unsigned short bytes_per_sector, char *flag) {
    char buf[32], dirname[9], adir[256], ext[4];
    unsigned short new_cluster, low, high;
    unsigned ptr;
    int counter = 0;

    ptr = (filebytes + (cluster - 2)*num_of_sectors)*bytes_per_sector;
    buf[0] = '$';
    strcpy(adir, directory);
    if ((lseek(fd, ptr, 0)) != ptr) {
        printf("Error setting the file pointer to beginning\n");
        exit(1);
    }

    if ((read(fd, buf, sizeof(buf))) != sizeof(buf)) {
        printf("Error reading file entry\n");
        exit(1);
    }

    while (buf[0] != 0x0) {
        if (counter++ >= num_of_sectors*bytes_per_sector/32) {
            if (cluster%2) {
                low = (((unsigned short) fat_buffer[(3*cluster - 1)/2])>>4) & 0x000f;
                high = (((unsigned short) fat_buffer[(3*cluster + 1)/2])<<4) & 0x0ff0;
            } else {
                low = ((unsigned short) fat_buffer[3*cluster/2]) & 0x00ff;
                high = (((unsigned short) fat_buffer[(3*cluster + 2)/2])<<8) & 0x0f00;
            }
            cluster = low | high;
            if (cluster == 0x0 || cluster > 0xff0) {
                break;
            } else {
                counter = 0;
                ptr = (filebytes + (cluster - 2)*num_of_sectors)*bytes_per_sector;
                if ((lseek(fd, ptr, 0)) != ptr) {
                    printf("There was a problem moving the pointer \n");
                    exit(1);
                }
                if ((read(fd, buf, sizeof(buf))) != sizeof(buf)) {
                    printf("Error reading file entry\n");
                    exit(1);
                }
                continue;
            }
        }

        // exclude free space and removed files
        if (isprint((unsigned short) (buf[0] & 0xff))
                && (unsigned short) (buf[0] & 0xff) != 0xe5
                && (unsigned short) (buf[11]&0x08) != 0x08) {
            print_files(buf, directory, flag);
            if (buf[11]&0x10) {
                new_cluster = (((unsigned short) buf[26]) & 0xff) | (((unsigned short) buf[27]) & 0x0f)<<8;
                strncpy(dirname, buf, 8);
                strncpy(ext, buf+8, 3);
                dirname[8] = '\0';
                ext[3] = '\0';
                trim(dirname);
                trim(ext);
                if (strcmp(dirname, ".") && strcmp(dirname, "..")) {
                    strcat(adir, dirname);
                    if (ext[0] != '\0') {
                        strcat(adir, ".");
                        strcat(adir, ext);
                    }
                    strcat(adir, "/");
                    print_directories(new_cluster, adir, filebytes, num_of_sectors, bytes_per_sector, flag);
                    // reset pointer
                    lseek(fd, ptr + counter * 32, 0);
                }
            }
        }
        if ((read(fd, buf, sizeof(buf))) != sizeof(buf)) {
            printf("There was a problem reading the next file/entry\n");
            exit(1);
        }
    }
}

void traverse(char* flag) {
    unsigned short low, high, fat_tables, values, fat_sectors, sectors, rootbytes, filebytes;
    char buf[32], directory[256], file[9], extension[4];
    size_t number_of_bytes;
    number_of_bytes = sizeof(buf);

    if ((lseek(fd, SEEK_SET, SEEK_SET)) != 0) {
        printf("There was a problem setting pointer to beginning of file\n");
        exit(1);
    }

    if ((read(fd, buf, sizeof(buf)) != sizeof(buf))){
        printf("Error reading from floppy disk, try again.\n");
        exit(1);
    }

    low = ((unsigned short) buf[11]) & 0xff;
    high = ((unsigned short) buf[12]) & 0xff;
    bytes_per_sector = low | (high << 8);
    num_of_sectors = ((unsigned short) buf[13]) & 0xff;
    fat_tables = ((unsigned short) buf[16]) & 0xff;
    low = ((unsigned short) buf[17]) & 0xff;
    high = ((unsigned short) buf[18]) & 0xff;
    values = low | (high << 8);
    low = ((unsigned short) buf[22]) & 0xff;
    high = ((unsigned short) buf[23]) & 0xff;
    fat_sectors = low | (high << 8);

    fatbytes = fat_sectors * bytes_per_sector;
    fat_buffer = (char *) malloc(fatbytes);

    if ((lseek(fd, bytes_per_sector, SEEK_SET)) != bytes_per_sector) {
        printf("There was an issue setting the cursor\n");
        exit(1);
    }

    if ((read(fd, fat_buffer, fatbytes)) != fatbytes) {
        printf("There was an error reading the floppy\n");
        exit(1);
    }

    sectors = values * 32 / bytes_per_sector;
    rootbytes = fat_sectors * fat_tables + 1;
    filebytes = rootbytes + sectors;

    strcpy(directory, "/");

    if (strcmp("-l", flag) == 0) {
        printf(" *****************************\n");
        printf(" ** FILE ATTRIBUTE NOTATION **\n");
        printf(" ** **\n");
        printf(" ** R ------ READ ONLY FILE **\n");
        printf(" ** S ------ SYSTEM FILE **\n");
        printf(" ** H ------ HIDDEN FILE **\n");
        printf(" ** A ------ ARCHIVE FILE **\n");
        printf(" *****************************\n\n");
    }

    for (int i = 0;i < values; i++) {
        // go to root entry
        if ((lseek(fd, rootbytes * bytes_per_sector + i * 32, 0))
                != rootbytes * bytes_per_sector + i * 32) {
            printf("There was an error reading entries in floppy \n");
            exit(1);
        }

        if ((read(fd, buf, sizeof(buf))) != sizeof(buf)) {
            printf("There was an error reading directory \n");
            exit(1);
        }

        // skip deleted files or free space
        if (((unsigned short) (buf[0]&0xff) == 0xe5) ||
                ((unsigned short) (buf[0]&0xff) == 0x0) ||
                ((unsigned short) (buf[11]&0x08) == 0x08))  {
            continue;
        }

        print_files(buf, directory, flag);
        if (buf[11] & 0x10) {
            cluster = (((unsigned short) buf[26]) & 0xff) | (((unsigned short) buf[27]) & 0x0f)<<8;
            strncpy(file, buf, 8);
            strncpy(extension, buf+8, 3);
            file[8] = '\0';
            extension[3] = '\0';
            trim(file);
            trim(extension);
            strcat(directory, file);
            if (extension[0] != '\0') {
                strcat(directory, ".");
                strcat(directory, extension);
            }
            strcat(directory, "/");
            print_directories(cluster, directory, filebytes, num_of_sectors, bytes_per_sector, flag);
            // go back to root dir
            strcpy(directory, "/");
        }
    }
    free(fat_buffer);
}

void show_sector(int sec) {

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

void output_redirection(int new_fd, char *redir_symbol, char *comd, void (*func)())
{
    if ((new_fd = open((const char*)comd[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
        printf("error creating redirect file\n");
        exit(1);
    }
    if (fork() == 0) {
        // Child process: stdout redirection
        if (strchr(redir_symbol, '>') != NULL) {
            close(1);
            dup(new_fd);
            close(new_fd);
        }
        // Child process: exec other program
        func();
        exit(0);
    }
    close(new_fd);
}

void output_redirection2(int new_fd, char *redir_symbol, char* comd, void (*func)(char*))
{
    if ((new_fd = open((const char*)comd[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
        printf("error creating redirect file\n");
        exit(1);
    }
    if (fork() == 0) {
        // Child process: stdout redirection 
        if (strchr(redir_symbol, '>') != NULL) {
            close(1);
            dup(new_fd);
            close(new_fd);
        }
        // Child process: exec other program 
        func((char*)comd[1]);
        exit(0);
    }
    close(new_fd);
}

void output_redirection3(int new_fd, char *redir_symbol, char* comd, void (*func)(int))
{
    if ((new_fd = open((const char*)comd[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0) {
        printf("error creating redirect file\n");
        exit(1);
    }
    if (fork() == 0) {
        // Child process: stdout redirection 
        if (strchr(redir_symbol, '>') != NULL) {
            close(1);
            dup(new_fd);
            close(new_fd);
        }
        // Child process: exec other program
        func(atoi((const char*)comd[1]));
        exit(0);
    }
    close(new_fd);
}
