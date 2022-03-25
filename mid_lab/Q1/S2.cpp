#include"sham.h"
#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to send data

 
void die(char *s)
{
    perror(s);
    exit(1);
}

int main(int argc, char *argv[]) {
        ssize_t nbytes;
        char buffer[16];
        int sfd, cfd, fds;
        struct sockaddr_un addr;
        int f=0;
        while(1){
        unlink("shamsocket");   
        sfd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (sfd == -1)
                perror("Failed to create socket\n");

        memset(&addr, 0, sizeof(struct sockaddr_un));
        addr.sun_family = AF_UNIX;
        cout<<"1\n";
        cout<<"shamal\n";
        printf("Enter message : \n");
        cin>>buffer;
        
        strncpy(addr.sun_path, "shamsocket", sizeof(addr.sun_path) - 1);

        if (bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
              perror("Failed to bind to socket\n");

        if (listen(sfd, 5) == -1)
               perror("Failed to listen on socket\n");

        cfd = accept(sfd, NULL, NULL);
        if (cfd == -1)
                perror("Failed to accept incoming connection\n");
            cout<<"2\n";
        fds = recv_fd (cfd);

        struct sockaddr_in si_other;
        int s, i, slen=sizeof(si_other);
        char buf[BUFLEN];
        char message[BUFLEN];
     cout<<"3\n";
        if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
        {
            die("socket");
        }
     cout<<"4\n";
        memset((char *) &si_other, 0, sizeof(si_other));
        si_other.sin_family = AF_INET;
        si_other.sin_port = htons(PORT);
        si_other.sin_addr.s_addr=INADDR_ANY;

        while(1)
        {
            printf("Enter message : \n");
            cin.getline(message,100);
             //try to receive some data, this is a blocking call
            if (recvfrom(fds, buf, 100, 0, (struct sockaddr *) &si_other,(socklen_t*) &slen) == -1)
            {
                die("recvfrom()");
            }
            
             
            //receive a reply and print it
            //clear the buffer by filling null, it might have previously received data
            memset(buf,'\0', 100);
            //send the message
            if (sendto(fds, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen)==-1)
            {
                die("sendto()");
            }
             
            puts(buf);
        }
    }
    return 0;
}