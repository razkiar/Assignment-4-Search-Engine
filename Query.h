#ifndef QUERY_H
#define QUERY_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include "AvlTree.h"

class Query {
public:
    Query() = default;

    // Parses the query entered by the user and updates the finalDocs vector with relevant documents
    std::vector<std::pair<std::string, int>> parseQuery(const std::string& query,
                    AvlTree<std::string, std::map<std::string, int>>& wordTree,
                    AvlTree<std::string, std::set<std::string>>& people,
                    AvlTree<std::string, std::set<std::string>>& orgs,
                    AvlTree<std::string, std::string>& stopWords);

private:
    // Helper methods for parsing different aspects of the query
    void parseAndProcessTerms(const std::string& query,
                              AvlTree<std::string, std::map<std::string, int>>& wordTree,
                              std::map<std::string, int>& finalDocs);

    void parseAndProcessOrgs(const std::string& query,
                             AvlTree<std::string, std::set<std::string>>& orgs,
                             std::map<std::string, int>& finalDocs);

    void parseAndProcessPeople(const std::string& query,
                               AvlTree<std::string, std::set<std::string>>& people,
                               std::map<std::string, int>& finalDocs);

    void excludeTerms(const std::set<std::string>& terms,
                      std::map<std::string, int>& finalDocs);

    // Method for ranking the results based on relevancy
    std::vector<std::pair<std::string, int>> rankResults(std::map<std::string, int>& finalDocs);
};

#endif // QUERY_H
