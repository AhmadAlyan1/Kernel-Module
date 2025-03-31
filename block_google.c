#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ahmad Alyan");
MODULE_DESCRIPTION("Kernel Module to Block Only 8.8.8.8");

static struct nf_hook_ops nfho;

// Function to check if the IP is 8.8.8.8
static bool is_blocked_ip(u32 ip) {
    return ip == htonl(0x08080808); // 8.8.8.8
}

// Netfilter hook function
unsigned int block_google_dns(void *priv, struct sk_buff *skb, const struct nf_hook_state *state) {
    struct iphdr *iph;

    if (!skb)
        return NF_ACCEPT;

    iph = ip_hdr(skb);
    if (!iph)
        return NF_ACCEPT;

    // Drop packets from 8.8.8.8
    if (is_blocked_ip(iph->saddr)) {
        printk(KERN_INFO "Blocked packet from 8.8.8.8\n");
        return NF_DROP;
    }

    return NF_ACCEPT;
}

static int __init block_init(void) {
    nfho.hook = block_google_dns;
    nfho.hooknum = NF_INET_PRE_ROUTING;
    nfho.pf = PF_INET;
    nfho.priority = NF_IP_PRI_FIRST;

    nf_register_net_hook(&init_net, &nfho);
    printk(KERN_INFO "IP Blocking Module Loaded (Blocking Only 8.8.8.8)\n");
    return 0;
}

static void __exit block_exit(void) {
    nf_unregister_net_hook(&init_net, &nfho);
    printk(KERN_INFO "IP Blocking Module Unloaded\n");
}

module_init(block_init);
module_exit(block_exit);
