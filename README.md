TUIDs - Time based Unique IDentifiers

SYNOPSIS

USAGE

Setup

A context must be created that defines the format of the desired TUID.  Every
thread that 

TUIDs are created by initializing a context 


s - most significant bits from second component of unixtime
n - most significant bits from nanosecond component of unixtime
i - static identifier
c - counter
r - random



create_tuid_context("t16
