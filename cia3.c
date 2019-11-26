#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
int fd[2]; //array for reading and writing pipe
if(pipe(fd) == -1) //Start the pipe and check for its failure
{
perror("ERROR creating a pipe\n"); //print the system error message if failed
exit(1);
}
if (!fork()) // this is for the child process
{
close(1); // close the standard output file
dup(fd[1]); // now fd[1] (the writing end of the pipe) is the standard output
close(fd[0]); // the reader end is closed because it is writing end.
execlp("ls", "ls", NULL); // executes the ls process
}
else // this is for the parent process 
{
close(0); // close the standard input file
dup(fd[0]); // fd0 is the standard input
close(fd[1]);// the write end of the pipe is closed
execlp("wc", "wc", "-l", NULL); //executes the wc process
}
return(0);
} 
