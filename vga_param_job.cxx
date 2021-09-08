
#include <iostream>
#include <mpl/mpl.hpp>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <sstream>

class ReadFile {
  public:
  bool readIt(std::string inFile, std::vector<std::string> &v1) {
    std::ifstream in(inFile.c_str());
    if (!in) {
      std::cerr << "Cannot open file " << inFile << '\n';
      return false;
    }
    std::string s0;
    while (std::getline(in, s0)) {
      if (s0.size() > 0) {
        v1.push_back(s0);
      }
    }
    in.close();
    return true;
  }
};

const std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
const std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();

int main(int argc, char* argv []) {
  const mpl::communicator &comm(mpl::environment::comm_world());
  int rank{comm.rank()}, size{comm.size()}; // size = number of lines in input file
  std::string proc{mpl::environment::processor_name()};
  if ((comm.size() < 2) || (argc != 2)) {
    std::cout << "\nSynopsis: start parallel job reading a parametric file\n"
              << "Usage: vga_param_job <param_file>\n"
              << "Note: number of processors = number of jobs\n"
              << "Use more than 1 processor\n\n"; 
    comm.abort(EXIT_FAILURE);
  }

  const int N{10000};
  char arr[N];
  if (rank == 0) {
    std::vector<std::string> v1;
    char arrS[N];
    ReadFile obj;
    obj.readIt(argv[1], v1);
    std::string s0(v1[0]);
    std::strcpy(arr, s0.c_str());
    
    for (int i = 1; i < size; ++i) { // leave process 0 by itself 
      std::string s(v1[i]);
      std::strcpy(arrS, s.c_str());
      comm.send(arrS, i);
    }
  }

  for (int i = 1; i <= size; ++i) {    
    if (rank == i) {
      comm.recv(arr, 0);
    }
  }
  std::system(arr);
  const auto end = std::chrono::steady_clock::now();
  std::stringstream outMessage;
  outMessage << proc << " [" << rank << "/" << size << "] finished in " 
             << std::chrono::duration_cast<std::chrono::minutes>(end - start).count() << " min\n";
  std::cout << outMessage.str();

  return EXIT_SUCCESS;
}
