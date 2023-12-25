#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <chrono>
#include "AVLTree.h"  // Assuming this is the correct path
#include "DocumentParser.h"
#include "Index.h"
#include "Query.h"
#include "document.h"

using namespace std;
using namespace chrono;

class UserInterface {
private:
    // Assuming specific types for keys and values as per your project's requirements
    AvlTree<string, map<string, int>> wordTree;
    AvlTree<string, set<string>> people;
    AvlTree<string, document> docTree;
    AvlTree<string, set<string>> orgs;          
    AvlTree<string, string> stopWords;
    vector<pair<string, int>> finalDocs;
    microseconds time;
    int numDocs;

public:
    void displayMenu();
    void createIndex(const string& path);
    void writeIndex();  // tree to file
    void readIndex();   // file to tree
    void enterQuery(const string& query, bool letOpen);
    void outputStatistics();
    const vector<pair<string, int>>& readQueryResults() const;
};
#endif