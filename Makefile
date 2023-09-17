################################################################################
#								  Utils										   #
################################################################################

NAME		= 	ircserv
CC			= 	c++
CFLAGS		=	-std=c++98

RUN_PARAM	=	

################################################################################
#								  Sources									   #
################################################################################

SRCS_EXTENSION	=	.cpp
SRCS_PATH		=	.
SRCS			=	main.cpp \
					$(addprefix server/, \
						$(addprefix commands/, \
							handler.cpp \
						) \
						$(addprefix parsing/, \
							parsing.cpp \
						) \
						$(addprefix signals/, \
							signals.cpp \
							sigInt.cpp \
						) \
						$(addprefix socket/, \
							socket.cpp \
						) \
						$(addprefix utils/, \
							utils.cpp \
						) \
						Channel.cpp \
						Client.cpp \
						Server.cpp \
					)

################################################################################
#								  Includes									   #
################################################################################

INCLUDE_DIRS		=	$(addprefix ./include/, \
							server \
							$(addprefix server/, \
								commands \
								$(addprefix commands/, \
									messages \
								) \
								parsing \
								signals \
								socket \
								utils \
							) \
						)

#               /!\ Do not touch the rest of the file /!\ 

################################################################################
#								  Objects									   #
################################################################################

OBJS_PATH		=	./build

OBJS			=	$(addprefix $(OBJS_PATH)/, ${SRCS:$(SRCS_EXTENSION)=.o})
OBJS_DEPEND		=	$(addprefix $(OBJS_PATH)/, ${SRCS:$(SRCS_EXTENSION)=.d})

################################################################################
#								  Constants									   #
################################################################################

