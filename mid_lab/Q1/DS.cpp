/*

socket()
socket()
bind()
bind()
listen()
listen() 
select()
accept()



*/

// DS :


// int sfd1 ,sfd2;
// connection oriented
// select use 
// while(1){

//     accept

//     if(sfd1){
//         signal S1
//         and give C1 to that S1
//     }
//     else if(sfd2){
//         send_fd(shamsocket,sfd2) 
//     }
// }




// S1  connection oriented: 

// pause();

// recv from C1
//  see 1,2,3

// if(3){
//     make fork process and serve
// }
// else if(2){
//     make thread and func and serve
// }
// else if(1){
//     serve itself
// }

// S2 connectionless:

// recv_fd()

// read()
// send()

// C1 : 

// connection oriented client

// sends priority

// clsoe

// C2 : 

// connectionless

// sendto 
// receive from


#include"sham.h"
#define ADDRESS "shamsocket"

int main(int argc,char *argv[]){
    int sfd[2];int  usfd,opt=1;
    struct sockaddr_in serv_addr1,serv_addr2,cli_addr1,cli_addr2;
    socklen_t cli_len1,cli_len2;
    int port_no1=atoi(argv[1]);
    int port_no2=atoi(argv[2]);
    struct sockaddr_un userv_addr,ucli_addr;
    socklen_t userv_len,ucli_len;

    if((sfd[0] = socket(AF_INET,SOCK_STREAM,0))==-1)
        perror("\n socket ");
    else 
        printf("\n socket created successfully");

    if((sfd[1] = socket(AF_INET,SOCK_STREAM,0))==-1)
        perror("\n socket ");
    else 
        printf("\n socket created successfully");  

    if((usfd = socket(AF_UNIX , SOCK_STREAM , 0))==-1)
        perror("\n socket ");
    else 
        printf("\n socket created successfully");      
  

    if (setsockopt(sfd[0], SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT , &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 

    if (setsockopt(sfd[1], SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT , &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 

    bzero(&userv_addr,sizeof(userv_addr));

    userv_addr.sun_family = AF_UNIX;
    strcpy(userv_addr.sun_path, ADDRESS);
    unlink(ADDRESS);
    userv_len = sizeof(userv_addr);

    if(bind(usfd, (struct sockaddr *)&userv_addr, userv_len)==-1)
    perror("server: bind");

    listen(usfd,10);

    ucli_len=sizeof(ucli_addr);
     

    bzero(&serv_addr1,sizeof(serv_addr1));

    serv_addr1.sin_family = AF_INET;
    serv_addr1.sin_port = htons(port_no1);
    serv_addr1.sin_addr.s_addr = INADDR_ANY;

    bzero(&serv_addr2,sizeof(serv_addr2));

    serv_addr2.sin_family = AF_INET;
    serv_addr2.sin_port = htons(port_no2);
    serv_addr2.sin_addr.s_addr = INADDR_ANY;

    if(bind(sfd[0],(struct sockaddr *) &serv_addr1,sizeof(serv_addr1))==-1)
        perror("\n bind : ");
    else 
        printf("\n bind successful ");

    if(bind(sfd[1],(struct sockaddr *) &serv_addr2,sizeof(serv_addr2))==-1)
        perror("\n bind : ");
    else 
        printf("\n bind successful ");

    listen(sfd[0],10);

    listen(sfd[1],10);

    int nsfd1,nsfd2;
    cout<<"\nsignal sent\n";
    cout<<"passsing fd\n";
    fd_set readset;
    FD_ZERO(&readset);
    
    int max=-1;
    
    for(int i=0;i<2;i++)
    {
        FD_SET(sfd[i], &readset);
        if(sfd[i]>max)
        max=sfd[i];      
    }
    struct timeval t;
    t.tv_sec=3;
    t.tv_usec=100;
    int rv = select(max + 1, &readset, NULL, NULL, &t);

    if (rv == -1) 
    {
        perror("select");
    }
    
    else if (rv == 0) 
    {
            printf("Timeout occurred!\n");
    } 
    
    else 
    {
        int i;
        // check for events 
        
            if (FD_ISSET(sfd[0], &readset)) 
        {
            if((nsfd1 = accept(sfd[0] , (struct sockaddr *)&cli_addr1 , &cli_len1))==-1)
                perror("\n accept ");
            else 
                printf("\n accept successful");

            int fd = fileno(popen("pidof ./S1", "r"));
            char s[1000];
            read(fd, &s, 1000);
            int x = atoi(s);

            kill(x,SIGCONT);

            close(sfd[0]);
            FD_CLR(sfd[0],&readset);
            }
        else{
                if((nsfd2 = accept(sfd[1] , (struct sockaddr *)&cli_addr2 , &cli_len2))==-1)
                    perror("\n accept ");
                else 
                    printf("\n accept successful");

                int nusfd;
                nusfd=accept(usfd, (struct sockaddr *)&ucli_addr, &ucli_len);

                send_fd(nusfd,nsfd2);
        }    
    }   

    return 0;
}


