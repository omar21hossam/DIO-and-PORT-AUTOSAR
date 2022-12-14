 /******************************************************************************
 *
 * Module: PORT
 *
 * File Name: PORT_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - PORT Driver
 *
 * Author: Omar hossam el-din
 ******************************************************************************/

#include "Port.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between PORT_PBcfg.c and PORT.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between PORT_PBcfg.c and PORT.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

/* PB structure used with PORT_Init API */
const Port_ConfigType Port_Configuration = {
  
            PORTA,PIN0,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTA,PIN1,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW, 
            PORTA,PIN2,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,  
            PORTA,PIN3,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,  
            PORTA,PIN4,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTA,PIN5,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,  
            PORTA,PIN6,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,  
            PORTA,PIN7,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,  
            PORTB,PIN0,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,  
            PORTB,PIN1,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,  
            PORTB,PIN2,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTB,PIN3,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTB,PIN4,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTB,PIN5,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTB,PIN6,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTB,PIN7,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTC,PIN0,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTC,PIN1,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTC,PIN2,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTC,PIN3,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTC,PIN4,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTC,PIN5,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTC,PIN6,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTC,PIN7,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTD,PIN0,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTD,PIN1,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTD,PIN2,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTD,PIN3,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTD,PIN4,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTD,PIN5,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTD,PIN6,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTD,PIN7,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTE,PIN0,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTE,PIN1,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTE,PIN2,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTE,PIN3,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTE,PIN4,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTE,PIN5,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTF,PIN0,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTF,PIN1,GPIO_MODE,PORT_PIN_OUT,OFF_DIRECTION,OFF,OFF_MODE,PORT_PIN_LEVEL_LOW,
            PORTF,PIN2,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTF,PIN3,GPIO_MODE,PORT_PIN_IN,ON_DIRECTION,OFF,ON_MODE,PORT_PIN_LEVEL_LOW,
            PORTF,PIN4,GPIO_MODE,PORT_PIN_IN,OFF_DIRECTION,PULL_UP,OFF_MODE,PORT_PIN_LEVEL_LOW
           
				         };