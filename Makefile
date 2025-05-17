##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile
##

CXX     = g++
RM      = rm -f
FIND    = find
ECHO    = echo -e

SRC_DIR     = src
INCLUDE_DIR = include

NAME        = labyrinth

BLACK       = \033[0;30m
RED         = \033[0;31m
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
BLUE        = \033[0;34m
MAGENTA     = \033[0;35m
CYAN        = \033[0;36m
WHITE       = \033[0;37m
BOLD        = \033[1m
RESET       = \033[0m

CXXFLAGS    = -Wall -Wextra -std=c++11 -iquote $(INCLUDE_DIR)
LDFLAGS     = -lsfml-graphics -lsfml-window -lsfml-system

DEBUG_FLAGS = -g3 -DDEBUG

SRC_CORE = main.cpp labyrinthe.cpp

SRC = $(addprefix $(SRC_DIR)/, $(SRC_CORE))

OBJ     = $(SRC:.cpp=.o)

all: intro $(NAME) outro

intro:
	@clear
	@$(ECHO) "$(RED)  ██╗      █████╗ ██████╗ ██╗   ██╗██████╗ ██╗███╗   ██╗████████╗██╗  ██╗"
	@$(ECHO) "$(RED)  ██║     ██╔══██╗██╔══██╗╚██╗ ██╔╝██╔══██╗██║████╗  ██║╚══██╔══╝██║  ██║"
	@$(ECHO) "$(RED)  ██║     ███████║██████╔╝ ╚████╔╝ ██████╔╝██║██╔██╗ ██║   ██║   ███████║"
	@$(ECHO) "$(RED)  ██║     ██╔══██║██╔══██╗  ╚██╔╝  ██╔══██╗██║██║╚██╗██║   ██║   ██╔══██║"
	@$(ECHO) "$(RED)  ███████╗██║  ██║██████╔╝   ██║   ██║  ██║██║██║ ╚████║   ██║   ██║  ██║"
	@$(ECHO) "$(RED)  ╚══════╝╚═╝  ╚═╝╚═════╝    ╚═╝   ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝"
	@$(ECHO) "$(YELLOW)===============================================================$(RESET)"
	@$(ECHO) "$(CYAN)➤ Building Labyrinth project$(RESET)"
	@$(ECHO) "$(YELLOW)===============================================================$(RESET)"

outro:
	@$(ECHO) "$(GREEN)$(BOLD)  🎮 LABYRINTH successfully built! 🎮$(RESET)"
	@$(ECHO) "$(CYAN)  Run with: $(WHITE)./$(NAME)$(RESET)"
	@$(ECHO) "$(CYAN)  Run with map: $(WHITE)./$(NAME) map/map_easy.txt$(RESET)"

$(NAME): $(OBJ)
	@$(ECHO) "$(YELLOW)⚡ Linking executable: $(CYAN)$@$(RESET)"
	@$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@$(ECHO) "$(GREEN)✓ Build complete!$(RESET)"

debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: clean intro $(NAME)
	@$(ECHO) "$(GREEN)✓ Debug build complete!$(RESET)"

run: $(NAME)
	@$(ECHO) "$(YELLOW)🎮 Starting Labyrinth...$(RESET)"
	@./$(NAME)

run_test: $(NAME)
	@$(ECHO) "$(YELLOW)🎮 Starting Labyrinth with test map...$(RESET)"
	@./$(NAME) map/map_easy.txt

valgrind: $(NAME)
	@$(ECHO) "$(MAGENTA)🔍 Running memory check with Valgrind...$(RESET)"
	@valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) map/map_easy.txt

%.o: %.cpp
	@$(ECHO) "$(BLUE)Compiling: $(WHITE)$<$(RESET)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@$(ECHO) "$(RED)🧹 Cleaning object files...$(RESET)"
	@$(FIND) . -name "*.o" -delete
	@$(ECHO) "$(GREEN)✓ Object files removed.$(RESET)"

fclean: clean
	@$(ECHO) "$(RED)╔══════════════════════════════════════╗$(RESET)"
	@$(ECHO) "$(RED)║         FULL CLEANUP WIZARD          ║$(RESET)"
	@$(ECHO) "$(RED)╚══════════════════════════════════════╝$(RESET)"
	@$(ECHO) "$(YELLOW)➤ $(CYAN)Removing coverage files...$(RESET)"
	@$(FIND) . -name "*.gcno" -delete
	@$(FIND) . -name "*.gcda" -delete
	@$(ECHO) "$(YELLOW)➤ $(CYAN)Removing executable and debug files...$(RESET)"
	@$(RM) $(NAME) a.out vgcore*
	@sleep 0.1
	@$(ECHO) "$(GREEN)╔══════════════════════════════════════╗$(RESET)"
	@$(ECHO) "$(GREEN)║       CLEANUP COMPLETE! (100%)       ║$(RESET)"
	@$(ECHO) "$(GREEN)╚══════════════════════════════════════╝$(RESET)"

re: fclean all

help:
	@$(ECHO) "$(YELLOW)╔═════════════════════════════════════════════════╗$(RESET)"
	@$(ECHO) "$(YELLOW)║             LABYRINTH MAKE COMMANDS             ║$(RESET)"
	@$(ECHO) "$(YELLOW)╚═════════════════════════════════════════════════╝$(RESET)"
	@$(ECHO) "$(CYAN)  make$(RESET)        - Build the labyrinth game"
	@$(ECHO) "$(CYAN)  make run$(RESET)    - Run the game"
	@$(ECHO) "$(CYAN)  make run_test$(RESET) - Run with test map"
	@$(ECHO) "$(CYAN)  make debug$(RESET)  - Build with debug symbols"
	@$(ECHO) "$(CYAN)  make valgrind$(RESET) - Check for memory leaks"
	@$(ECHO) "$(CYAN)  make clean$(RESET)  - Remove object files"
	@$(ECHO) "$(CYAN)  make fclean$(RESET) - Remove all generated files"
	@$(ECHO) "$(CYAN)  make re$(RESET)     - Rebuild the project"
	@$(ECHO) "$(CYAN)  make help$(RESET)   - Display this help"

.PHONY: make all debug run run_test valgrind clean fclean re help intro outro
