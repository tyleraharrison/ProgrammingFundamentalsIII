#ifndef H_graph
#define H_graph
  
#include <fstream>
#include <iomanip>
#include <iostream>

#include "linkedList.h"
#include "linkedQueue.h"
#include "unorderedLinkedList.h"

using namespace std;

class graphType {
 public:
  bool isEmpty() const;
  // Function to determine whether the graph is empty.
  // Postcondition: Returns true if the graph is empty;
  //               otherwise, returns false.

  void createGraph();
  // Function to create a graph.
  // Postcondition: The graph is created using the
  //               adjacency list representation.

  void clearGraph();
  // Function to clear graph.
  // Postcondition: The memory occupied by each vertex
  //               is deallocated.

  void printGraph() const;
  // Function to print graph.
  // Postcondition: The graph is printed.

  void depthFirstTraversal();
  // Function to perform the depth first traversal of
  // the entire graph.
  // Postcondition: The vertices of the graph are printed
  //               using depth first traversal algorithm.

  void dftAtVertex(int vertex);
  // Function to perform the depth first traversal of
  // the graph at a node specified by the parameter vertex.
  // Postcondition: Starting at vertex, the vertices are
  //               printed using depth first traversal
  //               algorithm.

  void breadthFirstTraversal();
  // Function to perform the breadth first traversal of
  // the entire graph.
  // Postcondition: The vertices of the graph are printed
  //               using breadth first traversal algorithm.

  graphType(int size = 0);
  // Constructor
  // Postcondition: gSize = 0; maxSize = size;
  //               graph is an array of pointers to linked
  //               lists.

  ~graphType();
  // Destructor
  // The storage occupied by the vertices is deallocated.

 protected:
  int maxSize;                      // maximum number of vertices
  int gSize;                        // current number of vertices
  unorderedLinkedList<int> *graph;  // array to create
                                    // adjacency lists

 private:
  void dft(int v, bool visited[]);
  // Function to perform the depth first traversal of
  // the graph at a node specified by the parameter vertex.
  // This function is used by the public member functions
  // depthFirstTraversal and dftAtVertex.
  // Postcondition: Starting at vertex, the vertices are
  //                using depth first traversal
  //               algorithm.
};

bool graphType::isEmpty() const { 
  return (gSize == 0); }

void graphType::createGraph() {
  ifstream infile;
  string fileName;

  int index;
  int vertex;
  int adjacentVertex;

  if (gSize != 0)  // if the graph is not empty, make it empty
    clearGraph();

  cout << "Enter input file name: ";
  cin >> fileName;
  cout << endl;

  string path = __FILE__; //gets source code path, include file name
  path = path.substr(0,1+path.find_last_of('\\')); //removes file name
  path+= fileName; //adds input file to path

  infile.open(path);

  if (!infile) {
    cout << "Cannot open input file." << endl;
    return;
  }

  infile >> gSize;  // get the number of vertices
  graph = new unorderedLinkedList<int>[gSize];

  for (index = 0; index < gSize; index++) {
    infile >> vertex;
    infile >> adjacentVertex;

    while (adjacentVertex != -999) {
      graph[vertex].insertLast(adjacentVertex);
      infile >> adjacentVertex;
    }
  }
  infile.close();
}

void graphType::clearGraph() {
  int index;
  for (index = 0; index < gSize; index++) 
    graph[index].destroyList();

  gSize = 0;
}

void graphType::printGraph() const {
  int index;

  for (index = 0; index < gSize; index++) {
    cout << index << " ";
    graph[index].print();
    cout << endl;
  }
  cout << endl;
}

void graphType::depthFirstTraversal() {
  bool *visited;  // pointer to create the array to keep track of the visited vertices
  visited = new bool[gSize];

  int index;

  for (index = 0; index < gSize; index++) 
    visited[index] = false;

  // For each vertex that is not visited, do a depth first traverssal
  for (index = 0; index < gSize; index++)
    if (!visited[index]) dft(index, visited);
  delete[] visited;
}

void graphType::dft(int v, bool visited[]) {
  visited[v] = true;
  cout << " " << v << " ";  // visit the vertex

  linkedListIterator<int> graphIt;

  // for each vertex adjacent to v
  for (graphIt = graph[v].begin(); graphIt != graph[v].end(); ++graphIt) {
    int w = *graphIt;
    if (!visited[w]) dft(w, visited);
  }
}

void graphType::dftAtVertex(int vertex) {
  bool *visited;

  visited = new bool[gSize];

  for (int index = 0; index < gSize; index++) 
    visited[index] = false;

  dft(vertex, visited);

  delete[] visited;
}

void graphType::breadthFirstTraversal() {
  linkedQueueType<int> queue;

  bool *visited;
  visited = new bool[gSize];

  for (int ind = 0; ind < gSize; ind++)
    visited[ind] = false;  // initialize the array visited to false

  linkedListIterator<int> graphIt;

  for (int index = 0; index < gSize; index++)
    if (!visited[index]) {
      queue.addQueue(index);
      visited[index] = true;
      cout << " " << index << " ";

      while (!queue.isEmptyQueue()) {
        int u = queue.front();
        queue.deleteQueue();

        for (graphIt = graph[u].begin(); graphIt != graph[u].end(); ++graphIt) {
          int w = *graphIt;
          if (!visited[w]) {
            queue.addQueue(w);
            visited[w] = true;
            cout << " " << w << " ";
          }
        }
      }
    }
  delete[] visited;
}

// Constructor
graphType::graphType(int size) {
  maxSize = size;
  gSize = 0;
  graph = new unorderedLinkedList<int>[size];
}

// Destructor
graphType::~graphType() { clearGraph(); }

#endif