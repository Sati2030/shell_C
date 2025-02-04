#include "commands.h"
#include "input_reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ECHO "echo"
#define EXIT "exit"
#define TYPE "type"
#define PWD "pwd"
#define CD "cd"

//Redirects the builtin commands
void command_handling(Arguments *args){

    char *command = args->arguments[0];


    if(!strcmp(command,ECHO)){
        echo(args);
    }
    else if(!strcmp(command,TYPE)){
        type(args);
    }
    else if(!strcmp(command,EXIT)){
        exit_(args);
    }
    else if(!strcmp(command,PWD)){
        pwd();
    }
    else if(!strcmp(command,CD)){
        char *directory = args->arguments[1];
        cd(directory);
    }

    return;
}

//Function for the echo command
void echo(Arguments *args){

    for(int i = 1; i<(args->count);i++){
        printf("%s",args->arguments[i]);
        if(i < (args->count-1)){
            printf(" ");
        }
    }   

    printf("\n");
    return;
}

//Function for the type command
void type(Arguments *args){

    char *type;

    for(int i = 1; i<args->count;i++){
        if(!strcmp(args->arguments[i],"")){ //Handles if the second argument is empty
            continue;
        }
        type = valid_command(args->arguments[i]);
        if(type){
            printf("%s is %s\n",args->arguments[i],type);
            if(strcmp(type,"a shell builtin"))free(type);
        }
        else{
            printf("%s: not found\n",args->arguments[i]);
        }
    }

    return;
}

//Function for the exit command
void exit_(Arguments *args){
    
    //Handles if there is just exit
    if(args->count < 2){
        printf("Not enough arguments\n");
        return;
    }
    else if(!strcmp(args->arguments[1],"0")){
        for(int i = 0; i<(args->count);i++){
            free(args->arguments[i]);
        }
        free(args->arguments);
        activateCannonMode();
        exit(0);
    }
    else{
        printf("Not a valid argument\n");
        return;
    }

    return;
}

//Function for the pwd command
void pwd(){
    char *cwd = getcwd(NULL,0);

    if(cwd){
        printf("%s\n",cwd);
        free(cwd);
    }
    else{
        perror("Error locating current working directory\n");
    }

    return;
}

//Function for the cd command
void cd (char *dir){
    //If there is no argument or the argument is "~" go to the HOME directory
    if(!dir || !strcmp(dir,"~")){
        if(!chdir(getenv("HOME"))){
            return;
        }
        else{
            printf("Error changing to home directory\n");
            return;
        }
    }
    //Else move to the specified directory
    else if(!chdir(dir)){
        return;
    }
    //If specified directory does not exist
    else{
        printf("cd: %s: No such file or directory\n",dir);
    }

    return;
}