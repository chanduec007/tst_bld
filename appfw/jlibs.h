
#include "os_includes.h"
#include <jansson.h>

typedef struct
{
	uint32_t scrid;
	uint32_t modid;
	uint32_t funid;
	uint32_t msgid;
} msd01_t;

typedef enum
{
	HMS_MOD_FUNC_UNKNOWN = 0,

	HMS_MOD1_FUNC1_DEF1,
	HMS_MOD1_FUNC2_DEF2,
	HMS_MOD1_FUNC3_DEF3,

	HMS_MOD2_FUNC1_DEF1,
	HMS_MOD2_FUNC2_DEF2,
	HMS_MOD2_FUNC3_DEF3
} hmsid_t;

typedef enum
{
	DGS_MOD_FUNC_UNKNOWN = 0,

	DGS_MOD1_FUNC1_DEF1,
	DGS_MOD1_FUNC2_DEF2,
	DGS_MOD1_FUNC3_DEF3
} dgsid_t;


//char *prepare_jmsd01(msd01_t msd01);
uint32_t prepare_jmsd01(msd01_t msd01);



