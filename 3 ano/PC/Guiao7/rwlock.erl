-module(rwlock).
-export([create/0, acquire/2, release/1]).

%% Tipos de mensagens:
%% {acquire, From, read}
%% {acquire, From, write}
%% {release, From}

-record(state, {
    readers = [],          % Lista de PIDs lendo
    writer = undefined,    % PID do escritor atual
    queue = []             % Fila: [{PID, read | write}]
}).

%%%% API %%%%

create() ->
    spawn(fun() -> loop(#state{}) end).

acquire(LockPid, Mode) when Mode == read; Mode == write ->
    LockPid ! {acquire, self(), Mode},
    receive
        granted -> ok
    end.

release(LockPid) ->
    LockPid ! {release, self()},
    ok.

%%%% Loop principal do servidor de lock %%%%

loop(State = #state{readers=Readers, writer=Writer, queue=Queue}) ->
    receive
        %% RELEASE
        {release, From} ->
            NewState = case {Writer, lists:member(From, Readers)} of
                {From, false} ->  % Releasing writer
                    process_queue(State#state{writer = undefined});
                {_, true} ->      % Releasing reader
                    NewReaders = lists:delete(From, Readers),
                    process_queue(State#state{readers = NewReaders});
                _ ->
                    State  % Unknown or invalid release
            end,
            loop(NewState);

        %% ACQUIRE - READER
        {acquire, From, read} ->
            case can_grant_read(State) of
                true ->
                    From ! granted,
                    NewState = State#state{readers = [From | Readers]},
                    loop(NewState);
                false ->
                    loop(State#state{queue = Queue ++ [{From, read}]})
            end;

        %% ACQUIRE - WRITER
        {acquire, From, write} ->
            case can_grant_write(State) of
                true ->
                    From ! granted,
                    NewState = State#state{writer = From},
                    loop(NewState);
                false ->
                    loop(State#state{queue = Queue ++ [{From, write}]})
            end
    end.

%%%% Helpers %%%%

can_grant_read(#state{writer=undefined, queue=[]}) ->
    true;
can_grant_read(#state{writer=undefined, queue=Queue}) ->
    %% Só permite se não houver escritor na fila
    not lists:any(fun({_, Mode}) -> Mode == write end, Queue);
can_grant_read(_) ->
    false.

can_grant_write(#state{writer=undefined, readers=[]}) ->
    true;
can_grant_write(_) ->
    false.

process_queue(State = #state{queue=Queue}) ->
    process_queue(Queue, State#state{queue=[]}).

process_queue([], State) ->
    State;
process_queue([{Pid, read} | Rest], State) ->
    case can_grant_read(State) of
        true ->
            Pid ! granted,
            process_queue(Rest, State#state{readers = [Pid | State#state.readers]});
        false ->
            State#state{queue = State#state.queue ++ [{Pid, read}] ++ Rest}
    end;
process_queue([{Pid, write} | Rest], State) ->
    case can_grant_write(State) of
        true ->
            Pid ! granted,
            process_queue(Rest, State#state{writer = Pid});
        false ->
            State#state{queue = State#state.queue ++ [{Pid, write}] ++ Rest}
    end.
