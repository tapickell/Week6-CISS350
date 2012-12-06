#pragma once
#include "Suspect.h"
#include "QueType.h"

typedef Suspect ItemType; //key for tree

struct TreeNode;



enum OrderType {PRE_ORDER, IN_ORDER, POST_ORDER};
class TreeType
{
public:
  TreeType();                     // constructor
 ~TreeType();                    // destructor
  TreeType(const TreeType& originalTree); 
  void operator=(const TreeType& originalTree);
  // copy constructor
  void MakeEmpty();
  bool IsEmpty() const;
  bool IsFull() const;
  int GetLength() const; 
  ItemType GetItem(ItemType item, bool& found);
  
  void PutItem(ItemType item);
  void DeleteItem(ItemType item);
  void ResetTree(OrderType order); 
  ItemType GetNextItem(OrderType order, bool& finished);
  void Print(std::stringstream& outFile) const;
  void findTipInList(std::string stringIN, int &x);
  int getNumNodes();
  std::string getRootName();
 
private:
	int numNodes;
	TreeNode* root;
	QueType preQue;
	QueType inQue;
	QueType postQue;

	void Insert(TreeNode*& tree, ItemType item);
	void Delete(TreeNode*& tree, ItemType item);
	void DeleteNode(TreeNode*& tree);
	void removeSuspects(TreeNode* tree, std::string stringIN, int &x);

};
