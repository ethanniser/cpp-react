import math from "@repo/cpp/math.js";
import React from "react";
import { useState } from "react";

const Module = await math();
const { addOne, Counter } = Module;

let id = 0;
globalThis.cppInstances = new Map();

export function createCppComponent(CppClass: any) {
  return class CppWrapper extends React.Component {
    private cppInstance: T;

    constructor(props: any) {
      super(props);
      this.cppInstance = new CppClass();
      const nextId = id++;
      const stringifiedId = nextId.toString();
      globalThis.cppInstances.set(stringifiedId, this.cppInstance);
      this.cppInstance.setId(stringifiedId);

      this.cppInstance.setStateChangeCallback(() => {
        this.forceUpdate();
      });
    }

    render() {
      const element = this.cppInstance.render();
      return element.toReactElement(React);
    }
  };
}

const CounterComponent = createCppComponent(Counter);

export default function Client() {
  const [count, setCount] = useState(0);

  return (
    <div className="flex min-h-screen flex-col items-center justify-center gap-4">
      <h1 className="text-6xl font-bold">Welcome to React</h1>
      <button onClick={() => setCount(addOne(count))}>count is {count}</button>
      <CounterComponent />
      <CounterComponent />
    </div>
  );
}
