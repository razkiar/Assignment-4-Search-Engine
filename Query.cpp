#include "Query.h"
#include <sstream>
#include <algorithm>
#include <cctype>

std::vector<std::pair<std::string, int>> Query::parseQuery(const std::string &query,
                                                           AvlTree<std::string, std::map<std::string, int>> &wordTree,
                                                           AvlTree<std::string, std::set<std::string>> &people,
                                                           AvlTree<std::string, std::set<std::string>> &orgs,
                                                           AvlTree<std::string, std::string> &stopWords)
{

    std::map<std::string, int> finalMap;
    std::set<std::string> exclusionSet;

    std::istringstream queryStream(query);
    std::string word;
    while (queryStream >> word)
    {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower); // Convert word to lowercase
        if (word.find("org:") == 0)
        {
            parseAndProcessOrgs(word.substr(4), orgs, finalMap);
        }
        else if (word.find("person:") == 0)
        {
            parseAndProcessPeople(word.substr(7), people, finalMap);
        }
        else if (!word.empty() && word[0] != '-')
        {
            parseAndProcessTerms(word, wordTree, finalMap);
        }
        else if (!word.empty())
        {
            exclusionSet.insert(word.substr(1));
        }
    }
    excludeTerms(exclusionSet, finalMap);
    return rankResults(finalMap);
}

void Query::parseAndProcessTerms(const std::string &term,
                                 AvlTree<std::string, std::map<std::string, int>> &wordTree,
                                 std::map<std::string, int> &finalMap)
{
    // Check if the term exists in the wordTree
    if (wordTree.contains(term))
    {
        // Retrieve the document-frequency map for the term
        std::map<std::string, int> docs = wordTree.getValues(term);

        // If the finalMap is empty, initialize it with the current term's documents
        if (finalMap.empty())
        {
            finalMap = docs;
        }
        else
        {
            // If the finalMap is not empty, retain only those documents that also appear for the current term
            for (auto iter = finalMap.begin(); iter != finalMap.end();)
            {
                if (docs.find(iter->first) == docs.end())
                {
                    // If the document is not present for the current term, remove it from finalMap
                    iter = finalMap.erase(iter);
                }
                else
                {
                    // If the document is present, update the frequency count by adding the current term's frequency
                    iter->second += docs[iter->first];
                    ++iter;
                }
            }
        }
    }
}

void Query::parseAndProcessOrgs(const std::string &org,
                                AvlTree<std::string, std::set<std::string>> &orgs,
                                std::map<std::string, int> &finalMap)
{
    // Check if the organization exists in the orgs tree
    if (orgs.contains(org))
    {
        // Retrieve the set of documents associated with the organization
        std::set<std::string> docs = orgs.getValues(org);

        // If finalMap is empty, initialize it with the current organization's documents
        if (finalMap.empty())
        {
            for (const auto &uuid : docs)
            {
                finalMap[uuid] = 1; // Initialize the relevancy score to 1
            }
        }
        else
        {
            // If finalMap is not empty, retain only those documents that also appear for the current organization
            for (auto iter = finalMap.begin(); iter != finalMap.end();)
            {
                if (docs.find(iter->first) == docs.end())
                {
                    // If the document is not present for the current organization, remove it from finalMap
                    iter = finalMap.erase(iter);
                }
                else
                {
                    // If the document is present, increment the relevancy score
                    iter->second += 1;
                    ++iter;
                }
            }
        }
    }
}

void Query::parseAndProcessPeople(const std::string &person,
                                  AvlTree<std::string, std::set<std::string>> &people,
                                  std::map<std::string, int> &finalMap)
{
    // Check if the person exists in the people tree
    if (people.contains(person))
    {
        // Retrieve the set of documents associated with the person
        std::set<std::string> docs = people.getValues(person);

        // If finalMap is empty, initialize it with the current person's documents
        if (finalMap.empty())
        {
            for (const auto &uuid : docs)
            {
                finalMap[uuid] = 1; // Initialize the relevancy score to 1
            }
        }
        else
        {
            // If finalMap is not empty, retain only those documents that also appear for the current person
            for (auto iter = finalMap.begin(); iter != finalMap.end();)
            {
                if (docs.find(iter->first) == docs.end())
                {
                    // If the document is not present for the current person, remove it from finalMap
                    iter = finalMap.erase(iter);
                }
                else
                {
                    // If the document is present, increment the relevancy score
                    iter->second += 1;
                    ++iter;
                }
            }
        }
    }
}

void Query::excludeTerms(const std::set<std::string> &terms,
                         std::map<std::string, int> &finalMap)
{
    // Loop through each term in the set of terms to be excluded
    for (const auto &term : terms)
    {
        // Remove any entries from finalMap that match the excluded terms
        for (auto it = finalMap.begin(); it != finalMap.end();)
        {
            if (it->first == term)
            {
                it = finalMap.erase(it); // Erase and advance the iterator
            }
            else
            {
                ++it; // Advance the iterator
            }
        }
    }
}

std::vector<std::pair<std::string, int>> Query::rankResults(std::map<std::string, int> &finalMap)
{
    // Convert the finalMap into a vector of pairs for sorting
    std::vector<std::pair<std::string, int>> rankedResults(finalMap.begin(), finalMap.end());

    // Sort the results based on the frequency count or relevancy score in descending order
    std::sort(rankedResults.begin(), rankedResults.end(),
              [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)
              {
                  return a.second > b.second;
              });

    return rankedResults;
}
