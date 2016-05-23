// graphNode.hpp

#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include<iostream>
#include<string>
#include<vector>

#include "systemInterface.hpp"


class GraphNode {
public:
    GraphNode( std::string name );
    std::string getName()	{ return _name; }
    void setName( std::string name )	{ _name = name; }
    void setTimestamp(int ts)		{ _timestamp = ts; }
    int getTimestamp()		{ return _timestamp; }
    std::vector<GraphNode *> *dependentNodes()	{ return _listOfDependentNodes; }
    void setCommand(std::string cmnd)	{ _command = cmnd; }
    std::string getCommand()		{ return _command; }
    void runCommand();		// execute the command associated with this node.
    void addDependentNode(GraphNode *child);
    bool onPath()		{ return _onPath; }
    void onPath(bool v)		{ _onPath = v; }
    bool wasMade()		{ return _wasMade; }
    void wasMade(bool v)	{ _wasMade = v; }
    bool isATarget()		{ return _isATarget; }
    void isATarget(bool v)	{ _isATarget = v; }
    int numDependentNodes()	{ return _listOfDependentNodes->size(); }
    void print();

private:
    std::string _name, _command;
    int _timestamp;
    std::vector<GraphNode *> *_listOfDependentNodes;

    bool _onPath, _isATarget, _wasMade;
};

#endif
