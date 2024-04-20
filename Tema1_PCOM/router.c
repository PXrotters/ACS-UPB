#include <arpa/inet.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib.h"
#include "protocols.h"
#include "queue.h"

#define ICMP_TIME_EXCEEDED 11  // Time to live field hit to 0
#define ICMP_DESTINATION_UNREACHABLE 3  // Packet could not be delivered
#define ICMP_ECHO_REPLY 0  // Response to Ping request
#define ETHERTYPE_IP 0x0800  //  Protocol type : IP
#define ETHERTYPE_ARP 0x0806  // Protocol type : ARP
#define ETH_ALEN 6  // Ethernet address length
#define IP_ALEN 4  // IP address length
#define ICMP_PAYLOAD_SIZE 64
#define ARP_REQUEST 1
#define ARP_REPLY 2
#define ARPHRD_ETHER 1
#define ARP_PTYPE_IP 2048

struct packet {
	char *buffer;
	int length;
	int interface;
};

// Transformarea IP-ului din sir de caractere in intreg
uint32_t ip_address_to_int(const char *ip_address) {
    uint32_t new_ip_address = 0;
    int octet = 0;

    while (*ip_address != '\0') {
        if (*ip_address == '.') {
            // Atunci cand intalnim un punct, mutam octetul la stanga cu 8 biti
            new_ip_address = (new_ip_address << 8) | octet;
            octet = 0;
        } else if (*ip_address >= '0' && *ip_address <= '9') {
            // Daca este un numar, actualizam valoarea octetului
            octet = octet * 10 + (*ip_address - '0');
        } else {
            // In caz contrar, ignoram orice alte caractere
        }
        ip_address++; // Trecem la urmatorul caracter din adresa IP
    }

    // Adaugam ultimul octet la adresa IP
    new_ip_address = (new_ip_address << 8) | octet;

    return new_ip_address;
}

// Parcurgerea tabelei MAC si cautarea unei intrari care se potriveste cu adresa IP data
struct arp_table_entry *get_arp_table_entry(uint32_t ip_address, struct arp_table_entry *arp_table, int table_length) {
    // Parcurgem tabela ARP
    for (struct arp_table_entry *entry = arp_table; entry < arp_table + table_length; entry++) {
        // Verificam daca adresa IP cautata se potriveste cu adresa IP din intrare
        if (entry->ip == ip_address) {
            // Returnam pointerul catre intrarea corespunzatoare din tabel
            return entry;
        }
    }
    // Daca nu gasim o potrivire, returnam NULL
    return NULL;
}

// Cautare binara pe tabela de rutare pentru a gasi cea mai specifica ruta a adresei IP primite ca parametru
struct route_table_entry *binary_search(uint32_t ip_destination, struct route_table_entry *route_table, int left, int right) {
	if (left > right) {
		return NULL;
	}

	int middle = (left + right) / 2;

	if (route_table[middle].prefix <= (ip_destination & route_table[middle].mask)) {
		struct route_table_entry *best_entry = binary_search(ip_destination, route_table, middle + 1, right);
		if (best_entry != NULL) {
			return best_entry;
		}
		return &route_table[middle];
	} else {
		return binary_search(ip_destination, route_table, left, middle - 1);
	}
}

struct route_table_entry *best_route(uint32_t ip_destination, struct route_table_entry *route_table, int length) {
	return binary_search(ip_destination, route_table, 0, length - 1);
}

