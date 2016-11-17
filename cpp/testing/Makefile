TOP_DIR := ..
SRC_DIR := ./src
INCLUDE_DIR := ./include
BIN_DIR := ./bin
OBJ_DIR := ./obj
GENERATED_SRC_DIR := $(TOP_DIR)/generated_src
TOP_INCLUDE_DIR := $(TOP_DIR)/include
TOP_OBJ_DIR := $(TOP_DIR)/obj
DEP_DIR = ./depends

CC := g++
CPPFLAGS += -I $(INCLUDE_DIR) -I $(SRC_DIR) -I $(TOP_INCLUDE_DIR) -I $(GENERATED_SRC_DIR) -I /usr/local/include 
CFLAGS +=  -g -fPIC -std=c++14 
LDFLAGS += -L/usr/local/lib 
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.Td	
LDLIBS += -lgrpc++ -lgrpc -lboost_thread-mt -lboost_system-mt -lboost_program_options-mt -lprotobuf -lpthread -ldl -lgrpc++_reflection -lglog -lgtest -lgtest_main

BIN := roper_test
TARGET := $(BIN_DIR)/$(BIN)
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS)) $(wildcard $(TOP_OBJ_DIR)/*.o)
DEPENDS := $(wildcard $(DEP_DIR)/*.d)
MAIN_OBJS := $(addprefix $(TOP_OBJ_DIR)/, main.o)
OBJS := $(filter-out $(MAIN_OBJS), $(OBJS))

COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
COMPILE.cc = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c

RM := rm -rf
MKDIR := mkdir -p
POSTCOMPILE = mv -f $(DEP_DIR)/$*.Td $(DEP_DIR)/$*.d

.PHONY: install clean clobber

all : compile $(TARGET)

compile:
	$(MAKE) -C $(TOP_DIR)

$(TARGET) : $(OBJS)
	@$(MKDIR) $(dir $@)
	$(LINK.c) $(LDLIBS) -o $@ $^

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(DEP_DIR)/%.d
	@$(MKDIR) $(dir $@)
	$(COMPILE.c) $< -o $@
	$(POSTCOMPILE)

.PRECIOUS: $(DEP_DIR)/%.d
$(DEP_DIR)/%.d:
	@$(MKDIR) $(dir $@)

clean:
	$(RM) $(OBJ_DIR)/*.o

clobber: clean
	$(RM) $(OBJ_DIR)
	$(RM) $(DEP_DIR)
	$(RM) $(TARGET)

-include $(DEPENDS)

