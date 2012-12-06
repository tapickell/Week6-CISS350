#include "stdafx.h"
#include "TreeType.h"



struct TreeNode
{
  ItemType info;
  TreeNode* left;
  TreeNode* right;
};


TreeType::TreeType()
{
  root = NULL;
  numNodes = 0;
}

void Destroy(TreeNode*& tree);

TreeType::~TreeType()
// Calls recursive function Destroy to destroy the tree.
{
  //Destroy(root);
}


bool TreeType::IsFull() const
// Returns true if there is no room for another item 
//  on the free store; false otherwise.
{
  TreeNode* location;
  try
  {
    location = new TreeNode;
    delete location;
    return false;
  }
  catch(std::bad_alloc exception)
  {
    return true;
  }
}

int TreeType::getNumNodes()
{
	return numNodes;
}

bool TreeType::IsEmpty() const
// Returns true if the tree is empty; false otherwise.
{
  return root == NULL;
}

int CountNodes(TreeNode* tree);

int TreeType::GetLength() const
// Calls recursive function CountNodes to count the 
// nodes in the tree.
{
	return CountNodes(root);
}


int CountNodes(TreeNode* tree)
// Post: returns the number of nodes in the tree.
{
	if (tree != NULL)
	{
		if (tree->left == NULL && tree->right == NULL) {
			return 1;
		} else {
			return 1 + CountNodes(tree->right) + CountNodes(tree->left);
		}
	} else {
		return 0;
	}
	/*int nodes = 0;*/
	//if (tree == NULL) {
	//  return 0;
	//} else {
	//	//std::cout << "Left " << CountNodes(tree->left) << " Right " << CountNodes(tree->right) << std::endl;
	//	return 1 + CountNodes(tree->right) + CountNodes(tree->left);//switched left <=> right no fix possible when deleting nodes not setting  NULL
	//	//nodes = 1; //for root node
	//	//if (tree->left) { 
	//	//	nodes += CountNodes(tree->left);  // Access violation reading location not being caught by try / catch block!
	//	//}
	//	////catch (const std::exception &e) {

	//	////}
	//	//if (tree->right) {
	//	//	nodes += CountNodes(tree->right);
	//	//}
	//	////catch (const std::exception &e) {

	//	////}
	//	//return nodes;
	//}
}

void Retrieve(TreeNode* tree, 
     ItemType& item, bool& found);

ItemType TreeType::GetItem(ItemType item, bool& found)
// Calls recursive function Retrieve to search the tree for item.
{
  Retrieve(root, item, found);
  return item;
}


void Retrieve(TreeNode* tree, 
     ItemType& item, bool& found)
// Recursively searches tree for item.
// Post: If there is an element someItem whose key matches item's,
//       found is true and item is set to a copy of someItem; 
//       otherwise found is false and item is unchanged.
{
  if (tree == NULL)
    found = false;                     // item is not found.
  else if (item.getName() < tree->info.getName())      //used for alphabetical sorting of names
    Retrieve(tree->left, item, found); // Search left subtree.
  else if (item.getName() > tree->info.getName())		//used for alphabetical sorting of names
    Retrieve(tree->right, item, found);// Search right subtree.
  else
  {
    item.getName() = tree->info.getName();                 // item is found.
    found = true;
   }
} 



void TreeType::PutItem(ItemType item)
// Calls recursive function Insert to insert item into tree.
{
  Insert(root, item);
}


void TreeType::Insert(TreeNode*& tree, ItemType item)
// Inserts item into tree.
// Post:  item is in tree; search property is maintained.
{
  if (tree == NULL)
  {// Insertion place found.
    tree = new TreeNode;
    tree->right = NULL;
    tree->left = NULL;
    tree->info = item;
	numNodes++;
  }
  else if (item.getName() < tree->info.getName())//used for alphabetical sorting of names
    Insert(tree->left, item);    // Insert in left subtree.
  else
    Insert(tree->right, item);   // Insert in right subtree.
} 




void TreeType::DeleteItem(ItemType item)
// Calls recursive function Delete to delete item from tree.
{
  Delete(root, item);
}


void TreeType::Delete(TreeNode*& tree, ItemType item)
// Deletes item from tree.
// Post:  item is not in tree.
{
  if (item.getName() < tree->info.getName())
    Delete(tree->left, item);   // Look in left subtree.
  else if (item.getName() > tree->info.getName())
    Delete(tree->right, item);  // Look in right subtree.
  else
    DeleteNode(tree);           // Node found; call DeleteNode.
}   

void GetPredecessor(TreeNode* tree, ItemType& data);

void TreeType::DeleteNode(TreeNode*& tree)
// Deletes the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no 
//       longer in the tree.  If tree is a leaf node or has only 
//       non-NULL child pointer the node pointed to by tree is 
//       deleted; otherwise, the user's data is replaced by its 
//       logical predecessor and the predecessor's node is deleted.
{
  ItemType data;
  TreeNode* tempPtr;

 
  tempPtr = tree;
	/*
	personnaly I think alot of my problems with pointers pointing 
	at garbage data stem from this function, it seems like everything 
	is fine till you start deleting stuff, possibly this needs to be 
	setting the left and /or right pointers to NULL if nothing is there.
	But this is the way the book teaches us and I am not sure how to do
	it other wise.  :(
	*/
	// no case for 2 children first??
	if (tree->left == NULL && tree->right == NULL)
	{
		tree = NULL;
	}
	else if (tree->left == NULL)	//one child right??
	{
	tree = tree->right;
	delete tempPtr;
	}
	else if (tree->right == NULL)	//one child left??
	{
	tree = tree->left;
	delete tempPtr;
	}
	else
	{
	GetPredecessor(tree->left, data);
	tree->info = data;
	Delete(tree->left, data);  // Delete predecessor node.
	}
}

