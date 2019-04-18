
//Description: Implementations for the binary search tree class.

#include "TTT.h"
#include "time.h"
#include <iomanip>
#include <sstream>

//Constructor
TTT::TTT(){
    root = NULL;
}

//Returns true if there are no nodes in the tree
bool TTT::isEmpty(){
    return root == NULL;
}

void TTT::printTree(ostream &out) const{
  out << "Two-Three Tree Index:\n-------------------------\n";
  printTreeHelper(root, out);
}
void TTT::printTreeHelper(node *t, ostream &out) const{
  if(t==NULL)
    return;
  /*else{
    printTreeHelper(t->leftchild, out);
    out << setw(30) << std::left;
		out << "K1: "<< t->key1 << " " << t->lines1[0];
		for (int i = 1; i < t->lines1.size(); i++)
			out << ", " << t->lines1[i];
		out << endl;
		printTreeHelper(t->middlechild, out);
    if(t->key2.compare("") != 0){
      out << setw(30) << std::left;
  		out << "K2: " << t->key2 << " " << t->lines2[0];
  		for (int i = 1; i < t->lines2.size(); i++)
  			out << ", " << t->lines2[i];
  		out << endl;
  		printTreeHelper(t->rightchild, out);
    }
	}*/
  cout << t->key1 << " : " << t->key2 << endl;
  cout << "Leftchild\n";
  printTreeHelper(t->leftchild, out);
  cout << "Middlechild\n";
  printTreeHelper(t->middlechild, out);
  cout << "Rightchild\n";
  printTreeHelper(t->rightchild, out);
}

//Receives the specified input file and constructs
//the actual tree. Prints a message when finished.
void TTT::buildTree(ifstream & input){
	int line = 1, numWords = 0, distWords = 0, treeHeight = 0;
	stringstream tempWord;
	double totalTime, finishTime, startTime = clock();
	while (!input.eof()) {
		string tempLine, tempWord;

		//Read a whole line of text from the file
		getline(input, tempLine);
		for (int i = 0; i < tempLine.length(); i++) {
		    //Insert valid chars into tempWord until a delimiter( newline or space) is found
		    while (tempLine[i] != ' '&& tempLine[i] != '\n' && i < tempLine.length() ) {
			      tempWord.insert(tempWord.end(), tempLine[i]);
			       i++;
		    }

        //Trim any punctuation off end of word. Will leave things like apostrophes
        //and decimal points
        while(tempWord.length() > 0 && !isalnum(tempWord[tempWord.length() - 1]))
            tempWord.resize(tempWord.size() -1);

        if (tempWord.length() > 0){
        //Once word is formatted,call insert with the word, the line of the input
        //file it came from, the root of our tree, and the distinct word counter
            node* temp = nullptr;
            insertHelper(tempWord, line, root, temp, distWords);
            //Increment our total number of words inserted
            numWords++;
            //Clear out tempWord so we can use it again
            tempWord.clear();
		    }

		}
		line++;
	}

  /*****
	//Do time and height calculation
	finishTime = clock();
	totalTime = (double) (finishTime - startTime)/CLOCKS_PER_SEC;
	treeHeight = findHeight(root);
	//Print output
	cout << setw(40) << std::left;
	cout << "Total number of words: " << numWords<< endl;
	cout << setw(40) << std::left
	<< "Total number of distinct words: " << distWords << endl;
	cout << setw(40) << std::left
	<<"Total time spent building index: " << totalTime << endl;
	cout << setw(40) << std::left
	<<"Height of TTT is : " << treeHeight << endl;
  *****/
}

