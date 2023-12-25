#include "Index.h"

#include <fstream>
#include <iostream>
#include <string>

Index::Index() : documentCount(0) {
    // Constructor implementation
}

void Index::saveWordData(std::string &filepath, AvlTree<std::string, std::map<std::string, int>> &wordTree) {
    wordTree.writeIndex(filepath, wordTree);
}

void Index::saveNameData(std::string &filepath, AvlTree<std::string, std::set<std::string>> &nameTree) {
    nameTree.writeIndex(filepath, nameTree);
}

void Index::saveDocumentData(std::string &filepath, AvlTree<std::string, document> &documentTree) {
    documentTree.writeIndex(filepath, documentTree);
}

void Index::loadWordData(const std::string &filepath, AvlTree<std::string, std::map<std::string, int>> &wordTree) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "The file cannot open: " << filepath << std::endl;
        return;
    }

    std::string key, uuid;
    int frequency;
    while (!file.eof()) {
        std::map<std::string, int> currentMap;
        file >> key;
        while (!file.eof()) {
            file >> uuid;
            if (uuid == ";") {
                break;
            }
            file >> frequency;
            currentMap.emplace(uuid, frequency);
        }
        if (!currentMap.empty()) {
            wordTree.insert(key, currentMap);
        }
    }

    file.close();
}

void Index::loadNameData(const std::string &filepath, AvlTree<std::string, std::set<std::string>> &nameTree) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "The file cannot open: " << filepath << std::endl;
        return;
    }

    while (!file.eof()) {
        std::string key, uuid;
        std::set<std::string> currentSet;
        file >> key;

        // Read UUIDs associated with the key until a semicolon is encountered
        while (file >> uuid && uuid != ";") {
            currentSet.insert(uuid);
        }

        // Add the set to the tree if it's not empty
        if (!currentSet.empty()) {
            nameTree.insert(key, currentSet);
        }
    }

    file.close();
}

void Index::loadDocumentData(const std::string &filepath, AvlTree<std::string, document> &documentTree) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "The file cannot open: " << filepath << std::endl;
        return;
    }

    while (!file.eof()) {
        std::string uuid;
        file >> uuid;

        document doc;
        std::string title;
        std::string identifier;
        std::string publicationDate;
        std::string authorName;
        std::string content;

        std::getline(file, title); // Assuming title is on a new line
        doc.title = title;

        file >> identifier;
        doc.identifier = identifier;

        file >> publicationDate;
        doc.publicationDate = publicationDate;

        std::getline(file, authorName); // Assuming authorName is on a new line
        doc.authorName = authorName;

        std::getline(file, content); // Assuming content is on a new line
        doc.content = content;

        if (!uuid.empty()) {
            documentTree.insert(uuid, doc);
        }
    }

    file.close();
}
