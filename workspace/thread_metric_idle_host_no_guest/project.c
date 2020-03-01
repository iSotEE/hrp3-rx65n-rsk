#include <kernel.h>
#include <t_syslog.h>
#include <t_stdlib.h>
#include "syssvc/serial.h"
#include "syssvc/syslog.h"
#include "kernel_cfg.h"
#include "project.h"

Inline void
svc_perror(const char *file, int_t line, const char *expr, ER ercd)
{
	if (ercd < 0) {
		t_perror(LOG_ERROR, file, line, expr, ercd);
	}
}

#define	SVC_PERROR(expr)	svc_perror(__FILE__, __LINE__, #expr, (expr))

void
main_task(intptr_t exinf)
{
    SVC_PERROR(act_tsk(ISOTEE_GUEST_TASK));
}

void
empty_guest_task(intptr_t exinf)
{
	_svc_service_call_1(0, 30 /*TFN_ISOTEE_PARA_INITIALIZE*/);
    while(1);
}
