# React Components in C++ (Yes Seriously)

```cpp
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
    bindMethod(&Counter::increment, "increment");
  }

  void increment()
  {
    CounterState newState = state;
    newState.count += 1;
    setState(newState);
  }

  Element render() override
  {
    return h("div", {{"className", "min-w-[200px]"}},
             h("h1", {{"className", "text-2xl"}},
               text("Counter (C++)")),
             h("p", {{"className", "text-lg"}},
               text("Count: " + std::to_string(state.count))),
             h("button",
               {{"className", "bg-blue-500 text-white px-4 py-2 rounded hover:bg-blue-700"},
                {"onClick", getBoundMethod("increment")}},
               text("Increment")));
  }
};
```

## Limitations

- No SSR
- No Hot Reloading
- so many honestly

Its really fragile but does work so
Its 2 am and I nerded sniped myself into this 5 hours ago and have work to do so I'm calling it here
