#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void free_map(char **clear)
{
    int i = 0;
    while(clear[i])
    {
        free(clear[i]);
        i++;
    }
    free(clear);
    return;
}

char ** export_variable(char **env, char *arg)
{   
    char **new_env;
    int i = 0;
    while(env[i])
        i++;
    new_env = malloc((i+1) * (sizeof(char *)));
    
        
}

int main (int argc, char **argv, char**env)
{
    if(argc<=1)
        return;
    env = export_variable(env, argv[1]);
    int i=0;
    while(env[i])
    {
       printf("%s\n", env[i]);
        i++;
    }
    free(env);
}