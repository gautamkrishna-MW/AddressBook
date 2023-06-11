#pragma once

/* The basic contact class method implementations */

#include "contactInfoClass.h"

basicContactInfo::basicContactInfo(string firstName, uint64_t phoneNumber) :
	m_lPhoneNumber{ phoneNumber }
{
	this->SetFirstName(firstName);
}

basicContactInfo::basicContactInfo(string firstName, string lastName, uint64_t phoneNumber) :
	m_lPhoneNumber{ phoneNumber }
{
	this->SetFirstName(firstName);
	this->SetLastName(lastName);
}

basicContactInfo::basicContactInfo(const char* firstName, const char* lastName, uint64_t phoneNumber) :
	m_lPhoneNumber{ phoneNumber }
{
	this->SetFirstName(firstName);
	this->SetLastName(lastName);
}

void basicContactInfo::SetFirstName(const string& firstName)
{
	m_strFirstName = firstName;
	checkString(m_strFirstName);
}

void basicContactInfo::SetLastName(const string& lastName)
{
	m_strLastName = lastName;
	checkString(m_strLastName);
}
void basicContactInfo::SetPhoneNumber(const uint64_t& phoneNumber)
{
	m_lPhoneNumber = phoneNumber;
}

string basicContactInfo::getFirstName() const
{
	return m_strFirstName;
}

string basicContactInfo::getLastName() const
{
	return m_strLastName;
}

uint64_t basicContactInfo::getPhoneNumber() const
{
	return m_lPhoneNumber;
}

void basicContactInfo::setField(string fieldName, int* inpVal, size_t inpSize)
{
	fieldStruct newFieldobj;
	newFieldobj.eleType = fieldStruct::int32;
	newFieldobj.dataPtr = (void*)inpVal;
	newFieldobj.dataSize = inpSize;

	basicContactInfo::checkString(fieldName);
	this->m_newFieldMap[fieldName] = newFieldobj;
}

void basicContactInfo::setField(string fieldName, char* inpVal, size_t inpSize)
{
	fieldStruct newFieldobj;
	newFieldobj.eleType = fieldStruct::char8;
	newFieldobj.dataPtr = (void*)inpVal;
	newFieldobj.dataSize = inpSize;

	basicContactInfo::checkString(fieldName);
	this->m_newFieldMap[fieldName] = newFieldobj;
}

void basicContactInfo::setField(string fieldName, float* inpVal, size_t inpSize)
{
	fieldStruct newFieldobj;
	newFieldobj.eleType = fieldStruct::float32;
	newFieldobj.dataPtr = (void*)inpVal;
	newFieldobj.dataSize = inpSize;

	basicContactInfo::checkString(fieldName);
	this->m_newFieldMap[fieldName] = newFieldobj;
}

void basicContactInfo::setField(string fieldName, double* inpVal, size_t inpSize)
{
	fieldStruct newFieldobj;
	newFieldobj.eleType = fieldStruct::float64;
	newFieldobj.dataPtr = (void*)inpVal;
	newFieldobj.dataSize = inpSize;

	basicContactInfo::checkString(fieldName);
	this->m_newFieldMap[fieldName] = newFieldobj;
}

void basicContactInfo::getField(string fieldName, void* inpVal, size_t& dataSize, fieldStruct::elemTypeEnum& dataType)
{
	fieldStruct newFieldobj = this->m_newFieldMap[fieldName];
	inpVal = newFieldobj.dataPtr;
	dataSize = newFieldobj.dataSize;
	dataType = newFieldobj.eleType;
}

void basicContactInfo::checkString(string& inpString)
{
	if (inpString[0] >= 'a' && inpString[0] <= 'z')
		inpString[0] = inpString[0] - 32;
	for (int i = 1; i < inpString.size(); i++)
	{
		if (inpString[i] >= 'A' && inpString[i] <= 'Z')
			inpString[i] = inpString[i] + 32;
	}
}