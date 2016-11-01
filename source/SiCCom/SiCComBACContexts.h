#ifndef SIC_COM_BAC_CONTEXTS_H
#define SIC_COM_BAC_CONTEXTS_H

// Contexts for the Sub-image Transform Blocks (STBs)
#define CTX_STB_CODE_BLOCK_OFFSET			(0)
#define CTX_STB_LAST_SIG_COARSE_OFFSET		(CTX_STB_CODE_BLOCK_OFFSET + 1)
#define CTX_STB_LAST_SIG_FINE_OFFSET		(CTX_STB_LAST_SIG_COARSE_OFFSET + 1)
#define CTX_STB_SIG_FLAG_OFFSET				(CTX_STB_LAST_SIG_FINE_OFFSET + 1)
#define CTX_STB_ABS_COEFF_GREATER_1_OFFSET	(CTX_STB_SIG_FLAG_OFFSET + 64)
#define CTX_STB_ABS_COEFF_GREATER_2_OFFSET	(CTX_STB_ABS_COEFF_GREATER_1_OFFSET + 1)
#define CTX_STB_ABS_COEFF_LEVEL_OFFSET		(CTX_STB_ABS_COEFF_GREATER_2_OFFSET + 1)
#define NUM_STB_COMP_CONTEXT				(CTX_STB_ABS_COEFF_LEVEL_OFFSET + 1)

#define CTX_STB_LUMA_OFFSET					(0)
#define CTX_STB_CHROMA_OFFSET				(CTX_STB_LUMA_OFFSET + NUM_STB_COMP_CONTEXT)
#define NUM_STB_DIR_CONTEXT					(2 * NUM_STB_COMP_CONTEXT)

#define CTX_VSTB_BASE						(0)
#define CTX_HSTB_BASE						(CTX_VSTB_BASE + NUM_STB_DIR_CONTEXT)
#define NUM_STB_CONTEXT						(2 * NUM_STB_DIR_CONTEXT)

// Contexts for the Prediction Blocks (PBs)
#define CTX_PB_BASE							(CTX_VSTB_BASE + NUM_STB_CONTEXT)
#define CTX_PB_LUMA_MODE_DC					(CTX_PB_BASE)
#define CTX_PB_LUMA_COPY_MODE				(CTX_PB_LUMA_MODE_DC + 1)
#define CTX_PB_LUMA_COPY_DIR				(CTX_PB_LUMA_COPY_MODE + 1)
#define CTX_PB_LUMA_COPY_SOURCE				(CTX_PB_LUMA_COPY_DIR + 1)
#define CTX_PB_CHROMA_SOURCE_MSB			(CTX_PB_LUMA_COPY_SOURCE + 1)
#define CTX_PB_CHROMA_SOURCE_LSB			(CTX_PB_CHROMA_SOURCE_MSB + 1)
#define NUM_PB_CONTEXT						(CTX_PB_CHROMA_SOURCE_LSB + 1)

// Contexts for the Residual Transform Blocks (RTBs)
#define CTX_RTB_CODE_BLOCK_OFFSET			(0)
#define CTX_RTB_LAST_SIG_COARSE_OFFSET		(CTX_RTB_CODE_BLOCK_OFFSET + 1)
#define CTX_RTB_LAST_SIG_FINE_OFFSET		(CTX_RTB_LAST_SIG_COARSE_OFFSET + 1)
#define CTX_RTB_SIG_FLAG_OFFSET				(CTX_RTB_LAST_SIG_FINE_OFFSET + 1)
#define CTX_RTB_ABS_COEFF_GREATER_1_OFFSET	(CTX_RTB_SIG_FLAG_OFFSET + 64)
#define CTX_RTB_ABS_COEFF_GREATER_2_OFFSET	(CTX_RTB_ABS_COEFF_GREATER_1_OFFSET + 1)
#define CTX_RTB_ABS_COEFF_LEVEL_OFFSET		(CTX_RTB_ABS_COEFF_GREATER_2_OFFSET + 1)
#define NUM_RTB_COMP_CONTEXT				(CTX_RTB_ABS_COEFF_LEVEL_OFFSET + 1)

#define CTX_RTB_LUMA_BASE					(CTX_PB_BASE + NUM_PB_CONTEXT)
#define CTX_RTB_CHROMA_BASE					(CTX_RTB_LUMA_BASE + NUM_RTB_COMP_CONTEXT)
#define NUM_RTB_CONTEXT						(2 * NUM_RTB_COMP_CONTEXT)

#define NUM_TOTAL_CONTEXT					(NUM_STB_CONTEXT + NUM_PB_CONTEXT + NUM_RTB_CONTEXT)

#endif
