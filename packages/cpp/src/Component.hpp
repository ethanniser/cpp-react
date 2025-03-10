#include <emscripten/bind.h>
#include "CSX.hpp"

template <typename State>
class Component
{
protected:
    State state;
    val stateChangeCallback;
    std::map<std::string, val> boundMethods;

    // Helper to bind methods
    template <typename T>
    val bind(void (T::*method)())
    {
        val instance = val(this);
        val func = val::global("Function").new_(std::string("return function() { return this.") + std::string(method) + std::string(".apply(this, arguments); }"));
        return func.call<val>("bind", instance);
    }

    // Bind method and store it
    template <typename T>
    void bindMethod(const std::string &name, void (T::*method)())
    {
        boundMethods[name] = bind(method);
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
        return boundMethods[name];
    }
};
