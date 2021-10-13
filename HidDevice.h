// HidDevice class

#include <string>

#ifndef HIDDEVICE_H_
#define HIDDEVICE_H_

struct hid_device_;

class HidDevice {
private:
	struct hid_device_ *handle;
	
public:
	HidDevice(uint16_t Vid, uint16_t Pid);
	~HidDevice();
	
	bool Available();
	
	std::string GetManufacturer();
	std::string GetProductString();
	std::string GetSerial();

	// Запись репорта, длина указывается тольео для данных, без учёта байта с номером репорта
	bool WriteReport(uint8_t ReportId, uint8_t * Buffer, size_t BufferSize);
	bool ReadReport(uint8_t ReportId, uint8_t * Buffer, size_t BufferSize);

protected:
	std::string FromWstring(std::wstring wstr);
	
protected:
};

#endif
