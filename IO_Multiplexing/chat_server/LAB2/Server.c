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

struct read1{
	char *a1;
	char *a2;
};

void *reader(void *params){
	struct thread_args *args = (struct thread_args *) params;
	char s[1024];
	int fd;
	while(1){
		fd = open(args->client, O_RDONLY);
		read(fd, s, sizeof(s));
		printf("\t\t\tserver: %s", s);
		close(fd);
	}
}

void *writer(void *params){
	struct thread_args *args = (struct thread_args *) params;
 	char s[1024];
 	int fd,i;
 	while(1){
 		fd = open(args->client, O_WRONLY);
 		struct iovec iov[3];
 		char buf[3][128];
 		for(i = 0; i < 3; i++)
 			scanf(" %[^\n]s", buf[i]);
 		for (i = 0; i < 3; i++) {
            iov[i].iov_base = (void *)buf[i];
            iov[i].iov_len = sizeof(buf[i]);
        }
 		ssize_t  nrr= writev(fd, iov, 3);
 		printf("Wrote: %ld\n",nrr);
 		close(fd);
 	}
}

int main()
{
	char *server = "/tmp/myfifo", *client = "/tmp/myfifo1"; 
	
    mkfifo(server, 0666);
	mkfifo(client, 0666);
	
    struct thread_args *args1 = malloc(sizeof(struct thread_args)), *args2 = malloc(sizeof(struct thread_args));
    args1->client = server, args2->client = client;
    
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, reader, args1);
    pthread_create(&thread2, NULL, writer, args2);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    
    unlink(server),unlink(client);
    return 0;
}
