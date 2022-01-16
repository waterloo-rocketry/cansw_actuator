#ifndef ACTUATOR_H
#define	ACTUATOR_H


#include <stdbool.h>
#include "canlib/message_types.h"

void actuator_init();

void actuator_set(enum ACTUATOR_STATE state);

enum ACTUATOR_STATE get_actuator_state(void);

void actuator_send_status(enum ACTUATOR_STATE req_state);

#endif /*ACTUATOR_H*/
