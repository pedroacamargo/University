#!/usr/bin/env python

# Simple 'echo' workload in Python for Maelstrom

import logging
from ms import receiveAll, reply

logging.getLogger().setLevel(logging.DEBUG)

for msg in receiveAll():
    if msg.body.type == 'init':
        node_id = msg.body.node_id
        node_ids = msg.body.node_ids
        logging.info('node %s initialized', node_id)

        reply(msg, type='init_ok')
    elif msg.body.type == 'echo':
        logging.info('echoing %s', msg.body.echo)

        reply(msg, type='echo_ok', echo=msg.body.echo)
    else:
        logging.warning('unknown message type %s', msg.body.type)
