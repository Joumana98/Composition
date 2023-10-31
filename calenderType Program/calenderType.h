#include "../../std_lib_facilites.h"

enum class Month
{
	jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

class Date
{
public:

	//throw errors
	class Invalid {};

	//construtor
	Date();
	Date(int yy, Month mm, int dd);

	//Accessors
	void is_valid(int yy, Month mm, int dd);
	void printDate() const;
	int year() const;
	int month() const;
	int day() const;
	Date add_Day();
	Date add_Days(int);
	bool isLeap() const;
	int daysInMonth() const;
	int daysPassed() const;
	int daysRemaining() const;

	//mutators
	void setDay(int);
	void setMonth(int);
	void setYear(int);



private:
	int y;
	Month m;
	int d;


};

vector<string> MonthNames = { "January","February","March","April","May","June","July","August",
"September","October","November","December" };

class extDate : public Date
{
public:

	//constructors
	extDate();
	extDate(int, Month, int, string);
	extDate(Date);

	// accessors
	string getMonthName() const;
	void printextDate() const;

private:
	string MonthString;
};


class dayType
{
public:

	//throw Error
	class Invalid {};

	//costructor
	dayType();
	dayType(string);

	//accessors
	void printDay() const;
	string getDay() const;
	dayType nextDay() const;
	dayType prevDay() const;
	dayType calculateDay(int d) const;

	//mutators
	bool setDay(string d);


private:
	string day;
};

class calendarType
{
public:

	// throw errors
	class Invalid {};

	//constructor
	calendarType();
	calendarType(const extDate&);
	calendarType(const dayType&, const extDate&);

	//accessors
	int getMonth() const;
	int getYear() const;
	void printCalendar() const;


	//mutators
	void firstDayOfMonth();
	void setMonth(int mm);
	void setYear(int yy);


private:
	dayType firstDay;
	extDate store;

};
