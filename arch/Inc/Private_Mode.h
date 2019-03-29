#ifndef __PRIVATE_MODE_H__
#define __PRIVATE_NODE_H__

#include "Hw_Config.h"

/* Private define ------------------------------------------------------------*/
#define SP_PROCESS_SIZE               0x200 /* Process stack size */
#define SP_PROCESS                    0x02  /* Process stack */
#define SP_MAIN                       0x00  /* Main Stack */
#define THREAD_MODE_PRIVILEGED        0x00  /* Thread mode has privileaged access */
#define THREAD_MODE_UNPRIVILEGED      0x01  /* Thread mode has unprivileged access */



#ifdef PRIVATE_MODE_LOCAL
#define PRIVATE_MODE_DEF
#else
#define PRIVATE_MODE_DEF                            extern
#endif


/* Private variables ---------------------------------------------------------*/
PRIVATE_MODE_DEF uint32_t Get_Current_ThreadMode(void);
PRIVATE_MODE_DEF uint32_t Get_Current_Stack(void);
PRIVATE_MODE_DEF void Mode_Privilege_Test(void);



#endif
