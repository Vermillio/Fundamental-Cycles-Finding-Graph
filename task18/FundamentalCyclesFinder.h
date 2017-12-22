//Class that finds a set of fundamental cycles of a connected undirected graph given by an incidence table.


#pragma once
#include <vector>
#include <set>
#include "T_Graph.h"

using namespace std;

namespace Graph
{
	struct cycle
	{
		vector<int> c;
	};

	class FundamentalCyclesFinder
	{
		int depth = -1;
		vector<int> used;
		vector<int> ftr;
		set<cycle> *sol;
		T_Graph *gr;
		void Save(int start, int end);
		void findProc(int vnum);
	public:
		void run(T_Graph &G, set<cycle> &fc);
		void demo();
	};
}