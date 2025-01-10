#include <stdio.h>
#include <string.h>

int main() {

  while(1){
    // Flush after every printf
    setbuf(stdout, NULL);
    // Uncomment this block to pass the first stage
    printf("$ ");
    // Wait for user input
    char input[100];
    fgets(input, 100, stdin);
    //Removes the new line of the input buffer
    input[strlen(input) - 1] = '\0';

    //If command is echo, print the characters following the command
    if(strncmp(input,"echo ",5) == 0){
      printf("%s\n",input+5);
      continue;
    }

    //Exits shell if input "exit 0"
    if(strcmp(input,"exit 0") == 0){
      break;
    }
    
    //Prints (input command): command not found
    printf("%s: command not found\n",input);
  }
  
  return 0;
}
