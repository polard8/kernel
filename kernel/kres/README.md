# kres

  The resources. The built-in subsystems.

```
  These folders represents the built-in subsistems
  in the kernel core that possibly can be virtualized
  and controlled by cgroups or namespaces forming the
  infra-structure for a container runtime.
```

## Folders

```
  * dev   - A place dor built-in device drivers.
  * fs    - Filesystems
  * gramk - This is where the kernel controls the user interactions
            with keyboard, mouse and display.
  * ke    - CPU management.
          - Process and thread management. It handles the dispatcher
            and the scheduler.
          - This is also a place for global components of the system.
  * mm    - Memory management.
  * net   - Network management.
          - Network initialization, socket, domains and protocols.
```

