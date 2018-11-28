#include <vector>
#include <string>
using namespace std;

typedef struct M_INFO{
	int b_num;
	string restrict_due;
	int cap;
}M_INFO;
class Member{
	private:

	public:
		vector<string> name;
		vector<M_INFO> data;
		int location;
		void set_restrict_day(string _date, string d_day, string &ret_date); 
		bool isExceed(int N); 
		void final_state(string B, string resrc_type, int size);
		bool isRestricted(string _date);
		void get_member(string _name);  
		//bool isOverCapacity(int C);
		virtual int do_op(string, string, string, string&, string, int) = 0;
};

class Under : public Member{
	private:
		int capacity;
		int n_book;
	public:
		Under();
		int do_op(string B, string _name, string _date, string& ret_date, string r_type, int size);
};

class Graduate : public Member{
	private:
		int capacity;
		int n_book;
	public:
		Graduate();
		int do_op(string B, string _name, string _date, string& ret_date, string r_type, int size);
};

class Faculty : public Member{
	private:
		int capacity;
		int n_book;
	public:
		Faculty();
		int do_op(string B, string _name, string _date, string& ret_date, string r_type, int size);
};
