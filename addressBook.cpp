#pragma once

/* Address book method definitions */

#include "addressBook.h"

addressBookClass::addressBookClass(basicContactInfo& contactInfoObj)
{
	m_mutexLock.lock();
	insertContact(contactInfoObj);
	m_contactListIterator = m_vectContactList.begin();
	m_mutexLock.unlock();
}

addressBookClass::addressBookClass(vector<basicContactInfo>& contactList)
{
	m_mutexLock.lock();
	for (int i = 0; i < contactList.size(); i++)
		insertContact(contactList[i]);
	m_contactListIterator = m_vectContactList.begin();
	m_mutexLock.unlock();
}

void addressBookClass::addContact(basicContactInfo& contactInfoObj)
{
	m_mutexLock.lock();
	insertContact(contactInfoObj);
	m_mutexLock.unlock();
}

void addressBookClass::insertContact(basicContactInfo& contactInfoObj)
{
	m_vectContactList.insert(contactInfoObj);
}

size_t addressBookClass::size()
{
	return this->m_vectContactList.size();
}

vector<basicContactInfo> addressBookClass::retrieveEntriesByFirstName()
{
	vector<basicContactInfo> sortedContactList(m_vectContactList.begin(), m_vectContactList.end());
	return sortedContactList;
}

vector<basicContactInfo> addressBookClass::retrieveEntriesByLastName()
{
	set<basicContactInfo, strCompByLastName> oderingByLastName(m_vectContactList.begin(), m_vectContactList.end());
	vector<basicContactInfo> sortedContactList(oderingByLastName.begin(), oderingByLastName.end());
	return sortedContactList;
}

vector<basicContactInfo> addressBookClass::searchEntriesByName(string searchString)
{
	vector<basicContactInfo> searchResults;
	basicContactInfo::checkString(searchString);
	for (set<basicContactInfo>::iterator it = m_vectContactList.begin(); it != m_vectContactList.end(); ++it)
	{
		if (it->getFirstName().find(searchString, 0) != string::npos || it->getLastName().find(searchString, 0) != string::npos)
			searchResults.push_back(*it);
	}
	return searchResults;
}

void addressBookClass::removeContact(string& firstName, string& lastName)
{
	m_mutexLock.lock();
	set<basicContactInfo>::iterator toErase = m_vectContactList.begin();
	for (set<basicContactInfo>::iterator it = m_vectContactList.begin(); it != m_vectContactList.end(); ++it)
	{
		if (it->getFirstName() == firstName && it->getLastName() == lastName)
		{
			toErase = it;
		}
	}
	m_vectContactList.erase(toErase);
	m_mutexLock.unlock();
}

void addressBookClass::displayContacts()
{
	for (set<basicContactInfo>::iterator it = m_vectContactList.begin(); it != m_vectContactList.end(); ++it)
		cout << *it;
}