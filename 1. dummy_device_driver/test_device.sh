GREEN='\033[0;32m'
dd if=/dev/my_dummy_device0 of=test bs=14 count=100

echo -e "dmesg output: ${GREEN}"
dmesg | tail -3
