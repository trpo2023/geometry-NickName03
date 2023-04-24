CC = gcc
RM = rm
SRC_EXT = c

CFLAGS = -Wall -Werror
CPPFLAGS = -I src/libgeometry -MP -MMD

APP_NAME = geometry
LIB_NAME = libgeometry
FILE_NAME = test.txt

OBJ_DIR = obj
SRC_DIR = src
BIN_DIR = bin

APP_PATH = $(BIN_DIR)/$(APP_NAME)
LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/$(LIB_NAME).a

APP_SOURCES = $(shell find $(SRC_DIR)/$(APP_NAME) -name '*.$(SRC_EXT)')
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

LIB_SOURCES = $(shell find $(SRC_DIR)/$(LIB_NAME) -name '*.$(SRC_EXT)')
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)


.PHONY: all
all: $(APP_PATH)

$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ -lm $(LDFLAGS) $(LDLIBS) 

$(LIB_PATH): $(LIB_OBJECTS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $(CPPFLAGST) $< -o $@

.PHONY: clean run
run: 
	./$(BIN_DIR)/$(APP_NAME)

runs: 
	./$(BIN_DIR)/$(APP_NAME) $(FILE_NAME)

clean:
	$(RM) $(APP_PATH) $(LIB_PATH)
	find $(OBJ_DIR) -name '*.o' -exec $(RM) '{}' \;
	find $(OBJ_DIR) -name '*.d' -exec $(RM) '{}' \;