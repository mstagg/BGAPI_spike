There is a line in btle_driver.c -> handle_data() called print_bytes(); that is commented out.
It can be toggled to print raw data, however it has some memory issues at the moment.

Messages are printed in doubles for an unknown reason at the moment.
