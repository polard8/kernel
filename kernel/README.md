# kernel - The kernel.

This is code for the base kernel. It builds the image KERNEL.BIN.

## The folders

```
 * docs    - Documentation.
 * include - Main header files for the kernel.
 * kctl    - Control resources layer.
 * kres    - Kernel resources layer.
```

## Why these layers?

```
  Based on the idea that we need to control
  the kernel resourses used by the process groups
  we put all these resources into a single
  folder called kres. So the folder kctl needs
  to control the access to theses resources
  inside the kres folder.
```
