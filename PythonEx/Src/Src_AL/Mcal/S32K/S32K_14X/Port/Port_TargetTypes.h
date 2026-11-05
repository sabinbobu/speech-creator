#ifndef PORT_CFG_2020_10_21_H_
  #define PORT_CFG_2020_10_21_H_

  //=============================================================================
  // Includes
  //=============================================================================
  #include <Std_Types.h>

  //=============================================================================
  // Private Types
  //=============================================================================
 
  typedef struct Port_PinSpecificCharacteristicsType
  {
    uint8                            portBaseIndex;      // Port base index
    uint32                           pinPortIdx;         // Port pin number
    uint8                            pullConfig;         // Internal resistor pull feature selection - pull up or pull down - ?????
    boolean                          passiveFilter;      // Passive filter configuration - ????
    uint8                            driveSelect;        // Configures the drive strength - ????
    uint8                            mux;                // Pin mux selection
    uint8                            direction;          // Port data direction
    uint8                            initValue;          // Initial value
    boolean                          digitalFilter;      // Enables digital filter - ?????
    uint8                            gpioBaseIndex;      // Gpio base pointer
  } Port_PinSpecificCharacteristicsType;

  //=============================================================================
  // Public types
  //=============================================================================

  typedef struct Port_ConfigSpecificType
  {
    uint8                                      ucCountOfPorts;
    const Port_PinSpecificCharacteristicsType* ptyPinSpecificCharacteristics;
  }
  Port_ConfigSpecificType;

#endif /* PORT_CFG_2020_10_21_H_ */
