Standard Header Files

The following include files are part of the Xlib standard:

<X11/Xlib.h>
	

This is the main header file for Xlib. The majority of all Xlib symbols are declared by including this file. 
This file also contains the preprocessor symbol XlibSpecificationRelease. This symbol is defined to have the 6 in this release of the standard. 
(Release 5 of Xlib was the first release to have this symbol.)

<X11/X.h>
	

This file declares types and constants for the X protocol that are to be used by applications. 
It is included automatically from <X11/Xlib.h> so application code should never need to reference this file directly.

<X11/Xcms.h>
	

This file contains symbols for much of the color management facilities described in chapter 6. 
All functions, types, and symbols with the prefix "Xcms", plus the Color Conversion Contexts macros, are declared in this file. 
<X11/Xlib.h> must be included before including this file.

<X11/Xutil.h>
	

This file declares various functions, types, and symbols used for inter-client communication and application utility functions, 
which are described in chapters 14 and 16. <X11/Xlib.h> must be included before including this file.

<X11/Xresource.h>
	

This file declares all functions, types, and symbols for the resource manager facilities, which are described in chapter 15. 
<X11/Xlib.h> must be included before including this file.

<X11/Xatom.h>
	

This file declares all predefined atoms, which are symbols with the prefix "XA_".

<X11/cursorfont.h>
	

This file declares the cursor symbols for the standard cursor font, which are listed in Appendix B. All cursor symbols have the prefix "XC_".

<X11/keysymdef.h>
	

This file declares all standard KeySym values, which are symbols with the prefix "XK_". The KeySyms are arranged in groups,
and a preprocessor symbol controls inclusion of each group. The preprocessor symbol must be defined prior to inclusion of the 
file to obtain the associated values. The preprocessor symbols are XK_MISCELLANY, XK_XKB_KEYS, XK_3270, XK_LATIN1, XK_LATIN2, XK_LATIN3, XK_LATIN4,
XK_KATAKANA, XK_ARABIC, XK_CYRILLIC, XK_GREEK, XK_TECHNICAL, XK_SPECIAL, XK_PUBLISHING, XK_APL, XK_HEBREW, XK_THAI, and XK_KOREAN.

<X11/keysym.h>
	

This file defines the preprocessor symbols XK_MISCELLANY, XK_XKB_KEYS, XK_LATIN1, XK_LATIN2, XK_LATIN3, XK_LATIN4, and XK_GREEK and then includes <X11/keysymdef.h>.

<X11/Xlibint.h>
	

This file declares all the functions, types, and symbols used for extensions, which are described in Appendix C. This file automatically includes <X11/Xlib.h>.

<X11/Xproto.h>
	

This file declares types and symbols for the basic X protocol, for use in implementing extensions. 
It is included automatically from <X11/Xlibint.h>, so application and extension code should never need to reference this file directly.

<X11/Xprotostr.h>
	

This file declares types and symbols for the basic X protocol, for use in implementing extensions. 
It is included automatically from <X11/Xproto.h>, so application and extension code should never need to reference this file directly.

<X11/X10.h>
	

This file declares all the functions, types, and symbols used for the X10 compatibility functions, which are described in Appendix D. 