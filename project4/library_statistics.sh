#!/bin/bash

echo $1 $2 $3
if [ "$1" == "resource" ]; 
then
	#if [ $2="all"]
	#then
	x="Book"
	y="E-book"
	z="Magazine"
	for comp in $x $y $z
	do
		if [ "$2" == "all" ] || [ "$2" == "$comp" ];
		then
			cat $1.dat | grep -w 'Type' > tmp.dat
			cat $1.dat | grep -w '\t'$comp'\t' >> tmp.dat
			mkdir -p resource
			mv -f tmp.dat ./resource
			cd ./resource
			mv tmp.dat $comp.dat
			cd ..
		fi
	done
elif [ "$2" == "date" ]
then
		start_y=$(echo $3 | cut -d'/' -f 1)
		start_m=$(echo $3 | cut -d'/' -f 2)
		start_d=$(echo $3 | cut -d'/' -f 3)
		end_y=$(echo $4 | cut -d'/' -f 1)
		end_m=$(echo $4 | cut -d'/' -f 2)
		end_d=$(echo $4 | cut -d'/' -f 3)
		start_date=$start_y$start_m$start_d
		end_date=$end_y$end_m$end_d
	if [ "$1" == "input" ]
	then
		target="input"
		x="resource"
		y="space"
		while read D Ect
		do
			if [ "$D" == "Date[yy/mm/dd]" ]
			then 
				echo -e $D'\t'$Ect > tmp.dat
				continue
			fi
			comp_y=$(echo $D | cut -d'/' -f 1)
			comp_m=$(echo $D | cut -d'/' -f 2)
			comp_d=$(echo $D | cut -d'/' -f 3)
			comp_date=$comp_y$comp_m$comp_d
			if [ $comp_date -ge $start_date ] && [ $comp_date -le $end_date ]
			then
				echo -e $D'\t'"$Ect"  >> tmp.dat	
			fi
		done < input.dat
	elif [ "$1" == "space" ]
	then
		target="space"
		x="resource"
		y="input"
		start_t=$(echo $3 | cut -d'/' -f 4)
		end_t=$(echo $4 | cut -d'/' -f 4)
		start_date+=$start_t
		end_date+=$end_t
		while read D Ect
		do
			if [ "$D" == "Date[yy/mm/dd/hh]" ]
			then
				echo -e $D'\t'$Ect > tmp.dat
				continue
			fi
			comp_y=$(echo $D | cut -d'/' -f 1)
			comp_y=$(echo ${comp_y:2:2})
			comp_m=$(echo $D | cut -d'/' -f 2)
			comp_d=$(echo $D | cut -d'/' -f 3)
			comp_t=$(echo $D | cut -d'/' -f 4)
			comp_date=$comp_y$comp_m$comp_d$comp_t
			if [ $comp_date -ge $start_date ] && [ $comp_date -le $end_date ]
			then
				echo -e $D'\t'"$Ect"  >> tmp.dat	
			fi
		done < space.dat
	fi
	make
	mkdir -p tmp_dir
	mkdir -p $target
	cp -f tmp.dat ./$target
	cd ./$target
	mv tmp.dat date.dat
	cd ..
	mv -f tmp.dat ./tmp_dir
	cp -f ./lib ./tmp_dir
	cp -f $x.dat $y.dat ./tmp_dir
	cd ./tmp_dir
	mv -f tmp.dat $target.dat
	./lib
	cp -f output.dat ..
	rm *
	cd ..
	mkdir -p output
	cp -f output.dat ./output
	rmdir tmp_dir

elif [ "$1" == "input" ] || [ "$1" == "space" ];
then
	if [ "$1" == "input" ];
	then
		x="resource.dat"
		y="space.dat"
		target="input"
		option=$2
	elif [ "$1" == "space" ];
	then
		x="input.dat"
		y="resource.dat"
		target="space"
		option=$2
	fi
	make
	for comp in Faculty Undergraduate Graduate Seat StudyRoom Book E-book Magazine
	do
		if [ "$1" == "input" ] 
		then
			if [ "$comp" == "Seat" ] || [ "$comp" == "StudyRoom" ]
			then
				continue
			fi
		elif [ "$1" == "space" ]
		then
			if [ "$comp" == "Book" ] || [ "$comp" == "E-book" ] || [ "$comp" == "Magazine" ]
			then 
				continue
			fi
		fi
		if [ "$2" == "all" ] || [ "$2" == "$comp" ];
		then
			if [ "$3" != '' ] && [ "$3" != 'all' ] && [ "$4" == '' ];
			then
				option=$2'\t'$3
			fi
			cat $1.dat | grep -w Member_type > tmp.dat
			cat $1.dat | grep -P '\t'$comp'\t' >> tmp.dat
			mkdir -p tmp_dir
			mkdir -p $target
			cp -f tmp.dat ./$target
			cd ./$target
			mv tmp.dat $comp.dat
			cd ..
			mv -f tmp.dat ./tmp_dir
			cp -f ./lib ./tmp_dir
			cp -f $x $y ./tmp_dir
			cd ./tmp_dir
			mv tmp.dat $target.dat
			./lib
			cp -f output.dat ..
			rm *
			cd ..
			mkdir -p output
			cp -f output.dat output
			rmdir tmp_dir
		fi
	done
fi


if [ "$1" == "output" ];
then
	mkdir -p output
	cp -f output.dat ./output
	cd ./output
	echo -e Return_code' \t'Number > stat_table.dat
	for x in -1 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16
	do
		cnt=0
		while read N R Des
		do
			if [ "$R" == "Return_code" ];
			then
				continue
			elif [ $R -eq $x ];
			then
				((cnt++))
			fi
		done < output.dat
		echo -e $x' \t'$cnt >> stat_table.dat
	done
	rm output.dat
	cd ..
fi
