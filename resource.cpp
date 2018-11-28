#include <iostream>
#include <string>
#include <vector>
#include "resource.h"
using namespace std;

void Book::add_resource(string _name)
{
	INFO data_tmp;
	data_tmp.mem_name = "";
	data_tmp.state = true;
	data_tmp.date = "";
	data_tmp.due_date = "";
	name.push_back(_name);
	data.push_back(data_tmp);
}
void Magazine::add_resource(string _name)
{
	INFO *data_tmp = new INFO[N_MGZ];
	int i;
	for(i=0;i<N_MGZ;i++)
	{
		data_tmp[i].mem_name = "";
		data_tmp[i].state = true;
		data_tmp[i].date = "";
		data_tmp[i].due_date = "";
		data_tmp[i].month = "";
	}
	name.push_back(_name);
	data.push_back(data_tmp);
}
/*void E_book::add_resource(string _name, int size)
{
	INFO data_tmp;
	data_tmp.mem_name = "";
	data_tmp.state = true;
	data_tmp.date = "";
	data_tmp.due_date = "";
	data_tmp.size = size;
	name.push_back(_name);
	data.push_back(data_tmp);
}*/
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
	


	for(i=0;i<N_MGZ;i++)
	{
		if(data.at(location)[i].month == month)
		{
			if(data.at(location)[i].mem_name == member_name) 
			{
				ret_date = data.at(location)[i].date;
				return 4;
			}
			else
			{
				ret_date = data.at(location)[i].due_date;
				return 5;
			}
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
void Magazine::final_state(bool in, int due, string member_name, string _date)
{
	int i;

	if(in == false) // Borrow
	{
		for(i=0;i<N_MGZ;i++)
		{
			if(data.at(location)[i].month == "")
			{
				data.at(location)[i].state = in;
				data.at(location)[i].mem_name = member_name;
				set_date(_date, due, data.at(location)[i].date, data.at(location)[i].due_date);
				data.at(location)[i].month = month_rec;
				return;
			}
		}
	}
	else // Return
	{
		for(i=0;i<N_MGZ;i++)
		{
			if(data.at(location)[i].month == month_rec)
			{
				data.at(location)[i].state = in;
				data.at(location)[i].mem_name = "";
				data.at(location)[i].month = "";
				return;
			}
		}
	}
}

int Resource::isGoodReturn(string _date, string due_date)
{
	int i;
	for(i=0;i<_date.size();i++)
	{
		if(_date.at(i) < due_date.at(i)) return 0;
		if(_date.at(i) > due_date.at(i)) return 7;
	}
	return 0;
}
int Book::do_op(string B, string _name, string mem_name, string now, string &ret_date, int size)
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
		ret = isGoodReturn(now, data.at(location).due_date);
		if(ret == 7) return ret;
	}
	return 0;
}
/*int E_book::do_op(string B, string _name, string mem_name, string now, string &ret_date, int size)
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
		ret = isGoodReturn(now, data.at(location).due_date);
		if(ret == 7) return ret;
	}
	return 0;
}*/
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
int Magazine::do_op(string B, string _name, string mem_name, string now, string &ret_date, int size)
{
	int ret;
	int s, e;

	string s_b = "[";
	string e_b = "]";
	s = _name.find(s_b);
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
		for(i=0;i<N_MGZ;i++)
		{
			if(data.at(location)[i].month == month) break;
		}
		if(data.at(location)[i].mem_name != mem_name)
			return 3;
		ret = isGoodReturn(now, data.at(location)[i].due_date);
		if(ret == 7) return ret;
	}
	return 0;
}





