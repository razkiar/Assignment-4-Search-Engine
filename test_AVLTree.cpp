#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "AVLTree.h"

TEST_CASE("AVL Tree functionality", "[AVLTree]")
{
    AvlTree<int, int> tree;

    SECTION("Insertion and balance")
    {
        tree.insert(10, 10);
        tree.insert(20, 20);
        tree.insert(30, 30);
        tree.insert(40, 40);
        tree.insert(50, 50);

        REQUIRE(tree.contains(10));
        REQUIRE(tree.contains(20));
        REQUIRE(tree.contains(30));
        REQUIRE(tree.contains(40));
        REQUIRE(tree.contains(50));
    }

    SECTION("Removal and rebalancing")
    {
        tree.insert(10, 10);
        tree.insert(20, 20);
        tree.insert(30, 30);
        tree.insert(40, 40);
        tree.insert(50, 50);

        tree.remove(30);
        REQUIRE_FALSE(tree.contains(30));
    }

    SECTION("Search functionality")
    {
        tree.insert(15, 15);
        REQUIRE(tree.contains(15));
        REQUIRE_FALSE(tree.contains(100));
    }

    SECTION("Checking balance after insertions")
    {
        std::vector<int> insertionKeys = {10, 20, 30, 40, 50, 60};
        for (int key : insertionKeys)
        {
            tree.insert(key, key);
            REQUIRE(tree.contains(key)); // Verifying each insertion
        }
    }

    SECTION("Checking balance after removals")
    {
        // Pre-populate the tree with necessary keys
        std::vector<int> initialKeys = {10, 20, 30, 40, 50, 60};
        for (int key : initialKeys)
        {
            tree.insert(key, key);
        }

        std::vector<int> removalKeys = {20, 30, 40};
        for (int key : removalKeys)
        {
            if (tree.contains(key))
            {
                tree.remove(key);
                REQUIRE_FALSE(tree.contains(key)); // Verifying each removal
            }
            else
            {
                // Handle the case when key is not found
                REQUIRE_THROWS_AS(tree.remove(key), std::runtime_error);
            }
        }
    }

    SECTION("Exception on Duplicate Insertion")
    {
        tree.insert(10, 10);
        REQUIRE_THROWS_AS(tree.insert(10, 10), std::runtime_error);
    }

    SECTION("Exception on Removing Non-existing Element")
    {
        REQUIRE_THROWS_AS(tree.remove(10), std::runtime_error);
    }

    SECTION("Operations on Empty Tree")
    {
        AvlTree<int, int> emptyTree;
        REQUIRE_FALSE(emptyTree.contains(10));
        REQUIRE_THROWS_AS(emptyTree.remove(10), std::runtime_error);
    }

    SECTION("Single Element Operations")
    {
        AvlTree<int, int> singleElementTree;
        singleElementTree.insert(15, 15);
        REQUIRE(singleElementTree.contains(15));
        singleElementTree.remove(15);
        REQUIRE_FALSE(singleElementTree.contains(15));
    }

    SECTION("Complex Operations")
    {
        AvlTree<int, int> complexTree;
        std::vector<int> keys = {50, 20, 70, 10, 30, 60, 80, 15, 25, 55, 65};
        for (int key : keys)
        {
            complexTree.insert(key, key);
        }
        complexTree.remove(20);
        complexTree.remove(30);
        complexTree.insert(22, 22);
        REQUIRE(complexTree.contains(22));
    }

    SECTION("Sequential Insertions and Removals")
    {
        AvlTree<int, int> sequentialTree;
        for (int i = 1; i <= 10; ++i)
        {
            sequentialTree.insert(i, i);
        }
        for (int i = 10; i >= 1; --i)
        {
            sequentialTree.remove(i);
            REQUIRE_FALSE(sequentialTree.contains(i));
        }
    }

    SECTION("Stress Test")
    {
        AvlTree<int, int> stressTree;
        int numElements = 1000; // Adjust as needed
        for (int i = 0; i < numElements; ++i)
        {
            stressTree.insert(i, i);
        }
        for (int i = 0; i < numElements; ++i)
        {
            stressTree.remove(i);
            REQUIRE_FALSE(stressTree.contains(i));
        }
    }

    SECTION("Key Retrieval Test")
    {
        tree.insert(10, 100);
        REQUIRE(tree.getValues(10) == 100);
    }

    SECTION("Edge Case Test with Extreme Values")
    {
        tree.insert(INT_MAX, 100);
        tree.insert(INT_MIN, 200);
        REQUIRE(tree.contains(INT_MAX));
        REQUIRE(tree.contains(INT_MIN));
    }
}