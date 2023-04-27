myShell: myShell.o myLS.o mycp.o myps.o mymv.o mygrep.o myShell.h
	gcc myShell.o myLS.o mycp.o myps.o mymv.o mygrep.o -o myShell -lreadline
myShell.o: myShell.c myShell.h
	gcc -c myShell.c -o myShell.o -lreadline
myLS.o: myLS.c myShell.h
	gcc -c myLS.c -o myLS.o -lreadline
mycp.o: mycp.c myShell.h
	gcc -c mycp.c -o mycp.o -lreadline
myps.o: myps.c myShell.h
	gcc -c myps.c -o myps.o
mymv.o: mymv.c myShell.h
	gcc -c mymv.c -o mymv.o
mygrep.o: mygrep.c myShell.h
	gcc -c mygrep.c -o mygrep.o
clean: myShell.o myLS.o mycp.o myps.o mymv.o mygrep.o
	rm myShell.o myLS.o mycp.o myps.o mymv.o mygrep.o
