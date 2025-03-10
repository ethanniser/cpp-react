import { Counter } from "@repo/cpp/Counter";
import React from "react";
import { useState } from "react";

export default function Client() {
  const [count, setCount] = useState(0);

  return (
    <div className="flex min-h-screen flex-col items-center justify-center gap-4">
      <h1 className="text-6xl font-bold">Welcome to React</h1>
      <button onClick={() => setCount(count + 1)}>count is {count}</button>
      <Counter />
      <Counter />
    </div>
  );
}
