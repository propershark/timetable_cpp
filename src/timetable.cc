#include <iostream>

#include "wamped/Wamp.h"
#include "wamped/WampTransportWS.h"

WampTransportWS *wt;
Wamp *wamp;

int next_visits(std::string something) {
  std::cout << "Got a request\n";

  return 10;
}

int main() {
  wt = new WampTransportWS("ws://shark-nyc1.transio.us:8080/ws");
  wamp = new Wamp(*wt);

  wamp->onClose = ([&]() {
    wamp->connect();
  });

  wamp->connect([&]() {
    std::cout << "Session joined :" << wamp->sessionID << "\n";

    // wamp->subscribe("vehicles.4004", [](MPNode args, MPNode kwargs) {
    //   std::cout << "Received event: " << args << "\n";
    // });

    wamp->registerProcedure("timetable.next_visits", next_visits, [](URI err) {
      if(!err.empty()) std::cout << "REGISTRATION ERROR:" << err << "\n";
      else std::cout << "Registration OK" << "\n";
    });
  });

  while(true) wt->process();
  return 0;
}
