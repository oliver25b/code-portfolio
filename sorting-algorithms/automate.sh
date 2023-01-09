#Oliver Bartz
#12/01/2022
#Goal: run sort.exe repeatedly with all the text documents and each argument option.
    #output the data to a .csv file.

datas=(5 10 50 100 500 1000 5000)
    #, 10000, 50000, 100000, 500000, 1000000)
nums=(1 2 3 4 5 6)

#runs through all 6 sort options for outer loop
int1=0

#runs through all data values for inner loop
int2=0
#"constant" for number of elements in datas()
max2=5

rm data.csv &> null
touch data.csv

echo "Number of Sortees,Bubble Sort,Selection Sort,Insertion Sort,Shell Sort,Quick Sort,Merge Sort" >> data.csv


while [ $int1 -le 6 ]
do
    echo -n "${datas[$int1]}," >> data.csv
    while [ $int2 -le $max2 ]
    do
        echo -n "$(./sort.exe ${datas[$int1]} ${nums[$int2]})" >> data.csv
        [[ $int2 -lt $max2 ]] && echo -n "," >> data.csv || echo "" >> data.csv
        int2=$(($int2+1))
    done
    int1=$(($int1+1))
    int2=0
done

rm null