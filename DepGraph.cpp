// Eli Simmonds
// CS315 Project04
// DepGraph.cpp

#include "DepGraph.hpp"
#include "GraphNode.hpp"

DepGraph::DepGraph( std::string name ) {
	_fileToMake = name;
	_targetToMake = " ";
	firstTarget = nullptr;
	_tree = new MakeTree();
}

void DepGraph::print() {	// just for testing
	_tree->print();	
}

void DepGraph::parseDepGraph() {
	Reader *reader = new Reader(_fileToMake);		// reader created with makefile
	Token token = readAndProcessDependencyPair( reader );	// get first spot
	while ( !token.isEOF() ) {
		token = readAndProcessDependencyPair( reader );	// start building data structures
	}							// and save the current spot into token
}

bool DepGraph::isCyclic() {
	return isCyclic(firstTarget);
}

bool DepGraph::isCyclic( GraphNode *p ) {
	if (p->onPath())	// check initial on path
		return true;
	p->onPath( true );	// set true
	for (int i = 0; i < p->numDependentNodes(); i++) {	// recursively check if its cyclic
		if (isCyclic(p->dependentNodes()->at(i))) {
			std::cout << p->dependentNodes()->at(i)->getName() << ' '; // print cyclic node
			return true; }	// return
	}
	p->onPath( false );	// no dependent nodes have cycles
	return false;		// done
}

void DepGraph::runMake() {
	for (int i = 0; i < firstTarget->numDependentNodes(); i++) {
		runMake(( *(firstTarget->dependentNodes()))[i]);	// run each node
	} 	
	runMake(firstTarget);	// finally compile it all
}

void DepGraph::runMake( GraphNode *p ) {
	bool run = false;
	long time;
	long depTime;
	timestamp(p->getName().c_str(), &time);	// time
	p->setTimestamp(time);			// set timestamp
	for (int i = 0; i < p->numDependentNodes(); i++) {
		timestamp(p->dependentNodes()->at(i)->getName().c_str(), &depTime);	// dependent time
		p->dependentNodes()->at(i)->setTimestamp(depTime);			// set time for dep
		if (depTime > time) {	// does it need to be compiled again?
			run = true;
		}
	}
	if (run) {	// needs to be recompiled
		p->runCommand();
	}
	else if (p->getName() == firstTarget->getName()) {	// all set!
		std::cout << p->getName() << " is up to date" << std::endl;
	}
}

bool DepGraph::timestamp( const char *fname, long *time ) {
	struct stat finfo;	// local timestamp funct.
	
	if (stat( fname, &finfo ) == 0) {
		*time = finfo.st_mtime;
		return true; }
	else if (errno == ENOENT) {
		*time = -1L;
		return true;	}
	else
		return false;
}

Token DepGraph::readAndProcessDependencyPair( Reader *reader ) {
	GraphNode *targetNode;
	GraphNode *dependentNode;

	Token target = reader->getToken();	// get intial token
	if( target.isEOF() ) {	// check if end of file.
		return target;	// crap out
	}

	if( ! target.isName() ) {	// error checking
		std::cout << "The first token of a dependency line should be a name-token.\n";
		exit(1);
	}
	if (_tree->find(target.getName()) == nullptr) {	// check if in list
		targetNode = new GraphNode(target.getName());	// not in list. lets create it
		targetNode->isATarget(true);			// yep its a target
		_tree->insert(targetNode);			// throw it in the tree as makenode
	}
	if (firstTarget == nullptr) {	// is it empty?
		firstTarget = targetNode;	// make it the first node
	}
	else {
		targetNode = _tree->find(target.getName());	// check if it's in the tree and save node
//		targetNode->print();				// print what we found
	}
	Token colon = reader->getToken();
	if( ! colon.isColon() ) {	// error checking makefile
		std::cout << "Missing colon character on the dependency line.\n";
		exit(1);
	}
	// everything is set. time to get dependencies.
	Token token = reader->getToken();
	do {
		if (_tree->find(token.getName()) != nullptr) {	// check if it's in there
				dependentNode = _tree->find(token.getName());	// if its in save
				targetNode->addDependentNode(dependentNode);	// and insert into the vector
			}
			else {
			dependentNode = new GraphNode(token.getName());	// not in there yet
			_tree->insert(dependentNode);			// insert now
			targetNode->addDependentNode(dependentNode);	// add into vector as well
		}
		token = reader->getToken();	// get next name
	} while( token.isName() ) ;

	if( ! token.isEOL() ) {	// error checking
		std::cout << "Dependency line contains a non-name token.\n";
        	exit(1);
	}
	if (targetNode->isATarget()) {	// if its a target then set the timestamp
		targetNode->setTimestamp(-1);
	}	
	Token command = reader->getToken();	// lets get the final line and save to token
	if (command.isEOF())	// check if we're at the end of file
		return command;	// yep let's return the token
	if (!command.isCommand()) {	// error checking
		std::cout << "DepGraph: No Command found" << std::endl;
		exit(1);
	}
	targetNode->setCommand(command.getCommand());	// it's a command. set it to the target. 
	return token;	// return current token
}

