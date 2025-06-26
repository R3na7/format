# 🧩 String Formatter in Modern C++

## 📖 Overview

This project implements a custom `format` function in C++ that allows string formatting using placeholders like `{0}`, `{1}`, etc. The function accepts a variable number of arguments of any type that can be printed to an `std::ostream`.

### Example

```cpp
auto text = format("{1}+{1} = {0}", 2, "one");
assert(text == "one+one = 2");
```
