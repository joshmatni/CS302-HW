#include "arrayGraph.h"

template <class LabelType>
int ArrayGraph<LabelType>::getIndex(string city) const
{
   for(int i = 0; i < numVertices; i++) 
   {
        if(cities[i] == city)
            return i; // city found return the index
   }
    return -1; // city not found
}

template <class LabelType>
ArrayGraph<LabelType>::ArrayGraph()
{
   numVertices = 0;
   numEdges = 0;
   for(int i = 0; i < CITIES; i++) 
   {
        for(int j = 0; j < CITIES; j++)
            distances[i][j] = 0;
   }
}

template <class LabelType>
ArrayGraph<LabelType>::ArrayGraph(const ArrayGraph &rhs)
{
    numVertices = rhs.numVertices;
    numEdges = rhs.numEdges;

    for(int i = 0; i < numVertices; i++)
        cities[i] = rhs.cities[i];

    for(int i = 0; i < CITIES; i++) 
    {
        for(int j = 0; j < CITIES; j++)
            distances[i][j] = rhs.distances[i][j];
    }
}

template <class LabelType>
int ArrayGraph<LabelType>::getNumVertices() const
{
    return numVertices;
}

template <class LabelType>
int ArrayGraph<LabelType>::getNumEdges() const
{
    return numEdges;
}

template <class LabelType>
bool ArrayGraph<LabelType>::add(LabelType start, LabelType end, int edgeWeight)
{
    // check if start city exists
    if(getIndex(start) == -1)
    {
        if(numVertices < CITIES)
        {
            cities[numVertices] = start;
            numVertices++;
        }
        else
            return false;
    }

    // check if end city exists
    if(getIndex(end) == -1)
    {
        if(numVertices < CITIES)
        {
            cities[numVertices] = end;
            numVertices++;
        }
        else
            return false;
    }

    int startIndex = getIndex(start);
    int endIndex = getIndex(end);

    //case for invalidity
    if(startIndex == -1 || endIndex == -1)
        return false;
    
    distances[startIndex][endIndex] = edgeWeight;
    numEdges++;
    return true;
}

template <class LabelType>
bool ArrayGraph<LabelType>::remove(LabelType start, LabelType end)
{
    int startIndex = getIndex(start);
    int endIndex = getIndex(end);

    // check for valid indices
    if(startIndex == -1 || endIndex == -1)
        return false; // edge cannot be removed because one or both cities are not in the graph

    // remove the edge
    distances[startIndex][endIndex] = 0; // default value for no edge
    numEdges--;
    
    // check and remove isolated vertices
    if(isVertexIsolated(startIndex))
        removeVertex(startIndex);
    
    if(isVertexIsolated(endIndex))
        removeVertex(endIndex);

    return true;
}

template <class LabelType>
int ArrayGraph<LabelType>::getEdgeWeight(LabelType start, LabelType end) const
{
    int startIndex = getIndex(start);
    int endIndex = getIndex(end);

    // case for invalidity
    if(startIndex == -1 || endIndex == -1) 
        return -1;

    return distances[startIndex][endIndex];
}

template <class LabelType>
void ArrayGraph<LabelType>::depthFirstTraversal(LabelType start, void visit(LabelType&))
{
    int startIndex = getIndex(start);

    if(startIndex == -1)
        return;

    // to keep track of vistedCities
    bool visitedCities[CITIES] = {false}; 
    depthFirstTraversalHelper(startIndex, visit, visitedCities);
}

template <class LabelType>
void ArrayGraph<LabelType>::depthFirstTraversalHelper(int vertexIndex, void visit(LabelType&), bool visited[])
{
    // mark the vertex as visited
    visited[vertexIndex] = true;

    // process the vertex
    LabelType vertexLabel = cities[vertexIndex];
    visit(vertexLabel);

    // recursively visit all adjacent vertices that have not been visited
    for(int i = 0; i < numVertices; i++) 
    {
        if(distances[vertexIndex][i] != 0 && !visited[i])
            depthFirstTraversalHelper(i, visit, visited);
    }
}

template <class LabelType>
void ArrayGraph<LabelType>::breadthFirstTraversal(LabelType start, void visit(LabelType&))
{
    int startIndex = getIndex(start);
    if(startIndex == -1)
        return; // invalid start vertex

    // keep track of visited vertices
    bool visited[CITIES] = {false};

    // for managing the order of traversal
    ArrayQueue<int> vertexQueue;

    // Start with the 'start' vertex
    visited[startIndex] = true;
    vertexQueue.enqueue(startIndex);

    while(!vertexQueue.isEmpty()) 
    {
        // dequeue a vertex from the queue
        int currentVertexIndex = vertexQueue.peekFront();
        vertexQueue.dequeue();

        // process the vertex
        LabelType currentVertexLabel = cities[currentVertexIndex];
        visit(currentVertexLabel);

        // enqueue all adjacent unvisited vertices
        for(int i = 0; i < numVertices; i++) 
        {
            if(distances[currentVertexIndex][i] != 0 && !visited[i]) 
            {
                visited[i] = true;
                vertexQueue.enqueue(i);
            }
        }
    }
}

template <class LabelType>
bool ArrayGraph<LabelType>::isVertexIsolated(int index) const
{
    for(int i = 0; i < CITIES; i++) 
    {
        if(distances[index][i] != 0 || distances[i][index] != 0)
            return false; // found an edge
    }
    return true; // no edges found
}

template <class LabelType>
void ArrayGraph<LabelType>::removeVertex(int index)
{
    // shift cities array
    for(int i = index; i < numVertices - 1; i++)
        cities[i] = cities[i + 1];

    // shift distances matrix
    // remove row
    for(int i = index; i < numVertices - 1; i++) 
    {
        for(int j = 0; j < CITIES; j++)
            distances[i][j] = distances[i + 1][j];
    }

    // remove column
    for(int j = index; j < numVertices - 1; j++) 
    {
        for(int i = 0; i < numVertices; i++)
            distances[i][j] = distances[i][j + 1];
    }

    numVertices--;
}