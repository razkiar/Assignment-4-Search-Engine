#include "DocumentParser.h"
#include "document.h"
#include "porter2_stemmer.h"
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <sstream>


#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"

DocumentParser::DocumentParser() : documentCount(0) {
    // Constructor implementation
}

void DocumentParser::readJsonFile(const std::string &filePath,
                                  AvlTree<std::string, std::map<std::string, int>> &wordTree,
                                  AvlTree<std::string, std::set<std::string>> &personTree,
                                  AvlTree<std::string, std::set<std::string>> &organizationTree,
                                  AvlTree<std::string, std::string> &stopWordsTree,
                                  AvlTree<std::string, document> &documentTree) {
    std::ifstream ifs(filePath);
    if (!ifs.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }

    rapidjson::IStreamWrapper isw(ifs);
    rapidjson::Document jsonDoc;
    jsonDoc.ParseStream(isw);

    // Extracting and processing information from the JSON document
    std::string uuid = jsonDoc["uuid"].GetString();
    std::string title = jsonDoc["title"].GetString();
    std::string text = jsonDoc["text"].GetString();
    std::string author = jsonDoc["author"].GetString();
    std::string published = jsonDoc["published"].GetString();

    // Creating a new document object and inserting it into the document tree
    document newDoc(title, uuid, published, author, text);
    documentTree.insert(uuid, newDoc);

    // Tokenizing the text and populating the word tree
    std::vector<std::string> tokens;
    tokenize(text, tokens);
    for (const auto& token : tokens) {
        if (!stopWordsTree.contains(token)) {
            wordTree[token][uuid]++;
        }
    }

    // Processing entities and populating person and organization trees
    const auto& entities = jsonDoc["entities"];
    processEntities(entities["persons"], uuid, personTree);
    processEntities(entities["organizations"], uuid, organizationTree);

    ifs.close();
}

// processEntities() takes in a reference to a JSON array of entities, document ID and an AVL tree 
// and inserts the entity name and its corresponding document ID into the AVL tree.
void DocumentParser::processEntities(const rapidjson::Value& entities, 
                                     const std::string& documentId,
                                     AvlTree<std::string, std::set<std::string>>& entityTree) {
    for (const auto& entity : entities.GetArray()) {
        std::string name = entity["name"].GetString();
        entityTree.insert(name, {documentId});
    }
}
 
// tokenize() takes in a string and a vector of strings and tokenizes the string, applies Porter2 stemming, 
// and stores the tokens in the vector.
void DocumentParser::tokenize(const std::string& content, std::vector<std::string>& tokens) {
    std::istringstream iss(content);
    std::string token;
    while (iss >> token) {
        // Process each token
        cleanToken(token);
        if (!token.empty()) {
            Porter2Stemmer::stem(token); // Apply Porter2 stemming
            tokens.push_back(token);
        }
    }
}
 
// cleanToken() takes in a string and removes punctuation and converts it to lowercase.
void DocumentParser::cleanToken(std::string& token) {
    // Remove punctuation and convert to lowercase
    token.erase(std::remove_if(token.begin(), token.end(), [](char c) {
        return std::ispunct(c) || c == '\''; // Remove punctuation and apostrophes
    }), token.end());
 
    std::transform(token.begin(), token.end(), token.begin(), [](unsigned char c){
        return std::tolower(c); // Convert to lowercase
    });
}
 
// getDocumentCount() returns the total number of documents processed so far.
int DocumentParser::getDocumentCount() const {
    return documentCount;
}
 
// fileSystem() takes in a directory path and multiple AVL trees and recursively reads all the JSON files 
// in the directory and populates the AVL trees.
void DocumentParser::fileSystem(const std::string &directoryPath,
                                AvlTree<std::string, std::map<std::string, int>> &wordTree,
                                AvlTree<std::string, std::set<std::string>> &personTree,
                                AvlTree<std::string, std::set<std::string>> &organizationTree,
                                AvlTree<std::string, std::string> &stopWordsTree,
                                AvlTree<std::string, document> &documentTree) {
    for (const auto &entry : std::filesystem::recursive_directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            readJsonFile(entry.path().string(), wordTree, personTree, organizationTree, stopWordsTree, documentTree);
            documentCount++;
            if (documentCount % 10000 == 0) {
                std::cout << documentCount << " documents processed." << std::endl;
            }
        }
    }
    std::cout << "Total documents processed: " << documentCount << std::endl;
}
 
// readStopWords() takes in a file path and an AVL tree and reads all the stop words from the file and 
// populates the AVL tree.
void DocumentParser::readStopWords(const std::string& filePath, AvlTree<std::string, std::string>& stopWordsTree) {
    std::ifstream file(filePath);
    std::string word;
    while (getline(file, word)) {
        stopWordsTree.insert(word, word); // Populating the stop words tree
    }
}