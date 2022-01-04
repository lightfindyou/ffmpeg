#ifndef DEBUG_INCLUDED
#define DEBUG_INCLUDED
#include "awn/awn.h"

#define USETS_MEMCPY 1
//Turns on debugging messages
#undef SHOW_DEBUG
#ifndef SHOW_DEBUG
	#define SHOW_DEBUG 0
#endif

#undef SHOW_MSG
#ifndef SHOW_MSG
	#define SHOW_MSG 1
#endif

#undef PRINT_DEBUG_FILE
#ifndef PRINT_DEBUG_FILE
#define PRINT_DEBUG_FILE 1
#endif

#define USE_PKEY 0

#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define PRINT_FD stdout

typedef char* charptr;

/** xzjin 16进制打印内存数据,每行16 byte
 * @mem 内存开始地址
 * @lineNr 打印的行数
*/
void printMem(void* mem, int lineNr);

#define ERROR_IF_PRINT(r, data, elem) if(data == elem) { DEBUG("errno == %s (%i): %s\n", MK_STR(elem), elem, strerror(elem)); }

#define PRINTFUNC fprintf 

#define UNBLOCKABLE_MSG(format, ...) do{PRINTFUNC(PRINT_FD, "\033[01;32mMSG(\e[m\033[01;36mF:%s L:%d\e[m\033[01;33m):\e[m" , __func__ , __LINE__); PRINTFUNC(PRINT_FD,  format, ##__VA_ARGS__); fflush(PRINT_FD); }while(0)

#if SHOW_MSG
	#define MSG(format, ...) do{PRINTFUNC(PRINT_FD, "\033[01;32mMSG(\e[m\033[01;36mF:%s L:%d\e[m\033[01;33m):\e[m" , __func__ , __LINE__); PRINTFUNC(PRINT_FD,  format, ##__VA_ARGS__); fflush(PRINT_FD); }while(0)
#else
	#define MSG(format, ...)
#endif
#define ERROR(format, ...) do{PRINTFUNC(PRINT_FD, "\033[01;31mERROR\e[m (F:%s L:%d): " , __func__ , __LINE__); PRINTFUNC(PRINT_FD,  format, ##__VA_ARGS__); /*_nv_error_count++;*/ }while(0)

#define DEBUG_FD stderr

#if PRINT_DEBUG_FILE
#define DEBUG_FILE(format, ...) do {PRINTFUNC(DEBUG_FD, "DEBUG (F:%s L:%d):" , __func__ ,__LINE__); PRINTFUNC(DEBUG_FD, format, ##__VA_ARGS__); fflush(DEBUG_FD); }while(0)
#else
#define DEBUG_FILE(format, ...) do{}while(0)
#endif

//int _nv_error_count;

#if SHOW_DEBUG
	#define DEBUG(format, ...)   do{PRINTFUNC(PRINT_FD, "\033[01;33mDEBUG (\e[m\033[01;35mF:%s L:%d\e[m\033[01;32m):\e[m", __func__ , __LINE__); PRINTFUNC(PRINT_FD, format, ##__VA_ARGS__); fflush(PRINT_FD); } while(0)
    #define WARNING(format, ...) do{PRINTFUNC(PRINT_FD, "\033[01;36mWARNING (\e[m\033[01;35mF:%s\e[m\033[01;32m):\e[m ", __func__); PRINTFUNC(PRINT_FD, format, ##__VA_ARGS__); } while(0)
	#define DEBUG_P(format, ...) do{PRINTFUNC(PRINT_FD, format, ##__VA_ARGS__); } while(0)
	#define PRINTEXTENT(fEnt) do{PRINTFUNC(PRINT_FD, "F:%s L:%d\toffset:%8lu,\n\tlength:*%8lu,\n\tphysicalPos:%8lu\n",  __func__, __LINE__, ((struct fileExtent *)fEnt)->offset, ((struct fileExtent *)fEnt)->length, ((struct fileExtent *)fEnt)->pysicalPos); } while(0)
#else
	#define DEBUG(format, ...) do{}while(0)
	#define WARNING(format, ...) do{}while(0)
	#define DEBUG_P(format, ...) do{}while(0)
	#define PRINTEXTENT(fEnt) do{} while(0)
#endif


#endif	//DEBUG_INCLUDED