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
		echo $comp    $2
		if [ "$2" == "all" ] || [ "$2" == "$comp" ]
		then
			cat $1.dat | grep -w 'Type' > tmp.dat
			cat $1.dat | grep -w $comp >> tmp.dat
			mkdir -p resource
			mv -f tmp.dat ./resource
			cd ./resource
			mv tmp.dat $comp.dat
			cd ..
		fi
	done
fi
if [ "$1" == "input" ] && ["$2" != "all"];
then
	x="resource.dat"
	y="space.dat"
	target="input"
	option=$2
elif [ "$1" == "space" ] && [ "$2" != "all" ]
then
	x="input.dat"
	y="resource.dat"
	target="space"
	option=$2
	if [ "$3" != '' ] && [ "$3" != 'all' ] && [ "$4" == '' ];
	then
		option=$2'\t'$3
	fi
	make
	cat $1.dat | grep -w 'Date' > tmp.dat
	cat $1.dat | grep -P $option >> tmp.dat
	mkdir -p tmp_dir
	mkdir -p $target
	cp -f tmp.dat ./$target
	cd ./$target
	mv tmp.dat $2.dat
	cd ..
	mv -f tmp.dat ./tmp_dir
	mv -f ./lib ./tmp_dir
	cp -f $x $y ./tmp_dir
	cd ./tmp_dir
	mv tmp.dat $target.dat
	./lib
	cp -f output.dat ..
	rm *
	cd ..
	#mkdir -p output
	#mv -f output.dat output
	rmdir tmp_dir
#	fi
fi

if [ "$1" == "output" ]
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
			if [ "$R" == "Return_code" ]
			then
				continue
			elif [ $R -eq $x ]
			then
				((cnt++))
			fi
		done < output.dat
		echo -e $x' \t'$cnt >> stat_table.dat
	done
	rm output.dat
	cd ..
fi
