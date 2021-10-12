// Example from linux:
// https://github.com/torvalds/linux/blob/master/samples/hidraw/hid-example.c

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "hidapi/hidapi.h"

#define MAX_STR 255

int main(void)
{
	int res;
	hid_device *handle;
	
	// Initialize the hidapi library
	res = hid_init();
	
	// Open the device using the VID, PID,
	// and optionally the Serial number.
	handle = hid_open(0x0483U, 0x5711U, NULL);

	if(handle)
	{
		wchar_t wstr[MAX_STR];
		
		//res = hid_set_nonblocking(handle, 1);
		
		// Read the Manufacturer String
		res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
		wprintf(L"Manufacturer String: %s\n", wstr);

		// Read the Product String
		res = hid_get_product_string(handle, wstr, MAX_STR);
		wprintf(L"Product String: %s\n", wstr);

		// Read the Serial Number String
		res = hid_get_serial_number_string(handle, wstr, MAX_STR);
		wprintf(L"Serial Number String: (%d) %s\n", wstr[0], wstr);

		{
			unsigned char buf[65];
			// Store value (cmd 0x03). The first byte is the report number (0x0).
			buf[0] = 0x03;
			buf[1] = 0x55;
			res = hid_write(handle, buf, 2);
			
			// Toggle LED (cmd 01). The first byte is the report number (0x0).
			buf[0] = 0x01;
			buf[1] = 0x01;
			res = hid_write(handle, buf, 2);
			
			usleep(100000);
			
			// Read state
			for(int i = 0; i < 20; i++)
			{
				buf[0] = 0x04;
				buf[1] = 0x00;
				buf[2] = 0x00;
				buf[3] = 0x00;
				buf[4] = 0x00;
				res = hid_read(handle, buf, 5);

				//if(res == 5)
				{
					wprintf(L"Readed: 0x%02x 0x%02x (res: %d)\n", buf[3], buf[4], res);
				}
				 
				usleep(1000);
			}
		}
		
		hid_close(handle);
	}
	else
		puts("Could not open hid device v:0x0483 p:0x5711");
		
	// Finalize the hidapi library
	res = hid_exit();

    return 0;
}