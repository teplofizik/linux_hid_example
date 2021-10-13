// Example from linux:
// https://github.com/torvalds/linux/blob/master/samples/hidraw/hid-example.c

#include <iostream>
#include <unistd.h>
#include "HidDevice.h"

class ExampleDevice : public HidDevice {
public:
	ExampleDevice() : HidDevice(0x0483U, 0x5711U) {
		
	}
	bool SwitchLed1() {
		uint8_t buf[1] = { 0x01 };
		return WriteReport(1, buf, 1);
	}
	bool SwitchLed2() {
		uint8_t buf[1] = { 0x01 };
		return WriteReport(2, buf, 1);
	}
	bool SetValue(uint8_t Value) {
		uint8_t buf[1] = { Value };
		return WriteReport(3, buf, 1);
	}
};

int main(void)
{
	int res;
	ExampleDevice device;
	
	if(device.Available())
	{
		// Read the Manufacturer String
		std::string Manufacturer = device.GetManufacturer();
		std::string ProductString = device.GetProductString();
		std::string Serial = device.GetSerial();
		
		std::cout << "Manufacturer String: " << Manufacturer << std::endl;
		std::cout << "Product String: " << ProductString << std::endl;
		std::cout << "Serial Number String: " << Serial << std::endl;

		device.SetValue(0x22);
		device.SwitchLed1();

		for(int i = 0; i < 20; i++)
		{
			uint8_t buf[4];
			
			if(device.ReadReport(4, buf, sizeof(buf)))
			{
				printf("Readed: 0x%02x 0x%02x 0x%02x 0x%02x\n", buf[0], buf[1], buf[2], buf[3]);
			}
			
			usleep(1000);
		}
	}
	else
		puts("Could not open hid device v:0x0483 p:0x5711");
		
    return 0;
}