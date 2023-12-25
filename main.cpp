#include <iostream>
#include <exception>

#include "DocumentParser.h"
#include "UserInterface.h"

using namespace std;

void runApplication(int argc, char **argv);

int main(int argc, char **argv) {

    // Encapsulate the main application logic in a try block to catch any exception
    try {
        runApplication(argc, argv);
    // Catch and handle standard exceptions derivced from std::exeption
    } catch (const std::exception& e) {
        cerr << "Exception caught in main: " << e.what() << endl;
        return 1;
    // Catch-all handler for any other exceptions not derived from std::exception
    } catch (...) {
        cerr << "Unknown exception caught in main." << endl;
        return 1;
    }
    // Return 0 to indicate successful execution
    return 0;
}

void runApplication(int argc, char **argv) {
    if (argc < 2) {
        cout << "Usage: [index/query/ui] [additional parameters]" << endl;
        return;
    }

    string command = argv[1];
    UserInterface ui;

    if (command == "index") {
        if (argc < 3) {
            cout << "Missing path for index command." << endl;
            return;
        }
        ui.createIndex(argv[2]);
        ui.writeIndex();
    } else if (command == "query") {
        if (argc < 3) {
            cout << "Missing query string for query command." << endl;
            return;
        }
        ui.readIndex();
        ui.enterQuery(argv[2], false);
    } else if (command == "ui") {
        ui.displayMenu();
    } else {
        cout << "Invalid command." << endl;
    }
}