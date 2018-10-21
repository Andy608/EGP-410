/*main.cpp
	*
	*	Dean Lawson
	*	Champlain College
	*	2011
	*
	*/
#include <cstdlib>
#include <ctime>
#include <crtdbg.h>

#include <SDL.h>

#include "Game.h"
#include "GameApp.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Defines.h"
#include <Timer.h>
#include <MemoryTracker.h>
#include <PerformanceTracker.h>

#include "PathfindingList.h"
#include "Path.h"

PerformanceTracker* gpPerformanceTracker = NULL;

int main(int argc, char **argv)
{
	gpPerformanceTracker = new PerformanceTracker();

	gpGame = new GameApp();

	gpGame->init();

	bool shouldExit = false;

	while( !shouldExit )
	{
		gpGame->beginLoop();
		gpGame->processLoop();
		shouldExit = gpGame->endLoop();
	}

	//cleanup
	gpGame->cleanup();
	delete gpGame;
	delete gpPerformanceTracker;

	MemoryTracker::getInstance()->reportAllocations( std::cout );

	/*PathfindingList* testList = new PathfindingList();
	Node* n1 = new Node(4);
	Node* n2 = new Node(3);
	Node* n3 = new Node(2);
	Node* n4 = new Node(1);

	Connection* c1 = new Connection(n4, n2, 10);
	Connection* c2 = new Connection(n1, n2, 20);
	Connection* c3 = new Connection(n2, n3, 15);
	Connection* c4 = new Connection(n3, n4, 32);

	NodeRecord r1 = NodeRecord(n1, c1, 0);
	NodeRecord r2 = NodeRecord(n2, c2, 4);
	NodeRecord r3 = NodeRecord(n3, c3, 10);
	NodeRecord r4 = NodeRecord(n4, c4, 18);

	*testList += r1;
	*testList += r2;
	*testList += r3;
	*testList += r4;

	std::cout << "LIST: ";
	testList->print();

	NodeRecord smallest;
	testList->getSmallestElement(smallest);
	std::cout << "SMALLEST: " << std::to_string(smallest.costSoFar) << std::endl;

	bool find = testList->contains(n1);
	std::cout << "CONTAINS: " << std::to_string(find) << std::endl;

	NodeRecord foundNode;
	testList->find(n1, foundNode);
	std::cout << "FOUND NODE: " << std::to_string(foundNode.costSoFar) << std::endl;

	std::vector<NodeRecord> records = testList->mNodeRecords;
	testList->mergeSort(records, 0, testList->size() - 1);

	auto iter = records.begin();

	for (; iter != records.end(); ++iter)
	{
		std::cout << std::to_string((*iter).costSoFar) << " ";
	}

	std::cout << '\n';

	NodeRecord binaryRecord;
	testList->binarySearch(records, 0, testList->size() - 1, n1, binaryRecord);
	
	std::cout << "BINARY SEARCH NODE: " << binaryRecord.costSoFar << std::endl;

	*testList -= foundNode;

	std::cout << "LIST B4 Delete: ";
	testList->print();

	Path* path = new Path();
	NodeRecord temp = r4;
	while (temp.node != r2.node)
	{
		testList->find(temp.connection->getFromNode(), temp);
		path->addNode(temp.node);
	}

	delete testList;

	std::cout << "LIST After Delete: ";
	testList->print();*/

	std::cin.get();
	return 0;
}

