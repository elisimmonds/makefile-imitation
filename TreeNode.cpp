// Eli Simmonds
// CS315 Project05
// TreeNode.cpp

#include "TreeNode.hpp"

TreeNode::TreeNode ( GraphNode *nNode ) {
	makeNode = nNode;
	leftSubtree = rightSubtree = nullptr;
}

void TreeNode::print() {
//	leftSubtree->print();
	graphNode()->print();
//	rightSubtree->print();
}
