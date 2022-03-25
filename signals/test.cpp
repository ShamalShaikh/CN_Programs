#include<bits/stdc++.h>
/*#include<sys/ioctl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#define magic_no 'S'
#define seq_no 0
#define setfont _IOW(magic_no,seq_no,unsigned long)
using namespace std;
int main(){
	
	int fd=open("hello1.txt",O_WRONLY);
	//int fd=fileno(f);
	char *c="Arial";
	//unsigned long int l=(long)c;
	int k=ioctl(fd,setfont,c);
	write(fd,"abcde",20);
	char s[20];
	read(fd,s,20);
	cout<<s<<endl;
	close(fd);
}*/
#include <sys/ioctl.h>
#include <stdio.h>
int main(int argc, char **argv)
{
  struct winsize sz;

  ioctl(0, TIOCGWINSZ, &sz);
  printf("Screen width: %i  Screen height: %i\n", sz.ws_col, sz.ws_row);
  return 0;
}


