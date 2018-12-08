#include "space.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

		bool Space::isOpen(int start, int time[2])
		{
			if(start > time[1] || start < time[0]) return false;
			return true;
		}
		int Space::comp(string a, string b)
		{
			int i;
			for(i=0;i<a.size();i++)
			{
				if(a.at(i) == b.at(i)) continue;
				else if(a.at(i) > b.at(i)) return 1;
				else return -1;
			}
			return 0;
		}
		Seat::Seat()
		{
			time[1][0] = 0; time[1][1] = 24;
			time[2][0] = 9; time[2][1] = 21;
			time[3][0] = 9; time[3][1] = 18;
			max_time[0] = 3; // Undergraduate
			int i, j;
			prev_date = "";
			for(i=1;i<=3;i++)
			{
				seat_cnt[i] = 0;
				for(j=0;j<MAX_SIZE;j++)
				{
					seat[i][j][0] = -1;
					seat[i][j][1] = -1;
					seat[i][j][2] = -1;
					mem[i][j] = "";
				}
			}
		}
		void Seat::flush_date(string date)
		{
			prev_date = date;
			int i, j;
			for(i=1;i<=3;i++)
			{
				seat_cnt[i] = 0;
				for(j=0;j<MAX_SIZE;j++)
				{
					seat[i][j][0] = -1;
					seat[i][j][1] = -1;
					seat[i][j][2] = -1;
					mem[i][j] = "";
				}
			}
		}
		void Seat::flush_time(int now)
		{
			int i, j;
			for(i=1;i<=3;i++)
			{
				for(j=0;j<MAX_SIZE;j++)
				{
					if(seat[i][j][1] <= now)  
					{
						if(seat[i][j][1] == -1) continue;
						seat[i][j][0] = -1;
						seat[i][j][1] = -1;
						seat[i][j][2] = -1;
						mem[i][j] = "";
						seat_cnt[i]--;
					}
					else if(seat[i][j][2] < now)
					{
						if(seat[i][j][2] == -1) continue;
						seat[i][j][0] = -1;
						seat[i][j][1] = -1;
						seat[i][j][2] = -1;
						mem[i][j] = "";
						seat_cnt[i]--;
					}
				}
			}
		}
		void Seat::final_state(string state, string name, int floor, int start, int last)
		{
			int i, j;
			int loc;
			for(i=0;i<MAX_SIZE;i++)
			{
				if(seat[floor][i][0] == -1) // insert in empty space
				{
					loc = i;
					break;
				}
			}
			if(state == "B")
			{
				seat[floor][loc][0] = start;
				seat[floor][loc][1] = start + last;
				mem[floor][loc] = name;
				seat_cnt[floor]++;
			}
			else if(state == "E")
			{
				for(i=1;i<=3;i++)
				{
					for(j=0;j<MAX_SIZE;j++)
					{
						if(mem[i][j] == name)
						{
							seat[i][j][2] = start;
						}
					}
				}
			}
			else if(state == "C")
			{
				for(i=1;i<=3;i++)
				{
					for(j=0;j<MAX_SIZE;j++)
					{
						if(mem[i][j] == name)
						{
							seat[i][j][2] = -1;
							break;
						}
					}
				}
			}
			else
			{
				for(i=1;i<=3;i++)
				{
					for(j=0;j<MAX_SIZE;j++)
					{
						if(mem[i][j] == name)
						{
							seat[i][j][0] = -1;
							seat[i][j][1] = -1;
							seat[i][j][2] = -1;
							mem[i][j] = "";
							seat_cnt[i]--;
							break;
						}
					}
				}		
			}
		}
		bool Seat::isUsing(string name)
		{
			int i, j;
			for(i=1;i<=3;i++)
			{
				for(j=0;j<MAX_SIZE;j++)
				{
					if(mem[i][j] == name) return true;
				}
			}
			return false;
		}
		bool Seat::isFull(int floor, int& fastest_time)
		{
			int i;
			int min = 25;
			if(seat_cnt[floor] == MAX_SIZE)
			{
				for(i=0;i<MAX_SIZE;i++)
				{
					if(min > seat[floor][i][1])
					{
						min = seat[floor][i][1];
					}
				}
				if(min > time[floor][1]) fastest_time = time[floor][1];
				else fastest_time = min;
				return true;
			}
			return false;
		}
		int Seat::do_op(string date, int start_time, int floor, string state, string name, int num_of_mem, int last_time, string mem_type, int ret_time[2])
		{
			if(prev_date == "" || comp(date, prev_date) > 0) 
			{
				flush_date(date);
			}
			else flush_time(start_time);

			int index;
			if(mem_type == "Undergraduate")
			{
				index = 0;
			}
			if(floor <= 0 || floor > 3) return 8; // invalid floor
			if(isOpen(start_time, time[floor]) == 0) 
			{
				ret_time[0] = time[floor][0];
				ret_time[1] = time[floor][1];
				return 9;
			}
			if(state == "R" || state == "E" || state == "C")
			{
				if(!isUsing(name)) 
					return 10;
			}
			else if(state == "B")
			{
				if(isUsing(name)) return 11;
			}
			if(num_of_mem > 1) return 12;     // member limit exceeded
			if(last_time > max_time[index]) return 13; // time limit exceeded
			if(isFull(floor, ret_time[0])) return 14;

			return 0;
		}
		StudyRoom::StudyRoom()
		{
			time[0] = 9; time[1] = 18;
			max_time = 3;
			room_cnt = 0;
			max_ppl = 6;
			prev_date = "";
			int i;
			for(i=1;i<=10;i++)
			{
				room[i][0] = -1;
				room[i][1] = -1;
				mem[i] = "";
			}
		}
		void StudyRoom::flush_date(string date)
		{
			prev_date = date;
			int i;
			room_cnt = 0;
			for(i=1;i<=10;i++)
			{
				room[i][0] = -1;
				room[i][1] = -1;
				mem[i] = "";
			}
		}
		void StudyRoom::flush_time(int now)
		{
			int i;
			for(i=1;i<=10;i++)
			{
				if(room[i][1] <= now)
				{
					if(room[i][1] == -1) continue;
					room[i][0] = -1;
					room[i][1] = -1;
					mem[i] = "";
					room_cnt--;
				}
			}
		}
		void StudyRoom::final_state(string state, string name, int id, int start, int last)
		{
			if(state == "B")
			{
				room[id][0] = start;
				room[id][1] = start + last;
				room_cnt++;
				mem[id] = name;
			}	
			else if(state == "R")
			{
				room[id][0] = -1;
				room[id][1] = -1;
				room_cnt--;
				mem[id] = "";
			}
/*int i;
for(i=0;i<10;i++)
cout << mem[i+1] << endl;*/
		}
		bool StudyRoom::isUsing(string name)
		{
			int i;
			for(i=1;i<=10;i++)
			{
				if(mem[i] == name) return true;
			}
			return false;
		}
		bool StudyRoom::isFull(int id, int &fastest_time)
		{
			int i;
			int min = 25;
			if(room[id][0] != -1)
			{
				if(room[id][1] >= time[1]) fastest_time = time[1];
				else
					fastest_time = room[id][1];
				return true;
			}
			return false;
		}
		int StudyRoom::do_op(string date, int start_time, int id, string state, string name, int num_of_mem, int last_time, int ret_time[2])
		{
			if(prev_date == "" || comp(date, prev_date) > 0) flush_date(date);
			else flush_time(start_time);
			if(id <= 0 || id > 10) return 8;  // invalid space id
			if(state == "B")
			{
				if(isOpen(start_time, time) == 0)
				{
					ret_time[0] = time[0];
					ret_time[1] = time[1];
					return 9;
				}
				if(isUsing(name)) return 11;
				if(num_of_mem > 6) return 12;
				if(last_time > 3) return 13;
				if(isFull(id, ret_time[0])) return 14;
			}
			else if(state == "R")
			{
				if(!isUsing(name)) 
					return 10;
			}


			return 0;

		}
