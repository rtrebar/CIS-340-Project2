#include <stdio.h>
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
	}
	else {
		printf("The floppy disk was not mounted, check location and filename and try again.");
	}
}

void fumount()
{
	if ((close(fd)) < 0) {
		printf("There was an error un-mounting the floppy disk\n");
	}
	else {
		printf("The floppy was unmounted successfully.\n");
	}
}

void structure(int fd)
{
    printf("structure\n");
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
	printf("\n   0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");
	lseek(fd,sec*512,SEEK_SET);
	for(i=0;i<512;i++){
		read(fd,&hex[i],1);
		if(i % 16 == 0){
			printf("\n %x ",i);
		}
		printf("%02x ", hex[i]);
	}
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
		}else {
				low = ((unsigned short) fat_buffer[3*temp/2]) & 0x00ff;
				high = (((unsigned short) fat_buffer[(3*temp + 2)/2])<<8) & 0x0f00;
		}
		cluster = low | high;

		if (cluster)
			printf("\t %x", cluster);
		else
			printf("\t FREE");
	}

	printf("\n");
	free(fat_buffer);
}
