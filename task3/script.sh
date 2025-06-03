LIMIT_BLOCKS=1
LIMIT_BYTES=$((LIMIT_BLOCKS * 512))

echo "Setting file size limit to $LIMIT_BYTES bytes ($LIMIT_BLOCKS blocks)"
ulimit -f $LIMIT_BLOCKS

./main.exe