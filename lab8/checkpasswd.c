#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 256

#define SUCCESS "Password verified\n"
#define INVALID "Invalid password\n"
#define NO_USER "No such user\n"

int main(void) {
  char user_id[MAXLINE];
  char password[MAXLINE];

  /* The user will type in a user name on one line followed by a password 
     on the next.
     DO NOT add any prompts.  The only output of this program will be one 
	 of the messages defined above.
     Please read the comments in validate carefully
   */

  if(fgets(user_id, MAXLINE, stdin) == NULL) {
      perror("fgets");
      exit(1);
  }
  if(fgets(password, MAXLINE, stdin) == NULL) {
      perror("fgets");
      exit(1);
  }
  
  // set up the pipes!!
  int pipefd[2];
  pipe(pipefd);

  //set up the fork! 
  pid_t pid = fork();

  if(pid==0){
    close(pipefd[1]); // no writing needed
    dup2(pipefd[0], STDIN_FILENO); // however we do want our read pipe to replace stdin
    close(pipefd[0]); // but not right now, it's for later
    execl("./validate", "validate", user_id, password, NULL);

    perror("validate failed to reach an exit(i)");
    exit(127);
  }

  close(pipefd[0]); // this time no reading required!
  dprintf(pipefd[1],"%s",user_id); 
  usleep(10000);
  dprintf(pipefd[1],"%s",password);
  // give explicit text to be written to write end of pipe
  close(pipefd[1]); // done with assigning it so we can close it

  int status;
  waitpid(pid,&status,0);

  if(WIFEXITED(status)==1){
    //exited with some code, assigns code to outcome, then proceeds by cases
    int outcome = WEXITSTATUS(status);
    if(outcome==0){
      printf(SUCCESS);
    }
    if(outcome==1){
      exit(0);
    }
    if(outcome==2){
      printf(INVALID);
    }
    if(outcome==3){
      printf(NO_USER);
    }
  }
  else{
    exit(1);
  }
  return 0;
}