//x is the word to insert, line is the line in the text file
//the word was found at, node is the node of the tree being
//examined, and distWord is incremented if a new word is created
//and used by buildTree
void TTT::insertHelper(const string &x, int line, node *& t, node *& p, int &distWord){
    //First Call: Initialize root
    if(t == NULL){
	    t = new node(x, NULL, NULL);
      t->parent = NULL;
	    t->lines1.push_back(line);
	    distWord++;
      cout << "Created node for word " << t->key1;
      cout << " which is found on line " << t->lines1.back() << endl;
      return;
    }

    //Word is not a new distinct word
    if(x.compare(t->key1) == 0){
      t->lines1.push_back(line);
      return;
    }
    else if(x.compare(t->key2) == 0){
      t->lines2.push_back(line);
      return;
    }

    //Word is new distinct word, ie, x will never be key1 or key2
    //TODO: check that second condition isn't messing stuff up
    if(t->leftchild == NULL && t->middlechild == NULL){ //leaf node reached
      if(t->key2 == ""){ //single value in leaf DONE
        if(x.compare(t->key1) < 0){ //x is smaller than first key
          t->key2 = t->key1;
          t->key1 = x;
          t->lines2 = t->lines1;
          t->lines1.clear();
          t->lines1.push_back(line);
          cout<< "swapped " << t->key2 << "with " << x << endl;
          cout << "\nAfter inserting " << x << ":\n";
          printTree();
        }
        else if(x.compare(t->key1) > 0){ //x is larger than first key
          t->key2 = x;
          t->lines2.push_back(line);
          cout << "\nAfter inserting " << x << ":\n";
          printTree();
        }
      }

      else if(t==root){ //a one time case for the third word, when root is a leaf
        string temp = t->key1;
        vector<int> tempLines = t->lines1;
        if(x.compare(t->key1) > 0){
          if(x.compare(t->key2) > 0){ //case: x is largest word
            temp = t->key2;
            tempLines = t->lines2;
            t->lines2.clear();
            t->lines2.push_back(line);
            t->key2 = x;
            cout << t->key1 << ' ' << temp << t->key2 << endl;
          }

          else {   //case x is middle word
            temp = x;
            tempLines.clear();
            tempLines.push_back(line);
          }
        }
        else{ //case: x is smallest word
          t->key1 = x;
          t->lines1.clear();
          t->lines1.push_back(line);
        }

        node* leftChild = new node(t->key1, NULL, NULL);
        leftChild->lines1 = t->lines1;
        leftChild->parent = root;
        node* rightChild = new node(t->key2, NULL, NULL);
        rightChild->lines1 = t->lines2;
        rightChild->parent = root;
        t->key1 = temp;
        t->key2 = "";
        t->leftchild = leftChild;
        t->middlechild = rightChild;
        t->lines1.clear();
        t->lines2.clear();
        t->lines1 = tempLines;
        cout << "\nAfter inserting " << x << ":\n";
        printTree();
      }

      else if(t!= root && t->parent->key2==""){ //need to promote a value and parent has room

        string temp = t->key1;
        vector<int> tempLines = t->lines1;

        //get middle value and it's lines
        if(x.compare(t->key1) > 0){
          if(x.compare(t->key2) > 0){ //case: x is largest word
            temp = t->key2;
            tempLines = t->lines2;
            t->lines2.clear();
            t->lines2.push_back(line);
            t->key2 = x;
          }

          else {   //case x is middle word
            temp = x;
            tempLines.clear();
            tempLines.push_back(line);
          }
        }
        else{ //case: x is smallest word
          t->key1 = x;
          t->lines1.clear();
          t->lines1.push_back(line);
        }

        //find right spot in parent

        //TODO: Check out if it works when promoted values comes from middle child
        if(temp.compare(t->parent->key1) > 0){
          t->parent->key2 = temp;
          t->parent->lines2 = tempLines;
          t->parent->rightchild = new node(t->key2, NULL, NULL);
          t->parent->rightchild->lines1 = t->lines2;
          t->key2 = "";
          t->lines2.clear();
          cout << "\nAfter inserting " << x << ":\n";
          printTree();
        }
        else{ //By now we've determined the value to promote, and that the value is less the the parent's value
          //swap parents key1 and key 2
          t->parent->key2 = t->parent->key1;
          t->parent->lines2 = t->parent->lines1;
          //enter in new value
          t->parent->key1 = temp;
          t->parent->lines1.clear();
          t->parent->lines1 = tempLines;
          //child management;
          t->parent->rightchild = t->parent->middlechild;
          t->parent->middlechild = new node(t->key2, NULL, NULL);
          t->parent->middlechild->lines1 = t->lines2;
          t->key2 = "";
          t->lines2.clear();
          cout << "\nAfter inserting " << x << ":\n";
          printTree();
        }
      }

      else{ //need to promote and no room in parent. The tricky part
        //TODO: Figure out the split to make the initial subtree
        node* s;
        siftUP(t->parent, s);
      }
    }

    //find correct path to go down
    else if(x.compare(t->key1) < 0)
      insertHelper(x, line, t->leftchild, t, distWord);
    else if(t->rightchild == NULL || x.compare(t->key2) < 0)
        insertHelper(x, line, t->middlechild, t, distWord);
    else
        insertHelper(x, line, t->rightchild, t, distWord);

}

