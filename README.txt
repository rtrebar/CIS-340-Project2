Description:  
    The program allows a user to access data on a floppy disk. The operations
    available to the user are: help, fmount, fumount, structure, traverse, 
    showsector, showfat, and quit.

Member Contributions:

Compilation instructions:
    1. type make
    2. type ./main
    3. mount floppy disk with fmount <imagefile>
    4. use commands structure, traverse, 
    showsector, and showfat to access data on the floppy disk.
    5. to get help with the commands, type help on the command line.
    6. to unmount the image file before quitting, type fumount.
    6. to exit the program, type quit in the command line.
    
Sample Run:
$ ./main
flop: help
The available commands are:
    help                    - display a list of available commands.
    fmount <file_name>      - mount the specified image file
    fumount                 - umount the mounted floppy disk.
    structure               - list the structure of the floppy disk image.
    traverse [-l]           - list the contents in the root directory. Optional -l flag gives a long listing of the root directory.
    showsector <sector_num> - show the content of the given sector.
    showfat                 - show the content of the FAT table.
    quit                    - quit the floppy shell
flop: fmount imagefile.img
imagefile.img has been mounted.
flop: structure
Structure of the floppy image:

number of fats:         2
sectors used by fat:    9
sectors per cluster:    1
number of ROOT Entries:         224
number of bytes per sector:     512
---Sector #---     ---Sector Types---
       0                  BOOT
    01 -- 09              FAT1
    10 -- 18              FAT2
    19 -- 32              ROOT DIRECTORY
flop: traverse
/A.CLA
/ALOOP1.CLA
/ALOOP1.JAV
/ALOOP2.CLA
/ALOOP2.JAV
/ALOOP3.CLA
/ALOOP3.JAV
/B.CLA
/CONDIT.CLA
/CONDIT.JAV
/D.CLA
/DEMO.CLA
/DEMO.JAV
/DIR1                                           <DIR>
/DIR1/.                                         <DIR>
/DIR1/..                                        <DIR>
/DIR1/DIR2                                      <DIR>
/DIR1/DIR2/.                                    <DIR>
/DIR1/DIR2/..                                   <DIR>
/DIR1/DIR2/FILE3
/DIR1/C.CLA
/POLYTEST.CLA
/POLYTEST.JAV
/SOME.CLA
flop: traverse -l
 *****************************
 ** FILE ATTRIBUTE NOTATION **
 ** **
 ** R ------ READ ONLY FILE **
 ** S ------ SYSTEM FILE **
 ** H ------ HIDDEN FILE **
 ** A ------ ARCHIVE FILE **
 *****************************

-A---     10/27/2014 13:13:05               670     /A.CLA                                          24
-A---     10/27/2014 13:13:05               763     /ALOOP1.CLA                                     24
-A---     10/27/2014 13:13:05               333     /ALOOP1.JAV                                     24
-A---     10/27/2014 13:13:05               786     /ALOOP2.CLA                                     24
-A---     10/27/2014 13:13:05               404     /ALOOP2.JAV                                     24
-A---     10/27/2014 13:13:05               786     /ALOOP3.CLA                                     24
-A---     10/27/2014 13:13:05               408     /ALOOP3.JAV                                     24
-A---     10/27/2014 13:13:05               358     /B.CLA                                          24
-A---     10/27/2014 13:13:05              1067     /CONDIT.CLA                                     24
-A---     10/27/2014 13:13:05               444     /CONDIT.JAV                                     24
-A---     10/27/2014 13:13:05               508     /D.CLA                                          24
-A---     10/27/2014 13:13:05               967     /DEMO.CLA                                       24
-A---     10/27/2014 13:13:05               648     /DEMO.JAV                                       24
-----     10/27/2014 13:13:05        <DIR>          /DIR1                                           24
-----     10/27/2014 13:13:05        <DIR>          /DIR1/.                                         24
-----     10/27/2014 13:13:05        <DIR>          /DIR1/..                                        24
-----     10/27/2014 13:13:05        <DIR>          /DIR1/DIR2                                      24
-----     10/27/2014 13:13:05        <DIR>          /DIR1/DIR2/.                                    24
-----     10/27/2014 13:13:05        <DIR>          /DIR1/DIR2/..                                   24
-A---     10/27/2014 13:13:05                11     /DIR1/DIR2/FILE3                                24
-A---     10/27/2014 13:13:05               427     /DIR1/C.CLA                                     24
-A---     10/27/2014 13:13:05               630     /POLYTEST.CLA                                   24
-A---     10/27/2014 13:13:05              1063     /POLYTEST.JAV                                   24
-A---     10/27/2014 13:13:05               226     /SOME.CLA                                       24
flop: showsector 10

