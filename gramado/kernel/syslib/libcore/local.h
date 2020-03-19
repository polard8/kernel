
/*
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
*/

/*
 * Return true iff the given FILE cannot be written now.
 */


/*
#define	cantwrite(fp) \
	((((fp)->_flags & __SWR) == 0 || (fp)->_bf._base == NULL) && \
	 __swsetup(fp))
*/
 

/*
 * Detect if the current file position fits in a long int.
 */

/*
static __inline bool
__long_overflow(off_t pos)
{
	return (pos < LONG_MIN) || (pos > LONG_MAX);
}
*/



