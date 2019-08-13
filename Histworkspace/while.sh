#!/bin/bash

dirarray1=('wj' 'dy' 'tt' 'sg' 'ww' 'wz')
dirarray2=('pre' 'VBF' 'Final')

for i in ${dirarray1[*]};do
for j in ${dirarray2[*]};do
while :
do
	date
	if [ $(ps ux|grep "make"|wc -l) -eq 1 ];then
		./argument.sh $i $j
		echo **************************************************************************start...
		break
	fi
	sleep 120
done
done
done
