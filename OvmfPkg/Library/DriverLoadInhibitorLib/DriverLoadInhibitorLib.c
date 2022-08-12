// @file
// Copyright (c) 2022, Google LLC. All rights reserved.<BR>
// SPDX-License-Identifier: BSD-2-Clause-Patent
//

#include <PiDxe.h>

#include <Library/QemuFwCfgSimpleParserLib.h>
#include <Library/UefiBootServicesTableLib.h>

EFI_STATUS
EFIAPI
DriverLoadInhibitorLibConstructor (
  IN  EFI_HANDLE        Handle,
  IN  EFI_SYSTEM_TABLE  *SystemTable
  )
{
  RETURN_STATUS     Status;
  BOOLEAN           Enabled;

  Status = QemuFwCfgParseBool (FixedPcdGetPtr (PcdDriverInhibitorFwCfgVarName),
                               &Enabled);
  if (!RETURN_ERROR (Status) && !Enabled) {
    return gBS->Exit (Handle, EFI_REQUEST_UNLOAD_IMAGE, 0, NULL);
  }
  return EFI_SUCCESS;
}
