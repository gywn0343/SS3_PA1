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
	string filePath = "output.dat";

	ofstream outFile;
	outFile.open(filePath, ios_base::app);
	if(outFile.is_open())
	{
		outFile << ++write_ptr << "	";
		outFile << n << "	";
		switch(n)
		{
			case 0:
				outFile << result[0] << endl; return;
			case 1:
				outFile << result[1] << endl; return;
			case 2:
				outFile << result[2] << num1 << endl; return;
			case 3:
				outFile << result[3] << endl; return;
			case 4:
				outFile << result[4] << date << endl; return;
			case 5:
				outFile << result[5] << date << endl; return;
			case 6:
				outFile << result[6] << date << endl; return;
			case 7:
				outFile << result[7] << date << endl; return;
			case 8:
				outFile << result[8] << endl; return;
			case 9:
				outFile << result[9];
				if(num1 < 10) outFile << "0";
 				outFile << num1 << " to "; 
				if(num2 < 10) outFile << "0";
				outFile << num2 << "." << endl; 
				return;
			case 10:
				outFile << result[10] << endl; return;
			case 11: 
				outFile << result[11] << endl; return;
			case 12:
				outFile << result[12] << endl; return;
			case 13:
				outFile << result[13] << endl; return;
			case 14:
				outFile << result[14] << num1 << "." << endl; return;
			case 15:
				outFile << result[15] << endl; return;
			case 16:
				outFile << result[16] << endl; return;
		}
		outFile.close();
	}
}
void Library::print_exception(int state)
{
	string filePath = "output.dat";

	ofstream outFile;
	outFile.open(filePath, ios_base::app);
	if(outFile.is_open())
	{
		outFile << ++write_ptr << "	";
		outFile << "-1	";
		switch(state)
		{
			case DATE_EXCP:
				outFile << exception[DATE_EXCP] << endl; return;
			case SPACE_TYPE_EXCP:
				outFile << exception[SPACE_TYPE_EXCP] << endl; return;
			case OPERATION_EXCP:
				outFile << exception[OPERATION_EXCP] << endl; return;
			case MEMBER_TYPE_EXCP:
				outFile << exception[MEMBER_TYPE_EXCP] << endl; return;
			case MEMBER_NAME_EXCP:
				outFile << exception[MEMBER_NAME_EXCP] << endl; return;
			case TIME_EXCP:
				outFile << exception[TIME_EXCP] << endl; return;
		}
		outFile.close();
	}
}
void Library::get_class()
{
	if(member_type == "Undergraduate") 
	{	
		M = &U;
		LOAN_PERIOD = 14;
		B_NUM = 1;
	}
	else if(member_type == "Graduate") 
	{	
		M = &G;
		LOAN_PERIOD = 30;
		B_NUM = 5;
	}
	else if(member_type == "Faculty")
	{	
		M = &F;
		LOAN_PERIOD = 30;
		B_NUM = 10;
	}

	if(resrc_type == "Book") R = &B;
	else if(resrc_type == "Magazine") R = &Mag;
	else if(resrc_type == "E-book") R = &E;
}

void Library::do_resource()
{
	int ret1, ret2;
	int due;
	string ret_date1;
	string ret_date2;
	int ret_num;
	get_class();
	string d_day;

	ret1 = R->do_op(state, resrc_name, member_name, date, ret_date1, ebook_size, d_day, LOAN_PERIOD);
	if(ret1 == 1)  // no kind of resources in here B
	{
		print_result(1, 0, 0, "");
		return;
	}
	if(ret1 == 3)  // you never borrowed R
	{
		print_result(3, 0, 0, "");
		return;
	}

	ret2 = M->do_op(state, member_name, date, ret_date2, resrc_type, ebook_size);

	if(ret2 == 2)  // borrow # exceeded B
	{
		print_result(2, B_NUM, 0, "");
		return;
	}

	if(ret1 == 4)  // you already borrowed B
	{
		print_result(4, 0, 0, ret_date1);
		return;
	}
	if(ret1 == 5)  // other people borrowed B
	{
		print_result(5, 0, 0, ret_date1);
		return;
	}
	if(ret2 == 6)  // you are restricted B
	{
		print_result(6, 0, 0, ret_date2);
		return;
	}
	if(ret1 == 7)  // delayed R
	{
		R->get_due(d_day, member_name);
		R->final_state(true, LOAN_PERIOD, "", "");
		M->set_restrict_day(date, d_day, ret_date1);
		M->final_state(state, resrc_type, ebook_size, d_day);
		
		print_result(7, 0, 0, ret_date1);
		return;
	}
	if(ret2 == 0)  // success 
	{
		if(state == "B")
		{
			R->final_state(false, LOAN_PERIOD, member_name, date);
			M->final_state(state, resrc_type, ebook_size, d_day);
		}
		else
		{
			R->get_due(d_day, member_name);
			R->final_state(true, LOAN_PERIOD, "", "");
			M->final_state(state, resrc_type, ebook_size, d_day);
		}
		print_result(0, 0, 0, "");
		return;
	}
	if(ret2 == 15)
	{
		print_result(15, 0, 0, "");
		return;
	}
	if(ret2 == 16)
		print_result(16, 0, 0, "");
		
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
		if(ret == 0) SR.final_state(state, member_name, space_num, stoi(date.substr(11, 2)), time);
		print_result(ret, ret_time[0], ret_time[1], "");
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
			B.add_resource(in, 0);
		}
		else if(rsrc == "Magazine")
		{
			Mag.add_resource(in, 0);
		}
		else if(rsrc == "E-book")
		{
			int s, e;

			string s_b = "[";
			string e_b = "]";
			s = in.find(s_b);
			e = in.find(e_b);
			ebook_size = stoi(in.substr(s + 1, e - s - 1));
			E.add_resource(in.substr(0, s), ebook_size);
		}
	}
}

