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
MD5_DIR 	= md5/
SHA256_DIR 	= sha256/


BASE_DOBJS		= ./comp/base/
DES_DOBJS	= ./comp/des/
BASE64_DOBJS		= ./comp/base64/
MD5_DOBJS	= ./comp/md5/
sha256_DOBJS		= ./comp/sha256/

# SOURCES
BASE_SRCS 		= 	args.c		\
					binary.c	\
					control.c	\
					data.c		\
					display.c	\
					error.c		\
					file.c		\
					hash.c		\
					main.c		\
					option.c	\
					padding.c	\
					swap.c

DES_SRCS 		= 	const.c		\
					des.c		\
					key.c		\
					operation.c	\
					round.c

BASE64_SRCS 	=	base64.c	\
					decode.c	\
					encode.c

MD5_SRCS 	=		auxiliary_functions.c	\
					const.c	\
					digest.c	\
					md5.c

SHA256_SRCS 	=		auxiliary_functions.c	\
					const.c	\
					digest.c	\
					sha256.c

# OBJS
BASE_OBJS 		= $(BASE_SRCS:%.c=$(BASE_DOBJS)%.o)
DES_OBJS 	= $(DES_SRCS:%.c=$(DES_DOBJS)%.o)
BASE64_OBJS 		= $(BASE64_SRCS:%.c=$(BASE64_DOBJS)%.o)
MD5_OBJS 		= $(MD5_SRCS:%.c=$(MD5_DOBJS)%.o)
SHA256_OBJS 		= $(SHA256_SRCS:%.c=$(SHA256_DOBJS)%.o)

#HEADER FILE
HEADER	=	./incs/des.h ./incs/base64.h ./incs/base.h ./incs/md5.h ./incs/sha256.h 

all: $(FT_DES)

# COMPILATION
# $(FT_DES):	$(BASE_OBJS) $(DES_OBJS) $(BASE64_OBJS) $(MD5_OBJS) $(SHA256_OBJS)
# 	$(CC) $(FLAGS) $(BASE_OBJS) $(DES_OBJS) $(BASE64_OBJS) $(MD5_OBJS) $(SHA256_OBJS) -o $(FT_DES)
# 	echo -e "$(GREEN)FT_DES DONE ✔$(RESET)"

$(FT_DES):	$(BASE_OBJS) $(DES_OBJS) $(BASE64_OBJS) $(MD5_OBJS)
	$(CC) $(FLAGS) $(BASE_OBJS) $(DES_OBJS) $(BASE64_OBJS) $(MD5_OBJS) -o $(FT_DES)
	echo -e "$(GREEN)FT_DES DONE ✔$(RESET)"

$(BASE_OBJS): 	| $(BASE_DOBJS)
$(DES_OBJS): | $(DES_DOBJS)
$(BASE64_OBJS): 	| $(BASE64_DOBJS)
$(MD5_OBJS): | $(MD5_DOBJS)
$(SHA256_OBJS): 	| $(SHA256_DOBJS)


$(BASE_DOBJS)%.o:	$(DSRCS)$(BASE_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(DES_DOBJS)%.o:	$(DSRCS)$(DES_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(BASE64_DOBJS)%.o:	$(DSRCS)$(BASE64_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(MD5_DOBJS)%.o:	$(DSRCS)$(MD5_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(SHA256_DOBJS)%.o:	$(DSRCS)$(SHA256_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@


# OBJECT FILE DIRECTORY CREATION
$(BASE_DOBJS):
	mkdir -p $(BASE_DOBJS)

$(DES_DOBJS):
	mkdir -p $(DES_DOBJS)

$(BASE64_DOBJS):
	mkdir -p $(BASE64_DOBJS)

$(MD5_DOBJS):
	mkdir -p $(MD5_DOBJS)

$(SHA256_DOBJS):
	mkdir -p $(SHA256_DOBJS)


# CLEAR
clean:
	$(RM) ./comp

fclean: clean
	$(RM) $(FT_DES)

re: fclean all

.PHONY: all clean fclean re
.SILENT: all $(FT_DES)