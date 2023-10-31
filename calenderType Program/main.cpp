int main()
try {
	extDate today{ Date{2006,Month::sep,1} };

	//extDate tomorrow{ today.add_Day()};

	cout << "Today: ";
	today.printextDate();
	//cout << "Tomorrow: ";
	//tomorrow.printextDate();

	//cout << "The number of days in the month is: " << today.daysInMonth() << endl;
	//cout << "The number of days that passed in the year is: " << today.daysPassed() << endl;
	//cout << "The number of remaining days of the year is: " << today.daysRemaining() << endl;

	//extDate next{ today.add_Days(25) };
	//cout << "The Date after 25 days is: ";
	//next.printextDate();

	calendarType cal{ today };
	cal.printCalendar();


	return 0;
}
catch (Date::Invalid)
{
	cerr << "Invalid date" << endl;
}

catch (dayType::Invalid)
{
	cerr << "Invalid day of the week" << endl;

}
catch (calendarType::Invalid)
{
	cerr << "Invalid calendar parameters" << endl;
}