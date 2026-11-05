#ifndef __APPLI_H__
#define __APPLI_H__

extern void APPLI_CAN_enable_interrupt(void);
extern void APPLI_CAN_disable_interrupt(void);
extern void APPLI_Run(void);
extern void APPLI_enable_interrupt(void);
extern void APPLI_disable_interrupt(void);
extern void APPLI_CAN_Interrupt_Enter(void);
extern void APPLI_CAN_Interrupt_Exit(void);

#endif // __APPLI_H__
