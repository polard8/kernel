
; example of simplified Windows programming using complex macro features

include 'win32ax.inc' ; you can simply switch between win32ax, win32wx, win64ax and win64wx here

.code

  start:

	invoke	MessageBox,HWND_DESKTOP,"May I introduce myself?",invoke GetCommandLine,MB_YESNO

	.if eax = IDYES
		invoke	MessageBox,HWND_DESKTOP,"Hi! I'm the example program!","Hello!",MB_OK
	.endif

	invoke	ExitProcess,0

.end start
