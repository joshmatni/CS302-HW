// Authors: Ploy Wandeevong and Joshua Matni
// Purpose: Binary Trees and Binary Search Trees!
// Date: 11/04/2023

#include "LinkedBSearchTree.h"
#include <iostream>
#include <fstream>
#include <ctime> // for time()
using namespace std;

int generateRandomNumber(int min, int max);
void visit(int item);

ofstream outFile; // global ofstream object

int main()
{
    LinkedBSearchTree<int> tree;
    outFile.open("bst_output.txt");

    srand(time(NULL));

    // generate 100 random vals and add to bst
    while(tree.getNumberOfNodes() != 100)
    {
        int num = generateRandomNumber(1, 200);
        if(!tree.contains(num))
        {
            tree.add(num);
        }
    }

    outFile << "HEIGHT: " << tree.getHeight() << endl;
    outFile << "INORDER" << endl;
    tree.inorderTraverse(visit);

    outFile << endl << "PREORDER" << endl;
    tree.preorderTraverse(visit);

    outFile << endl << "POSTORDER" << endl;
    tree.postorderTraverse(visit);
    outFile << endl;

    outFile.close(); 
    return 0;
}

int generateRandomNumber(int min, int max)
{
    return (rand() % (max - min)) + min;
}

void visit(int item)
{
    //prints out the item from the traversal
    outFile << item << " "; // uses out global variable to write to file
}
