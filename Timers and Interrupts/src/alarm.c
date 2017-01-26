#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <assert.h>

volatile int interval = 0; //Interval in seconds
volatile int runLength = 0; //Total seconds program will run
volatile int flag = 0; //Whether or not interrupt handler was entered


/*
 * interruptHandler does what it suggests. Once an interrupt is signaled, the fu * nction subtracts the interval of the total time, obtains the current time and * sets the flag to signal it has been entered and lastly prints the current tim * e.
 */

void interruptHandler()
{

  runLength = runLength - interval;
  
  time_t *temp = NULL; //Temporary time to pass to time function
  time_t current = time(temp); //Current Unix based time

  flag = 1;
  
  printf("current time is %s", ctime(&current));

}
 
/*
 * main obtains the parameters and uses them to set up the alarm to go off every * interval 
 *
 * @param argc The number of string parameters passed to the main function
 * @param *argv[] The parameters passed to the main function
 * @return 0 if everything worked, else it didn't
 */

int main(int argc, char *argv[])
{

  if (argc != 3)
    {
      printf( "usage: an interval (in seconds) <int>  a cap of how many total s         econds the program will run for <int>\n");
    }
  
  int sigCheck; //Check the signal
  int alarmCheck; //Check the alarm

  interval = atoi(argv[1]);
  runLength = atoi(argv[2]);

  void(*isr) () = interruptHandler; //Pointer to the function

  struct sigaction sig; //Sigaction structure to pass sa_handler to pointer
  sig.sa_handler = isr;

  sigCheck = sigaction(SIGALRM, &sig, NULL);
  assert(sigCheck > -1);

  alarmCheck = alarm(interval);
  assert(alarmCheck > -1);

  //Run up until the run length paramter and check if interrupt flag has been se  //t for the duration parameter
  while(runLength >= interval)
    {

      if(flag == 1)
	{
	  flag = 0;
	  alarmCheck = alarm(interval);
	  assert(alarmCheck > -1);
	}

    }
  exit(0);
}
