/*
 * globals.h
 *
 *  Created on: Nov 14, 2009
 *      Author: carlos
 *
 * Description: For global variables used throughout the program
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

/** @brief Provides a global enumeration for the implemented methods of digital image correlation in the Qcorr class.
 *  The enumerated correlation methods are: N0_CORR_METHOD = 0, CROSS_CORR = 1, SUM_SQ_DIFF = 2, or CORR_COEFF = 3
 */
enum MethodOfCorrelation{
      N0_CORR_METHOD = 0,
      CROSS_CORR = 1,
      SUM_SQ_DIFF        = 2,
      CORR_COEFF = 3
};

#endif /* GLOBALS_H_ */
