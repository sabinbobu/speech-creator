// *****************************************************************************
// Rte_Chk.h
//
// 
// *****************************************************************************

#ifndef __RTE_CHK_H
#define __RTE_CHK_H


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// includes
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <Rte.h>
#include <Rte_Cfg.h>


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// preprocessor definitions
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define ALRTEGEN_VERSION_MAJOR_MIN    0
#define ALRTEGEN_VERSION_MINOR_MIN   27

#define RTE_SCHEDULE_POLICY_DEFAULT   RTE_PREEMPT_FULL


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// preprocessor checks and settings
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// check AlRteGenerator version
#if((ALRTEGENERATOR_VERSION_MAJOR <  ALRTEGEN_VERSION_MAJOR_MIN) || \
   ((ALRTEGENERATOR_VERSION_MAJOR == ALRTEGEN_VERSION_MAJOR_MIN) && \
    (ALRTEGENERATOR_VERSION_MINOR <  ALRTEGEN_VERSION_MINOR_MIN)))
  #error "AlRteGenerator Version is obsolete! Please update this tool!"
#endif

// set default RTE scheduling policy
#ifndef RTE_SCHEDULE_POLICY
#define RTE_SCHEDULE_POLICY   RTE_SCHEDULE_POLICY_DEFAULT
#endif


#endif // __RTE_CHK_H

