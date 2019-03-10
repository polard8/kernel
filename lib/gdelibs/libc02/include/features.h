
/*
 * File: features.h
 *
 * Semelhante à glibc, aqui será o lugar de coniguração da biblioteca.
 *
 * History:
 *     2019 - Created by Fred Nora.
 */


#ifndef __FEATURES_H
#define __FEATURES_H 1

/*
 Descrições
 (baseado na glibc)
 
 
   These are defined by the user (or the compiler)
   to specify the desired environment: 
   ----------------------------------------------------
   
   __STRICT_ANSI__	ISO Standard C.
   _GRAMADO_SOURCE  Gramado stuff. 
   _POSIX_SOURCE	IEEE Std 1003.1.
   ...
   
   
   These are defined by this file and are used by the
   header files to decide what to declare or define:
   
   __USE_GRAMADO		Define GRAMADO extensions.
   __USE_POSIX		Define IEEE Std 1003.1 things.
   __USE_POSIX2		Define IEEE Std 1003.2 things.
   ...
 
 */


/* Limpando tudo ...*/
/* Undefine everything, so we get a clean slate.  */
#undef	__USE_GRAMADO
#undef	__USE_POSIX
#undef	__USE_POSIX2
//...

/* Use everything in this case*/
#ifdef	_GRAMADO_SOURCE
# undef  _GRAMADO_SOURCE
# define _GRAMADO_SOURCE 1
# undef _POSIX_SOURCE
# define _POSIX_SOURCE
//...
#endif

/* If nothing is defined, define _DEFAULT_SOURCE.  */
#if (defined _DEFAULT_SOURCE					\
     || (!defined __STRICT_ANSI__				\
	 && !defined _GRAMADO_SOURCE				\
	 && !defined _POSIX_SOURCE  )  )          
# undef  _DEFAULT_SOURCE
# define _DEFAULT_SOURCE	1
#endif


#ifdef	_GRAMADO_SOURCE
# define __USE_GRAMADO	1
#endif


#endif /*features.h*/
