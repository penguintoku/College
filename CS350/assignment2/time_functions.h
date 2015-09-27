#ifdef time_fns
#else
#define time_fns
#include <sys/timeb.h>
#include <time.h>

struct timeb timestruct;
// following 4 interfaces are "exposed" for user access
void start_timing();
void stop_timing();
double get_wall_clock_diff();
double get_CPU_time_diff();

// following variables are "private" to the functions in this header file

time_t cs350_timer__time1, cs350_timer__time2;
unsigned short cs350_timer__millitm1, cs350_timer__millitm2;
double cs350_timer__C1,cs350_timer__C2;  // for use by the clock fcn 
double cs350_timer__CPU_start, cs350_timer__CPU_end; // for Linux "times" and wintime

//following interfaces are for internal use by above functions //(can't hide them in C, need to use C++ for that and
// don't want to use C++ because most users will not be using C++)
void get_wall_clock(time_t *secs, unsigned short *mils);

long get_CPU_time();

void start_timing()  // get start values for wallclock and CPU time
{get_wall_clock(&cs350_timer__time1, &cs350_timer__millitm1);
  cs350_timer__CPU_start=get_CPU_time();
}

void stop_timing()	 // get final values for wallclock and CPU time
{get_wall_clock(&cs350_timer__time2, &cs350_timer__millitm2);
  cs350_timer__CPU_end=get_CPU_time();
}

double get_wall_clock_diff()
	{// same for Windows and Linux (uses ftime)
	double fnlt1, fnlt2, realfnl;
	fnlt1= (double) cs350_timer__time1+(double)cs350_timer__millitm1/1000;
	fnlt2= (double) cs350_timer__time2+(double)cs350_timer__millitm2/1000;
	realfnl= (fnlt2-fnlt1); // following values are correctly displayed
	return realfnl;
	}

#ifndef WIN32
double get_CPU_time_diff()  
	// CPU time for Linux
        {double diff; 
	diff= (cs350_timer__CPU_end-cs350_timer__CPU_start);
	//printf("Linux cputime diff=%10.3f, diff/1k=%10.3f \n",diff, diff/1000);
        return diff/1000;
        }
#else
double get_CPU_time_diff()
	{//CPU time for Windows
		long TENMEG=10000000;
		return(double)(cs350_timer__CPU_end-cs350_timer__CPU_start)/TENMEG;
	}
#endif

 void get_wall_clock(time_t *secs, unsigned short *mils)
 {	// wall clock time in all systems
	ftime(&timestruct);
	*secs=timestruct.time;
	*mils=timestruct.millitm;

 }
#ifndef WIN32
#include <sys/times.h>
#include <unistd.h>
 long get_CPU_time()  // integer # of clock_ticks converted into mils
 {struct  tms tmsbuf;	clock_t x0;double x1, clock_ticks_per_sec;
	//sysconf() gives # CLOCKS_PER_SEC on Linux
	clock_ticks_per_sec=sysconf(_SC_CLK_TCK);
	times(&tmsbuf); // clock_t units, Linux only.wx
	x0=tmsbuf.tms_utime;
	 //must div by clock_ticks_per_sec to get milliseconds
	x1=(double)x0;
	x1=1000*(x1/clock_ticks_per_sec); // x0 and x1 are OK
	return (long)x1; // long returns whole seconds only, but need the mils
 }
#else 
 #include <windows.h>
 long get_CPU_time()
 {int passed;DWORD my_PID;//int junk;
	HANDLE my_Phandle; //long errnum;
	FILETIME CreationTime, ExitTime, KernelTime, UserTime;
	// pointers to above */
	LPFILETIME lpCreationTime, lpExitTime, lpKernelTime, lpUserTime;
	lpCreationTime=&CreationTime; lpExitTime=&ExitTime; 
	lpKernelTime=&KernelTime; lpUserTime=&UserTime;
		
	my_PID=GetCurrentProcessId(); /* get the true Process Handle with all privileges */
	my_Phandle=OpenProcess(PROCESS_ALL_ACCESS,TRUE,my_PID);
	//if (my_Phandle==NULL){cout<<"handle error";return 1;}

	/* ----------------- get all 4 times ----------- */
	passed=GetProcessTimes(my_Phandle, 
		 lpCreationTime, lpExitTime, lpKernelTime, lpUserTime);// all outputs are FILETIME structures
	/* next line dies, so don't use it */
	//passed=QueryProcessCycleTime(my_Phandle, __out pcycles1); // this call gets a "write to 0" failure
	if (!passed) {/*cout<<"failed with code="<<GetLastError(); */return -1;}
	// following 2 lines are for debugging
	//cout<<"USER:highpart="<<UserTime.dwHighDateTime<<"   lowpart="<<UserTime.dwLowDateTime<<endl;
	//cout<<"KRNL:highpart="<<KernelTime.dwHighDateTime<<"   lowpart="<<KernelTime.dwLowDateTime<<endl;
	
	/* ----------------- now convert filetime to usable time ---------------------- */
	/*	Type SYSTEMTIME:
			  wYear As Integer
			  wMonth As Integer
			  wDayOfWeek As Integer
			  wDay As Integer
			  wHour As Integer
			  wMinute As Integer
			  wSecond As Integer
			  wMilliseconds As Integer
		End Type
	  */

	/*
	typedef struct _FILETIME 
	{  DWORD dwLowDateTime;  DWORD dwHighDateTime;
	} FILETIME,  *PFILETIME;

	typedef union _LARGE_INTEGER 
	{	struct 
			{DWORD LowPart; LONG HighPart; };  
		struct 
			{DWORD LowPart; LONG HighPart; } u;
		LONGLONG QuadPart;
	} LARGE_INTEGER,  *PLARGE_INTEGER;

	*/
	SYSTEMTIME systime; SYSTEMTIME* lpsystime; // not currently used
	ULARGE_INTEGER outtime;                     //not currently used
	//lpsystime= &systime;
	//FileTimeToSystemTime(lpKernelTime,lpsystime); /* now can do math on the parts */
	//cout<<systime.wMonth<<" "<<systime.wDay<<" "<<systime.wHour<<" "<<systime.wMinute<<" "<<systime.wSecond<<" "<<systime.wMilliseconds<<endl;;
	return UserTime.dwLowDateTime;  // give back the milliseconds since process started.
	/*It is not recommended that you add and subtract values from the SYSTEMTIME structure to 
	  obtain relative times. Instead, you should:

			1. Convert the SYSTEMTIME structure to a FILETIME structure. 
			2. Copy the resulting FILETIME structure to a ULARGE_INTEGER structure. 
			3. Use normal 64-bit arithmetic on the ULARGE_INTEGER value. 
*/

/*	It is not recommended that you add and subtract values from the FILETIME structure 
    to obtain relative times. Instead, you should:
	1. copy the low- and high-order parts of the file time to a LARGE_INTEGER structure, 
	2. perform 64-bit arithmetic on the QuadPart member, 
	3. copy the LowPart and HighPart members into the FILETIME structure.
*/

 }
#endif
#endif


