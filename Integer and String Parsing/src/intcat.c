#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFERSIZE 128 //Size of buffer, chose power of 2

/*
  The main function takes in a parameter for the input file and prints the
  contents in that file.

  @param argc: argc is the number of parameters passed to main
  @param argv[]: the actual parameters

 */
int main(int argc, char *argv[]){

  //If there isn't enough arguments passed, then quit
  if(argc != 2){
    fprintf(stderr, "usage: intgen <infile>\n");
    exit(1);
  }

  char *infile = argv[1]; //String form of the input file

  int buffer[BUFFERSIZE]; //Buffer allocated for the binary numbers

  //Open the file for read only and check for errors
  int ifile = open(infile, O_RDONLY);
  assert(ifile > -1);
  
  //While read hasn't reached end of line, check if there is a negative and 
  //create a space. Then print the number from buffer
  while(read(ifile, &buffer, sizeof(int)) > 0){
      if(buffer[0] == '-'){
         buffer[0] = ' ';
        printf("- %d\n", *buffer); 
      }
      else{
      printf("%d\n", *buffer);
      } 
  }
  
  close(ifile); //Close the file

  return 0;
}
