# ══ Names ═══════════════════════════════════════════════════════════════════ #

NAME 				= philo_bonus
EXEC_PATH			= $(NAME)

# ══ Colors ══════════════════════════════════════════════════════════════════ #

DEL_LINE 			= \033[2K
ITALIC 				= \033[3m
BOLD 				= \033[1m
DEF_COLOR 			= \033[0m
GRAY 				= \033[0;90m
RED 				= \033[0;91m
GREEN 				= \033[0;92m
YELLOW 				= \033[0;93m
BLUE 				= \033[0;94m
MAGENTA 			= \033[0;95m
CYAN 				= \033[0;96m
WHITE 				= \033[0;97m
BLACK 				= \033[0;99m
ORANGE 				= \033[38;5;209m
BROWN 				= \033[38;2;184;143;29m
DARK_GRAY 			= \033[38;5;234m
MID_GRAY 			= \033[38;5;245m
DARK_GREEN 			= \033[38;2;75;179;82m
DARK_YELLOW 		= \033[38;5;143m

# ══ Compilation══════════════════════════════════════════════════════════════ #

CC 					= clang
AR 					= ar rcs
RM 					= rm -f
MK 					= make -C -g
MKD					= mkdir -p
MCL 				= make clean -C
MFCL 				= make fclean -C
MK_					= && make

# ══ Directorios ════════════════════════════════════════════════════════════ #
SRC_DIR             = ./src
INIT_DIR            = ./init_struct
SIM_DIR             = ./simulator
OBJ_DIR             = ./obj
INCLUDES_DIR        = ./includes
EXEC_PATH           = ./philo_bonus # Nombre del ejecutable

# ══ Flags ══════════════════════════════════════════════════════════════════ #
CFLAGS              = -Wall -Werror -Wextra
IFLAGS              = -I${INCLUDES_DIR}
LFLAGS              = -lpthread

# ══ Fuentes y objetos ══════════════════════════════════════════════════════ #
SRC                 = ${SRC_DIR}/checker_bonus.c \
						${SRC_DIR}/utils_bonus.c \
						${SRC_DIR}/manage_philos_bonus.c 

INT                 = ${INIT_DIR}/init_struct_bonus.c \

SIM                 = ${SIM_DIR}/philo_bonus.c \
						${SIM_DIR}/init_simulation_bonus.c
                     
OBJ_SRC             = $(patsubst ${SRC_DIR}/%.c, ${OBJ_DIR}/%.o, ${SRC})
OBJ_INT             = $(patsubst ${INIT_DIR}/%.c, ${OBJ_DIR}/%.o, ${INT})
OBJ_SIM             = $(patsubst ${SIM_DIR}/%.c, ${OBJ_DIR}/%.o, ${SIM})
OBJS                = ${OBJ_SRC} ${OBJ_INT} ${OBJ_SIM}

# ══ Reglas ═════════════════════════════════════════════════════════════════ #
all: ${EXEC_PATH}

${EXEC_PATH}: ${OBJS}
	@echo "$(YELLOW)Compiling ...$(DEF_COLOR)"
	@${CC} ${CFLAGS} ${IFLAGS} -o $@ ${OBJS} ${LFLAGS}
	@echo "$(GREEN) $(EXEC_PATH) all created ✓$(DEF_COLOR)"

# Reglas para generar objetos
${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	@mkdir -p $(dir $@) # Asegura que el directorio obj exista
	@${CC} ${CFLAGS} ${IFLAGS} -c $< -o $@

${OBJ_DIR}/%.o: ${INIT_DIR}/%.c
	@mkdir -p $(dir $@)
	@${CC} ${CFLAGS} ${IFLAGS} -c $< -o $@

${OBJ_DIR}/%.o: ${SIM_DIR}/%.c
	@mkdir -p $(dir $@)
	@${CC} ${CFLAGS} ${IFLAGS} -c $< -o $@

clean:
	@echo "$(YELLOW)Removing object files!$(DEF_COLOR)"
	@$(RM) ${OBJ_DIR}/*.o
	@echo "$(RED)Object files removed! $(DEF_COLOR)"

fclean:	clean
	@echo "$(YELLOW)Removing executables!$(DEF_COLOR)"
	@${RM} ${EXEC_PATH}
	@echo "$(RED)Executables removed! $(DEF_COLOR)"
re: fclean all

# Declaración de reglas como phony para evitar conflictos
.PHONY: all clean fclean re
