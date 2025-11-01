#!/bin/bash
# This script sets up file integrity monitor

if [ "$(id -u)" -ne 0 ]; then
    echo "This script must be run as root."
    exit 1
fi

if [ ! -f "./file_shadow" ]; then
    echo "Creating file_shadow..."
    touch ./file_shadow
    chmod 777 ./file_shadow
    # chown root:root ./file_shadow
    echo "file_shadow created successfully."
else
    echo "file_shadow already exists. Skipping creation."
fi

gcc ./code/protect.c -o protect -lcrypto -Wno-deprecated-declarations
gcc ./code/verify.c -o verify -lcrypto -Wno-deprecated-declarations

# TODO: Add a cron job to check file integrity every hour