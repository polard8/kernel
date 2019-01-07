
format PE GUI 4.0
entry start

include 'win32a.inc'

section '.text' code readable executable

  start:
	invoke	SetLastError,0
	invoke	ShowLastError,HWND_DESKTOP
	invoke	ExitProcess,0

section '.idata' import data readable writeable

  library kernel,'KERNEL32.DLL',\
	  errormsg,'ERRORMSG.DLL'

  import kernel,\
	 SetLastError,'SetLastError',\
	 ExitProcess,'ExitProcess'

  import errormsg,\
	 ShowLastError,'ShowLastError'
