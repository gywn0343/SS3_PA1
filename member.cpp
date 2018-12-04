#include <iostream>
#include <vector>
#include <string>
#include "member.h"
using namespace std;

int Member::comp(string a, string b)
{
	int i;
	for(i=0;i<a.size();i++)
	{
		if(a.at(i) > b.at(i)) return 1;
		else if(a.at(i) < b.at(i)) return -1;
	}
	return 0;
}
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
	E_INFO e_tmp;
	e_tmp.due = "";
	e_tmp.size = 0;
	tmp.b_num = 0;
	tmp.cap = 0;
	tmp.restrict_due = "";
	tmp.e_info.push_back(e_tmp);
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

	int year, month, day, carry;

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
	if(day + n_day > 30) 
	{
		day += n_day + carry - 30;
		carry = 1;
	}
	else 
	{
		day += n_day;
		carry = 0;
	}

	if(month + n_month + carry > 12) 
	{
		month += n_month + carry - 12;
		carry = 1;
	}
	else 
	{
		month += n_month + carry;
		carry = 0;
	}
	year += n_year + carry;

	data.at(location).restrict_due = "";
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

	int ret = comp(_date, data.at(location).restrict_due);
	if(ret > 0) return 0;
	else return 1;
}
int Member::isOverdue(string now)
{
	list<string>::iterator it = data.at(location).due.begin();
	for(;it != data.at(location).due.end();++it)
	{
		if(*it == "") continue;
		if(comp(now, *it) > 0) return 1;
	}
	return 0;
}
void Member::final_state(string B, string resrc_type, int size, string due)
{
	if(B == "B")
	{
		data.at(location).b_num += 1;
		data.at(location).due.push_back(due);
		if(resrc_type == "E-book") 
		{
			E_INFO tmp;
			tmp.due = due;
			tmp.size = size;
			
			data.at(location).e_info.push_back(tmp);
			data.at(location).cap += size;
			data.at(location).b_num++;
		}
	}
	else
	{
		data.at(location).b_num -= 1;
		list<string>::iterator it = data.at(location).due.begin();
		for(;it != data.at(location).due.end();++it)
		{
			if(*it == due) 
			{
				data.at(location).due.erase(it);
				break;
			}
		}
		if(resrc_type == "E-book") 
		{
			list<E_INFO>::iterator iter = data.at(location).e_info.begin();
			for(;iter != data.at(location).e_info.end();iter++)
			{
				if(iter->size == size)
				{
					data.at(location).e_info.erase(iter);
					break;
				}
			}
			data.at(location).cap -= size;
			data.at(location).b_num--;
		}
	}
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

bool Member::isOverCapacity(int C, int size)
{
	if(data.at(location).cap + size > C) return true;
	return false;
}
void Member::update_ebook(string now)
{
	list<E_INFO>::iterator iter;
	for(iter = data.at(location).e_info.begin();iter != data.at(location).e_info.end();++iter)
	{
		if(comp(iter->due, now) < 0)
		{
			data.at(location).cap -= iter->size;
			data.at(location).b_num -= 1;
			iter = data.at(location).e_info.erase(iter);
			--iter;
		}
	}
}
int Under::do_op(string B, string _name, string _date, string& ret_date, string resrc_type, int size)
{
	int ret;
	get_member(_name);
	if(size > 0) update_ebook(_date);
	if(B == "B")
	{
		if(isExceed(n_book)) return 2;
		ret = isRestricted(_date);
		if(ret == true)
		{
			ret_date = data.at(location).restrict_due;
			return 6;
		}
		if(resrc_type == "E-book")
		{
			if(isOverCapacity(capacity, size)) return 15;
		}
		if(isOverdue(_date)) return 16;
		return 0;
	}
	else return 0;
}

int Faculty::do_op(string B, string _name, string _date, string& ret_date, string resrc_type, int size)
{
	int ret;
cout << _name << _date << resrc_type<< endl;
	get_member(_name);
	if(size > 0) update_ebook(_date);
	if(B == "B")
	{
		if(isExceed(n_book)) return 2;
		ret = isRestricted(_date);
		if(ret == true)
		{
			ret_date = data.at(location).restrict_due;
			return 6;
		}
		if(resrc_type == "E-book")
		{
			if(isOverCapacity(capacity, size)) return 15;
		}
		if(isOverdue(_date)) return 16;
		return 0;
	}
	else return 0;
}
int Graduate::do_op(string B, string _name, string _date, string& ret_date, string resrc_type, int size)
{
	int ret;

	get_member(_name);	
	
	if(size > 0) update_ebook(_date);
	if(B == "B")
	{
		if(isExceed(n_book)) return 2;
		ret = isRestricted(_date);
		if(ret == true)
		{
			ret_date = data.at(location).restrict_due;
			return 6;
		}
		if(resrc_type == "E-book")
		{
			if(isOverCapacity(capacity, size)) return 15;
		}
		if(isOverdue(_date)) return 16;
		return 0;
	}
	else return 0;
}
