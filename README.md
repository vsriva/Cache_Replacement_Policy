# Cache_Replacement_Policy
LRU, ARC
Date Created:10 Nov 2015
Date Finished:01 Dec 2015

README

Don't use runscript.sh. It will not run correctly for some reason.

Following steps have been checked at general.asu.edu so there shouldn't be an issue in compilation. If there are warnings ignore them.
There are two folders provided with LRU and ARC codes and respective header files.
First change directory to LRU

Steps to compile the LRU file
1. Type in the command: gcc -O3 project3_LRU.c -o project3_LRU.o. This will compile the program
2. Then type in command:./project3_LRU.o <path of file> <cache size>.This will begin the simulation.
3. After some time (less than 2 sec) the program will be done with the results.

Now change directory to ARC

Steps to compile the ARC file
1. Type in the command: gcc -O3 project3_ARC.c -o project3_ARC.o. This will compile the program
2. Then type in command:./project3_ARC.o <path of file> <cache size>.This will begin the simulation.
(Note: The file will only work for P3.lis for now. Therefore don't use P4.lis or P6.lis)
3. After some time (could take a while for bigger cache sizes so use cache size <= 4096, takes less than 5 min) the program will be done with the results.

