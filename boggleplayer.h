/*
 * Name: Anish narsian
 * UID: anarsian
 */

#include <vector>
#include <iomanip>

#include "baseboggleplayer.h"
#include "boggleutil.h"
#include <iostream>

/*
 * This is the .h file for BaseBogglePlayer. 
 * It has the function prototypes and variables
 *
 */

class BogglePlayer : public BaseBogglePlayer
{
	private:
	

        trie *tri;
	bool boardBool;
	bool lexBool;


	string **board;

	bool **visArray;
	int colVal;
	int rowVal;
	int tempVar;
	


        //private helper functions
	void clearBoard();
	string toLowerCase(string s);

       	void checkBo(int a, int b, string wor, int min_len, set<string>* words);

	vector<int> helper(bool **vArr, string str, int ro, int co, int len);
	
	public:
	
	BogglePlayer();
	~BogglePlayer();
	void buildLexicon(const set<string>& word_list);
	void setBoard(unsigned int rows, unsigned int cols, string** diceArray);
	bool getAllValidWords(unsigned int minimum_word_length, set<string>* words);
	bool isInLexicon(const string& word_to_check);
	vector<int> isOnBoard(const string& word_to_check);
	void getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols);
};
