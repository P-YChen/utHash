TARGET:=example
OBJ:=$(TARGET).o
SRC:=$(TARGET).c


$(TARGET):$(OBJ)
	gcc $(OBJ) -o $(TARGET)
	
$(OBJ):$(SRC)
	gcc -c $(SRC) -o $(OBJ) -Iinclude
	
clean:
	rm $(OBJ) $(TARGET)