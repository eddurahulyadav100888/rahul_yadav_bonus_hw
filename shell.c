#define CMDSIZE 1024
#define TOKEN_SIZE 64
#define TOKEN_DELIM " \t\r\n\a"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h> 

char *read_cmd(void)
{

  /*Read the command given in the prompt
    Assuming the command length is unknown,
    reallocation of space is done on exceeding a given length.
  */
  int cmdmax = CMDSIZE;
  int position = 0;
  char *buffer = (char*)malloc(sizeof(char) * cmdmax);
  int ch;

  if (!buffer) {
    fprintf(stderr, "Buffer allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    ch = getchar();

    if (ch == EOF || ch == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = ch;
    }
    position++;

    // Reallocate buffer on exceeding the maximum length
    if (position >= cmdmax) {
      cmdmax += CMDSIZE;
      buffer = (char*)realloc(buffer, cmdmax);
      if (!buffer) {
        fprintf(stderr, "Buffer allocation error!\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}


char **process_cmd(char *cmd)
{
  /*Command line is tokenized for easier processing and execution.*/
  
  int buffermax = TOKEN_SIZE, position = 0;
  char **tokens = (char**)malloc(buffermax * sizeof(char*));
  char *token;

  if (!tokens) {
    fprintf(stderr, "token allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(cmd, TOKEN_DELIM);
  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= buffermax) {
      buffermax += TOKEN_SIZE;
      tokens = (char**)realloc(tokens, buffermax * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "token allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, TOKEN_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}

int start_pid(char **args)
{
  pid_t pid, wait_pid;
  int status;

  pid = fork();
  if (pid == 0) {
    if (execvp(args[0], args) == -1) {
      perror("error!");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    // If error on forking
    perror("error!");
  } else {
    do {
      wait_pid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

//declaring shell commands
int shell_cd(char **args);
int shell_list(char **args);
int shell_help(char **args);
int shell_quit(char **args);
int shell_history(char **args);

char *shell_cmd_str[] = {
  "cd",
  "list",
  "help",
  "quit",
  "history"
};

int (*shell_cmd_func[]) (char **) = {
  &shell_cd,
  &shell_list,
  &shell_help,
  &shell_quit,
  &shell_history
  
};

int shell_cmd_num() {
  return sizeof(shell_cmd_str) / sizeof(char *);
}

int shell_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "Expected an argument for \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("Error!");
    }
  }
  return 1;
}

int shell_list(char **args){
  DIR *d;
  struct dirent *dir;
  d = opendir(".");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      printf("%s\n", dir->d_name);
    }
    closedir(d);
  }
  return 1;
}
int shell_help(char **args){
  printf("Following commands are available in this shell:\n");
  printf("1. list : Print out all files present in the current directory.\n");
  printf("2. cd <directory> : Change the directory to specified destination.\n");
  printf("3. history : List out all the previous commands given to the shell.\n");
  printf("4. quit\t: Exit out of the shell prompt.\n");
  return 1;

}


int shell_quit(char **args)
{
  return 0;
}

int shell_history(char **args){
  FILE *fPtr;
  fPtr = fopen("uab_sh.log", "r");
  char ch;
  do
    {
      ch = fgetc(fPtr);
      putchar(ch);
    } while (ch != EOF);
  fclose(fPtr);
  return 1;
}


int execute(char **args)
{
  int i;
  if (args[0] == NULL) {
    // if command is empty
    return 1;
  }

  for (i = 0; i < shell_cmd_num(); i++) {
    if (strcmp(args[0], shell_cmd_str[i]) == 0) {
      return (*shell_cmd_func[i])(args);
    }
  }
  return start_pid(args);
}

void update_log(char* cmd){
  FILE *fPtr;
  fPtr = fopen("uab_sh.log", "a");
  if (fPtr == NULL)
    {
        /* Unable to open file hence exit */
        printf("Please check whether file exists and you have write privilege.\n");
        exit(EXIT_FAILURE);
    }
   fputs(cmd, fPtr);
   fputs("\n", fPtr);
   fclose(fPtr);
}


void run_shell(void){
  char *cmd;
  char **args;
  int status;

  do {
    // Command prompt
    printf("uab_sh> ");
    // Read the user input as command
    cmd = read_cmd();
    // Update the log for keeping history
    update_log(cmd);
    // Tokenize the cmd
    args = process_cmd(cmd);
    // Execute commands
    status = execute(args);
    free(cmd);
    free(args);
  } while (status);
}

int main(int argc, char **argv)
{
  run_shell();
  return 0;
}
