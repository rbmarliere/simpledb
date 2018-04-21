#include <eosiolib/eosio.hpp>

class simpledb : public eosio::contract
{
    public:
        simpledb(account_name self) : contract(self), messages(_self,_self) {}

        // @abi action
        void addmessage( account_name sender, std::string text )
        {
            require_auth(sender);

            auto iter = messages.emplace( _self, [&](auto& message) {
                message.id = messages.available_primary_key();
                message.sender = sender;
                message.text = text;
            } );
        }

    private:
        // @abi table
        struct messages
        {
            uint64_t id = 0;
            account_name sender;
            std::string text;
            uint32_t primary_key() const { return id; }
            EOSLIB_SERIALIZE( messages, (id)(sender)(text) );
        };
        eosio::multi_index<N(messages), messages> messages;
};

EOSIO_ABI( simpledb, (addmessage) );

