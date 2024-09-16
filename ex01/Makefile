# Compiler and flags
NAME        =   RPN
CXX         =   c++
CXXFLAGS    =   -Wall -Werror -Wextra -std=c++98 -pedantic-errors

# Directories
SRC_DIR                 =   src/
OBJ_DIR                 =   obj/
INC_DIR                 =   include/
CURRENT_PATH            =   $(shell pwd)
CURRENT_DIRECTORY_NAME  =   $(shell basename $(CURRENT_PATH))
CURRENT_DIRECTORY       :=  ./$(CURRENT_DIRECTORY_NAME)

# Control codes
RESET       =   \033[0m
GREEN       =   \033[32m
YELLOW      =   \033[33m
BLUE        =   \033[34m
RED         =   \033[31m
UP          =   \033[A
CUT         =   \033[K

# Automatically discover source files
SRC_FILES   :=  $(wildcard $(SRC_DIR)*.cpp)
OBJ_FILES   :=  $(SRC_FILES:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)

# Variables for loading percentage
TOTAL_FILES =   $(words $(SRC_FILES))
COMPILED_FILES = 0
COMPILED = 0

# All rule
all: $(NAME)

# Compile the executable
$(NAME): $(OBJ_FILES)
	@printf "$(YELLOW)Compiling [$(NAME)]...$(RESET)\n"
	@$(CXX) $(CXXFLAGS) $(OBJ_FILES) -o $(NAME)
	@printf "$(GREEN)Finished [$(NAME)]$(RESET)\n"
	@$(eval COMPILED=1)
	@if [ $(COMPILED) -eq 1 ]; then \
    		printf "\n"; \
    		printf "$(GREEN)                  EEEEEEEEEEEEEEEEEEEEEE\n$(RESET)"; \
    		printf "$(GREEN)      <<<<<<<     E::::::::::::::::::::E                      >>>>>>>      \n$(RESET)"; \
    		printf "$(GREEN)     <:::::<      E::::::::::::::::::::E                       >:::::>     \n$(RESET)"; \
    		printf "$(GREEN)    <:::::<       EE::::::EEEEEEEEE::::E                        >:::::>    \n$(RESET)"; \
    		printf "$(GREEN)   <:::::<          E:::::E       EEEEEEzzzzzzzzzzzzzzzzz        >:::::>   \n$(RESET)"; \
    		printf "$(GREEN)  <:::::<           E:::::E             z:::::::::::::::z         >:::::>  \n$(RESET)"; \
    		printf "$(GREEN) <:::::<            E::::::EEEEEEEEEE   z::::::::::::::z           >:::::> \n$(RESET)"; \
    		printf "$(GREEN)<:::::<             E:::::::::::::::E   zzzzzzzz::::::z             >:::::>\n$(RESET)"; \
    		printf "$(GREEN) <:::::<            E:::::::::::::::E         z::::::z             >:::::> \n$(RESET)"; \
    		printf "$(GREEN)  <:::::<           E::::::EEEEEEEEEE        z::::::z             >:::::>  \n$(RESET)"; \
    		printf "$(GREEN)   <:::::<          E:::::E                 z::::::z             >:::::>   \n$(RESET)"; \
    		printf "$(GREEN)    <:::::<         E:::::E       EEEEEE   z::::::z             >:::::>    \n$(RESET)"; \
    		printf "$(GREEN)     <:::::<      EE::::::EEEEEEEE:::::E  z::::::zzzzzzzz      >:::::>     \n$(RESET)"; \
    		printf "$(GREEN)      <<<<<<<     E::::::::::::::::::::E z::::::::::::::z     >>>>>>>      \n$(RESET)"; \
    		printf "$(GREEN)                  E::::::::::::::::::::Ez:::::::::::::::z                  \n$(RESET)"; \
    		printf "$(GREEN)                  EEEEEEEEEEEEEEEEEEEEEEzzzzzzzzzzzzzzzzz                  \n$(RESET)"; \
    		printf "\n"; \
    	fi

# Compile objects with progress
$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	$(eval COMPILED_FILES=$(shell echo $$(($(COMPILED_FILES)+1))))
	@PERCENT=$(shell echo $$((100 * $(COMPILED_FILES) / $(TOTAL_FILES)))); \
	printf "$(YELLOW)Compiling [$@]... $(COMPILED_FILES)/$(TOTAL_FILES) ($$PERCENT%%)$(RESET)\n";
	@$(CXX) $(CXXFLAGS) -I $(INC_DIR) -o $@ -c $<
	@printf "$(UP)$(CUT)"
	@printf "$(GREEN)Finished [$@]$(RESET)\n"
	@printf "$(UP)$(CUT)"
	@$(eval COMPILED=1)

# Clean rule
clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
	rm -rf $(OBJ_DIR); \
	printf "$(BLUE)Deleting all objects from $(CURRENT_DIRECTORY)...$(RESET)\n"; else \
	printf "No objects to remove from $(CURRENT_DIRECTORY).\n"; \
	fi;

# Fclean rule
fclean: clean
	@if [ -f "$(NAME)" ]; then \
	rm -f $(NAME); \
	printf "$(BLUE)Deleting $(RED)$(NAME)$(BLUE) binary from $(CURRENT_DIRECTORY)$(RESET)\n"; else \
	printf "No Executable to remove from $(CURRENT_DIRECTORY).\n"; \
	fi;

# Rebuild rule
re: fclean all

# Run rule (optional)
run: $(NAME)
	./$(NAME)

# Phony targets
.PHONY: all clean fclean re run
