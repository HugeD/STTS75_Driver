#include "STTS75_ACC_driver.h"


/*******************************************************************************
* Function Name		: STTS75_ACC_WriteReg
* Description		: Generic Writing function. It must be fullfilled with either
*					: I2C or SPI writing function
* Input				: Register Address, ptr to buffer to be written,
*                                 length of buffer
* Output			: None
* Return			: None
*******************************************************************************/
stts_status_t STTS75_ACC_WriteReg(void *handle, u8_t Reg, u8_t *Bufp, u16_t len)
{
  //To be completed with either I2c or SPI writing function
  //i.e.   HAL_I2C_Mem_Write(&hi2c1, STTS75_ACC_I2C_ADDRESS_WRITE, Reg, I2C_MEMADD_SIZE_8BIT, 
  //             Bufp, len, 1000); 
	
	/* Added by HugeD at 2021-1-21 *BEGIN* */
	HAL_StatusTypeDef status;
	
	status = HAL_I2C_Mem_Write(handle, STTS75_ACC_I2C_ADDRESS_WRITE & 0xFE, Reg, 1, Bufp, len, 100);
	if(HAL_OK != status)
	{
		//I2CÐ´Êý¾Ý´íÎó
		return STTS_ERROR;
	}
	/* Added by HugeD at 2021-1-21 *END* */
	
  return STTS_SUCCESS;
}

/*******************************************************************************
* Function Name		: STTS75_ACC_ReadReg
* Description		: Generic Reading function. It must be fullfilled with either
*					: I2C or SPI writing function
* Input				: Register Address, ptr to buffer to be read,
*                                 length of buffer
* Output			: None
* Return			: None
*******************************************************************************/
stts_status_t STTS75_ACC_ReadReg(void *handle, u8_t Reg, u8_t *Bufp, u16_t len)
{
  //To be completed with either I2c or SPI writing function
  //i.e. HAL_I2C_Mem_Read(&hi2c1, STTS75_ACC_I2C_ADDRESS_READ, Reg, I2C_MEMADD_SIZE_8BIT, 
  //     Bufp, len, 1000);
  
  /* Added by HugeD at 2021-1-21 *BEGIN* */
	HAL_StatusTypeDef status;
	
	status = HAL_I2C_Mem_Read(handle, STTS75_ACC_I2C_ADDRESS_READ, Reg, 1, Bufp, len, 100);
	if(HAL_OK != status)
	{
		//I2C¶ÁÊý¾Ý´íÎó
		return STTS_ERROR;
	}
	/* Added by HugeD at 2021-1-21 *END* */
  
  return STTS_SUCCESS; 
}



/*******************************************************************************
* Function Name  : STTS75_ACC_R_TEMP_BIT_SB
* Description    : Read TEMP_BIT_SB
* Input          : Pointer to u8_t
* Output         : Status of TEMP_BIT_SB 
* Return         : stts_status_t [STTS_ERROR, STTS_SUCCESS]
*******************************************************************************/
stts_status_t STTS75_ACC_R_TEMP_BIT_SB(void *handle, u16_t *value)
{
 if( !STTS75_ACC_ReadReg(handle, STTS75_ACC_I2C_TEMP, (u8_t *)value, 2) )
    return STTS_ERROR;

  *value &= STTS75_ACC_I2C_TEMP_BIT_SB; //coerce	
  *value = *value >> STTS75_ACC_I2C_TEMP_BIT_POSITION; //mask	

  return STTS_SUCCESS;
}


/*******************************************************************************
* Function Name  : STTS75_ACC_W_Resolution
* Description    : Write Resolution
* Input          : STTS75_ACC_CONF_RC_t
* Output         : None
* Return         : stts_status_t [STTS_ERROR, STTS_SUCCESS]
*******************************************************************************/
stts_status_t  STTS75_ACC_W_Resolution(void *handle, STTS75_ACC_CONF_RC_t newValue)
{
  u8_t value;

  if( !STTS75_ACC_ReadReg(handle, STTS75_ACC_I2C_CONF, &value, 1) )
    return STTS_ERROR;

  value &= ~STTS75_ACC_CONF_RC_MASK; 
  value |= newValue;
  
  if( !STTS75_ACC_WriteReg(handle, STTS75_ACC_I2C_CONF, &value, 1) )
    return STTS_ERROR;

  return STTS_SUCCESS;
}

/*******************************************************************************
* Function Name  : STTS75_ACC_R_Resolution
* Description    : Read Resolution
* Input          : Pointer to STTS75_ACC_CONF_RC_t
* Output         : Status of IF_ADD_INC see STTS75_ACC_CONF_RC_t
* Return         : stts_status_t [STTS_ERROR, STTS_SUCCESS]
*******************************************************************************/
stts_status_t STTS75_ACC_R_Resolution(void *handle, STTS75_ACC_CONF_RC_t *value)
{
 if( !STTS75_ACC_ReadReg(handle, STTS75_ACC_I2C_CONF, (u8_t *)value, 1) )
    return STTS_ERROR;

  *value &= STTS75_ACC_CONF_RC_MASK; //mask

  return STTS_SUCCESS;
}

