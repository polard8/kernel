
    Two classes for system calls:
    ============================

    io/    (i/o related)
       + fs
       + networking
       + dd


    mk/    (process related)
       + scheduler
       + mm
       + ipc
   -----------------------------------
   
   Todas as system calls devem ser direcionadas para uma dessas duas pastas,
    onde ficarão os wrappers que chamarão as rotinas que estão em outras partes
   do projeto.
   
   O projeto em si pode ser organizado de forma a respeitar essa ordem
   das rotinas chamadoras.





