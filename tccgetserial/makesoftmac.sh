#!/system/bin/sh

if [ ! -f /system/etc/softmac ]; then
	mount -o remount,rw /system
	tccgetserial -w > /system/etc/softmac
	mount -o remount,ro /system
fi
