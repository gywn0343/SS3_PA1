#include <iostream>
using namespace std;

#ifndef _SPACE_H
#define _SPACE_H

#define MAX_SIZE 50
class Space{
	private:
	public:
		bool isOpen(int start, int time[2]);
		int comp(string a, string b);

};

class Seat : public Space{
	private:
		int time[4][2];
		int max_time[3];
		int seat_cnt[4];
		int seat[4][MAX_SIZE][3];
		string mem[4][MAX_SIZE];
		string prev_date;
		string mem_name;
	public:
		/*void print_seat()
		{
			int i, j;
			for(i=1;i<=3;i++)
			{
				for(j=0;j<50;j++)
				{
					if(seat[i][j][0] == -1) continue;
					cout << seat[i][j][0] << "~" << seat[i][j][1] << "(" << seat[i][j][2] << "): ";
					cout << mem[i][j] << endl;
				}
				cout << endl;
			}
		}*/
		Seat();
		void flush_date(string date);
		void flush_time(int now);
		void final_state(string state, string name, int floor, int start, int last);
		bool isUsing(string name);
		bool isFull(int floor, int& fastest_time);
		int do_op(string date, int start_time, int floor, string state, string name, int num_of_mem, int last_time, string mem_type, int ret_time[2]);
};

class StudyRoom : public Space{
	private:
		int time[2];
		int max_time;
		int room_cnt;
		int room[11][2];
		int max_ppl;
		string prev_date;
		string mem[11];
	public:
		StudyRoom();
		void flush_date(string date);
		void flush_time(int now);
		void final_state(string state, string name, int id, int start, int last);
		bool isUsing(string name);
		bool isFull(int id, int &fastest_time);
		int do_op(string date, int start_time, int id, string state, string name, int num_of_mem, int last_time, int ret_time[2]);
};
#endif
