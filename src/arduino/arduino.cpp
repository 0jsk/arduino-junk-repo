#include "arduino.h"

Arduino::Arduino(const std::string &port) {
  connect(port);
}

Arduino::~Arduino() {
  CloseHandle(serialPortHandle);
}

void Arduino::connect(const std::string &port) {
  serialPortHandle = CreateFileA(
    port.c_str(),
    GENERIC_READ | GENERIC_WRITE,
    0,
    nullptr,
    OPEN_EXISTING,
    FILE_ATTRIBUTE_NORMAL,
    nullptr
  );

  if (serialPortHandle == INVALID_HANDLE_VALUE) {
    throw std::runtime_error("Failed to open serial port");
  }

  DCB serialParams = { 0 };
  serialParams.DCBlength = sizeof(serialParams);

  if (!GetCommState(serialPortHandle, &serialParams)) {
    throw std::runtime_error("Failed to get serial port state");
  }

  serialParams.BaudRate = CBR_9600;
  serialParams.ByteSize = 8;
  serialParams.StopBits = ONESTOPBIT;
  serialParams.Parity = NOPARITY;

  if (!SetCommState(serialPortHandle, &serialParams)) {
    throw std::runtime_error("Failed to set serial port state");
  }

  connected = true;
}

void Arduino::sendMessage(const std::string &message) {
  if (!connected) {
    throw std::runtime_error("Arduino is not connected");
  }

  DWORD bytesSent;

  if (!WriteFile(serialPortHandle, message.c_str(), message.length(), &bytesSent, nullptr)) {
    throw std::runtime_error("Failed to send message to Arduino");
  }
}
std::string Arduino::readMessage() {
  if (!connected) {
    throw std::runtime_error("Arduino is not connected");
  }

  char buffer[256];

  DWORD bytesRead;

  if (!ReadFile(serialPortHandle, buffer, sizeof(buffer), &bytesRead, nullptr)) {
    throw std::runtime_error("Failed to read message from Arduino");
  }

  return std::string(buffer, bytesRead);
}
