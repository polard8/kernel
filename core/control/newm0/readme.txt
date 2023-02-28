
    The kernel process:

    This is the process for the kernel image itself, called
    KERNEL.BIN. But this process also has another image
    called MOD0.BIN, found in prestier/init/modr0.
    #todo: The MOD0.BIN module cannot use the rtl libc, it is
    because we don't wanna use syscalls in ring0. So this way
    this module needs to link to the kernel using another method.
    Maybe the kernel needs to indicate the reason for calling the
    entrypoint ... and in the initialization reason the kernel
    can give to the module a list of valid entrypoints for services
    inside the kernel base.
