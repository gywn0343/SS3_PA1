#include <iostream>
#include <string>
#include <vector>
using namespace std;
#ifndef _RESOURCE_H
#define _RESOURCE_H
struct info{
	int day; 
	int month; 
	int year;
};

class Resource{
	private:
		vector<string> name;
		vector<string> mem_name;
		vector<bool> state;
		vector<struct info> date;
		vector<struct info> due_date;
		int location;
		void print();
		void set_date(string _date, int due);
		void struct_to_string(struct info due, string &ret_date);
	public:
		void add_resource(string _name);
		int isInLibrary(string _name);
		int isAvailable(string member_name, string _date, string& ret_date);
		void final_state(bool in, int due, string member_name, string _date);
		int isGoodReturn(string member_name, string _date);
		void get_due(string& d_day)
		{
			struct_to_string(due_date.at(location), d_day);
		}
};

class Book : public Resource{
	private:
	public:
		int do_op(string B, string _name, string mem_name, string now, string &ret_date);
		
};

#endif
