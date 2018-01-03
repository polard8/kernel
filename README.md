# gramado

Gramado Operating System v 0.1 
(c) Coppyright 2018 - Fred Nora.

//Compilation process:
I'm using a .bat file on Windows platform.
Check the file make-kernel.bat.

//Boot process:
The boot has two programs, BM.BIN and BL.BIN. It loads all the files.
I'm working to support GRUB boot loader. But i need to load the kernel and some other files. 
Maybe you can help me with this thing.

//Resolution:
The kernel starts in Graphics Mode, resolution 800x600x24.

//Folders:
<br>/init    = init application
<br>/kernel  = kernel
<br>/shell   = shell application 
<br>/taskman = taskman application

@frednora

<img src="https://github.com/frednora/gramado/blob/master/screenshots/gui.png">
