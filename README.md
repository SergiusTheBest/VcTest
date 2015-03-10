# VcTest
A sample that demonstrates RDP8.1 virtual channel bug

## The Bug
If RDP 8.1 is active packets with the length of 1591-1596 bytes are working not as expected. Reproduced on Windows 8.1/2012R2.

## Response from Microsoft
* The packet length is reduced from 1600 to 1596 bytes because static virtual channels are run on dynamic ones in RDP8.1.
* The bug is fixed in the latest private build of Windows 10. The latest public build 9926 has the bug.
* Affected systems: 
 * Windows 7/2008R2 (with RDP 8.1 update)
 * Windows 8/2012
 * Windows 8.1/2012R2.
* They are working on a fix for pre-Windows 10 systems.

## How to Run
1. Build a solution with VS2013 (or [download release binaries](//github.com/SergiusTheBest/VcTest/releases/latest)).
2. Copy `VcTestAddin.dll` to `system32` (or `syswow64` on 64-bit windows, in that case you need to [disable 64-bit mstsc.exe](http://blogs.msdn.com/b/notime/archive/2012/12/15/run-32-bit-remote-desktop-rdp-on-windows-64-bit.aspx)).
3. Import `AddinRegistry.reg`.
4. Open a remote session via `mstsc.exe`.
5. Copy `VcTest` into the remote session.
6. Open command prompt and run `VcTest [packet length]`

Update: Added x64 build, so it can be tested on x64 mstsc.

## Test Results
For better reading the test results here are the flag values:
```cpp
#define CHANNEL_FLAG_FIRST      0x01
#define CHANNEL_FLAG_LAST       0x02
```

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

### Sending 2000 bytes

Windows 8.1 | Windows 8.0
------------| -----------
![2000 bytes on W81](/images/test-2000-w81.png)|![2000 bytes on W80](/images/test-2000-w80.png)
![2000 bytes part 2 on W81](/images/test-2000-2-w81.png)|![2000 bytes part 2 on W80](/images/test-2000-2-w80.png)

This is a positive case too but we see the chunk length is not 1600 on Windows 8.1.
