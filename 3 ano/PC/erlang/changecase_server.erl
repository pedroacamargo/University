-module(changecase_server).
-export([start/0, loop/0]).

start() ->
    % this will create a new process (module, function, [args])
    spawn(changecase_server, loop, []).

loop() ->
    % pattern matching
    % Check different kind of messages that receives from processes
    receive
        {Client, {Str, uppercase}} -> 
            Client ! {self(), string:to_upper(Str)};
        {Client, {Str, lowercase}} ->
            Client ! {self(), string:to_lower(Str)}
    end,
    loop().
    % loop() is called recursively to keep the process alive (infinite loop)