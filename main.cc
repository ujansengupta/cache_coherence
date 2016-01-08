/*******************************************************
                          main.cc
                  Ahmad Samih & Yan Solihin
                           2009
                {aasamih,solihin}@ece.ncsu.edu
********************************************************/

#include <cstdlib>
#include <assert.h>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

#include "cache.h"

int main(int argc, char *argv[])
{

	if(argv[1] == NULL){
		 printf("input format: ");
		 printf("./smp_cache <cache_size> <assoc> <block_size> <num_processors> <protocol> <trace_file> \n");
		 exit(0);
        }

	/*****uncomment the next five lines*****/
	int cache_size = atoi(argv[1]);
	int cache_assoc= atoi(argv[2]);
	int blk_size   = atoi(argv[3]);
	int num_processors = atoi(argv[4]);/*1, 2, 4, 8*/
	int protocol   = atoi(argv[5]);	 /*0:MSI, 1:MESI, 2:Dragon*/
	char *fname =  (char *)malloc(20);
 	fname = argv[6];
 	char op;

   ifstream fin;
   FILE * pFile;

	    //***************************************************//
    cout<<"===== 506 Personal Information ====="<<endl;
    cout<<"Ujan Sengupta"<<endl;
    cout<<"usengup"<<endl;
    cout<<"NO"<<endl;

	//****************************************************//
	//**printf("===== Simulator configuration =====\n");**//
	//*******print out simulator configuration here*******//
	//****************************************************//
	cout<<"===== 506 SMP Simulator configuration ====="<<endl;
    cout<<"L1_SIZE: "<<cache_size<<endl;
    cout<<"L1_ASSOC: "<<cache_assoc<<endl;
    cout<<"L1_BLOCKSIZE: "<<blk_size<<endl;
    cout<<"NUMBER OF PROCESSORS: "<<num_processors<<endl;
    switch (protocol)
    {
    case 0:
        cout<<"COHERENCE PROTOCOL: MSI"<<endl;
        break;
    case 1:
        cout<<"COHERENCE PROTOCOL: MESI"<<endl;
        break;
    case 2:
        cout<<"COHERENCE PROTOCOL: Dragon"<<endl;
        break;
    }
    cout<<"TRACE FILE: "<<argv[6]<<endl;


	//*********************************************//
        //*****create an array of caches here**********//
	//*********************************************//

	vector <Cache *> vcache;

	for(int i=0; i<num_processors; i++)
    {

        vcache.push_back(new Cache(cache_size,cache_assoc,blk_size));

    }

	pFile = fopen (fname,"r"); //fname

	if(pFile == 0)
	{
		printf("Trace file problem\n");
		exit(0);
	}
	///******************************************************************//
	//**read trace file,line by line,each(processor#,operation,address)**//
	//*****propagate each request down through memory hierarchy**********//
	//*****by calling cachesArray[processor#]->Access(...)***************//
	///******************************************************************//

	fin.open(fname, ios::in); //fname
	string line;

	while (getline(fin,line))
	{
		ulong addr_in_hex;
		int proc;

        proc = line[0] - '0';
        op = line[2];
        string address = line.substr(4);

        if (proc<0 || proc>8)
            break;
            
        istringstream buffer (address);
        buffer >> hex >> addr_in_hex;

        vcache[proc]->Access(addr_in_hex, op, protocol, proc, vcache);
	}

	fclose(pFile);

	//********************************//
	//print out all caches' statistics //
	//********************************//

	for(int i=0; i<num_processors; i++)
    {
        vcache[i]->printStats(i, protocol);
    }

}
