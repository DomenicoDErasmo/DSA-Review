COMPILER		:= clang++
CURRENT_DIR		:= $(subst /,\,${CURDIR})
FOLDER			:= testing
EXTENSION		:= cpp
INCLUDE_FLAGS 	:= -I $(FOLDER) -I src
COMPILER_FLAGS 	:= -g -MD -Wall -Werror -Wvla -Wgnu-folding-constant -Wno-missing-braces -fdeclspec
LINKER_FLAGS 	:= -g
SUBDIRS 		:= \$(FOLDER) $(subst $(CURRENT_DIR),,$(shell dir $(FOLDER) /S /AD /B | findstr /i $(FOLDER)))

# Make does not offer a recursive wildcard function, so here's one:
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
CODE_FILES 		:= $(call rwildcard,$(FOLDER)/,*.$(EXTENSION)) # Get all .cpp files
OBJ				:= obj
OBJ_FILES		:= $(CODE_FILES:%=$(OBJ)/%.o)
BIN 			:= bin
EXECUTABLE		:= $(BIN)\$(FOLDER).exe

build: scaffold link

.PHONY: scaffold
scaffold:
	@echo Scaffolding folder structure...
	-@setlocal enableextensions enabledelayedexpansion && mkdir $(addprefix $(OBJ), $(SUBDIRS)) 2>NUL || cd .
	-@setlocal enableextensions enabledelayedexpansion && mkdir $(BIN) 2>NUL || cd .
	@echo Done.

$(OBJ)/%.$(EXTENSION).o: %.$(EXTENSION) # compile .cpp to .cpp.o object
	@echo   $<...
	@$(COMPILER) $< $(COMPILER_FLAGS) -c -o $@ $(INCLUDE_FLAGS)

.PHONY: link
link: $(OBJ_FILES)
	@$(COMPILER) $(OBJ_FILES) -o $(BIN)/$(FOLDER).exe $(LINKER_FLAGS)

.PHONY: clean
clean:
	@echo Deleting all files in $(BIN)\$(FOLDER)
	@del /s $(BIN)\$(FOLDER)*
	@echo Deleting $(OBJ)\$(FOLDER) if it exists
	@if exist .\$(OBJ)\$(FOLDER) rmdir /s /q .\$(OBJ)\$(FOLDER)
	@echo Done
