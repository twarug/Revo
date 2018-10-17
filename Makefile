# Additional options
V = @

# Commands
MKDIR := mkdir -p
RM    := rm -rf
LS    := ls -AdoGh --time-style long-iso

# Informs
INFORM_INFO_COUNT := printf "\n> \033[36m%s (%s)\033[0m\n"
INFORM_EXE        := printf "\033[32m[Executable] %s\033[0m\n"
INFORM_OBJECT     := printf "\033[33m[Object] %s\033[0m\n"

# Compiler
CXX       := g++
CXX_FLAGS := -std=c++17 -g -Wall -Wextra -Wpedantic -DM2_DEBUG

# Linker
LD       := g++
LD_FLAGS := -lcomdlg32 -lstdc++fs

# Static linker
STATIC_LD       := ar rcs
STATIC_LD_FLAGS :=

# Dynamic linker
DYNAMIC_LD       := g++
DYNAMIC_LD_FLAGS := -shared

# Toolchain info
TCH_TARGET  := x86_64
TCH_NAME    := MinGW
TCH_VERSION := 7.3.0
TCH_PATH    := $(TCH_TARGET)/$(TCH_NAME)/$(TCH_VERSION)

# Target (app | dynamic | static)
TARGET = app

# Project directories
SRC_DIR := src
OBJ_DIR := obj
OUT_DIR := out

# Sources & objects
SRC_GLOB := '*.cpp'

SRC_DIRS := $(shell find $(SRC_DIR) -type d)
OBJ_DIRS := $(addprefix $(OBJ_DIR)/,$(SRC_DIRS))
SOURCES  := $(shell find $(SRC_DIR) -type f -name $(SRC_GLOB))
OBJECTS  := $(addprefix $(OBJ_DIR)/,$(addsuffix .o,$(SOURCES)))

# Executable
EXE_NAME := a.exe
EXE      := $(OUT_DIR)/$(EXE_NAME)

# Directory for all libraries
LIBS_DIR := E:/Dev/Libraries

# GLFW
GLFW_IDIR := -isystem $(LIBS_DIR)/GLFW-3.2.1/include
GLFW_LIBS := -L$(LIBS_DIR)/GLFW-3.2.1/lib/$(TCH_PATH) -lglfw3 -lgdi32 -lopengl32

# glad
GLAD_IDIR := -isystem $(LIBS_DIR)/glad-3.3.0/include
GLAD_LIBS := -L$(LIBS_DIR)/glad-3.3.0/lib/$(TCH_PATH) -lglad

# glm
GLM_IDIR := -isystem $(LIBS_DIR)/glm-0.9.9/include
GLM_LIBS :=

# ImGui
IMGUI_IDIR := -isystem src/ImGui
IMGUI_LIBS :=

# nlohmann Json
JSON_IDIR := -isystem $(LIBS_DIR)/nlohmannJson-3.1.2/include
JSON_LIBS :=

# stb
STB_IDIR := -isystem $(LIBS_DIR)/stb/include
STB_LIBS :=

# Final libraries config
IDIR := $(GLFW_IDIR) $(GLAD_IDIR) $(GLM_IDIR) $(IMGUI_IDIR) $(JSON_IDIR) $(STB_IDIR) -Iinclude -IC:/Users/Stritch/github/m2/src
LIBS := $(GLFW_LIBS) $(GLAD_LIBS) $(GLM_LIBS) $(IMGUI_LIBS) $(JSON_LIBS) $(STB_LIBS)

# .PHONY
.PHONY := all dirs re run rerun clean

all: dirs $(EXE)

$(EXE): $(OBJECTS)
	$(V) $(INFORM_EXE) $@
	$(V) $(LD) -o $@ $^ $(LD_FLAGS) $(LIBS)
	$(V) chmod +x $@
	$(V) $(LS) $@

dirs:
	$(V) $(MKDIR) $(OUT_DIR) $(OBJ_DIR) $(OBJ_DIRS)

$(OBJ_DIR)/%.o: %
	$(V) $(INFORM_OBJECT) $@
	$(V) $(CXX) -o $@ -c $< $(CXX_FLAGS) $(IDIR)
	$(V) $(LS) $@

run: all
	$(V) cd $(OUT_DIR) ; ./$(EXE_NAME)

re: clean all

rerun: re run

clean:
	$(V) find $(OBJECTS_DIR) -type f -name '*.o' -delete

info:
	$(V) $(INFORM_INFO_COUNT) "Sources directories" $(words $(SRC_DIRS))
	$(V) echo $(SRC_DIRS) | sed 's/ /\n/g'
	$(V) $(INFORM_INFO_COUNT) "Sources" $(words $(SOURCES))
	$(V) echo $(SOURCES) | sed 's/ /\n/g'
	$(V) $(INFORM_INFO_COUNT) "Objects directories" $(words $(OBJ_DIRS))
	$(V) echo $(OBJ_DIRS) | sed 's/ /\n/g'
	$(V) $(INFORM_INFO_COUNT) "Objects" $(words $(OBJECTS))
	$(V) echo $(OBJECTS) | sed 's/ /\n/g'
	$(V) $(INFORM_INFO_COUNT) "Executable" $(words $(EXE))
	$(V) echo $(EXE)
