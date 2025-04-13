-module(changecase_client).
-export([changecase/3]).

changecase(Server, Str, Command) ->
    Server ! {self(), {Str, Command}},
    receive 
        {Server, ResultString} ->
            io:format("Result from server: ~s~n", [ResultString])
    end.