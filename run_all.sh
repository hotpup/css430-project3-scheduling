# check for missing arg
if [ -z "$1" ]; then
    echo 'usage: ./run_all.sh input-file'
    exit;
fi

# compile all files
make fcfs
make sjf
make priority
make rr
make priority_rr

echo running FCFS
echo 'FCFS' > $1_output.txt # make new file, then append all other output
./fcfs $1 >> $1_output.txt
echo >> $1_output.txt

echo running SJF
echo 'SJF' >> $1_output.txt
./sjf $1 >> $1_output.txt
echo >> $1_output.txt

echo running Priority
echo 'PRIORITY' >> $1_output.txt
./priority $1 >> $1_output.txt
echo >> $1_output.txt

echo running RR
echo 'RR' >> $1_output.txt
./rr $1 >> $1_output.txt
echo >> $1_output.txt

echo running Priority RR
echo 'PRIORITY-RR' >> $1_output.txt
./priority_rr $1 >> $1_output.txt
echo >> $1_output.txt

echo output file: $1_output.txt 