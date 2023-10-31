#include "calenderType.h"


Date::Date() : d{ 1 }, m{ Month::jan }, y{ 1900 }
{

}

Date::Date(int yy, Month mm, int dd) : y{ yy }, m{ mm }, d{ dd }
{
	is_valid(yy, mm, dd);

}

void Date::setYear(int yy)
{
	if (yy <= 0)
		throw Invalid{};
	y = yy;

}

void Date::setMonth(int mm) {

	if (int(mm) <= 0 || int(mm) > 12)
		throw Invalid{};
	m = Month(mm);

}

void Date::setDay(int dd)
{
	// a valid day is related to the month, so the value of month shoud be set first (in case each value isset separatly)
	if (dd <= 0)
		throw Invalid{};

	int day_in_month = 31;
	switch (int(m))
	{
	case 2:
	{
		if (isLeap())
			day_in_month = 29;
		else
			day_in_month = 28;
	}
	case 4:
	case 6:
	case 9:
	case 11:
		day_in_month = 30;
		break;
	}
	if (dd > day_in_month)
		throw Invalid{};

	d = dd;

}

void Date::is_valid(int yy, Month mm, int dd)
{
	// check for year
	if (yy <= 0)
		throw Invalid{};

	// check for month
	if (int(mm) <= 0 || int(mm) > 12)
		throw Invalid{};

	// check for day
	if (dd <= 0)
		throw Invalid{};

	int day_in_month = 31;
	switch (int(mm))
	{
	case 2:
	{
		if (isLeap())
			day_in_month = 29;
		else
			day_in_month = 28;
		break;
	}
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

Date Date::add_Day()
{
	Date next{ y,m,d };

	int max = 31;
	switch (int(m))
	{
	case 2:
	{
		if (isLeap())
			max = 29;
		else
			max = 28;
		break;
	}
	case 4:
	case 6:
	case 9:
	case 11:
		max = 30;
		break;
	}

	if (d == max)
	{
		next.d = 1;
		next.m = Month(int(m) + 1);// wraps around
	}
	else
		next.d++;

	if (int(next.m) > 12)
	{
		next.m = Month::jan;
		next.y++;
	}

	is_valid(next.y, next.m, next.d);
	return next;

}

Date Date::add_Days(int n)
{
	Date next{ y,m,d };
	for (int i = 0; i < n; i++)
		next = next.add_Day();
	return next;
}

void Date::printDate() const
{
	cout << d << "/" << int(m) << "/" << y << endl;

}

int Date::year() const
{
	return y;
}

int Date::month() const
{
	return int(m);
}

int Date::day() const
{
	return d;
}

bool Date::isLeap() const
{
	if (y % 4 == 0)
	{
		if (y % 100 == 0)
		{
			if (y % 400 == 0)
				return true;
			return false;
		}
		return true;

	}
	return false;
}

int Date::daysInMonth() const
{
	int days = 31;
	switch (int(m))
	{
	case 2:
	{
		if (isLeap())
			days = 29;
		else
			days = 28;
		break;
	}
	case 4:
	case 6:
	case 9:
	case 11:
		days = 30;
		break;
	}

	return days;

}

int Date::daysPassed() const
{
	int days = 0;
	for (int i = 1; i < int(m); i++)
	{
		switch (i)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			days += 31;
			break;

		case 2:
		{
			if (isLeap())
				days += 29;
			else
				days += 28;
			break;
		}
		case 4:
		case 6:
		case 9:
		case 11:
			days += 30;
			break;
		}

	}
	days += d;
	return days;

}

int Date::daysRemaining() const
{
	if (isLeap())
		return 366 - daysPassed();
	return 365 - daysPassed();

}

//-----------------------------------------------------------------------------------------------------------
extDate::extDate() : MonthString{ "" }
{

}

extDate::extDate(int yy, Month mm, int dd, string mon) : Date{ yy,mm,dd }
{
	if (mon == getMonthName())
		MonthString = mon;
	else
		throw Invalid{};
}

extDate::extDate(Date dd)
{
	setYear(dd.year());
	setMonth(dd.month());
	setDay(dd.day());
	MonthString = getMonthName();

}

string extDate::getMonthName() const
{
	return MonthNames[int(month()) - 1];
}

void extDate::printextDate() const
{
	cout << getMonthName() << " " << day() << ", " << year() << endl;;
}


//------------------------------------------------------------------------------------------------------------

dayType::dayType() : day{ "Monday" }
{

}

dayType::dayType(string d)
{
	setDay(d);
}

bool dayType::setDay(string d)
{
	bool isValid = true;
	if (d == "mon" || d == "Mon" || d == "Monday")
	{
		day = "Mon";
		return isValid;
	}

	else if (d == "tue" || d == "Tue" || d == "Tuesday")
	{
		day = "Tue";
		return isValid;
	}
	else if (d == "wed" || d == "Wed" || d == "Wednesday")
	{
		day = "Wed";
		return isValid;
	}
	else if (d == "thu" || d == "Thu" || d == "Thursday")
	{
		day = "Thu";
		return isValid;
	}
	else if (d == "fri" || d == "Fri" || d == "Friday")
	{
		day = "Fri";
		return isValid;
	}
	else if (d == "sat" || d == "Sat" || d == "Saturday")
	{
		day = "Sat";
		return isValid;
	}
	else if (d == "sun" || d == "Sun" || d == "Sunday")
	{
		day = "Sun";
		return isValid;
	}
	throw Invalid{};
}


void dayType::printDay() const
{
	cout << day;
}


string dayType::getDay() const
{
	return day;
}

dayType dayType::nextDay() const
{
	if (day == "Mon")
		return dayType("Tue");

	else if (day == "Tue")
		return dayType("Wed");

	else if (day == "Wed")
		return dayType("Thu");

	else if (day == "Thu")
		return dayType("Fri");

	else if (day == "Fri")
		return dayType("Sat");

	else if (day == "Sat")
		return dayType("Sun");

	else if (day == "Sun")
		return dayType("Mon");

}


dayType dayType::prevDay() const
{
	if (day == "Mon")
		return dayType("Sun");

	else if (day == "Tue")
		return dayType("Mon");

	else if (day == "Wed")
		return dayType("Tue");

	else if (day == "Thu")
		return dayType("Wed");

	else if (day == "Fri")
		return dayType("Thu");

	else if (day == "Sat")
		return dayType("Fri");

	else if (day == "Sun")
		return dayType("Sat");

}

dayType dayType::calculateDay(int d) const
{
	dayType next = dayType(day);
	for (int i = 0; i < d; i++)
		next = next.nextDay();

	return next;
}

//-----------------------------------------------------------------------------------------------------------

void calendarType::firstDayOfMonth()
{
	int daysNb = 0;
	dayType temp{ "Mon" };
	extDate tempDate{ Date{1500,Month::jan,1} };

	for (int i = 1500; i < store.year(); i++)
	{
		tempDate.setYear(i);
		if (tempDate.isLeap())
			daysNb += 366;
		else
			daysNb += 365;
	}
	daysNb += store.daysPassed() - 1;
	firstDay = temp.calculateDay(daysNb);
}

calendarType::calendarType()
{
	firstDay = dayType{ "Monday" };
	Date d{ 1500,Month(1),1 };
	store = extDate{ d };
}

calendarType::calendarType(const extDate& date)
{
	if (date.day() != 1)
		throw Invalid{};
	if (date.year() < 1500)
		throw Invalid{};
	store = date;
	firstDayOfMonth();
	cout << endl;

}

calendarType::calendarType(const dayType& first, const extDate& date)
{
	firstDayOfMonth();
	if (firstDay.getDay() != first.getDay())
		throw Invalid{};

	if (date.day() != 1)
		throw Invalid{};
	if (date.year() < 1500)
		throw Invalid{};
	store = date;
}

void calendarType::setMonth(int mm)
{
	if (mm <= 0 || mm > 12)
		throw Invalid{};
	store.setMonth(mm);

}
void calendarType::setYear(int yy)
{
	if (yy < 1500)
		throw Invalid{};
	store.setYear(yy);

}

int calendarType::getMonth() const
{
	return store.month();

}
int calendarType::getYear() const
{
	return store.year();
}

void calendarType::printCalendar() const
{
	cout << "             " << MonthNames[store.month() - 1] << "  " << store.year() << endl;

	dayType temp{ "Sun" };
	int index;
	for (int i = 1; i <= 7; i++)
	{
		if (firstDay.getDay() == temp.getDay())
			index = i;
		temp.printDay();
		cout << "   ";
		temp = temp.nextDay();
	}
	cout << endl;
	for (int j = 1; j < store.daysInMonth() + index; j++)
	{
		if (j < index)
			cout << "      ";
		else
		{
			cout << right << setw(3) << j - index + 1 << "   ";
		}
		if (j % 7 == 0)
			cout << endl;
	}

}
