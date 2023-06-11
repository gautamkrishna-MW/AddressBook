#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <memory>
#include <variant>

using namespace std;

struct fieldStruct
{
	enum elemTypeEnum {int32,float32,float64,char8};
	elemTypeEnum eleType;
	void* dataPtr;
	size_t dataSize;
};

/* Basic contact information container
	The 'basicContactInfo' class instance holds details of individual contact. An ordered collection of this class instances form the address book. 
	This class contains setter and getter methods to obtain information from every individual contact. This class also holds the 'm_newFieldMap' container to
	add more fields to contacts dynamically through 'setField()' method.

	The class is also overloaded with a output stream operator to view the detials of a given contact. This supports disply of the dynamically added newer fields too.

	Presently, fields of type integer, floating, and character arrays are only supported for dynamic addition. 
*/

class basicContactInfo
{
	/* Private class members holding the raw data of given contact */
private:
	string m_strFirstName;
	string m_strLastName;
	uint64_t m_lPhoneNumber;
	map<string, fieldStruct> m_newFieldMap;

public:

	/* Various contructors for different scenarios */
	basicContactInfo() :
		m_strFirstName{ "" }, m_strLastName{ "" }, m_lPhoneNumber{ 0 } {};

	basicContactInfo(string firstName, uint64_t phoneNumber);
	basicContactInfo(string firstName, string lastName, uint64_t phoneNumber = 0);
	basicContactInfo(const char* firstName, const char* lastName, uint64_t phoneNumber = 0);

	/* Setter methods to set first name, last name and phone number */
	void SetFirstName(const string& firstName);
	void SetLastName(const string& lastName);
	void SetPhoneNumber(const uint64_t& phoneNumber);

	/* Getter methods return the first/last name and phone number */
	string getFirstName() const;
	string getLastName() const;
	uint64_t getPhoneNumber() const;

	/* Overloaded methods to support the basic types of newer fields that can be added dynamically */
	void setField(string fieldName, int* inpVal, size_t inpSize);
	void setField(string fieldName, float* inpVal, size_t inpSize);
	void setField(string fieldName, double* inpVal, size_t inpSize);
	void setField(string fieldName, char* inpVal, size_t inpSize);

	/* Getter method get the data of any dynamically added field. This returns a void pointer along with the type of pointer. */
	void getField(string fieldName, void* inpVal, size_t& dataSize, fieldStruct::elemTypeEnum& dataType);
	
	/* Output stream method used to display the contact information to stdout */
	friend ostream& operator<<(ostream& output, basicContactInfo contactInfoObj)
	{
		output << contactInfoObj.m_strFirstName << ", " << contactInfoObj.m_strLastName << endl;
		if (contactInfoObj.m_lPhoneNumber != 0)
		{
			output << contactInfoObj.m_lPhoneNumber << endl;

			for (map<string, fieldStruct>::iterator it = contactInfoObj.m_newFieldMap.begin(); it != contactInfoObj.m_newFieldMap.end(); ++it)
			{
				cout << it->first << " : ";
				if (it->second.eleType == fieldStruct::int32)
					cout << (int*)it->second.dataPtr << endl;

				if (it->second.eleType == fieldStruct::float32)
					cout << (float*)it->second.dataPtr << endl;

				if (it->second.eleType == fieldStruct::float64)
					cout << (double*)it->second.dataPtr << endl;

				if (it->second.eleType == fieldStruct::char8)
					cout << (char*)it->second.dataPtr << endl;
			}
			output << endl;
		}
		else
			output << "\n\n";
		return output;
	}


	/* This is used to pre-process an input string to make first letter capital and rest of the letters small. */
	static void checkString(string& inpString);
};