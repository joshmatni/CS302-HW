// Author: Josh Matni
// Purpose: CS 302 hw7 Graphs!
// 11/20/2023

#include "arrayGraph.h"
#include <iostream>
#include <fstream>
#include <string>
#include <limits> // for numeric limits (referenced from geeksforgeeks)
#define MAX_CITIES 5
using namespace std;

void populateGraphFromFile(ArrayGraph<string>&, const string&);
double calculateCost(int, int);
void swap(string&, string&);
void permute(ArrayGraph<string>&, string[], int, int, double&, string&, ofstream&);
int calculatePathDistance(ArrayGraph<string>&, string[], int);
string createPathString(string[], int);
void visit(string&);
double calculateFuelCost(int);
double calculatePathCost(ArrayGraph<string>&, string[], int);

string cities[MAX_CITIES-1] = {"SF", "LV", "Seattle", "SLC"}; // global arr for cities

int main()
{
    ArrayGraph<string> graph;
    populateGraphFromFile(graph, "paths.txt");

    double minCost = numeric_limits<double>::max(); // set minCost to the maximum value of double (referenced from geeks4geeks)
    string bestPath;
    ofstream outFile("all_paths.txt");

    permute(graph, cities, 0, MAX_CITIES - 2, minCost, bestPath, outFile);

    outFile << "\nBest Path:\nReno -> " << bestPath << " -> Reno\nTotal Cost: $" << minCost << endl;

    if(minCost < numeric_limits<double>::max()) // (referenced from geeks4geeks)
    {
        cout << "Cheapest path: Reno -> " << bestPath << " -> Reno" << endl;
        cout << "Total cost: $" << minCost << endl;
    } else
        cout << "No valid path found!" << endl;

    outFile.close();
    return 0;
}

void populateGraphFromFile(ArrayGraph<string>& graph, const string& filename)
{
    ifstream file(filename);
    string city1, city2;
    int distance;
    char delimiter;

    while(file >> city1 >> city2 >> distance) // undirected graph
    {
        graph.add(city1, city2, distance);
        graph.add(city2, city1, distance); 
    }
}

void swap(string& a, string& b)
{
    string temp = a;
    a = b;
    b = temp;
}

// to generate permutations
void permute(ArrayGraph<string>& graph, string arr[], int start, int end, double& minCost, string& bestPath, ofstream& outFile)
{
    if(start == end)
    {
        int distance = calculatePathDistance(graph, arr, end);
        if(distance != -1) // check if the path is valid
        { 
            double cost = calculatePathCost(graph, arr, end);
            string currentPath = "Reno -> " + createPathString(arr, end) + " -> Reno";
            outFile << currentPath << " - Distance: " << distance << " miles - Cost: $" << cost << "\n";
            if(cost < minCost)
            {
                minCost = cost;
                bestPath = createPathString(arr, end);
            }
        }
    } 
    else
    {
        for(int i = start; i <= end; i++)
        {
            swap(arr[start], arr[i]);
            permute(graph, arr, start + 1, end, minCost, bestPath, outFile);
            swap(arr[start], arr[i]); // backtrack
        }
    }
}

int calculatePathDistance(ArrayGraph<string>& graph, string arr[], int size)
{
    int totalDistance = 0;
    string startCity = "Reno";

    // calculate distance starting from Reno to the first city in arr
    totalDistance += graph.getEdgeWeight(startCity, arr[0]);

    for(int i = 0; i < size - 1; i++)
    {
        totalDistance += graph.getEdgeWeight(arr[i], arr[i + 1]);
    }

    // add distance from the last city back to Reno
    totalDistance += graph.getEdgeWeight(arr[size - 1], startCity);

    return totalDistance;
}

string createPathString(string arr[], int size)
{
    string path;
    for(int i = 0; i < size; i++)
    {
        if(i != 0)
            path += " -> ";

        path += arr[i];
    }
    return path;
}

double calculateFuelCost(int distance)
{
    const double fuelEfficiency = 40.0; // miles per gallon
    const double costPerGallon = 3.5; // cost per gallon
    return (distance / fuelEfficiency) * costPerGallon;
}

double calculatePathCost(ArrayGraph<string>& graph, string arr[], int size)
{
    int totalDistance = calculatePathDistance(graph, arr, size);
    return calculateFuelCost(totalDistance);
}

void visit(string& city)
{
    cout << " " << city << " ";
}