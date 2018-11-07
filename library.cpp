#include <iostream>
#include <vector>
#include "library.h"
#include <fstream>
using namespace std;

int Library::comp(string line1, string line2)
{
	string tmp1;
	string tmp2;
	tmp1 = line1.substr(0, 8);
	tmp2 = line2.substr(2, 8);
	int i;
	for(i=0;i<8;i++)
	{
		if(tmp1.at(i) == tmp2.at(i)) continue;
		else if(tmp1.at(i) < tmp2.at(i)) return 1;
		else return 2;
	}
	return 1;
}
void Library::print_result(int n, int num1, int num2, string date)
{
	static int count = 0;
	string filePath = "output.dat";

	ofstream outFile;
	outFile.open(filePath, ios_base::app);
	if(outFile.is_open())
	{
		outFile << ++count << "	";
		outFile << n << "	";
		switch(n)
		{
			case 0:
				cout/*outFile*/ << result[0] << endl; return;
			case 1:
				cout/*outFile*/ << result[1] << endl; return;
			case 2:
				cout/*outFile*/ << result[2] << num1 << endl; return;
			case 3:
				cout/*outFile*/ << result[3] << endl; return;
			case 4:
				cout/*outFile*/ << result[4] << date << endl; return;
			case 5:
				cout/*outFile*/ << result[5] << date << endl; return;
			case 6:
				cout/*outFile*/ << result[6] << date << endl; return;
			case 7:
				cout/*outFile*/ << result[7] << date << endl; return;
			case 8:
				cout/*outFile*/ << result[8] << endl; return;
			case 9:
				cout/*outFile*/ << result[9];
				if(num1 < 10) cout/*outFile*/ << "0";
 				cout/*outFile*/ << num1 << " to "; 
				if(num2 < 10) cout/*outFile*/ << "0";
				cout/*outFile*/ << num2 << "." << endl; 
				return;
			case 10: 
				cout/*outFile*/ << result[10] << endl; return;
			case 11:
				cout/*outFile*/ << result[11] << endl; return;
			case 12:
				cout/*outFile*/ << result[12] << endl; return;
			case 13:
				cout/*outFile*/ << result[13] << num1 << "." << endl; return;
		}
		outFile.close();
	}
}

void Library::do_space()
{
	string _date, _time;
	int ret_time[2];
	int ret;
	if(space_type == "Seat")
	{
		ret = S.do_op(date.substr(0, 10), stoi(date.substr(11, 2)), space_num, state, member_name, member_num, time, member_type, ret_time);
		if(ret == 0) S.final_state(state, member_name, space_num, stoi(date.substr(11, 2)), time);
		print_result(ret, ret_time[0], ret_time[1], "");
	}
	else if(space_type == "StudyRoom")
	{
		ret = SR.do_op(date.substr(0, 10), stoi(date.substr(11, 2)), space_num, state, member_name, member_num, time, ret_time);
		if(ret == 0) SR.final_state(member_name, space_num, stoi(date.substr(11, 2)), time);
		print_result(ret, ret_time[0], ret_time[1], "");
	}
}
void Library::do_resource()
{
	int ret1, ret2;
	int due;
	string ret_date1;
	string ret_date2;
	int ret_num;
	if(resrc_type == "Book")
	{
		ret1 = B.do_op(state, resrc_name, member_name, date, ret_date1);
	}
	if(member_type == "Undergraduate")
	{
		ret2 = U.do_op(state, member_name, date, ret_date2);
		if(ret1 == 1)  // no kind of resources in here
		{
			print_result(1, 0, 0, "");
			return;
		}
		if(ret2 == 2)  // borrow # exceeded
		{
			print_result(2, 1, 0, "");
			return;
		}
		if(ret1 == 3)  // you never borrowed
		{
			print_result(3, 0, 0, "");
			return;
		}
		if(ret1 == 4)  // you already borrowed
		{
			print_result(4, 0, 0, ret_date1);
			return;
		}
		if(ret1 == 5)  // other people borrowed
		{
			print_result(5, 0, 0, ret_date1);
			return;
		}
		if(ret2 == 6)  // you are restricted
		{
			print_result(6, 0, 0, ret_date2);
			return;
		}
		if(ret1 == 7)  // delayed
		{
			string d_day;
			B.get_due(d_day);
			B.final_state(true, 14, "", "");
			U.set_restrict_day(date, d_day, ret_date1);
			U.final_state(state);
			print_result(7, 0, 0, ret_date1);
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
			print_result(0, 0, 0, "");
			return;
		}
	}
}

