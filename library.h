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
		string result[9] = {
			"Success.", //0
			"Non exist resource.", //1
			"Exeeds your possible number of borrow. possible# of borrows: ", //2
			"You did not borrow this book.", //3
			"You already borrowed this book at ", // 4
			"Other member already borrowed this book. This book will be returned at ", // 5
			"Restricted member until ", // 6
			"Delayed return. You'll be restricted until ", // 7
			"Exceeds your storage capacity." // 15
		};
		Member *M;
		Resource *R;
		Under U;
		Graduate G;
		Faculty F;
		Book B;
		Magazine Mag;
		E_book E;
		
		string member_name;
		string resrc_name;
		string date;
		string state;  // Borrow=0 or Return=1
		string resrc_type;  // Book=1 or others
		string member_type; // Under or others
		void get_class();
		int LOAN_PERIOD;
		int B_NUM;
		int ebook_size;
		void print_result(int n, int num, string date);
		void do_operation();
		void set_resource(string in, int cnt);
		void set_info(string in, int cnt);
		void getInformation(string line, int op);
	public:
		Library();
		
		
};

#endif
