#define _GNU_SOURCE  
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>

static inline int getcpu() {
    #ifdef SYS_getcpu
    int cpu, status;
    status = syscall(SYS_getcpu, &cpu, NULL, NULL);
    return (status == -1) ? status : cpu;
    #else
    return -1; // unavailable
    #endif
}

int main( int argc, char *argv[] ){

  int cpuid,optx;

  cpuid = getcpu();
  if ( argc!=2 ) { printf("You need to provide a command line value\n"); return 1; }
  optx = atoi(argv[1]);
  if ( optx==1 ) {
    printf("cpu id (hardware) for energy measurement = %d\n",cpuid);
  } else if( optx==2 ) {
    printf("cpu id (hardware) for computation = %d\n",cpuid);
  } else {
    printf("You need to provide a command line value of 1 or 2\n"); return 1;
  }
  return 0;
}
