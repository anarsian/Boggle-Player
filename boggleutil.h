/*
 * Name: Anish Narsian
 * UID: anarsian
 */

#ifndef BOGGLEUTIL_HPP
#define BOGGLEUTIL_HPP
#include <iostream>
#include <iomanip>


class triClass {

public:

  /** Constructor to create TriClass
   */
  triClass(const char & d) : data(d) {
    left = right = middle = 0;
    end = false;
  }

  triClass* middle;
  char const data;   
  bool end;

  triClass* left;
  triClass* right;
  
};

class trie
{

	public:
	triClass* root;
	trie(): root(0){
	}
	~trie()
	{
		delete root;
	}
        bool find(const std::string& item);
	triClass* helperFunction(const std::string& item);

	void insert(const std::string& item);

};


#endif // BSTNODE_HP
