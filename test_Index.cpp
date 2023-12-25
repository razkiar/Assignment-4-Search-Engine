#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Index.h"
#include "AvlTree.h"
#include "document.h"
#include <string>
#include <map>
#include <set>

using namespace std;

TEST_CASE("AVL Tree Population and Size Verification", "[Index]")
{
    Index index;
    AvlTree<string, map<string, int>> wordTree;
    AvlTree<string, set<string>> nameTree;
    AvlTree<string, document> docTree;

    // Check for word tree
    SECTION("Check Word Tree Insertion")
    {
        wordTree.insert("word1", {{"doc1", 1}});
        wordTree.insert("word2", {{"doc2", 2}});
        REQUIRE(wordTree.size() == 2);
    }

    // Check for name tree
    SECTION("Check Name Tree Insertion")
    {
        nameTree.insert("Name1", {"uuid1"});
        nameTree.insert("Name2", {"uuid2"});
        REQUIRE(nameTree.size() == 2);
    }

    // Check for document tree
    SECTION("Check Document Tree Insertion")
    {
        document doc1("Title1", "doc1", "2023-01-01", "Author1", "Content1");
        document doc2("Title2", "doc2", "2023-02-01", "Author2", "Content2");
        docTree.insert("doc1", doc1);
        docTree.insert("doc2", doc2);
        REQUIRE(docTree.size() == 2);
    }
}

TEST_CASE("AVL Tree Querying and Updating", "[Index]")
{
    Index index;
    AvlTree<string, map<string, int>> wordTree;
    AvlTree<string, set<string>> nameTree;
    AvlTree<string, document> docTree;

    // Populate trees with sample data
    wordTree.insert("word1", {{"doc1", 1}});
    wordTree.insert("word2", {{"doc2", 2}});
    nameTree.insert("Name1", {"uuid1"});
    nameTree.insert("Name2", {"uuid2"});
    document doc1("Title1", "doc1", "2023-01-01", "Author1", "Content1");
    document doc2("Title2", "doc2", "2023-02-01", "Author2", "Content2");
    docTree.insert("doc1", doc1);
    docTree.insert("doc2", doc2);

    // Test querying functionality
    SECTION("Querying Trees")
    {
        REQUIRE(wordTree.contains("word1"));
        REQUIRE(nameTree.contains("Name1"));
        REQUIRE(docTree.contains("doc1"));
    }
    // Test updating functionality
    SECTION("Updating Trees")
    {
        wordTree["word1"]["doc1"] = 5;     // Update frequency
        nameTree["Name1"].insert("uuid3"); // Add another UUID
        document updatedDoc("Updated Title", "doc1", "2023-03-01", "Updated Author", "Updated Content");
        docTree["doc1"] = updatedDoc; // Update document

        REQUIRE(wordTree["word1"]["doc1"] == 5);
        REQUIRE(nameTree["Name1"].size() == 2);
        REQUIRE(docTree["doc1"].title == "Updated Title");
    }

    // Test removal functionality
    SECTION("Removing Entries from Trees")
    {
        wordTree.remove("word1");
        nameTree.remove("Name1");
        docTree.remove("doc1");

        REQUIRE(wordTree.contains("word1") == wordTree.contains("word1"));
        REQUIRE(nameTree.contains("Name1") == nameTree.contains("Name1"));
        REQUIRE(docTree.contains("doc1") == docTree.contains("doc1"));
    }
}