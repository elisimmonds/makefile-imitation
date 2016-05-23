// Eli Simmonds
// CS315 Project04
// GraphNode.cpp

#include "GraphNode.hpp"

GraphNode::GraphNode ( std::string name ) {
	setName( name );	// set name, initialize variables
	_command = " ";	
	_timestamp = 0;
	_onPath = _isATarget = _wasMade = false;
	_listOfDependentNodes = new std::vector<GraphNode *>;
}

void GraphNode::addDependentNode( GraphNode *child ) {
	_listOfDependentNodes->push_back( child );	// add dependency
}

void GraphNode::runCommand() {
// run the function executeCommand() from systemInterface.hpp
	executeCommand(_command.c_str());
}

void GraphNode::print() {	// just for testing
//	std::cout << _name << " dependencies: " << std::endl;
	for (unsigned int i = 0; i < _listOfDependentNodes->size(); i++) {
		std::cout << "name: " << _listOfDependentNodes->at(i)->getName() << std::endl;
		std::cout << "timeStamp: " << _listOfDependentNodes->at(i)->getTimestamp() << std::endl;
		std::cout << "command: " << _listOfDependentNodes->at(i)->getCommand() << std::endl;
	}
}
