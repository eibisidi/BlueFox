#Base on ARMv8 Reference Manual Appendix K13.3 Load-Acquire Exclusive
SRC_LIST=main.c simple_lock.s ticket_lock.s

.PHONY : all
all : lock_none lock_pthread lock_simple lock_ticket

lock_none : ${SRC_LIST}
	gcc -lpthread -DLOCK_NONE -o $@ $^

lock_pthread : ${SRC_LIST}
	gcc -lpthread -DLOCK_PTHREAD -o $@ $^

lock_simple : ${SRC_LIST}
	gcc -lpthread -DLOCK_SIMPLE -o $@ $^

lock_ticket : ${SRC_LIST}
	gcc -lpthread -DLOCK_TICKET -o $@ $^

.PHONY : clean
clean :
	rm *.o lock_none lock_pthread lock_simple lock_ticket

