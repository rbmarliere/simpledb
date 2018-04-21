#include <eosiolib/eosio.hpp>

class simpledb : public eosio::contract
{
    public:
        simpledb(account_name self) : contract(self), messages(_self,_self) {}

        struct new_message
        {
            account_name sender;
            std::string text;
            EOSLIB_SERIALIZE( new_message, (sender)(text) );
        };

        struct message
        {
            uint64_t id = 0;
            account_name sender;
            std::string text;
            uint32_t primary_key() const { return id; }
            EOSLIB_SERIALIZE( message, (id)(sender)(text) );
        };

        void on( const new_message& m )
        {
            require_auth(m.sender);

            auto iter = messages.emplace( _self, [&](auto& message) {
                message.id = messages.available_primary_key();
                message.sender = m.sender;
                message.text = m.text;
            } );
        }

        bool apply( account_name contract, action_name act )
        {
            if( contract != _self ) {
               return false;
            }

            switch( act ) {
                case N(add_message):
                    on( eosio::unpack_action_data<new_message>() );
                    return true;
            }

            return false;
        }

    private:
        eosio::multi_index<N(message), message> messages;
};

extern "C"
{
    void apply( uint64_t receiver, uint64_t code, uint64_t action )
    {
        simpledb(receiver).apply( code, action );
    }
}

