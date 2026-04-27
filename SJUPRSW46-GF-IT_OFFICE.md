!

ver 08.0.95hT213

!

hostname SJUPRSW46-GF-IT\_OFFICE

!

!

vlan 1 name DEFAULT-VLAN by port

&#x20;no untagged ethe 1/1/1 to 1/1/48

!

vlan 3 name Auth-Default by port

!

vlan 100 name "MGMT - Network Management" by port

&#x20;tagged ethe 1/1/48

&#x20;router-interface ve 100

!

vlan 101 name "MGMT - Wireless Access Points" by port

&#x20;tagged ethe 1/1/48

!

vlan 104 name "MGMT - AP Provisioning" by port

&#x20;tagged ethe 1/1/48

!

vlan 130 name "MGMT - LSP Gateway" by port

&#x20;tagged ethe 1/1/48

!

vlan 203 name "GPNS - Micros Terminals" by port

&#x20;tagged ethe 1/1/48

!

vlan 205 name "CASINO - Old Servers" by port

&#x20;tagged ethe 1/1/48

!

vlan 300 name "GPNS - Associate PCs" by port

&#x20;tagged ethe 1/1/48

!

vlan 301 name "GPNS - Associate Devices" by port

&#x20;tagged ethe 1/1/48

!

vlan 601 name "VENDOR - Associate VoIP" by port

&#x20;tagged ethe 1/1/48

!

vlan 652 name "VENDOR - Guest VoIP" by port

&#x20;tagged ethe 1/1/48

!

vlan 700 name "VENDOR - Surveillance" by port

&#x20;tagged ethe 1/1/48

!

vlan 800 name "VENDOR - Building Maintenance" by port

&#x20;tagged ethe 1/1/48

!

vlan 801 name "VENDOR - Background Music" by port

&#x20;tagged ethe 1/1/48

!

vlan 805 name "VENDOR - Business Center" by port

&#x20;tagged ethe 1/1/48

!

vlan 810 name "VENDOR - Digital Signage" by port

&#x20;tagged ethe 1/1/48

!

vlan 811 name "VENDOR - Security Devices" by port

&#x20;tagged ethe 1/1/48

!

vlan 815 name "VENDOR - ATM Machines" by port

&#x20;tagged ethe 1/1/48

!

vlan 821 name "VENDOR - Tokenization" by port

&#x20;tagged ethe 1/1/48

&#x20;untagged ethe 1/1/2 to 1/1/3

!

vlan 839 name "VENDOR - Non MI Time Clocks" by port

&#x20;tagged ethe 1/1/48

!

vlan 841 name "VENDOR - Key Machine" by port

&#x20;tagged ethe 1/1/48

!

vlan 843 name "VENDOR - Time Clock" by port

&#x20;tagged ethe 1/1/48

!

vlan 845 name "VENDOR - Gym Equipment" by port

&#x20;tagged ethe 1/1/48

!

vlan 847 name "VENDOR - KeyCard" by port

&#x20;tagged ethe 1/1/48

!

vlan 850 name "VENDOR - Enseo" by port

&#x20;tagged ethe 1/1/48

!

vlan 875 name "CASINO - Internet" by port

&#x20;tagged ethe 1/1/48

!

vlan 876 name "CASINO - VPN Connector" by port

&#x20;tagged ethe 1/1/48

!

vlan 877 name "CASINO - Gaming Machines" by port

&#x20;tagged ethe 1/1/48

!

vlan 878 name "VENDOR - ISISports" by port

&#x20;tagged ethe 1/1/48

!

vlan 1000 name "HSIA - Guest Wireless" by port

&#x20;tagged ethe 1/1/48

!

vlan 1017 name "HSIA - Associate Free" by port

&#x20;tagged ethe 1/1/48

!

vlan 1025 name "HSIA - Conference" by port

&#x20;tagged ethe 1/1/48

!

vlan 1050 name "HSIA - Guest Wired" by port

&#x20;tagged ethe 1/1/48

!

vlan 1254 name "VENDOR - Enseo Chromecast" by port

&#x20;tagged ethe 1/1/48

&#x20;router-interface ve 1254

!

vlan 1451 name Event\_Services by port

&#x20;tagged ethe 1/1/48

!

!

mstp scope all

mstp instance 0 vlan 1

mstp instance 0 vlan 3

mstp instance 0 vlan 100 to 1451

mstp edge-port-auto-detect

mstp start

!

authentication

&#x20;auth-default-vlan 3

&#x20;critical-vlan 1050

&#x20;restricted-vlan 1050

&#x20;auth-fail-action restricted-vlan

&#x20;dot1x enable

&#x20;dot1x enable ethe 1/1/1 to 1/1/47

&#x20;dot1x port-control auto ethe 1/1/1 to 1/1/47

&#x20;dot1x guest-vlan 1050

&#x20;mac-authentication enable

&#x20;mac-authentication enable ethe 1/1/1 to 1/1/47

!

aaa authentication dot1x default radius

aaa authentication login default radius local

aaa authentication enable default local

!

ip dhcp snooping vlan 101 104 130 203 205 300 to 301 601 652 700 800 801 805 810 811 815 821 839 841 843 845 847 850 875 1000 1017 1025 1050 1254

ip dhcp snooping

!

ip route 0.0.0.0/0 10.118.119.129

ip dns server-address 1.1.1.1

!

radius-server host 192.168.223.130 auth-port 1812 acct-port 1813 default key 2 $Y3FVT0dVcVU= dot1x mac-auth

!

snmp-server community ..... ro

snmp-server location IDF02 FL 1 GROUND LVL POOL

!

ntp server 192.168.223.130

!

!

interface ethernet 1/1/1 to 1/1/47

&#x20;port-name RADIUS

&#x20;loop-detection

&#x20;spanning-tree root-protect

&#x20;inline power power-by-class 3

&#x20;stp-bpdu-guard

!

interface ethernet 1/1/48

&#x20;port-name UPLINK\_TO\_STACK

&#x20;no untagged vlan 1

&#x20;ip dhcp snooping trust

!

interface ve 100

&#x20;ip address 10.118.119.161 255.255.255.128

!

interface ve 1254

!

!

end