void GetPredecessor(TreeNode* tree, ItemType& data)
// Sets data to the info member of the right-most node in tree.
{
	while (tree->right != NULL)//was NULL trying NULL instead
		tree = tree->right;
	data = tree->info;
}

void PrintTree(TreeNode* tree, std::stringstream& outFile) 
// Prints info member of items in tree in sorted order on outFile.
{
  if (tree != NULL)
  {
    PrintTree(tree->left, outFile);   // Print left subtree.
	outFile << tree->info.getName() << std::endl;						
    PrintTree(tree->right, outFile);  // Print right subtree.
  }
}

std::string TreeType::getRootName()
{
	if (root != NULL)
	{
		return root->info.getName();
	} else {
		return "Root is NULL";
	}

}

void TreeType::removeSuspects(TreeNode* tree, std::string stringIN, int &x)
{
	if (tree != NULL)
	{
		std::vector<std::string> attribsToSearch = tree->info.getAttribs();
		bool match = false;
		//iterate through attribs for match
		for (size_t i = 0; i < attribsToSearch.size(); i++)
		{
			if (attribsToSearch[i].compare(stringIN) == 0)	//match
			{
				match = true;
			}
		}
		//if no match afterwards then delete node from local tree
		if (match == false) {
			std::cout << tree->info.getName() << " not a match and should be removed from tree" << std::endl;
			DeleteNode(tree);
			x--;
			removeSuspects(tree, stringIN, x);	//if suspect deleted then spot is replaced by node lower on tree so check this node again
		} else {
			removeSuspects(tree->left, stringIN, x);
			removeSuspects(tree->right, stringIN, x);
		}
	}
}

void TreeType::findTipInList(std::string stringIN, int &x)
{
	removeSuspects(root, stringIN, x);
}

void TreeType::Print(std::stringstream& outFile) const
// Calls recursive function Print to print items in the tree.
{
  PrintTree(root, outFile);
}



void Destroy(TreeNode*& tree)
// Post: tree is empty; nodes have been deallocated.
{
  if (tree != NULL)
  {
    Destroy(tree->left);
    Destroy(tree->right);
    delete tree;
  }
}

void TreeType::MakeEmpty()
{
  Destroy(root);
  root = NULL;
  numNodes = 0;
}


void CopyTree(TreeNode*& copy, 
     const TreeNode* originalTree);

TreeType::TreeType(const TreeType& originalTree)
// Calls recursive function CopyTree to copy originalTree 
//  into root.
{
  CopyTree(root, originalTree.root);
}

void TreeType::operator= 
     (const TreeType& originalTree)
// Calls recursive function CopyTree to copy originalTree 
// into root.
{
  {
  if (&originalTree == this)
    return;             // Ignore assigning self to self
  Destroy(root);      // Deallocate existing tree nodes
  CopyTree(root, originalTree.root);
  numNodes = originalTree.numNodes;//to copy number of nodes over as well
  }

}
void CopyTree(TreeNode*& copy, 
     const TreeNode* originalTree)
// Post: copy is the root of a tree that is a duplicate 
//       of originalTree.
{
  if (originalTree == NULL)
    copy = NULL;
  else
  {
    copy = new TreeNode;
    copy->info = originalTree->info;
    CopyTree(copy->left, originalTree->left);
    CopyTree(copy->right, originalTree->right);
  }
}
// Function prototypes for auxiliary functions.

void PreOrder(TreeNode*, QueType&);
// Enqueues tree items in preorder.


void InOrder(TreeNode*, QueType&);
// Enqueues tree items in inorder.


void PostOrder(TreeNode*, QueType&);
// Enqueues tree items in postorder.


void TreeType::ResetTree(OrderType order)
// Calls function to create a queue of the tree elements in 
// the desired order.
{
  switch (order)
  {
    case PRE_ORDER : PreOrder(root, preQue);
                     break;
    case IN_ORDER  : InOrder(root, inQue);
                     break;
    case POST_ORDER: PostOrder(root, postQue);
                     break;
  }
}


void PreOrder(TreeNode* tree, 
     QueType& preQue)
// Post: preQue contains the tree items in preorder.
{
  if (tree != NULL)
  {
    preQue.Enqueue(tree->info);
    PreOrder(tree->left, preQue);
    PreOrder(tree->right, preQue);
  }
}


void InOrder(TreeNode* tree, 
     QueType& inQue)
// Post: inQue contains the tree items in inorder.
{
  if (tree != NULL)
  {
    InOrder(tree->left, inQue);
    inQue.Enqueue(tree->info);
    InOrder(tree->right, inQue);
  }
}


void PostOrder(TreeNode* tree, 
     QueType& postQue)
// Post: postQue contains the tree items in postorder.
{
  if (tree != NULL)
  {
    PostOrder(tree->left, postQue);
    PostOrder(tree->right, postQue);
    postQue.Enqueue(tree->info);
  }
}


ItemType TreeType::GetNextItem(OrderType order, bool& finished)
// Returns the next item in the desired order.
// Post: For the desired order, item is the next item in the queue.
//       If item is the last one in the queue, finished is true; 
//       otherwise finished is false.
{
  finished = false;
  ItemType item;
  switch (order)
  {
    case PRE_ORDER  : preQue.Dequeue(item);
                      if (preQue.IsEmpty())
                        finished = true;
                      break;
    case IN_ORDER   : inQue.Dequeue(item);
                      if (inQue.IsEmpty())
                        finished = true;
                      break;
    case  POST_ORDER: postQue.Dequeue(item);
                      if (postQue.IsEmpty())
                        finished = true;
                      break;
  }
  return item;
}



