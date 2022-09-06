COMPILER		:= clang++
CURRENT_DIR		:= $(subst /,\,${CURDIR})
TESTING			:= testing
FILE_EXTENSION	:= cpp
INCLUDE_FLAGS 	:= -I src -I $(TESTING)
COMPILER_FLAGS	:= -g
SRC_SUBDIRS 	:= \$(TESTING) $(subst $(CURRENT_DIR),,$(shell dir $(TESTING) /S /AD /B | findstr /i $(TESTING)))

# Make does not offer a recursive wildcard function, so here's one:
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
SRC_FILES 		:= $(call rwildcard,$(TESTING)/,*.$(FILE_EXTENSION)) # Get all .cpp files
OBJ				:= obj
OBJ_FILES		:= $(SRC_FILES:%=$(OBJ)/%.o)
BIN 			:= bin
EXECUTABLE		:= $(BIN)\$(TESTING).exe

build: scaffold link

test:
	@echo SRC_SUBDIRS: $(SRC_SUBDIRS)

.PHONY: scaffold
scaffold:
	@echo Scaffolding folder structure...
	-@setlocal enableextensions enabledelayedexpansion && mkdir $(BIN) 2>NUL || cd .
	-@setlocal enableextensions enabledelayedexpansion && mkdir $(addprefix $(OBJ), $(SRC_SUBDIRS)) 2>NUL || cd .
	@echo Done.

$(OBJ)/%.$(FILE_EXTENSION).o: %.$(FILE_EXTENSION) # compile .cpp to .cpp.o object
	@echo   $<...
	$(COMPILER) $< $(COMPILER_FLAGS) -c -o $@ $(INCLUDE_FLAGS)

.PHONY: link
link: $(OBJ_FILES)
	@$(COMPILER) $(OBJ_FILES) -o $(BIN)/$(TESTING).exe

.PHONY: clean
clean:
	if exist .\$(EXECUTABLE) del .\$(EXECUTABLE)
	rmdir /s /q .\obj\$(TESTING)