# Info
Test tool for USB Hid example for [gd32f107 project](https://github.com/teplofizik/gd32f1base)

# Prerequisites
```sh
git clone https://github.com/signal11/hidapi
cd hidapi
./bootstrap
./configure
make
sudo checkinstall
```

> docs: n
> descr: Usb HID library
> version: 0.8.0
> name: libhidapi
> provides: libhidapi

# Testing devices
## Build testing tool
```sh
git clone https://github.com/DIGImend/usbhid-dump
cd usbhid-dump/
autoreconf --install
autoconf
./configure
make
sudo checkinstall
```
> docs: n
> version: 1.4
> descr: Usb HID debug tool
> name: usbhid-dump
> provides: usbhid-dump

## Test
```sh
sudo usbhid-dump --model=0483 --entity=all
```

## Permissions
TODO: udev permissions