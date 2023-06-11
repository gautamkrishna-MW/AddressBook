// AddressBook.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "addressBook.h"
#include <time.h>
#include <utility>
#include <thread>

/* Function to generate random strings of specified length. */
string genRandName(int strLength)
{
    // srand(time(GetTickCount()));
    char* nameptr = new char[strLength];
    for (int i = 0; i < strLength; i++)
        nameptr[i] = ((rand() % 2 == 0) ? 65 : 97) + (rand() % 26);

    string nameStr(nameptr, strLength);
    return nameStr;
}

/* Function to generate a vector of contact objects. */
vector<basicContactInfo> genRandomContactList(int numEntries)
{
    vector<basicContactInfo> contactList(numEntries);

    for (int i = 0; i < numEntries; i++)
    {
        uint64_t phNum = rand() % UINT64_MAX;
        basicContactInfo contactObj(genRandName(8), genRandName(5), phNum);
        contactList[i] = contactObj;
    }
    return contactList;
}

/* Display Function to output vector of contacts. Used for debugging. */
void displayList(vector<basicContactInfo> contactList)
{
    for (vector<basicContactInfo>::iterator it = contactList.begin(); it != contactList.end(); ++it)
        cout << *it;
}

/* Packing objects into a structure for thread inputs. */
struct threadStruct
{
    addressBookClass *addrBook;
    vector<basicContactInfo> *contList;
    int listId;
};

/* Thread function to be executed by individual threads. */
void threadFunction(threadStruct thStruct)
{
    int idx = thStruct.listId;
    thStruct.addrBook->addContact(thStruct.contList[0][idx]);
}

/* Main */
int main()
{
    // Generate random contact list.
    vector<basicContactInfo> contactList = genRandomContactList(10);

    // Add to the address book
    addressBookClass addressBookObj(contactList);

    // Add contacts individually
    basicContactInfo contactObj1("Gautam", "Krishna", 458745578);
    basicContactInfo contactObj2("John", "Doe", 64877501);
    addressBookObj.addContact(contactObj1);
    addressBookObj.addContact(contactObj2);
    addressBookObj.displayContacts();

    // Remove contacts based on first name
    string deleteContactFirstName("John");
    string deleteContactLastName("John");
    addressBookObj.removeContact(deleteContactFirstName, deleteContactLastName);
    addressBookObj.displayContacts();

    // Display all contacts
    // Also, displays contacts in alphabetical order of the first name
    cout << "Displaying All contacts: " << endl;
    addressBookObj.displayContacts();

    // Display contacts in alphabetical order of the last name
    cout << "Displaying last name sorted: " << endl;
    vector<basicContactInfo> sortedContacts = addressBookObj.retrieveEntriesByLastName();
    displayList(sortedContacts);

    // Search through contacts with a search string
    cout << "Displaying search entry matches: " << endl;
    vector<basicContactInfo> searchContacts = addressBookObj.searchEntriesByName("Ujo");
    if (!searchContacts.empty())
        displayList(searchContacts);
    else
        cout << "No match found" << endl;

    // Add newer fields to the contact or addressbook.
    cout << "Adding new fields: " << endl;
    string addressStr = genRandName(20);
    addressBookObj.updateFieldToList("Address", addressStr.data(), 20);
    addressBookObj.displayContacts();


    /* Multi-Threading Check */
    addressBookClass addressBookNew;
    threadStruct thStructCaller{ 0 };
    thStructCaller.addrBook = &addressBookNew;
    thStructCaller.contList = &contactList;

    thStructCaller.listId = 0;
    thread thObj0(threadFunction, thStructCaller);
    thStructCaller.listId = 1;
    thread thObj1(threadFunction, thStructCaller);
    thStructCaller.listId = 2;
    thread thObj2(threadFunction, thStructCaller);
    thStructCaller.listId = 3;
    thread thObj3(threadFunction, thStructCaller);
    thStructCaller.listId = 4;
    thread thObj4(threadFunction, thStructCaller);
    thStructCaller.listId = 5;
    thread thObj5(threadFunction, thStructCaller);
    thStructCaller.listId = 6;
    thread thObj6(threadFunction, thStructCaller);
    thStructCaller.listId = 7;
    thread thObj7(threadFunction, thStructCaller);
    thStructCaller.listId = 8;
    thread thObj8(threadFunction, thStructCaller);
    thStructCaller.listId = 9;
    thread thObj9(threadFunction, thStructCaller);


    thObj0.join(); thObj1.join(); thObj2.join(); thObj3.join(); thObj4.join();
    thObj5.join(); thObj6.join(); thObj7.join(); thObj8.join(); thObj9.join();

    cout << "After threading: " << endl;
    addressBookNew.displayContacts();

    return 0;
}