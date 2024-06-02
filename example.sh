#!/bin/bash

FWALL_ELF=./build/fwall
FWALL_RULES=./samples/example.fwall
INPUT_FILE=./samples/example.input

if [ ! -f $FWALL_ELF ]; then
	echo "$FWALL_ELF is not exist"
	exit 1
fi

if [ ! -f $FWALL_RULES ]; then
	echo "$FWALL_RULES is not exist"
	exit 1
fi

if [ ! -f $INPUT_FILE ]; then
	echo "$INPUT_FILE is not exist"
	exit 1
fi

echo -e "---------------Firewall rules---------------\n"
cat $FWALL_RULES
echo -e "\n---------------FWALL OUPUT---------------\n"

$FWALL_ELF -f $FWALL_RULES -i $INPUT_FILE
