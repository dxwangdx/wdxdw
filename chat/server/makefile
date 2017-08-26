TAGET:=bin/serverTest
OBJ:=obj/serverLink.o obj/serverFunction.o obj/serverMenu.o
OBJ+=obj/serverTest.o
F:=-lpthread -Wall -g
CC:=gcc

$(TAGET):$(OBJ)
	$(CC) -o $@ -I./include $^ $(F)
obj/%.o:src/%.c
	$(CC) -o $@ -I./include -c $^ $(F) 

.PHONEY:clean
clean:
	rm -rf $(TAGET)
	rm -rf obj/*.o
	rm -rf *~ *.*~
	rm -rf include/*.*~
	rm -rf src/*.*~