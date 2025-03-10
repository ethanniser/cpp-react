import { Counter } from "@repo/cpp/Counter";
import React from "react";
import { useState } from "react";

export default function Client() {
  return (
    <div className="flex min-h-screen flex-col items-center justify-center gap-4">
      <h1 className="text-6xl font-bold text-center">
        C++ React <br /> Class Components
      </h1>
      <h2 className="italic text-4xl">Because why not?</h2>
      <ReactCounter />
      <Counter />
      <ReactCounter />
      <Counter />
      <footer className="text-center">
        <a
          href="https://github.com/ethanniser/cpp-react"
          className="hover:underline"
        >
          Source
        </a>
        {" | "}
        <a href="https://ethanniser.dev" className="hover:underline">
          Made by Ethan Niser
        </a>
      </footer>
    </div>
  );
}

function ReactCounter() {
  const [count, setCount] = useState(0);
  return (
    <div className="min-w-[200px]">
      <h1 className="text-2xl">Counter (React)</h1>
      <h2 className="text-lg">Count: {count}</h2>
      <button
        onClick={() => setCount(count + 1)}
        className="bg-blue-500 text-white px-4 py-2 rounded hover:bg-blue-700"
      >
        Increment
      </button>
    </div>
  );
}
