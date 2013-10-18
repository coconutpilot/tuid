# TUIDs - Time based Unique IDentifiers

### What are TUIDs?

TUIDs are unique identifiers designed for high performance computing.
They are realized using native integer datatypes which allows efficient use as key
fields in key/value stores and SQL databases.  They provide guaranteed uniqueness 
across threads/processes/machines without IPC or synchronization.  TUIDs can be
monotonically increasing so their natural sort order is the order of creation.


## SYNOPSIS

    tuid64_s *myctx = tuid64_init(NULL);
    uint64_t mytuid;
     
    do {
        mytuid = tuid64_r(myctx);
        ...
        
    } while (! is_done());


## DOCUMENTATION

See tuid.h for usage.

## Travis-ci Build Status

[![Build Status](https://travis-ci.org/coconutpilot/tuid.png)](https://travis-ci.org/coconutpilot/tuid)
