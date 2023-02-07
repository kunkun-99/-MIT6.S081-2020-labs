#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
prime(int *fd)
{
    close(fd[1]);
    int newfd[2];
    pipe(newfd);
    if(fork()==0)
    {
	prime(newfd);
	exit(0);
    }
    else
    {
	close(newfd[0]);
	int n;
	//先把第一个数打印出来
	if(read(fd[0],&n,sizeof(n))==sizeof(n))
	{
	    printf("prime %d\n",n);

	}
	int temp;
	while(read(fd[0],&temp,sizeof(temp))==sizeof(temp))
	{
	    if(temp%n!=0)
	    {
		write(newfd[1],&temp,sizeof(temp));
	    }
	}
	close(newfd[1]);
	wait(0);
	exit(0);
    }

}

int
main(int argc, char *argv[])
{

    int fd[2];
    pipe(fd);
    if(fork()==0)
    {
	//子进程
	prime(fd);
	
    }
    else
    {
	//父进程
	close(fd[0]);
	int limit = 35;
	if(argc == 2)limit = atoi(argv[1]);
	for(int i = 2; i <= limit; i++)
	{
	    write(fd[1],&i,sizeof(i));

	}
	close(fd[1]);
	wait(0);
    }
    exit(0);


}
