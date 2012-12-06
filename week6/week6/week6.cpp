// week6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "fileHandler.h"
#include "TreeType.h"

using namespace std;

void spitout(string);
string userInput(string);
void newCase(TreeType);

int _tmain(int argc, _TCHAR* argv[])
{
	//counter for adds
	int added = 0;
	//Welcome to ...

	fileHandler CrimList("Criminal.mf");
	fileHandler CrimOut("Criminal.trn");
	CrimOut.getFile(); //create new out file

	//save crimlist to a tree
	TreeType criminals = TreeType();
	//for each crim in list add to tree ***** possibly use seperator in file to keep attribs seperate while maintaining spaces ******
	//vector strings to tree 
	vector<string> stringList = CrimList.getFile(); //need error handling if file is empty
	for (size_t i = 0; i < stringList.size(); i++)
	{
		//create suspect
		Suspect tempSuspect = Suspect();
		//add name
		tempSuspect.setName(stringList[i]);
		i++;//increment to attribs
		vector<string> tempAttribs;
		while (stringList[i] != "!")
		{
			//add attribs till you hit a bang
			tempAttribs.push_back(stringList[i]);
			i++; //increment through attribs till hit bang
		}
		tempSuspect.setAttribs(tempAttribs); //add attribs to suspect
		//add suspect to tree
		criminals.PutItem(tempSuspect);
		//should add to tree by alphabetical order of crim name 
		//if not may need to overide < and > in Suspect

	}	//the increment on the for loop will push past the bang after the attribs

	//main menu loop
	bool done = false;
	while (!done)
	{
		spitout("Available menu commands: ADD, INQUIRY, QUIT");
		//get command from user
		string command = userInput("Enter menu command: ");

		if (command == "ADD")
		{
			//if command is add then add new criminal to db
			spitout("Enter Suspect name and attributes. Type DONE when finished");
			bool more = true;
			vector<string> attribs;
			string crimName = userInput("Suspect name: ");
			while (more)
			{
				string attrib = userInput("Suspect attribute: ");
				attrib == "DONE" ? 	more = false : attribs.push_back(attrib);
			}
			//attribs.push_back("!"); //adds stop to attrib list  ***may only be needed when writing back out to file***
			//create new ItemType and add to the tree
			Suspect theSuspect = Suspect();
			theSuspect.setName(crimName);
			theSuspect.setAttribs(attribs);
			criminals.PutItem(theSuspect);
			added++;
			stringstream ss;
			ss << "Suspect " << crimName << " added to database";
			spitout(ss.str());


		} else if (command == "INQUIRY") {
			//if command is inquiry then open new case
			newCase(criminals);

		} else if (command == "QUIT") {
			//if command is quit save crimlist to file if adds and exit program
			if (added > 0)
			{
				//crimlist to vector strings
				vector<string> listOut;
				//iterate through tree adding each Suspect with name, attribs then bang to vector
				bool fin;
				do
				{
					//get next suspect
					criminals.ResetTree(IN_ORDER);
					Suspect toBeAdded = criminals.GetNextItem(IN_ORDER, fin);
					//add name to vector
					listOut.push_back(toBeAdded.getName());
					//add attribs to vector
					vector<string> attribsToAdd = toBeAdded.getAttribs();
					for (size_t i = 0; i < attribsToAdd.size(); i++)
					{
						listOut.push_back(attribsToAdd[i]);
					}
					//add bang to vector
					listOut.push_back("!");

				} while (fin == false);

				//overwrite CrimList file
				CrimList.putFile(listOut);
			}
			done = true;

		} else {
			//bad command input error
			spitout("Error: Bad Command");
		}	
	}
	//Thank you for using...
	spitout("Thank you for using the Cyberdyne Criminal Database System.");
	spitout("The best automated criminal persecution software since August 29, 1997");

	system("pause");
	return 0;
}

