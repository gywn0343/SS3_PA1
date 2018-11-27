#include <iostream>
#include <string>
#include <vector>
#include <list>
#include "resource.h"
using namespace std;

void Book::add_resource(string _name, int s)
{
	INFO data_tmp;
	data_tmp.mem_name = "";
	data_tmp.state = true;
	data_tmp.date = "";
	data_tmp.due_date = "";
	name.push_back(_name);
	data.push_back(data_tmp);
}
void Magazine::add_resource(string _name, int s)
{
	INFO data_tmp;
	list<INFO> list_tmp;

	data_tmp.mem_name = "";
	data_tmp.state = true;
	data_tmp.date = "";
	data_tmp.due_date = "";
	data_tmp.month = "";
	list_tmp.push_back(data_tmp);

	name.push_back(_name);
	data.push_back(list_tmp);
}
void E_book::add_resource(string _name, int _size)
{
	INFO data_tmp;
	list<INFO> list_tmp;
	
	data_tmp.mem_name = "";
	data_tmp.date = "";
	data_tmp.due_date = "";
	list_tmp.push_back(data_tmp);
	
	name.push_back(_name);
	size.push_back(_size);
	data.push_back(list_tmp);
}
int Resource::isInLibrary(string _name)
{
	for(int i=0;i<name.size();i++)
	{
		if(name.at(i) == _name)
		{
			return i;
		}
	}
	return -1;
}
int Book::isAvailable(string member_name, string _date, string& ret_date)
{
	if(data.at(location).state == true)
	{
		return 0;
	}
	else
	{
		if(data.at(location).mem_name == member_name)
		{
			ret_date = data.at(location).date;
			return 4;
		}
		else
		{
			ret_date = data.at(location).due_date;
			return 5;
		}
	}
}

int Magazine::isAvailable(string member_name, string _date, string& ret_date, string month)
{
	int i, tmp;

	list<INFO>::iterator iter;
	for(iter = data.at(location).begin();iter != data.at(location).end();++iter)
	{
		if(iter->month == month)
		{
			if(iter->mem_name == member_name) 
			{
				ret_date = iter->date;
				return 4;
			}
			else
			{
				ret_date = iter->due_date;
				return 5;
			}
		}
	}

	return 0;
}
int E_book::isAvailable(string member_name, string _date, string& ret_date)
{
	list<INFO>::iterator iter;
	for(iter = data.at(location).begin();iter != data.at(location).end();++iter)
	{
		if(iter->mem_name == member_name)
		{
			ret_date = iter->date;
			return 4;
		}
	}

	return 0;
}
void Resource::set_date(string _date, int due, string& date, string& due_date)
{
	date = _date;	
	due_date = "";
	int tyear = stoi(_date.substr(0, 2));
	int tmonth = stoi(_date.substr(3, 2));
	int tday = stoi(_date.substr(6, 2));
	due--;
	int year, month, day;
	if(tday + due > 30)
	{
		if(tmonth + 1 > 12)
		{
			year = tyear + 1;
			month = 1;
		}
		else
		{
			month = tmonth + 1;
			year = tyear;
		}
		day = (tday + due) % 30;
	}
	else
	{
		day = tday + due;
		month = tmonth;
		year = tyear;
	}
	if(year < 10) due_date += "0";
	due_date += to_string(year);
	due_date += "/";
	if(month < 10) due_date += "0";
	due_date += to_string(month);
	due_date += "/";
	if(day < 10) due_date += "0";
	due_date += to_string(day);

}
void Book::final_state(bool in, int due, string member_name, string _date)
{
	data.at(location).state = in;
	if(member_name != "") 
		data.at(location).mem_name = member_name;
	if(_date != "")
		set_date(_date, due, data.at(location).date, data.at(location).due_date);
}
void E_book::final_state(bool in, int due, string member_name, string _date)
{

	INFO tmp;
	tmp.mem_name = member_name;
	set_date(_date, due, tmp.date, tmp.due_date);
	data.at(location).push_back(tmp);
}
void Magazine::final_state(bool in, int due, string member_name, string _date)
{
	list<INFO>::iterator iter;

	if(in == false) // Borrow
	{
		INFO tmp;
		tmp.state = in;
		tmp.mem_name = member_name;
		set_date(_date, due, tmp.date, tmp.due_date);
		tmp.month = month_rec;
		data.at(location).push_back(tmp);

		return;
	}
	else // Return
	{

		for(iter = data.at(location).begin();iter != data.at(location).end();++iter)
		{
			if(iter->month == month_rec)
			{
				iter = data.at(location).erase(iter);
				iter--;
				return;
			}
		}
	}
}

