// class declaration for Team Project 10
#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "LinkedGraph.h"
#include "Edge"
#include “Vertex"
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
  		EulerEdge(){}
  		EulerEdge(ItemType start, Edge<ItemType> ed){
  		startLabel = start; edge = ed; checked = false;
  		}
  
  		void setChecked(bool value){ checked = value;  }
  		ItemType getStart()const { return startLabel; }
  		ItemType getEnd() const { return edge.getEndVertex(); }
  		int getWeight() const { return edge.getWeight(); }
  		bool isChecked() const { return checked; }
  
  		bool operator<(const EulerEdge &right)
  		{
  			return this->edge.getWeight() < right.getWeight();
  		}
  
  	};
    private:
    	vector<EulerEdge<ItemType>> minSpanTree; // shortest path
  	  vector<EulerEdge<ItemType>> orderedEdges;//
     //needed for creating minispintree
   void selectionSort(vector<EulerEdge<ItemType>> &array, int size);
    
    public:
    Euler(){}
    ~Euler(){}
    
    //This function returns count of vertices reachable from v.
    int DFSCount();
    //This function is used to check if the graph makes a eulerian graph
    bool IfEuler();
    
  	void createMinSpanTree();
  	void writeMinSpanTree(ostream &os);
  	void writeOrderedEdges(ostream &os);
  	
    bool add(ItemType start,ItemType end, int edgeWeight=0)
    { 
      if(LinkedGraph<ItemType>::add(start,end,edgeWeight))
      {
        Edge<ItemType edge(end,edgeWeight);
        EulerEdge<ItemType> newEdge(start, edge);
    		orderedEdges.push_back(newEdge);
    		return true;
      }
      return false;
    }
    bool remove(ItemType start, ItemType end);
    
    bool isValidNextEdge() // key step, use this to find the path of Fleury’s Algorithm
    {
      // need to check
      //v is # of vertex
      //u is nodes
      //1) If v is the only adjacent vertex of u
      //2) If there are multiple adjacents, then u-v is not a bridge
    }
};
