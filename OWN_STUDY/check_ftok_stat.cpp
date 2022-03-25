#include<bits/stdc++.h>
#include <sys/ipc.h>
 #include <fcntl.h>
 #include <sys/types.h>
 #include <sys/stat.h>
#include <dirent.h>
int main(int argc, char **argv){
	 struct stat pp;
	 if (argc != 2)
	 perror("usage: ftok <pathname>");
	 stat(argv[1], &pp);
	 printf("st-dev: %lx, st-ino: %lx, key: %x\n",(u_long) pp.st_dev, (u_long) pp.st_ino,ftok(argv[1], 0x57));
	 exit (0);
 }
