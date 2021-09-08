# submitMpi
Synopsis: Submit bash files in a parallel environment

Usage: vga_submitMpiJob prefix_bash_files

Example: mpirun vga_submitMpiJob drdna_

Notes: drdna_ is the prefix of bash files named drdna_0.sh, drdna_1.sh, ... drdna_30.sh (see the nonB-DNA repository)
vga_submitMpiJob is a c++ utility with MPI directives used to submit jobs in a parallel environment across multiple nodes. It expects a positional parameter corresponding to the prefix of a numbber of bash files that are distinguished only by their count number.

Compile: Makefile provides the tool to compile vga_submitMpiJob.cpp, simply type "make". This will generate a directory named "build" containing the binary. You will need to preload the MPI modules before you compile and also before you launch the program. 

## vga_param_job

Synopsis: Start a parallel job reading from a parametric file

Usage: vga_param_job <param_file>

Note: The parametric file contains an n number of lines, each executing a command or an executable file. The number of lines n = number of processors to request. The script uses MPL directives: see  https://github.com/rabauke/mpl

``` r
#include <mpl/mpl.hpp>
```
