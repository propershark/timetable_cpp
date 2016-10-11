#pragma once

#include <list>

#include "wamped/Wamp.h"
#include "wamped/WampTransportWS.h"

#include "wamp_actions.h"


class Transport {
  // To use Raw Sockets instead, simply change `WampTransportWS` to `WampTransportRS`.
  typedef WampTransportWS transport_t;


  // The URI of the WAMP Router where Timetable will be listening for calls.
  std::string router_url;
  // Ordered list of actions to perform after connection to the WAMP router.
  std::list<WampAction*> action_queue;

  // The transport driver for the WAMP client.
  transport_t transport;
  // The WAMP client interface. All actions interacting with WAMP will go
  // through here.
  Wamp *wamp;


  public:
    Transport(std::string router) : router_url(router), transport(transport_t(router)), wamp(new Wamp(transport)) {
      // If the connection is closed for any reason, immediately attempt to reconnect.
      wamp->onClose = [&]() {
        wamp->connect();
      };
    };

    ~Transport() {
      // As a pointer, the `wamp` destructor must be explicitly called to be
      // garbage collected properly.
      delete wamp;
    };

    // Start a connection to the WAMP router, performing all queued actions
    // that were requested before this call.
    // NOTE: this call will block forever while waiting for events from the
    // router.
    void start() {
      wamp->connect([&]() {
        _perform_actions();
      });
      while(true) transport.process();
    };


    // Proxy WAMP actions through to the actual client.
    // TODO: Determine if a better forwarding paradigm exists.
    void subscribe(std::string const &topic, TSubscriptionCallback callback = nullptr) {
      action_queue.push_front(new WampSubscribeAction(topic, callback));
    };
    template<typename ...ARGS>
    void publish(std::string const &topic, ARGS&& ...args) {
      action_queue.push_front(new WampPublishAction<ARGS...>(topic, std::forward<ARGS>(args)...));
    };

    void call(std::string const &topic, const MsgPack &arguments, const MsgPack &argumentsKW, TCallCallback callback) {
      action_queue.push_front(new WampCallAction(topic, arguments, argumentsKW, callback));
    };
    template<typename Proc>
    void procedure(std::string const &topic, Proc p, TRegisterCallback callback = nullptr) {
      action_queue.push_front(new WampRegisterAction<Proc>(topic, p, callback));
    };


  private:
    // Dynamically generate an `onJoin` callback function containing all of the
    // previously-queued actions.
    void _perform_actions() {
      for(auto* next_action : action_queue) next_action->perform(wamp);
    };
};
