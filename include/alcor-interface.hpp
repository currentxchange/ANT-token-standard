#pragma once

// Originally Published: https://github.com/stableex/sx.alcor/blob/main/alcor.hpp

#include <eosio/asset.hpp>
#include <eosio/singleton.hpp>
#include <math.h>


namespace alcor {

    using namespace std;
    using namespace eosio;

    // reference
    const name id = "alcor"_n;
    const name code = "eostokensdex"_n;
    const name wax_code = "alcordexmain"_n;
    const string description = "Alcor Converter";

    const static uint8_t MAX_ORDERS = 20;        // place MAX_ORDERS orders at a time only - to fit in one transaction


    struct [[eosio::table]] markets_row {
        uint64_t        id;
        extended_symbol base_token;
        extended_symbol quote_token;
        asset           min_buy;
        asset           min_sell;
        bool            frozen;
        uint8_t          fee;

        uint64_t primary_key() const { return id; }
    };
    typedef eosio::multi_index<"markets"_n, markets_row> markets_table;

    struct [[eosio::table]] order_row {
        uint64_t        id;
        name            account;
        asset           bid;
        asset           ask;
        uint128_t       unit_price;
        uint32_t        timestamp;

        uint64_t primary_key() const { return id; }
        uint128_t get_price() const { return unit_price; }
    };

    typedef eosio::multi_index<"buyorder"_n, order_row,
        indexed_by< "byprice"_n, const_mem_fun<order_row, uint128_t, &order_row::get_price> >
    > buyorder_table;

    typedef eosio::multi_index<"sellorder"_n, order_row,
        indexed_by< "byprice"_n, const_mem_fun<order_row, uint128_t, &order_row::get_price> >
    > sellorder_table;

    static uint8_t get_fee()
    {
        return 0;
    }

    static pair<asset, string> get_amount_out(uint64_t pair_id, asset in, symbol sym_out) {

        asset out{0, sym_out};
        markets_table markets( code, code.value );
        auto row = markets.get(pair_id, "sx.alcor: no such pair");
        double fee_adj = static_cast<double>((10000 - get_fee())) / 10000;
        double price_adj = static_cast<double>(pow(10, sym_out.precision()))/pow(10, in.symbol.precision());
        int orders = MAX_ORDERS;
        string memo = out.to_string() + "@";
        // print("\nin: ", in, " base: ", row.base_token.get_symbol(), "memo: ", memo);

        if(row.base_token.get_symbol() == in.symbol) {

            memo += row.quote_token.get_contract().to_string();
            check(row.quote_token.get_symbol() == sym_out, "sx.alcor: wrong pair_id");
            sellorder_table ordertable( code, pair_id );
            auto index = ordertable.get_index<"byprice"_n>();

            for(auto rowit = index.begin(); rowit!=index.end() && in.amount>0 && orders--; ++rowit){
                if(in.amount - rowit->ask.amount >= 0) out.amount += rowit->bid.amount * fee_adj;
                else out.amount += in.amount * rowit->bid.amount / rowit->ask.amount * fee_adj;
                in -= rowit->ask;
                // eosio::print("\n", rowit->id, " bid: ", rowit->bid, " ask: ", rowit->ask, " price: ", rowit->unit_price, " in: ", in, " out: ", out);
            }
        }
        else {

            memo += row.base_token.get_contract().to_string();
            check(row.base_token.get_symbol() == sym_out && row.quote_token.get_symbol() == in.symbol, "sx.alcor: wrong pair_id");
            buyorder_table ordertable( code, pair_id );
            auto index = ordertable.get_index<"byprice"_n>();

            for(auto rowit = index.begin(); rowit!=index.end() && in.amount>0 && orders--; ++rowit){
                if(in.amount - rowit->ask.amount >= 0) out.amount += rowit->bid.amount * fee_adj;
                else out.amount += in.amount * rowit->bid.amount / rowit->ask.amount * fee_adj;
                in -= rowit->ask;
                //eosio::print("\n", rowit->id, " bid: ", rowit->bid, " ask: ", rowit->ask, " price: ", rowit->unit_price, " in: ", in, " out: ", out);
            }
        }
        if(in.amount > 0) return { asset{0, sym_out}, "" };   //if there are not enough orders out fulfill our order
        return { out, memo };
    };
};