#ifndef ARDUINO_TEST_ARDUINO_H
#define ARDUINO_TEST_ARDUINO_H

#include <Windows.h>
#include <SetupAPI.h>
#include <devguid.h>
#include <fileapi.h>

#include <string>
#include <vector>
#include <stdexcept>

class Arduino {
  public:
    Arduino(const std::string& port);
    ~Arduino();

    void sendMessage(const std::string& message);
    std::string readMessage();

  private:
    void connect(const std::string& port);

    HANDLE serialPortHandle = nullptr;
    bool connected = false;
};


#endif //ARDUINO_TEST_ARDUINO_H
