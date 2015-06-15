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
  
  		bool operator<(const EulerEdge &right)	{return this->edge.getWeight() < right.getWeight();}
  	};
    private:
    LinkedStack<ItemType> storelink;
    vector<EulerEdge<ItemType>> eulerlist;
    int removecount;
    public:
    Euler(){removecount = 0;}
    ~Euler(){}
    //add elements to the euler list
    void euleradd();
    //remove elements to the euler list
    void eulerremove();
    //recover elements to the euler list
    void eulerrecover();
    //This function is used to check if the graph makes a eulerian graph
    bool isEuler();
    // key step, use this to find the path of Fleury’s Algorithm    
    bool isValidNextEdge();
    // Method to check if all non-zero degree vertices are connected
    bool isConnected();
    // Function to do DFS starting from v. Used in isConnected();
    void DFSUtil(int v,bool visited[]);
      // Methods to print Eulerian tour
  void printEulerTour();
  void printEulerUtil(int s);
  
};    
/* The main function that print Eulerian Trail. It first finds an odd
   degree vertex (if there is any) and then calls printEulerUtil()
   to print the path */
void Graph::printEulerTour()
{
  // Find a vertex with odd degree
  int u = 0;
  for (int i = 0; i < eulerlist->getNumVertices(); i++)
      if (eulerlist[i].size() & 1)
        {   u = i; break;  }
 
  // Print tour starting from oddv
  printEulerUtil(u);
  cout << endl;
}

// Print Euler tour starting from vertex u
void Graph::printEulerUtil(int u)
{
  // Recur for all the vertices adjacent to this vertex
  list<int>::iterator i;
  for (i = eulerlist[u].begin(); i != eulerlist[u].end(); ++i)
  {
      int v = *i;
 
      // If edge u-v is not removed and it's a a valid next edge
      if (v != -1 && isValidNextEdge(u, v))
      {
          cout << u << "-" << v << "  ";
          rmvEdge(u, v);
          printEulerUtil(v);
      }
  }
}
template <class ItemType>    
void Euler::euleradd(EulerEdge<ItemType> a)
{
	eulerlist.insert(a);
}

template <class ItemType>    
void Euler::eulerrecover()
{
	eulerlist.inster(storelink->peek());
	storelink->pop();
	removecount--;
}

template <class ItemType>    
void Euler::eulerremove()
{
	EulerEdge<ItemType> tempvec = eulerlist[removecount];
	storelink -> push(tempvec);
	eulerlist.erase();
	removecount++;
}

template <class ItemType>    
bool Euler::isValidNextEdge() 
{
// The edge u-v is valid in one of the following two cases:
 
  // 1) If v is the only adjacent vertex of u
  int count = 0;  // To store count of adjacent vertices
  list<int>::iterator i;
  for (i = eulerlist[u].begin(); i != eulerlist[u].end(); ++i)
     if (*i != -1)
        count++;
  if (count == 1)
    return true;
 
 
  // 2) If there are multiple adjacents, then u-v is not a bridge
  // Do following steps to check if u-v is a bridge
 
  // 2.a) count of vertices reachable from u
  bool visited[eulerlist->getNumVertices()];
  memset(visited, false, eulerlist->getNumVertices());
  int count1 = DFSCount(u, visited);
 
  // 2.b) Remove edge (u, v) and after removing the edge, count
  // vertices reachable from u
  rmvEdge(u, v);
  memset(visited, false, eulerlist->getNumVertices());
  int count2 = DFSCount(u, visited);
 
  // 2.c) Add the edge back to the graph
  addEdge(u, v);
 
  // 2.d) If count1 is greater, then edge (u, v) is a bridge
  return (count1 > count2)? false: true;
}
    
template <class ItemType>
bool Euler::isEuler()
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
bool Euler::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;
 
    // Recur for all the vertices adjacent to this vertex
   vector<EulerEdge<ItemType>>::iterator i;
    for (i = eulerlist[v].begin(); i != eulerlist[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
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
