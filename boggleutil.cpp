/*
 * Name: Anish Narsian
 * UID: anarsian
 */
#include "boggleutil.h"
#include <iostream>

  /** Given a reference to a Data item, insert a copy of it in this BST.
   *  Return  true if the item was added to this BST
   *  as a result of this call to insert,
   *  false if an item equal to this one was already in this BST.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items.
   */ // TODO
  void trie::insert(const std::string& item) {
    bool thisRoot=false;
    if(root == 0)
    {
      thisRoot=true;  //set flag true
      root = new triClass(item[0]);
      std::cout << " root data " << root->data << std::endl;

  }
  
    unsigned int i=0; //init index
    if(thisRoot) {
      i++;  //inc i
    }


    triClass *cuRoot = root;  //create root of type triClass
   for(; i<item.length();i++)
  {
	  while(true)
	  {

		  if(cuRoot == 0)
		  {
			  cuRoot = new triClass(item[i]);
			  if(i == (item.length() - 1)) //if index = end then break
				  cuRoot->end = true;
			  
			  
			  break; //break
		  }


		  if(item[i] == cuRoot->data)
		  {
			  if(cuRoot->middle!= 0) { //break if middle child exists
				  cuRoot=cuRoot->middle;

				  break;
			  }
                          //case where same letter got
			  if(item[i] == item[i-1])  { 


				  cuRoot->middle= new triClass(item[i]);

				  if(i == (item.length() - 1)) //if end
					  cuRoot->middle->end=true;
			  }
			  break;
		  }

                  
		  if( cuRoot->middle == 0 && cuRoot->data == item[i-1]) {
			  cuRoot->middle = new triClass(item[i]); //create new node and isnert at mid
			  if(i == (item.length() - 1))
				  cuRoot->middle->end = true; //set flag true
			  cuRoot = cuRoot->middle;


			  break;
		  }
		  else if(item[i] < cuRoot->data) { //move nodes around if data in item less
			  if(cuRoot->left == 0)
			  {
				  cuRoot->left = new triClass(item[i]);
				  if(i == (item.length() - 1))
				  	cuRoot->left->end = true;
				  cuRoot = cuRoot->left;
				  break;

			  }
			  cuRoot=cuRoot->left;
		  }


		  else {
			  if(cuRoot->right == 0)
			  {
				  cuRoot->right = new triClass(item[i]);
				  if(i == (item.length() - 1))
				  	cuRoot->right->end = true;
				  cuRoot = cuRoot->right;


				  break;
			  }


			  cuRoot=cuRoot->right;
		  }
	  }
     }
		
  } 


 /*
  *This is the helper function for the boggleutil class
  */

 triClass* trie::helperFunction(const std::string& item){

   if(root == 0) {return root;}
   triClass* cuRoot=root;
  
   
   for(unsigned int i=0;i<item.length();i++)
  {
  	while(true) //Iterate till it reaches a null, ie end
  	{
		if(cuRoot == 0) {return cuRoot;}
		if(item[i] < cuRoot->data) //if data less then change cuNode ptr
		{


			cuRoot=cuRoot->left;
		}
		else if(cuRoot->data < item[i]) //if data less then change cuNode ptr to right
		{


			cuRoot= cuRoot->right;
		}
		else
		{


			if(i != item.length()-1)
			cuRoot= cuRoot->middle;
			break;
		}
  	}
  }


  return cuRoot;
 }



  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or pointing past
   *  the last node in the BST if not found.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items.
   */ // TODO
  bool trie::find(const std::string& item){
  if(root == 0) {


    return false; //if no tree
  }
  triClass* cuRoot=root;
  for(unsigned int i=0;i<item.length();i++)
  {
  	while(true) //Infinite loop
  	{
		if(cuRoot == 0)
			return false;
		if(item[i] < cuRoot->data) { //change around nodes


			cuRoot=cuRoot->left;
		}


		else if(cuRoot->data < item[i]) { 


			cuRoot= cuRoot->right;
		}

		else { //last case
			if(i == (item.length() -1) && cuRoot->end == true) return true;
			cuRoot= cuRoot->middle; //change cuRoot to pt to middle
			break; 
		}
  	}
  }
  return false; //return false if not found 
 }



 
