format PE64 console
entry start

include 'win64a.inc'

section '.text' code readable executable

start:
	sub	rsp,8

	invoke	WriteMessage,message

	invoke	ExitProcess,0

section '.data' data readable

  message db "Hi! I'm the example program!",0

section '.idata' import data readable writeable

  library kernel32,'KERNEL32.DLL',\
	  writemsg,'WRITEMSG.DLL'

  include 'api/kernel32.inc'

  import writemsg,\
	 WriteMessage,'WriteMessage'