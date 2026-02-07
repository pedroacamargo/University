#!/usr/bin/env python3

# Simple 'echo' workload in Python for Maelstrom

import logging
from ms import receiveAll, reply

logging.getLogger().setLevel(logging.DEBUG)


database = {
    # key: value
}


for msg in receiveAll():
    if msg.body.type == 'init':
        logging.info('initializing node %s', msg.body.node_id)
        reply(msg, type='init_ok')
    
    if msg.body.type == 'read':
        key = msg.body.key
        logging.info('reading key %s with value %s', key, database.get(key, None))
        
        reply(msg, type='read_ok', value=database.get(key, None))

    elif msg.body.type == 'write':
        logging.info('writing key %s with value %s', msg.body.key, msg.body.value)
        database[msg.body.key] = msg.body.value

        reply(msg, type='write_ok')
        
        
    elif msg.body.type == 'cas':
        key = msg.body.key
        expected = msg.body.expected
        new_value = msg.body.value
        
        current_value = database.get(key, None)
        logging.info('cas on key %s: expected %s, current %s, new %s', key, expected, current_value, new_value)
        
        if current_value == expected:
            database[key] = new_value
            reply(msg, type='cas_ok', succeeded=True)
        else:
            reply(msg, type='cas_ok', succeeded=False)
    else:
        logging.warning('unknown message type %s', msg.body.type)