int Resource::isLate(string a, string b) // is 'a' late than 'b' ? a > b ?
{
	int i;
	for(i=0;i<a.size();i++)
	{
		if(a.at(i) < b.at(i)) return 0;
		if(a.at(i) > b.at(i)) return 1;
	}
	return 0;
}
int Book::do_op(string B, string _name, string mem_name, string now, string &ret_date, int& size, string& d_day, int due)
{
	int ret;
	if((ret = isInLibrary(_name)) == -1) return 1;
	else location = ret;
	if(B == "B")
	{
		ret = isAvailable(mem_name, now, ret_date);
		if(ret == 4 || ret == 5) return ret; 
	}
	else 
	{
		if(data.at(location).mem_name != mem_name)
			return 3;
		ret = isLate(now, data.at(location).due_date);
		if(ret == true) return 7;
	}
	return 0;
}

void E_book::flush_ebook(string now)
{
	list<INFO>::iterator iter;

	int i;
	for(i=0;i<data.size();i++)
	{
		for(iter = data.at(i).begin();iter != data.at(i).end();++iter)
		{
			if(iter->due_date == "") continue;
			if(isLate(now, iter->due_date))
			{
				iter = data.at(i).erase(iter);
				iter--;
			}
		}
	}

}
int E_book::do_op(string B, string _name, string mem_name, string now, string &ret_date, int& _size, string& d_day, int due)
{
	int ret, i;
	if((ret = isInLibrary(_name)) == -1) return 1;
	else location = ret;


	flush_ebook(now);

	ret = isAvailable(mem_name, now, ret_date);
	if(ret == 4) return ret; 

	_size = size.at(location);
	string tmp;
	set_date(now, due, tmp, d_day);
	return 0;
}

int Magazine::check_month(string _date, string month)
{
	int n_year = stoi(_date.substr(0, 2));
	int n_month = stoi(_date.substr(3, 2));
	int b_year = stoi(month.substr(0, 2));
	int b_month = stoi(month.substr(3, 2));

	if(n_year < b_year)
		return 1;          // no such month's magazine (requesting future mag)
	else if(n_year > b_year)
	{
		if(n_year == b_year + 1)	
		{
			if(n_month > b_month) return 1; // req expired mag
		}
		else return 1; // requesting expired magazine
	}
	else
	{
		if(n_month < b_month) // requesting future mag
			return 1;
	}
}
int Magazine::do_op(string B, string _name, string mem_name, string now, string &ret_date, int& _size, string& d_day, int due)
{
	int ret;
	int s, e;
	string s_b = "[";
	string e_b = "]";
	s = _name.find(s_b);
	if(s == -1)
	{
		return 1;
	}
	e = _name.find(e_b);
	string month = _name.substr(s + 1, e - s - 1);

	month_rec = month;
	ret = check_month(now, month);
	if(ret == 1) return ret;

	_name = _name.substr(0, s);
	if((ret = isInLibrary(_name)) == -1) return 1;
	else location = ret;


	int i;
	if(B == "B")
	{
		ret = isAvailable(mem_name, now, ret_date, month);
		if(ret == 4 || ret == 5) return ret; 
	}
	else 
	{
		list<INFO>::iterator iter;
		for(iter = data.at(location).begin();iter != data.at(location).end();++iter)
		{
			if(iter->month == month) break;
		}
		if(iter->mem_name != mem_name)
			return 3;
		ret = isLate(now, iter->due_date);
		if(ret == true) return 7;
	}
	return 0;
}





