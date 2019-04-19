//Description: Takes a text file supplied by the user
//             and turns it into a word index, implemented
//             through the use of a TTT
//Lizzy Axworthy and Sean Miltenberger

#include <iostream>
#include <fstream>
#include "TTT.h"
#include "BST.h"
using namespace std;

int main(int argc, char* argv[]) {
	int choice;
	if (argc != 2) {
		cout << argc;
		cout << "Incorrect input. Correct format: ./<exectuable.out> <inputtext.txt>\n";
		return 1;
	}

	ifstream input(argv[1]);

	if(input.is_open()){

		cout << "Options: (1) BST, (2) 2-3 Tree, (3) Compare BST and 2-3 Tree\n";
		cin >> choice;
		if(choice == 3){
			cout << "wah\n";
		}
		if(choice == 1){
			BST myTree;
			myTree.buildTree(input);
			while(1){
			choice = 0;
			cout <<"Options: (1) display index, (2) search, (3) save index, (4) quit\n";
			cin >> choice;

			//Print index
				if(choice == 1)
					myTree.printTree(cout);

			//Search index for a word
				else if(choice == 2)
					myTree.contains();

			//Save index
				else if(choice == 3){
					string outputFile;
						cout << "Enter a filename to save your index to (Suggested: <filename>.txt) : ";
						cin >> outputFile;
						ofstream output(outputFile.c_str());
						myTree.printTree(output);
						output.close();
						cout << "Saved\n";
				}

				//Quit
				else
					break;
				}
		}
		else{
			TTT myTree;
			myTree.buildTree(input);
			while(1){
			choice = 0;
			cout <<"Options: (1) display index, (2) search, (3) save index, (4) quit\n";
			cin >> choice;

			//Print index
				if(choice == 1)
					myTree.printTree(cout);

			//Search index for a word
				else if(choice == 2)
					myTree.contains();

			//Save index
				else if(choice == 3){
					string outputFile;
						cout << "Enter a filename to save your index to (Suggested: <filename>.txt) : ";
						cin >> outputFile;
						ofstream output(outputFile.c_str());
						myTree.printTree(output);
						output.close();
						cout << "Saved\n";
				}

				//Quit
				else
					break;
				}
		}
		input.close();


	}

	else{
		cout << "Invalid File Name. Restart Program.\n";
		return 2;
  }

	return 0;
}
