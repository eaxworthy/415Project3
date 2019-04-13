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
    if(t == NULL){
	    t = new node(x, NULL, NULL);
      t->parent = NULL;
	    t->lines1.push_back(line);
	    distWord++;
      cout << "Created node for word " << t->key1;
      cout << "Which is found on line " << t->lines1.back();
    }
    else {

    }
  }
