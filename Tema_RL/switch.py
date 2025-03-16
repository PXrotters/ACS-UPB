#!/usr/bin/python3
import sys
import struct
import wrapper
import threading
import time
from wrapper import recv_from_any_link, send_to_link, get_switch_mac, get_interface_name

mac_address_table = {}  # Tabela adreselor MAC
vlan_mapping = {}  # Asocieri VLAN-uri
# Starea porturilor
port_states = {}  # Starile porturilor
# Identificatori pentru bridge-uri si costul drumului
root_bridge_id = None  # ID-ul root bridge-ului
root_bridge_path_cost = None  # Costul drumului catre root bridge

# Constante bdbu
BPDUS_DESTINATION_MAC = b'\x01\x80\xC2\x00\x00\x00'  # MAC-ul destinatiei pentru BPDU
LLC_HEADER_LENGTH = b'\x00\x38'  # Lungimea header-ului LLC
LLC_HEADER_CONTENT = b'\x42\x42\x03'  # Continutul header-ului LLC
PROTO_IDENTIFIER = b'\x00' * 5  # Identificatorul protocolului (5 octeti de zero)
PADDING_BYTES = b'\x00' * 8

def parse_ethernet_header(data):
    # Unpack the header fields from the byte array
    #dest_mac, src_mac, ethertype = struct.unpack('!6s6sH', data[:14])
    dest_mac = data[0:6]
    src_mac = data[6:12]
    
    # Extract ethertype. Under 802.1Q, this may be the bytes from the VLAN TAG
    ether_type = (data[12] << 8) + data[13]

    vlan_id = -1
    # Check for VLAN tag (0x8100 in network byte order is b'\x81\x00')
    if ether_type == 0x8200:
        vlan_tci = int.from_bytes(data[14:16], byteorder='big')
        vlan_id = vlan_tci & 0x0FFF  # extract the 12-bit VLAN ID
        ether_type = (data[16] << 8) + data[17]

    return dest_mac, src_mac, ether_type, vlan_id

def create_vlan_tag(vlan_id):
    # 0x8100 for the Ethertype for 802.1Q
    # vlan_id & 0x0FFF ensures that only the last 12 bits are used
    return struct.pack('!H', 0x8200) + struct.pack('!H', vlan_id & 0x0FFF)


def send_bdpu_every_sec(interfaces):
    while True:
        # TODO Send BDPU every second if necessary
        # Daca switch-ul curent este root bridge
        if root_bridge_ID == local_bridge_ID:
            bpdu_prefix = BPDUS_DESTINATION_MAC + get_switch_mac() + LLC_HEADER_LENGTH + LLC_HEADER_CONTENT + PROTO_IDENTIFIER
            root_bridge_bytes = root_bridge_ID.to_bytes(8, byteorder='big')
            root_bridge_path_cost_bytes = root_bridge_path_cost.to_bytes(4, byteorder='big')
            local_bridge_bytes = local_bridge_ID.to_bytes(8, byteorder='big')

            for interface in interfaces:
                if vlan_mapping.get(get_interface_name(interface)) == 'T':
                    port_bytes = interface.to_bytes(2, byteorder='big')
                    bpdu = bpdu_prefix + root_bridge_bytes + root_bridge_path_cost_bytes + local_bridge_bytes + port_bytes + PADDING_BYTES
                    send_frame(bpdu, interface)
        
        time.sleep(1)

def send_frame(dataFrame, port):
    send_to_link(port, len(dataFrame), dataFrame)

def load_switch_configuration(switch_id):
    switch_file = f'configs/switch{switch_id}.cfg'
    priority = None

    with open(switch_file, 'r') as file:
        for line in file:
            tokens = line.split()

            if len(tokens) == 1:
                priority = int(tokens[0])
            else:
                port, vlan = tokens
                vlan_mapping[port] = vlan
                if vlan == 'T':
                    port_states[port] = port_states[port] = 'BLOCKED'
                else:
                    port_states[port] = 'DESIGNATED'

    return priority


