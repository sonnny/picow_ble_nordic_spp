# picow_ble_nordic_spp
demo of pico w ble using nordic spp example
assumes pico-sdk is installed from https://github.com/raspberrypi/pico-sdk

once you get it running, put your own routine:

     1) edit blink.c
     2) on function nordic_spp_packet_handler:
     
          case RFCOMM_DATA_PACKET:
          led_on = !led_on;
          // send small letter t to toggle led
          if (packet[0] == 0x74) cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
          
          here I'm just toggling pico w led by sending small letter t from ble app
          
  I have tested this with nRF Connect for Mobile (android app) from Google Playstore
  also I have tested this with flutter app, source available here --> http://pinoysa.us/picow_ble
  after installing the flutter app make sure you allow location permission by going to settings, apps, click on your app, click on permissions and allow locations
  
  You need to edit CMakeLists.txt to reflect your own environment settings.
  
  
  Troubleshooting - try the forum --> https://forums.raspberrypi.com/viewforum.php?f=145&sid=1f7ed8f7d8fdb3b9413e41d17b5ea206
  
  
