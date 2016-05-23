#include<iostream>
#include<cstdlib>
#include "DepGraph.hpp"

int main(int argc, const char *argv[] ) 
{
    if( argc != 2 ) {
        std::cout << "usage: " << argv[0] << " name-of-a-makefile\n";
        exit(1);
    }
    DepGraph *make = new DepGraph(argv[1]);
    make->parseDepGraph();
    std::cout << "Files affected by cycles: ";
    if( make->isCyclic() )  {
//        std::cerr << "Input graph has cycles.\n";
	std::cout << std::endl;
        exit(1);
    }
    std::cout << "None!" << std::endl;
    make->runMake();
    return 0;
}
