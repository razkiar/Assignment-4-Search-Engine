#include "UserInterface.h"

using namespace std;
using namespace chrono;

// This function displays the Super Search menu and handles user input
void UserInterface::displayMenu()
{
    int choice = -1;
    while (choice != 0)
    {
        // Display the menu options
        cout << "\n-- Super Search Menu --\n";
        cout << "1. Create Index from Documents\n";
        cout << "2. Write Index to File\n";
        cout << "3. Read Index from File\n";
        cout << "4. Enter a Query\n";
        cout << "5. Output Statistics\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        // Get user input
        cin >> choice;

        // Validate input
        if (cin.fail())
        {
            cin.clear();                                         // Clears the error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discards the input buffer
            cout << "Invalid input, please enter a number.\n";
            continue;
        }

        // Handle the choice
        switch (choice)
        {
        case 1:  // Create index from documents
        {
            string path;
            cout << "Enter the path for documents: ";
            cin >> path;
            createIndex(path);
            break;
        }
        case 2:  // Write index to file
            writeIndex();
            break;
        case 3:  // Read index from file
            readIndex();
            break;
        case 4:  // Enter a query
        {
            string query;
            cout << "Enter your query: ";
            cin.ignore(); // Clear the newline character from the buffer
            getline(cin, query);
            enterQuery(query, true);
            break;
        }
        case 5:  // Output statistics
            outputStatistics();
            break;
        case 0:  // Exit
            cout << "Exiting Super Search.\n";
            break;
        default:  // Invalid choice
            cout << "Invalid choice, please try again.\n";
            break;
        }
    }
}

// This function creates an index of words from the given document path
void UserInterface::createIndex(const string &path)
{
    auto start = high_resolution_clock::now();
    cout << "Creating index..." << endl;

    DocumentParser parser;
    parser.fileSystem(path, wordTree, people, orgs, stopWords, docTree);
    numDocs = parser.getDocumentCount();

    auto stop = high_resolution_clock::now();
    time = duration_cast<microseconds>(stop - start);
}

// This function writes the index data to files
void UserInterface::writeIndex() {
    cout << "Writing index to file..." << endl;
    Index index;

    // Save word data
    string filePath = "../wordsPersist.txt";
    index.saveWordData(filePath, wordTree);

    // Save people data
    filePath = "../peoplePersist.txt";
    index.saveNameData(filePath, people);

    // Save organization data
    filePath = "../orgPersist.txt";
    index.saveNameData(filePath, orgs);

    // Save document data
    filePath = "../docsPersist.txt";
    index.saveDocumentData(filePath, docTree);
}

// This function reads the index data from files
void UserInterface::readIndex()
{
    cout << "Reading index from persistence..." << endl;

    Index index;
    index.loadWordData("wordsPersist.txt", wordTree);
    index.loadNameData("peoplePersist.txt", people);
    index.loadNameData("orgPersist.txt", orgs);
    index.loadDocumentData("docsPersist.txt", docTree);
}

// Function to parse the query entered by user and output the results
void UserInterface::enterQuery(const string &choice, bool letOpen)
{
    // Create a new Query object
    Query query = Query();
    // Parse the query using the wordTree, people, orgs and stopWords
    finalDocs = query.parseQuery(choice, wordTree, people, orgs, stopWords);

    // Check if any results were found
    if (finalDocs.empty())
    {
        cout << "No results found" << endl;
    }
    else
    {
        int i = 0;
        // Loop through the documents in the finalDocs vector
        for (const auto &d : finalDocs)
        {
            // Get the document from the docTree
            document doc = docTree.getValues(d.first);
            // Output the various attributes of the document
            cout << i + 1 << endl;
            cout << "Title: " << doc.title << endl;
            cout << "UUID: " << doc.identifier << endl;
            cout << "Author: " << doc.authorName << endl;
            cout << "Published: " << doc.publicationDate << endl;
            cout << endl;
            i++;
            // Break out of the loop after 15 iterations
            if (i >= 15)
                break;
        }

        // Let the user open the document if letOpen is true
        while (letOpen)
        {
            cout << "Enter the document number you want to view. Enter 0 to return to menu" << endl;
            string num;
            cin >> num;
            int numInt = stoi(num);
            // Break out of the loop if the user enters 0
            if (numInt == 0)
                break;
            // Check if the entered number is valid
            if (numInt < 0 || static_cast<size_t>(numInt) > finalDocs.size())
            {
                cout << "Please enter a valid document number" << endl;
                continue;
            }
            // Output the content of the document
            cout << "Text: " << docTree.getValues(finalDocs.at(numInt - 1).first).content << endl;
        }
    }
}

// Function to output the statistics
void UserInterface::outputStatistics()
{
    cout << "Statistics:" << endl;
    // Output the time taken to index
    cout << "Time taken to index: " << time.count() << " microseconds" << endl;
    // Output the total number of unique words
    cout << "Total Number of Unique words: " << wordTree.size() << endl;
    // Output the total number of documents
    cout << "Total Number of Documents: " << numDocs << endl;
    // Output the total number of people
    cout << "Total Number of People: " << people.size() << endl;
    // Output the total number of organisations
    cout << "Total Number of Orgs: " << orgs.size() << endl;

    // Resetting the tree after statistics output
    wordTree.makeEmpty();
}

// Function to read the query results
const vector<pair<string, int>>& UserInterface::readQueryResults() const {
    return finalDocs;
}