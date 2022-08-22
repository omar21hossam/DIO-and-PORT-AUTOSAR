 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Omar Hossam El-Din
 ******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_OFF)
#define PORT_SETUP_PIN_DIRECTION             (STD_OFF)
#define PORT_SETUP_PIN_MODE                  (STD_OFF)

/* number of pin in the microconroller */
#define PIN_NUMBER                            (43U)

/* number the lock the magic number */
#define LOCK_MASK                             0x4C4F434B
   
/* Range of the modes */
#define LOWER_LIMIT_MODE                      (9U)
#define UPPER_LIMIT_MODE                      (14U)
   
/* Port ID'S */
#define PORTA                                 (0U)
#define PORTB                                 (1U)   
#define PORTC                                 (2U)
#define PORTD                                 (3U)
#define PORTE                                 (4U)
#define PORTF                                 (5U)
   
/* Pin ID'S */
#define PIN0                                  (0U)
#define PIN1                                  (1U)
#define PIN2                                  (2U)
#define PIN3                                  (3U)
#define PIN4                                  (4U)
#define PIN5                                  (5U)
#define PIN6                                  (6U)
#define PIN7                                  (7U)

/* Pin modes */
#define GPIO_MODE                             (0U)
#define ADC_MODE                              (20U)
#define U0RX                                  (1U)
#define U0TX                                  (1U)
#define U1RX                                  (1U)
#define U1TX                                  (1U)
#define U4RX                                  (1U)
#define U4TX                                  (1U)
#define U3RX                                  (1U)
#define U3TX                                  (1U)
#define SSI3CLK                               (1U)
#define SSI3Fss                               (1U)
#define SSI3RX                                (1U)
#define SSI3TX                                (1U)
#define U6RX                                  (1U)
#define U6TX                                  (1U)
#define U2RX                                  (1U)
#define U2TX                                  (1U)
#define U7RX                                  (1U)
#define U7TX                                  (1U)
#define U5RX                                  (1U)
#define U5TX                                  (1U)
#define U1RTS                                 (1U)
#define U1CTS                                 (1U)
#define SSI0CLK                               (2U)
#define SSI0Fss                               (2U)
#define SSI0RX                                (2U)                            
#define SSI0TX                                (2U)
#define SSI2CLK                               (2U)
#define SSI2Fss                               (2U)
#define SSI2RX                                (2U)
#define SSI2TX                                (2U)
#define U1RX_PC4                              (2U)
#define U1TX_PC5                              (2U)
#define SSI1CLK                               (2U)
#define SSI1Fss                               (2U)
#define SSI1RX                                (2U)
#define SSI1TX                                (2U)
#define I2C1SCL                               (3U)
#define I2C1SDA                               (3U)
#define I2C0SCL                               (3U)
#define I2C0SDA                               (3U)
#define I2C3SCL                               (3U)
#define I2C3SDA                               (3U)
#define I2C2SCL                               (3U)
#define I2C2SDA                               (3U)
#define CAN0RX                                (3U)
#define CAN0TX                                (3U)
#define M0PWM0                                (4U)
#define M0PWM1                                (4U)
#define M0PWM2                                (4U)
#define M0PWM3                                (4U)
#define M0PWM4                                (4U)
#define M0PWM5                                (4U)
#define M0PWM6                                (4U)
#define M0PWM7                                (4U)
#define M0FAULT0                              (4U)
#define M1PWM0                                (5U)
#define M1PWM1                                (5U)
#define M1PWM2                                (5U)
#define M1PWM3                                (5U)
#define M1PWM4                                (5U)
#define M1PWM5                                (5U)
#define M1PWM6                                (5U)
#define M1PWM7                                (5U)
#define M1FAULT0                              (5U)
#define IDX1                                  (6U)       
#define PHA1                                  (6U)
#define PHB1                                  (6U)
#define IDX1                                  (6U)
#define IDX0                                  (6U)
#define PHA0                                  (6U)
#define PHB0                                  (6U)
#define T2CCP0                                (7U)
#define T2CCP1                                (7U)
#define T3CCP0                                (7U)
#define T3CCP1                                (7U)
#define T1CCP0                                (7U)
#define T1CCP1                                (7U)
#define T0CCP0                                (7U)
#define T0CCP1                                (7U)
#define WT0CCP0                               (7U)
#define WT0CCP1                               (7U)
#define WT1CCP0                               (7U)
#define WT1CCP1                               (7U)
#define WT2CCP0                               (7U)
#define WT2CCP1                               (7U)
#define WT3CCP0                               (7U)
#define WT3CCP1                               (7U)
#define WT4CCP0                               (7U)
#define WT4CCP1                               (7U)
#define WT5CCP0                               (7U)
#define WT5CCP1                               (7U)
#define CAN1RX                                (8U)
#define CAN1TX                                (8U)
#define CAN0RX_PB4_PE4                        (8U)
#define CAN0TX_PB5_PE5                        (8U)
#define U1RTS_PC4                             (8U)
#define U1CTS_PC5                             (8U)
#define USB0EPEN                              (8U)
#define USB0PFLT                              (8U)
#define NMI                                   (8U)
#define C0O                                   (9U)
#define C1O                                   (9U)
#define TRD1                                  (14U)
#define TRD0                                  (14U)
#define TRCLK                                 (14U)

#endif /* DIO_CFG_H */
