#ifndef CTIME_H
#define CTIME_H

// header
#include <time.h>
#include <string.h>

// type
typedef unsigned short _Tus;
typedef long long _Tll;
typedef unsigned long long _Tull;

// c time struct
struct CTime
{
	_Tus _second;
	_Tus _minute;
	_Tus _hour;
	_Tus _day;
	_Tus _month;
	_Tus _year;

	char _clock[9];
	char _date[11];
	char _complete[22];
};

// compare
inline bool ctime_less_than(CTime _left_obj, CTime _right_obj) // _left_obj < _right_obj
{
	return (strcmp(_left_obj._complete, _right_obj._complete) < 0);
}

inline bool ctime_bigger_than(CTime _left_obj, CTime _right_obj) // _left_obj > _right_obj
{
	return (strcmp(_left_obj._complete, _right_obj._complete) > 0);
}

inline bool ctime_equal_to(CTime _left_obj, CTime _right_obj) // _left_obj == _right_obj
{
	return !strcmp(_left_obj._complete, _right_obj._complete);
}

inline short ctime_cmp(CTime _left_obj, CTime _right_obj)
{
	return strcmp(_left_obj._complete, _right_obj._complete);
}

// change and input
inline void ctime_change(CTime *_input_obj)
{
	// change date
	(*_input_obj)._year = ((*_input_obj)._date[0] - '0') * 1000 + ((*_input_obj)._date[1] - '0') * 100 + ((*_input_obj)._date[2] - '0') * 10 + ((*_input_obj)._date[3] - '0');
	(*_input_obj)._month = ((*_input_obj)._date[5] - '0') * 10 + ((*_input_obj)._date[6] - '0');
	(*_input_obj)._day = ((*_input_obj)._date[8] - '0') * 10 + ((*_input_obj)._date[9] - '0');

	// change clock
	(*_input_obj)._hour = ((*_input_obj)._clock[0] - '0') * 10 + ((*_input_obj)._clock[1] - '0');
	(*_input_obj)._minute = ((*_input_obj)._clock[3] - '0') * 10 + ((*_input_obj)._clock[4] - '0');
	(*_input_obj)._second = ((*_input_obj)._clock[6] - '0') * 10 + ((*_input_obj)._clock[7] - '0');;
}

inline CTime ctime_now()
{
	char *computer_ctime, month[4];
	CTime timing;
	time_t tt;
	tm *ti;

	// calculate computer time
	time(&tt);
	ti = localtime(&tt);
	computer_ctime = asctime(ti); // "Fri Jan 14 00:02:41 2019"

								  // set clock
	strncpy(timing._clock, computer_ctime + 11, 8);
	timing._clock[8] = 0;

	// set date
	//* set month
	strncpy(month, computer_ctime + 4, 3);
	month[3] = 0;

	if (!strcmp(month, "Jan")) { strcpy(timing._date + 5, "01"); }
	else if (!strcmp(month, "Feb")) { strcpy(timing._date + 5, "02"); }
	else if (!strcmp(month, "Mar")) { strcpy(timing._date + 5, "03"); }
	else if (!strcmp(month, "Apr")) { strcpy(timing._date + 5, "04"); }
	else if (!strcmp(month, "May")) { strcpy(timing._date + 5, "05"); }
	else if (!strcmp(month, "Jun")) { strcpy(timing._date + 5, "06"); }
	else if (!strcmp(month, "Jul")) { strcpy(timing._date + 5, "07"); }
	else if (!strcmp(month, "Aug")) { strcpy(timing._date + 5, "08"); }
	else if (!strcmp(month, "Sep")) { strcpy(timing._date + 5, "09"); }
	else if (!strcmp(month, "Oct")) { strcpy(timing._date + 5, "10"); }
	else if (!strcmp(month, "Nov")) { strcpy(timing._date + 5, "11"); }
	else { strcpy(timing._date + 5, "12"); }

	//* set year
	strncpy(timing._date, computer_ctime + 20, 4);
	timing._date[4] = timing._date[7] = '/';
	//* set day
	strncpy(timing._date + 8, computer_ctime + 8, 2);
	timing._date[10] = 0;

	// set cmplete date
	strcpy(timing._complete, timing._date); // "2019/06/14"
	strcpy(timing._complete + 10, " "); // "2019/06/14 "
	strcpy(timing._complete + 11, timing._clock); // "2019/06/14 00:02:41"

												  // calculate date on uint type
	ctime_change(&timing);

	return timing;
}

inline CTime ctime_insert(char *_input_obj)
{
	CTime timing;

	// seprate input date
	strcpy(timing._complete, _input_obj);
	strcpy(timing._clock, timing._complete + 11);
	strncpy(timing._date, timing._complete, 10);
	timing._date[10] = 0;

	// calculate date on uint type
	ctime_change(&timing);

	return timing;
}

inline CTime ctime_insert_date(char *_input_obj_date)
{
	char input_obj[20];
	strcpy(input_obj, _input_obj_date);
	strcpy(input_obj + 10, " 00:00:00");
	return ctime_insert(input_obj);
}

// difference function
inline _Tll ctime_minus(CTime _left_obj, CTime _right_obj) // base on seconds
{
	switch (ctime_cmp(_left_obj, _right_obj))
	{
	case 0:
		return 0;
	case -1:
		CTime tmp = _left_obj;
		_left_obj = _right_obj;
		_right_obj = tmp;
	}

	_Tll diff, obj_1_coef, obj_2_coef;
	obj_1_coef = obj_2_coef = 2592000;
	diff = _left_obj._second - _right_obj._second;
	diff += (_left_obj._minute - _right_obj._minute) * 60;
	diff += (_left_obj._hour - _right_obj._hour) * 3600;
	diff += (_left_obj._day - _right_obj._day) * 86400;

#ifdef Month_30
	diff += (_left_obj._month - _right_obj._month) * 2592000; // each month has 30 days
	diff += (_left_obj._year - _right_obj._year) * 31104000; // each year has 360 days
#else
	switch (_left_obj._month)
	{
	case 2:
		obj_1_coef = 2419200;
		break;
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		obj_1_coef = 2678400;
		break;
	}

	switch (_right_obj._month)
	{
	case 2:
		obj_2_coef = 2419200;
		break;
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		obj_2_coef = 2678400;
		break;
	}

	diff += (_left_obj._month * obj_1_coef) - (_right_obj._month * obj_2_coef);
	diff += (_left_obj._year - _right_obj._year) * 31536000; // each year has 365 days
#endif

	return diff;
}

inline _Tll ctime_minus_by_day(CTime _left_obj, CTime _right_obj)
{
	return ctime_minus(_left_obj, _right_obj) / 86400;
}

#endif // !CTIME_H

// *******************************************
// *** Made by: Ali Forouzandeh Hafshejani ***
// *** IUT Scientific Computing Specialist ***
// *******************************************
