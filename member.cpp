#include <iostream>
#include <vector>
#include <string>
#include "member.h"
using namespace std;

void Member::get_member(string _name)
{
	int i;
	for(i=0;i<name.size();i++)
	{
		if(name.at(i) == _name) 
		{
			location = i;
			return;
		}
	}
	name.push_back(_name);
	M_INFO tmp;
	tmp.b_num = 0;
	tmp.cap = 0;
	tmp.restrict_due = "";
	data.push_back(tmp);
	location = i;
}


void Member::set_restrict_day(string _date, string due_day, string &ret_date)
{
	int n_year = stoi(_date.substr(0, 2));
	int n_month = stoi(_date.substr(3, 2));
	int n_day = stoi(_date.substr(6, 2));
	int d_year = stoi(due_day.substr(0, 2));
	int d_month = stoi(due_day.substr(3, 2));
	int d_day = stoi(due_day.substr(6, 2));

	int year, month, day;
	if(n_day < d_day)
	{
		if(n_month <= d_month)
		{
			year = n_year - d_year - 1;
			month = 12 + (n_month - d_month - 1);
			day = 30 + (n_day - d_day);
		}
		else
		{
			year = n_year - d_year;
			month = n_month - d_month - 1;
			day = 30 + (n_day - d_day);
		}
	}
	else
	{
		year = n_year - d_year;
		month = n_month - d_month;
		day = n_day - d_day;
	}
	year += n_year;
	month += n_month;
	day += n_day;

	if(year < 10) data.at(location).restrict_due += "0";
	data.at(location).restrict_due += to_string(year);
	data.at(location).restrict_due += "/";
	if(month < 10) data.at(location).restrict_due += "0";
	data.at(location).restrict_due += to_string(month);
	data.at(location).restrict_due += "/";
	if(day < 10) data.at(location).restrict_due += "0";
	data.at(location).restrict_due += to_string(day);
	ret_date = data.at(location).restrict_due;
}
bool Member::isExceed(int N)
{
	if(data.at(location).b_num >= N) return true;
	return false;
}
bool Member::isRestricted(string _date)
{
	if(data.at(location).restrict_due == "") return 0;
	string comp = data.at(location).restrict_due;
	int i;
	for(i=0;i<_date.size();i++)
	{
		if(_date.at(i) < comp.at(i)) return 0;
	}
	return 1;
}
void Member::final_state(string B, string resrc_type, int size)
{
	if(B == "B")
	{
		data.at(location).b_num += 1;
		//if(resrc_type == "E_book") 
		//	data.at(location).cap += size;
	}
	else
		data.at(location).b_num -= 1;
}
Under::Under()
{
	capacity = 100;
	n_book = 1;
}
Graduate::Graduate()
{
	capacity = 500;
	n_book = 5;
}
Faculty::Faculty()
{
	capacity = 1000;
	n_book = 10;
}
/*bool Member::isOverCapacity(int C, int size)
{
	if(data.at(location).cap + size > C) return true;
	return false;
}*/
int Under::do_op(string B, string _name, string _date, string& ret_date, string resrc_type, int size)
{
	int ret;
	get_member(_name);
	if(B == "B")
	{
		if(isExceed(n_book)) return 2;
		ret = isRestricted(_date);
		if(ret == true)
		{
			ret_date = data.at(location).restrict_due;
			return 6;
		}
		//if(isOverCapacity(capacity, size)) return 15;
		return 0;
	}
	else return 0;
}
int Faculty::do_op(string B, string _name, string _date, string& ret_date, string resrc_type, int size)
{
	int ret;
	get_member(_name);
	if(B == "B")
	{
		if(isExceed(n_book)) return 2;
		ret = isRestricted(_date);
		if(ret == true)
		{
			ret_date = data.at(location).restrict_due;
			return 6;
		}
		//if(isOverCapacity(capacity, size)) return 15;
		return 0;
	}
	else return 0;
}
int Graduate::do_op(string B, string _name, string _date, string& ret_date, string resrc_type, int size)
{
	int ret;
	get_member(_name);
	if(B == "B")
	{
		if(isExceed(n_book)) return 2;
		ret = isRestricted(_date);
		if(ret == true)
		{
			ret_date = data.at(location).restrict_due;
			return 6;
		}
		//if(isOverCapacity(capacity, size)) return 15;
		return 0;
	}
	else return 0;
}
