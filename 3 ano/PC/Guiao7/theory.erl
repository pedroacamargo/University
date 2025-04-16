-module(theory).
-export([create/0, send_message/2, receive_message/0, loop/0, sleep/1, flush/0]).

% Processes do not share memory. All communication is done through message passing.

% To create a process in Erlang, we use the spawn function.

create() ->
    % Spawn a new process that runs the function 'loop/0'
    spawn(theory, loop, []).

loop() ->
    receive
        {From, Message} ->
            io:format("Received in loop: ~p from ~p~n", [Message, From]),
            From ! {self(), ack},
            loop()
    end.

% A process finishes when the specified function returns.
% The process will terminate and the memory will be freed.
% The process will also terminate if it receives an exit signal.

% Each process has a mailbox.
% -> The mailbox is a queue of messages that the process receives.
% -> The mailbox is a FIFO queue. (First In First Out)
% To send a message to a process, we use the '!' operator.

% Pid ! Message
% Pid -> The process identifier of the process we want to send the message to.
% Message -> The message we want to send to the process.

% To remove a message from the mailbox, we use the 'receive' construct.
% The 'receive' construct will block the process until a message is received.
% The mechanism use Pattern Matching to match the message with the pattern.

% We can send your PID in the message.
send_message(Pid, Message) ->
    Pid ! {self(), Message}.

receive_message() ->
    receive
        {From, Message} ->
            io:format("Received message: ~p from: ~p~n", [Message, From]),
            From ! {self(), ok}

        % If we don't receive a message in 5 seconds, we will print a message.
        % The after clause will be executed if no message is received in the specified time.
        after 5000 ->
            io:format("No message received in 5 seconds~n")
    end.


% The sleep function will block the process for the specified time.
sleep(Time) ->
    receive
        after Time ->
            true
    end.

% The flush function will remove all messages from the mailbox.
flush() ->
    receive
        _ ->
            flush()
        after 0 ->
            io:format("Mailbox empty~n")
    end.



% register(Name, Pid) -> Register the process with the given name.
% unregister(Name) -> Unregister the process with the given name.
% whereis(Name) -> Get the PID of the process with the given name.
% registered() -> Get the list of all registered processes.