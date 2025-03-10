import math from "@repo/cpp/math.js";
import { useState } from "react";

const { addOne } = await math();

export default function Client() {
  const [count, setCount] = useState(0);

  return (
    <div className="flex min-h-screen flex-col items-center justify-center gap-4">
      <h1 className="text-6xl font-bold">Welcome to React</h1>
      <button onClick={() => setCount(addOne(count))}>count is {count}</button>
    </div>
  );
}
