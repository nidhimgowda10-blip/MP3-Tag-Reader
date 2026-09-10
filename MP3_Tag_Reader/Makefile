CC = gcc

CFLAGS = -Iinclude -Wall -Wextra

SRC = source/main.c \
      source/utils.c \
      source/validate.c \
      source/view.c \
      source/edit.c

OBJ = $(SRC:source/%.c=obj/%.o)

TARGET = bin/mp3_tag_reader


$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)


obj/%.o: source/%.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f obj/*.o $(TARGET)


.PHONY: clean