-module(manager).
-export([start/0, loop/1, log/1, rpc/1, list_accounts/0]).

% ?MODULE - The name of the module. (in this case, manager)

rpc(Request) ->
    ?MODULE ! {self(), rpc, Request},

    receive
        {From, ok} -> From
    end.

list_accounts() ->
    rpc({list_accounts, self()}).

log(Msg) ->
    Pid = whereis(?MODULE),
    Pid ! {self(), log, Msg},
    receive
        {_, ok} ->
            ok
    end.

start() ->
    App = #{
        pedro => #{
            level => 100,
            life => 100,
            title => "Master"
        },
        carlos => #{
            level => 3,
            life => 0,
            title => "Nabo"
        },
        moniz => #{
            level => 1,
            life => 100,
            title => "cg ninja"
        },
        renatao => #{
            level => 1,
            life => 100,
            title => "árbitro"
        }
    },

    Pid = spawn(fun() -> loop(App) end),
    register(?MODULE, Pid).

loop(App) ->
    receive
        {From, log, Message} ->
            io:format("LOG: ~p~n", [Message]),
            From ! {self(), ok},
            loop(App);
        {Rpc, rpc, {list_accounts, _}} ->
            maps:map(
                fun(Key, Value) -> 
                    io:format("Account: ~p, Level: ~p, Life: ~p, Title: ~p~n", [
                        Key,
                        maps:get(level, Value),
                        maps:get(life, Value),
                        maps:get(title, Value)
                    ])    
                end,
                App
            ),
            Rpc ! {self(), ok},
            loop(App)
    end.