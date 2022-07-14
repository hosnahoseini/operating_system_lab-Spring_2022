#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("Enter some srting after command!");
        return 1;
    }

    // create two pipes:
    // - descriptors used by parent to write to child

    int descriptors[2];

    // read:[0] - write:[1]
    if (pipe(descriptors) != 0)  /* || not && */
    {
        fprintf(stderr, "pipes failed!\n");
        return 1;
    }

    // fork() child process
    int child = fork();

    if (child < 0)
    {
        fprintf(stderr, "fork failed!");
        return 1;
    }
    else if (child != 0)    /* parent */
    {
        while (wait(NULL) > 0);

        // close unwanted pipe (write)
        close(descriptors[1]);

        // read from pipe
        char pipelineText[100];
        int n = read(descriptors[0], pipelineText, sizeof(pipelineText) - 1);
        pipelineText[n] = '\0';
        printf("Parent: read from pipe '%s'\n", pipelineText);
        close(descriptors[0]);


        for (int i = 0; pipelineText[i]!='\0'; i++)
    	{

    		if(pipelineText[i] >= 'a' && pipelineText[i] <= 'z')
    		{
    			pipelineText[i] = pipelineText[i] - 32;
  		}		
    		else if(pipelineText[i] >= 'A' && pipelineText[i] <= 'Z')
    		{
    			pipelineText[i] = pipelineText[i] + 32;
  		}
    	}

        printf("Parent: after processing: %s\n",pipelineText);

        
    }
    else
    {

        // close unwanted pipe
        close(descriptors[0]);

        // write from terminal to pipe
        printf("Child: writing to pipe '%s'\n", argv[1]);
        write(descriptors[1], argv[1], strlen(argv[1]));
        close(descriptors[1]);

        
    }

    return 0;
}