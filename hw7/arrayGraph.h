#ifndef ARRAYGRAPH_H
#define ARRAYGRAPH_H

#include "graph.h"
#include "arrayQueue.h"
#include <string>
#define CITIES 5
using namespace std;

template <class LabelType>
class ArrayGraph: public GraphInterface<LabelType>
{
    int distances[CITIES][CITIES];
    string cities[CITIES];
    int numVertices, numEdges;
    
    // added private functions 
    int getIndex(string) const;
    bool isVertexIsolated(int) const;
    void removeVertex(int);

    // recursive function
    void depthFirstTraversalHelper(int, void visit(LabelType&), bool []);

    public:
        ArrayGraph();
        ArrayGraph(const ArrayGraph&);
        int getNumVertices() const;
        int getNumEdges() const;
        bool add(LabelType start, LabelType end, int edgeWeight);
        bool remove(LabelType start, LabelType end);
        int getEdgeWeight(LabelType start, LabelType end) const;
        void depthFirstTraversal(LabelType start, void visit(LabelType&));
        void breadthFirstTraversal(LabelType start, void visit(LabelType&));
};
#include "arrayGraph.cpp"
#endif