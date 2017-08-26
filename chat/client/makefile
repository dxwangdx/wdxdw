TAGET:=bin/clientTest
OBJ:=obj/clientView.o obj/clientFunction.o obj/clientMenu.o
OBJ+=obj/clientTest.o
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