// Construirea si trimiterea unui pachet ICMP
void send_icmp(int interface, char *buf, uint8_t type) {
	struct ether_header *eth_hdr = (struct ether_header *)buf;
	struct iphdr *ip_hdr = (struct iphdr *)(buf + sizeof(struct ether_header));
	struct icmphdr *icmp_hdr = (struct icmphdr *)(buf + sizeof(struct ether_header) + sizeof(struct iphdr));
	char new_buf[MAX_PACKET_LEN];

	memcpy(new_buf, buf, sizeof(struct iphdr) + ICMP_PAYLOAD_SIZE);
	memcpy(eth_hdr->ether_dhost, eth_hdr->ether_shost, ETH_ALEN);
	get_interface_mac(interface, eth_hdr->ether_shost);

	ip_hdr->tot_len = ntohl(2 * sizeof(struct iphdr) + sizeof(struct icmphdr) + ICMP_PAYLOAD_SIZE);
	ip_hdr->ttl = ICMP_PAYLOAD_SIZE;
	ip_hdr->protocol = 1;
	ip_hdr->daddr = ip_hdr->saddr;
	ip_hdr->check = 0;
	ip_hdr->saddr = htonl(ip_address_to_int(get_interface_ip(interface)));
	ip_hdr->check = ntohs(checksum((void *)(ip_hdr), sizeof(struct iphdr)));

	icmp_hdr->type = type;
	icmp_hdr->code = 0;
	icmp_hdr->checksum = 0;
	icmp_hdr->checksum = checksum((void *)(icmp_hdr), sizeof(struct icmphdr));

	memcpy(buf + sizeof(struct iphdr) + sizeof(struct icmphdr) + sizeof(struct ether_header), new_buf, sizeof(struct iphdr) + ICMP_PAYLOAD_SIZE);

	int packet_length = 2 * sizeof(struct iphdr) + sizeof(struct icmphdr) + ICMP_PAYLOAD_SIZE + sizeof(struct ether_header);
	send_to_link(interface, buf, packet_length);
}

// Comparatorul folosit de functia qsort
int comparator(const void *current, const void *next) {
	struct route_table_entry *first = (struct route_table_entry *)current;
	struct route_table_entry *second = (struct route_table_entry *)next;

	if (first->mask != second->mask) {
		return (second->mask - first->mask);  // Descrescator dupa masca de retea
	} else {
		return (first->prefix - second->prefix);  // Crescator dupa prefixul retelei
	}
}

// Trimiterea unui raspuns de tip ARP
void arp_reply(uint32_t tpa, struct ether_header *eth_hdr, int interface, uint16_t op) {
	struct arp_header new_header;
	char buf[MAX_PACKET_LEN];
	new_header.htype = htons(ARPHRD_ETHER);
	new_header.ptype = htons(ARP_PTYPE_IP);
	new_header.hlen = ETH_ALEN;
	new_header.plen = IP_ALEN;
	new_header.op = op;
	memcpy(new_header.sha, eth_hdr->ether_shost, ETH_ALEN);
	new_header.spa = htonl(ip_address_to_int(get_interface_ip(interface)));
	memcpy(new_header.tha, eth_hdr->ether_dhost, ETH_ALEN);
	new_header.tpa = tpa;
	memset(buf, 0, MAX_PACKET_LEN);
	memcpy(buf, eth_hdr, sizeof(struct ether_header));
	memcpy(buf + sizeof(struct ether_header), &new_header, sizeof(struct arp_header));
	int len = sizeof(struct arp_header) + sizeof(struct ether_header);
	send_to_link(interface, buf, len);
}

