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

void DocumentParser::processEntities(const rapidjson::Value& entities, 
                                     const std::string& documentId,
                                     AvlTree<std::string, std::set<std::string>>& entityTree) {
    for (const auto& entity : entities.GetArray()) {
        std::string name = entity["name"].GetString();
        entityTree.insert(name, {documentId});
    }
}


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

void DocumentParser::cleanToken(std::string& token) {
    // Remove punctuation and convert to lowercase
    token.erase(std::remove_if(token.begin(), token.end(), [](char c) {
        return std::ispunct(c) || c == '\''; // Remove punctuation and apostrophes
    }), token.end());

    std::transform(token.begin(), token.end(), token.begin(), [](unsigned char c){
        return std::tolower(c); // Convert to lowercase
    });
}

int DocumentParser::getDocumentCount() const {
    return documentCount;
}

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

void DocumentParser::readStopWords(const std::string& filePath, AvlTree<std::string, std::string>& stopWordsTree) {
    std::ifstream file(filePath);
    std::string word;
    while (getline(file, word)) {
        stopWordsTree.insert(word, word); // Populating the stop words tree
    }
}
