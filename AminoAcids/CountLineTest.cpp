#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <string>
using namespace std;

extern "C" {
   #include "hr_time.h"
}

#define BENCHMARKING
#define NUM_OF_PASSES 10

unsigned int FileRead( istream & is, vector <char> & buff ) {
    is.read( &buff[0], buff.size() );
    return is.gcount();
}

unsigned int CountLines( const vector <char> & buff, int sz ) {
    int newlines = 0;
    const char * p = &buff[0];
    for ( int i = 0; i < sz; i++ ) {
        if ( p[i] == '\n' ) {
                newlines++;
        }
    }
    return newlines;
}

int main( int argc, char * argv[] ) {
    //time_t now = time(0);

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

		  //  if ( argc == 1  ) {
		  //      cout << "lines\n";
		  //      ifstream ifs( "FinalGENIE200.ped" );
				////ifstream ifs( "example.ped" );
		  //      int n = 0;
		  //      string s;
		  //      while( getline( ifs, s ) ) {
		  //              n++;
		  //      }
		  //      cout << n << endl;
		  //  }
		  //  else {
				cout << "buffer\n";
				const int SZ = 512 * 512;
				std::vector <char> buff( SZ );
				ifstream ifs( "FinalGENIE200.ped" );
				//ifstream ifs( "Example.ped" );
				int n = 0;
				while( int cc = FileRead( ifs, buff ) ) {
						n += CountLines( buff, cc );
				}
				//cout << n << endl;
			//}


		#ifdef BENCHMARKING

			stopTimer(&executionTimer);
			printf("Elapsed Time: %f(s), %f(ms)\n", getElapsedTime(&executionTimer), getElapsedTimeInMilli(&executionTimer));
			aggregatedElapsedTime += getElapsedTimeInMilli(&executionTimer);

		}

		printf("Average: %f milliseconds\n", (aggregatedElapsedTime/NUM_OF_PASSES));
	#endif

    //cout << time(0) - now << endl;
	getchar();
	return 0;
}