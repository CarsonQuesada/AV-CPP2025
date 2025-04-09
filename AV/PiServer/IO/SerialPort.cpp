#include "SerialPort.h"

SerialPort &SerialPort::get_instance()
{
    // TODO: insert return statement here
}

int SerialPort::retrieve_serial_data(UserInputBuff& serialBuff)
{
    bool dataReady;
    int bytesAvailable;
    int bytesRead;
    // Check if there are available bytes in the serial buffer
	bytesAvailable = serial_data_available(piHandle, serialHandle);
	printf("Serial available: %d\n", bytesAvailable);
			
	// If sufficient data is available, read it into the serial buffer
	if (bytesAvailable >= preParseBuffSize) {
        int bytesToRead = std::min(bytesAvailable, 5);
        bytesRead = serial_read(piHandle, serialHandle, serialBuff.expose_buffer(), bytesToRead);
    }
	printf("RX: %s\n", serialBuff.expose_buffer());

    return bytesRead;
}

bool SerialPort::initialize()
{
    char buffer[4];
    if(!initialized) {
        piHandle = Pigpio::get_instance().get_handle();
        serialHandle = serial_open(piHandle, buffer, 115200, 0);			// init serial and assign handle to "serialHdl"

        if (serialHandle < 0) {
            printf("[!] Failed to init serial! Try turning car off and on again!\n");
        } else {
            printf("> serial open %s \tINIT OK\n", serialPortPath);
            initialized = true;
        }
    } else {
        printf("Serial already initialized\n");
    }
    return initialized;
}

void SerialPort::cleanup()
{
    if (initialized)
    {
        serial_close(piHandle, serialHandle);
        initialized = false;
    }
    else
        printf("WARNING: Tried closing serial connection without initialization\n");
}

SerialPort::~SerialPort()
{
    if (initialized)
        serial_close(piHandle, serialHandle);
}
