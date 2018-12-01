#include <string>
#include "resource.h"
#include "member.h"
#include "space.h"
#include <fstream>
#ifndef _LIBRARY_H
#define _LIBRARY_H
using namespace std;
enum {DATE_EXCP, SPACE_TYPE_EXCP, OPERATION_EXCP, MEMBER_TYPE_EXCP, MEMBER_NAME_EXCP, TIME_EXCP};

class Library{
	private:
		string result[16] = {
			"Success.",
			"Non exist resource.", //1
			"Exeeds your possible number of borrow. Possible # of borrows: ", //2
			"You did not borrow this book.", //3
			"You already borrowed this book at ", // 4
			"Other member already borrowed this book. This book will be returned at ", // 5
			"Restricted member until ", // 6
			"Delayed return. You'll be restricted until ", // 7
			"Invalid space id.", // 8
			"This space is not available now. Available from ", // 9
			"You did not borrow this space.", // 10
			"You already borrowed this kind of space.", // 11
			"Exceed available number.", // 12
			"Exceed available time.", // 13
			"There is no remain space. This space is available after ", // 14
			"Exceeds your storage capacity." // 15
		};
		string exception[6] = {
			"Date out of range",
			"Non-exist space type",
			"Non-exist operation",
			"Non-exist member type",
			"Member name with numbers",
			"Negative time"
		};
		Member *M;
		Resource *R;
		Under U;
		Graduate G;
		Faculty F;
		Book B;
		Magazine Mag;
		E_book E;
		Seat S;
		int write_ptr;
		StudyRoom SR;
		string member_name;
		string resrc_name;
		string date;
		string state; 
		string resrc_type;  
		string member_type; 
		void get_class();
		int LOAN_PERIOD;
		int B_NUM;
		int ebook_size;
		string space_type;
		string line1, line2;
		void check_member_excp(string in);
		void print_exception(int state);
		void check_date_range(string in);
		int space_num;
		int time;
		int member_num;
		void print_result(int n, int num1, int num2, string date);
		void do_resource();
		void do_space();
		int comp(string, string);
		void set_resource(string in, int cnt);
		int set_resource_info(string in, int cnt);
		int set_space_info(string in, int cnt, int error);
		int getInformation(string line, int op);
	public:
		Library();
		
};

#endif
