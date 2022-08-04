#include <Library/PcdLib.h>
#include <Library/DebugLib.h>
#include <Library/QemuFwCfgSimpleParserLib.h>

RETURN_STATUS
EFIAPI
SetNetworkingSupportPcds (
 VOID
 )
{
  BOOLEAN       FwCfgBool;
  RETURN_STATUS Status;

  DEBUG ((DEBUG_INFO, "[network] %a\n", __FUNCTION__));

  Status = QemuFwCfgParseBool ("etc/networking", &FwCfgBool);
  if (RETURN_ERROR (Status)) {
    DEBUG ((DEBUG_INFO,
           "[network] QemuFwCfgParseBool('etc/networking') failed, will return "
           "SUCCESS and continue without overriding PcdNetworkSupport.\n"));
    return RETURN_SUCCESS;
  }
  DEBUG ((DEBUG_INFO, "[network] etc/networking = %d\n", FwCfgBool));

  Status = PcdSetBoolS (PcdNetworkSupport, FwCfgBool);
  if (RETURN_ERROR (Status)) {
    return Status;
  }
  DEBUG ((DEBUG_INFO, "[network] PcdNetworkSupport was set to %d\n", FwCfgBool));

  return RETURN_SUCCESS;
}