void Library::set_resource(string in, int cnt)
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

void Library::set_resource_info(string in, int cnt)
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
void Library::set_space_info(string in, int cnt)
{
	switch(cnt)
	{
		case 0:
			date = in;
			return;
		case 1:
			space_type = in;
			return;
		case 2:
			space_num = stoi(in);
			return;
		case 3:
			state = in;
			return;
		case 4:
			member_type = in;
			return;
		case 5:
			member_name = in;
			return;
		case 6:
			member_num = stoi(in);
			return;
		case 7:
			time = stoi(in);
			return;

	}
}

void Library::getInformation(string line, int op)
{
cout << line << endl;
	int i;
	int s, e;
	s = 0;
	int cnt = 0;
	for(i=0;i<line.size();i++)
	{
		if(line.at(i) == '\t') 
		{
			e = i-1;
			if(op == 1)
				set_resource_info(line.substr(s, e-s+1), cnt++);
			else if(op == 2)
				set_space_info(line.substr(s, e-s+1), cnt++);
			else
				set_resource(line.substr(s, e-s+1), cnt++);
			s = i+1;
		}
	}
	if(op == 1)
	{
		set_resource_info(line.substr(s, i-s+1), cnt);
	}
	else if(op == 2)
	{
		set_space_info(line.substr(s, i-s+1), cnt);
	}
	else
		set_resource(line.substr(s, i-s+1), cnt);
}

Library::Library()
{
	string filePath = "output.dat";
	string filePath1, filePath2;
	string line;
	ofstream outFile(filePath.data());
	if(outFile.is_open())
	{
		outFile << "OP_#	Return_code	Description" << endl;
		outFile.close();
	}
	filePath = "resource.dat";
	ifstream resourceFile(filePath.data());
	int cnt1, cnt2;
	if(resourceFile.is_open())
	{
		cnt1 = 0;
		while(getline(resourceFile, line))
		{
			if(cnt1++ == 0) continue;
			getInformation(line, 0);
		}
		resourceFile.close();
	}
	filePath1 = "input1.dat";
	filePath2 = "input2.dat";
	ifstream openFile1(filePath1.data());  // resource
	ifstream openFile2(filePath2.data());  // space

	int flag1 = 0;
	int flag2 = 0;
	int ret;
	cnt1 = 0;
	if(openFile2.is_open() && openFile1.is_open())
	{
		while(1)
		{
			if(flag1 == 0)
			{
				getline(openFile1, line1);
				if(line1 == "") flag1 = 2; // flag == 2 -> end of file
			}
			if(flag2 == 0)
			{
				getline(openFile2, line2);
				if(line2 == "") flag2 = 2;
			}
			if(cnt1++ == 0) continue;

			if(flag1 == 2 && flag2 == 2) break;

			if(flag1 != 2 && flag2 != 2)
				ret = comp(line1, line2);
			if(ret == 1 || flag2 == 2) 
			{                               // flag == 1
				if(flag2 == 0) flag2 = 1;   // not operated -> so you cannot read next line
				
				getInformation(line1, 1);
				do_resource();
				flag1 = 0;                  // flag == 0 -> read next line
			}
			else if(ret == 2 || flag1 == 2)
			{
				if(flag1 == 0) flag1 = 1;
				
				getInformation(line2, 2);
				do_space();
				flag2 = 0;
			}
		}
		openFile1.close();
		openFile2.close();
	}
}
