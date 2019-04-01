


/*
 * Exception/Trap Stack Frame
 */

//netbsd trapframe for x86.

/*
struct trapframe {
	uint16_t	tf_gs;
	uint16_t	tf_gs_pad;
	uint16_t	tf_fs;
	uint16_t	tf_fs_pad;
	uint16_t	tf_es;
	uint16_t	tf_es_pad;
	uint16_t	tf_ds;
	uint16_t	tf_ds_pad;
	int	tf_edi;
	int	tf_esi;
	int	tf_ebp;
	int	tf_ebx;
	int	tf_edx;
	int	tf_ecx;
	int	tf_eax;
	int	tf_trapno;
	// below portion defined in 386 hardware 
	int	tf_err;
	int	tf_eip;
	int	tf_cs;
	int	tf_eflags;
	//below used when transitting rings (e.g. user to kernel) 
	int	tf_esp;
	int	tf_ss;
};
*/

/*
 * Interrupt stack frame
 */
//netbsd int frame for x86.
/*
struct intrframe {
	int	if_ppl;
	int	if_gs;
	int	if_fs;
	int	if_es;
	int	if_ds;
	int	if_edi;
	int	if_esi;
	int	if_ebp;
	int	if_ebx;
	int	if_edx;
	int	if_ecx;
	int	if_eax;
	uint32_t __if_trapno;	// for compat with trap frame - trapno 
	uint32_t __if_err;	// for compat with trap frame - err 
	// below portion defined in 386 hardware 
	int	if_eip;
	int	if_cs;
	int	if_eflags;
	//below only when transitting rings (e.g. user to kernel) 
	int	if_esp;
	int	if_ss;
};
*/




