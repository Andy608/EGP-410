#include "PathfindingList.h"
#include <string>

PathfindingList::~PathfindingList()
{
	mNodeRecords.clear();
}

bool PathfindingList::contains(Node* node)
{
	unsigned int i = 0;
	for (; i < mNodeRecords.size(); ++i)
	{
		if (mNodeRecords.at(i).node == node)
		{
			return true;
		}
	}
	
	return false;
}

bool PathfindingList::find(Node* node, NodeRecord& nodeRecord)
{
	unsigned int i = 0;
	for (; i < mNodeRecords.size(); ++i)
	{
		if (mNodeRecords.at(i).node == node)
		{
			nodeRecord = mNodeRecords.at(i);
			return true;
		}
	}

	std::cout << "There is no NodeRecord with that node in the list!" << std::endl;
	return false;
}

bool PathfindingList::getSmallestElement(NodeRecord& nodeRecord)
{
	if (mNodeRecords.size() > 0)
	{
		nodeRecord = *mNodeRecords.begin();
		return true;
	}
	else
	{
		std::cout << "The pathfinding list is empty!" << std::endl;
		return false;
	}
}

void PathfindingList::operator+=(NodeRecord& recordToAdd)
{
	unsigned int i = 0;
	for (; i < mNodeRecords.size(); ++i)
	{
		NodeRecord& currentRecord = mNodeRecords.at(i);

		if (recordToAdd <= currentRecord)
		{
			//std::cout << "ADDING: " << recordToAdd.costSoFar << " AT INDEX: " << std::to_string(i) << std::endl;
			mNodeRecords.insert(mNodeRecords.begin() + i, recordToAdd);
			return;
		}
	}

	//std::cout << "ADDING: " << recordToAdd.costSoFar << " AT END OF LIST." << std::endl;
	mNodeRecords.push_back(recordToAdd);
}

void PathfindingList::operator-=(NodeRecord& recordToRemove)
{
	unsigned int i = 0;
	for (; i < mNodeRecords.size(); ++i)
	{
		if (mNodeRecords.at(i) == recordToRemove)
		{
			//std::cout << "REMOVING: " << std::to_string(recordToRemove.costSoFar) << std::endl;
			mNodeRecords.erase(mNodeRecords.begin() + i);
			break;
		}
	}
}

void PathfindingList::print()
{
	print(mNodeRecords);
}

void PathfindingList::print(std::vector<NodeRecord> records)
{
	auto iter = records.begin();

	for (; iter != records.end(); ++iter)
	{
		std::cout << std::to_string((*iter).costSoFar) << " ";
	}

	std::cout << '\n';
}
