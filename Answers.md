# Assignment 4: Answers

**Complete this document, commit your changes to Github and submit the repository URL to Canvas.** Keep your answers short and precise.

Names of all team members: Razkia Rouabah




Used free extension: [ ] 24 hrs or [ ] 48 hrs

[ ] Early submission (48 hrs)

[ ] Bonus work. Describe: ...

Place [x] for what applies.


## Answers

### Project Management

Complete the tasks and planned completion columns **BEFORE** You start with 
coding!


Weekly milestones/tasks. Set out a plan at the beginning and then record when you got it done.

| Task        | Planned completion | Actual completion | Time spent in hrs by X | Time spent in hrs by Y |
| ----------- | :-----------------:| :---------------: | :--------------------: | :--------------------: |
| AVL tree    | Nov 16              | Nov 17           | 13                    | 0                      |
| Document    | Nov 20              | Nov 20           | 3                    | 0                      |
| Document Parser| Nov 28           | Dec 1            | 10                    | 0                      |
| Index       | Dec 5               | Dec 16           | 6                    | 0                      |
| Query       | Dec 14              | Dec 20           | 12                    | 0                      |
| User Interface| Dec 16            | Dec 23          | 8                    | 0                      |
| Main        | Dec 17              | Dec 24          | 2                    | 0                      |



### High-level Design of Solution

- Add a UML class diagram, etc.
- High-level pseudo code for each component.


# AVL Tree

The `AvlTree` class is a template-based implementation of an AVL tree, a self-balancing binary search tree. It is used to store and manage data efficiently, ensuring that the tree remains balanced at all times for optimal performance during insertions, deletions, and lookups.

## Key Components

### AvlNode (Struct inside AvlTree)
- Represents a node in the AVL tree.
- Contains a key (`Key k`), a value (`Value v`), pointers to left and right children, and the height of the node.

### AvlTree Class
- Manages the AVL tree operations.
- Contains a pointer to the root node and various methods for tree manipulation and data retrieval.

## Methods

### Insertion (insert)
- Inserts a new key-value pair into the tree.
- Maintains the balance of the tree after insertion.

### Balancing (balance)
- Ensures the tree remains balanced after insertions and deletions.
- Performs rotations (left, right, double left, double right) to maintain balance.

### Searching (contains)
- Checks whether a certain key exists in the tree.

### Deletion (remove)
- Removes a key-value pair from the tree.
- Maintains the balance of the tree after removal.

### Traversal (getKeys, printTree, prettyPrintTree)
- Methods to traverse the tree and retrieve keys or print the tree structure.

### Utility Methods (makeEmpty, clone, size)
- Provide additional functionalities like clearing the tree, cloning it, and getting its size.

### Persistence (writeIndex)
- Writes the contents of the AVL tree to a file, supporting different types of data (e.g., map, set, document).

## Data Structure Complexity

### Time Complexity
- Insertion, Deletion, Search - O(log n), due to the self-balancing nature.

### Space Complexity
- O(n), where n is the number of nodes in the tree.

## Rationale for Using AVL Tree
- Chosen for its self-balancing characteristic, which ensures that the operations like insertion, deletion, and lookup remain efficient (O(log n)) even in the worst-case scenario.
- Alternative: A regular binary search tree could have been used but might become unbalanced with skewed insertions, leading to O(n) operation times in the worst case.

```markdown
class AvlTree
    // Node structure for AVL Tree
    struct AvlNode
        Key k
        Value v
        AvlNode left
        AvlNode right
        int height

    // Root node of the AVL Tree
    AvlNode root

    // Insert key-value pair into the tree
    Method insert(key, value)
        root = insertIntoTree(root, key, value)

    // Recursive method to insert and balance tree
    Method insertIntoTree(node, key, value)
        If node is null
            return new AvlNode(key, value)
        If key < node.key
            node.left = insertIntoTree(node.left, key, value)
        Else if key > node.key
            node.right = insertIntoTree(node.right, key, value)
        Else
            // Key already exists, update value
            node.value = value
        return balance(node)

    // Check if tree contains a key
    Method contains(key)
        return containsInTree(root, key)

    Method containsInTree(node, key)
        If node is null
            return false
        If key < node.key
            return containsInTree(node.left, key)
        Else if key > node.key
            return containsInTree(node.right, key)
        Else
            return true

    // Remove a key from the tree
    Method remove(key)
        root = removeFromTree(root, key)

    Method removeFromTree(node, key)
        // Implement removal logic, similar to insert
        // Make sure to balance the tree after removal
        return balance(node)

    // Balance the tree at a given node
    Method balance(node)
        If node is null
            return null
        // Calculate balance factor
        balanceFactor = height(node.left) - height(node.right)
        If balanceFactor > 1 // Left heavy
            // Implement rotations
        Else if balanceFactor < -1 // Right heavy
            // Implement rotations
        // Update node's height
        node.height = max(height(node.left), height(node.right)) + 1
        return node

    // Utility methods
    Method height(node)
        // Return height of the node
    Method max(a, b)
        // Return max of two values
    Method rotateLeft(node)
        // Perform left rotation
    Method rotateRight(node)
        // Perform right rotation
    Method doubleRotateLeftRight(node)
        // Perform double rotation (left then right)
    Method doubleRotateRightLeft(node)
        // Perform double rotation (right then left)

    // Traversal and utility operations
    Method getKeys()
        // Traverse tree and collect keys
    Method printTree()
        // Print tree structure
    Method prettyPrintTree()
        // Print tree in a visually appealing format
    Method writeIndex(filepath)
        // Write tree contents to a file

    // Method to clear the tree
    Method makeEmpty()
        root = null

    // Method to clone the tree
    Method clone()
        return cloneTree(root)

    Method cloneTree(node)
        // Implement cloning logic

    // Method to get size of the tree
    Method size()
        // Implement size calculation logic
```