/*******************************************************************************
* Function Name  : STTS75_ACC_W_Thys
* Description    : Write Hysteresis register
* Input          : Pointer to u8_t
* Output         : None
* Return         : stts_status_t [STTS_ERROR, STTS_SUCCESS]
*******************************************************************************/
stts_status_t STTS75_ACC_W_Thys(void *handle, u16_t newValue)
{
 u8_t value;

  if( !STTS75_ACC_ReadReg(handle, STTS75_ACC_I2C_THYS, &value, 1) )
    return STTS_ERROR;

  value &= ~STTS75_ACC_THYS_DEF; 
  value |= newValue;
  
  if( !STTS75_ACC_WriteReg(handle, STTS75_ACC_I2C_THYS, &value, 1) )
    return STTS_ERROR;

  return STTS_SUCCESS;
}

/*******************************************************************************
* Function Name  : STTS75_ACC_R_Thys
* Description    : Read Hysteresis register
* Input          : Pointer to u8_t
* Output         : Value of THYS temperature
* Return         : stts_status_t [STTS_ERROR, STTS_SUCCESS]
*******************************************************************************/
stts_status_t STTS75_ACC_R_Thys(void *handle, u16_t *value)
{
 if( !STTS75_ACC_ReadReg(handle, STTS75_ACC_I2C_THYS, (u8_t *)value, 2) )
    return STTS_ERROR;

  return STTS_SUCCESS;
}

/*******************************************************************************
* Function Name  : STTS75_ACC_W_Tos
* Description    : Write Overtemperature shutdown
* Input          : Pointer to u8_t
* Output         : None
* Return         : stts_status_t [STTS_ERROR, STTS_SUCCESS]
*******************************************************************************/
stts_status_t STTS75_ACC_W_Tos(void *handle, u16_t newValue)
{
 u8_t value;

  if( !STTS75_ACC_ReadReg(handle, STTS75_ACC_I2C_TOS, &value, 1) )
    return STTS_ERROR;

  value &= ~STTS75_ACC_TOS_DEF; 
  value |= newValue;
  
  if( !STTS75_ACC_WriteReg(handle, STTS75_ACC_I2C_TOS, &value, 1) )
    return STTS_ERROR;

  return STTS_SUCCESS;
}

/*******************************************************************************
* Function Name  : STTS75_ACC_R_Thys
* Description    : Read Overtemperature shutdown
* Input          : Pointer to u8_t
* Output         : Value of TOS temperature
* Return         : stts_status_t [STTS_ERROR, STTS_SUCCESS]
*******************************************************************************/
stts_status_t STTS75_ACC_R_Tos(void *handle, u16_t *value)
{
 if( !STTS75_ACC_ReadReg(handle, STTS75_ACC_I2C_TOS, (u8_t *)value, 2) )
    return STTS_ERROR;

  return STTS_SUCCESS;
}


/*******************************************************************************
* Function Name  : STTS75_Check
* Description    : Check if the equipment is on line
* Input          : Device Address
* Output         : Device Status
* Return         : stts_status_t [STTS_ERROR, STTS_SUCCESS]
*******************************************************************************/
stts_status_t STTS75_Check(void *handle, u8_t DeviceAddress)
{
	uint8_t stat;
	stat = HAL_I2C_IsDeviceReady(handle, DeviceAddress, 10, 100);
	if(HAL_OK != stat)
	{
		printf("Ó²¼þ¹ÊÕÏ\r\n");
		return STTS_ERROR;
	}
	return STTS_SUCCESS;
}

/*******************************************************************************
* Function Name  : STTS75_GET_Temp
* Description    : Get the converted temperature
* Input          : Pointer to u16_t
* Output         : Device Status
* Return         : stts_status_t [STTS_ERROR, STTS_SUCCESS]
*******************************************************************************/
stts_status_t STTS75_GET_Temp(void *handle, float *Value)
{
	uint8_t stat;
	uint8_t temp[2];
	stat =  HAL_I2C_Mem_Read(handle, STTS75_ACC_I2C_ADDRESS_READ, STTS75_ACC_I2C_TEMP, 1, temp, 2, 100);
	if(HAL_OK != stat)
	{
		printf("ÎÂ¶È¶ÁÈ¡Ê§°Ü\r\n");
		return STTS_ERROR;
	}
	if(((temp[0]<<8|temp[1]) & 0x8000) >> 15)
		*Value = -(0x8000 - (0x7fff & (temp[0]<<8|temp[1])));
	else
		*Value = (temp[0]<<8|temp[1]) / 256.0;
	
	return STTS_SUCCESS;
}




