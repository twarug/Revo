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
CXX_FLAGS := -std=c++17 -O2 -flto -Wall -Wextra -Wpedantic -DRV_DEBUG -DRV_OPENGL

# Linker
LD       := g++
LD_FLAGS := -flto -s -static

# Static linker
STATIC_LD       := ar rcs
STATIC_LD_FLAGS :=

# Dynamic linker
DYNAMIC_LD       := g++
DYNAMIC_LD_FLAGS := -shared

# Toolchain info
TCH_NAME := MinGW

# Target (app | dynamic | static)
TARGET = app

# Project directories
SRC_DIR := Revo/source example
OBJ_DIR := obj
OUT_DIR := example

# Sources & objects
SRC_GLOB := '*.cpp'

SRC_DIRS := $(shell find $(SRC_DIR) -type d)
OBJ_DIRS := $(addprefix $(OBJ_DIR)/,$(SRC_DIRS))
SOURCES  := $(shell find $(SRC_DIR) -type f -name $(SRC_GLOB))
OBJECTS  := $(addprefix $(OBJ_DIR)/,$(addsuffix .o,$(SOURCES)))

# Executable
EXE_NAME := RevoTest.exe
EXE      := $(OUT_DIR)/$(EXE_NAME)

# Directory for all libraries
LIBS_DIR := E:/Dev/Libraries

# ImGui SDL2
IMGUI_SDL2_NAME := ImGuiSDL2
IMGUI_SDL2_IDIR := -isystem $(LIBS_DIR)/$(IMGUI_SDL2_NAME)/include
IMGUI_SDL2_LIBS := -L$(LIBS_DIR)/$(IMGUI_SDL2_NAME)/lib/$(TCH_NAME) -limgui

# SDL2
SDL2_NAME := SDL2
SDL2_IDIR := -isystem $(LIBS_DIR)/$(SDL2_NAME)/include
SDL2_LIBS := -L$(LIBS_DIR)/$(SDL2_NAME)/lib/$(TCH_NAME) -lmingw32 -lSDL2main -lSDL2 -mwindows -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid -lsetupapi -lhid -static-libgcc

# glad
GLAD_NAME := glad
GLAD_IDIR := -isystem $(LIBS_DIR)/$(GLAD_NAME)/include
GLAD_LIBS := -L$(LIBS_DIR)/$(GLAD_NAME)/lib/$(TCH_NAME) -lglad

# glm
GLM_NAME := glm
GLM_IDIR := -isystem $(LIBS_DIR)/$(GLM_NAME)/include
GLM_LIBS :=

# nlohmann Json
NLOHMANN_JSON_NAME := nlohmannJson
NLOHMANN_JSON_IDIR := -isystem $(LIBS_DIR)/$(NLOHMANN_JSON_NAME)/include
NLOHMANN_JSON_LIBS :=

# stb
STB_NAME := stb
STB_IDIR := -isystem $(LIBS_DIR)/$(STB_NAME)/include
STB_LIBS :=

# fmt
FMT_NAME := fmt
FMT_IDIR := -isystem $(LIBS_DIR)/$(FMT_NAME)/include
FMT_LIBS :=

# Final libraries config
IDIR := $(IMGUI_SDL2_IDIR) $(SDL2_IDIR) $(GLAD_IDIR) $(GLM_IDIR) $(NLOHMANN_JSON_IDIR) $(STB_IDIR) $(FMT_IDIR) -IRevo/include
LIBS := $(IMGUI_SDL2_LIBS) $(SDL2_LIBS) $(GLAD_LIBS) $(GLM_LIBS) $(NLOHMANN_JSON_LIBS) $(STB_LIBS) $(FMT_LIBS)

# .PHONY
.PHONY := all dirs re run rf rrf clean pure

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

rf:
	make clean && make -j4

rrf:
	make clean && make run -j4

clean:
	$(V) find $(OBJ_DIRS) -type f -name '*.o' -delete
	rm $(EXE)

pure:
	$(V) rm -rf $(OBJ_DIR)

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
