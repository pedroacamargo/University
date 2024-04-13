
#define SERVER "fifo_server"
#define CLIENT "fifo_client"

typedef struct msg{
    int needle;
    int pid;
    int occurrences;
} Msg;