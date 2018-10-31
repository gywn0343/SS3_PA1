#include <vector>
#include <string>
using namespace std;

struct data{
	int year;
	int day;
	int month;
};
class Member{
	private:
		vector<string> name;
		vector<struct data> restrict_due;
		vector<int> b_num;
		int location;
	public:
		int get_member(string _name);
		void get_res_due(string& ret_date);
		void set_restrict_day(string _date, string d_day, string &ret_date);
		bool isExceed(int N);
		bool isRestricted(string _date);
		void final_state(string B);
};

class Under : public Member{
	private:
	public:
		int do_op(string B, string _name, string _date, string& ret_date);
};
