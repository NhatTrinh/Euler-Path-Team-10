// class declaration for Team Project 10
#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "LinkedGraph.h"
#include "Edge.h"
#include "Vertex.h"
#include "LinkedStack.h"

// nhat: double check if the project is supposed to use csv files as input, because i'm not sure it does
// and the stack needs to be double checked also, because it only stores the removed edges that the user specified
//more head files will be added when we need them
using namespace std;

template <class ItemType>
class Euler : public LinkedGraph<ItemType>
{
	template <class ItemType>
	class EulerEdge
	{
	private:
		ItemType startpoint;
		Edge<ItemType> edge;
		bool checked;
	public:
		EulerEdge(){ startpoint = 0; edge = 0; checked = 0; }
		EulerEdge(ItemType start, Edge<ItemType> ed){ startLabel = start; edge = ed; checked = false; }

		void setChecked(bool value){ checked = value; }
		ItemType getStart()const { return startLabel; }
		ItemType getEnd() const { return edge.getEndVertex(); }
		int getWeight() const { return edge.getWeight(); }
		bool isChecked() const { return checked; }

		bool operator<(const EulerEdge &right)	{ return this->edge.getWeight() < right.getWeight(); }
	};
private:
	vectore<EulerEdge<ItemType>> Eulertree;
	// Method to check if all non-zero degree vertices are connected
	bool isConnected();	
	//This function is used to check if the graph makes a eulerian graph
	bool isEuler();
	// key step, use this to find the path of Fleury’s Algorithm    
	bool isValidNextEdge(ItemType a, ItemType b);
public:
	Euler(){}
	~Euler(){}
	bool add(ItemType start, ItemType end, int edgeWeight = 0)
	{
		if (LinkedGraph<ItemType>::add(start, end, edgeWeight))
		{
			Edge<ItemType> edge(end, edgeWeight);
			EulerEdge<ItemType> newEdge(start, edge);
			Eulertree.push_back(newEdge);
			return true;
		}
		return false;
	}
	bool remove(ItemType start, ItemType end)
	{
		vector<EulerEdge<ItemType>>::iterator i;
		for (i = Eulertree.begin(); iterElem != Eulertree.end(); ++iterElem)
		{
			ItemType end1 = i->getStart();
			ItemType end2 = i->getEnd();
			if (start == end1 && end == end2 || start == end2 && end == end1){
				Eulertree.erase(i);
				break;
			}
		}
		return LinkedGraph<LabelType>::remove(start, end);
	}



};

template <class ItemType>
bool Euler<ItemType>::isValidNextEdge(ItemType start, ItemType end)
{
	// The edge u-v is valid in one of the following two cases:

	// 1) If v is the only adjacent vertex of u
	int count = 0;  // To store count of adjacent vertices
	vector<EulerEdge<ItemType>>::iterator i;
	//list<int>::iterator i;
	for (i = eulerlist[start].begin(); i != eulerlist[start].end(); ++i)
		if (*i != -1)
			count++;
	if (count == 1)
		return true;


	// 2) If there are multiple adjacents, then u-v is not a bridge
	// Do following steps to check if u-v is a bridge

	// 2.a) count of vertices reachable from u
	int count1 = EulerTree->getNumVertices();

	// 2.b) Remove edge (u, v) and after removing the edge, count
	// vertices reachable from u
	Eulertree->remove(start, end);

	int count2 = EulerTree->getNumVertices();

	// 2.c) Add the edge back to the graph
	Eulertree->add(start, end);

	// 2.d) If count1 is greater, then edge (u, v) is a bridge
	return (count1 > count2) ? false : true;
}

template <class ItemType>
bool Euler<ItemType>::isEuler()
{
	// Check if all non-zero degree vertices are connected
	if (isConnected() == false)
		return 0;

	// Count vertices with odd degree
	int odd = 0;
	for (int i = 0; i < eulerlist->getNumVertices(); i++)
		if (eulerlist[i].size() & 1)
			odd++;

	// If count is more than 2, then graph is not Eulerian
	if (odd > 2)
		return 0;

	// If odd count is 2, then semi-eulerian.
	// If odd count is 0, then eulerian
	// Note that odd count can never be 1 for undirected graph
	return (odd) ? 1 : 2;
}

template <class ItemType>
bool Euler<ItemType>::isConnected()
{
	// Mark all the vertices as not visited
	bool visited[Eulertree->getNumVertices()];
	int i;
	for (i = 0; i < Eulertree->getNumVertices(); i++)
		visited[i] = false;

	// Find a vertex with non-zero degree
	for (i = 0; i < Eulertree->getNumVertices(); i++)
		if (Eulertree[i].size() != 0)
			break;

	// If there are no edges in the graph, return true
	if (i == Eulertree->getNumVertices())
		return true;

	// Start DFS traversal from a vertex with non-zero degree
	DFSUtil(i, visited);

	// Check if all non-zero degree vertices are visited
	for (i = 0; i < Eulertree->getNumVertices(); i++)
		if (visited[i] == false && Eulertree[i].size() > 0)
			return false;

	return true;
}
