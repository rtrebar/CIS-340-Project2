#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "flop.h"

void help(void)
{
    printf("The available commands are:\n");
    printf("    help                  - display a list of available commands.\n");
    printf("    fmount file_name      - mount the specified image file\n");
    printf("    fumount file_name     - unmount the specified image file\n");
    printf("    structure             - list the structure of the floppy disk image.\n");
    printf("    traverse [-l]         - list the contents in the root directory. Optional -l flag\n");
    printf("                            gives a long listing of the root directory.\n");
    printf("    showsector sector_num - show the content of the given sector.\n");
    printf("    showfat               - show the content of the FAT table.\n");
}

int fmount(char *file)
{
    int fd = open((const char *)file, O_RDONLY);
    if (fd == -1) {
        printf("Error: unable to mount\n");
    } else {
        printf("mount successful\n");
    }
    return fd;
}

void fumount(int fd)
{
    if (close(fd) == -1) {
        printf("Error: unable to unmount\n");
    } else {
        printf("unmounted\n");
    }
}

void structure(int fd)
{
    printf("structure\n");
}

void traverse(int fd, char flag)
{
    if (flag == 'l') { //long traverse
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

void show_sector(int fd, int sector)
{
    printf("show sector %d\n", sector);
}

void show_fat(int fd)
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
