#!/bin/sh
cd minishell
make fclean
make bonus 
valgrind ./minishell
