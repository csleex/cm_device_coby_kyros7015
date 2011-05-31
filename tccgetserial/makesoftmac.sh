#!/system/bin/sh

if [ ! -f /system/wifi/softmac ]; then
	mount -o remount,rw /system
	tccgetserial -w > /system/wifi/softmac
	mount -o remount,ro /system
	ln -fs /system/wifi/softmac /data/softmac
fi