int Library::set_resource_info(string in, int cnt)
{
	switch(cnt)
	{
		case 0:
			date = in;
			return 0;
		case 1:
			resrc_type = in;
			return 0;
		case 2:
			resrc_name = in;
			return 0;
		case 3:
			state = in;
			return 0;
		case 4:
			member_type = in;
			return 0;
		case 5:
			member_name = in;
			return 0;
	}
}

void Library::check_date_range(string in)
{
	string comp = "09/12/30";
	int i;
	for(i=0;i<in.size();i++)
	{
		if(comp.at(i) == in.at(i)) continue;
		else if(comp.at(i) < in.at(i)) return;
		else throw in;
	}
	
}
void Library::check_member_excp(string in)
{
	int i;
	for(i=0;i<in.size();i++)
	{
		if(in.at(i) >= '0' && in.at(i) <= '9') throw in;
	}
	
}
int Library::set_space_info(string in, int cnt, int error)
{
	if(error > 0) return 1;
	switch(cnt)
	{
		case 0:
			try{
				check_date_range(in.substr(2, 8));
				date = in;
			}
			catch(string s)
			{
				print_exception(DATE_EXCP);
				return 1;
			}
			return 0;
		case 1:
			try{
				if(!(in=="Seat" || in=="StudyRoom")) throw in;
				space_type = in;
			}
			catch(string s)
			{
				print_exception(SPACE_TYPE_EXCP);
				return 1;
			}
			return 0;
		case 2:
			space_num = stoi(in);
			return 0;
		case 3:
			try{
				if(!(in=="B" || in=="R" || in=="E" || in=="C")) throw in;
				state = in;
			}
			catch(string s)
			{
				print_exception(OPERATION_EXCP);
				return 1;
			}
			return 0;
		case 4:
			try{
				if(!(in=="Undergraduate" || in=="Faculty" || in=="Graduate")) throw in;
				member_type = in;
			}
			catch(string s)
			{
				print_exception(MEMBER_TYPE_EXCP);
				return 1;
			}
			return 0;
		case 5:
			try{
				check_member_excp(in);
				member_name = in;
			}
			catch(string s)
			{
				print_exception(MEMBER_NAME_EXCP);
				return 1;
			}
			return 0;
		case 6:
			member_num = stoi(in);
			return 0;
		case 7:
			try{
				if(in.at(0) == '-') throw in;
				time = stoi(in);
			}
			catch(string s)
			{
				print_exception(TIME_EXCP);
				return 1;
			}
			return 0;

	}
}

int Library::getInformation(string line, int op)
{
	int i;
	int s, e;
	s = 0;
	int cnt = 0;
	int ret;
	int error = 0;
	for(i=0;i<line.size();i++)
	{
		if(line.at(i) == '\t') 
		{
			e = i-1;
			if(op == 1)
				set_resource_info(line.substr(s, e-s+1), cnt++);
			else if(op == 2)
			{
				ret += set_space_info(line.substr(s, e-s+1), cnt++, error);	
				error = ret;
			}
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
		ret += set_space_info(line.substr(s, i-s+1), cnt, error);
	}
	else
		set_resource(line.substr(s, i-s+1), cnt);
	return ret;
}

Library::Library()
{
	write_ptr = 0;
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
	filePath1 = "input.dat";
	filePath2 = "space.dat";
	ifstream openFile1(filePath1.data());  // resource
	ifstream openFile2(filePath2.data());  // space

	int flag1 = 0;
	int flag2 = 0;
	int ret, ret_val;
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
				
				ret_val = getInformation(line1, 1);
				if(ret_val == 0) 
					do_resource();
				flag1 = 0;                  // flag == 0 -> read next line
			}
			else if(ret == 2 || flag1 == 2)
			{
				if(flag1 == 0) flag1 = 1;
				
				ret_val = getInformation(line2, 2);
				if(ret_val == 0)
					do_space();
				flag2 = 0;
			}
		}
		openFile1.close();
		openFile2.close();
	}
}
