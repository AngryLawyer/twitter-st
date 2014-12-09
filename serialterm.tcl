#!/usr/bin/env tclsh

puts "Starting serialterm..."

set device [lindex $argv 0]

puts "Using device $device"

# Now, we can connect
set serial [open $device r+]
fconfigure $serial -mode "9600,n,8,1" -blocking 0 -buffering none
fileevent $serial readable [list serial_receiver $serial]

set quit 0

proc serial_receiver { chan } {
    if { [eof $chan] } {
        puts stderr "Closing $chan"
        catch {close $chan}
        set quit 1
        return
    }
    set data [read $chan]
    set size [string length $data]
    puts $data
}

proc input_receiver { chan } {
    upvar quit quit
    upvar serial serial
    if { [eof $chan] } {
        puts stderr "Closing $chan"
        catch {close $chan}
        set quit 1
        return
    }
    if {[gets $chan line] >= 0} {
        if {[string equal $line "quit"]} {
            puts stderr "Closing $chan"
            catch {close $chan}
            set quit 1
            return
        }
        if {[string equal $line "CTRL_Z"]} {
            puts $serial 0x1a
        } else {
            puts $serial $line
        }
    }
}

fconfigure stdin -blocking 0 -buffering line
fileevent stdin readable [list input_receiver stdin]

vwait quit

catch {close $serial}
