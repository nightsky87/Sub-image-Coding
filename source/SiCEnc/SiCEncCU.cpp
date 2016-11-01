#include "SICEncCU.h"

void SiCEncCU(s16 *img, u16 width, u16 height, paramStruct param)
{
	// Create the Coding Pyramid (CP) structure
	cpStruct *cpSmallest, *cpLargest, *cp;

	// Begin with a 4x4 Downsampled CU (DCU) and allocate space for each DCU
	cp = new cpStruct;
	cpLargest = cp;
	cpSmallest = cp;
	cpSmallest->smaller = NULL;
	for (u8 i = 4; i <= CU_SIZE; i *= 2)
	{
		// Allocate space for the DCU coefficients
		u16 dcuSize = i * i;
		cp->pLuma = new s16[dcuSize];
		cp->pChroma1 = new s16[dcuSize];
		cp->pChroma2 = new s16[dcuSize];
		cp->predMode = new u8[dcuSize / 16];

		// Write the DCU parameters
		cp->width = i;
		cp->height = i;
		cp->chromaSub = param.chromaSub;

		// Allocate the next DCU
		cpLargest = cp;
		cp = new cpStruct;
		cp->smaller = cpLargest;
		cpLargest->larger = cp;
	}
	cpLargest->larger = NULL;
	delete(cp);

	// Generate the coefficients in the CP
	generateCP(img, width, height, cpLargest);

	// Encode each Coding Pyramid Slice (CPS) starting from the coarsest scale
	cp = cpSmallest;
	u8 qp = param.qp;
	while (cp->width < CU_SIZE)
	{
		// Search for the best predictors for the luma component
		predSearch(cp);

		// Encode the prediction modes

		// Transform and quantize the residuals
		dct(cp->larger);
		quantConst(cp->larger, qp);

		// Encode the residuals

		// Reconstruct the larger slice
		dequantConst(cp->larger, qp);
		idct(cp->larger);
		pred(cp);

		// Apply an optional filter to the reconstructed slice
		//sliceFilt(cp, 8);

		// Proceed to the next slice
		cp = cp->larger;
	}

	// Copy to the image
	for (u8 y = 0; y < CU_SIZE; y++)
		memcpy(&img[width * y], &cpLargest->pLuma[cpLargest->width * y], CU_SIZE * sizeof(s16));
}

void generateCP(s16 *img, u16 width, u16 height, cpStruct *cpLargest)
{
	// Copy all luma pixels to the finest scale
	for (u8 y = 0; y < CU_SIZE; y++)
	{
		memcpy(&cpLargest->pLuma[cpLargest->width * y], &img[width * y], CU_SIZE * sizeof(s16));
	}

	// Generate each slice of the CP
	cpStruct *cp = cpLargest;
	while (cp->width > 4)
	{
		for (u8 y = 0; y < cp->height; y += 2)
		{
			for (u8 x = 0; x < cp->width; x += 2)
			{
				cp->smaller->pLuma[cp->smaller->width * (y / 2) + (x / 2)] = cp->pLuma[cp->width * y + x];
			}
		}
		cp = cp->smaller;
	}
}

void sliceFilt(cpStruct *cp, u8 preserve)
{
	// Filter the CPS
	for (u8 y = 1; y < cp->height - 1; y++)
	{
		for (u8 x = 1; x < cp->width - 1; x++)
		{
			cp->pLuma[cp->width * y + x] *= preserve;
			cp->pLuma[cp->width * y + x] += cp->pLuma[cp->width * (y - 1) + (x - 1)];
			cp->pLuma[cp->width * y + x] += cp->pLuma[cp->width * (y - 1) + x];
			cp->pLuma[cp->width * y + x] += cp->pLuma[cp->width * (y - 1) + (x + 1)];
			cp->pLuma[cp->width * y + x] += cp->pLuma[cp->width * y + (x - 1)];
			cp->pLuma[cp->width * y + x] += cp->pLuma[cp->width * y + (x + 1)];
			cp->pLuma[cp->width * y + x] += cp->pLuma[cp->width * (y + 1) + (x - 1)];
			cp->pLuma[cp->width * y + x] += cp->pLuma[cp->width * (y + 1) + x];
			cp->pLuma[cp->width * y + x] += cp->pLuma[cp->width * (y + 1) + (x + 1)];
			cp->pLuma[cp->width * y + x] /= (preserve + 8);
		}
	}
}

