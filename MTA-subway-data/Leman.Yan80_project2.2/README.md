I tested my subway portal, subway station and subway system with my own tester files. They work but I have no idea what is wrong when I run the makefile with main.o. Used gdb but the response is not helpful.

(gdb) backtrace
#0  0x00007ffff71a1428 in raise () from /lib/x86_64-linux-gnu/libc.so.6
#1  0x00007ffff71a302a in abort () from /lib/x86_64-linux-gnu/libc.so.6
#2  0x00007ffff71e37ea in ?? () from /lib/x86_64-linux-gnu/libc.so.6
#3  0x00007ffff71ec37a in ?? () from /lib/x86_64-linux-gnu/libc.so.6
#4  0x00007ffff71f053c in free () from /lib/x86_64-linux-gnu/libc.so.6
#5  0x0000000000404ed0 in SubwayPortal::~SubwayPortal (this=0x7fffffed4e00, 
    __in_chrg=<optimized out>) at subway_portal.h:33
#6  0x0000000000410180 in main ()




no idea whats wrong with my project

@Leman-Y
Leman-Y committed 2 hours ago
 
Added constructor to subway system & destructor to hash table:

@Leman-Y
Leman-Y committed 3 hours ago
 
No idea what the issue is. Tested all the relevant files. Might be so…  …

@Leman-Y
Leman-Y committed 3 hours ago
 
Testing subway system

@Leman-Y
Leman-Y committed 3 hours ago
 
Looks like subway station works

@Leman-Y
Leman-Y committed 3 hours ago
 
Testing subway station. Not sure if primary_name should be the portal…  …

@Leman-Y
Leman-Y committed 4 hours ago
 
Tested subway portal and it looks good. Time to test subway station

@Leman-Y
Leman-Y committed 4 hours ago
 
debug

@Leman-Y
Leman-Y committed 13 hours ago
 
Still got same error and doing get nearest portal

@Leman-Y
Leman-Y committed 14 hours ago
 
Let's pray that my functions work

@Leman-Y
Leman-Y committed a day ago
 
Changed find in hash_table in order to do get portal in subway system

@Leman-Y
Leman-Y committed a day ago
 
No idea if my functions actually work

@Leman-Y
Leman-Y committed a day ago
 
I think I'm good? No idea

@Leman-Y
Leman-Y committed a day ago
 
Commits on May 9, 2019
Need to update station name and list of children

@Leman-Y
Leman-Y committed a day ago
 
Doing form functions

@Leman-Y
Leman-Y committed a day ago
 
Implementing form stations & i still get subway portal = error

@Leman-Y
Leman-Y committed a day ago
 
No idea how to fix operator= error

@Leman-Y
Leman-Y committed a day ago
 
undefined reference and operator+ errors in make

@Leman-Y
Leman-Y committed a day ago
 
Do not put tester files in same folder when u are running make:

@Leman-Y
Leman-Y committed a day ago
 
Got bugs makefile wont compile:

@Leman-Y
Leman-Y committed a day ago
 
Added expected output files

@Leman-Y
Leman-Y committed a day ago
 
Implementing add portal

@Leman-Y
Leman-Y committed a day ago
 
Implementing add portal first

@Leman-Y
Leman-Y committed a day ago
 
Commits on May 7, 2019
Added some private data variables to subway system

@Leman-Y
Leman-Y committed 3 days ago
 
What private data member variables should I have?

@Leman-Y
Leman-Y committed 3 days ago
 
Implementing subway system

@Leman-Y
Leman-Y committed 3 days ago
 
Time to implement subway system

@Leman-Y
Leman-Y committed 3 days ago
 
Fixed bug

@Leman-Y
Leman-Y committed 4 days ago
 
Added updated subway system file

@Leman-Y
Leman-Y committed 4 days ago
 
Commits on May 6, 2019
No idea what the issue is with subwaystation interacting w/ private d…  …

@Leman-Y
Leman-Y committed 4 days ago
 
Update

@Leman-Y
Leman-Y committed 4 days ago
 
Still getting error with private member vars interacting w/ subway st…  …

@Leman-Y
Leman-Y committed 4 days ago
 
Still facing issue with SubwayStation getting an error when interacti…  …

@Leman-Y
Leman-Y committed 4 days ago
 
error with subwaystation interacting with portal's private member var…  …

@Leman-Y
Leman-Y committed 4 days ago
 
Still doing subway station