BLUE		=	\033[1;34m
CYAN		=	\033[0;36m
GREEN		=	\033[0;32m
ORANGE  	=	\033[0;33m
NO_COLOR	=	\033[m

################################################################################
#								  Makefile									   #
################################################################################

INCLUDE_FLAGS 	=	$(addprefix -I , ${INCLUDE_DIRS})

ifeq (noflag, $(filter noflag,$(MAKECMDGOALS)))
	CFLAGS	+=	-Wall -Wextra
else
	CFLAGS	+=	-Wall -Wextra -Werror
endif
ifeq (debug, $(filter debug,$(MAKECMDGOALS)))
	CFLAGS	+=	-g3
endif
ifeq (sanadd, $(filter sanadd,$(MAKECMDGOALS)))
	CFLAGS	+=	-fsanitize=address
endif
ifeq (santhread, $(filter santhread,$(MAKECMDGOALS)))
	CFLAGS	+=	-fsanitize=thread
endif

define count_files
	TOTAL_FILES=`bash -c 'make -n | grep -- "-c.*-o" | wc -l'`; \
	TOTAL_FILES=$$((TOTAL_FILES-1)); \
	if [ $$TOTAL_FILES -ne 0 ]; then \
		echo -n $$TOTAL_FILES > .MAKEFILE_total_files; \
		echo -n "0" > .MAKEFILE_compiled_files; \
		tput civis; \
	fi;
endef

define file_compiled
	COMPILED=`bash -c 'cat .MAKEFILE_compiled_files'`; \
	COMPILED=$$((COMPILED+1)); \
	echo -n $$COMPILED > .MAKEFILE_compiled_files; \
	sleep 0.1;
endef

define draw_bar
	TOTAL_FILES=`bash -c 'cat .MAKEFILE_total_files'`; \
	COMPILED=`bash -c 'cat .MAKEFILE_compiled_files'`; \
	TOTAL_LENGTH=52; \
	if [ $$COMPILED -eq 0 ]; then \
		COMPLETED_LENGTH=0; \
	else \
		INCREMENT=$$((TOTAL_LENGTH/TOTAL_FILES)); \
		COMPLETED_LENGTH=$$((INCREMENT*COMPILED)); \
	fi; \
	PRINT=0; \
	printf "\r"; \
	while [ $$PRINT -ne $$COMPLETED_LENGTH ]; do \
		printf "\e[0;32m█\e[0m"; \
		PRINT=$$((PRINT+1)); \
	done; \
	if [ $$COMPILED -eq $$TOTAL_FILES ]; then \
		while [ $$PRINT -ne $$TOTAL_LENGTH ]; do \
			printf "\e[0;32m█\e[0m"; \
			PRINT=$$((PRINT+1)); \
		done; \
	fi; \
	while [ $$PRINT -ne $$TOTAL_LENGTH ]; do \
		printf "\e[0m▒\e[0m"; \
		PRINT=$$((PRINT+1)); \
	done; \
	if [ $$COMPILED -eq $$TOTAL_FILES ]; then \
		printf "\n"; \
		tput cvvis; \
	fi;
endef

define clean
	rm -f .MAKEFILE_total_files; \
	rm -f .MAKEFILE_compiled_files; \
	tput cvvis;
endef

################################################################################
#								  Rules										   #
################################################################################

all:	header message
		@make -s $(NAME) || $(MAKE) reset

#beautiful
header:
		@echo -n "${BLUE}"
		@echo "  _  _ ___                    _         __ _ _      "
		@echo " | || |__ \                  | |       / _(_) |     "
		@echo " | || |_ ) |  _ __ ___   __ _| | _____| |_ _| | ___ "
		@echo " |__   _/ /  | '_ \` _ \ / _\` | |/ / _ \  _| | |/ _ \\"
		@echo "    | |/ /_  | | | | | | (_| |   <  __/ | | | |  __/"
		@echo "    |_|____| |_| |_| |_|\__,_|_|\_\___|_| |_|_|\___|"
		@echo -n "${NO_COLOR}"

message:
		@make -q $(NAME) && echo "$(GREEN)Everything is already up to date ! No work for me$(NO_COLOR)" || true
		@$(call count_files)

#Compilation
$(OBJS_PATH)/%.o:	$(SRCS_PATH)/%$(SRCS_EXTENSION)
			@mkdir -p $(dir $@)
			@$(call draw_bar)
			@echo "\r$(CYAN)Compiling $(BLUE)$@ ...$(NO_COLOR)                             "
			@$(call draw_bar)
			@$(CC) $(CFLAGS) -MMD -MF $(@:.o=.d)  ${INCLUDE_FLAGS} -c $< -o $@
			@$(call file_compiled)
			@$(call draw_bar)
$(OBJS_PATH)/%.o:	%$(SRCS_EXTENSION)
			@mkdir -p $(dir $@)
			@$(call draw_bar)
			@echo "\r$(CYAN)Compiling $(BLUE)$@ ...$(NO_COLOR)                             "
			@$(call draw_bar)
			@$(CC) $(CFLAGS) -MMD -MF $(@:.o=.d)  ${INCLUDE_FLAGS} -c $< -o $@
			@$(call file_compiled)
			@$(call draw_bar)
			
#Link
-include $(OBJS_DEPEND) $(OBJ_MAIN_DEPEND)
$(NAME):	${OBJS} ${OBJ_MAIN}
		@echo "$(ORANGE)Linking $(BLUE)$@ ...$(NO_COLOR)"
		@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -o $@ ${OBJS} ${OBJ_MAIN}
		@$(call clean)
		@echo "$(GREEN)$@ created !$(NO_COLOR)"

#clean
clean:		header
		@rm -rf $(OBJS_PATH)
		@echo "$(GREEN)Removed objects !$(NO_COLOR)"

fclean:		header clean
		@rm -f $(NAME)
		@echo "$(GREEN)Removed $(NAME) !$(NO_COLOR)"

re:			header fclean all

#test
run:		header all
		@echo "$(BLUE)Executing...$(NO_COLOR)"
		@echo ""
		@./$(NAME) $(RUN_PARAM)

show:		header
		@echo "$(CYAN)Compilator: $(GREEN)$(CC)$(NO_COLOR)"
		@echo "$(CYAN)Flags: $(GREEN)$(CFLAGS)$(NO_COLOR)"
		@echo "$(CYAN)Includes: $(GREEN)$(INCLUDE_FLAGS)$(NO_COLOR)"
		@echo ""
		@echo "$(CYAN)Sources:$(NO_COLOR)"
		@echo "$(GREEN)$(MAIN) ${addprefix $(SRCS_PATH)/, $(SRCS)}$(NO_COLOR)"
		@echo ""
		@echo "$(CYAN)Libs:$(NO_COLOR)"
		@echo "$(GREEN)$(ALL_LIBS)$(NO_COLOR)"

nm:
	@nm -DA  $(NAME)

scan-build:
	@mkdir -p build/scan-build
	@scan-build --use-cc=$(CC) --use-c++=$(CC) --status-bugs -stats -internal-stats -o build/scan-build $(MAKE) all

cppcheck:
	@mkdir -p build/cppcheck
	cppcheck --cppcheck-build-dir=build/cppcheck/ --check-config --enable=all --suppress=missingIncludeSystem --xml $(SRCS) $(INCLUDE_FLAGS) 2> build/cppcheck/cppcheck.xml

cppcheck-htmlreport: cppcheck
	@cppcheck-htmlreport --file=build/cppcheck/cppcheck.xml --report-dir=build/cppcheck/cppcheck-htmlreport/ --title=IRCserv
	@open build/cppcheck/cppcheck-htmlreport/index.html

#do nothing
noflag: 	all
		@echo -n ""
debug:		all
		@echo -n ""
sanadd:		all
		@echo -n ""
santhread:	all
		@echo -n ""

reset:
		@$(call clean)
		
.PHONY:		all header clean fclean re run show nm scan-build cppcheck cppcheck-htmlreport noflag debug sanadd santhread show reset