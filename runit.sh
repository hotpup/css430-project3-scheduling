# compile all files
make fcfs
make sjf
make priority
make rr
make priority_rr

echo "FCFS"
./fcfs "schedule.txt"
echo ""

echo "SJF"
./sjf "schedule.txt"
echo ""

echo "PRIORITY"
./priority "schedule.txt"
echo ""

echo "RR"
./rr "schedule.txt"
echo ""

echo "PRIORITY-RR"
./priority_rr "schedule.txt"