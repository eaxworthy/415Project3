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
			double bSearchTime = 0.0, tSearchTime = 0.0;
			cout << "Building Two Tree Tree:\n-------------------------\n";
			TTT tTree;
			tTree.buildTree(input);

			input.clear();
			input.seekg( 0, std::ios::beg );

			cout << "\nBuilding Binary Search Tree:\n-------------------------\n";
			BST bTree;
			bTree.buildTree(input);

			input.close();
			input.open("wordList0.txt");
			cout << "\nBeginning Search:\n-------------------------\n";
			double finishTime, startTime;
			while (!input.eof()) {
				string tempLine, tempWord;
				getline(input, tempLine);
				for (int i = 0; i < tempLine.length(); i++) {
					while (tempLine[i] != ' ' && tempLine[i] != '\n' && i < tempLine.length()) {
						tempWord.insert(tempWord.end(), tempLine[i]);
						i++;
					}
					if(!isalnum(tempWord[0]))
						tempWord.erase(0);
					while (tempWord.length() > 0 && !isalnum(tempWord[tempWord.length() - 1]))
						tempWord.resize(tempWord.size() - 1);
					if (tempWord.length() > 0) {
						startTime = clock();
						tTree.silentContains(tempWord);
						finishTime = clock();
						tSearchTime += (finishTime-startTime)/CLOCKS_PER_SEC;
						startTime = clock();
						bTree.silentContains(tempWord);
						finishTime = clock();
						bSearchTime += (finishTime-startTime)/CLOCKS_PER_SEC;
						tempWord.clear();
					}
				}
			}
			cout << "Done!\nTotal Search Times:\n-------------------------\n";
			cout << "Two-Three Tree Times: " << tSearchTime << endl;
			cout << "Binary Search Tree Times: " << bSearchTime << endl;
		}

		else if(choice == 1){
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
