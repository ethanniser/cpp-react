import React from "react";

let id = 0;
globalThis.cppInstances = new Map();

export function createCppComponent(CppClass: any): React.ComponentType {
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
