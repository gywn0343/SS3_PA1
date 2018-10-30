#include <iostream>
#include <string>
#include <vector>
#include "resource.h"
using namespace std;


void Resource::print()
{
	int i;
	for(i=0;i<name.size();i++)
	{
		cout << name.at(i) << ": " << state.at(i) << " ";
		cout << (date.at(i)).year << "/" << (date.at(i)).month << "/" << (date.at(i)).day;
		cout << " ~ ";
		cout << (due_date.at(i)).year << "/" << (due_date.at(i)).month << "/" << (due_date.at(i)).day;
		cout << endl;
	}
	cout << "------------------" << endl;
}

void Resource::set_date(string _date, int due)
{
	(date.at(location)).year = stoi(_date.substr(0, 2));
	(date.at(location)).month = stoi(_date.substr(3, 2));
	(date.at(location)).day = stoi(_date.substr(6, 2));

	struct info tmp = date.at(location);
	if(tmp.day + due > 30)
	{
		if(tmp.month + 1 > 12)
		{
			(due_date.at(location)).year = tmp.year + 1;
			(due_date.at(location)).month = 1;
		}
		else
		{
			(due_date.at(location)).month = tmp.month + 1;
			(due_date.at(location)).year = tmp.year;
		}
		(due_date.at(location)).day = (tmp.day + due) % 30;
	}
	else
	{
		(due_date.at(location)).day = tmp.day + due;
		(due_date.at(location)).month = tmp.month;
		(due_date.at(location)).year = tmp.year;
	}
}

void Resource::struct_to_string(struct info due, string &ret_date)
{
	ret_date.push_back(due.year / 10 + '0');
	ret_date.push_back(due.year % 10 + '0');
	ret_date.push_back('/');
	ret_date.push_back(due.month / 10 + '0');
	ret_date.push_back(due.month % 10 + '0');
	ret_date.push_back('/');
	ret_date.push_back(due.day / 10 + '0');
	ret_date.push_back(due.day % 10 + '0');
}
void Resource::add_resource(string _name)
{
	struct info tmp;
	tmp.year = 0;
	tmp.month = 0;
	tmp.day = 0;
	name.push_back(_name);
	state.push_back(true);
	date.push_back(tmp);
	due_date.push_back(tmp);
	mem_name.push_back("");
}
int Resource::isInLibrary(string _name)
{
	for(int i=0;i<name.size();i++)
	{
		if(name.at(i) == _name)
		{
			location = i;
			return 0;
		}
	}
	return -1;
}
int Resource::isAvailable(string member_name, int due, string _date, string& ret_date)
{
	if(state.at(location) == true)
	{
		return 0;
	}
	else
	{
		if(mem_name.at(location) == member_name)
		{
			struct_to_string(date.at(location), ret_date);
			return 4;
		}
		else
		{
			struct_to_string(due_date.at(location), ret_date);
			return 5;
		}
	}
}
void Resource::final_state(bool in, int due, string member_name, string _date)
{
	state.at(location) = in;
	if(member_name != "") 
		mem_name.at(location) = member_name;
	if(_date != "")
		set_date(_date, due);
	print();
}

int Resource::isGoodReturn(string member_name, string _date)
{
	if(mem_name.at(location) != member_name)
	{
		return 3;
	}
	int year, month, day;
	year = stoi(_date.substr(0, 2));
	month = stoi(_date.substr(3, 2));
	day = stoi(_date.substr(6, 2));
	if(year > (due_date.at(location)).year)
		return 7;
	if(month > (due_date.at(location)).month)
		return 7;
	if(day > (due_date.at(location)).day)
		return 7;
	return 0;
}
int Book::do_op(string B, string _name, int due, string mem_name, string now, string &ret_date)
{
	int ret;
	if(isInLibrary(_name) == -1) return 1;
	if(B == "B")
	{
		ret = isAvailable(mem_name, due, now, ret_date);
		if(ret == 4 || ret == 5) return ret; 
	}
	else 
	{
		ret = isGoodReturn(mem_name, now);
		if(ret == 7 || ret == 3) return ret;
	}
	return 0;
}
