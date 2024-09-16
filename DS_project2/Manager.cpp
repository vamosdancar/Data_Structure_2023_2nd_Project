#include "Manager.h"
#include "BpTree.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <limits>
#include <iomanip>
#include <vector>
#include <cctype>
#include <map>


using namespace std;

// Function to process commands from a file
void Manager::run(const char* command) {
    // Open the command file and a log file
    fin.open(command);
    flog.open("log.txt");

    // Check the command file opened
    if (!fin) {
        flog << "File Open Error" << endl;
        return;
    }

    char cmd[10];

    // Read commands from the file
    while (!fin.eof()) {
        while (fin >> cmd) {
            // Compare the read command

            if (strcmp(cmd, "LOAD") == 0) {
                LOAD();
            }

            else if (strcmp(cmd, "ADD") == 0) {
                ADD();
            }

            else if (strcmp(cmd, "SEARCH_BP") == 0) {
                string line;
                getline(fin, line); // Read the entire command line

                stringstream ss(line);
                string command, firstArg, secondArg;

                getline(ss, command, '\t');
                getline(ss, firstArg, '\t');
                getline(ss, secondArg, '\t');

                if (!secondArg.empty()) {
                    //range search
                    SEARCH_BP_RANGE(firstArg, secondArg);
                } else {
                    //book name search
                    SEARCH_BP_BOOK(firstArg);
                }
            }

            else if (strcmp(cmd, "PRINT_BP") == 0) {
                PRINT_BP();
            }
             

            else if (strcmp(cmd, "PRINT_ST") == 0) {
                string line;
    getline(fin, line); // Read the entire command line including "\t100"

    stringstream ss(line);
    int categoryCode;

    ss >> ws; 
    ss >> categoryCode; // categoryCode saving

    if (!ss.fail()) {
        PRINT_ST(categoryCode); // get categoryCode
    } else {
        printErrorCode(500); // print the error code
    }
            }

            else if (strcmp(cmd, "DELETE") == 0) {
                DELETE();
            }

            else if (strcmp(cmd, "EXIT") == 0) {
                printSuccessCode("EXIT");
                this -> ~Manager();                
                exit(0);
            }

            else {
                //print an error code
                printErrorCode(700);
            }
        }
    }

    // Close the file streams
    fin.close();
    flog.close();
    return;
}



bool Manager::LOAD() {
    // Check if the B+ tree already has data loaded
    if (bptree->getRoot() != NULL) {
        printErrorCode(100); // Error code 
        return false;
    }

    // Open the file 
    ifstream file("loan_book.txt");

    if (!file) {
        printErrorCode(100);
        return false;
    }

    string line;
    bool isEmpty = true; // Flag to check if the file is empty

    // Read each line from the file
    while (getline(file, line)) {
        if (line.empty()) continue; 
        isEmpty = false; // Set flag 


        // Parse the line
        stringstream ss(line);
        string name, author, codeStr, yearStr, loanCountStr;
        getline(ss, name, '\t'); // Assuming tab delimiter
        getline(ss, codeStr, '\t');
        getline(ss, author, '\t');
        getline(ss, yearStr, '\t');
        getline(ss, loanCountStr);

        // Convert strings 
        int code = stoi(codeStr);
        int year = stoi(yearStr);
        int loanCount = stoi(loanCountStr);

        // Insert the data 
        LoanBookData* newData = new LoanBookData();
        newData->setBookData(name, code, author, year, loanCount);
        if (!bptree->Insert(newData)) 
        {
            delete newData; // Clean up memory 
            printErrorCode(100); // Error code 
            return false;
        }

        if (!stree->Insert(newData)) 
        {
            printErrorCode(100); // Error code 
            continue; // Skip this data
        }

        

// Find the node
SelectionTreeNode* node = stree->findNode(newData->getCode());

if (node) {
    LoanBookHeap* heap = node->heaps();

    if (!heap) {
        // create and initialize it
        heap = new LoanBookHeap("log.txt");  // Create a new LoanBookHeap
        node->setHeap(heap);  // Set the heap
    }

    // Insert the data 
    if (!heap->Insert(newData)) {
        printErrorCode(100);  // Print error code 
        return false;
    }
} else {
    printErrorCode(100);  // Print error code
    return false;
}
    
    }

    file.close();

    // Check if the file was empty
    if (isEmpty) {
        printErrorCode(100); // Error code 
        return false;
    }

    printSuccessCode("LOAD"); // Success message 
    return true;
}



