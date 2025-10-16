#!/bin/bash

# Start a QEMU virtual machine with specified parameters
# -m 2048: Allocate 2048 MB of RAM
# -smp 2: Use 2 CPU cores
# -hda output.qcow2: Use output.qcow2 as the hard disk image (make sure this file exists)
# To create a .qcow2 image
# -net nic: Create a network interface card
# -net user,hostfwd=tcp::2222-:22: Set up user-mode networking with port forwarding from host port 2222 to guest port 22 (SSH)
# -enable-kvm: Enable KVM for hardware acceleration
# -vga virtio: Use Virtio for better graphics performance
# -monitor stdio: Use standard input/output for QEMU monitor
qemu-system-x86_64 -m 2048 -smp 2 -hda output.qcow2 -enable-kvm -net nic -net user,hostfwd=tcp::2222-:22 -vga virtio -monitor stdio
