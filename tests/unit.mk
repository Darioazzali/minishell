UNIT_TEST= $(EXECUTE_COMMAND)
EXECUTE_COMMAND = execute_command

$(EXECUTE_COMMAND):$(BUILD_DIR)/execute_command.o $(OBJS) $(CJSON_OBJ) $(UNITY_OBJ) $(LIBFT)
	make -C .. libminishell.a DEBUG=$(DEBUG)
	DEBUG=0 $(CC)  $< $(OBJS)  $(CJSON_OBJ) $(LDFLAGS)  -o $@
