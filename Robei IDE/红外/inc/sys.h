#ifndef RO_SYS_H
#define RO_SYS_H

/** @addtogroup Exported_types
  * @{
  */  
typedef enum 
{
  RESET = 0, 
  SET = !RESET
} FlagStatus, ITStatus;

typedef enum 
{
  DISABLE = 0, 
  ENABLE = !DISABLE
} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum
{
  SUCCESS = 0U,
  ERROR = !SUCCESS
} ErrorStatus;

/**
  * @}
  */
/**
  * @brief	Hamster Status structures definition
  */
typedef enum
{
  RO_OK	   = 0x00U,
  RO_ERROR    = 0x01U,
  RO_BUSY	   = 0x02U,
  RO_TIMEOUT  = 0x03U
} Ro_StatusTypeDef;

#endif /* RO_SYS_H */
