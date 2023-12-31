/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : 91x_emi.c
* Author             : MCD Application Team
* Version            : V2.1
* Date               : 12/22/2008
* Description        : This file provides all the EMI firmware functions.
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "91x_emi.h"
#include "91x_scu.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* These constant variables are used as masks to handle the EMI registers.  */


#define   EMI_Burst_and_PageModeRead_TL_Mask         0xFFFFF3FF
#define   EMI_Burst_and_PageModeRead_Sel_Mask         0xFFFFFEFF
#define   EMI_MemWidth_Mask                      0xFFFFFFCF
#define   EMI_WriteProtect_Mask                         0xFFFFFFF7  
#define   EMI_ByteLane_Mask                         0xFFFFFFFE  
#define   EMI_AccessRead_Dev_Mask                 0xFFFFFDFF  
#define   EMI_BurstModeWrite_Sel_Mask                 0xFFFEFFFF
#define   EMI_AccessWrite_Dev_Mask                 0xFFFDFFFF
#define   EMI_BurstModeWrite_TL_Mask                 0xFFF3FFFF


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Registers reset value */
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************
* Function Name  : EMI_DeInit
* Description    : Deinitializes the EMI peripheral registers to their default
*                  reset values.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void EMI_DeInit(void)
{

  SCU_AHBPeriphReset(__EMI, ENABLE);          /* EMI peripheral under Reset */
  SCU_AHBPeriphReset(__EMI,DISABLE );         /* EMI not under Reset */

}

/*******************************************************************************
* Function Name  : EMI_StructInit
* Description    : Fills the EMI_InitTypeDef structure member with its reset
*                  value.
* Input          : EMI_InitStruct : pointer to a EMI_InitTypeDef structure
*                  which will be initialized.
* Output         : None
* Return         : None
*******************************************************************************/

void EMI_StructInit( EMI_InitTypeDef *EMI_InitStruct)
{

  /* Number of bus turnaround cycles added between read and write accesses.*/
  /*This member can be 0x01,0x02,0x03, ....0xF (Reset value:0xF "15 cycles"*/

  EMI_InitStruct->EMI_Bank_IDCY =0xF;


  /* Number of wait states for read accesses*/
  /*This member can be: 0x01,0x02,0x03, ....0x1F (Reset value:0x1F "31 cycles"*/

  EMI_InitStruct->EMI_Bank_WSTRD =0x1F;


  /* Number of wait states for write accesses*/
  /*This member can be: 0x01,0x02,0x03, ....0x1F (Reset value:0x1F "31 cycles"*/

  EMI_InitStruct->EMI_Bank_WSTWR =0x1F;

  /*Output enable assertion delay from chip select assertion*/
  /*This member can be: 0x01,0x02,0x03, ....0xF (Reset value:0x01 "1 cycle"*/

  EMI_InitStruct->EMI_Bank_WSTROEN =0x01;


  /*Write enable assertion delay from chip select assertion*/
  /*This member can be: 0x01,0x02,0x03, ....0xF (Reset value:0x00 "0 cycle"*/

  EMI_InitStruct->EMI_Bank_WSTWEN =0x00;
  
  /*Number of wait states for burst read accesses after the first read.*/ 
  /* They do not apply to non-burst devices.*/ 
  /*This member can be: 0x01,0x02,0x03, ....0x1F (Reset value:0x1F "31 cycles"*/
  
  EMI_InitStruct->EMI_Bank_BRDCR =0x1F;

  /*This member Controls the memory width*/
  /*This member can be :"EMI_Width_Byte" = 8 bits width or "EMI_Width_HalfWord" = 16 bits width*/

  EMI_InitStruct->EMI_Bank_MemWidth = EMI_Width_Byte;


  /*Write protection feature */
  /*This member can be :"EMI_Bank_NonWriteProtect" = No write protection or "EMI_Bank_WriteProtect" = bank is write protected*/

  EMI_InitStruct-> EMI_Bank_WriteProtection= EMI_Bank_NonWriteProtect;


  /* Burst Read or page mode transfer length */
  /*This member can be :"EMI_Read_4Data"  or "EMI_Read_8Data" for page mode*/
  /*Read and it can be "EMI_Read_4Data","EMI_Read_8Data","EMI_Read_16Data" */
  /*or "EMI_Read_Continuous"(synchronous only) for burst mode read*/
                                                       
  EMI_InitStruct->EMI_Burst_and_PageModeRead_TransferLength= EMI_Read_4Data;

  /*Select or deselect the Burst and page mode read*/
  /*This member can be :"EMI_NormalMode" or "EMI_BurstModeRead" */

  EMI_InitStruct->EMI_Burst_and_PageModeRead_Selection = EMI_NormalMode;
  
  
  /* Enables the byte select signals in 16-bit PSRAM bus mode*/ 
  /*(EMI_UBn and EMI_LBn) are enabled. Bit 2 in the GPIO EMI register */
  /*(SCU_EMI) must also be set to 1 */
  
   EMI_InitStruct->EMI_ByteLane_Selection=EMI_Byte_Select_disabled;
  
  /*Access the device using synchronous accesses for reads*/
   
  EMI_InitStruct-> EMI_AccessRead_Support=EMI_Read_Asyn;
  
  /*Access the device using synchronous accesses for Write*/
   
  EMI_InitStruct->EMI_AccessWrite_Support=EMI_Write_Asyn;
  
  /* Burst Write transfer length */
  /*This member can be :"EMI_Write_4Data", "EMI_Write_8Data" or */
  /*"EMI_Write_Continuous" for synchronous only*/
  
  EMI_InitStruct->EMI_BurstModeWrite_TransferLength = EMI_Write_4Data;
  
  /* Select burst or non-burst write to memory*/
   
  EMI_InitStruct-> EMI_BurstModeWrite_Selection=EMI_NonBurstModeWrite;
  

}

