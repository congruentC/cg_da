# cg_da
A generic dynamic array for C (cgda). A cgda owns its buffer and grows automatically — when capacity is exhausted it doubles, so amortized push is O(1). Because the array is type-erased through `void *` and an element size, it works with any fixed-size type. The caller is responsible for passing consistently-typed elements.

Part of [CongruentC](https://github.com/CongruentC).

---

## Usage

Drop `cg_da.h` into your project. In exactly one translation unit, define the implementation macro before including:

```c
#define CGDA_IMPLEMENTATION
#include "cg_da.h"
```

Every other file includes it bare:

```c
#include "cg_da.h"
```

No build system changes are necessary, nor is linking against a separate library.

---

## Example

```c
#define CGDA_IMPLEMENTATION
#include "cg_da.h"
#include <stdio.h>

int main(void) {
    cgda arr = cgda_init(4, sizeof(int));

    for (int i = 0; i < 6; i++)
        cgda_push(&arr, &i);

    cgda_remove(&arr, 2);

    int popped;
    cgda_pop(&arr, &popped);
    printf("popped: %d\n", popped);

    for (int i = 0; i < cgda_count(&arr); i++)
        printf("%d ", ((int *)arr.data)[i]);
    printf("\n");

    cgda_free(&arr);
    return 0;
}
```

Output:
```
popped: 5
0 1 3 4
```

---

## License

MIT
