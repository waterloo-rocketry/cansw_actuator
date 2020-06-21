#ifndef VALVE_H
#define	VALVE_H
void vent_init(void);

void vent_open(void);
void vent_close(void);

void vent_send_status(enum VALVE_STATE req_state);

#endif /*VALVE_H*/
