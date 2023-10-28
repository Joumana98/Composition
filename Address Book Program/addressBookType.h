#ifndef  H-tess
#define H-test

#include "../../std_lib_facilites.h"

class addressType
{
public:
	// throw errors
	class Invalid {};

	// constructors
	addressType();
	addressType(string, string, string, int);

	//accessors
	void printAddress() const;
	string getStreet() const;
	string getCity() const;
	string getState() const;
	int getZIP() const;
	bool sameCity(const addressType add) const;
	bool sameState(const addressType add) const;

	//mutators
	void setAddress(string, string, string, int);
	void loadAddress(istream&);
	void setStreet(string);
	void setCity(string);
	void setState(string);
	void setZIP(int);

private:
	string streetAddress;
	string city;
	string state;
	int zipCode;
};

class personType
{
public:
	void print() const;
	string getFirstName() const;
	string getLastName() const;
	bool nameIsEqual(const personType& person) const;
	bool lastIsEqual(const personType& person) const;

	void setName(string, string);
	void setFirstName(string);
	void setLastName(string);

	personType(string = "", string = "");


private:
	string firstName;
	string lastName;
};

class dateType
{
public:
	//throw errors
	class Invalid {};

	//constructors
	dateType();
	dateType(int, int, int);

	//accessors
	void printDate() const;
	int getDay() const;
	int getMonth() const;
	int getYear() const;
	dateType add_day(const dateType&);


	//mutators
	void loadDate(istream&);
	void setDate(int, int, int);

private:
	void is_valid(int yy, int mm, int dd);

	int y;
	int m;
	int d;

};

class extPersonType : public personType
{
public:

	//throw error
	class Invalid {};

	//constructor;
	extPersonType();
	extPersonType(string, string, addressType, string, dateType, string);

	//accessors 
	void printInfo() const;
	string getPhone() const;
	string getRelation() const;
	dateType getBirthDate() const;

	//mutators
	void setInfo(string, string, addressType, string, dateType, string);
	void setPhone(string);
	void setRelation(string);

private:
	addressType address;
	string phone;
	dateType birthDate;
	string relation;


};

class addressBookType
{
public:

	//throw Errors
	class Invalid {};
	class NotFound {};

	//accessors
	addressBookType searchByLastName(const string&) const;
	void printMemberInfo(const personType& p) const;
	void birthMonth(int) const;
	void printRelation(string);
	void printBookInfo() const;


	//mutators
	void loadData(istream&);
	void sortByLastName();
	void printBTW(string, string);


private:
	extPersonType people[500];
	int entriesNb;
};

#endif  H-tess
