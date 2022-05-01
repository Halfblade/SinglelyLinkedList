////////////////////////////////////////////////////////////////////////////////////////////////
// File :			DTSLab3.cpp
// Author :			Rodney Stoeffler
// Created :		06.03.08
// Last Modified :	01.14.19
// Purpose :		Driver Program for the SLList and SLLIter classes.
// Notes :			Property of Full Sail University, Data Structures Course.
//					DON'T CHANGE THIS FILE. change your code if something is not working
//					Program Output should match the Lab Document
////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////
// LEAK DETECTION
////////////////////////////////////////////////////////////////////////////////////////////////
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

////////////////////////////////////////////////////////////////////////////////////////////////
// INCLUDES
////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
using namespace std;
#include "SLList.h"		// Include the SLList header.

////////////////////////////////////////////////////////////////////////////////////////////
// Function :	printSLList 
// Parameters : list - the Singly Linked List to print
// Return :		void
////////////////////////////////////////////////////////////////////////////////////////////
template <typename Type>
void printSLList(SLList<Type> &list)
{
	cout << "Size: " << list.size() << "\t\tList Contents { ";
	SLLIter<Type> i (list);
	for (i.begin (); !i.end (); ++i)
		cout << i.current () << ' ';
	cout << "}\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Function :	main
// Parameters : argc - the number of command line arguments
//				argv - the array of command line arguments
// Return :		int - 0 for success
////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char ** argv)
{
////////////////////////////////////////////////////////////////////////////////////////////////
// LEAK DETECTION
////////////////////////////////////////////////////////////////////////////////////////////////
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// this function call will set a breakpoint at the location of a leaked block
	// set the parameter to the identifier for a leaked block
	//_CrtSetBreakAlloc();

////////////////////////////////////////////////////////////////////////////////////////////////
// LAB 3
////////////////////////////////////////////////////////////////////////////////////////////////
	cout << "**********************************************************************\n";
	cout << "**                              LAB 3:                              **\n";
	cout << "**********************************************************************\n\n";

	////////////////////////////////////////////////////////////////////////////////////////////
	// Declarations
	////////////////////////////////////////////////////////////////////////////////////////////
	SLList<string> list;
	SLList <string> list2;
	SLList <string> *list3;
	SLLIter<string> iter(list);
	SLList<int> *testPointer;

	////////////////////////////////////////////////////////////////////////////////////////////
	// TEST 1
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "\n*** TEST 1 ***\n";
	cout << "Adding Nodes to the front...\n";
	printSLList(list);
	list.addHead("Rules");
	printSLList(list);
	list.addHead("Sail");
	printSLList(list);
	list.addHead("Full");
	printSLList(list);
	cout << "Now Clearing...\n";
	list.clear();
	printSLList(list);

	////////////////////////////////////////////////////////////////////////////////////////////
	// TEST 2
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "\n*** TEST 2 ***\n";
	cout << "Inserting and removing from the list...\n";
	list.addHead("jerks");
	list.addHead("of");
	list.addHead("full");
	list.addHead("is");
	list.addHead("Six");
	list.addHead("Pod");
	printSLList(list);
	cout << "Removing 'Pod'\n";
	iter.begin();
	list.remove(iter);
	printSLList(list);
	cout << "Removing 'full'\n";
	++iter; ++iter;
	list.remove(iter);
	printSLList(list);
	cout << "Removing 'jerks'\n";
	++iter;
	list.remove(iter);
	printSLList(list);
	cout << "Inserting 'Pod'\n";
	iter.begin();
	list.insert(iter, "Pod");
	printSLList(list);
	cout << "Inserting 'full'\n";
	++iter; ++iter; ++iter;
	list.insert(iter, "full");
	printSLList(list);
	cout << "Removing 'of'\n";
	++iter;
	list.remove(iter);
	printSLList(list);
	list.clear();

	////////////////////////////////////////////////////////////////////////////////////////////
	// TEST 3
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "\n*** TEST 3 ***\n";
	cout << "Using operator=...\n";
	list.addHead("Rules");
	list.addHead("Sail");
	list.addHead("Full");
	SLList<string> copy;
	copy = list;
	printSLList(list);
	printSLList(copy);
	copy.clear();
	list = copy;
	printSLList(list);

	////////////////////////////////////////////////////////////////////////////////////////////
	// TEST 4
	////////////////////////////////////////////////////////////////////////////////////////////
	cout << "\n*** Test 4 ***\n";
	cout << "Stress testing the List (and possibly your trouble shooting)\n";

	////////////////////////////////////////////////////////////////////////////////////////////
	// 4a
	////////////////////////////////////////////////////////////////////////////////////////////
	list.clear();
	list.addHead("is it safe??");
	printSLList(list);
	iter.begin();
	++iter;
	++iter;

	////////////////////////////////////////////////////////////////////////////////////////////
	// 4b
	////////////////////////////////////////////////////////////////////////////////////////////
	list.clear();
	iter.begin();
	list.insert(iter, "shouldn't be here");
	printSLList(list);
	list.clear();
	iter.begin();
	list.remove(iter);
	printSLList(list);

	////////////////////////////////////////////////////////////////////////////////////////////
	// 4c
	////////////////////////////////////////////////////////////////////////////////////////////
	list.clear();
	list3 = &list;
	list.addHead("still here");
	*list3 = list;
	printSLList(*list3);

	////////////////////////////////////////////////////////////////////////////////////////////
	// 4d
	////////////////////////////////////////////////////////////////////////////////////////////
	list.clear();
	list2.clear();
	list.addHead("should be here");
	list2.addHead("shouldn't be here");
	list2 = list;
	printSLList(list2);

	////////////////////////////////////////////////////////////////////////////////////////////
	// 4e
	////////////////////////////////////////////////////////////////////////////////////////////
	testPointer = new SLList<int>;
	for(int x = 0; x < 28; x+=4)
		testPointer->addHead(x);
	SLList<int> testCpyCtr2(*testPointer);
	delete testPointer;
	printSLList(testCpyCtr2);
	testCpyCtr2.clear();
	printSLList(testCpyCtr2);

	////////////////////////////////////////////////////////////////////////////////////////////
	// 4f
	////////////////////////////////////////////////////////////////////////////////////////////
	list.clear();
	list.addHead("bubba");
	iter.begin();
	list.remove(iter);
	printSLList(list);

	////////////////////////////////////////////////////////////////////////////////////////////
	// Complete
	////////////////////////////////////////////////////////////////////////////////////////////
	return 0;
}