# useReduce

```tsx
import { useReducer } from "react";

type Action = "inc" | "dec";

const countReducer = (state: number, action: Action): number => {
  switch (action) {
    case "inc":
      return state + 1;
    case "dec":
      return state - 1;
    default:
      throw new Error("Invalid action");
  }
};

const App = () => {
  const [state, dispatch] = useReducer(countReducer, 0);

  const handlerIncrement = () => dispatch("inc");
  const handlerDecrement = () => dispatch("dec");

  return (
    <>
      <div style={{ padding: 10 }}>
        <button onClick={handlerIncrement} className="btn btn-primary mr-2">
          Increment
        </button>
        <span>{state}</span>
        <button onClick={handlerDecrement} className="btn btn-primary ml-2">
          Decrement
        </button>
      </div>
    </>
  );
};

export default App;
```
