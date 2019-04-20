//Description: Prototypes for the two-three search tree class.

#ifndef TTT_H
#define TTT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

class TTT {
public:
	TTT();
	void contains() const;
	bool silentContains(string &x);
	bool isEmpty();
	void printTree(ostream& out = cout) const;
	void buildTree(ifstream& input);

private:
	struct node {
		node(const string& x, node* l, node* m, node* p) {
			key1 = x;
			key2 = "";
			leftchild = l;
			middlechild = m;
			rightchild = NULL;
			parent = p;
		}
		string key1, key2;
		vector<int> lines1, lines2;
		node* parent, * leftchild, * middlechild, * rightchild;
	};
	node* root;
	int numWords;
	void insertHelper(const string& X, int line, node*& t, node*& p, int& distWords);
	void siftUp(node* t, node* s);
	void containsHelper(const string & x, node * t) const;
	bool silentContainsHelper(const string &x, node* t) const;
	void printTreeHelper(node* t, ostream& out) const;
	void writeWordList(node* t, ostream& out);
	int findHeight(node *t);
public:
	node* nullNode = nullptr;
};

#endif
