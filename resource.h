#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;
#ifndef _RESOURCE_H
#define _RESOURCE_H
#define N_MEMBER 100
typedef struct resrc_info{
	string month;
	string mem_name;
	bool state;
	string date;
	string due_date;
}INFO;

class Resource{
	private:
	public:
		vector<string> name;
		int location;
		int isInLibrary(string _name);
		int isLate(string _date, string due_date);
		void set_date(string _date, int due, string&, string&);
		virtual void add_resource(string _name, int s) = 0;
		virtual void final_state(bool in, int due, string member_name, string _date) = 0;
		virtual int do_op(string B, string _name, string mem_name, string now, string &ret_date, int& size, string& d_day, int due) = 0;
		virtual void get_due(string& d_day, string) = 0;
};

class Book : public Resource{
	private:
		vector<INFO> data;
		int isAvailable(string member_name, string _date, string& ret_date);
	public:
		void final_state(bool in, int due, string member_name, string _date);
		void add_resource(string _name, int s);
		int do_op(string B, string _name, string mem_name, string now, string &ret_date, int& size, string& d_day, int due);
		void get_due(string& d_day, string mem_name)
		{
			d_day = data.at(location).due_date;
		}
		
};
class Magazine : public Resource{
	private:
		vector<list<INFO>> data;
		string month_rec;
		int isAvailable(string member_name, string _date, string& ret_date, string month);
		int check_month(string, string, string);
	public:
		void add_resource(string _name, int s);
		void final_state(bool in, int due, string member_name, string _date);
		int do_op(string B, string _name, string mem_name, string now, string &ret_date, int& size, string& d_day, int due);
		void get_due(string& d_day, string mem_name)
		{
			list<INFO>::iterator iter;
			for(iter = data.at(location).begin();iter != data.at(location).end();++iter)
			{
				if(iter->month == month_rec) break;
			}
			if(iter == data.at(location).end()) d_day = "99/99/99";
			else
				d_day = iter->due_date;
		}
};

class E_book : public Resource{
	private:
		vector<list<INFO>> data;
		vector<int> size;
		int isAvailable(string member_name, string _date, string& ret_date);
		void flush_ebook(string now);
	public:
		void add_resource(string _name, int size);
		void final_state(bool in, int due, string member_name, string _date);
		int do_op(string B, string _name, string mem_name, string now, string &ret_date, int& size, string& d_day, int due);
		void get_due(string& d_day, string mem_name)
		{
			list<INFO>::iterator iter;

			for(iter = data.at(location).begin();iter != data.at(location).end();++iter)
			{
				if(iter->mem_name == mem_name) break;
			}
			if(iter == data.at(location).end()) d_day = "99/99/99";
			else
				d_day = iter->due_date;
		}
};

#endif
