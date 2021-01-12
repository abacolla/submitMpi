/*
Albino Bacolla
MDACC - MCO
6767 Bertner Avenue
Houston, TX 77030
Email abacolla@mdanderson.org

November 2018

vga_submitMpiJob.cpp -- utility to submit multiple jobs
*/

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <mpi.h>
#include <ctime>
#include <chrono>

int main(int argc, char* argv[])
{
  using namespace std;
  using namespace std::chrono;
  steady_clock::time_point t1 = steady_clock::now();
  MPI_Init(&argc, &argv);
  int size, rank, name_len;
  MPI_Comm comm;
  comm = MPI_COMM_WORLD;
  MPI_Comm_size(comm, &size);
  MPI_Comm_rank(comm, &rank);
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  MPI_Get_processor_name(processor_name, &name_len);

  stringstream s1, s2;
  s1 << "bash " << argv[1] << rank << ".sh";  // file => argv[1]
  s2 << argv[1] << rank << ".sh";             // file => argv[1]
  system(s1.str().c_str());

  steady_clock::time_point t2 = steady_clock::now();
  duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

  cout << processor_name << " [processor "
       << rank << "/" << size - 1 << "] finished "
       << s2.str() << " in "
       << time_span.count()/60 << " min" << '\n';

  MPI_Finalize();

  return 0;
}
