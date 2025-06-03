LIMIT_MB=32
LIMIT_KB=$((LIMIT_MB * 1024))

echo "Setting max virtual memory to $LIMIT_KB KB ($LIMIT_MB MB)"
ulimit -v $LIMIT_KB

echo "Running program with memory limit..."
./main.exe