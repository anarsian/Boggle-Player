/*
 * Name: Anish Narsian
 * UID: anarsian
 */

#include "boggleplayer.h"
#include <algorithm>
using namespace std;

/*
 * Clear board helper funct
 * @return void
 */

void BogglePlayer::clearBoard()
{
	rowVal=0;
	colVal=0;
	boardBool=false;
	lexBool=false;
}




BogglePlayer::~BogglePlayer()
{


 for (int i = 0; i < rowVal; ++i) {
        delete [] board[i];
	delete [] visArray[i];
 }
  delete [] board;


  delete [] visArray;


  delete tri;
}


/*
 * This is teh helper function called in isOnBoard
 */

vector<int> BogglePlayer::helper(bool** boolV, string str, int ro, int co, int len)
{
	bool chNext = true; //init 
	int index = 0;

	std::vector<int> vec;
	for(int i=-1; i<= 1; i++) //row loop
	{
	   for(int j=-1; j<=1; j++) //col loop
           {

			chNext = true; //set flag true
			index = 0;
			
			if((i+ro) >= 0 && (i+ro) < rowVal && (j+co) >= 0 && (j+co) < colVal && boolV[i+ro][j+co] != true)
			{
				string s= board[i+ro][j+co];


				for(unsigned int sLen=0; sLen<s.length(); sLen++)
				{
					if(board[i+ro][j+co][sLen] != str[len+sLen]) {

						chNext = false; //set flag to flase


					}

					index++;  //increment
				}


				if(chNext)
				{
					tempVar = len+index;
					boolV[i+ro][j+co] = true;
					
					if((unsigned)tempVar <= str.length())
                                       { 
				
                    			vec = helper(boolV, str, i+ro, j+co, tempVar);
                  		       }


					if(!vec.empty()) {
					   goto label;  //skip out of loop and goto label
 					}
					else {
					  tempVar = len-index; 
        				}


				}
			}
		}
	}
	label:
	vec.push_back(ro*colVal+co); //current pos

	if((unsigned)tempVar == str.length())
		return vec; //vector
	else
	{
		vector<int> newVec;
		return newVec;
	}
}

/*
 * This is the isOnBoard method, it checks if word_to_check
 * is on the board
 */

vector<int> BogglePlayer::isOnBoard(const string& word_to_check)
{
	for(int i=0; i< rowVal; i++) {
	  for(int j=0; j< colVal; j++) {
	    visArray[i][j] = false;
          }
        }


	bool chNext;
	int index; //init


	std::vector<int> vec;
	for(int i=0; i< rowVal; i++)
	{
		for(int j=0; j< colVal; j++)
		{
			index = 0;
			chNext = true; //set flag true

			string s= board[i][j];
			for(unsigned int sLen=0; sLen<s.length(); sLen++)
			{
                                //change flag
				if(board[i][j][sLen] != word_to_check[sLen])
					chNext = false;


				index++; //inc index
			}
			if(chNext)
			{	

				visArray[i][j] = true;
				vec = helper(visArray, word_to_check, i, j, index);
				
                                if(vec.size()!=0)
				{
					std::reverse(vec.begin(), vec.end()); //reverse the string of words
					return vec;
				}
			}
		}
	}
	vec.clear(); //call clear
	return vec;
}



/*
 * This is the buildLexicon method
 * @param: a set containing the word list
 */

void BogglePlayer::buildLexicon(const set<string>& word_list)
{
    //Build trie
	tri = new trie();
	for (set<string>::iterator itr = word_list.begin(); itr != word_list.end(); itr++)
	{
		string str = *itr;

		tri->insert(str);
	}
	lexBool = true;	//bool flag 
}



/*
 * isInLexicon method
 */


bool BogglePlayer::isInLexicon(const string& word)
{
	
	return tri->find(word); //call find
}






/*
 * This is the set Board method,
 * It sets the board based on the parsm
 */

void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** boArray)
{
	rowVal = rows; //set rowVal from class def
	colVal = cols;
	board = new std::string*[rowVal];

  	for(int r=0; r < rowVal; r++) 
	{
                //setting strings
    		this->board[r] = new std::string[colVal];


	}


	visArray = new bool*[rowVal];

  	for(int r=0; r < rowVal; r++) 
	{
    		this->visArray[r] = new bool[colVal];
	}
	for(unsigned int i=0;i<rows;i++) {

	  for(unsigned int j=0;j<cols;j++)
	  {
		board[i][j]=toLowerCase(boArray[i][j]); //change to lowerCase

		visArray[i][j]=false; //set the 2D Arr flags to false
	  }
        }
	boardBool = true; 
}



/*
 * Method to get all the valid words
 */

bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words)
{
	
	if(!boardBool || !lexBool) //checks the flags
	{ 
		return false;
	}
 
	for(int i=0;i< rowVal; i++)
	{
		for(int j=0; j< colVal; j++)
		{
			for(int sLen=0; sLen< rowVal; sLen++) {
			  for(int s=0; s< colVal; s++) {
			     visArray[sLen][s] = false; //set bool 2D arr to false
                          }
                        }
			visArray[i][j] = true; //set bool 2D arr to true
			checkBo(i, j, board[i][j], minimum_word_length, words); //call helper funct 
		}
	}


	for (set<string>::iterator i = words->begin(); i != words->end(); i++)
	{
		string s = *i;
	}
	return true;
}



/*
 * Ths toLowerCase function
 * It converts the string to lower case
 */

string BogglePlayer::toLowerCase(string str)
{
	string str1;
	int len = (int)str.length();
	for(int i=0;i<len;i++)
		str1+=tolower(str[i]);
	return str1;
}


/*
 * checkBoard helper function
 */

void BogglePlayer::checkBo(int ro, int co, string strWor, int min_len, set<string>* words)
{


	triClass* curr;
	for(int i=-1; i<= 1; i++)
	{
		for(int j=-1; j<=1; j++)
		{
			if((i+ro) >= 0 && (i+ro) < rowVal && (j+co) >= 0 && (j+co) < colVal && !visArray[i+ro][j+co] )
			{
				strWor = strWor+board[i+ro][j+co];
                
				curr = tri->helperFunction(strWor);//call helperFunct

				if(curr != 0)
				{
					visArray[i+ro][j+co]=true; //set 2D arr bool flag to true
					checkBo(i+ro, j+co, strWor, min_len, words);
					if(curr->end && strWor.length() >= min_len)
					{	
                                        words->insert(strWor);
                                                //erase wor
                                                strWor.erase(strWor.length()-board[i+ro][j+co].length(), 
                                                                                  board[i+ro][j+co].length());
                                                visArray[i+ro][j+co]=false;
					}
					else
					{
						strWor.erase(strWor.length()-board[i+ro][j+co].length(), 
                                                                                    board[i+ro][j+co].length());
                                                //set 2D arr boolflag to false
						visArray[i+ro][j+co]= false; 
					}
				}
				else
				{
				
        	strWor.erase(strWor.length()-board[i+ro][j+co].length(), board[i+ro][j+co].length());
				}
			}
		}
	}			
}




/*
 * Custom board def for testing
 */

void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols) {}

/*
 * constr
 */

BogglePlayer::BogglePlayer()
{
	rowVal=0;
	colVal=0;
	tempVar=0;
}

