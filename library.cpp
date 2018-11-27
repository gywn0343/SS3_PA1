#include <iostream>
#include <vector>
#include "library.h"
#include <fstream>
using namespace std;

void Library::print_result(int n, int num, string date)
{
	static int count = 0;
	string filePath = "output.dat";

	ofstream outFile;
	outFile.open(filePath, ios_base::app);
	if(outFile.is_open())
	{
		/*outFile*/cout << ++count << "	";
		/*outFile*/cout << n << "	";
		switch(n)
		{
			case 0:
				outFile << result[0] << endl; return;
			case 1:
				outFile << result[1] << endl; return;
			case 2:
				outFile << result[2] << num << endl; return;
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

void Library::do_operation()
{
	int ret1, ret2;
	int due;
	string ret_date1;
	string ret_date2;
	int ret_num;
	get_class();
	string d_day;

	ret1 = R->do_op(state, resrc_name, member_name, date, ret_date1, ebook_size, d_day, LOAN_PERIOD);
	if(ret1 == 1)  // no kind of resources in here
	{
		print_result(1, 0, "");
		return;
	}

	ret2 = M->do_op(state, member_name, date, ret_date2, resrc_type, ebook_size);

	if(ret2 == 2)  // borrow # exceeded
	{
		print_result(2, B_NUM, "");
		return;
	}
	if(ret1 == 3)  // you never borrowed
	{
		print_result(3, 0, "");
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
	if(ret2 == 6)  // you are restricted
	{
		print_result(6, 0, ret_date2);
		return;
	}
	if(ret1 == 7)  // delayed R
	{
		R->get_due(d_day, member_name);
		R->final_state(true, LOAN_PERIOD, "", "");
		M->set_restrict_day(date, d_day, ret_date1);
		M->final_state(state, resrc_type, ebook_size, d_day);
		
		print_result(7, 0, ret_date1);
		return;
	}
	if(ret2 == 0 || ret1 == 7)  // success or delayed return
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
		print_result(0, 0, "");
		return;
	}
	if(ret2 == 15)
		print_result(15, 0, "");
		
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

void Library::set_info(string in, int cnt)
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

void Library::getInformation(string line, int op)
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
		do_operation();
	}
	else
		set_resource(line.substr(s, i-s+1), cnt);
}

Library::Library()
{
	string filePath = "output.dat";
	ofstream outFile(filePath.data());
	if(outFile.is_open())
	{
		outFile << "OP_#	Return_code	Description" << endl;
		outFile.close();
	}
	filePath = "resource.dat";
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
