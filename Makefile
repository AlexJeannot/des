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
BASE_DIR 	= base/
DES_DIR		= des/
BASE64_DIR 	= base64/


BASE_DOBJS		= ./comp/base/
DES_DOBJS	= ./comp/des/
BASE64_DOBJS		= ./comp/base64/


# SOURCES
BASE_SRCS 		= 	args.c		\
					binary.c	\
					control.c	\
					error.c		\
					file.c		\
					main.c

DES_SRCS 		= 	const.c		\
					des.c		\
					key.c		\
					operation.c	\
					round.c

BASE64_SRCS 	=	base64.c	\
					decode.c	\
					encode.c	\
					msg.c


# OBJS
BASE_OBJS 		= $(BASE_SRCS:%.c=$(BASE_DOBJS)%.o)
DES_OBJS 	= $(DES_SRCS:%.c=$(DES_DOBJS)%.o)
BASE64_OBJS 		= $(BASE64_SRCS:%.c=$(BASE64_DOBJS)%.o)

#HEADER FILE
HEADER	=	./incs/des.h ./incs/base64.h ./incs/base.h

all: $(FT_DES)

# COMPILATION
$(FT_DES):	$(BASE_OBJS) $(DES_OBJS) $(BASE64_OBJS)
	$(CC) $(FLAGS) $(BASE_OBJS) $(DES_OBJS) $(BASE64_OBJS) -o $(FT_DES)
	echo -e "$(GREEN)FT_DES DONE ✔$(RESET)"



$(BASE_OBJS): 	| $(BASE_DOBJS)
$(DES_OBJS): | $(DES_DOBJS)
$(BASE64_OBJS): 	| $(BASE64_DOBJS)



$(BASE_DOBJS)%.o:	$(DSRCS)$(BASE_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(DES_DOBJS)%.o:	$(DSRCS)$(DES_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(BASE64_DOBJS)%.o:	$(DSRCS)$(BASE64_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@



# OBJECT FILE DIRECTORY CREATION
$(BASE_DOBJS):
	mkdir -p $(BASE_DOBJS)

$(DES_DOBJS):
	mkdir -p $(DES_DOBJS)

$(BASE64_DOBJS):
	mkdir -p $(BASE64_DOBJS)

# CLEAR
clean:
	$(RM) ./comp

fclean: clean
	$(RM) $(FT_DES)

re: fclean all

.PHONY: all clean fclean re
.SILENT: all $(FT_DES)