def main():
    # init returns the max interface number. Our interfaces
    # are 0, 1, 2, ..., init_ret value + 1
    switch_id = sys.argv[1]

    num_interfaces = wrapper.init(sys.argv[2:])
    interfaces = range(0, num_interfaces)

    priority = load_switch_configuration(switch_id)
    global local_bridge_ID
    global root_bridge_ID
    global root_bridge_path_cost

    local_bridge_ID = priority
    root_bridge_ID = local_bridge_ID
    root_bridge_path_cost = 0

    # print("# Starting switch with id {}".format(switch_id), flush=True)
    # print("[INFO] Switch MAC", ':'.join(f'{b:02x}' for b in get_switch_mac()))

    # Create and start a new thread that deals with sending BDPU
    t = threading.Thread(target=send_bdpu_every_sec, args=(interfaces,))
    t.start()

    # Printing interface names
    # for i in interfaces:
    #    print(get_interface_name(i))

    while True:
        # Note that data is of type bytes([...]).
        # b1 = bytes([72, 101, 108, 108, 111])  # "Hello"
        # b2 = bytes([32, 87, 111, 114, 108, 100])  # " World"
        # b3 = b1[0:2] + b[3:4].
        interface, data, length = recv_from_any_link()

        dest_mac, src_mac, ethertype, vlan_id = parse_ethernet_header(data)

        # Print the MAC src and MAC dst in human readable format
        dest_mac = ':'.join(f'{b:02x}' for b in dest_mac)
        src_mac = ':'.join(f'{b:02x}' for b in src_mac)

        # Note. Adding a VLAN tag can be as easy as
        # tagged_frame = data[0:12] + create_vlan_tag(10) + data[12:]
        # Determinarea etichetarii VLAN
        if vlan_id == -1:
            vlan_id = vlan_mapping[get_interface_name(interface)]     
            if vlan_id != 'T':
                tagged_frame = data[0:12] + create_vlan_tag(int(vlan_id)) + data[12:]
                untagged_frame = data
        else:
            tagged_frame = data            
            untagged_frame = data[0:12] + data[16:]

        # print(f'Destination MAC: {dest_mac}')
        # print(f'Source MAC: {src_mac}')
        # print(f'EtherType: {ethertype}')

        # print("Received frame of size {} on interface {}".format(length, interface), flush=True)

        # TODO: Implement forwarding with learning
        # TODO: Implement VLAN support
        # TODO: Implement STP support

        mac_address_table[src_mac] = interface
        
        # Verificam daca cadrul primit este un BPDU
        if dest_mac == '01:80:c2:00:00:00':
            
            # Extragem informatiile din cadrul BPDU
            data_root_bridge_ID = data[29]
            data_sender_path_cost = data[33]
            data_sender_bridge_ID = data[41]

             # Verificam daca root bridge-ul primit este mai mic decat cel local
            if data_root_bridge_ID < root_bridge_ID:
                root_bridge_ID = data_root_bridge_ID  # Actualizam root bridge ID
                root_bridge_path_cost = data_sender_path_cost + 10  # Calculam costul drumului
                root_port = interface  # Stabilim root port
                
                # Daca root bridge-ul este local, blocam porturile neetichetate
                if root_bridge_ID == local_bridge_ID:
                    for i in interfaces:
                        port_name = get_interface_name(i)
                        if vlan_mapping[port_name] != 'T':
                            port_states[port_name] = 'BLOCKED'  # Seteaza starea portului ca BLOCKED
                    port_states[get_interface_name(root_port)] = 'DESIGNATED'  # Seteaza starea portului root ca DESIGNATED

                # Daca root port-ul este BLOCKED, il setam ca DESIGNATED
                if port_states[get_interface_name(root_port)] == 'BLOCKED':
                    port_states[get_interface_name(root_port)] = 'DESIGNATED'
                    
                # Trimitem BPDU-uri pe toate interfetele etichetate, exceptand root port-ul
                for i in interfaces:
                    port_name = get_interface_name(i)
                    if vlan_mapping[port_name] == 'T' and i != root_port:
                        # Conversia ID-urilor si costului in bytes
                        root_bridge_bytes = int(root_bridge_ID).to_bytes(8, byteorder='big')
                        local_bridge_bytes = int(local_bridge_ID).to_bytes(4, byteorder='big')
                        root_bridge_path_cost_bytes = int(root_bridge_path_cost).to_bytes(8, byteorder='big')
                        port_bytes = i.to_bytes(2, byteorder='big')
                        # Crearea BPDU-ului
                        bpdu = (BPDUS_DESTINATION_MAC + get_switch_mac() + LLC_HEADER_LENGTH + LLC_HEADER_CONTENT + PROTO_IDENTIFIER +
                                root_bridge_bytes + local_bridge_bytes + root_bridge_path_cost_bytes + port_bytes + PADDING_BYTES)
                        # Trimiterea BPDU-ului
                        send_frame (bpdu, i)

            # Verificam daca ID-ul root bridge-ului este acelasi cu cel local
            elif data_root_bridge_ID == root_bridge_ID:
                if interface == root_port and data_sender_path_cost + 10 < root_bridge_path_cost:
                    root_bridge_path_cost = data_sender_path_cost + 10  # Actualizam costul drumului
                elif interface != root_port and data_sender_bridge_ID > root_bridge_path_cost and port_states[get_interface_name(interface)] != 'DESIGNATED':
                            port_states[get_interface_name(interface)] = 'DESIGNATED'

            # Verificam daca ID-ul bridge-ului trimis este local
            elif data_sender_bridge_ID == local_bridge_ID:
                port_states[get_interface_name(interface)] = 'BLOCKED'

            # Daca root bridge-ul este local, setam porturile etichetate ca DESIGNATED
            if root_bridge_ID == local_bridge_ID:
                for i in interfaces:
                    if vlan_mapping[get_interface_name(i)] == 'T':
                        port_states[get_interface_name(i)] = 'DESIGNATED'

        # Redirectionarea pe baza tabelei MAC
        elif dest_mac != 'ff:ff:ff:ff:ff:ff' and dest_mac in mac_address_table:
            interface_name = get_interface_name(mac_address_table[dest_mac])
            # Verificam tipul VLAN-ului si trimitem cadrul corespunzator
            if vlan_mapping[interface_name] == 'T':
                send_frame(tagged_frame, mac_address_table[dest_mac])
            else:
                send_frame(untagged_frame, mac_address_table[dest_mac])
        else:
            # Trimitem cadrul pe toate interfetele, exceptand interfata curenta
            for i in interfaces:
                if i != interface and port_states[get_interface_name(i)] != 'BLOCKED':
                    current_vlan = vlan_mapping[get_interface_name(i)]
                    # Verificam tipul VLAN-ului si trimitem cadrul corespunzator
                    if current_vlan == str(vlan_id):
                        send_frame(untagged_frame, i)
                    elif current_vlan == 'T':
                        send_frame(tagged_frame, i)


if __name__ == "__main__":
    main()