bool Manager::ADD() {
	string inputLine;
	getline(fin, inputLine);  // Get the full command line after ADD
	inputLine.erase(0, inputLine.find_first_not_of("\t "));

	// the input based
	stringstream ss(inputLine);
	string token, name, codeStr, author, yearStr;
	int tabCount = 0;
	int code = 0; 


	// Extract
	while (getline(ss, token, '\t') && tabCount < 4)
	{

		switch (tabCount) {
		case 0: name = token; break;
		case 1: codeStr = token; break;
		case 2: author = token; break;
		case 3: yearStr = token; break;
		}
		++tabCount;
	}

	// Check if all arguments are present
	if (name.empty() || codeStr.empty() || author.empty() || yearStr.empty()) {
		printErrorCode(200);  // Replace with actual error code
		return false;
	}
	try {
		code = stoi(codeStr);
		// Same needs 
	}
	catch (const invalid_argument& ia) {
		printErrorCode(200);  // Replace for invalid argument
		return false;
	}


	// Create a new LoanBookData object
	LoanBookData* newData = new LoanBookData();
	newData->setName(name);
	newData->setCode(stoi(codeStr));  // Assume the LoanBookData class has these methods
	newData->setAuthor(author);
	newData->setYear(stoi(yearStr));

	// Attempt to insert
	if (!bptree->Insert(newData)) {
		// clean up the allocated memory
		delete newData;
		printErrorCode(200);  // Replace with actual error code
		return false;
	}


// Insert the same data
if (!stree->Insert(newData)) {
    delete newData;  // Clean up memory
    printErrorCode(200);  // Print error code
    return false;
}

// Find the node
SelectionTreeNode* node = stree->findNode(newData->getCode());

if (node) {
    LoanBookHeap* heap = node->heaps();

    if (!heap) {
       
        heap = new LoanBookHeap("log.txt");  // Create a new LoanBookHeap
        node->setHeap(heap);  // Set the heap object
    }

    // Insert the data
    if (!heap->Insert(newData)) {
        printErrorCode(200);  // Print error code 
        return false;
    }
} else {
    printErrorCode(200);  // Print error code
    return false;
}


	SuccessADD("ADD", name, code, author, stoi(yearStr));  // Corrected to pass
	return true;
}



// search for a book by name
bool Manager::SEARCH_BP_BOOK(string name) {
    // Remove leading spaces and tabs
    size_t start = name.find_first_not_of(" \t");
    name = (start == string::npos) ? "" : name.substr(start);

    // Check if the name is valid
    if (name.empty()) {
        printErrorCode(300); // Error code
        return false;
    }

    // Search the B+ tree
    if (bptree->searchBook(name)) {
        LoanBookData* bookData = bptree->getBookDetails(name);
        if (bookData) {
            // display success message
            SuccessSearch("SEARCH_BP", bookData->getName(), bookData->getCode(), bookData->getAuthor(), bookData->getYear(), bookData->getLoanCount());
            return true;
        } else {
            printErrorCode(300); // Error code 
            return false;
        }
    } else {
        printErrorCode(300); // Error code 
        return false;
    }
}


