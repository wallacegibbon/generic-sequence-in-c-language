## Introduction

You should use generic sequence with pointer variable:
```c
struct generic_sequence *s;
```

Creating the sequence and initializing it with `gs_new`:
```c
s = gs_new(3, sizeof(float));
```

Now you can `set`/`get` value `to`/`from` it. Just like normal arrays:
```c
gs_set(s, 1, &float_val);
```

```c
gs_get(s, 1, &float_val);
```

Or you can use it as a stack:
```c
gs_push(s, &float_val);
```

```c
gs_pop(s, &float_val);
```

You can set a comparing function for it:
```c
int float_cmp(float *left, float *right) {
	return *left - *right;
}

gs_set_cmp_fn(s, (generic_sequence_cmp_fn)float_cmp);
```

Then you can sort it with:
```c
gs_sort(s);
```

You should free the data when you don't need it.
```c
gs_free(s);
```


## Run tests

```sh
gcc src/*.c && ./a.out
```
