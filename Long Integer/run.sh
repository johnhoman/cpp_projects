#! /bin/bash
#S=$PATH
MYPATH=/afs/cad/u/j/m/jmh25/CS610/Project2
FILE=Long_Integer.cpp
OUTPUT=johnhoman_cs610_pa2.ascii
if [ -a ${MYPATH}/${FILE} ] 
	then
		echo -e "Found file $FILE\n"
		echo -e "Compiling file\n"
		if  g++ ${MYPATH}/${FILE} ; then
			echo -e "File $FILE compiled succesfully\n"
			echo -e "Running $FILE ..."
			echo -e "Piping results to file $OUTPUT in your home area\n"
			${MYPATH}/a.out > ~/${OUTPUT}
			${MYPATH}/a.out > ${MYPATH}/${OUTPUT}
		fi
fi
echo -e "The length of test case E messes up the way I output the file (for E only)\n"
echo -e "If you have X11 forwarding enabled I can open it up in gedit which respects the line formatting"
while true; do
	printf "Open gedit [Y] or display contents to terminal [n]: "
	read answer
	if [ "$answer" = "Y" ] || [ "$answer" = "y" ];then
		echo -e "Opening gedit..."
		gedit ${MYPATH}/${OUTPUT}
		echo -e "\n\n\n"
		printf "Did gedit successfully open [Y,n]: "
		read ans
		if [ "$ans" = "Y" ] || [ "$ans" = "y" ];then
			break
		else
			cat ${MYPATH}/${OUTPUT}
			break
		fi
	elif [ "$answer" = "n" ] || [ "$answer" = "N" ]; then
		cat ${MYPATH}/${OUTPUT}
		break
	else 
		echo "Unrecognized input...try again"
	fi
done

