#!/bin/bash

astyle  *.c  -s2 --style=allman --pad-oper --align-pointer=type --align-reference=type --suffix=none --mode=c -c -v