int main(int argc, char *argv[])
{
	char buf[MAX_PACKET_LEN];

	// Do not modify this line
	init(argc - 2, argv + 2);

	queue Queue;
	Queue = queue_create();

	//Alocarea tabelelor de rutare si ARP
	struct arp_table_entry *arp_table = malloc(sizeof(struct arp_table_entry) * 100);
	struct route_table_entry *route_table = malloc(sizeof(struct route_table_entry) * 100000);
	//DIE folosit daca una din alocari a esuat
	DIE(route_table == NULL, "memory");
	DIE(arp_table == NULL, "memory");

	int route_table_length = read_rtable(argv[1], route_table);  // Citirea tabelei de rutare si retinerea lungimii sale
	int arp_table_length = 0;  // Lungimea tabelei arp
	qsort(route_table, route_table_length, sizeof(struct route_table_entry), comparator);  // Sortarea tabelei de rutare

	while (1) {

		int interface;
		size_t len;

		interface = recv_from_any_link(buf, &len);
		DIE(interface < 0, "recv_from_any_links");

		struct ether_header *eth_hdr = (struct ether_header *)buf;
		/* Note that packets received are in network order,
		any header field which has more than 1 byte will need to be conerted to
		host order. For example, ntohs(eth_hdr->ether_type). The oposite is needed when
		sending a packet on the link, */

		if (eth_hdr->ether_type == ntohs(ETHERTYPE_IP)) {
			struct iphdr *ip_hdr = (struct iphdr *)(buf + sizeof(struct ether_header));

			// Verificarea integritatii ip_hdr folosind checksum
			uint16_t old_check = ip_hdr->check;
			ip_hdr->check = 0;
			if (old_check != htons(checksum((uint16_t *)ip_hdr, sizeof(struct iphdr)))) {
				continue;
			}

			// Gasirea celei mai bune rute specifice
			struct route_table_entry *best_router = best_route(ip_hdr->daddr, route_table, route_table_length);

			if (best_router == NULL) {
				send_icmp(interface, buf, ICMP_DESTINATION_UNREACHABLE);
				continue;
			}
			uint32_t my_ip = inet_addr(get_interface_ip(interface));
			if (my_ip == ip_hdr->daddr) {
				send_icmp(interface, buf, ICMP_ECHO_REPLY);
				continue;
			}
			if (ip_hdr->ttl <= 1) {
				send_icmp(interface, buf, ICMP_TIME_EXCEEDED);
				continue;
			}

			// Daca TTL > 1, se recalculeaza TTL-ul si checksum-ul
			--ip_hdr->ttl;
			ip_hdr->check = htons(checksum((uint16_t *)ip_hdr, sizeof(struct iphdr)));

			/* Actualizarea adreselor Ethernet. Folosirea functiei get_arp_table_entry pentru a gasi adresa MAC de destinatie.
			 Folosirea functiei get_interface_mac pentru a gasi adresa MAC a interfetei */
			struct arp_table_entry *nexthop_mac = get_arp_table_entry(best_router->next_hop, arp_table, arp_table_length);
			if (nexthop_mac == NULL) {
				struct ether_header new_eth_hdr;
				get_interface_mac(best_router->interface, new_eth_hdr.ether_shost);
				memset(new_eth_hdr.ether_dhost, 0xff, sizeof(new_eth_hdr.ether_dhost));
				new_eth_hdr.ether_type = htons(ETHERTYPE_ARP);
				arp_reply(best_router->next_hop, &new_eth_hdr, best_router->interface, htons(ARP_REQUEST));

				// Salveaza pachetul curent intr-o coada
				struct packet *package_copy = malloc(sizeof(struct packet));
				package_copy->interface = best_router->interface;
				package_copy->buffer = malloc(sizeof(char) * MAX_PACKET_LEN);
				DIE(package_copy == NULL, "Couldn't allocate memory");
				memcpy(package_copy->buffer, buf, sizeof(buf));
				package_copy->length = len;
				queue_enq(Queue, package_copy);
				continue;
			}
			memcpy(eth_hdr->ether_dhost, nexthop_mac->mac, sizeof(eth_hdr->ether_dhost));
			get_interface_mac(best_router->interface, eth_hdr->ether_shost);
			send_to_link(best_router->interface, buf, len);
		} else if (ntohs(eth_hdr->ether_type) == ETHERTYPE_ARP) {
			struct arp_header *arp_hdr = (struct arp_header *)(buf + sizeof(struct ether_header));

			switch (ntohs(arp_hdr->op)) {
			case (ARP_REQUEST):
			{
				struct ether_header new_eth_hdr;
				get_interface_mac(interface, new_eth_hdr.ether_shost);
				memcpy(new_eth_hdr.ether_dhost, arp_hdr->sha, sizeof(arp_hdr->sha));
				new_eth_hdr.ether_type = htons(ETHERTYPE_ARP);
				arp_reply(arp_hdr->spa, &new_eth_hdr, interface, htons(ARP_REPLY));
				break;
			}
			case (ARP_REPLY):
			{
				struct arp_table_entry new_arp_entry;
				new_arp_entry.ip = arp_hdr->spa;
				memcpy(new_arp_entry.mac, arp_hdr->sha, sizeof(arp_hdr->sha));

				arp_table[arp_table_length++] = new_arp_entry;

				// Trimiterea pachetelor din coada catre destinatie
				while (!queue_empty(Queue)) {
					struct packet *package_q = (struct packet *)queue_deq(Queue);
					struct ether_header *enqued_eth_hdr = (struct ether_header *)package_q->buffer;

					get_interface_mac(package_q->interface, enqued_eth_hdr->ether_shost);
					memcpy(enqued_eth_hdr->ether_dhost, arp_hdr->sha, sizeof(arp_hdr->sha));

					send_to_link(package_q->interface, package_q->buffer, package_q->length);
				}
			}
			}
		}
	}
}