hex dump of sector : 10
         0       1       2       3       4       5       6       7       8       9       A     B        C       D       E       F
 0       f0      ff      ff      0       40      0       ff      6f      0       ff      ff    ff       9       f0      ff      ff
 10      cf      0       ff      ff      ff      ff      f       1       11      f0      ff    ff       ff      ff      15      f0
 20      ff      17      f0      ff      ff      ff      ff      ff      ff      ff      1d    f0       ff      1f      0       2
 30      ff      ff      ff      0       0       0       0       0       0       0       0     0        0       0       0       0
 40      0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 50      0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 60      0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 70      0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 80      0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 90      0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 a0      0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 b0      0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 c0      0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 d0      0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 e0      0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 f0      0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 100     0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 110     0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 120     0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 130     0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 140     0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 150     0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 160     0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 170     0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 180     0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 190     0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 1a0     0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 1b0     0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 1c0     0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 1d0     0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 1e0     0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
 1f0     0       0       0       0       0       0       0       0       0       0       0     0        0       0       0       0
flop: showfat

         0       1       2       3       4       5       6       7       8       9       a     b        c       d       e       f
                         FREE    4       fff     6       fff     fff     9       fff     fff   c        fff     fff     fff     10
 10      11      fff     fff     fff     15      fff     17      fff     fff     fff     fff   fff      1d      fff     1f      20
 20      fff     fff     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 30      FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 40      FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 50      FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 60      FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 70      FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 80      FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 90      FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 a0      FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 b0      FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 c0      FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 d0      FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 e0      FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 f0      FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 100     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 110     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 120     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 130     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 140     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 150     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 160     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 170     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 180     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 190     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 1a0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 1b0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 1c0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 1d0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 1e0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 1f0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 200     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 210     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 220     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 230     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 240     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 250     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 260     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 270     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 280     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 290     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 2a0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 2b0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 2c0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 2d0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 2e0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 2f0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 300     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 310     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 320     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 330     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 340     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 350     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 360     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 370     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 380     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 390     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 3a0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 3b0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 3c0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 3d0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 3e0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 3f0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 400     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 410     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 420     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 430     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 440     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 450     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 460     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 470     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 480     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 490     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 4a0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 4b0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 4c0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 4d0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 4e0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 4f0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 500     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 510     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 520     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 530     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 540     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 550     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 560     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 570     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 580     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 590     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 5a0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 5b0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 5c0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 5d0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 5e0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 5f0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 600     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 610     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 620     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 630     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 640     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 650     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 660     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 670     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 680     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 690     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 6a0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 6b0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 6c0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 6d0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 6e0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 6f0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 700     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 710     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 720     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 730     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 740     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 750     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 760     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 770     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 780     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 790     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 7a0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 7b0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 7c0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 7d0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 7e0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 7f0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 800     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 810     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 820     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 830     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 840     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 850     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 860     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 870     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 880     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 890     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 8a0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 8b0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 8c0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 8d0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 8e0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 8f0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 900     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 910     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 920     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 930     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 940     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 950     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 960     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 970     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 980     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 990     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 9a0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 9b0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 9c0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 9d0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 9e0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 9f0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 a00     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 a10     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 a20     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 a30     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 a40     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 a50     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 a60     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 a70     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 a80     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 a90     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 aa0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 ab0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 ac0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 ad0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 ae0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 af0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 b00     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 b10     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 b20     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 b30     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 b40     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 b50     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 b60     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 b70     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 b80     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 b90     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 ba0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 bb0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 bc0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 bd0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 be0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
 bf0     FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE    FREE  FREE     FREE    FREE    FREE    FREE
flop: traverse > shorttraversefile
flop: traverse -l > longtraversefile
flop: showsector 10 > showsectorfile
flop: showfat > showfatfile
flop: structure > structurefile
flop: fumount
The floppy was unmounted successfully.
flop: quit

 Exiting the floppy disk shell...


Bugs:
