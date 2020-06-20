#! /bin/sh
dd if=/dev/mtdblock1 bs=4 skip=1 count=1024 |grep _ >/tmp/wlan_mib
. /tmp/wlan_mib
set

ifconfig wlan0 hw ether `echo $HW_WLAN0_WLAN_ADDR |sed -e 's/\(..\)/\1:/g' -e 's/:$//'`
ifconfig wlan1 hw ether `echo $HW_WLAN1_WLAN_ADDR |sed -e 's/\(..\)/\1:/g' -e 's/:$//'`
ifconfig eth0 hw ether `echo $HW_NIC0_ADDR |sed -e 's/\(..\)/\1:/g' -e 's/:$//'`
ifconfig eth1 hw ether `echo $HW_NIC1_ADDR |sed -e 's/\(..\)/\1:/g' -e 's/:$//'`

ifconfig wlan1 up
ifconfig wlan0 up

iwpriv wlan1 set_mib pwrlevelHT40_1S_A=$HW_WLAN1_TX_POWER_HT40_1S_A
iwpriv wlan1 set_mib pwrlevelHT40_1S_B=$HW_WLAN1_TX_POWER_HT40_1S_B
iwpriv wlan1 set_mib pwrlevelCCK_B=$HW_WLAN1_TX_POWER_CCK_B
iwpriv wlan1 set_mib pwrlevelCCK_A=$HW_WLAN1_TX_POWER_CCK_A
iwpriv wlan1 set_mib pwrdiffHT20=$HW_WLAN1_TX_POWER_DIFF_HT20
iwpriv wlan1 set_mib pwrdiffOFDM=$HW_WLAN1_TX_POWER_DIFF_OFDM
iwpriv wlan1 set_mib xcap=$HW_WLAN1_11N_XCAP
iwpriv wlan1 set_mib ther=$HW_WLAN1_11N_THER
iwpriv wlan1 set_mib pwrdiffHT40_2S=$HW_WLAN1_TX_POWER_DIFF_HT40_2S
iwpriv wlan1 set_mib regdomain=$HW_WLAN1_REG_DOMAIN
iwpriv wlan1 set_mib 2ndchoffset=2
iwpriv wlan1 set_mib use40M=2
iwpriv wlan1 set_mib shortGI20M=1
iwpriv wlan1 set_mib ldpc=1
iwpriv wlan1 set_mib ampdu=1
iwpriv wlan1 set_mib coexist=1


iwpriv wlan0 set_mib pwrdiff_40BW2S_20BW2S_A=$HW_WLAN0_TX_POWER_DIFF_5G_40BW2S_20BW2S_A
iwpriv wlan0 set_mib pwrdiff_40BW2S_20BW2S_B=$HW_WLAN0_TX_POWER_DIFF_5G_40BW2S_20BW2S_B
iwpriv wlan0 set_mib pwrdiff_20BW1S_OFDM1T_A=$HW_WLAN0_TX_POWER_DIFF_5G_20BW1S_OFDM1T_A
iwpriv wlan0 set_mib pwrdiff_20BW1S_OFDM1T_B=$HW_WLAN0_TX_POWER_DIFF_5G_20BW1S_OFDM1T_B
iwpriv wlan0 set_mib xcap=$HW_WLAN0_11N_XCAP
iwpriv wlan0 set_mib ther=$HW_WLAN0_11N_THER
iwpriv wlan0 set_mib pwrlevel5GHT40_1S_A=$HW_WLAN0_TX_POWER_5G_HT40_1S_A
iwpriv wlan0 set_mib pwrlevel5GHT40_1S_B=$HW_WLAN0_TX_POWER_5G_HT40_1S_B
iwpriv wlan0 set_mib regdomain=$HW_WLAN0_REG_DOMAIN
iwpriv wlan0 set_mib 2ndchoffset=2
iwpriv wlan0 set_mib use40M=2
iwpriv wlan0 set_mib shortGI20M=1
iwpriv wlan0 set_mib ldpc=1
iwpriv wlan0 set_mib ampdu=1
iwpriv wlan0 set_mib coexist=1

ifconfig wlan0 down
ifconfig wlan1 down
ifconfig wlan1 up
ifconfig wlan0 up

( sleep 25 ; /sbin/wifi ; ) &



