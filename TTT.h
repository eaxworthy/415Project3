//Description: Prototypes for the binary search tree class.

#ifndef TTT_H
#define TTT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

class TTT{
    public:
        TTT();
        void contains() const;
        bool isEmpty();
        void printTree(ostream & out = cout) const;
        void buildTree(ifstream & input);
    private:
      struct node{
	       node(const string &x, node *l, node *r){
                key1=x;
                key2="";
                leftchild = l;
                middlechild = NULL;
                rightchild = r;
	       }
	       string key1, key2;
         vector<int> lines1, lines2;
         node* parent, *leftchild, *middlechild, *rightchild;
	   };
	node * root;
	void insertHelper(const string &X, int line, node *& t, node*& p, int &distWords);
	//bool containsHelper(const string & x, node * t, node* &result) const;
	//void printTreeHelper(node *t, ostream & out) const;
	//int findHeight(node *t);
};

#endif
