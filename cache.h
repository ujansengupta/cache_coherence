/*******************************************************
                          cache.h
                  Ahmad Samih & Yan Solihin
                           2009
                {aasamih,solihin}@ece.ncsu.edu
********************************************************/

#ifndef CACHE_H
#define CACHE_H

#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

typedef unsigned long ulong;
typedef unsigned char uchar;
typedef unsigned int uint;

/****add new states, based on the protocol****/
enum{
	INVALID = 0,
	SHARED = 1,
	MODIFIED = 2,
	EXCLUSIVE = 3,
	SHARED_MOD = 4
};

class cacheLine
{
protected:
   ulong tag;
   ulong Flag;   // 0:invalid, 1:valid, 2:dirty
   ulong seq;

public:
   ulong shared_ctr;
   cacheLine()            { tag = 0; Flag = 0; }
   ulong getTag()         { return tag; }
   ulong getFlag()			{ return Flag;}
   ulong getSeq()         { return seq; }
   void setSeq(ulong Seq)			{ seq = Seq;}
   void setFlag(ulong flag)			{  Flag = flag;}
   void setTag(ulong a)   { tag = a; }
   void invalidate()      { tag = 0; Flag = INVALID; shared_ctr=0;}//useful function
   bool isValid()         {return ((Flag) != INVALID);}
};

class Cache
{
protected:
   ulong size, lineSize, assoc, sets, log2Sets, log2Blk, tagMask, numLines;
   ulong reads,readMisses,writes,writeMisses,writeBacks;
   int cache_num;
   ulong mem_trans, interventions, invalidations, flushes, busrdX, cache2cache;

   //******///
   //add coherence counters here///
   //******///

   cacheLine **cache;
   ulong calcTag(ulong addr)     { return (addr >> (log2Blk) );}
   ulong calcIndex(ulong addr)  { return ((addr >> log2Blk) & tagMask);}
   ulong calcAddr4Tag(ulong tag)   { return (tag << (log2Blk));}

public:
    ulong currentCycle;

    Cache(int,int,int);
   ~Cache() {
       cout<<"Calling Destructor for "<<this<<endl;
       delete cache;
       }

   cacheLine *findLineToReplace(ulong addr);
   cacheLine *fillLine(ulong addr);
   cacheLine * findLine(ulong addr);
   cacheLine * getLRU(ulong);

   ulong getRM(){return readMisses;} ulong getWM(){return writeMisses;}
   ulong getReads(){return reads;}ulong getWrites(){return writes;}
   ulong getWB(){return writeBacks;}

   void writeBack(ulong)   {writeBacks++;}
   void Access(ulong,uchar,uint, int, vector <Cache *>&);
   void printStats(int, int);
   void updateLRU(cacheLine *);
   void BusRd(ulong, int, int, int, vector<Cache *>);
   void BusRdX(ulong, int, int, int, vector<Cache *>);
   void BusUpgr(ulong, int, int, int, vector<Cache *>);
   void BusUpdate(ulong, int, int, vector<Cache *>);
   bool copyExists(ulong, int, int, vector <Cache *>);

   //******///
   //add other functions to handle bus transactions///
   //******///

};

#endif

