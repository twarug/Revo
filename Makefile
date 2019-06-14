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
CXX_FLAGS := -std=c++17 -g -Wall -Wextra -Wpedantic -DRV_DEBUG -DRV_OPENGL

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
TCH_BUILD   := Debug
TCH_PATH    := $(TCH_TARGET)/$(TCH_NAME)/$(TCH_VERSION)/$(TCH_BUILD)

# Target (app | dynamic | static)
TARGET = app

# Project directories
SRC_DIR := Revo/source
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

# ImGui SDL2
IMGUI_SDL2_NAME := ImGuiSDL2-1.67
IMGUI_SDL2_IDIR := -isystem $(LIBS_DIR)/$(IMGUI_SDL2_NAME)/include
IMGUI_SDL2_LIBS := -L$(LIBS_DIR)/$(IMGUI_SDL2_NAME)/lib/$(TCH_PATH) -limgui

# ImGui GLFW
IMGUI_GLFW_NAME := ImGuiGLFW-1.65
IMGUI_GLFW_IDIR := -isystem $(LIBS_DIR)/$(IMGUI_GLFW_NAME)/include
IMGUI_GLFW_LIBS := -L$(LIBS_DIR)/$(IMGUI_GLFW_NAME)/lib/$(TCH_PATH) -limgui

# SDL2
SDL2_NAME := SDL2-2.0.9
SDL2_IDIR := -isystem $(LIBS_DIR)/$(SDL2_NAME)/include
SDL2_LIBS := -L$(LIBS_DIR)/$(SDL2_NAME)/lib/$(TCH_PATH) -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lgdi32 -limm32

# GLFW
GLFW_NAME := GLFW-3.2.1
GLFW_IDIR := -isystem $(LIBS_DIR)/$(GLFW_NAME)/include
GLFW_LIBS := -L$(LIBS_DIR)/$(GLFW_NAME)/lib/$(TCH_PATH) -lglfw3 -lgdi32 -lopengl32

# glad
GLAD_NAME := glad-3.3.0
GLAD_IDIR := -isystem $(LIBS_DIR)/$(GLAD_NAME)/include
GLAD_LIBS := -L$(LIBS_DIR)/$(GLAD_NAME)/lib/$(TCH_TARGET)/$(TCH_NAME)/$(TCH_VERSION) -lglad

# glm
GLM_NAME := glm-0.9.9.3
GLM_IDIR := -isystem $(LIBS_DIR)/$(GLM_NAME)/include
GLM_LIBS :=

# nlohmann Json
NLOHMANN_JSON_NAME := nlohmannJson-3.5.0
NLOHMANN_JSON_IDIR := -isystem $(LIBS_DIR)/$(NLOHMANN_JSON_NAME)/include
NLOHMANN_JSON_LIBS :=

# stb
STB_NAME := stb
STB_IDIR := -isystem $(LIBS_DIR)/$(STB_NAME)/include
STB_LIBS :=

# fmt
FMT_NAME := fmt-5.3.0
FMT_IDIR := -isystem $(LIBS_DIR)/$(FMT_NAME)/include
FMT_LIBS :=

# Final libraries config
IDIR := $(IMGUI_SDL2_IDIR) $(SDL2_IDIR) $(GLAD_IDIR) $(GLM_IDIR) $(NLOHMANN_JSON_IDIR) $(STB_IDIR) $(FMT_IDIR) -IRevo/include
LIBS := $(IMGUI_SDL2_LIBS) $(SDL2_LIBS) $(GLAD_LIBS) $(GLM_LIBS) $(NLOHMANN_JSON_LIBS) $(STB_LIBS) $(FMT_LIBS)

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

rf:
	make clean && make -j4

rrf:
	make clean && make run -j4

clean:
	$(V) find $(OBJ_DIRS) -type f -name '*.o' -delete

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
