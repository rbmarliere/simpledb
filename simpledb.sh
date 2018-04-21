#!/bin/sh

SIMPLEDB_DIR=~/git/simpledb

simpledb_init()
{
    eos_init_contract simpledb || return 1
    eosc push action simpledb addmessage '{"sender":"zaratustra","text":"hello world"}' -p zaratustra@active
    eosc get table simpledb simpledb messages
}

