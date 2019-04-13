//Description: Prototypes for the binary search tree class.

#ifndef TTH_H
#define TTH_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

class TTH{
    public:
        TTH();
        void contains() const;
        bool isEmpty();
        void printTree(ostream & out = cout) const;
        void buildTree(ifstream & input);
    private:
    struct node{
	    node(const string &x, node *l, node *r){
                lines.resize(1, vector<int>(1));
                keys.push_back(x)
                children.push_back(r);
                children.push_back(NULL);
                children.push_back(l);
	    }
	    vector<string> keys;
	    vector<node *> children;
	    vector<vector<int>> lines;
	};
	node * root;
	void insertHelper(const string &X, int line, node *& t, int &distWords);
	bool containsHelper(const string & x, node * t, node* &result) const;
	void printTreeHelper(node *t, ostream & out) const;
	int findHeight(node *t);
};

#endif
