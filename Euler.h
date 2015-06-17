// class declaration for Team Project 10
#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <fstream>
#include "LinkedGraph.h"
#include "Edge.h"
#include "Vertex.h"
#include "LinkedStack.h"


using namespace std;

template <class LabelType>
class Euler : public LinkedGraph<LabelType>
{
	// nested class Euler Edge, data to connect one vertice to another
	template <class LabelType>
	class EulerEdge
	{
	private:
		LabelType startpoint;
		Edge<LabelType> edge;
		bool checked;
	public:
		EulerEdge(){ startpoint = 0; edge = 0; checked = 0; }
		EulerEdge(LabelType start, LabelType ed){ startLabel = start; Edge = ed; checked = false; }
		
		void setChecked(bool value){ checked = value; }
		LabelType getStart()const { return startLabel; }
		LabelType getEnd() const { return edge.getEndVertex(); }
		int getWeight() const { return edge.getWeight(); }
		bool isChecked() const { return checked; }

		bool operator<(const EulerEdge &right)	{ return this->edge.getWeight() < right.getWeight(); }
	};

private:
	// Euler Tree
	vector<LabelType> Eulertree;
	// Method to check if all non-zero degree vertices are connected
	bool isConnected();	

	// key step, use this to find the path of Fleury’s Algorithm    
	bool isValidNextEdge(LabelType a, LabelType b);
public:
	Euler(bool openInputFile(ifstream &ifs);
	~Euler(){}
	//This function is used to check if the graph makes a eulerian graph
	bool isEuler();

	bool add(LabelType start, LabelType end, int edgeWeight = 0);
	bool remove(LabelType start, LabelType end);
	bool findEulerPath();
};

// class constructor with infile stream to populate the graph
template <class LabelType>
Euler::Euler(bool openInputFile(ifstream &ifs))
{
	LabelType start;
	LabelType end;
	int edgeWeight = 0;
	
	
}
template <class LabelType>
bool Euler<LabelType>::add(LabelType start, LabelType end, int edgeWeight = 0)
	{
		if (LinkedGraph<LabelType>::add(start, end, edgeWeight))
		{
			Edge<LabelType> edge(end, edgeWeight);
			EulerEdge<LabelType> newEdge(start, edge);
			Eulertree.push_back(newEdge);
			return true;
		}
		return false;
	}
template <class LabelType>	
bool Euler<LabelType>::remove(LabelType start, LabelType end)
{
	vector<EulerEdge<LabelType>>::iterator i;
	for (i = Eulertree.begin(); i != Eulertree.end(); ++i)
	{
		LabelType end1 = i->getStart();
		LabelType end2 = i->getEnd();
		if (start == end1 && end == end2 || start == end2 && end == end1){
			Eulertree.erase(i);
			break;
		}
		return LinkedGraph<LabelType>::remove(start, end);
}


template <class LabelType>
bool Euler<LabelType>::isValidNextEdge(LabelType start, LabelType end)
{
	// The edge u-v is valid in one of the following two cases:

	// 1) If v is the only adjacent vertex of u
	int count = 0;  // To store count of adjacent vertices
	vector<EulerEdge<LabelType>>::iterator i;
	//list<int>::iterator i;
	for (i = Eulertree[start].begin(); i != Eulertree[start].end(); ++i)
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

template <class LabelType>
bool Euler<LabelType>::isEuler()
{
	bool checkEulerian = false;
	// Check if all non-zero degree vertices are connected
	if (isConnected() == false)
		return 0;

	// Count vertices with odd degree
	int odd = 0;
	for (int i = 0; i < Eulertree->getNumVertices(); i++)
	{
		if (Eulertree[i].size() % 2 == 1)
		{
			odd++;
		}
	}

	// If count is more than 2, then graph is not Eulerian
	// If odd count is 2, then semi-eulerian.
	// If odd count is 0, then eulerian
	// Note that odd count can never be 1 for undirected graph
	
	if (odd == 2)
	{
		cout << "There is one (one way or reverse) Eulerian path exists." << endl;
		checkEulerian = true;
	}
	else if (odd == 0)
	{
		cout << "There are Eulerian paths or circuits in this graph." << endl;
		checkEulerian = true;
	}
	else
	{
		cout << "There are NO Eulerian paths or circuits available in this graph." << endl;
	}
	
	return checkEulerian;
}

template <class LabelType>
bool Euler<LabelType>::isConnected()
{
	// Mark all the vertices as not visited
	Eulertree->unvisitVertices();

	// Find a vertex with non-zero degree
	for (i = 0; i < Eulertree->getNumVertices(); i++)
		if (Eulertree[i].size() != 0)
			break;

	// If there are no edges in the graph, return true
	if (i == Eulertree->getNumVertices())
		return true;

	// Start DFS traversal from a vertex with non-zero degree
//	DFSUtil(i, visited);

	// Check if all non-zero degree vertices are visited
	for (i = 0; i < Eulertree->getNumVertices(); i++)
		if (Eulertree[i]->isVisited() == false && Eulertree[i].size() > 0)
			return false;

	return true;
}

bool Euler<LabelType>::findEulerPath()
{
	
}
