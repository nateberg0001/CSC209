#!/usr/bin/env bash
./echo_arg CSC209 -o echo_out
./echo_stdin < echo_stdin.c
./count 210 | wc -m 
ls -S | ./echo_stdin 

