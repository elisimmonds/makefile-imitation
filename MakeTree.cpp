// Eli Simmonds
// CS315 Project 4
// MakeTree.cpp

#include "MakeTree.hpp"
#include "GraphNode.hpp"

MakeTree::MakeTree() {
//	_root = new TreeNode();
}

GraphNode *MakeTree::find( TreeNode *root, std::string name ) {
	if (root == nullptr) { 
		return nullptr;
	}
	if (root->graphNode()->getName() == name)
		return root->graphNode();
	if (root->graphNode()->getName() < name)
		return find(root->right(), name);
	return find(root->left(), name);
}

TreeNode *MakeTree::insert( TreeNode *tNode, GraphNode *nNode ) {
	if ( tNode == nullptr )
		return new TreeNode( nNode );
	if ( tNode->graphNode()->getName() < nNode->getName() )
		tNode->right( insert(tNode->right(), nNode) );
	else
		tNode->left( insert(tNode->left(), nNode) );
	return tNode;
}

void MakeTree::print( TreeNode *root ) {
	if (root == nullptr)
		return;
	print(root->left());
	std::cout << root->graphNode()->getName();
	print(root->right());
}
