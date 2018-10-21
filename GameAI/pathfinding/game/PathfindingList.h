#ifndef PATHFINDING_LIST_H_
#define PATHFINDING_LIST_H_

#include <vector>
#include <Trackable.h>
#include "Node.h"
#include "Connection.h"

struct NodeRecord : public Trackable
{
	inline NodeRecord(Node* n = NULL, Connection* c = NULL, float cost = 0.0f, float estimate = 0.0f) :
		node(n), connection(c), costSoFar(cost), estimatedTotalCost(estimate) {};

	Node* node;
	Connection* connection;
	float costSoFar;
	float estimatedTotalCost;

	bool operator==(const NodeRecord& another)
	{
		return (node == another.node && connection == another.connection 
			&& costSoFar == another.costSoFar && estimatedTotalCost == another.estimatedTotalCost);
	}

	bool operator<=(const NodeRecord& another)
	{
		return (costSoFar <= another.costSoFar);
	}
};

class PathfindingList : public Trackable
{
public:
	inline PathfindingList() {};
	~PathfindingList();

	bool contains(Node* node);
	bool PathfindingList::find(Node* node, NodeRecord& nodeRecord);
	bool PathfindingList::getSmallestElement(NodeRecord& nodeRecord);

	void operator+=(NodeRecord& recordToAdd);
	void operator-=(NodeRecord& recordToRemove);

	void print();

	inline const int size() { return mNodeRecords.size(); };

private:
	void print(std::vector<NodeRecord> records);
	std::vector<NodeRecord> mNodeRecords;
};

#endif