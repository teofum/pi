#include <stdio.h>

// We use unsigned int instead of unsigned long because it's all but guaranteed
// to hold 32 bits, it's not 1990 anymore
int format_ip(unsigned int ip, char *str);
void print_ip_data(unsigned int ip, unsigned char net_bits);

int main(void) {
  printf("%-18s  %-15s %-15s\n", "IP/network bits", "Network IP", "Host IP");
  print_ip_data(0xC0A80064, 16);
  print_ip_data(0x10FF1112, 24);
  print_ip_data(0x10FF1112, 23);
  print_ip_data(0x10FF1112, 16);

  return 0;
}

int format_ip(unsigned int ip, char *str) {
  unsigned char byte[4];
  byte[0] = (ip & 0xff000000) >> 24;
  byte[1] = (ip & 0x00ff0000) >> 16;
  byte[2] = (ip & 0x0000ff00) >> 8;
  byte[3] = (ip & 0x000000ff);

  return snprintf(str, 16, "%d.%d.%d.%d", byte[0], byte[1], byte[2], byte[3]);
}

void print_ip_data(unsigned int ip, unsigned char net_bits) {
  // Build net mask with net_bits ones and then all zeroes
  unsigned int net_mask = 0x00000000;
  unsigned int partial_mask = 0x80000000;
  unsigned char i = net_bits;
  while (i > 0) {
    net_mask |= partial_mask;
    partial_mask >>= 1;
    i--;
  }

  unsigned int net_ip = ip & net_mask;
  unsigned int host_ip = ip & ~net_mask;

  char str[16];
  char net_str[16];
  char host_str[16];
  format_ip(ip, str);
  format_ip(net_ip, net_str);
  format_ip(host_ip, host_str);

  printf("%-15s/%-2d  %-15s %-15s\n", str, net_bits, net_str, host_str);
}
