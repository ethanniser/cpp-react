#include <emscripten/bind.h>
#include "CSX.hpp"
#include "Component.hpp"

struct CounterState
{
  int count;
};

class Counter : public Component<CounterState>
{
public:
  Counter()
  {
    state.count = 0;
    // bindMethod("increment", &Counter::increment);
  }

  void increment()
  {
    CounterState newState = state;
    newState.count += 1;
    setState(newState);
  }

  Element render() override
  {
    return h("div", {{"className", "p-4"}},
             h("h1", {{"className", "text-2xl"}},
               text("Counter")),
             h("p", {{"className", "text-lg"}},
               text("Count: " + std::to_string(state.count))),
             h("button",
               {{"className", "bg-blue-500 text-white px-4 py-2 rounded"},
                // {"onClick", getBoundMethod("increment")}},
                {}},
               text("Increment")));
  }
};

EMSCRIPTEN_BINDINGS(math_module)
{
  // Base component binding
  class_<Component<CounterState>>("BaseComponent")
      .function("render", &Component<CounterState>::render)
      .function("setStateChangeCallback", &Component<CounterState>::setStateChangeCallback);

  // Counter binding
  class_<Counter, base<Component<CounterState>>>("Counter")
      .constructor()
      .function("render", &Counter::render)
      .function("setStateChangeCallback", &Counter::setStateChangeCallback);
}
