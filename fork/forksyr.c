/*
  Nerys Jimenez Pichardo
  The College of Saint Rose
  Operating Systems
  Spring 2016

  forksyr.c program uses the fork() system call to generate
  child process using the Collatz conjectures sequence.
  The starting number will be provided from the command line.
  There is error checking to ensure that a positive integer is passed 
  on the command line. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  long num_process;
  pid_t pid;
  
  //command line is required
  if(argc < 2)
  {
    fprintf(stderr, "Usage: %s num_process \n", argv[0]);
    return 0;
  }
  
  //get command line
  num_process = atoi(argv[1]);
  
  //only positive command line
  if(num_process < 0)
  {
      fprintf(stderr, "%s: num_process must be positive \n", argv[0]);
      return 0;
  }
  
  pid = fork();
  
  //if can't create child, exit
  if(pid < 0)
  {
    printf("Could not create child %d \n", num_process);
    return 0;
  }
  
  //generates child process using the Collatz conjectures sequence
  if(pid == 0)
  {
    while(num_process != 0)
    {
      printf("Created child %d, pid %d \n",num_process, getpid());
      if(num_process == 1)
      {
	break;
      }
      if((num_process % 2) == 0) //if even
      {
	num_process = (num_process/2);
      }
      else
      {
	num_process = 3 * num_process + 1;
      }
     }
     return 0;
    }
  else
  {
    waitpid(pid,NULL,0);
  }
  
  //end of program
  return 0;
}
