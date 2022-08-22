 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Omar Hossam El-Din
 ******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"


#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port.h does not match the expected version"
#endif

#endif
   
STATIC const Port_PinConfigType *Port_PinPtr = NULL_PTR;  
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;

/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant 
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver module.
************************************************************************************/
void Port_Init(const Port_ConfigType *ConfigPtr )
{
  boolean error = FALSE;
  #if (PORT_DEV_ERROR_DETECT == STD_ON)
	/* check if the input configuration pointer is not a NULL_PTR */
	if (NULL_PTR == ConfigPtr)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
		     PORT_E_PARAM_CONFIG);
                error = TRUE;
	}
	else
#endif
	{
		/*
		 * Set the module state to initialized and point to the PB configuration structure using a global pointer.
		 * This global pointer is global to be used by other functions to read the PB configuration structures
		 */
		Port_Status       = PORT_INITIALIZED;
                Port_PinPtr       = ConfigPtr->Port_Pin;
        }
        
  
    volatile uint32 * PortPin_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    volatile uint32 delay = 0;
    
    for(uint8 i = ZERO ; i<PIN_NUMBER ; i++)
    {
    switch(Port_PinPtr[i].port_num)
    {
        case  0: PortPin_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
	case  1: PortPin_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
	case  2: PortPin_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
	case  3: PortPin_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
        case  4: PortPin_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
        case  5: PortPin_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
    }
    
     /* Enable clock for PORT and allow time for clock to start*/
    SYSCTL_REGCGC2_REG |= (1<<Port_PinPtr[i].port_num);
    delay = SYSCTL_REGCGC2_REG;
    
    if( ((Port_PinPtr[i].port_num == 3) && (Port_PinPtr[i].pin_num == 7)) || ((Port_PinPtr[i].port_num == 5) && (Port_PinPtr[i].pin_num == 0)) ) /* PD7 or PF0 */
    {
        *(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_LOCK_REG_OFFSET) = LOCK_MASK;                     /* Unlock the GPIOCR register */   
        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_COMMIT_REG_OFFSET) , Port_PinPtr[i].pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
    }
    else if( (Port_PinPtr[i].port_num == 2) && (Port_PinPtr[i].pin_num <= 3) ) /* PC0 to PC3 */
    {
        /* Do Nothing ...  this is the JTAG pins */
    }
    else
    {
        /* Do Nothing ... No need to unlock the commit register for this pin */
    }
    
    if(Port_PinPtr[i].direction == PORT_PIN_OUT)
    {
	SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_DIR_REG_OFFSET) , Port_PinPtr[i].pin_num);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
        
        if(Port_PinPtr[i].level_value == PORT_PIN_LEVEL_HIGH)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_DATA_REG_OFFSET) , Port_PinPtr[i].pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
        }
        else
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_DATA_REG_OFFSET) , Port_PinPtr[i].pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
        }
    }
    else if(Port_PinPtr[i].direction == PORT_PIN_IN)
    {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_DIR_REG_OFFSET) , Port_PinPtr[i].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
        
        if(Port_PinPtr[i].resistor == PULL_UP)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_PinPtr[i].pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
        }
        else if(Port_PinPtr[i].resistor == PULL_DOWN)
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_PinPtr[i].pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
        }
        else
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_PinPtr[i].pin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_PinPtr[i].pin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
        }
    }
    else
    {
        /* Do Nothing */
    }
    
    if(Port_PinPtr[i].mode == GPIO_MODE)
    { 
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PinPtr[i].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PinPtr[i].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
    *(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PinPtr[i].pin_num * 4));     /* Clear the PMCx bits for this pin */
   SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PinPtr[i].pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
    }
    
    else if (Port_PinPtr[i].mode == ADC_MODE)
    {
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PinPtr[i].pin_num);      /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PinPtr[i].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
    *(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PinPtr[i].pin_num * 4));     /* Clear the PMCx bits for this pin */
   CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PinPtr[i].pin_num);        /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
      
    }
    
    else
    {
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PinPtr[i].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PinPtr[i].pin_num);             /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PinPtr[i].pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
      *(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_CTL_REG_OFFSET) |= (Port_PinPtr[i].mode << (Port_PinPtr[i].pin_num * 4));
    }
    
    }
}

#if (PORT_SETUP_PIN_DIRECTION == STD_ON)
/************************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: Reentrant 
* Parameters (in): Pin - Port Pin ID number , Direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction.
************************************************************************************/
void Port_SetPinDirection(Port_PinType Pin,Port_PinDirectionType Direction)
{
  boolean error = FALSE;
  #if (PORT_DEV_ERROR_DETECT == STD_ON)
  /* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
        
  /* check if the pin required to be changed is in the valid range */
        if(Pin>PIN_NUMBER)
  {
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN);
		error = TRUE;
	}
        else
        {
          /* No Action Required */
        }
        /* check if the pin required to be changed is changeable */
        if(Port_PinPtr[Pin].changeable_direction == OFF_DIRECTION)
        {
          Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_DIRECTION_SID, PORT_E_DIRECTION_UNCHANGEABLE);
		error = TRUE;
        }
        else
