/***************************************************************************

 
 ***************************************************************************/
#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <Windows.h>
#include <assert.h>

#include "communicationDefines.h"

//mwm: Comes from QMK? Missing license...
//a set of tools for dataconversion

namespace ToolBox //made it a namespace, rather than a class
{
  int Data2Int(int *Data , int Start, bool is_signed = true);
  INT16 Data2Int(UINT8 *Data , int Start, bool is_signed = true);
  UINT8 Encode64(UINT8 TX_Data[serialComms::RXD_BUFFER_LEN], UINT8 Data[serialComms::RXD_BUFFER_LEN],unsigned int Length);
  UINT8  Decode64(UINT8 decodedDataOut[serialComms::RXD_BUFFER_LEN], UINT8 encodedDataIn[serialComms::RXD_BUFFER_LEN], UINT8 ReceivedBytes);
  void AddCRC(UINT8 packet[serialComms::RXD_BUFFER_LEN], unsigned int datalen);
};

#endif // TOOLBOX_H
