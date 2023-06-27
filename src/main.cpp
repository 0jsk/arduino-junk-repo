#include "arduino/arduino.h"
#include <iostream>

int main() {
  try {
    Arduino arduino("COM6");
    arduino.sendMessage("Hello world!");

    std::string response = arduino.readMessage();
    std::cout << "Response from Arduino: " << response << std::endl;
  } catch (const std::exception& ex) {
    std::cerr << "Error: " << ex.what() << std::endl;
  }

  std::cin.get();

  return 0;
}
