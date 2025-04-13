-module(priorityqueue).
-export([create/0,enqueue/3,dequeue/1,dequeue_items/2]).

-type priority() :: integer().
-type priorityqueue() :: #{
    priority() => term()
}.

-spec create() -> priorityqueue().
create() ->
    #{}.

-spec enqueue(priorityqueue(), priority(), term()) -> priorityqueue().
enqueue(PQ, Priority, Item) ->
    case maps:find(Priority, PQ) of
        {ok, Items} ->
            maps:put(Priority, [Item | Items], PQ);
        error ->
            maps:put(Priority, [Item], PQ)
    end,
    PQ.

-spec dequeue(priorityqueue()) -> empty | {priorityqueue(), term()}.
dequeue(PQ) ->
    case maps:keys(PQ) of
        [] ->
            empty;
        Priorities ->
            MaxPriority = lists:max(Priorities),
            {Items, NewPQ} = dequeue_items(PQ, MaxPriority),
            case Items of
                [] ->
                    empty;
                [H | _] ->
                    {NewPQ, H}
            end
    end.

-spec dequeue_items(priorityqueue(), priority()) -> {list(), priorityqueue()}.
dequeue_items(PQ, Priority) ->
    case maps:find(Priority, PQ) of
        {ok, Items} ->
            NewPQ = maps:remove(Priority, PQ),
            {Items, NewPQ};
        error ->
            {[], PQ}
    end.






%
% -module(priorityqueue).
% -export([create/0, enqueue/3, dequeue/1]).

% -type priority() :: integer().
% -type item() :: term().
% -type pri_queue() :: #{priority() => queue()}.
% -type queue() :: {list(), list()}.

% -spec create() -> pri_queue().
% create() ->
%     #{}.

% -spec enqueue(pri_queue(), item(), priority()) -> pri_queue().
% enqueue(PQ, Item, Priority) ->
%     Queue = maps:get(Priority, PQ, {[], []}),
%     NewQueue = enqueue_queue(Queue, Item),
%     maps:put(Priority, NewQueue, PQ).

% -spec dequeue(pri_queue()) -> empty | {pri_queue(), item()}.
% dequeue(PQ) ->
%     case maps:keys(PQ) of
%         [] -> empty;
%         Keys ->
%             Sorted = lists:sort(fun(A, B) -> A > B end, Keys),
%             dequeue_from_priorities(Sorted, PQ)
%     end.

% %%% ========================
% %%% Internal helper functions
% %%% ========================

% -spec enqueue_queue(queue(), item()) -> queue().
% enqueue_queue({Front, Rear}, Item) ->
%     {Front, [Item | Rear]}.

% -spec dequeue_from_priorities([priority()], pri_queue()) -> empty | {pri_queue(), item()}.
% dequeue_from_priorities([], _) ->
%     empty;
% dequeue_from_priorities([P | Ps], PQ) ->
%     Queue = maps:get(P, PQ),
%     case dequeue_queue(Queue) of
%         empty ->
%             dequeue_from_priorities(Ps, PQ);  % skip empty queue
%         {NewQueue, Item} ->
%             NewPQ = case NewQueue of
%                         {[], []} -> maps:remove(P, PQ);  % remove empty queue
%                         _ -> maps:put(P, NewQueue, PQ)
%                     end,
%             {NewPQ, Item}
%     end.

% -spec dequeue_queue(queue()) -> empty | {queue(), item()}.
% dequeue_queue({[], []}) ->
%     empty;
% dequeue_queue({[], Rear}) ->
%     dequeue_queue({lists:reverse(Rear), []});
% dequeue_queue({[H | T], Rear}) ->
%     {{T, Rear}, H}.
