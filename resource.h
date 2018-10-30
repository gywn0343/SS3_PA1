#include <iostream>
#include <string>
using namespace std;
#ifndef _RESOURCE_H
#define _RESOURCE_H

class Resource{
	private:
		vector<string> name;
		vector<string> mem_name;
		struct info{
			int day; 
			int month; 
			int year;
		};
		vector<bool> state;
		vector<struct info> date;
		vector<struct info> due_date;
		int location;
		void print()
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
	public:
		Resource()
		{
		//	cnt = 0;
		}
		void add_resource(string _name)
		{
			struct info tmp;
			name.push_back(_name);
			state.push_back(true);
			date.push_back(tmp);
			due_date.push_back(tmp);
			mem_name.push_back("");
		}
		void printResource()
		{
			for(auto i : name)
			{
				cout << i << endl;
			}
		}
		int isInLibrary(string _name)
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
		void set_date(string _date, int due)
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
		void struct_to_string(struct info due, string &ret_date)
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
		int isAvailable(string member_name, int due, string _date, string& ret_date)
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
		void final_state(bool in, int due, string member_name, string _date)
		{
			state.at(location) = in;
			if(member_name != "") 
				mem_name.at(location) = member_name;
			if(_date != "")
				set_date(_date, due);
			print();
		}
		int isGoodReturn(string member_name, string _date)
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
};

class Book : public Resource{
	private:
		struct info checkout;
		struct info checkin;
		int rent_day;
	public:
		Book() : Resource()
		{
		
		}
		int do_op(string B, string _name, int due, string mem_name, string now, string &ret_date)
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
		
};

#endif
