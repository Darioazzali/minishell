include config.mk
# LOG_FILE_PATH 	= 
# LOG_LEVEL	 	= 	0
EXPANDER				=	expander
TOKENIZER				=	tokenizer
EXPORT_BTIN				=	export
CD						=	cd
ECHO					=	echo
PWD						=	pwd
TOKEN_RECOGNITION		=	token_recognition
QUOTE_REMOVAL			=	quote_removal
ALL						=	$(EXPANDER)				\
							$(TOKENIZER)			\
							$(QUOTE_REMOVAL)		\
							$(TOKEN_RECOGNITION)	\
							$(EXPORT_BTIN)			\
							$(AST_BUILD)			\
							$(CD)					\
							$(ECHO)					\
							$(PWD)					\
							$(UNIT_TEST)

all: $(ALL)

$(EXPANDER):$(BUILD_DIR)/expander.o $(OBJS) $(CJSON_OBJ) $(UNITY_OBJ) $(LIBFT)
	make -C .. libminishell.a DEBUG=$(DEBUG)
	DEBUG=0 $(CC)  $< $(OBJS)  $(CJSON_OBJ) $(LDFLAGS)  -o $@

$(TOKENIZER):$(BUILD_DIR)/tokenizer.o $(OBJS) $(UNITY_OBJ) $(CJSON_OBJ)  $(LIBFT)
	make -C .. libminishell.a DEBUG=$(DEBUG)
	$(CC)  $< $(OBJS) $(CJSON_OBJ) $(LDFLAGS)  -o $@

$(CD):$(BUILD_DIR)/cd.o $(OBJS) $(CJSON_OBJ) $(UNITY_OBJ)  $(LIBFT)
	make -C .. libminishell.a DEBUG=$(DEBUG)
	$(CC)  $< $(OBJS) $(CJSON_OBJ) $(LDFLAGS)  -o $@

$(TOKEN_RECOGNITION):$(BUILD_DIR)/token_recognition.o $(OBJS) $(CJSON_OBJ) $(UNITY_OBJ) $(LIBFT)
	make -C .. libminishell.a DEBUG=$(DEBUG)
	$(CC)  $< $(OBJS) $(CJSON_OBJ) $(LDFLAGS)  -o $@

$(AST_BUILD):$(AST_OBJ) $(OBJS) $(CJSON_OBJ) $(UNITY_OBJ) $(LIBFT)
	make -C .. libminishell.a DEBUG=$(DEBUG)
	$(CC)  $(AST_OBJ)  $(OBJS) $(CJSON_OBJ) $(LDFLAGS)  -o $@

$(QUOTE_REMOVAL):$(BUILD_DIR)/quote_removal.o $(OBJS) $(CJSON_OBJ) $(UNITY_OBJ)  $(LIBFT) force
	make -C .. libminishell.a DEBUG=$(DEBUG)
	$(CC)  $< $(OBJS) $(CJSON_OBJ) $(LDFLAGS)  -o $@

$(EXPORT_BTIN):$(BUILD_DIR)/export.o $(OBJS) $(CJSON_OBJ) $(UNITY_OBJ) $(LIBFT) force
	make -C .. libminishell.a DEBUG=$(DEBUG)
	$(CC)  $< $(OBJS) $(CJSON_OBJ) $(LDFLAGS)  -o $@

$(PWD):$(BUILD_DIR)/pwd.o $(OBJS) $(CJSON_OBJ) $(UNITY_OBJ) $(LIBFT) force
	make -C .. libminishell.a DEBUG=$(DEBUG)
	$(CC)  $< $(OBJS) $(CJSON_OBJ) $(LDFLAGS)  -o $@

$(ECHO):$(BUILD_DIR)/echo.o $(OBJS) $(CJSON_OBJ) $(UNITY_OBJ) $(LIBFT) force
	make -C .. libminishell.a DEBUG=$(DEBUG)
	$(CC)  $< $(OBJS) $(CJSON_OBJ) $(LDFLAGS)  -o $@

$(LIBFT): force
	echo "compiling libft"
	make -C $(LIBFT_DIR)

$(BUILD_DIR)/cJSON.o: $(CJSON_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/unity.o: $(UNITY_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRCS_DIR)/ast/%.c $(AST_HEADERS) Makefile
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) \
	-I $(LIBFT_DIR) \
	-I $(INC_DIR) \
	-I $(MINISHELL_INC) \
	-I $(MINISHELL_SRC) \
	-I libs \
	-c $< -o $@

$(BUILD_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS) Makefile
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) \
	-I $(LIBFT_DIR) \
	-I $(INC_DIR) \
	-I $(MINISHELL_INC) \
	-I $(MINISHELL_SRC) \
	-I libs \
	-c $< -o $@

include unit.mk

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(ALL)

re: fclean all

.PHONY: all clean fclean re force
