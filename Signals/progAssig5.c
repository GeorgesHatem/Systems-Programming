/*

   Name: Georges Hatem
   CS525 Assignment 5: Sending Signals
   
   The code below simulates an alarm clock. The child process waits for 5 seconds before sending a SIGALRM
   signal to its parent. Then, the parent process catches the SIGALRM signal.

   Due Date: November 21, 2021, at 11:59 PM EST


*/


#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

void signalalarm();

int main(void){

   unsigned int waitTime = 5; // Child process will wait 5 seconds before sending a SIGALRM signal to its parent
   
   pid_t pid;
   
   printf("Alarm app starting\n");
   
   // Child Process
   if((pid = fork()) == 0){
   
      printf("Waiting for the alarm to sound....\n\n");
      sleep(waitTime); // Waiting for 5 seconds
      kill(getppid(), SIGALRM); // sending a SIGALRM to its parent
   
   }
   
   // Parent Process
   else{
   
      signal(SIGALRM, signalalarm); // Parent catching SIGALRM with a call to signal
      
      while(1){
      
      
      }
   
   }

}

void signalalarm(){

   printf("Ding!\nDone.\n");

}
