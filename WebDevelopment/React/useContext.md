# useContext

```tsx
import { createContext, useContext, useState } from "react";

type Theme = "light" | "dark" | "system";

const ThemeContext = createContext<Theme>("system");

const useGetTheme = () => useContext(ThemeContext);

const Comp = () => {
  const theme = useGetTheme();
  return <div>Theme: {theme}</div>;
};

const App = () => {
  const [theme, setTheme] = useState<Theme>("system");
  const [index, setIndex] = useState(0);

  const click = () => {
    const newIndex = (index + 1) % 3;
    setIndex(newIndex);

    switch (index) {
      case 0:
        setTheme("light");
        break;
      case 1:
        setTheme("dark");
        break;
      case 2:
        setTheme("system");
        break;
    }
  };

  return (
    <>
      <div>
        <ThemeContext.Provider value={theme}>
          <Comp />
        </ThemeContext.Provider>
        <button onClick={click}>Change Theme</button>
      </div>
    </>
  );
};

export default App;
```
