#pragma once

#include <set>
#include <mutex>
#include "contactInfoClass.h"

/* Address book class.
	This class holds a vector of contacts. Each contact is alphabetically ordered according to the first name.
	Address book has many methods through which contacts can be searched, added or deleted.
*/

/* Structure to sort according to first names while creating the address book. */
struct strCompByFirstName
{
	bool operator() (const basicContactInfo &lhs, const basicContactInfo &rhs) const
	{
		return lhs.getFirstName() < rhs.getFirstName();
	}
};

/* Structure to sort according to last names when a user requests it. */
struct strCompByLastName
{
	bool operator() (const basicContactInfo& lhs, const basicContactInfo& rhs) const
	{
		return lhs.getLastName() < rhs.getLastName();
	}
};

/* The address book class holding the list of contacts. */
class addressBookClass
{
	/* Private members (class variables) are only to be accessed by the set/get methods. */
	/* The address book data is held by these class variables. */
private:
	set<basicContactInfo, strCompByFirstName> m_vectContactList;
	set<basicContactInfo, strCompByFirstName>::iterator m_contactListIterator;
	void insertContact(basicContactInfo& contactInfoObj);

	// Mutex lock for multithreaded operations.
	mutex m_mutexLock;

public:

	/* Constructors with uniform intializations */
	addressBookClass() :
		m_vectContactList{ set<basicContactInfo, strCompByFirstName>() }, m_contactListIterator{ m_vectContactList.begin() } {};
	addressBookClass(basicContactInfo& contactInfoObj);
	addressBookClass(vector<basicContactInfo>& contactList);

	// Size gives you the number of contacts in the address book.
	size_t size();

	// Method to add individual contact
	void addContact(basicContactInfo& contactInfoObj);

	// Method to display contacts and corresponsing information
	void displayContacts();

	// Templated method to add new field to every contact in the address book.
	template<typename T>
	void updateFieldToList(string fieldName, T* inpPtr, size_t inpSize)
	{
		m_mutexLock.lock();
		set<basicContactInfo, strCompByFirstName> newContactList;
		for (set<basicContactInfo>::iterator it = m_vectContactList.begin(); it != m_vectContactList.end(); ++it)
		{
			basicContactInfo tmpObj = *it;
			tmpObj.setField(fieldName, inpPtr, inpSize);
			newContactList.insert(tmpObj);
		}
		this->m_vectContactList.swap(newContactList);
		m_mutexLock.unlock();
	}
	
	// Methods to search and retrieve contacts
	vector<basicContactInfo> retrieveEntriesByFirstName();
	vector<basicContactInfo> retrieveEntriesByLastName();
	vector<basicContactInfo> searchEntriesByName(string searchString);

	// Method to remove contact by name from the address book
	void removeContact(string& firstName, string& lastName);
	
	~addressBookClass() = default;
};


