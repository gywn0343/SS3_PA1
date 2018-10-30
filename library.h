#include <string>
#include <vector>
#include "resource.h"
#include "member.h"
#include <fstream>
#ifndef _LIBRARY_H
#define _LIBRARY_H
using namespace std;

class Library{
	private:
		string result[8] = {
			"Success.",
			"Non exist resource.",
			"Exeeds your possible number of borrow. possible# of borrows: ",
			"You did not borrow this book.",
			"You already borrowed this book at ",
			"Other member already borrowed this book. This book will be returned at ",
			"Restricted member until ",
			"Delayed return. You'll be restricted until "
		};
		Book B;
		Under U;
		string member_name;
		string resrc_name;
		string date;
		string state;  // Borrow=0 or Return=1
		string resrc_type;  // Book=1 or others
		string member_type; // Under or others
		void print_result(int n, int num, string date)
		{
			static int count = 0;
			cout << ++count << "	";
			cout << n << "	";
			switch(n)
			{
				case 0:
					cout << result[0] << endl; return;
				case 1:
					cout << result[1] << endl; return;
				case 2:
					cout << result[2] << num << endl; return;
				case 3:
					cout << result[3] << endl; return;
				case 4:
					cout << result[4] << date << endl; return;
				case 5:
					cout << result[5] << date << endl; return;
				case 6:
					cout << result[6] << date << endl; return;
				case 7:
					cout << result[7] << date << endl; return;
			}
		}
		void do_operation()
		{
			int ret1, ret2;
			int due;
			string ret_date1;
			string ret_date2;
			int ret_num;
			if(resrc_type == "Book")
			{
				ret1 = B.do_op(state, resrc_name, member_name, date, ret_date1);
				/*if(ret == 1)  // no kind of resources in here
				{
					print_result(1, 0, "");
					return;
				}
				if(ret == 4)  // you already borrowed
				{
					print_result(4, 0, ret_date);
					return;
				}
				if(ret == 5)  // other people borrowed
				{
					print_result(5, 0, ret_date);
					return;
				}
				if(ret == 3)  // you never borrowed
				{
					print_result(3, 0, "");
					return;
				}
				if(ret == 7)  // delayed
				{
					print_result(7, 0, ret_date);
					string d_day;
					B.get_due(d_day);
					U.set_restrict_day(date, d_day);
					return;
				}*/
			}
			if(member_type == "Undergraduate")
			{
				ret2 = U.do_op(state, member_name, date, ret_date2);
				if(ret1 == 1)  // no kind of resources in here
				{
					print_result(1, 0, "");
					return;
				}
				if(ret2 == 6)  // you are restricted
				{
					print_result(6, 0, ret_date2);
					return;
				}
				if(ret2 == 2)  // borrow # exceeded
				{
					print_result(2, 1, "");
					return;
				}


				if(ret1 == 4)  // you already borrowed
				{
					print_result(4, 0, ret_date1);
					return;
				}
				if(ret1 == 5)  // other people borrowed
				{
					print_result(5, 0, ret_date1);
					return;
				}
				if(ret1 == 3)  // you never borrowed
				{
					print_result(3, 0, "");
					return;
				}
				if(ret1 == 7)  // delayed
				{
					string d_day;
					B.get_due(d_day);
					B.final_state(true, 14, "", "");
					U.set_restrict_day(date, d_day, ret_date1);
					U.final_state(state);
					print_result(7, 0, ret_date1);
					return;
				}
				if(ret2 == 0 || ret1 == 7)  // success or delayed return
				{
					if(state == "B")
					{
						B.final_state(false, 14, member_name, date);
						U.final_state(state);
					}
					else
					{
						B.final_state(true, 14, "", "");
					}
					print_result(0, 0, "");
					return;
				}
			}

		}
		void set_resource(string in, int cnt)
		{
			static string rsrc;
			if(cnt == 0)
			{
				rsrc = in;
			}
			else
			{
				if(rsrc == "Book")
				{
					B.add_resource(in);
				}
			}
		}
		void set_info(string in, int cnt)
		{
			switch(cnt)
			{
				case 0:
					date = in;
					return;
				case 1:
					resrc_type = in;
					return;
				case 2:
					resrc_name = in;
					return;
				case 3:
					state = in;
					return;
				case 4:
					member_type = in;
					return;
				case 5:
					member_name = in;
			}
		}
		void getInformation(string line, int op)
		{
			int i;
			int s, e;
			s = 0;
			int cnt = 0;
			for(i=0;i<line.size();i++)
			{
				if(line.at(i) == '\t') 
				{
					e = i-1;
					if(op == 0)
						set_info(line.substr(s, e-s+1), cnt++);
					else
						set_resource(line.substr(s, e-s+1), cnt++);
					s = i+1;
				}
			}
			if(op == 0)
			{
				set_info(line.substr(s, i-s+1), cnt);
cout << line << endl;
				do_operation();
			}
			else
				set_resource(line.substr(s, i-s+1), cnt);
		}
	public:
		Library()
		{
			string filePath = "resource.dat";
			ifstream openFile1(filePath.data());
			int cnt;
			if(openFile1.is_open())
			{
				string line;
				cnt = 0;
				while(getline(openFile1, line))
				{
					if(cnt++ == 0) continue;
					getInformation(line, 1);
				}
				openFile1.close();
			}
			filePath = "input.dat";
			ifstream openFile2(filePath.data());
			if(openFile2.is_open())
			{
				string line;
				cnt = 0;
				while(getline(openFile2, line))
				{
					if(cnt++ == 0) continue;
					getInformation(line, 0);
				}
				openFile2.close();
			}

		}
		
		
};

#endif
