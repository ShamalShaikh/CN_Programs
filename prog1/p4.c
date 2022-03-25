#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main(){
printf("Hey! My name is Muhammad!");
printf("\nMy ID is %d",getpid());
printf("\nI am the last! Bye!\n");
return 0;
}
