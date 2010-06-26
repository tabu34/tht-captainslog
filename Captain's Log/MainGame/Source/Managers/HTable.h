#ifndef HTABLE_H_
#define HTABLE_H_

#include "CCodeProfiler.h"
#include "SLList.h"
#include <windows.h>
#include <fstream>
using std::string;

typedef CCodeProfiler::tFunctionProfile functProfile;

#define NUMHASHBUCKETS 26

class HTable
{
	SLList<functProfile> * Table;
	unsigned int m_NumOfBuckets;

public:
	///////////////////////////////////////////////////////////////////////////////
	// Function : Constructor 
	// Parameters : numOfBuckets - the number of buckets
	//		hFunction - pointer to the hash function for this table
	// Notes : constructs an empty hash table
	///////////////////////////////////////////////////////////////////////////////
	HTable(unsigned int numOfBuckets, unsigned int (*hFunction) (const functProfile &v))
	{
		m_NumOfBuckets =numOfBuckets;
		Table = new SLList<functProfile>[numOfBuckets];
	}

	HTable()
	{
		m_NumOfBuckets = NUMHASHBUCKETS;
		Table = new SLList<functProfile>[NUMHASHBUCKETS];
	}

	void Initialize(unsigned int numOfBuckets, unsigned int (*hFunction) (const functProfile &v))
	{
		m_NumOfBuckets =numOfBuckets;
		Table = new SLList<functProfile>[numOfBuckets];
	}

	SLList<functProfile>* OutputTable()
	{
		return Table;
	}

	unsigned int NumBuckets()
	{
		return m_NumOfBuckets;
	}

	///////////////////////////////////////////////////////////////////////////////
	// Function : Destructor
	// Notes : destroys a hash table
	///////////////////////////////////////////////////////////////////////////////
	~HTable()
	{
		clear();
		delete[] Table;
	}

	///////////////////////////////////////////////////////////////////////////////
	// Function : Assignment Operator
	///////////////////////////////////////////////////////////////////////////////
	HTable& operator=(const HTable& that)
	{
		if (this != &that)
		{
			delete[] Table;
			m_NumOfBuckets = that.m_NumOfBuckets;
			Table = new SLList<functProfile> [m_NumOfBuckets];

			for (unsigned int i = 0; i < m_NumOfBuckets; i++)
			{
				Table[i] = that.Table[i];
			}
		}
		return *this;
	}

	///////////////////////////////////////////////////////////////////////////////
	// Function : Copy Constructor
	///////////////////////////////////////////////////////////////////////////////
	HTable(const HTable& that)
	{
		m_NumOfBuckets = that.m_NumOfBuckets;
		Table = new SLList<functProfile> [m_NumOfBuckets];

		for (unsigned int i = 0; i < m_NumOfBuckets; i++)
		{
			Table[i] = that.Table[i];
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	// Function : insert
	// Parameters : v - the item to insert into the hash table
	///////////////////////////////////////////////////////////////////////////////
	void insert(char* szFunctionName, functProfile* v)
	{
		Table[numHash(szFunctionName)].addHead(*v);
	}

	///////////////////////////////////////////////////////////////////////////////
	// Function : findAndRemove
	// Parameters : v - the item to remove(if it is found)
	///////////////////////////////////////////////////////////////////////////////
	bool findAndRemove(const functProfile& v)
	{
		bool exist = false;
		SLLIter<functProfile> Iter(Table[numHash(v.strFunctionName)]);
		Iter.begin();
		for (unsigned int i = 0; i < Table[numHash(v.strFunctionName)].size(); i++, ++Iter)
		{
			if (Iter.current().strFunctionName == v.strFunctionName)
			{
				Table[numHash(v.strFunctionName)].remove(Iter);
				exist = true;
				break;
			}
		}
		return exist;
	}

	///////////////////////////////////////////////////////////////////////////////
	// Function : clear
	// Notes : clears the hash table
	///////////////////////////////////////////////////////////////////////////////
	void clear()
	{
		for (unsigned int i = 0; i < m_NumOfBuckets; i++)
		{
			Table[i].clear();
		}
	}


	///////////////////////////////////////////////////////////////////////////////
	// Function : find
	// Parameters : v - the item to look for
	// Return : the bucket we found the item in or -1 if we didn’t find the item.
	///////////////////////////////////////////////////////////////////////////////
	int find(char* szFunctionName, functProfile** v)
	{
		string	tempFunctionName = szFunctionName;
		int bucket = numHash(tempFunctionName);
		SLLIter<functProfile> Iter(Table[bucket]);
		Iter.begin();
		for (; !Iter.end();++Iter)
		{
			if (Iter.current().strFunctionName == tempFunctionName)
			{
				*v = &Iter.current();
				return bucket;
			}
		}
		return -1;
	}

	unsigned int DisplaySize (int index)
	{
		return Table[index].size();
	}

	//void Display(unsigned int NumBuckets)
	//{
	//	ofstream out("htable.txt");
	//	for (unsigned int i = 0; i < NumBuckets; i++)
	//	{
	//		SLLIter<string> Iter(Table[i]);
	//		Iter.begin();
	//		for (unsigned int j = 0; j < Table[i].size(); j++, ++Iter)
	//		{
	//			out << Iter.current();
	//			(Iter.current().length() < 4)?out << "\t\t\t\t":(Iter.current().length() < 8)?out << "\t\t\t":(Iter.current().length() < 12)?out << "\t\t":(Iter.current().length() < 16)?out << "\t":cout << "";
	//		}
	//		out << endl;
	//	}
	//	out.close();
	//}

	//unsigned int numHash(const string &v)
	//{
	//	int number = 12 << 3;
	//	for (unsigned int i = 0; i < v.length(); i++)
	//	{
	//		if (i%3== 0)
	//		{
	//			number *= int(v[i]) << 3;
	//		}
	//		else
	//		{
	//			number *= int(v[i]) >> 3;
	//			number ^= int(v[i-1]);
	//		}
	//	}
	//	return number % NUMHASHBUCKETS;
	//}

	unsigned int numHash(const string &v)
	{
		return toupper(v[0]) - 'A';
	}

};

#endif