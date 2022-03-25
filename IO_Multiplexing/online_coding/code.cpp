#include<iostream>
using namespace std;
int main(int ac, char *av[]){
int x,y,result;
FILE *fp = fopen("i.txt","r");
char c = fgetc(fp);
x = atoi(&c);
c = fgetc(fp);
y = atoi(&c);
result = x+y;
printf("%d",result);
return 0;
}
