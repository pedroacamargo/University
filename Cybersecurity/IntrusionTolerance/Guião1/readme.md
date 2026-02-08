# Naive Replication

With replication implemented, we can now have a simple key-value store that replicates all updates to all other nodes. This is a simple way to achieve fault tolerance, but it does not handle network partitions or concurrent updates well.

### Increasing request rate and latency

```py
def broadcast(nodes, node_id, **body):
    for n in nodes:
        if n != node_id:
            send(node_id, n, **body)
```

```bash
./maelstrom test lin_kv --bin ../Guião1/echo.py --concurrency 10 --node-count 5 --rate 100 --latency 50
```

![Naive Replication Test Results](./HighLatency.png)

As we can see, in the image above, the latency of the requests increases significantly as the request rate increases. This is because each write request is replicated to all other nodes, which takes time. The more nodes we have, the more time it takes to replicate the updates. While the system still process a broadcast, another client can send a new request, which will be processed after the broadcast is done.

### Network partitions

If we have a network partition, some nodes will not receive the updates from other nodes, which can lead to inconsistent state across the cluster. For example, if we have a partition that isolates one node from the rest of the cluster, that node will not receive any updates from the other nodes, and it will have an outdated view of the data.

![Network Partition Test Results](./NetworkPartition.png)

For example, in the image above, n0 writes to n2, n3 and n4, but n1 is isolated and does not receive the update. When n1 tries to read the value of the key, it will return the old value, which is inconsistent with the other nodes.
