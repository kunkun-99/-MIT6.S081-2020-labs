#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"
#define MAXN 1024
int
main(int argc, char* argv[])
{
    //存放子进程exec的参数
    char * argvs[MAXARG];
    for(int i = 1; i < argc; i++)
    {
	argvs[i-1] = argv[i];
    }
    
    char buf[MAXN] = {"\0"};
    int n;
    while((n = read(0,buf,MAXN))>0)
    {
	char temp[MAXN]={"\0"};
	argvs[argc-1] = temp;
	for(int i = 0;i < strlen(buf);i++){
	    if(buf[i]=='\n')
	    {
		int pid = fork();
		if(pid == 0)
		{
		    exec(argv[1],argvs);
		}
		wait(0);
	    }
	    else
	    {
		temp[i] = buf[i];
	    }
	}
    }
    exit(0);

}
