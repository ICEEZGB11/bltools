#ifndef BLTOOLS_H
#define BLTOOLS_H

#include <stdlib.h>
#include <stdio.h>
#include <sstream>

#include "../deps/boost/boost/date_time/date.hpp"
#include "../deps/boost/boost/date_time/posix_time/posix_time.hpp"

#define BLTOOLS_RED 1 << 1
#define BLTOOLS_GREEN 1 << 2
#define BLTOOLS_BLUE 1 << 3
#define BLTOOLS_NATIVE 1 << 4

#ifdef _WIN32
	#include <windows.h>
#endif

namespace bltools
{
	const boost::posix_time::ptime EPOCH(boost::gregorian::date(1970,1,1));
	
	void print(const char* message,int colour=BLTOOLS_NATIVE)
	{
		#ifdef _WIN32
			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			
			if(colour & BLTOOLS_RED)
				SetConsoleTextAttribute(console,FOREGROUND_RED);
			else if(colour & BLTOOLS_GREEN)
				SetConsoleTextAttribute(console,FOREGROUND_GREEN);
			else if(colour & BLTOOLS_BLUE)
				SetConsoleTextAttribute(console,FOREGROUND_BLUE);
			
			printf("%s\n",message);
			SetConsoleTextAttribute(console,0);
		#elif __GNUC__
			if(colour & BLTOOLS_RED)
				printf("%c[%d;%dm%s%c[%dm\n",27,0,31,message,27,0);
			else if(colour & BLTOOLS_GREEN)
				printf("%c[%d;%dm%s%c[%dm\n",27,0,32,message,27,0);
			else if(colour & BLTOOLS_BLUE)
				printf("%c[%d;%dm%s%c[%dm\n",27,0,34,message,27,0);
			else
				printf("%s\n",message);
		#else
			printf("%s\n",message);
		#endif
	}
	void dump(const char* message,int code=0)
	{
		printf("%s\n",message);
		exit(code);
	}
	unsigned long timestamp()
	{
		
		return (boost::posix_time::ptime(boost::posix_time::microsec_clock::universal_time()) - EPOCH).total_milliseconds();
	}
};

#endif
