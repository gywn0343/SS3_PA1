#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*struct info{
	int day;
	int month;
	int year;
};*/
class Member{
	private:
		vector<string> name;
		vector<struct info> restrict_due;
		vector<int> b_num;
		int location;
	public:
		int get_member(string _name)
		{
			int i;
			for(i=0;i<name.size();i++)
			{
				if(name.at(i) == _name) 
				{
					location = i;
					return i;
				}
			}
			struct info tmp;
			tmp.day = 0;
			tmp.year = 0;
			tmp.month = 0;
			name.push_back(_name);
			restrict_due.push_back(tmp);
			b_num.push_back(0);
			location = i;
			return i;
		}
		void print()
		{
			cout << name.at(location) << ": " << b_num.at(location) << " ";
			cout << restrict_due.at(location).year << "/";
			cout << restrict_due.at(location).month << "/";
			cout << restrict_due.at(location).day << endl;
		}	
		void get_res_due(string& ret_date)
		{
			struct info due = restrict_due.at(location);
			ret_date.push_back(due.year / 10 + '0');
			ret_date.push_back(due.year % 10 + '0');
			ret_date.push_back('/');
			ret_date.push_back(due.month / 10 + '0');
			ret_date.push_back(due.month % 10 + '0');
			ret_date.push_back('/');
			ret_date.push_back(due.day / 10 + '0');
			ret_date.push_back(due.day % 10 + '0');
		}
		void set_restrict_day(string _date, string d_day, string &ret_date)
		{
			struct info tmp;
			tmp.year = stoi(_date.substr(0, 2));
			tmp.month = stoi(_date.substr(3, 2));
			tmp.day = stoi(_date.substr(6, 2));
			struct info tmp2;
			tmp2.year = stoi(d_day.substr(0, 2));
			tmp2.month = stoi(d_day.substr(3, 2));
			tmp2.day = stoi(d_day.substr(6, 2));

			struct info ret;
			if(tmp.day < tmp2.day)
			{
				if(tmp.month <= tmp2.month)
				{
					ret.year = tmp.year - tmp2.year - 1;
					ret.month = 12 + (tmp.month - tmp2.month);
					ret.day = 30 + (tmp.day - tmp2.day);
				}
				else
				{
					ret.year = tmp.year - tmp2.year;
					ret.month = tmp.month - tmp2.month - 1;
					ret.day = 30 + (tmp.day + tmp2.day);
				}
			}
			else
			{
				ret.year = tmp.year - tmp2.year;
				ret.month = tmp.month - tmp2.month;
				ret.day = tmp.day - tmp2.day;
			}

			ret.year += tmp.year;
			ret.month += tmp.month;
			ret.day += tmp.day;
			restrict_due.at(location) = ret;
			get_res_due(ret_date);
		}
		bool isExceed(int N)
		{
			if(b_num.at(location) >= N) return true;
			return false;
		}
		bool isRestricted(string _date)
		{
			struct info tmp;  // today
			tmp.year = stoi(_date.substr(0, 2));
			tmp.month = stoi(_date.substr(3, 2));
			tmp.day = stoi(_date.substr(6, 2));
			struct info comp = restrict_due.at(location); // restructed due
			if(comp.year > tmp.year)
				return true;
			if(comp.month > tmp.month)
				return true;
			if(comp.day >= tmp.day)
				return true;
			return false;
		}
		void final_state(string B)
		{
			if(B == "B")
				b_num.at(location) += 1;
			else
				b_num.at(location) -= 1;
		}
};

class Under : public Member{
	private:
	public:
		int do_op(string B, string _name, string _date, string& ret_date)
		{
			int ret;
			get_member(_name);
//print();
			if(B == "B")
			{
				if(isExceed(1)) return 2;
				ret = isRestricted(_date);
				if(ret == true)
				{
					get_res_due(ret_date);
					return 6;
				}
				return 0;
			}
			else return 0;
		}
};
