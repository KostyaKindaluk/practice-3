LIMIT_BLOCKS=1
LIMIT_BYTES=$((LIMIT_BLOCKS * 512))

echo "No args test:"
./main.exe
echo "3 args test:"
./main.exe input.txt output.txt something
echo "Non-existing source file test:"
./main.exe something output.txt

echo "Normal use:"
./main.exe input.txt output.txt

echo "File limit test:"
echo "Setting file size limit to $LIMIT_BYTES bytes ($LIMIT_BLOCKS blocks)"
ulimit -f $LIMIT_BLOCKS
./main.exe input.txt output.txt