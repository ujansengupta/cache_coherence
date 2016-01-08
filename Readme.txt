This project contains a simulator which maintains cache coherence across multiple processors.

Three coherence protocols, namely MSI, MESI and Dragon, are considered.

The cache.cc file contains the functions used for maintaining coherence. THe cache.h header file contains the data structures and function declarations. The main.cc file handles the input to and output from, the simulator.

Please include the makefile in the project directory when compiling. Simply typing 'make' will create an executable by the name smp_cache.

To run this executable, type the following command line input:

./smp_cache <cache_size> <assoc> <block_size> <num_processors> <protocol> <trace_file>

Here, the cache_size refers to the size of the L1 cache_size
		  assoc refers to the associativity
		  block_size refers to the size of the individual cache block/line
		  num_processors refers to the number of processors being considered. Any number of processors can be used.
		  trace_file refers to the traces that shall be input to the simulator. A list of trace files is included in the folder titled Traces.
		  
For the given trace files, the correct outputs are given in the folder titled Validations. Please note the inputs that are considered in the different validations (they're different for each validation run).

A summary and analysis of the simulator can be found in the pdf titled "report".
