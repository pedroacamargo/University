-module(myqueue).
-export([create/0, enqueue/2, dequeue/1]).

%{Front, Rear}:
    %Front holds the front of the queue (for dequeue)
    %Rear holds elements being enqueued (in reverse order)
-type myqueue() :: {list(), list()}.

% Spec is a type specification for the create function
-spec create() -> myqueue().
create() ->
    {[], []}.

% Will take the term and enqueue it to the queue (Rear)
-spec enqueue(myqueue(), term()) -> myqueue().
enqueue({Front, Rear}, Item) ->
    {Front, [Item | Rear]}.


-spec dequeue(myqueue()) -> empty | {myqueue(), term()}.
dequeue({[], []}) ->
    empty;
dequeue({[], Rear}) ->
    dequeue({lists:reverse(Rear), []});
dequeue({[H | T], Rear}) ->
    {{T, Rear}, H}.