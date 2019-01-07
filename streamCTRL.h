
/**
 * @file streamCTRL.h
 * @brief Data streams control panel
 * 
 * Manages data streams
 * 
 * 
 */

#ifndef _STREAMCTRL_H
#define _STREAMCTRL_H


/* =============================================================================================== */
/* =============================================================================================== */
/*                                        HEADER FILES                                             */
/* =============================================================================================== */
/* =============================================================================================== */


// #include <string.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <sys/file.h>
// #include <malloc.h>
// #include <sys/mman.h> // mmap()

// #include <time.h>
// #include <signal.h>

#include <stdint.h>    // int_fast8_t
#include <unistd.h>    // getpid()
// #include <sys/types.h>

// #include <sys/stat.h>
// #include <sys/types.h>


// #include <ncurses.h>
// #include <fcntl.h> 
// #include <ctype.h>

// #include <dirent.h>

// #include <wchar.h>
// #include <locale.h>
// #include <errno.h>

// #include <pthread.h>

/* =============================================================================================== */
/* =============================================================================================== */
/*                                      DEFINES, MACROS                                            */
/* =============================================================================================== */
/* =============================================================================================== */

#define STRINGLENMAX  32

#define streamNBID_MAX 10000
#define streamOpenNBpid_MAX 100
#define nameNBchar 100
#define PIDnameStringLen 12



/* =============================================================================================== */
/* =============================================================================================== */
/*                                  GLOBAL DATA DECLARATION                                        */
/* =============================================================================================== */
/* =============================================================================================== */



typedef struct
{
	char sname[nameNBchar];      // stream name

    long ID;
    
    int SymLink;
    char linkname[nameNBchar];   // if stream is sym link, resolve link name

    pid_t streamOpenPID[streamOpenNBpid_MAX];
    int streamOpenPID_cnt;
    int streamOpenPID_cnt1;                       // number of processes accessing stream
    int streamOpenPID_status;

    int atype;

    double updatevalue; // higher value = more actively recent updates [Hz]
    double updatevalue_frozen;

    long long cnt0; // used to check if cnt0 has changed
    long deltacnt0;
	
} STREAMINFO;



typedef struct
{
	int twaitus; // sleep time between scans
	double dtscan; // measured time interval between scans [s]
		
	int loop;   // 1 : loop     0 : exit
	long loopcnt;
	
	int filter;           // 1 if applying filter to name
	char namefilter[STRINGLENMAX];
	
	STREAMINFO *sinfo;
	long NBstream;
	int fuserUpdate;
	int fuserUpdate0;
	int sindexscan;
	char **PIDtable; // stores names of PIDs
	
} STREAMINFOPROC;






/* =============================================================================================== */
/* =============================================================================================== */
/*                                    FUNCTIONS SOURCE CODE                                        */
/* =============================================================================================== */
/* =============================================================================================== */




#ifdef __cplusplus
extern "C" {
#endif



/**
 * INITIALIZE ncurses
 *
 */
static int initncurses();

int get_process_name_by_pid(const int pid, char *pname);

int streamCTRL_CatchSignals();

static int get_PIDmax();

void *streamCTRL_scan(void* thptr);

/**
 * ## Purpose
 *
 * Control screen for stream structures
 *
 * ## Description
 *
 * Relies on ncurses for display\n
 *
 *
 */

int_fast8_t streamCTRL_CTRLscreen();

#ifdef __cplusplus
}
#endif

#endif // _STREAMCTRL_H
