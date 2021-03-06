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
class Euler : public LinkedGraph < LabelType >
{
private:
	static void visit(LabelType &);
	static void os(LabelType &);
	LinkedStack<LabelType> *eulerpath;
public:
	//This function is used to check if the graph makes a eulerian graph
	bool isEuler();
	bool isConnected();
	void DFSutil();
	void BFSutil();
	bool nextEdgeOk(LabelType start, LabelType end);
	void printEulerTour();
	void printEulerUtil(Vertex<LabelType> *startVertex);
	bool isValidNextEdge(Vertex<LabelType> *startVertex, Vertex<LabelType> *endVertex);
	void eulerwrite();
};

template <class LabelType>
void Euler<LabelType>::visit(LabelType & label) {}

template <class LabelType>
void Euler<LabelType>::os(LabelType & label)
{
	cout << endl;
	cout << label << endl;
	cout << endl;
	cout << "|" << endl;
	cout << "v" << endl;
	cout << endl;
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

	Vertex<LabelType> * startVertex;
	DACmapIterator<LabelType, Vertex<LabelType>*> * iter = this->vertices.iterator();
	while (iter->hasNext())
	{
		startVertex = iter->next();
		if (startVertex->getNumberOfNeighbors() % 2 == 1)
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
		cout << "There are NO Eulerian paths or circuits available in this graph." << endl;

	return checkEulerian;
}

template <class LabelType>
bool Euler<LabelType>::isConnected()
{
	// If there are no edges in the graph, return false
	if (this->numberOfEdges == 0) return false;

	// Mark all the vertices as not visited
	this->unvisitVertices();

	// Find a vertex with non-zero degree to start the traversal
	Vertex<LabelType> * startVertex = NULL;
	DACmapIterator<LabelType, Vertex<LabelType>*> * iter = this->vertices.iterator();
	while (iter->hasNext()) {
		startVertex = iter->next();
		if (startVertex->getNumberOfNeighbors() > 0) break;
	}

	// Start DFS traversal from a vertex with non-zero degree
	this->depthFirstTraversalHelper(startVertex, visit);

	// Check if all non-zero degree vertices are visited
	Vertex<LabelType> * v;
	iter = this->vertices.iterator();
	while (iter->hasNext()) {
		v = iter->next();
		if (v->getNumberOfNeighbors() > 0 && !v->isVisited()) return false;
	}
	return true;
}

template <class LabelType>
void Euler<LabelType>::DFSutil()
{
	string city;
	cout << "Enter the starting point: ";
	cin >> city;
	this->depthFirstTraversal(city, os);
}

template <class LabelType>
void Euler<LabelType>::BFSutil()
{
	string city;
	cout << "Enter the starting point: ";
	cin >> city;
	this->breadthFirstTraversal(city, os);
}

template <class LabelType>
bool Euler<LabelType>::nextEdgeOk(LabelType start, LabelType end)
{
	Vertex<LabelType> * startVertex = this->findOrCreateVertex(start);
	DACmapIterator<LabelType, Vertex<LabelType>*> * iter = this->vertices.iterator();
	// The edge start-end is valid in one of the following two cases:
	int adjacentCount = startVertex->getNumberOfNeighbors();
	int adjCountRemove = 0;
	//  If v is the only adjacent vertex of u
	if (adjacentCount == 1)
		return true;
	// If there are multiple adjacents, then start-end is not a bridge
	// Do following steps to check if start-end is a bridge

	// count of vertices reachable from start
	// Remove edge (start, end) and after removing the edge
	remove(start, end);
	// count vertices reachable from start
	adjCountRemove = startVertex->getNumberOfNeighbors();
	// Add the edge back to the graph
	add(start, end, 0);
	// If adjacentCount is greater than adjCountRemove, then edge (start, end) is a bridge
	if (adjacentCount > adjCountRemove)
		return true;
}

template <class LabelType>
void Euler<LabelType>::printEulerTour()
{
	// Find a vertex with odd degree
	Vertex<LabelType> * startVertex = NULL;
	DACmapIterator<LabelType, Vertex<LabelType>*> * iter = this->vertices.iterator();
	while (iter->hasNext()) {
		startVertex = iter->next();
		if (startVertex->getNumberOfNeighbors() & 1) break;
	}
	// Print tour starting from oddv
	printEulerUtil(startVertex);
	cout << endl;
}

// Print Euler tour starting from vertex u
template <class LabelType>
void Euler<LabelType>::printEulerUtil(Vertex<LabelType> *startVertex)
{
	// Recur for all the vertices adjacent to this vertex
	Edge<LabelType> edge;
	// use resetNeighbor() to use the adjacency list iterator
	// startVertex->resetNeighbor()
	DACmapIterator<LabelType, Edge<LabelType>> *iter = startVertex->adjacencyList.iterator();
	while (iter->hasNext())
	{
		edge = iter->next();

		Vertex<LabelType> *endVertex = this->findOrCreateVertex(edge.getEndVertex());
		if (nextEdgeOk(startVertex->getLabel(), endVertex->getLabel()))
		{
			cout << startVertex->getLabel() << " ";
			this->remove(startVertex->getLabel(), endVertex->getLabel());
			printEulerUtil(endVertex);
			this->add(startVertex->getLabel(), endVertex->getLabel());
		}
	}
}

template <class LabelType>
void Euler<LabelType>::eulerwrite()
{
	ofstream outFile;
	string outfilename;

	cout << "Name your output file(with file extension): ";
	cin.ignore();
	getline(cin, outfilename);
	outFile.open(outfilename);
	while (!eulerpath->isEmpty())
	{
		outFile >> eulerpath->peek();
		eulerpath->pop();
	}
}
