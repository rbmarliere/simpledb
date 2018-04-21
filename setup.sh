#!/bin/sh

simpledb_init()
{
    eos_unlock_wallet
    eos_init_accounts
    eoscpp -o simpledb.wast simpledb.cpp || return 1
    eosc set contract simpledb . simpledb.wast simpledb.abi -p simpledb@active
    eosc push action simpledb add.message '{"sender":"zaratustra","text":"hello world"}' -p zaratustra@active
}

