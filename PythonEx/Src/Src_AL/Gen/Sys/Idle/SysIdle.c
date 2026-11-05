#include <Sys/Idle/SysIdle.h>
#include <Wdg.h>

void SysIdle_OsIdleTask(void)
{
  Wdg_Trigger();
}
