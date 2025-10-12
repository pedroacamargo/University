#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE_ETHERNET 14

typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;

/* IP header */
struct sniff_ip
{
    u_char ip_vhl;                 /* version << 4 | header length >> 2 */
    u_char ip_tos;                 /* type of service */
    u_short ip_len;                /* total length */
    u_short ip_id;                 /* identification */
    u_short ip_off;                /* fragment offset field */
#define IP_RF 0x8000               /* reserved fragment flag */
#define IP_DF 0x4000               /* don't fragment flag */
#define IP_MF 0x2000               /* more fragments flag */
#define IP_OFFMASK 0x1fff          /* mask for fragmenting bits */
    u_char ip_ttl;                 /* time to live */
    u_char ip_p;                   /* protocol */
    u_short ip_sum;                /* checksum */
    struct in_addr ip_src, ip_dst; /* source and dest address */
};
#define IP_HL(ip) (((ip)->ip_vhl) & 0x0f)
#define IP_V(ip) (((ip)->ip_vhl) >> 4)

/* TCP header */
typedef u_int tcp_seq;

struct sniff_tcp
{
    u_short th_sport; /* source port */
    u_short th_dport; /* destination port */
    tcp_seq th_seq;   /* sequence number */
    tcp_seq th_ack;   /* acknowledgement number */
    u_char th_offx2;  /* data offset, rsvd */
#define TH_OFF(th) (((th)->th_offx2 & 0xf0) >> 4)
    u_char th_flags;
#define TH_FIN 0x01
#define TH_SYN 0x02
#define TH_RST 0x04
#define TH_PUSH 0x08
#define TH_ACK 0x10
#define TH_URG 0x20
#define TH_ECE 0x40
#define TH_CWR 0x80
#define TH_FLAGS (TH_FIN | TH_SYN | TH_RST | TH_ACK | TH_URG | TH_ECE | TH_CWR)
    u_short th_win; /* window */
    u_short th_sum; /* checksum */
    u_short th_urp; /* urgent pointer */
};

const struct sniff_ip *ip;
const struct sniff_tcp *tcp;
const char *payload;
u_int size_ip;
u_int size_tcp;
u_int size_payload;

/*
 * print data in rows of 16 bytes: offset   hex   ascii
 *
 * 00000   47 45 54 20 2f 20 48 54  54 50 2f 31 2e 31 0d 0a   GET / HTTP/1.1..
 */
// void print_hex_ascii_line(const u_char *payload, int len, int offset)
// {

//     int i;
//     int gap;
//     const u_char *ch;

//     /* offset */
//     printf("%05d   ", offset);

//     /* hex */
//     ch = payload;
//     for (i = 0; i < len; i++)
//     {
//         printf("%02x ", *ch);
//         ch++;
//         /* print extra space after 8th byte for visual aid */
//         if (i == 7)
//             printf(" ");
//     }
//     /* print space to handle line less than 8 bytes */
//     if (len < 8)
//         printf(" ");

//     /* fill hex gap with spaces if not full line */
//     if (len < 16)
//     {
//         gap = 16 - len;
//         for (i = 0; i < gap; i++)
//         {
//             printf("   ");
//         }
//     }
//     printf("   ");

//     /* ascii (if printable) */
//     ch = payload;
//     for (i = 0; i < len; i++)
//     {
//         printf("%c", *ch);
//         // if (isprint(*ch))
//         // else
//         //     printf(".");
//         ch++;
//     }

//     printf("\n");

//     return;
// }

/*
 * print packet payload data (avoid printing binary data)
 */
// void print_payload(const u_char *payload, int len)
// {

//     int len_rem = len;
//     int line_width = 16; /* number of bytes per line */
//     int line_len;
//     int offset = 0; /* zero-based offset counter */
//     const u_char *ch = payload;

//     printf("Len: %d", len);
//     if (len <= 0)
//         return;

