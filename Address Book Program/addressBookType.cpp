#include "addressBookType.h"

addressType::addressType() :streetAddress{ "" }, city{ "" }, state{ "" }, zipCode{ 0 }
{

}

void addressType::setAddress(string st, string c, string s, int zip)
{
	if (zip < 0)
		throw Invalid{};

	streetAddress = st;
	city = c;
	state = s;
	zipCode = zip;
}

void addressType::loadAddress(istream& in)
{
	char read;
	string st;
	string c;
	string s;
	int zip;

	in >> read;
	while (read != ',')
	{
		st += read;
		in.get(read);

	}

	in >> read;
	while (read != ',')
	{
		c += read;
		in.get(read);

	}

	in >> read;
	while (read != ',')
	{
		s += read;
		in.get(read);

	}

	in >> zip;

	setAddress(st, c, s, zip);

}

addressType::addressType(string st, string c, string s, int zip)
{
	setAddress(st, c, s, zip);
}

void addressType::printAddress() const
{
	cout << streetAddress << "," << city << "," << state << "," << zipCode << endl;
}

string addressType::getStreet() const {

	return streetAddress;

}
string addressType::getCity() const
{
	return city;
}
string addressType::getState() const
{
	return state;
}
int addressType::getZIP() const
{
	return zipCode;
}

void addressType::setStreet(string st)
{
	streetAddress = st;
}
void addressType::setCity(string c)
{
	city = c;
}
void addressType::setState(string s)
{
	state = s;
}

void addressType::setZIP(int zip)
{
	if (zip < 0)
		throw Invalid{};
	zipCode = zip;

}

bool addressType::sameCity(const addressType add) const
{
	if (city == add.city)
		return true;
	return false;
}
bool addressType::sameState(const addressType add) const
{
	if (state == add.state)
		return true;
	return false;
}

//----------------------------------------------------------------------------------------------------------
void personType::print() const
{
	cout << firstName << " " << lastName;
}

void personType::setName(string first, string last)
{
	firstName = first;
	lastName = last;
}

string personType::getFirstName() const
{
	return firstName;
}


string personType::getLastName() const
{
	return lastName;
}

personType::personType(string first, string last)
{
	firstName = first;
	lastName = last;
}

void personType::setFirstName(string first)
{
	firstName = first;
}

void personType::setLastName(string last)
{
	lastName = last;
}

bool personType::nameIsEqual(const personType& person) const
{
	if (firstName == person.firstName)
		return true;
	else
		return false;

}

bool personType::lastIsEqual(const personType& person) const
{
	if (lastName == person.lastName)
		return true;
	else
		return false;

}

//-----------------------------------------------------------------------------------------------------------

void dateType::is_valid(int yy, int mm, int dd)
{
	// check for year
	if (yy <= 0)
		throw Invalid{};

	// check for month
	if (mm <= 0 || mm > 12)
		throw Invalid{};

	// check for day
	if (dd <= 0)
		throw Invalid{};

	int day_in_month = 31;
	switch (mm)
	{
	case 2:
		day_in_month = 28; // ignore leap year where number of days in feb is 29
	case 4:
	case 6:
	case 9:
	case 11:
		day_in_month = 30;
		break;
	}
	if (dd > day_in_month)
		throw Invalid{};
}

dateType::dateType(int yy, int mm, int dd) : y{ yy }, m{ mm }, d{ dd }
{
	is_valid(yy, mm, dd);

}

dateType::dateType() :y{ 1 }, m{ 1 }, d{ 1900 }
{

}

void dateType::loadDate(istream& in)
{
	int dd, mm, yy;
	char c;
	in >> dd >> c >> mm >> c >> yy;
	setDate(dd, mm, yy);

}

dateType dateType::add_day(const dateType& day)
{
	dateType next = day;

	int max = 31;
	switch (day.m)
	{
	case 2:
		max = 28; // ignore leap year where number of days in feb is 29
	case 4:
	case 6:
	case 9:
	case 11:
		max = 30;
		break;
	}

	if (day.d == max)
	{
		next.d = 1;
		next.m++;
	}
	else
		next.d++;

	if (next.m > 12)
	{
		next.m = 1;
		next.y++;
	}

	is_valid(next.y, next.m, next.d);
	return next;

}

int dateType::getDay() const
{
	return d;
}
int dateType::getMonth() const
{
	return m;
}
int dateType::getYear() const
{
	return y;
}

void dateType::setDate(int dd, int mm, int yy)
{
	is_valid(yy, mm, dd);
	d = dd;
	m = mm;
	y = yy;

}

