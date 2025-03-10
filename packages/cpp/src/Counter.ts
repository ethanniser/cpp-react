// @ts-expect-error
import InitModule from "../out/Counter.js";
import { createCppComponent } from "./shim.js";

const Module = await InitModule();
const { Counter } = Module;

const CounterComponent = createCppComponent(Counter);

export { CounterComponent as Counter };
