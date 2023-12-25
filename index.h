#ifndef INDEX_H
#define INDEX_H

#include <map>
#include <set>
#include <string>
#include "AvlTree.h"
#include "DocumentParser.h"

class Index
{
public:
    Index();

    // Saving data to persistent storage
    void saveWordData(std::string &filepath, AvlTree<std::string, std::map<std::string, int>> &wordTree);
    void saveNameData(std::string &filepath, AvlTree<std::string, std::set<std::string>> &nameTree);
    void saveDocumentData(std::string &filepath, AvlTree<std::string, document> &documentTree);

    // Loading data from persistent storage
    void loadWordData(const std::string &filepath, AvlTree<std::string, std::map<std::string, int>> &wordTree);
    void loadNameData(const std::string &filepath, AvlTree<std::string, std::set<std::string>> &nameTree);
    void loadDocumentData(const std::string &filepath, AvlTree<std::string, document> &documentTree);

    void mergeData(AvlTree<std::string, std::map<std::string, int>> &tree,
                   const std::string &key,
                   const std::map<std::string, int> &newData);

private:
    int documentCount;
};

#endif // INDEX_H
