#include "wamped/Wamp.h"

class WampAction {
  protected:
    typedef WampAction base;

  public:
    std::string topic;

    enum class Action { SUBSCRIBE, PUBLISH, CALL, REGISTER } action;

    WampAction() = delete;
    WampAction(std::string topic, Action action) : topic(topic), action(action) {};

    virtual void perform(Wamp*) = 0;
};


class WampSubscribeAction : public WampAction {
  public:
    TSubscriptionCallback callback;

    WampSubscribeAction(std::string topic, TSubscriptionCallback cb) : callback(cb), base(topic, Action::SUBSCRIBE) {};

    void perform(Wamp* client) {
      client->subscribe(topic, callback);
    };
};


template<typename ...ARGS>
class WampPublishAction : public WampAction {
  public:
    std::tuple<ARGS&&...> args;

    WampPublishAction(std::string topic, ARGS&&... args) : args(std::forward<ARGS>(args)...), base(topic, Action::PUBLISH) {};

    void perform(Wamp* client) {
      client->publish(topic, std::forward<ARGS&&>(args)...);
    };
};


class WampCallAction : public WampAction {
  public:
    MsgPack args;
    MsgPack kwargs;
    TCallCallback callback;

    WampCallAction(std::string topic, MsgPack args, MsgPack kwargs, TCallCallback cb) : args(args), kwargs(kwargs), callback(cb), base(topic, Action::CALL) {};

    void perform(Wamp* client) {
      client->call(topic, args, kwargs, callback);
    };
};

template<typename Proc>
class WampRegisterAction : public WampAction {
  public:
    Proc procedure;

    WampRegisterAction(std::string topic, Proc p) : procedure(p), base(topic, Action::REGISTER) {};

    void perform(Wamp* client) {
      client->registerProcedure(topic, procedure);
    };
};
