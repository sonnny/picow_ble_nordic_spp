# picow_ble_nordic_spp
demo of pico w ble using nordic spp example
assumes pico-sdk is installed from https://github.com/raspberrypi/pico-sdk

```
git clone https://github.com/sonnny/picow_ble_nordic_spp
cd picow_ble_nordic_spp
mkdir build
cd build
cmake ..
make

you should have blink.uf2 under build directory
press bootsel button of the pico w
while pressing boot button, short run (pin 30) to ground momentarily
rp2 should mount as storage
copy blink.uf2 to rp2
after done copying, rp2 should start executing the code

```



```
once you get it running, put your own routine:

     1) edit blink.c
     2) on function nordic_spp_packet_handler:
     
          case RFCOMM_DATA_PACKET:
          led_on = !led_on;
          // send small letter t to toggle led
          if (packet[0] == 0x74) cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
          
          here I'm just toggling pico w led by sending small letter t from ble app
```
          
  Tested this with nRF Connect for Mobile (android app) from Google Playstore
  
  Tested this with flutter app, source available here --> http://pinoysa.us/picow_ble
  after installing the flutter app make sure you allow location permission by going to settings, apps, click on your app, click on permissions and allow locations

```
Tested with linux cli
linux cli bluetooth assuming bluez installed
sudo bluetoothctl
scan on
connect 28:CD:C1:00:9F:60
info
menu gatt
list-attributes
select-attribute /org/bluez/hci0/dev_28_CD_C1_00_9F_60/service0004/char0005
write 0x74 # toggle led
```
  
  
  You need to edit CMakeLists.txt to reflect your own environment settings.
  
  
  Troubleshooting - try the forum --> https://forums.raspberrypi.com/viewforum.php?f=145&sid=1f7ed8f7d8fdb3b9413e41d17b5ea206
  
  
