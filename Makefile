# Nom de l'exécutable
NAME = philo

# Répertoires
SRCDIR = srcs
OBJDIR = objs

# Fichiers sources et objets
SRC = $(SRCDIR)/main.c $(SRCDIR)/nbr_time.c $(SRCDIR)/alone_philo.c $(SRCDIR)/init.c $(SRCDIR)/routine.c \
	$(SRCDIR)/destroy.c $(SRCDIR)/check.c $(SRCDIR)/routine_utils.c $(SRCDIR)/monitoring.c
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Options de compilation
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -f

# Création de l'exécutable
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# Règle par défaut
all: $(NAME)

# Compilation des fichiers objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	$(RM) $(OBJ)
	$(RM) -r $(OBJDIR)

# Nettoyage complet (fichiers objets et exécutable
fclean: clean
	$(RM) $(NAME)

# Recompilation complète
re: fclean all

# Éviter les conflits avec des fichiers qui portent les mêmes noms que les cibles Makefile
.PHONY: all clean fclean re 
