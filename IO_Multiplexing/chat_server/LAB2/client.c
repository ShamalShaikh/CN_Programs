#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>
#include <sys/uio.h>

#define create_args malloc(sizeof(struct thread_args))

struct thread_args{
	char* client;	
};

void *reader(void *params){
	struct thread_args *args = (struct thread_args *) params;
	char s[1024];
	int fd, i;
	while(1){
		struct iovec iov[3];
		char buf[3][128];
		fd = open(args->client, O_RDONLY);
		for(i = 0 ; i < 3; i++)
		{
			iov[i].iov_base = buf[i];
	        iov[i].iov_len = sizeof (buf[i]);
	    }
		ssize_t nrr = readv (fd, iov, 3);
		printf("\t\t\tRead: %ld\n", nrr);
		printf("\t\t\tNav:\n");
		for(i = 0 ; i < 3; i++)
			printf("\t\t\t%s\n", (char *)iov[i].iov_base);
        printf("\n");
		close(fd);
	}
}

void *writer(void *params){
	struct thread_args *args = (struct thread_args *) params;
 	char s[1024];
 	int fd;
 	while(1){
 		fd = open(args->client, O_WRONLY);
 		fgets(s, sizeof(s), stdin);
 		write(fd, s, sizeof(s));
 		close(fd);
 	}
}

int main()
{
	char *server = "/tmp/myfifo", *client = "/tmp/myfifo1"; 
	
    mkfifo(server, 0666);
	mkfifo(client, 0666);
	
    struct thread_args *args1 = malloc(sizeof(struct thread_args)), *args2 = malloc(sizeof(struct thread_args));
    
	args1->client = client, args2->client = server;
    
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, reader, args1);
    pthread_create(&thread2, NULL, writer, args2);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    unlink(server),unlink(client);
    return 0;
}
