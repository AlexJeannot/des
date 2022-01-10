# VARIABLES
GREEN 		= \033[38;5;40m
RESET 		= \033[0m
FT_DES 		= ft_des

# COMPILATION
CC 		= gcc
FLAGS 	= -Wall -Wextra -Werror
RM 		= rm -rf


# DIRECTORIES
DSRCS		= ./srcs/

DOBJS		= ./comp/


# SOURCES
SRCS 		=	des.c key.c const.c round.c binary.c operation.c control.c file.c args.c error.c


# OBJS
OBJS 		= $(SRCS:%.c=$(DOBJS)%.o)


#HEADER FILE
HEADER	=	./incs/des.h


all: $(FT_DES)

# COMPILATION
$(FT_DES):	$(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(FT_DES)
	echo -e "$(GREEN)FT_DES DONE ✔$(RESET)"

$(OBJS): 	| $(DOBJS)

$(DOBJS)%.o:	$(DSRCS)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@


# OBJECT FILE DIRECTORY CREATION
$(DOBJS):
	mkdir -p $(DOBJS)

# CLEAR
clean:
	$(RM) ./comp

fclean: clean
	$(RM) $(FT_DES)

re: fclean all

.PHONY: all clean fclean re
.SILENT: all $(FT_DES)