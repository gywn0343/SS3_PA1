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
		void print_result(int n, int num, string date);
		void do_operation();
		void set_resource(string in, int cnt);
		void set_info(string in, int cnt);
		void getInformation(string line, int op);
	public:
		Library();
		
		
};

#endif
