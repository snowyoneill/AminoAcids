//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <sys/stat.h>

//#include <stdlib.h>
//#include <stdio.h>
//#include <time.h>

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

extern "C" {
   #include "hr_time.h"
}

#define BENCHMARKING
#define NUM_OF_PASSES 5

int main()
{
	printf("Start...\n");

	#ifdef BENCHMARKING
		printf("Number Of Passes: %d\n\n", NUM_OF_PASSES);

		double aggregatedElapsedTime = 0;
    #endif
	
	stopWatch executionTimer;

	#ifdef BENCHMARKING

		if(initialiseTimer(&executionTimer)!=0)
		{
			printf("Timer failed to initialise.\n");
			getchar();
			exit(EXIT_FAILURE);
		}
		
		for(int j=0; j<NUM_OF_PASSES; j++)
		{
			startTimer(&executionTimer);
	#endif

			ifstream infile;
			infile.open ("FinalGENIE200.ped", ifstream::in);

			string line;
			char c;
			char pair[4];

			FILE* outF = fopen("output.ped", "a");

			if (infile.is_open())
			{
				infile.seekg(15, ios::beg);

				while (!infile.eof())
				{
					getline(infile, line);

					//printf("%s", line);
					infile.get(c);
					if(c == '\n')
						fputs("\n", outF);
					if(c == '0')
						fputs("0,", outF);
					else if(c == 'a' || c == 'c' || c == 'g' || c == 't')
					{
						pair[0] = c;
						//printf("%c", pair[0]);
						infile.get(c);
						if(c == ' ')
						{
							infile.get(c);
							if(c == 'a' || c == 'c' || c == 'g' || c == 't' )
								{
									pair[1] = c;
									pair[2] = ',';
									pair[3] = '\0';
									//printf("%c,", pair[1]);
									fputs(pair, outF);
								}
						}
					}
				}
	
				infile.close();
			}

			fclose (outF);
		
	#ifdef BENCHMARKING

			stopTimer(&executionTimer);
			printf("Elapsed Time: %f(s), %f(ms)\n", getElapsedTime(&executionTimer), getElapsedTimeInMilli(&executionTimer));
			aggregatedElapsedTime += getElapsedTimeInMilli(&executionTimer);

		}

		printf("Average: %f milliseconds\n", (aggregatedElapsedTime/NUM_OF_PASSES));
	#endif

	
	
	printf("End\n");
	getchar();
	exit(EXIT_SUCCESS);
}