void dateType::printDate() const
{
	cout << d << "/" << m << "/" << y;
}

//------------------------------------------------------------------------------------------------------------
extPersonType::extPersonType()
{
	phone = "00/00";
	relation = "friend";

}

void extPersonType::setRelation(string r)
{
	if (r != "Family" && r != "Friend" && r != "Work")
		throw Invalid{};
	relation = r;
}

void extPersonType::setPhone(string nb)
{
	for (int i = 0; i < nb.size(); i++)
	{
		if (!isdigit(nb[i]) && nb[i] != '/' && nb[i] != ' ')
			throw Invalid{};
	}
	phone = nb;
}

extPersonType::extPersonType(string first, string last, addressType ad, string nb, dateType birth, string r)
	:personType{ first,last }, address{ ad }, birthDate{ birth }
{
	setPhone(nb);
	setRelation(r);
}

void extPersonType::printInfo() const
{
	cout << "Name: ";
	print();
	cout << endl;

	cout << "Address: ";
	address.printAddress();

	cout << "Phone Number: " << phone << endl;

	cout << "Date of birth: ";
	birthDate.printDate();
	cout << endl;

	cout << "Relation: " << relation << endl;


}
string extPersonType::getPhone() const
{
	return phone;
}
string extPersonType::getRelation() const
{
	return relation;
}

dateType extPersonType::getBirthDate() const
{
	return birthDate;
}

void extPersonType::setInfo(string first, string last, addressType ad, string nb, dateType birth, string r)
{
	setName(first, last);
	address = ad;
	setPhone(nb);
	birthDate = birth;
	setRelation(r);

}

//----------------------------------------------------------------------------------------------------------
void addressBookType::loadData(istream& in)
{
	// local variables to read data
	string first, last;
	addressType ad;
	string nb;
	dateType birth;
	string r;

	// first line provides the number of entries;
	in >> entriesNb;

	// each information for each person is stored on a seperate line
	for (int i = 0; i < entriesNb; i++)
	{
		in >> first >> last;
		ad.loadAddress(in);
		in >> nb;
		birth.loadDate(in);
		in >> r;

		people[i].setInfo(first, last, ad, nb, birth, r);
	}
}

void addressBookType::sortByLastName()
{
	extPersonType temp;
	string min;
	int minIndex;

	for (int i = 0; i < entriesNb; i++)
	{
		temp = people[i];
		min = temp.getLastName();

		for (int j = i + 1; j < entriesNb; j++)
		{
			if (people[j].getLastName() < min)
			{
				min = people[j].getLastName();
				minIndex = j;
			}
		}

		people[i] = people[minIndex];
		people[minIndex] = temp;
	}
}

addressBookType addressBookType::searchByLastName(const string& last) const
{
	addressBookType sameLast;
	sameLast.entriesNb = 0;

	for (int i = 0; i < entriesNb; i++)
	{
		if (people[i].getLastName() == last)
		{
			sameLast.people[sameLast.entriesNb] = people[i];
			sameLast.entriesNb++;
		}

	}

	if (sameLast.entriesNb == 0)
		throw NotFound{};

	return sameLast;
}

void addressBookType::printMemberInfo(const personType& p) const
{
	bool found = false;
	for (int i = 0; i < entriesNb; i++)
	{
		if (people[i].getFirstName() == p.getFirstName() && people[i].getLastName() == p.getLastName())
		{
			people[i].printInfo();
			cout << endl;
			found = true;
			return;
		}
	}

	if (found == false)
		throw NotFound{};

}

void addressBookType::birthMonth(int mm) const
{
	if (mm <= 0 || mm > 12)
		throw Invalid{};
	for (int i = 0; i < entriesNb; i++)
	{
		if (people[i].getBirthDate().getMonth() == mm)
		{
			people[i].print();
			cout << endl;
		}
	}
}

void addressBookType::printBTW(string beg, string end)
{
	sortByLastName();
	int i = 0;
	while (people[i].getLastName() != beg)
		i++;
	while (people[i].getLastName() != end)
	{
		people[i].print();
		cout << endl;
		i++;
	}
	people[i].print();
}

void addressBookType::printRelation(string r)
{
	if (r != "Family" && r != "Friend" && r != "Work")
		throw Invalid{};
	for (int i = 0; i < entriesNb; i++)
	{
		if (people[i].getRelation() == r)
		{
			people[i].print();
			cout << endl;
		}
	}
}

void addressBookType::printBookInfo() const
{
	for (int i = 0; i < entriesNb; i++)
	{
		people[i].printInfo();
		cout << endl;
	}

}