## Document Parser
The `DocumentParser` class is central to processing and extracting data from JSON documents.

### Methods
#### readJsonFile(path, wordTree, peopleMap, orgsMap, stopWordTree, docTree)
- Opens and parses a JSON file from the specified path.
- Converts the content into a document object and inserts it into `docTree`.
- Extracts entities (people, organizations) and words, processing them accordingly.
- Populates `wordTree`, `peopleMap`, and `orgsMap` with processed data.

#### tokenize(tweet)
- Splits a given tweet into words.
- Returns a list of words for further processing.

#### fileSystem(directoryPath, wordTree, peopleMap, orgsMap, stopWordTree, docTree)
- Iterates over all files within a specified directory.
- Applies `readJsonFile` on each file for processing.

#### readStopWords(stopWordTree)
- Reads a list of stop words and inserts them into `stopWordTree`.
- Helps in filtering out common but unimportant words during processing.

## Index
The `Index` class manages the persistence of data structures like trees and maps used in the system.

### Methods
#### makeWordPersist(wordTree, filepath)
- Writes the `wordTree` data structure to a file at the specified filepath.

#### makeNamePersist(nameMap, filepath)
- Writes the `nameMap` data structure, likely containing people or organization names, to a file.

#### makeDocTreePersist(docTree, filepath)
- Saves the `docTree`, which holds document objects, to a file.

#### readWordPersist(tree, filepath)
- Reads word data from a file and populates a given tree structure.

#### readNamePersist(tree, filepath)
- Populates a tree structure with name data read from a file.

#### readDocTreePersist(docTree, filepath)
- Loads document objects into `docTree` from a specified file.

## Query
The `Query` class is responsible for parsing and processing search queries to return relevant documents.

### Constructor
- **Query()**: Initializes a new Query object.

### Methods
#### parseQuery(query, wordTree, people, orgs, stopWords)
- Processes a query string and returns a list of relevant documents along with their relevance scores.

#### parseAndProcessTerms(term, wordTree, finalMap)
- Processes individual terms within a query.

#### parseAndProcessOrgs(org, orgs, finalMap)
- Handles the processing of organization names in the query.

#### parseAndProcessPeople(person, people, finalMap)
- Processes person names within the query.

#### excludeTerms(terms, finalMap)
- Excludes certain terms from the final map of results.

#### rankResults(finalMap)
- Ranks the results based on relevance criteria.

## UserInterface
`UserInterface` provides the means for users to interact with the system.

### Methods
#### displayMenu()
- Displays the main menu and handles user input.

#### createIndex(path)
- Creates an index from documents located at the specified path.

#### writeIndex()
- Writes the current index to a file for future use.

#### readIndex()
- Reads an index from a previously saved file.

#### enterQuery(choice, letOpen)
- Processes a user's query and displays the results.

#### outputStatistics()
- Displays statistics related to the indexing process.

## Used Data Structures
- **AvlTree**: Time - O(log n), Space - O(n). Balanced, ensuring efficient operations. Alternative: Binary search tree.
- **Map**: Time - O(log n), Space - O(n). Efficient for key-value pairs. Alternative: Hash map.
- **Set**: Time - O(log n), Space - O(n). Ensures uniqueness and order. Useful for names.

## Performance
### Indexing Speed
- Documents indexed in 0.203 seconds.

### Query Response Time
- Ranges from 0.2 to 0.3 seconds, depending on the complexity.

### Used Data Structures
Explanation of what data structures are used where. For each, state
    - time and space complexity (Big-Oh),
    - why it is the appropriate data structure and what other data structure could have been used.

## User Documentation

### Features of the Software
- **Index Creation**: Builds an index from JSON documents, allowing efficient data retrieval.
- **Persistent Storage**: Saves and retrieves indexes to and from persistent storage, ensuring data longevity.
- **Query Processing**: Supports advanced search queries, including filtering by organizations and people.
- **Statistical Output**: Provides insights and metrics about the indexing process and query performance.

### How to Use the Software
1. **Create Index**:
   - Input the directory path containing JSON documents.
   - The system will process these documents to build an index.
2. **Write Index**:
   - Save the created index to files for future use.
   - Ensures that the indexing effort is preserved.
3. **Read Index**:
   - Load an existing index from saved files.
   - Allows for quick retrieval of previously indexed data.
4. **Enter Query**:
   - Input a search query to find relevant documents.
   - Special operators like "org:" and "person:" can refine search results.
5. **Output Statistics**:
   - View statistical data such as the time taken for indexing and counts of words, documents, etc.

### Example Queries with Results
1. **Query**: "german"
   - **Terminal Command**: `supersearch query german`
   - **Output**:
     ```
     Reading index from persistence...
     1. Title: German firms doing business in UK gloomy about Brexit - survey
        UUID: e17252151a2d36344b7104d14805414a55042abe
        Author: Reuters Editorial
        Published: 2018-02-27T20:09:00.000+02:00
     ```

2. **Query**: "january"
   - **Terminal Command**: `supersearch query january`
   - **Output**:
     ```
     Reading index from persistence...
     1. Title: Eaton Vance Closed-End Funds Release Estimated Sources Of Distributions
        UUID: 4ad75456ae0bc42beeee2ff65fa58fa1cc503be2
        Author: cnbc.com
        Published: 2018-02-28T18:54:00.000+02:00

     2. Title: BRIEF-Strax Ab Result For Period Jan 1 - Dec 31 2017 amounted to 0.03 Euros Per Share
        UUID: 5293252386bb424828d17b0ac60299cb52a8ecb9
        Author: Reuters Editorial
        Published: 2018-02-28T04:00:00.000+02:00
     ```