/*******************************************************************************
* Function Name  : EMI_Init
* Description    : Initializes EMI  peripheral according to the specified
*                  parameters in the EMI_InitStruct.

* Input          : EMI_Bankx:where x can be 0,1,2 or 3 to select the EMI Bank.
                   EMI_InitStruct: pointer to a EMI_InitTypeDef structure
                  ( Structure Config to be loaded in EMI Registers). .

* Output         : None
* Return         : None
*******************************************************************************/

void EMI_Init( EMI_Bank_TypeDef* EMI_Bankx, EMI_InitTypeDef* EMI_InitStruct)

{

  EMI_Bankx->ICR  = EMI_InitStruct-> EMI_Bank_IDCY ;

  EMI_Bankx->RCR  = EMI_InitStruct->EMI_Bank_WSTRD ;

  EMI_Bankx->WCR  = EMI_InitStruct->EMI_Bank_WSTWR ;

  EMI_Bankx->OECR = EMI_InitStruct->EMI_Bank_WSTROEN;

  EMI_Bankx->WECR = EMI_InitStruct->EMI_Bank_WSTWEN ;
  
  EMI_Bankx->BRDCR  = EMI_InitStruct->EMI_Bank_BRDCR ;
  
  EMI_Bankx->BCR &= EMI_MemWidth_Mask;
  EMI_Bankx->BCR |= EMI_InitStruct->EMI_Bank_MemWidth;

  EMI_Bankx->BCR &= EMI_WriteProtect_Mask;
  EMI_Bankx->BCR |= EMI_InitStruct->EMI_Bank_WriteProtection;

 
  EMI_Bankx->BCR &= EMI_Burst_and_PageModeRead_TL_Mask;
  EMI_Bankx->BCR |= EMI_InitStruct->EMI_Burst_and_PageModeRead_TransferLength;
  
  EMI_Bankx->BCR &= EMI_Burst_and_PageModeRead_Sel_Mask;
  EMI_Bankx->BCR |=  EMI_InitStruct->EMI_Burst_and_PageModeRead_Selection;
  
  EMI_Bankx->BCR &= EMI_BurstModeWrite_TL_Mask;
  EMI_Bankx->BCR |= EMI_InitStruct->EMI_BurstModeWrite_TransferLength;
 
  EMI_Bankx->BCR &= EMI_BurstModeWrite_Sel_Mask;
  EMI_Bankx->BCR |=  EMI_InitStruct->EMI_BurstModeWrite_Selection;
  
  EMI_Bankx->BCR &=  EMI_ByteLane_Mask;
  EMI_Bankx->BCR |=  EMI_InitStruct->EMI_ByteLane_Selection;
  
  EMI_Bankx->BCR &=  EMI_AccessRead_Dev_Mask;    
  EMI_Bankx->BCR |=  EMI_InitStruct->EMI_AccessRead_Support;
  
  EMI_Bankx->BCR &=   EMI_AccessWrite_Dev_Mask;    
  EMI_Bankx->BCR |=  EMI_InitStruct->EMI_AccessWrite_Support;


}
/*******************************************************************************
* Function Name  : EMI_BCLKCmd
* Description    : Enable or Disable the activation of BCLK clock (LFBGA only)
* Input          : NewState : ENABLE or DISABLE
* Output         : None
* Return         : None
*******************************************************************************/
void EMI_BCLKCmd(FunctionalState NewState)
{
  if (NewState == ENABLE)
 *EMI_CCR |=0x1;
  else
 *EMI_CCR &=~0x1;
}



/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
