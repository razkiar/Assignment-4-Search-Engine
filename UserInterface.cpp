#include "UserInterface.h"

using namespace std;
using namespace chrono;

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
        case 1:
        {
            string path;
            cout << "Enter the path for documents: ";
            cin >> path;
            createIndex(path);
            break;
        }
        case 2:
            writeIndex();
            break;
        case 3:
            readIndex();
            break;
        case 4:
        {
            string query;
            cout << "Enter your query: ";
            cin.ignore(); // Clear the newline character from the buffer
            getline(cin, query);
            enterQuery(query, true);
            break;
        }
        case 5:
            outputStatistics();
            break;
        case 0:
            cout << "Exiting Super Search.\n";
            break;
        default:
            cout << "Invalid choice, please try again.\n";
            break;
        }
    }
}

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


void UserInterface::readIndex()
{
    cout << "Reading index from persistence..." << endl;

    Index index;
    index.loadWordData("wordsPersist.txt", wordTree);
    index.loadNameData("peoplePersist.txt", people);
    index.loadNameData("orgPersist.txt", orgs);
    index.loadDocumentData("docsPersist.txt", docTree);
}

void UserInterface::enterQuery(const string &choice, bool letOpen)
{
    Query query = Query();
    finalDocs = query.parseQuery(choice, wordTree, people, orgs, stopWords);

    if (finalDocs.empty())
    {
        cout << "No results found" << endl;
    }
    else
    {
        int i = 0;
        for (const auto &d : finalDocs)
        {
            document doc = docTree.getValues(d.first);
            cout << i + 1 << endl;
            cout << "Title: " << doc.title << endl;
            cout << "UUID: " << doc.identifier << endl;
            cout << "Author: " << doc.authorName << endl;
            cout << "Published: " << doc.publicationDate << endl;
            cout << endl;
            i++;
            if (i >= 15)
                break;
        }

        while (letOpen)
        {
            cout << "Enter the document number you want to view. Enter 0 to return to menu" << endl;
            string num;
            cin >> num;
            int numInt = stoi(num);
            if (numInt == 0)
                break;
            if (numInt < 0 || static_cast<size_t>(numInt) > finalDocs.size())
            {
                cout << "Please enter a valid document number" << endl;
                continue;
            }
            cout << "Text: " << docTree.getValues(finalDocs.at(numInt - 1).first).content << endl;
        }
    }
}

void UserInterface::outputStatistics()
{
    cout << "Statistics:" << endl;
    cout << "Time taken to index: " << time.count() << " microseconds" << endl;
    cout << "Total Number of Unique words: " << wordTree.size() << endl;
    cout << "Total Number of Documents: " << numDocs << endl;
    cout << "Total Number of People: " << people.size() << endl;
    cout << "Total Number of Orgs: " << orgs.size() << endl;

    // Resetting the tree after statistics output
    wordTree.makeEmpty();
}

const vector<pair<string, int>>& UserInterface::readQueryResults() const {
    return finalDocs;
}

