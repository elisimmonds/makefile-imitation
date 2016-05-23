
#ifndef _TreeNode_hpp
#define _TreeNode_hpp

#include<iostream>
#include<string>
#include "GraphNode.hpp"

class GraphNode;

class TreeNode {
public:
    TreeNode( GraphNode *nNode );

    TreeNode *left()			{ return leftSubtree; }    // getter
    void left( TreeNode *leftPtr )	{ leftSubtree = leftPtr; }     // setter
    TreeNode *right()			{ return rightSubtree; }   // getter
    void right( TreeNode *rightPtr )	{ rightSubtree = rightPtr; }	// setter
    void print();   // print the value of this node
    GraphNode *graphNode()		{ return makeNode; }

private:
    GraphNode *makeNode;
    TreeNode *leftSubtree, *rightSubtree;
};

#endif
