/*
    Simple udp client
*/
#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define SERVER "172.30.32.170"//33.156"//34.229:sush  34.112:pooja  33.212:mukhi//9"
#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to send data
 
void die(char *s)
{
    perror(s);
    exit(1);
}
 
int main(void)
{
    struct sockaddr_in si_other;
    int s, i, slen=sizeof(si_other);
    char buf[BUFLEN];
    char message[BUFLEN];
 
    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
 
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
    // si_other.sin_addr.s_addr=inet_addr(SERVER);
    si_other.sin_addr.s_addr=INADDR_ANY; 
 
    while(1)
    {
        printf("Enter message : ");
        cin.getline(message,BUFLEN);
         
        //send the message
        if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            die("sendto()");
        }
         
        //receive a reply and print it
        //clear the buffer by filling null, it might have previously received data
        memset(buf,'\0', BUFLEN);
        //try to receive some data, this is a blocking call
        if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other,(socklen_t*) &slen) == -1)
        {
            die("recvfrom()");
        }
         
        puts(buf);
    }
 
    close(s);
    return 0;
}