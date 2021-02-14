#ifndef VALVE_H
#define	VALVE_H


#include <stdbool.h>
#include "canlib/message_types.h"

void valve_init(void);

void vent_open(void);
void vent_close(void);

void vent_send_status(enum VALVE_STATE req_state);

bool get_valve_open_state(void);
bool get_valve_closed_state(void);

#endif /*VALVE_H*/
