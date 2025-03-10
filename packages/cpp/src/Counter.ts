import InitModule from "../out/Counter.js";
import { createCppComponent } from "./shim";

const Module = await InitModule();
const { Counter } = Module;

const CounterComponent = createCppComponent(Counter);

export { CounterComponent as Counter };
