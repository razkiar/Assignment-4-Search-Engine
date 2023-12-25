#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include "document.h"
#include "AvlTree.h"
#include <string>
#include <vector>
#include <map>
#include <set>

#include "porter2_stemmer.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

class DocumentParser {
public:
    DocumentParser();

    void readJsonFile(const std::string &filePath,
                      AvlTree<std::string, std::map<std::string, int>> &wordTree,
                      AvlTree<std::string, std::set<std::string>> &personTree,
                      AvlTree<std::string, std::set<std::string>> &organizationTree,
                      AvlTree<std::string, std::string> &stopWordsTree,
                      AvlTree<std::string, document> &documentTree);

    void tokenize(const std::string& content, std::vector<std::string>& tokens);

    void fileSystem(const std::string &directoryPath,
                    AvlTree<std::string, std::map<std::string, int>> &wordTree,
                    AvlTree<std::string, std::set<std::string>> &personTree,
                    AvlTree<std::string, std::set<std::string>> &organizationTree,
                    AvlTree<std::string, std::string> &stopWordsTree,
                    AvlTree<std::string, document> &documentTree);

    void readStopWords(const std::string& filePath, AvlTree<std::string, std::string>& stopWordsTree);

    int getDocumentCount() const; // Function to get document count

private:
    int documentCount;

    void cleanToken(std::string& token);
    void processEntities(const rapidjson::Value& entities, 
                         const std::string& documentId,
                         AvlTree<std::string, std::set<std::string>>& entityTree);
};

#endif // DOCUMENTPARSER_H