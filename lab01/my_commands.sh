#!/usr/bin/env bash
./echo_arg.c CSC209 -o echo_out
./echo_stdin < echo_stdin.c
wc -m ./count.c 209
ls -S | head n-1 | ./echo_stdin.c 