//     /* data fits on one line */
//     if (len <= line_width)
//     {
//         print_hex_ascii_line(ch, len, offset);
//         return;
//     }

//     /* data spans multiple lines */
//     for (;;)
//     {
//         /* compute current line length */
//         line_len = line_width % len_rem;
//         /* print line */
//         print_hex_ascii_line(ch, line_len, offset);
//         /* compute total remaining */
//         len_rem = len_rem - line_len;
//         /* shift pointer to remaining bytes to print */
//         ch = ch + line_len;
//         /* add offset */
//         offset = offset + line_width;
//         /* check if we have line width chars or less */
//         if (len_rem <= line_width)
//         {
//             /* print last line and get out */
//             print_hex_ascii_line(ch, len_rem, offset);
//             break;
//         }
//     }

//     return;
// }

void got_packet(__u_char *args, const struct pcap_pkthdr *header, const __u_char *packet)
{
    ip = (struct sniff_ip *)(packet + SIZE_ETHERNET);
    size_ip = IP_HL(ip) * 4;
    if (size_ip < 20)
    {
        printf("   * Invalid IP header length: %u bytes\n", size_ip);
        return;
    }

    printf("Got a packet from %s ", inet_ntoa(ip->ip_src));
    printf("-> %s\n", inet_ntoa(ip->ip_dst));

    /* determine protocol */
    switch (ip->ip_p)
    {
    case IPPROTO_TCP:
        printf("Protocol: TCP\n");
        break;
    case IPPROTO_UDP:
        printf("Protocol: UDP\n");
        return;
    case IPPROTO_ICMP:
        printf("Protocol: ICMP\n");
        return;
    case IPPROTO_IP:
        printf("Protocol: IP\n");
        return;
    default:
        printf("Protocol: unknown\n");
        return;
    }

    tcp = (struct sniff_tcp *)(packet + SIZE_ETHERNET + size_ip);
    size_tcp = TH_OFF(tcp) * 4;
    if (size_tcp < 20)
    {
        printf("   * Invalid TCP header length: %u bytes\n", size_tcp);
        return;
    }

    printf("Src port: %d\n", ntohs(tcp->th_sport));
    printf("Dst port: %d\n", ntohs(tcp->th_dport));

    /* define/compute tcp payload (segment) offset */
    payload = (u_char *)(packet + SIZE_ETHERNET + size_ip + size_tcp);
    size_payload = ntohs(ip->ip_len) - (size_ip + size_tcp);

    printf("   Payload (%d bytes):\n", size_payload);
    printf("%s\n", payload);

    /*
     * Print payload data; it might be binary, so don't just
     * treat it as a string.
     */
    // if (size_payload > 0)
    // {
    //     print_payload(payload, size_payload);
    // }

    printf("####################################################\n");
}

int main()
{
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];

    // Filter stuff
    struct bpf_program fp; // Compiled filter expression
    // char filter_exp[] = "icmp and host 10.9.0.5 and host 10.9.0.6"; // Filter expression
    char filter_exp[] = "tcp dst portrange 10-100"; // Filter expression
    bpf_u_int32 net;

    char *device = "br-74e56b1dea73";

    handle = pcap_open_live(device, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL)
    {
        fprintf(stderr, "Couldn't open device: %s: %s\n", device, errbuf);
        return -1;
    }

    // We can use pcap_datalink to check the type of link-layer headers the devices provides
    // But in this case, is not needed for us.

    if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1)
    {
        fprintf(stderr, "Couldn't parse filter: %s: %s\n", filter_exp, pcap_geterr(handle));
        return -1;
    }

    if (pcap_setfilter(handle, &fp) != 0)
    {
        fprintf(stderr, "Couldn't install filter: %s: %s\n", filter_exp, pcap_geterr(handle));
        return -1;
    }

    // -1 -> Should sniff until an error occurs
    pcap_loop(handle, -1, got_packet, NULL);

    pcap_close(handle);
    return 0;
}