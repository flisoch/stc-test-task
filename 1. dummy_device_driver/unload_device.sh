GREEN_COLOR='\033[0;32m'
NC='\033[0m' # No Color

module="my_dummy_device"
device="my_dummy_device0"

echo Unload module $module with:
echo -e "${GREEN_COLOR}sudo rmmod $module $* || exit 1${NC}"
sudo rmmod $module $* || exit 1

echo
echo Removing special device file for $device with:
echo -e "${GREEN_COLOR} sudo rm -f /dev/${device} ${NC}"
sudo rm -f /dev/${device}

echo 
echo -e "dmesg output: ${GREEN_COLOR}"
dmesg | tail -1
