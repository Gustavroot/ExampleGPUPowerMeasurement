#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>



#include <time.h>
#include <sys/time.h>
void print_datetime(){
  struct timeval curTime;
  gettimeofday(&curTime, NULL);
  int milli = curTime.tv_usec / 1000;

  char buffer [80];
  strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&curTime.tv_sec));

  char currentTime[84] = "";
  sprintf(currentTime, "%s:%03d", buffer, milli);
  printf("%s", currentTime);

  //time_t t = time(NULL);
  //struct tm tm = *localtime(&t);
  //printf("%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

static inline int getcpu() {
  #ifdef SYS_getcpu
  int cpu, status;
  status = syscall(SYS_getcpu, &cpu, NULL, NULL);
  return (status == -1) ? status : cpu;
  #else
  return -1; // unavailable
  #endif
}

int main(int argc, char** argv) {
  // Initialize the MPI environment
  MPI_Init(&argc, &argv);

  int cpuid,optx;

  // Get the number of processes
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Get the rank of the process
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  print_datetime();

  // Get the name of the processor
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);

  cpuid = getcpu();
  if ( argc!=2 ) { printf("You need to provide a command line value\n"); return 1; }
  optx = atoi(argv[1]);
  if ( optx==1 ) {
    printf(", Hello world from processor %s, rank %d out of %d processors, cpu id (hardware) for energy measurement = %d, ",processor_name, world_rank, world_size,cpuid);
  } else if( optx==2 ) {
    printf(", Hello world from processor %s, rank %d out of %d processors, cpu id (hardware) for computation = %d, ",processor_name, world_rank, world_size,cpuid);
  } else {
    printf("You need to provide a command line value of 1 or 2\n"); return 1;
  }

  print_datetime();
  printf("\n");

  // Finalize the MPI environment.
  MPI_Finalize();
}
