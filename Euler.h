// class declaration for Team Project 10
#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "LinkedGraph.h"
#include "Edge.h"
#include "Vertex.h"
#include LinkedStack.h

//more head files will be added when we need them
using namespace std;

template <class ItemType>
class Euler: public LinkedGraph<ItemType>
{
    template <class ItemType>
  	class EulerEdge
  	{
  	private:
  		ItemType startpoint;
  		Edge<ItemType> edge;
  		bool checked;
  	public:
  		EulerEdge(){ startpoint = 0; edge = 0; checked = 0;}
  		EulerEdge(ItemType start, Edge<ItemType> ed){startLabel = start; edge = ed; checked = false;}
  
  		void setChecked(bool value){ checked = value;  }
  		ItemType getStart()const { return startLabel; }
  		ItemType getEnd() const { return edge.getEndVertex(); }
  		int getWeight() const { return edge.getWeight(); }
  		bool isChecked() const { return checked; }
  
  		bool operator<(const EulerEdge &right)	{	return this->edge.getWeight() < right.getWeight();}
  	};
    private:
    LinkedStack<ItemType> storelink;
    vector<EulerEdge<ItemType>> eulerlist;
    
    public:
    Euler(){}
    ~Euler(){}
    //add elements to the euler list
    void euleradd();
    //remove elements to the euler list
    void eulerremove();
    //This function is used to check if the graph makes a eulerian graph
    bool isEuler();
    // key step, use this to find the path of Fleury’s Algorithm    
    bool isValidNextEdge();
    // Method to check if all non-zero degree vertices are connected
    bool isConnected();
};    
template <class ItemType>    
void Euler::euleradd(EulerEdge<ItemType> a)
{
	eulerlist.insert(a);
}

template <class ItemType>    
void Euler::eulerremove()
{
	EulerEdge<ItemType> tempvec = eulerlist[0];
	eulerlist.erase();
}

template <class ItemType>    
bool Euler::isValidNextEdge() 
    {
      // need to check
      //v is # of vertex
      //u is nodes
      //1) If v is the only adjacent vertex of u
      //2) If there are multiple adjacents, then u-v is not a bridge
    }
    
template <class ItemType>
bool Euler::isEuler()
   {
	// Check if all non-zero degree vertices are connected
	if (isConnected() == false)
		return 0;
		
	// Count vertices with odd degree
	int odd = 0;
	for (int i = 0; i < V; i++)
		if (adj[i].size() & 1)
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
bool Euler::isConnected()
{
	// Mark all the vertices as not visited
	bool visited[eulerlist->getNumVertices()];
	int i;
	for (i = 0; i < eulerlist->getNumVertices(); i++)
		visited[i] = false;

	// Find a vertex with non-zero degree
	for (i = 0; i < eulerlist->getNumVertices(); i++)
		if (eulerlist[i].size() != 0)
			break;

	// If there are no edges in the graph, return true
	if (i == eulerlist->getNumVertices())
		return true;

	// Start DFS traversal from a vertex with non-zero degree
	DFSUtil(i, visited);

	// Check if all non-zero degree vertices are visited
	for (i = 0; i < eulerlist->getNumVertices(); i++)
		if (visited[i] == false && eulerlist[i].size() > 0)
			return false;

	return true;
}
