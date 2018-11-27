#include <iostream>
#include <string>
#include <vector>
using namespace std;
#ifndef _RESOURCE_H
#define _RESOURCE_H
#define N_MGZ 100
typedef struct resrc_info{
	string month;
	string mem_name;
	bool state;
	string date;
	string due_date;
	int size;
}INFO;

class Resource{
	private:
	public:
		vector<string> name;
		int location;
		int isInLibrary(string _name);
		int isGoodReturn(string _date, string due_date);
		void set_date(string _date, int due, string&, string&);
};

class Book : public Resource{
	private:
		vector<INFO> data;
		int isAvailable(string member_name, string _date, string& ret_date);
	public:
		void final_state(bool in, int due, string member_name, string _date);
		void add_resource(string _name);
		int do_op(string B, string _name, string mem_name, string now, string &ret_date);
		void get_due(string& d_day)
		{
			d_day = data.at(location).due_date;
		}
		
};
class Magazine : public Resource{
	private:
		vector<INFO*> data;
		string month_rec;
		int isAvailable(string member_name, string _date, string& ret_date, string month);
		int check_month(string, string);
	public:
		void add_resource(string _name);
		void final_state(bool in, int due, string member_name, string _date);
		int do_op(string B, string _name, string mem_name, string now, string &ret_date);
		void get_due(string& d_day)
		{
			int i;
			for(i=0;i<N_MGZ;i++)
			{
				if(data.at(location)[i].month == month_rec) break;
			}
			d_day = data.at(location)[i].due_date;
		}
};

/*class E_book : public Resource{
	private:
		vector<INFO> data;
	public:
		void add_resource(string _name, int size);
};*/

#endif
