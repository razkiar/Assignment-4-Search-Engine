#include "index.h"

#include <fstream>
#include <iostream>
#include <string>

// Constructor for Index class
Index::Index() : documentCount(0) {
    // Initialize documentCount to 0
}
 
// Function to save word data to a file
void Index::saveWordData(std::string &filepath, AvlTree<std::string, std::map<std::string, int>> &wordTree) {
    // Write the index tree to the specified filepath
    wordTree.writeIndex(filepath, wordTree);
}
 
// Function to save name data to a file
void Index::saveNameData(std::string &filepath, AvlTree<std::string, std::set<std::string>> &nameTree) {
    // Write the index tree to the specified filepath
    nameTree.writeIndex(filepath, nameTree);
}
 
// Function to save document data to a file
void Index::saveDocumentData(std::string &filepath, AvlTree<std::string, document> &documentTree) {
    // Write the index tree to the specified filepath
    documentTree.writeIndex(filepath, documentTree);
}
 
// Function to load word data from a file
void Index::loadWordData(const std::string &filepath, AvlTree<std::string, std::map<std::string, int>> &wordTree) {
    // Open the specified file
    std::ifstream file(filepath);
    
    // Check if file is open
    if (!file.is_open()) {
        std::cerr << "The file cannot open: " << filepath << std::endl;
        return;
    }
 
    // Read the key and associated UUIDs and frequencies
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
            // Insert the key and map into the tree
            wordTree.insert(key, currentMap);
        }
    }
 
    // Close the file
    file.close();
}
 
// Function to load name data from a file
void Index::loadNameData(const std::string &filepath, AvlTree<std::string, std::set<std::string>> &nameTree) {
    // Open the specified file
    std::ifstream file(filepath);
    
    // Check if file is open
    if (!file.is_open()) {
        std::cerr << "The file cannot open: " << filepath << std::endl;
        return;
    }
 
    // Read the key and associated UUIDs
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
 
    // Close the file
    file.close();
}
 
// Function to load document data from a file
void Index::loadDocumentData(const std::string &filepath, AvlTree<std::string, document> &documentTree) {
    // Open the specified file
    std::ifstream file(filepath);
    
    // Check if file is open
    if (!file.is_open()) {
        std::cerr << "The file cannot open: " << filepath << std::endl;
        return;
    }
 
    // Read the UUID and associated document information
    while (!file.eof()) {
        std::string uuid;
        file >> uuid;
 
        document doc;
        std::string title;
        std::string identifier;
        std::string publicationDate;
        std::string authorName;
        std::string content;
 
        // Read the rest of the document information
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
 
        // If the UUID is not empty, add the document to the tree
        if (!uuid.empty()) {
            documentTree.insert(uuid, doc);
        }
    }
 
    // Close the file
    file.close();
}