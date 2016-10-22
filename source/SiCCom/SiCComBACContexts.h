#ifndef SIC_COM_BAC_CONTEXTS_H
#define SIC_COM_BAC_CONTEXTS_H

#define CTX_STB_NUM_SIG_OFFSET			(0)
#define CTX_STB_SIG_FLAG_OFFSET			(CTX_STB_NUM_SIG_OFFSET + 1)
#define CTX_STB_ABS_COEFF_GREATER_1		(CTX_STB_SIG_FLAG_OFFSET + 16)
#define CTX_STB_ABS_COEFF_GREATER_2		(CTX_STB_ABS_COEFF_GREATER_1 + 1)
#define CTX_STB_LEVEL_OFFSET			(CTX_STB_ABS_COEFF_GREATER_2 + 1)
#define NUM_STB_COMP_CONTEXT			(CTX_STB_LEVEL_OFFSET + 16)

#define CTX_STB_LUMA_OFFSET				(0)
#define CTX_STB_CHROMA_OFFSET			(CTX_STB_LUMA_OFFSET + NUM_STB_COMP_CONTEXT)
#define NUM_STB_DIR_CONTEXT				(2 * NUM_STB_COMP_CONTEXT)

#define CTX_VSTB_BASE					(0)
#define CTX_HSTB_BASE					(CTX_VSTB_BASE + NUM_STB_DIR_CONTEXT)
#define NUM_STB_CONTEXT					(2 * NUM_STB_DIR_CONTEXT)

#define NUM_TOTAL_CONTEXT				1000

#endif
