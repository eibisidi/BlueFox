.text
.global simple_lock
simple_lock:
	SEVL
	PRFM PSTL1KEEP, [X0]
Loop:
	WFE
	LDAXR W5, [X0]
	CBNZ W5, Loop
	STXR W5, X0, [X0]
	CBNZ W5, Loop
	RET

.global simple_unlock
simple_unlock:
	STLR XZR, [X0]
	RET
