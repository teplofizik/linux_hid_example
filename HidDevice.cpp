#include "HidDevice.h"
#include "hidapi/hidapi.h"
#include <locale>
#include <codecvt>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <string.h>

#define MAX_STR 255

static int DevCounter = 0;

HidDevice::HidDevice(uint16_t Vid, uint16_t Pid)
{
	if(DevCounter == 0)
	{
		hid_init();
	}
	
	DevCounter++;
	
	// Open the device using the VID, PID,
	// and optionally the Serial number.
	handle = hid_open(Vid, Pid, NULL);
}

HidDevice::~HidDevice() {
	DevCounter--;
	
	if (handle) hid_close(handle);
	if (DevCounter == 0)
	{
		hid_exit();
	}
}

bool HidDevice::WriteReport(uint8_t ReportId, uint8_t * Buffer, size_t BufferSize)
{
	if(BufferSize < 65)
	{
		uint8_t Dst[65];
		Dst[0] = ReportId;
	
		memcpy(&Dst[1], Buffer, BufferSize);
		int res = hid_write(handle, Dst, BufferSize + 1);
		
		return res > 0;
	}
	else
		throw new std::runtime_error("Buffer is too big");
}

bool HidDevice::ReadReport(uint8_t ReportId, uint8_t * Buffer, size_t BufferSize)
{
	if(BufferSize < 65)
	{
		uint8_t Dst[65];
		Dst[0] = ReportId;
	
		memset(&Dst[1], 0, BufferSize);
		int res = hid_read(handle, Dst, BufferSize + 1);
		
		if (res == BufferSize + 1)
		{
			memcpy(Buffer, &Dst[1], BufferSize);
			return true;
		}
		else
			return false;
	}
	else
		throw new std::runtime_error("Buffer is too big");
}

bool HidDevice::Available()
{
	return handle != 0;
}

std::string HidDevice::GetManufacturer()
{
	wchar_t wstr[MAX_STR];
	int res = hid_get_manufacturer_string(handle, wstr, MAX_STR);
	
	return (!res) ? FromWstring(std::wstring(wstr)) : "";
}

std::string HidDevice::GetProductString()
{
	wchar_t wstr[MAX_STR];
	int res = hid_get_product_string(handle, wstr, MAX_STR);

	return (!res) ? FromWstring(std::wstring(wstr)) : "";
}

std::string HidDevice::GetSerial()
{
	wchar_t wstr[MAX_STR];
	int res = hid_get_serial_number_string(handle, wstr, MAX_STR);

	return (!res) ? FromWstring(std::wstring(wstr)) : "";
}

std::string HidDevice::FromWstring(std::wstring wstr)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(wstr);
}
