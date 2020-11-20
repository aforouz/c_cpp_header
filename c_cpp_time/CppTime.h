#pragma once

// Header
#include <ctime>
#include <string>
#include <algorithm>

using namespace std;

// C++ time class
class CppTime
{
public:
	CppTime() { now(); }
	CppTime(string _input_time) { insert(_input_time); }
	CppTime(const CppTime& _obj) { insert(_obj._complete); }
	~CppTime() {}

	uint16_t second() { return _second; }
	uint16_t minute() { return _minute; }
	uint16_t hour() { return _hour; }
	uint16_t day() { return _day; }
	uint16_t month() { return _month; }
	uint16_t year() { return _year; }
	string clock() { return _clock; }
	string date() { return _date; }
	string complete() { return _complete; }

	void change()
	{
		_year = stoi(_date.substr(0, 4));
		_month = stoi(_date.substr(5, 2));
		_day = stoi(_date.substr(8, 2));

		_hour = stoi(_clock.substr(0, 2));
		_minute = stoi(_clock.substr(3, 2));
		_second = stoi(_clock.substr(6, 2));
	}

	void now()
	{
		string _computer_cpptime, _month;
		time_t _tt;
		tm *_ti;

		// calculate computer time
		time(&_tt);
		_ti = localtime(&_tt);
		_computer_cpptime = asctime(_ti); // "Fri Jan 14 00:02:41 2019"

		// set clock
		_clock = _computer_cpptime.substr(11, 8);

		// set date
		//* set month
		_month = _computer_cpptime.substr(4, 3);

		if (_month == "Jan") { _month = "01"; }
		else if (_month == "Feb") { _month = "02"; }
		else if (_month == "Mar") { _month = "03"; }
		else if (_month == "Apr") { _month = "04"; }
		else if (_month == "May") { _month = "05"; }
		else if (_month == "Jun") { _month = "06"; }
		else if (_month == "Jul") { _month = "07"; }
		else if (_month == "Aug") { _month = "08"; }
		else if (_month == "Sep") { _month = "09"; }
		else if (_month == "Oct") { _month = "10"; }
		else if (_month == "Nov") { _month = "11"; }
		else { _month = "12"; }

		//* set year
		_date = _computer_cpptime.substr(20, 4);
		//* set day
		_date += ('/' + _month + '/' + _computer_cpptime.substr(8, 2));

		// set complete
		_complete = _date + ' ' + _clock;

		// calculate date on uint16_t type
		change();
	}

	void insert(string _input_obj)
	{
		_date = _input_obj.substr(0, 10);
		_clock = _input_obj.substr(11, 8);
		_complete = _input_obj;
		change();
	}

	void insert_date(string _input_obj_date)
	{
		insert(_input_obj_date + " 00:00:00");
	}
	
	uint64_t operator-(CppTime _right_obj) // base on seconds
	{
		CppTime _left_obj(_complete);
		if (_complete == _right_obj._complete) { return 0; }
		else if (_complete < _right_obj._complete) { swap(_left_obj, _right_obj); }

		int64_t _diff, _obj_1_coef, _obj_2_coef;
		_obj_1_coef = _obj_2_coef = 2592000;
		_diff = _left_obj._second - _right_obj._second;
		_diff += (_left_obj._minute - _right_obj._minute) * 60;
		_diff += (_left_obj._hour - _right_obj._hour) * 3600;
		_diff += (_left_obj._day - _right_obj._day) * 86400;

#ifdef Month_30
		_diff += (_left_obj._month - _right_obj._month) * 2592000; // each month has 30 days
		_diff += (_left_obj._year - _right_obj._year) * 31104000; // each year has 360 days
#else
		switch (_left_obj._month)
		{
		case 2:
			_obj_1_coef = 2419200;
			break;
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			_obj_1_coef = 2678400;
			break;
		}

		switch (_right_obj._month)
		{
		case 2:
			_obj_2_coef = 2419200;
			break;
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			_obj_2_coef = 2678400;
			break;
		}

		_diff += (_left_obj._month * _obj_1_coef) - (_right_obj._month * _obj_2_coef);
		_diff += (_left_obj._year - _right_obj._year) * 31536000; // each year has 365 days
#endif

		return _diff;
	}

	int64_t minus_by_day(CppTime _right_obj)
	{
		CppTime _left_obj(_complete);
		return (_left_obj - _right_obj) / 86400;
	}

	CppTime operator=(CppTime _obj)
	{
		_second = _obj._second;
		_minute = _obj._minute;
		_hour = _obj._hour;
		_day = _obj._day;
		_month = _obj._month;
		_year = _obj._year;

		_clock = _obj._clock;
		_date = _obj._date;
		_complete = _obj._complete;
		
		return _obj;
	}

	bool operator<(CppTime _right_obj) { return (_complete < _right_obj._complete); }
	bool operator>(CppTime _right_obj) { return (_complete > _right_obj._complete); }
	bool operator<=(CppTime _right_obj) { return (_complete <= _right_obj._complete); }
	bool operator>=(CppTime _right_obj) { return (_complete >= _right_obj._complete); }
	bool operator==(CppTime _right_obj) { return (_complete == _right_obj._complete); }
	
private:
	uint16_t _second;
	uint16_t _minute;
	uint16_t _hour;
	uint16_t _day;
	uint16_t _month;
	uint16_t _year;

	string _clock;
	string _date;
	string _complete;
};

// *******************************************
// *** Made by: Ali Forouzandeh Hafshejani ***
// *** IUT Scientific Computing Specialist ***
// *******************************************
