#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <memory>
#include "Process.hpp"


Process::Process(){

int pid = fork();
if(pid == 0)
{
	// this is the child process
	execl("./child", NULL, NULL);
	exit(0); // shouldn't ever get here
}

}

//Deconstructor
Process::~Process(){

cout << "Process[" << getpid() << "]: Parent executing..." << endl;
sleep(2); // wait two seconds

if(wait(NULL) > 0)
cout << "Process[" << getpid() << "]: Parent detects child terminating..."
<< endl;

cout << "Process[" << getpid() << "]: Parent terminating." << endl;
return 0;
}

int main (void)
{

	pid_t pid;
    int pipe_in[2];
    int pipe_out[2];
    char buffer[400];

    pipe (pipe_in);
    pipe (pipe_out);

    pid = vfork ();
    if (pid == (pid_t) 0) /* child 1 */
    {
	
                close(pipe_in[1]);
                close(pipe_out[0]);
		
		
                dup2(pipe_in[0], 0);
                close(pipe_in[0]);
                dup2(pipe_out[1], 1);
                close(pipe_out[1]);

		
                execl("/bin/tr", "tr", "a", "b" , 0);
                perror("exec prog1");
                exit(1);
    }
    
    else 
    {
                close(pipe_in[0]);
                close(pipe_out[1]);
               
                write(pipe_in[1], "Data\n", 14);
                read(pipe_out[0], buffer, sizeof(buffer));

                close(pipe_in[1]);
                waitpid(pid, NULL, 0);
                close(pipe_out[0]);
                return EXIT_SUCCESS;
    }
}