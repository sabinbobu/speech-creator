// *****************************************************************************
// Rte_Mac.h
//
// 
// *****************************************************************************


#ifdef THREAD_NAME

CONCAT3(__NO_RETURN void thread_, THREAD_NAME, _func(void *argument))
{
  uint32_t Flags, Index;
  
  RTE_EVTREC2(CONCAT3(RTE_EVTREC_thread_, THREAD_NAME, _Start), (uint32_t)osThreadGetId(), (uint32_t)argument);

  Rte_Prestart((osMessageQueueId_t)argument);
 
  for(;;)
  {
    Flags = osThreadFlagsWait(THREADFLAGANY, osFlagsWaitAny, osWaitForever);
    
    if((Flags & OS_EVTFLAG_MASK_ERROR) == 0)
    {
      // Index = 0..30 (or 31 if all flags are cleared)
      while((Index = (__clz(Flags)-1)) < 31)
      {
        if(Index < CONCAT3(eRteThreadFlag_, THREAD_NAME, _Count))
        {
          RTE_EVTREC2(CONCAT3(RTE_EVTREC_Thread_, THREAD_NAME, _Runnable), (uint32_t)Index, CONCAT3((uint32_t)RTE_Runnable_, THREAD_NAME, _func[(Index)]));
          
          #if((THREAD_NAME == T_HH) || (THREAD_NAME == T_HL) || (THREAD_NAME == T_LH) || (THREAD_NAME == T_LL))
          RTE_RUNNABLE_SYNC_T_ENTRY
          #elif((THREAD_NAME == U_HH) || (THREAD_NAME == U_HL) || (THREAD_NAME == U_LH) || (THREAD_NAME == U_LL))
          RTE_RUNNABLE_SYNC_U_ENTRY
          #else
            #error "Invalid THREAD_NAME specified"
          #endif

          #if(OS_RTE_MONITOR == 1)
            RteMonitorBuffer[CONCAT3(eThread_, THREAD_NAME, _Zone)] = CONCAT3(RTE_Runnable_, THREAD_NAME, _func[(Index)]);
            RteMonitorActive = CONCAT3(RTE_Runnable_, THREAD_NAME, _func[(Index)]);
          #endif
          
          // call runnable
          CONCAT3(RTE_Runnable_, THREAD_NAME, _func[(Index)]());

          #if(OS_RTE_MONITOR == 1)
            RteMonitorBuffer[CONCAT3(eThread_, THREAD_NAME, _Zone)] = (pRunnable_t)0;
            RteMonitorActive = (pRunnable_t)0;
          #endif

          #if((THREAD_NAME == T_HH) || (THREAD_NAME == T_HL) || (THREAD_NAME == T_LH) || (THREAD_NAME == T_LL))
          RTE_RUNNABLE_SYNC_T_EXIT
          #elif((THREAD_NAME == U_HH) || (THREAD_NAME == U_HL) || (THREAD_NAME == U_LH) || (THREAD_NAME == U_LL))
          RTE_RUNNABLE_SYNC_U_EXIT
          #else
            #error "Invalid THREAD_NAME specified"
          #endif
        }
        else
        {
          RTE_EVTREC2(CONCAT3(RTE_EVTREC_Thread_, THREAD_NAME, _Index_Error), (uint32_t)Flags, (uint32_t)Index);
          RTE_ERRORHANDLER(__LINE__);
        }
        
        Flags &= (~THREADFLAGMASK(Index));
      }
    }
    else
    {
      RTE_EVTREC2(RTE_EVTREC_Thread_Internal_Error, __LINE__, 0UL);
      RTE_ERRORHANDLER(__LINE__);
    }
  }
}

#undef THREAD_NAME

#endif  // THREAD_NAME