// to search for books
bool Manager::SEARCH_BP_RANGE(string s, string e) {
    // Verify that both start
    if (s.empty() || e.empty()) {
        printErrorCode(300); // Error code 
        return false;
    }

    // Adjust the end key
    if (e.back() < 'z') {
        e.back() = e.back() + 1;
    } else {
        e += "a"; // In case the end key is 'z'
    }

    //there are books in the specified range
    if (bptree->searchRange(s, e)) {
        BpTreeNode* currentNode = bptree->searchLeafNode(s);
        bool found = false;
        flog << "========= SEARCH_BP ==========" << endl;

        // Iterate through leaf nodes
        while (currentNode != nullptr) {
            auto dataNode = dynamic_cast<BpTreeDataNode*>(currentNode);
            if (!dataNode) {
                break; // Break
            }

            // Iterate through the entries in the data node
            for (const auto& entry : *dataNode->getDataMap()) {
                string key = entry.first;
                if (key >= s && key < e) {
                    // Print book details
                    LoanBookData* bookData = entry.second;
                    ostringstream formattedCode;
                    formattedCode << setw(3) << setfill('0') << bookData->getCode(); // Format the book code

                    // Log the formatted book details
                    flog << bookData->getName() << "/" << formattedCode.str() << "/"
                         << bookData->getAuthor() << "/" << bookData->getYear() << "/"
                         << bookData->getLoanCount() << endl;
                    found = true;
                } else if (key >= e) {
                    break; // Break
                }
            }

            // Move to the next node
            currentNode = currentNode->getNext();
        }
        flog << "==============================" << endl << endl;
        return found; // Return true
    } else {
        // No books found in the range
        printErrorCode(300);
        return false;
    }
}

// Function to print the entire contents
bool Manager::PRINT_BP() {
    // Ensure
    if (!bptree) {
        printErrorCode(400); // Error code
        return false;
    }

    // Get the leftmost
    BpTreeNode* currentNode = bptree->getLeftmostDataNode();
    if (!currentNode) {
        printErrorCode(400); // Error code 
        return false;
    }

    flog << "======== PRINT_BP ========" << endl;

    // Iterate through all data nodes
    while (currentNode != nullptr) {
        auto* dataMap = currentNode->getDataMap(); // Retrieve the data map
        if (dataMap) {
            for (const auto& entry : *dataMap) {
                LoanBookData* bookData = entry.second;
                ostringstream formattedCode;
                formattedCode << setw(3) << setfill('0') << bookData->getCode(); // Format the book code

                // Log the formatted book
                flog << bookData->getName() << "/"
                     << formattedCode.str() << "/"
                     << bookData->getAuthor() << "/"
                     << bookData->getYear() << "/"
                     << bookData->getLoanCount() << endl;
            }
        }
        currentNode = currentNode->getNext(); // Move to the next data node
    }

    flog << "========================" << endl << endl;
    return true;
}

// Function to print data
bool Manager::PRINT_ST(int categoryCode) {

    // Find the node
    SelectionTreeNode* node = stree->findNode(categoryCode);
    if (!node) {
        printErrorCode(500); // Error code
        return false;
    }

    // Retrieve the heap
    LoanBookHeap* heap = node->heaps();

    if (!heap) {
        printErrorCode(500); // Error code
        return false;
    }

    else
        {
            
    heap->printHeap(); // Print the data

        }

    return true;
}

bool Manager::DELETE()
{
    printSuccessCode("DELETE");
}

// to print error codes 
void Manager::printErrorCode(int n) {
    flog << "======== ERROR =========" << endl;
    flog << n << endl; // Print the error code number
    flog << "=======================" << endl << endl;
}

// to print success messages
void Manager::printSuccessCode(const string& name) {
    flog << "======== " << name << " =========" << endl;
    flog << "Success" << endl; // Print a success message
    flog << "=====================" << endl << endl;
}

// to log successful addition
void Manager::SuccessADD(const string& action, string& name, int code_str, string& author, int year_str) {
    ostringstream formattedCode;
    formattedCode << setw(3) << setfill('0') << code_str; // Format the code with leading zeros

    flog << "======== " << action << " ========" << endl;
    flog << name << "/" << formattedCode.str() << "/" << author << "/" << year_str << endl; // Log book details
    flog << "=========================" << endl << endl;
}

// to log successful
void Manager::SuccessSearch(const string& action, const string& name, int code_str, const string& author, int year_str, int loan) {
    ostringstream formattedCode;
    formattedCode << setw(3) << setfill('0') << code_str; // Format the code with leading zeros

    flog << "======== " << action << " ========" << endl;
    flog << name << "/" << formattedCode.str() << "/" << author << "/" << year_str << "/" << loan << endl; // Log book details
    flog << "=========================" << endl << endl;
}


