#include <tonc.h>
#ifndef __MACROS__
#define __MACROS__

#define tte_init_se_flashtext(bgnr, bgcnt)\
	tte_init_se( bgnr, bgcnt, 0xF000,CLR_YELLOW , 0, &fwf_default, NULL)


#endif // __MACROS__
