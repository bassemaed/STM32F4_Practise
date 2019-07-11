#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "diag/Trace.h"

#define SETBIT(REG, BIT)			(REG) |= (1<<(BIT))
#define RESETBIT(REG, BIT)			(REG) &=~ (1<<(BIT))
#define SETBIT_N(REG,BIT,NUM)		(REG) |= ((NUM)<<(BIT))
#define RESETBIT_N(REG,BIT,NUM)		(REG) &=~ ((NUM)<<(BIT))
#define READBIT(REG,BIT)			((REG) & (BIT))


#endif /* __DEFINES_H__ */
