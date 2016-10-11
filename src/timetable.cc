#include <iostream>

#include "transport.h"


int main() {
  Transport t("ws://shark-nyc1.transio.us:8080/ws");
  t.subscribe("vehicles.4004", [](MPNode args, MPNode kwargs) {
    std::cout << "Received event: " << args << "\n";
  });
  t.start();

  return 0;
}
