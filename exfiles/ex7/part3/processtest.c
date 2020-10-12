/* Process and shared memory example based on code from "Operating System Concepts" (Ninth Edition)
   by  Silberschatz, Galvin, and Gagne. Copyright John Wiley & Sons - 2013 */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define   MAX_COUNT  10
#define   MSIZE 32
void  ChildProcess(void);                /* child process prototype  */
void  ParentProcess(void);               /* parent process prototype */

void  main(void)
{
     pid_t pid;

     pid = fork();
     if (pid == 0) 
          ChildProcess();
     else 
          ParentProcess();
}

void  ChildProcess(void)
{
     int i, memory;
     const char *name = "/shared_value";    
     void *ptr;

     memory = shm_open(name, O_RDONLY, 0666);
     
     ptr = mmap(0, MSIZE, PROT_READ, MAP_SHARED, memory, 0);

     for (i = 0; i < MAX_COUNT; i++)
     {
         printf("Child process, word %d is \"%s\"\n", (i+1), ptr);
         sleep(1);
     }
     printf("   *** Child process is done ***\n");

     close(memory);
     shm_unlink(name);
}

void  ParentProcess(void)
{
     int i, memory;
     const char *name = "/shared_value";
     const char *sentence[] = {"This", "is", "a", "sentence", "with", "ten", "words", "in", "it,", "just."};
     void *ptr;

     memory = shm_open(name, O_CREAT | O_RDWR, 0666);
     ftruncate(memory, MSIZE);

     ptr = mmap(NULL, MSIZE, PROT_READ | PROT_WRITE, MAP_SHARED, memory, 0);
    
     for (i = 0; i < MAX_COUNT; i++)
     {  
         printf("Parent Process, word %d is \"%s\"\n", (i+1), sentence[i]);         
         sprintf(ptr, "%s", sentence[i]);
         sleep(1);
     }
     printf("*** Parent is done ***\n");
}
