macro define EC_INST(name) ec_inst_##name##_data
define dump_ec_var
    if $argc == 2
        set $addr_start = &EC_INST($arg1)
        set $addr_end = $addr_start + sizeof(EC_INST($arg1))
        dump binary memory $arg0 &EC_INST($arg1) &EC_INST($arg1) + sizeof(EC_INST($arg1))
        print "done!"
    else
        print "dump_ec_var <dump_file_path> <counter_name>"
    end
end
