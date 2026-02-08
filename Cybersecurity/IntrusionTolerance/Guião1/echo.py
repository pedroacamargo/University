#!/usr/bin/env python3

# Simple 'echo' workload in Python for Maelstrom

import logging
from ms import receiveAll, reply, broadcast

logging.getLogger().setLevel(logging.DEBUG)


nodes = set()
node_id = None

database = {
    # key: value
}


for msg in receiveAll():
    if msg.body.type == 'init':
        logging.info('initializing node %s', msg.body.node_id)
        node_id = msg.body.node_id
        nodes.update(msg.body.node_ids)
        logging.info('nodes in cluster: %s', nodes)
        reply(msg, type='init_ok')
    
    elif msg.body.type == 'read':
        key = msg.body.key
        logging.info('reading key %s with value %s', key, database.get(key, None))
        reply(msg, type='read_ok', value=database.get(key, None))

    elif msg.body.type == 'write':
        logging.info('writing key %s with value %s', msg.body.key, msg.body.value)
        database[msg.body.key] = msg.body.value
        broadcast(nodes, node_id, type='replicate', key=msg.body.key, value=msg.body.value)
        reply(msg, type='write_ok')
    
    elif msg.body.type == 'replicate':
        database[msg.body.key] = msg.body.value
        
    elif msg.body.type == 'cas':
        key = msg.body.key
        from_value = msg.body.__dict__['from']
        new_value = msg.body.to
        
        current_value = database.get(key, None)
        
        logging.info('cas on key %s: expected %s, current %s, new %s', key, from_value, current_value, new_value)
        
        if key not in database:
            reply(msg, type='error', code=20, text='key does not exist')
        elif current_value != from_value:
            reply(msg, type='error', code=22, text='value does not match expected')
        else:
            database[key] = new_value
            broadcast(nodes, node_id, type='replicate', key=key, value=new_value)
            reply(msg, type='cas_ok')
    else:
        logging.warning('unknown message type %s', msg.body.type)
