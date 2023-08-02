#include <linux/init.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dov & Daniel");
MODULE_DESCRIPTION("My firewall");
MODULE_VERSION("0.1");


static struct nf_hook_ops nfho;

static unsigned int firewall_hook(void *priv,
                                 struct sk_buff *skb,
                                 const struct nf_hook_state *state) {
    struct iphdr *iph;

    if (!skb){
	return NF_ACCEPT;
    }
   
    iph = ip_hdr(skb);
    
    printk(KERN_INFO "Sourse: %pI4. Dest: %pI4\n",
           &iph->saddr, &iph->daddr);
    

    return NF_ACCEPT;
}

static int __init firewall_init(void) {
    nfho.hook = firewall_hook;
    nfho.pf = PF_INET;
    nfho.hooknum = NF_INET_PRE_ROUTING;
    nfho.priority = NF_IP_PRI_FIRST;

    nf_register_net_hook(&init_net, &nfho);
    printk(KERN_INFO "My netfilter\n");
    return 0;
}

static void __exit firewall_exit(void) {
    nf_unregister_net_hook(&init_net, &nfho);
    printk(KERN_INFO "GoodBye my netfilter\n");
}

module_init(firewall_init);
module_exit(firewall_exit);
