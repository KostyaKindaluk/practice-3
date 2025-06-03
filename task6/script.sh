LIMIT_KB=64
LIMIT_BYTES=$((LIMIT_KB * 1024))

echo "Setting max stack size to $LIMIT_BYTES bytes ($LIMIT_KB KB)"
ulimit -s $LIMIT_KB

echo "Running program with stack limit..."
./main.exe