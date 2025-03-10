#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <emscripten/console.h>
#include "CSX.hpp"

using namespace emscripten;

template <typename State>
class Component
{
protected:
    State state;
    val stateChangeCallback;
    std::string id;
    std::map<std::string, std::function<val()>> boundMethods;

    template <typename T>
    void bindMethod(void (T::*method)(), const std::string &name)
    {
        boundMethods[name] = [this, name]()
        {
            return val::global("Function").new_(val(std::string("globalThis.cppInstances.get('") + id + std::string("').") + name + std::string("()")));
        };
    }

public:
    Component() : stateChangeCallback(val::undefined()) {}
    virtual ~Component() {}

    virtual Element render() = 0;

    void setState(const State &newState)
    {
        state = newState;
        if (!stateChangeCallback.isUndefined())
        {
            stateChangeCallback();
        }
    }

    void setStateChangeCallback(val callback)
    {
        stateChangeCallback = callback;
    }

    val getBoundMethod(const std::string &name)
    {
        return boundMethods[name]();
    }

    void setId(std::string id_)
    {
        // val::global("console").call<void>("log", val("Setting id to " + id_));
        id = id_;
    }
};
