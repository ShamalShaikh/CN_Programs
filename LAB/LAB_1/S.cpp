#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include<ctype.h>
#include <poll.h>
#include <fcntl.h> 
#include <sys/stat.h> 
#include<iostream>
#include<signal.h>
using namespace std;
// 1024 is maximum pipe limit  

int flag = 1, sigcnt = 0;

void fn(int sig) {
	cout << "In handler!!";
	sigcnt++;
}

int main() {
	signal(SIGUSR1, fn);
	char str[8];
	
	int fd[2][2];
	for (int i = 0; i < 2; ++i) {
		if (pipe(fd[i]) == -1)
			return 1;
	}

	int ffd[2];
	
	mkfifo("/tmp/f1", 0666);
	mkfifo("/tmp/f2", 0666);
	//unlink("fifo1")
	ffd[0] = open("/tmp/f1", O_RDONLY|O_CREAT);
	ffd[1] = open("/tmp/f2", O_RDONLY | O_CREAT);

	int pfd[2];
	pfd[0] = fileno(popen("./A", "w"));
	pfd[1] = fileno(popen("./B", "w"));

	struct pollfd pfds[2];
	int timeout, pret;
	for (int i = 0; i < 2; ++i) {
		pfds[i].fd = ffd[i];
		pfds[i].events = POLLIN;
	}

	int pid[2] = {5,5};
	pid[0] = fork();
	if (pid[0] > 0) {
		pid[1] = fork();
	}

	if (pid[0] > 0 && pid[1] > 0) {
		close(fd[0][0]);
		close(fd[1][0]);
		while (1) {

			timeout = 5000;
			pret = poll(pfds, 2, timeout);

			if (pret == 0) {
				cout << "\nTimeout : " << timeout << endl;
			}
			else {
				for (int i = 0; i < 2; ++i) {
					if (pfds[i].revents & POLLIN) {
						memset(str,' ',sizeof(str));
						read(ffd[i], str, sizeof(str));
						if (sigcnt%2 == 0) {
							cout<<"\t\t";
							write(fd[i][1], str, sizeof(str));
							
							cout<<endl;
						}
						else {
							write(pfd[i], str, sizeof(str));
							cout<<endl;
						}
					}
				}
			}
		}
		close(ffd[0]);
		close(ffd[1]);
		close(fd[0][1]);
		close(fd[1][1]);
	}
	else if (pid[0] == 0) {
		while (1) {
			sleep(2);
			close(fd[0][1]);
			read(fd[0][0], str, 100);
			cout << str << endl;
			close(fd[0][0]);
		}
	}
	else {
		while (1) {
			sleep(2);
			close(fd[1][1]);
			read(fd[1][0], str, 100);
			cout << str << endl;
			close(fd[1][0]);
		}
	}
	

	return 0;
}
