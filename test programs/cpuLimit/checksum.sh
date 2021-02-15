#!/bin/bash

path=( \
    ./btn_psr
    ./btn_pss
    ./drv_pss
    ./ident_pult
    ./sens_psr
    ./sens_pss
    ./lib_abs_iface.so
    ./lib_eink.so
    ./lib_ishtar_baseitem.so
    ./lib_ishtar_checker.so
    ./lib_ishtar_drv.so
    ./lib_ishtar_fifo.so
    ./lib_ishtar_gui.so
    ./lib_ishtar_net.so
    ./lib_ishtar_protocol.so
    ./lib_ishtar_settings.so
    ./lib_pult_settings.so
    ./ishtar_true.zip
    ./ishtar_true0.zip
    ./ishtar_true1.zip
    ./ishtar_true2.zip
    ./ishtar_true3.zip
    ./ishtar_true4.zip
    ./ishtar_true5.zip
    ./ishtar_true6.zip
    ./ishtar_true7.zip
    ./ishtar_true8.zip
    ./ishtar_true9.zip
    )

hash=$(cat ${path[*]} 2>/dev/null | cpulimit -l 5 md5sum | awk '{print $1}')

echo -e  "${hash}"
