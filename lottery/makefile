TAGET:=bin/lotteryTest
OBJ:=obj/lotteryLink.o obj/lotteryFunction.o obj/view.o
OBJ+=obj/control.o
OBJ+=obj/menu.o
OBJ+=obj/lotteryTest.o
F:=-Wall -g
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