//siftUp is a recursive function that travels up the tree looking for a node with
//room to insert into. t is the parent of the last unsuccessful node, and s
//is the root of the subtree that resulted from splitting that node. If t has room,
//s will become on of the two keys in t and it's children will become t's children
//If already two keys in t, we will split t and combine with s to become a new subtree
//and call siftUp with t->parent.
void TTT;siftUP(node*& t, node*& s){
  //best case, there is room in t
  if(t->key2 == ""){

    if(s->key1.compare(t->key1) < 0 ){//if s becomes t->key1{
      //scoot key1, middlechild, and lines2 over to new positions
      t->key2 = t->key1;
      t->lines2 = t-> lines1;
      t->rightchild = t->middlechild;
      //add in s
      t->key1 = s->key1;
      t->lines1 = s->lines1;
      t->leftchild = s->leftchild;
      t->middlechild = s->middlechild;
      //delete s since we allocated it with new and don't need that node anymore
      //TODO: double check we NEED to delete it
      delete s;
    }
    else{//if s becomes t->key2
      t->key2 = s->key1;
      t->middlechild = s->leftchild;
      t->rightchild = s->middlechild;
      delete s;
    }
    return;
  }
  //means that t is the root AND t is full. We split root similar to what we did
  //in insertHelper and create a new root with the middle value from roots keys
  //and the root key of s
  if(t==root){

    if(s->key1.compare(t->key1) < 0){//s formed from leftchild
      //Double checked
      root = new node(t->key1, s, t);
      root->lines1 = t->lines1;
      t->key1 = t->key2;
      t->lines1 = t->lines2;
      t->lines2.clear();
      t->lines2="";
      t->leftchild = t->middlechild;
      t->middlechild = t->rightchild;
      t->rightchild = NULL;
    }
    else{//s formed from middle or right

      if(s->key1.compare(s->key2) < 0){//s formed from middlechild
        //Double checked
        node* newmiddle = new node(t->key2, s->middlechild, t->rightchild);
        newmiddle->lines1 = t->lines2;
        t->key2 = "";
        t->lines2.clear();
        t->middlechild = s->leftchild;
        t->rightchild = NULL;
        root = new node(s->key1, t, newmiddle);
      }

      else{//s formed from rightchild
        //Double Checked
        root = new node(t->key2, t, s);
        root->lines1 = t->lines2;
        t->key2="";
        t->lines2.clear();
        t->lines2="";
        t->rightchild = NULL;
      }
    }
    return;
  }
  //no room in t and t is not root. Find middle value between s root key and t's
  //two keys, find middle value, and have middle value become root of new s, then
  //call siftUp with new values
  else{
    node* temp;
    //leftchild case
    if(s->key1.compare(t->key1) < 0){
      temp = new node(t->key1, s, t);
      temp->lines1=t->lines1;
      t->key1 = t->key2;
      t->lines1 = t->lines2;
      t->key2 = "";
      t->lines2.clear();
      t->leftchild = t->middlechild;
      t->middlechild = t->rightchild;
      t->rightchild = NULL;
    }
    else{
    //middlechild case
      if(s->key1.compare(t->key2) < 0){
        temp = new node(s->key1, t, s);
        temp->lines1=s->lines1;
        t->middlechild = s->leftchild;
        s->key1 = t->key2;
        s->lines1 = t->lines2;
        s->leftchild = s->middlechild;
        s->middlechild = t->rightchild;
        t->key2="";
        t->lines2.clear();
        t->rightchild = NULL;
      }
    //rightchild case
      else{
        temp = new node(t->key2, t, s);
        temp->lines1 = t->lines2;
        t->key2="";
        t->lines2.clear();
        t->rightchild = NULL;
        s = temp;
      }
    }
    siftUp(t->parent, s);
  }
}
