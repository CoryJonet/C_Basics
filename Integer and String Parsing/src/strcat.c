#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define BUFFERSIZE 128 //Size of buffer, chose a power of 2

/*
  The main function takes in a parameter for the input file and prints the 
  contents in that file.

  @param argc: argc is the number of parameters passed to main
  @param argv[]: the actual parameters

*/
int main(int argc, char *argv[]){

  //If there aren't enough arguments passed, then quit
  if(argc != 2){
  fprintf(stderr, "usage: strcat <infile>\n");
    exit(1);
  }

  char *infile = argv[1]; //String form of the input file

  FILE *fp = fopen(infile, "r"); //Pointer to the input file
  assert(fp != NULL);

  char buffer[BUFFERSIZE]; //Array (buffer) allocated for strings

  //While fgets doesn't return the NULL terminating character, obtain the next
  //string from buffer and print it
  while((fgets(buffer, BUFFERSIZE, fp)) != NULL){
     printf("%s", buffer);
  }

  fclose(fp); //Close the file

  return 0; 
}

