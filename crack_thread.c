#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <pthread.h>


 
 //cc -o crack_thread crack_thread.c -lcrypt -pthread

 
/**
 Required by lack of standard function in C.   
*/
int count = 0;

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

/**
 This function can crack the kind of password explained above. All
combinations
 that are tried are displayed and when the password is found, #, is put
at the
 start of the line. Note that one of the most time consuming operations
that
 it performs is the output of intermediate results, so performance
experiments
 for this kind of program should not include this. i.e. comment out the
printfs.
*/

void crack(char *salt_and_encrypted)
{
  int i;
pthread_t thread_1, thread_2;

    void *kernel_function_1();
    void *kernel_function_2();

 
    
    pthread_create(&thread_1, NULL,kernel_function_1, salt_and_encrypted);
    pthread_create(&thread_2, NULL,kernel_function_2, salt_and_encrypted);

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
 }
void *kernel_function_1(void *salt_and_encrypted){
  int a, b,c;     // Loop counters
  char salt[7];    // String used in hahttps://www.youtube.com/watch?v=L8yJjIGleMwshing the password. Need space
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
     // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(a='A'; a<='M'; a++){
    for(b='A'; b<='Z'; b++){
      for(c=0; c<=99; c++){
        sprintf(plain, "%c%c%02d", a,b,c);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        }else{printf("%-8d%s %s\n", count, plain, enc);}
} 
    }
  }
  printf("%d solutions explored\n", count);
}

void *kernel_function_2(void *salt_and_encrypted){
  int a, b,c;     // Loop counters
  char salt[7];    // String used in hahttps://www.youtube.com/watch?v=L8yJjIGleMwshing the password. Need space
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  //int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(a='N'; a<='Z'; a++){
    for(b='A'; b<='Z'; b++){
      for(c=0; c<=99; c++){
        sprintf(plain, "%c%c%02d", a,b,c);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        }else{printf("%-8d%s %s\n", count, plain, enc);}
} 
    }
  }
  printf("%d solutions explored\n", count);
}


//Calculating time

int time_difference(struct timespec *start, struct timespec *finish, long long int *difference)
 {
	  long long int ds =  finish->tv_sec - start->tv_sec; 
	  long long int dn =  finish->tv_nsec - start->tv_nsec; 

	  if(dn < 0 ) {
	    ds--;
	    dn += 1000000000; 
  } 
	  *difference = ds * 1000000000 + dn;
	  return !(*difference > 0);
}



int main(int argc, char *argv[]){
 struct timespec start, finish;

  long long int time_elapsed;
  
 
  clock_gettime(CLOCK_MONOTONIC, &start);
 
  crack("$6$AS$eje0DWtfLsXbSENYo1/sApv8bROZShqBH8vBXdhimBkJBM4MgyNBU0j1Fi9oaA8YI/CFo7l0HOwZYO4rzZmW21");	

  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("%d solutions explored\n Time elapsed was %lldns or %0.9lfs\n", count, time_elapsed,  (time_elapsed/1.0e9)); 
  


  return 0;
}

