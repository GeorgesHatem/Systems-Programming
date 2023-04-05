#include<stdio.h>
#include<dirent.h>
#include"apue.h"
#include<sys/stat.h>
#include<limits.h>
#include<string.h>

int filewriter(char *, int *, int *);

int main(int argc, char *argv[]){

   struct stat buf;
   DIR* directory;
   struct dirent *readdirec;
   char* pathname = NULL;
   int n;
   int *ntotal = NULL;
   int *sizetotal = NULL;
   
   ntotal = (int*)malloc(sizeof(int));
   pathname = (char*)malloc((strlen(argv[1]) + 2)*(sizeof(char)));
   sizetotal = (int*)malloc(sizeof(int));
   
   if(argc != 2){
   
      err_quit("usage: a.out <pathname>");
   
   }
   
   if(lstat(argv[1], &buf) < 0){
   
      err_quit("lstat error");
   
   }
   
   else{
   
      if(S_ISDIR(buf.st_mode)){
      
         printf("Directory listing of %s:\n\n", argv[1]);
         // printf("\n");
         printf("%s\n", argv[1]);
         strcpy(pathname, argv[1]);
         n = strlen(pathname);
         pathname[n++] = '/';
         pathname[n] = 0;
         filewriter(pathname, ntotal, sizetotal);
         printf("Total space usage: %d\n", *sizetotal);
         printf("Total number of files: %d\n", *ntotal);
         printf("\n");
         printf("Done.\n");
      
      }
      
      else{
      
         err_quit("The entered pathname in terminal is not a directory");
      
      
      }
   
   
   
   }

exit(0);

}

int filewriter(char* pathname, int* ntotal, int* size){

   struct stat buf;
   DIR *directory;
   struct dirent *readdirec;
   char *pathtest;
   int currentsize;
   int n;
   
   if((directory = opendir(pathname)) == NULL){
   
      return 0;
   
   }
   
   while((readdirec = readdir(directory)) != NULL){
   
      if(strcmp(readdirec->d_name, ".") == 0 || strcmp(readdirec->d_name, "..") == 0){
      
         continue;
      
      
      }
      
      pathtest = (char*)malloc((strlen(pathname) + strlen(readdirec->d_name) + 1) * (sizeof(char)));
      
      pathtest = strcat(pathname, readdirec->d_name);
      
      if(lstat(pathtest, &buf) < 0){
      
         return 0;
      
      }
      
      if(S_ISDIR(buf.st_mode)){
      
         printf("\t%s/\n", readdirec->d_name);
         
         n = strlen(pathtest);
         pathtest[n++] = '/';
         pathtest[n] = 0;
         
         if((directory = opendir(pathtest)) == NULL){
         
            return 0;
         
         }
         
         // printf("\t%s/\n", readdirec->d_name);
      
      }
      
      else{
         
         currentsize = buf.st_size;
         printf("\t%s\t%d\n", readdirec->d_name, currentsize);
         ntotal++;
	 *size = (*size) + (currentsize);
      
      }
   
   
   }

return 0;

}
