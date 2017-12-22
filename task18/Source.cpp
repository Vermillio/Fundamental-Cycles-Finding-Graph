#include <iostream>
#include "T_Graph.h"
#include "FundamentalCyclesFinder.h"

using namespace Graph;

int main()
{
	T_Graph g;
	FundamentalCyclesFinder finder;
	finder.run(g);
	std::cout << "kek";
	return 0;
}