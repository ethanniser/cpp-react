#include <emscripten/bind.h>

int addOne(int x)
{
  return x + 1;
}

EMSCRIPTEN_BINDINGS(math_module)
{
  emscripten::function("addOne", &addOne);
}
