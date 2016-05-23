
#ifndef _DepGraph_hpp
#define _DepGraph_hpp

#include<iostream>
#include<stdio.h>
#include<cstring>
#include<sys/stat.h>
#include<sys/types.h>
#include<cstdlib>

#include "MakeTree.hpp"
#include "Token.hpp"
#include "Reader.hpp"
#include "systemInterface.hpp"

class GraphNode;

class DepGraph {
public:
    DepGraph( std::string name );
    void print();
    void parseDepGraph();
    void runMake();
    bool isCyclic();
    bool timestamp( const char *fname, long *time );

private:
    Token readAndProcessDependencyPair( Reader * );
    bool isCyclic(GraphNode *);
    void runMake( GraphNode *p );

private:
    std::string _fileToMake, _targetToMake;
    GraphNode *firstTarget;
    MakeTree *_tree;
};

#endif
