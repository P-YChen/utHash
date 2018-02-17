TARGET:=example
OBJ:=$(TARGET).o
SRC:=$(TARGET).c
TARGET1:=ut_string
OBJ1:=$(TARGET1).o
SRC1:=$(TARGET1).c

$(TARGET):$(OBJ)
	gcc $(OBJ) -o $(TARGET)
	
$(OBJ):$(SRC)
	gcc -c $(SRC) -o $(OBJ) -Iinclude

$(TARGET1):$(OBJ1)
	gcc $(OBJ1) -o $(TARGET1)
	
$(OBJ1):$(SRC1)
	gcc -c $(SRC1) -o $(OBJ1) -Iinclude
	
clean:
	rm $(OBJ) $(TARGET) $(OBJ1) $(TARGET1)