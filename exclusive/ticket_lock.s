.text
.global ticket_lock
ticket_lock:
	PRFM	PSTL1KEEP, [X0]
Loop1:
	LDAXR	W5, [X0]
	ADD	W3, W5, #0x10000
	STXR	W6, W3, [X0]
	CBNZ	W6, Loop1
//We have gotten our allocated ticket number in W5(higher 16 bits)
	AND	W6, W5, #0xFFFF		//current ticket number in W6
	CMP	W6, W5, LSR #16
	B.EQ	block_start
	SEVL
Loop2:
	WFE
	LDARH	W6, [X0]
	CMP	W6, W5, LSR #16
	B.NE	Loop2
block_start:
	ret

.global ticket_unlock
ticket_unlock:
	LDRH	W6, [X0]
	ADD	W6, W6, #1
	STLRH	W6, [X0]
	ret

