GREEN='\033[0;32m'
NC='\033[0m' # No Color

module="my_dummy_device"
device="my_dummy_device0"

echo Loading driver module for $device with:
echo -e "${GREEN}sudo insmod $module.ko${NC}"
sudo insmod ${module}.ko

major=`cat /proc/devices | awk "\\$2==\"$module\" {print \\$1}"`
echo
echo Create special device file for $device with:
echo -e "${GREEN}sudo mknod /dev/${device} c ${major} 0${NC}"
sudo mknod /dev/$device c $major 0

echo
echo -e "dmesg output:${GREEN}"
dmesg | tail -1
echo -e "${NC}"

