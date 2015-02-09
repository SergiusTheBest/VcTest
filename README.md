# VcTest
A sample that demonstrates RDP8.1 virtual channel bug

### Sending 1592 bytes

Windows 8.1 | Windows 8.0
------------| -----------
![1592 bytes on W81](/images/test-1592-w81.png)|![1592 bytes on W80](/images/test-1592-w80.png)

BUG: `CHANNEL_FLAG_LAST` is not set on Windows 8.1.

### Sending 1000 bytes after 1592

Windows 8.1 | Windows 8.0
------------| -----------
![1000 bytes after 1592 on W81](/images/test-1000-after-1592-w81.png)|![1000 bytes after 1592 on W80](/images/test-1000-after-1592-w80.png)

BUG: The next packet is treated as a continuation of the previous one on Windows 8.1. `CHANNEL_FLAG_FIRST` is not set.

### Sending 1592 bytes after 1592

Windows 8.1 | Windows 8.0
------------| -----------
![1592 bytes after 1592 on W81](/images/test-1592-after-1592-w81.png)|![1592 bytes after 1592 on W80](/images/test-1592-after-1592-w80.png)

BUG: Packets with the length of 1591-1596 bytes aren't treated as a continuation of the previous packet on Windows 8.1 (like other packets).

### Sending 1600 bytes

Windows 8.1 | Windows 8.0
------------| -----------
![1600 bytes on W81](/images/test-1600-w81.png)|![1600 bytes on W80](/images/test-1600-w80.png)
![1600 bytes part 2 on W81](/images/test-1600-2-w81.png)|

1600 is the length of a virtual channel chunk. On Windows 8.1 it is transmitted as 2 packets while on Windows 8.0 - as 1 packet.

### Sending 1000 bytes

Windows 8.1 | Windows 8.0
------------| -----------
![1000 bytes on W81](/images/test-1000-w81.png)|![1000 bytes on W80](/images/test-1000-w80.png)

This is a positive case where everything goes like it should.
