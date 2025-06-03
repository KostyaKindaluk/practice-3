CPU_LIMIT=1

echo "Setting CPU time limit to $CPU_LIMIT seconds"
ulimit -t $CPU_LIMIT

./main.exe