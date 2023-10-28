#include "addressBookType.h"


int main()
try {

	ifstream inFile;
	inFile.open("C:\\inData.txt");
	if (!inFile)
	{
		cout << "File does not exist." << endl;
		cout << "Program terminates." << endl;
		return 1;
	}

	addressBookType book1;
	book1.loadData(inFile);

	addressBookType book2 = book1.searchByLastName("Wilton");
	cout << "The people with last name \"Wilton\" are: " << endl;
	book2.printBookInfo();
	cout << endl;

	cout << "Results of searching Lisa Miller: " << endl;
	personType p{ "Lisa","Miller" };
	book1.printMemberInfo(p);
	cout << endl;

	cout << "The people born in Month 3 are: " << endl;
	book1.birthMonth(3);
	cout << endl;

	cout << "Family members are: " << endl;
	book1.printRelation("Family");
	cout << endl;

	cout << "People with last names between \"Goat\" and \"Wilton\" are: " << endl;
	book1.printBTW("Goat", "Wilton");
	cout << endl;

	return 0;
}
catch (addressType::Invalid)
{
	cerr << "Invalid Zip Code." << endl;
	return 1;
}
catch (dateType::Invalid)
{
	cerr << "Invalid date." << endl;
	return 1;
}
catch (extPersonType::Invalid)
{
	cerr << "Invalid Phone Number/Relation." << endl;
	return 1;
}
catch (addressBookType::Invalid)
{
	cerr << "Given Month Number is Invalid." << endl;
	return 1;
}

catch (addressBookType::NotFound)
{
	cerr << "Informaton is not present in the book!" << endl;
	return 1;
}
