#!/bin/sh

ROOT="/mnt/.root"
# This should be set to appropriate device for target
ROOT_DEV="/dev/vda"

echo "Running from initramfs"

# mount temporary filesystems
mount -n -t devtmpfs devtmpfs /dev
mount -n -t proc     proc     /proc
mount -n -t sysfs    sysfs    /sys
mount -n -t tmpfs    tmpfs    /run

# mount new root
[ -d ${ROOT} ] || mkdir -p ${ROOT}
mount ${ROOT_DEV} ${ROOT}
                                   
echo "Showing current filesystems"
df -Th
                                        
echo "###################################"
echo "Contents of test file in initramfs:"
cat /home/root/*
echo "###################################"


# switch to new rootfs and exec init
cd ${ROOT}
exec switch_root ${ROOT} "/sbin/init" "$@"