#endif
        {
          volatile uint32 * PortPin_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    volatile uint32 delay = 0;
    
    switch(Port_PinPtr[Pin].port_num)
    {
        case  0: PortPin_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
	case  1: PortPin_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
	case  2: PortPin_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
	case  3: PortPin_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
        case  4: PortPin_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
        case  5: PortPin_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
    }
           if(Port_PinPtr[Pin].direction == PORT_PIN_OUT)
    {
	SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_DIR_REG_OFFSET) , Port_PinPtr[Pin].pin_num);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
         
    }
    else if(Port_PinPtr[Pin].direction == PORT_PIN_IN)
    {
        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_DIR_REG_OFFSET) , Port_PinPtr[Pin].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
     
    }
    else
    {
        /* Do Nothing */
    }
        }
}
#endif

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant 
* Parameters (in): None 
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction.
************************************************************************************/
void Port_RefreshPortDirection(void)
{
  boolean error = FALSE;
  volatile uint32 * PortPin_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    volatile uint32 delay = 0;
  
   #if (PORT_DEV_ERROR_DETECT == STD_ON)
  /* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
#endif
     for(uint8 i = ZERO ; i<PIN_NUMBER ; i++)
    {
    switch(Port_PinPtr[i].port_num)
    {
        case  0: PortPin_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
	case  1: PortPin_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
	case  2: PortPin_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
	case  3: PortPin_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
        case  4: PortPin_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
        case  5: PortPin_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
    }
    if(Port_PinPtr[i].changeable_direction == OFF_DIRECTION)
    {
     if(Port_PinPtr[i].direction == PORT_PIN_OUT)
    {
	SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_DIR_REG_OFFSET) , Port_PinPtr[i].pin_num);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
    }
    else if(Port_PinPtr[i].direction == PORT_PIN_IN)
    {
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_DIR_REG_OFFSET) , Port_PinPtr[i].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
    }
    else
    {
      /* No Action Required */
    }
    }
    else
    {
      /* No Action Required */
    }
    }   
}


#if (PORT_VERSION_INFO_API == STD_ON)
/************************************************************************************
* Service Name: Port_GetVersionInfo 
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant 
* Parameters (in): None 
* Parameters (inout): None
* Parameters (out): None
* Return value: versioninfo - Pointer to where to store the version information of this module. 
* Description: Returns the version information of this module.
************************************************************************************/
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
  boolean error = FALSE;
   #if (PORT_DEV_ERROR_DETECT == STD_ON)
  /* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
        	/* Check if input pointer is not Null pointer */
	if(NULL_PTR == versioninfo)
	{
		/* Report to DET  */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
                error = TRUE;
	}
	else
 #endif
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)PORT_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
	}

}
#endif

#if(PORT_SETUP_PIN_MODE == STD_ON)
/************************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy: Reentrant 
* Parameters (in): Pin - Port Pin ID number , Mode - New Port Pin mode to be set on port pin 
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode.
************************************************************************************/
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode)
{
  boolean error = FALSE;
  
  #if (PORT_DEV_ERROR_DETECT == STD_ON)
  /* Check if the Driver is initialized before using this function */
	if (PORT_NOT_INITIALIZED == Port_Status)
	{
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}
        /* check if the pin required to be changed is in the valid range */
        if(Pin>PIN_NUMBER)
  {
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
		error = TRUE;
	}
        else
        {
          /* No Action Required */
        }
        
        /* Check if the mode is in the valid range */
        if( !(Mode < LOWER_LIMIT_MODE || Mode == UPPER_LIMIT_MODE || Mode == ADC_MODE) )
        {
          Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE);
		error = TRUE;
        }
        else
        {
          /* No Action Required */
        }
        
        /* Check if the pin's mode is changeable */
        if(Port_PinPtr[Pin].changeable_mode == OFF_MODE)
        {
          Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
				PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE);
		error = TRUE;
        }
        else
#endif
        {
          volatile uint32 * PortPin_Ptr = NULL_PTR; /* point to the required Port Registers base address */
    volatile uint32 delay = 0;
    
    switch(Port_PinPtr[Pin].port_num)
    {
        case  0: PortPin_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
	case  1: PortPin_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
	case  2: PortPin_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
	case  3: PortPin_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
        case  4: PortPin_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
        case  5: PortPin_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
    }
          if(Port_PinPtr[Pin].mode == GPIO_MODE)
    { 
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PinPtr[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PinPtr[Pin].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
    *(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PinPtr[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin */
   SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PinPtr[Pin].pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
    }
    
    else if (Port_PinPtr[Pin].mode == ADC_MODE)
    {
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PinPtr[Pin].pin_num);      /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PinPtr[Pin].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
    *(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_PinPtr[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin */
   CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PinPtr[Pin].pin_num);        /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
      
    }
    
    else
    {
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_PinPtr[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_PinPtr[Pin].pin_num);             /* Enable Alternative function for this pin by set the corresponding bit in GPIOAFSEL register */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_PinPtr[Pin].pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
      *(volatile uint32 *)((volatile uint8 *)PortPin_Ptr + PORT_CTL_REG_OFFSET) |= (Port_PinPtr[Pin].mode << (Port_PinPtr[Pin].pin_num * 4));
    }
        }
        
        
}
#endif
    