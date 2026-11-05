#include "MemIf.h"
#if MEMIF_VERSION_INFO_API
/* MEMIF-IMP-003: provide MemIf's own standard release information when configured. */
void MemIf_GetVersionInfo(Std_VersionInfoType *VersionInfoPtr)
{
    if (VersionInfoPtr != NULL_PTR)
    {
        VersionInfoPtr->vendorID = MEMIF_VENDOR_ID;
        VersionInfoPtr->moduleID = MEMIF_MODULE_ID;
        VersionInfoPtr->sw_major_version = MEMIF_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = MEMIF_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = MEMIF_SW_PATCH_VERSION;
    }
}
#endif