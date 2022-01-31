#!/bin/sh
cd minishell
make re
valgrind ./minishell
