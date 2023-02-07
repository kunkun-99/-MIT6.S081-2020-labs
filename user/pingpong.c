#include "kernel/types.h"
#include "user/user.h"
#include <stddef.h>
int
main()
{
    int pid;
    int fd1[2];
    int fd2[1];
    char buf[64];
    pipe(fd1);
    pipe(fd2);
    pid = fork();

    if(pid != 0){
	//parent
	write(fd1[1],"ping",strlen("ping"));
	read(fd2[0],buf,sizeof(buf));	
	printf("%d: received %s\n",getpid(),buf);
	wait(NULL);

    }
    else{
	read(fd1[0],buf,sizeof(buf));
	printf("%d: received %s\n",getpid(),buf);
	write(fd2[1],"pong",strlen("pong"));
    }
    exit(0);






}
