// SPDX-License-Identifier: GPL-2.0-or-later
#include "./app_cfg.h"
#ifndef __KEY_H__
#define __KEY_H__

/*============================ INCLUDES ======================================*/
#include "stm32f1xx_hal.h"
#include "../print_string/print_string.h"
#include "../../Vsf/release/kernel/beta/vsf/utilities/3rd-party/PLOOC/plooc.h"
/*============================ MACROS ========================================*/
#define __PLOOC_CLASS_USE_STRICT_TEMPLATE__
   
#if     defined(__KEY_CLASS_IMPLEMENT)
#       define __PLOOC_CLASS_IMPLEMENT
#elif   defined(__KEY_CLASS_INHERIT)
#       define __PLOOC_CLASS_INHERIT
#endif   
#include "../../Vsf/release/kernel/beta/vsf/utilities/3rd-party/PLOOC/plooc_class.h"
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

typedef enum {
    KEY_NULL = 0,
    KEY_DOWN,
    KEY_UP,
} key_evt_t;
typedef struct key_t {
    key_evt_t tEvent;
} key_t;

 declare_class(key_queue_t)
 def_class(key_queue_t,
     private_member(
         key_t* ptBuffer;
         uint16_t hwSize;
         uint16_t hwHead;
         uint16_t hwTail;
         uint16_t hwLength;
     )
 )
end_def_class(key_queue_t)

typedef struct {
    uint8_t chState;
    uint8_t chCnt;
} high_check_t;

typedef struct {
    uint8_t chState;
    uint8_t chCnt;
} low_check_t;

declare_class(wait_raising_edge_t)
def_class(wait_raising_edge_t,
    private_member (
        high_check_t tHighCheck;
        low_check_t tLowCheck;
    )
    public_member (
        uint8_t chState;
        key_queue_t *ptQueue;
    )
)
end_def_class(wait_raising_edge_t)

declare_class(wait_falling_edge_t)
def_class(wait_falling_edge_t,
    private_member (
        high_check_t tHighCheck;
        low_check_t tLowCheck;
    )
    public_member (
        uint8_t chState;
        key_queue_t *ptQueue;
    )
)
end_def_class(wait_falling_edge_t)

declare_class(key_service_t)
def_class(key_service_t,
    private_member(
        uint8_t chState;
        void *pOutputTarget;
        print_str_t *ptPrintStr;
        key_queue_t *ptQueue;
        key_t tKeyEvent;
    )
)
end_def_class(key_service_t)
typedef struct {
    void *pOutputTarget;
    key_queue_t *ptQueue;
}key_service_cfg_t;

def_interface(i_key_service_t)
    bool     (*Init)    (key_service_t *ptObj, key_service_cfg_t *ptCFG);
    key_t    (*GetKey)  (key_service_t *ptObj);
    fsm_rt_t (*Task)    (key_service_t *ptObj);
    struct {
        bool    (*Init)     (key_queue_t* ptObj, key_t* ptKeyEvent, uint16_t hwSize);
        bool    (*Enqueue)  (key_queue_t* ptObj, key_t tKeyEvent);
        bool    (*Dequeue)  (key_queue_t* ptObj, key_t* ptKeyEvent);
    } KeyQueue;
    struct {
        bool     (*Init)    (wait_raising_edge_t *ptRaiseObj, wait_falling_edge_t *ptFallObj, key_queue_t *ptQueue);
        fsm_rt_t (*Raising) (wait_raising_edge_t *ptObj);
        fsm_rt_t (*Falling) (wait_falling_edge_t *ptObj);
    } WaitKey;
end_def_interface(i_key_service_t)
/*============================ GLOBAL VARIABLES ==============================*/
extern const i_key_service_t KEY_SERVICE;
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
extern void key_init(void);
#endif
/* EOF */

