-module(manager).
-export([start/0, loop/1, log/1, rpc/1, list_accounts/0, create_account/2, close_account/1, login/2, logout/1, online/0]).

% ?MODULE - The name of the module. (in this case, manager)

rpc(Request) ->
    ?MODULE ! {self(), rpc, Request},

    receive
        {From, ok} -> From;
        {From, user_exists} ->
            io:format("Account already exists.~n"),
            From;
        {From, invalid} ->
            io:format("Invalid account.~n"),
            From
    end.

list_accounts() ->
    rpc({list_accounts, self()}).

create_account(Username, Password) ->
    rpc({create_account, Username, Password}).

close_account(Username) ->
    rpc({close_account, Username}).

login(Username, Password) ->
    rpc({login, Username, Password}).

logout(Username) ->
    rpc({logout, Username}).

online() ->
    rpc({online, self()}).

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
            password => "123456",
            level => 100,
            life => 100,
            title => "Master",
            online => false
        },
        carlos => #{
            password => "123456",
            level => 3,
            life => 0,
            title => "Nabo",
            online => false
        },
        moniz => #{
            password => "123456",
            level => 1,
            life => 100,
            title => "cg ninja",
            online => false
        },
        renatao => #{
            password => "123456",
            level => 1,
            life => 100,
            title => "árbitro",
            online => false
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
                    io:format("Account: ~p, Level: ~p, Life: ~p, Title: ~p, isOnline: ~p~n", [
                        Key,
                        maps:get(level, Value),
                        maps:get(life, Value),
                        maps:get(title, Value),
                        maps:get(online, Value)
                    ])    
                end,
                App
            ),
            Rpc ! {self(), ok},
            loop(App);
        {Rpc, rpc, {create_account, Username, Password}} ->
            case maps:is_key(Username, App) of
                true ->
                    Rpc ! {self(), user_exists},
                    loop(App);
                false ->
                    NewMap = maps:put(Username, #{
                        password => Password,
                        level => 1,
                        life => 100,
                        title => "newbie"
                    }, App),
                    io:format("Account created: ~p~n", [Username]),
                    Rpc ! {self(), ok},
                    loop(NewMap)    
            end;
        {Rpc, rpc, {close_account, Username}} ->
            case maps:is_key(Username, App) of
                true ->
                    NewMap = maps:remove(Username, App),
                    io:format("Account closed: ~p~n", [Username]),
                    Rpc ! {self(), ok},
                    loop(NewMap);
                false ->
                    Rpc ! {self(), invalid},
                    loop(App)
            end;
        {Rpc, rpc, {login, Username, Password}} ->
            case maps:get(Username, App) of
                Account ->
                    case maps:get(password, Account) of
                        PasswordUser -> case PasswordUser == Password of
                            true ->
                                io:format("Login successful for user: ~p~n", [Username]),
                                NewMap = maps:put(Username, #{
                                    password => Password,
                                    level => maps:get(level, Account),
                                    life => maps:get(life, Account),
                                    title => maps:get(title, Account),
                                    online => true
                                }, App),
                                Rpc ! {self(), ok},
                                loop(NewMap);
                            false ->
                                Rpc ! {self(), invalid},
                                loop(App)
                            end
                    end
            end;
        {Rpc, rpc, {logout, Username}} ->
            case maps:get(Username, App) of
                Account ->
                    NewMap = maps:put(Username, #{
                        password => maps:get(password, Account),
                        level => maps:get(level, Account),
                        life => maps:get(life, Account),
                        title => maps:get(title, Account),
                        online => false
                    }, App),
                    io:format("Logout successful for user: ~p~n", [Username]),
                    Rpc ! {self(), ok},
                    loop(NewMap)
            end;
        {Rpc, rpc, {online, _}} ->
            OnlineUsers = maps:filter(fun(_, Value) -> maps:get(online, Value) == true end, App),
            List = maps:keys(OnlineUsers),
            io:format("Online users: ~p~n", [List]),
            Rpc ! {self(), ok},
            loop(App)
        end.