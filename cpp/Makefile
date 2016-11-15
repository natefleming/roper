TOP_DIR := ..
SRC_DIR := ./src
GENERATED_SRC_DIR := ./generated_src
PROTO_DIR := $(TOP_DIR)/proto
INCLUDE_DIR := ./include
BIN_DIR := ./bin
OBJ_DIR := ./obj
DEP_DIR = ./depends

CC := g++
CPPFLAGS += -I $(INCLUDE_DIR) -I $(SRC_DIR) -I $(GENERATED_SRC_DIR) -I /usr/local/include 
CFLAGS +=  -g -fPIC -std=c++14 
LDFLAGS += -L/usr/local/lib 
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.Td	
LDLIBS += -lgrpc++ -lgrpc -lboost_thread-mt -lboost_system-mt -lboost_program_options-mt -lprotobuf -lpthread -ldl -lgrpc++_reflection -lglog
PROTOC=protoc
GRPC_CPP_PLUGIN := grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= $(shell which $(GRPC_CPP_PLUGIN))

BIN := main
TARGET := $(BIN_DIR)/$(BIN)
PROTO_SRCS := $(wildcard $(PROTO_DIR)/*.proto)
PROTO_PB_SRCS := $(patsubst $(PROTO_DIR)/%.proto, $(GENERATED_SRC_DIR)/%.pb.cc, $(PROTO_SRCS))
PROTO_GRPC_SRCS := $(patsubst $(PROTO_DIR)/%.proto, $(GENERATED_SRC_DIR)/%.grpc.pb.cc, $(PROTO_SRCS))
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(GENERATED_SRC_DIR)/%.pb.cc, $(OBJ_DIR)/%.pb.o, $(PROTO_PB_SRCS) $(PROTO_GRPC_SRCS)) $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
DEPENDS := $(wildcard $(DEP_DIR)/*.d)

COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
COMPILE.cc = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c

#MAIN_OBJS := $(addprefix $(OBJ_DIR)/, main.o)
#OBJS := $(filter-out $(MAIN_OBJS), $(OBJS))

RM := rm -rf
MKDIR := mkdir -p
POSTCOMPILE = mv -f $(DEP_DIR)/$*.Td $(DEP_DIR)/$*.d

.PHONY: install clean clobber

all : system-check $(TARGET)

$(TARGET) : $(OBJS)
	@$(MKDIR) $(dir $@)
	$(LINK.c) $(LDLIBS) -o $@ $^

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(DEP_DIR)/%.d
	@$(MKDIR) $(dir $@)
	$(COMPILE.c) $< -o $@
	$(POSTCOMPILE)

$(OBJ_DIR)/%.pb.o : $(GENERATED_SRC_DIR)/%.pb.cc $(DEP_DIR)/%.d
	@$(MKDIR) $(dir $@)
	$(COMPILE.c) $< -o $@
	$(POSTCOMPILE)

$(OBJ_DIR)/%.grpc.pb.o : $(GENERATED_SRC_DIR)/%.grpc.pb.cc $(DEP_DIR)/%.d
	@$(MKDIR) $(dir $@)
	$(COMPILE.c) $< -o $@
	$(POSTCOMPILE)

.PRECIOUS: $(GENERATED_SRC_DIR)/%.grpc.pb.cc 
$(GENERATED_SRC_DIR)/%.grpc.pb.cc: $(PROTO_DIR)/%.proto
	@$(MKDIR) $(dir $@)
	$(PROTOC) -I $(PROTO_DIR) --grpc_out=$(GENERATED_SRC_DIR) --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

.PRECIOUS: $(GENERATED_SRC_DIR)/%.pb.cc
$(GENERATED_SRC_DIR)/%.pb.cc: $(PROTO_DIR)/%.proto
	@$(MKDIR) $(dir $@)
	$(PROTOC) -I $(PROTO_DIR) --cpp_out=$(GENERATED_SRC_DIR) $<

.PRECIOUS: $(DEP_DIR)/%.d
$(DEP_DIR)/%.d:
	@$(MKDIR) $(dir $@)

install:

clean:
	$(RM) $(OBJ_DIR)/*.o
	$(RM) $(GENERATED_SRC_DIR)/*

clobber: clean
	$(RM) $(GENERATED_SRC_DIR)
	$(RM) $(OBJ_DIR)
	$(RM) $(DEP_DIR)
	$(RM) $(TARGET)

-include $(DEPENDS)

PROTOC_CMD = which $(PROTOC)
PROTOC_CHECK_CMD = $(PROTOC) --version | grep -q libprotoc.3
PLUGIN_CHECK_CMD = which $(GRPC_CPP_PLUGIN)
HAS_PROTOC = $(shell $(PROTOC_CMD) > /dev/null && echo true || echo false)
ifeq ($(HAS_PROTOC),true)
HAS_VALID_PROTOC = $(shell $(PROTOC_CHECK_CMD) 2> /dev/null && echo true || echo false)
endif
HAS_PLUGIN = $(shell $(PLUGIN_CHECK_CMD) > /dev/null && echo true || echo false)

SYSTEM_OK = false
ifeq ($(HAS_VALID_PROTOC),true)
ifeq ($(HAS_PLUGIN),true)
SYSTEM_OK = true
endif
endif

system-check:
ifneq ($(HAS_VALID_PROTOC),true)
	@echo " DEPENDENCY ERROR"
	@echo
	@echo "You don't have protoc 3.0.0 installed in your path."
	@echo "Please install Google protocol buffers 3.0.0 and its compiler."
	@echo "You can find it here:"
	@echo
	@echo "   https://github.com/google/protobuf/releases/tag/v3.0.0"
	@echo
	@echo "Here is what I get when trying to evaluate your version of protoc:"
	@echo
	-$(PROTOC) --version
	@echo
	@echo
endif
ifneq ($(HAS_PLUGIN),true)
	@echo " DEPENDENCY ERROR"
	@echo
	@echo "You don't have the grpc c++ protobuf plugin installed in your path."
	@echo "Please install grpc. You can find it here:"
	@echo
	@echo "   https://github.com/grpc/grpc"
	@echo
	@echo "Here is what I get when trying to detect if you have the plugin:"
	@echo
	-which $(GRPC_CPP_PLUGIN)
	@echo
	@echo
endif
ifneq ($(SYSTEM_OK),true)
	@false
endif
