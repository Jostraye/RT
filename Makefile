# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jostraye <jostraye@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/01 19:04:14 by jostraye          #+#    #+#              #
#    Updated: 2018/01/14 14:48:29 by jostraye         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

FLAGS += -Wall -Werror -Wextra -I
FRMWRK = -framework OpenGL -framework AppKit
LIBS = -lmlx -lft
LX = libmlx/
LT = libft/
LTA = libft.a
LXA = libmlx.a
ALLC = *.c
ALLO = *.o

RM = rm -f

SRCS = main.c \

all: $(LTA) $(LXA) $(NAME)

$(LXA):
	make -C $(LX)

$(LTA):
	make -C $(LT)

rtv1:
	gcc $(FLAGS) $(LX) -c $(LT)$(ALLC) $(ALLC)
	gcc $(FLAGS) $(LX) $(ALLO) -L$(LX) -L$(LT) $(LIBS) -o $(NAME) $(FRMWRK)

clean:
	$(RM) $(ALLO) $(LT)$(ALLO) $(LX)$(ALLO)

fclean: clean
	$(RM) $(NAME)

re: fclean all
