CC				=	cc
CFLAGS			=	-Wall -Wextra -g
CFLAGS          += -I $(MINISHELL_SRC)/debug
CFLAGS          += -I $(MINISHELL_SRC)/parsing  
CFLAGS          += -I $(MINISHELL_SRC)/errors
CFLAGS          += -I $(MINISHELL_SRC)/variables
CFLAGS          += -I $(CJSON_DIR) -I $(UNITY_DIR)
LDFLAGS 		= -L $(MINISHELL_DIR) -lminishell -L $(LIBFT_DIR) -lft -lreadline
MINISHELL_DIR	=	..
DEBUG			?=	0
BUILD_DIR		=	build
SRCS_DIR		:=	srcs
SRCS_FILES		:=	test.c 
INC_DIR			=	includes
CJSON_DIR 		= libs/cjson
CJSON_SRC 		= $(CJSON_DIR)/cJSON.c
CJSON_OBJ 		= $(BUILD_DIR)/cJSON.o
UNITY_DIR       = libs/unity/src
UNITY_SRC       = $(UNITY_DIR)/unity.c
UNITY_OBJ       = $(BUILD_DIR)/unity.o
MINISHELL_INC	=	$(MINISHELL_DIR)/includes
MINISHELL_SRC	=	$(MINISHELL_DIR)/srcs
HEADERS			:=	includes/test.h 
SRCS			:=	$(addprefix $(SRCS_DIR)/,$(SRCS_FILES))
AST_BUILD				=	 ast_parse
AST_BUILD_DIR			=	 $(SRCS_DIR)/ast
AST_SRCS				:=	ast_build.c \
						 	ast_build_parse.c \
						 	ast_build_fmt.c 
AST_SRCS				:=	$(addprefix $(AST_BUILD_DIR)/,$(AST_SRCS))
AST_OBJ					=	$(patsubst $(AST_BUILD_DIR)/%.c,$(BUILD_DIR)/%.o,$(AST_SRCS))
AST_HEADERS				=	$(HEADERS) \
							$(AST_BUILD_DIR)/ast_test.h 
LIBFT_DIR				=	../libft
LIBFT					=	$(LIBFT_DIR)/libft.a
UTILS					=	$(BUILD_DIR)/test.o
OBJS            		:=	$(patsubst $(SRCS_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
