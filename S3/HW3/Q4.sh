# !/bin/bash
echo "Enter start line:"
read x
echo "Enter end line:"
read y
echo "Enter file name:"
read file_name
if [ $x -gt $y ]
then
   echo "Error: start number should be less than end number"
   exit 1
fi
if [[ ! -f "$file_name" ]]; then
   echo "File doesn't exist"
   exit 1
fi
i=1
while read line
do
   if [ $i -ge $x ]&&[ $i -le $y ]
   then
       echo $line
   fi
   ((i=$i+1))
done < $file_name