void newCase(TreeType treeIN)
{
	//load in from crimlist to a binary search tree
	//each INQUIRY is a new binary search tree built that starts as a copy of the crim list
	TreeType caseTree = treeIN;

	//get inquiry name from user
	string inquiryName = userInput("Name of inquiry: ");

	//check for empty tree
	if (!caseTree.IsEmpty())
	{
		//if only one node left case is solved and closed
		spitout("Available inquiry commands: TIP, CHECK, PRINT");
		//while (caseTree.GetLength() > 1)  would cuase issue acessing invlaid memory on one node left
		int x = caseTree.GetLength();
		cout << "Tree length: " << x << endl;
		while (x > 1)
		{
			//get input from user, whithin inquiry choices are tip, check and print
			string inqCommand = userInput("Enter inquiry command: ");
			if (inqCommand == "TIP")	//every tip added to inquiry removes all nodes that do not match
			{
				//get tip from user 
				bool fin;
				string tip = userInput("Tip: ");
				caseTree.findTipInList(tip, x);// passes x to count down to one node left
				
				//do
				//{
				//	//get next suspect
				//	caseTree.ResetTree(IN_ORDER);
				//	Suspect nextSuspect = caseTree.GetNextItem(IN_ORDER, fin);	
				//	/* 
				//	***** breaks here ********* 
				//	Unhandled exception at at 0x74BCC41F in week6.exe: 
				//	Microsoft C++ exception: EmptyQueue at memory location 0x0030ED57.
				//	*/
				//	//get attribs to search from suspect
				//	vector<string> attribsToSearch = nextSuspect.getAttribs();
				//	bool match = false;
				//	//iterate through attribs for match
				//	for (size_t i = 0; i < attribsToSearch.size(); i++)
				//	{
				//		if (attribsToSearch[i].compare(tip) == 0)	//match
				//		{
				//			match = true;
				//		}
				//	}
				//	//if no match afterwards then delete node from local tree
				//	if (match == false) {
				//		caseTree.DeleteItem(nextSuspect);
				//		x--;
				//	}
				//} while (fin == false);
				//iterate through tree and attemp to match to attribs for each suspect in tree
				//if suspect doesnt have matching attrib remove suspect from local tree

			} else if (inqCommand == "CHECK") {
				//get suspect name from user
				string name = userInput("Name: ");
				Suspect searchName = Suspect();
				searchName.setName(name);
				//search tree for suspect name
				bool found;
				Suspect foundSuspect = caseTree.GetItem(searchName, found);
				//if found print out suspect info
				if (found)
				{
					spitout("Suspect found in list");
					spitout(foundSuspect.toString());
				} else {
					//else print out not found error
					spitout("Suspect not found");
				}
				
			} else if (inqCommand == "PRINT") {
				//print all suspects left in local tree
				stringstream ss;
				ss << "Current list of suspects: " << endl;
				caseTree.Print(ss);
				spitout(ss.str());

			} else {
				//bad command input error
				spitout("Error: Bad Command");
			}
			
		}
		//once the tree has only one node then the case is considered solved
		//inquiryName has been solved!
		

		//ItemTypes info needs to be printed out
		//The Suspect is :
		//bool theEnd;
		/* this crashes VVVV  GetNextItem does something wrong */
		/*caseTree.ResetTree(IN_ORDER);
		Suspect theSuspect = caseTree.GetNextItem(IN_ORDER, theEnd);
		string SuspectName = theSuspect.getName();*/
		if (x ==1) {
			stringstream sss;
			sss << "The " << inquiryName << " case has been solved!";
			spitout(sss.str());
			stringstream ss;
			ss << "The Suspect is : " << caseTree.getRootName();
			//caseTree.Print(ss);
			spitout(ss.str());
		} else {
			spitout("Case Unsolved!!!");
		}

	} else {
		//error out b/c tree is empty
		spitout("Cant search an empty tree!");
	}

}

//spitOUT() method that outputs strings to cout and to fileHandler
void spitout(string strIN)
{
	cout << strIN << endl;
	fileHandler spitFile("Criminal.trn");
	vector<string> output;
	output.push_back(strIN);
	spitFile.appendFile(output);
}

string userInput(string stringIN)
{
	string temp;
	spitout(stringIN);
	getline(cin, temp);
	return temp;
}
