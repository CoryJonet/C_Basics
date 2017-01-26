#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

volatile int interval = 0; //Interval in seconds
volatile int runLength = 0; //Length of program
volatile int timeFlag = 0; //Alarm interrupt flag
volatile int controlCFlag = 0; //Control-c interrupt flag
volatile int modeFlag = 0; //Control-c interrupt flag to switch lower->upper, vi                           //ce versa

/*
 * timeInterruptHandler handles when alarm signals an interrupt by subtracting t * he interval from the total run length, obtaining the current unix time and pr * inting it along with setting the time flag.
 */

void timeInterruptHandler()
{

  runLength = runLength - interval;

  time_t *temp = NULL; //Temporary time_t to pass to time function
  time_t current = time(temp); //Current Unix time

  timeFlag = 1;

  printf("current time is %s", ctime(&current));

}

/*
 * controlCInterruptHandler sets the controlCFlag and switches modes (ie. lower  * to upper or upper to lower.
 */

void controlCInterruptHandler()
{

  controlCFlag = 1;

  if(modeFlag == 1)
    {
      modeFlag = 0;
    }

  else
    {
      modeFlag = 1;
    }

}

/*
 * main function sets up the parameters to set up the alarm and control the prog * ram while waiting for the asynchronous interrupts.
 *
 * @param argc The number of string arguments
 * @param *argv The actual string arguments
 * @return 0 if function completed, else it failed
 */

int main(int argc, char *argv[])
{

  if (argc != 4)
    {
      printf( "usage: an interval (in seconds) <int>  a cap of how many total se        conds the program will run for <int>\n");
    }

  int sigCheck; //Check the alarm signal
  int alarmCheck; //Check the alarm
  int charCheck; //Check char being printed

  size_t length; //Length of the last string parameter
  char *stringArg; //The buffer to place the last string parameter into

  //Obtain the last parameter, allocate memory
  length = strlen(argv[3]);
  assert(length != 0);

  stringArg = malloc(length);
  assert(stringArg != NULL);

  //Copy last parameter into stringArg
  strncpy(stringArg, argv[3], length);
  assert(stringArg != NULL);

  interval = atoi(argv[1]);
  runLength = atoi(argv[2]);
  
  void(*isr) () = timeInterruptHandler; //Function pointer to timeInterrupt...
  void(*isr2) () = controlCInterruptHandler; //Function pointer to controlC...

  struct sigaction sig; //Sig struct to pass sa_handler to pointer
  sig.sa_handler = isr;

  sigCheck = sigaction(SIGALRM, &sig, NULL);
  assert(sigCheck > -1);

  alarmCheck = alarm(interval);
  assert(alarmCheck > -1);

  signal(SIGINT, isr2);

  int n; //Loop iterator
  char character; //Current character being looked at

  //While the run length hasn't been reached
  while(runLength >= interval)
    {

      //If alarm interrupt
      if(timeFlag == 1)
        {
          timeFlag = 0;
          alarmCheck = alarm(interval);
          assert(alarmCheck > -1);  
        }

      //If control-C interrupt
      if(controlCFlag == 1)
	{
	  controlCFlag = 0;

	  //If lower to upper
	  if(modeFlag == 1)
	    {
	      for(n = 0; stringArg[n] != '\0'; n++)
		{
		  character = stringArg[n];
		  charCheck = putchar(toupper(character));
		  assert(charCheck != -1);
		}
	      printf("\n");
	    }

	  //If upper to lower
	  else
	    {
	      for(n = 0; stringArg[n] != '\0'; n++)
                {
                  character = stringArg[n];
                  charCheck = putchar(tolower(character));
		  assert(charCheck != -1);
                }
	      printf("\n");
	    }
	}

      pause(); 
    }

  exit(0);
}
