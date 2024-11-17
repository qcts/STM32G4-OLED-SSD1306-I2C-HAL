# STM32 based OLED screen driver with software or hardware I2C support (HAL library)

**0.96" OLED(SSD1306) display driver based on [STM32](https://blog.zeruns.tech/tag/stm32/) G474 (4-pin [I2C](https://blog.zeruns.tech/tag/I2C/) interface), supports hardware IIC/software IIC , HAL library version.**

**This driver is more complete, it can realize content display of English, integer, floating point, Chinese characters, images, binary numbers, hexadecimal numbers, etc. It can draw points, straight lines, rectangles, circles, ellipses, triangles, etc., and support multiple fonts, almost equivalent to a simple version of the [Graphics Library](https://blog.zeruns.tech/tag/图形库/).**

The program is based on [zeruns](https://github.com/zeruns/STM32G4-OLED-SSD1306-I2C-HAL) three times modified, the original version based on Jiangxie Technology v1.1 version of the code, I modified and updated to Jiangxie Technology v2.0 version of 

**the code Test hardware for the STM32F103C8T6 Core Board**

Test hardware for the NUCLEO-G474RE development board

About the OLED driver principle, as well as the use of driver tutorials can see the video of Jiangxie Technology: [https://url.zeruns.tech/L7j6y](https://www.bilibili.com/video/BV1EN41177Pc)

- STM32 using hardware I2C to read SHTC3 temperature and humidity sensor: [https://blog.zeruns.tech/archives/692.html](https://blog.zeruns.tech/archives/692.html)
- STM32F407 standard library project template with U8g2 graphics library ported: [https://blog.zeruns.tech/archives/722.html](https://blog.zeruns.tech/archives/722.html)
- STM32F1 based 0.96" OLED display driver with hardware/software I2C support: [https://blog.zeruns.tech/archives/769.html](https://blog.zeruns.tech/archives/769.html)

Electronic / microcontroller technology exchange group: [820537762](https://qm.qq.com/q/ZmTfBbFM4Y)

## rendering

![](https://tc2.zeruns.tech/2024/03/17/1710612830448.gif)

![](https://tc2.zeruns.tech/2024/03/17/IMG_20240317_021954.jpeg)

![](https://tc2.zeruns.tech/2024/03/17/IMG_20240317_022008.jpeg)


## Introduction to I2C Protocol

I2C communication protocol (Inter-Integrated Circuit) was developed by Phiilps, because it has fewer pins, simple hardware implementation, strong scalability, and does not require external transceiver devices (those level conversion chips) such as USART, CAN and other communication protocols, it is now widely used in the system of multiple Nowadays, it is widely used in the communication between multiple integrated circuits (ICs) in a system.

I2C has only one data bus SDA (Serial Data Line), serial data bus, can only send data one by one, belongs to the serial communication, half-duplex communication.

Half-duplex communication: can be realized in both directions of communication, but not in both directions at the same time, you must take turns to alternate, in fact, can also be understood as a kind of switching direction of simplex communication, the same time must only be a direction of transmission, only a data line.

For the I2C communication protocol is divided into physical layer and protocol layer physical layer provides for the communication system with mechanical and electronic functions of the characteristics of the part (hardware), to ensure that the original data transmission in the physical media. The protocol layer specifies the communication logic and standardizes the data packetization and unpacketization criteria for both senders and receivers (software level).

## I2C Physical Layer

**Commonly used connection between I2C communication devices**

![](https://tc.zeruns.tech/images/2022/11/03/image.png)

(1) It is a bus that supports multiple devices. The term "bus" refers to a signal line shared by multiple devices. Multiple I2C communication devices can be connected to one I2C communication bus, supporting multiple communication masters and multiple communication slaves.

(2) An I2C bus uses only two bus lines, a bi-directional serial data line SDA (Serial Data Line) and a serial clock line SCL (Serial Clock Line). Data line that is used to indicate the data, the clock line is used to send and receive data synchronization

(3) The bus is connected to the power supply through a pull-up resistor. ** when the I2C device is idle will output a high resistance **, and when all devices are idle, all output a high resistance, ** by the pull-up resistor to pull the bus to a high level **.

The microcontroller GPIO port must be set to open-drain output for I2C communication, otherwise it may cause a short circuit.

For more I2C related information and usage of STM32 you can see this article: [https://url.zeruns.tech/JC0Ah](https://url.zeruns.tech/JC0Ah)

There is also the STM32 Getting Started Tutorial from Jiangxie Technology: [https://www.bilibili.com/video/BV1th411z7sn?p=31](https://url.zeruns.tech/1zvY1)

I won't go into detail here.

## Instructions for use

The project is created with Keil5 and developed with Vscode+EIDE, both software can open this project.

All project files are encoded in UTF-8, if you open them, you need to change the editor code to UTF-8.

### Hardware I2C

STM32CubeMX configuration, find the pin of the I2C peripheral you want to use, and set the pin function to SCL and SDA, the following picture shows the SCL of I2C3.

![](https://tc2.zeruns.tech/2024/03/17/image-20240317002450658.png)

Next, configure the I2C peripheral, enable the corresponding I2C peripheral, set the speed mode to `Fast Mode Plus`, change the speed to 1000, and other defaults will work.

![](https://tc2.zeruns.tech/2024/03/17/I2C829c2d4769742895.png)

Configure GPIO, after the above setting, it will automatically configure those two pins as multiplexed open-drain output mode, then you only need to change the IO output speed to `Very High`, and the definition of GPIO label (User Label) to `I2C3_SCL` and `I2C3_SDA` respectively, on the line, if you are using other I2C, you can also set it to other values, the code should be modified at the corresponding place. If you are using other I2C, you can set it to other values, and change the code in the corresponding place. After changing the code, click Generate Code.

![](https://tc2.zeruns.tech/2024/03/17/I2C_GPIO.png)

In the OLED.c file, comment out `#define OLED_USE_SW_I2C`, uncomment `#define OLED_USE_HW_I2C`, and change `I2C3_SCL` and `I2C3_SDA` in the code if you are using other I2C pins and have defined other names.

![](https://tc2.zeruns.tech/2024/03/17/image-20240317003414458.png)

### Software I2C

STM32CubeMX configuration, set two pins as SCL and SDA signal lines of I2C, modify the `User Lable` of IO port to `I2C3_SCL` and `I2C3_SDA` respectively, if you change it to something else, you need to change it in the code, the IO mode is set to open-drain output, the default output level is high, the output level of pull-up is high and the speed is set to the highest. The following figure shows. Click Generate Code after change.

![](https://tc2.zeruns.tech/2024/03/17/I2C.png)

In the OLED.c file, comment out `#define OLED_USE_HW_I2C`, uncomment `#define OLED_USE_SW_I2C`, and change `I2C3_SCL` and `I2C3_SDA` in the code if you use other pins as I2C pins and define other names.

![](https://tc2.zeruns.tech/2024/03/17/image-20240317001749175_bebe48917fc7a6d9e041be6ae5177659.png)

## 需要用的元件

- STM32开发板入门套件：[https://u.jd.com/fQS0YAe](https://union-click.jd.com/jdc?e=618%7Cpc%7C&p=JF8BARAJK1olXwQFXFpVCkofBV8IGlocXA8KVV9eD00RAV9MRANLAjZbERscSkAJHTdNTwcKBlMdBgABFksWAmYJElMUXAUFUlhfFxJSXzI4Wz5BI19ZKz44aRtJVG11QlpGC3pENFJROEonA24JGloSWgAAXG5tCEwnQgEIGVkRWgYDXG5cOEsRAmYBHVwdXAQEVFttD0seM20IGFgQWgQLUUJUDEoUAGY4K2sWbQECXUpbegpFF2l6K2sVbQUyVF9dAEgSBmYKE14JXQYDV1lVFEsRAmYBHVwcWw4BXFZtCkoWB2Y4K2tOGm0GLCA7dk1xZy19eQZFJ0JhEh8_bBl5AWsLHz9CB05XUiBaSiphUTl6Kw)
- STM32G474开发板：[https://s.click.taobao.com/8OwQ8vt](https://uland.taobao.com/coupon/edetail?e=3ztEP0oQ8WilhHvvyUNXZfh8CuWt5YH5OVuOuRD5gLJMmdsrkidbOWgpcJRl3wFwcV%2FlEyhmp8CYmXjGnIgd7UQu6s6gsCE0%2FJOeBFIUQHYHaI303F8Xg737A3DD3JZA0JtKkhb8h4Y84NOxmA9znSTsFs8hRhSMI%2BtaUgbudUxA%2B536asYsLU%2F9Zk7cDx8UI8pw0IfAr8CRxhZhkEO340qNMjRfsCNa84PXs%2B2%2FtMQYVCeN7Tu%2Fd3uXlFscPBzidQgRNzkZNvIYuReXXyTaYZoRR2hmQ%2BW20sE3ms4bv2mPbKNQ%2F2RySp8EKmb7V4loLbt9mvxQOOSF0oPBbaOrMoSJM%2BTNQmfVSYm1X96%2FcgElM1ZJHcLCJg%3D%3D&traceId=0bf8fe4917106137422975129e69f3&union_lens=lensId%3APUB%401710613647%40212bf9e0_0cfd_18e4884d1e3_cb09%4003MFVvyOa8SOvNqtO63j0Qi%40eyJmbG9vcklkIjo4NTQ2Nywiic3BtQiiI6Il9wb3J0YWxfdjJfcGFnZXNfcHJvbW9fZ29vZHNfZGV0YWlsX2h0bSIsInNyY0Zsb29ySWQiiOiiI4MDY3NCJ9%3Bscm%3A1007.30148.329090.pub_search-item_f2cf28a9-76a5-4d43-a6da-a494f40f2b9d_)
- OLED模块：[https://s.click.taobao.com/EF0Evwt](https://s.click.taobao.com/t?e=m%3D2%26s%3DBQQVS9oR8Wlw4vFB6t2Z2ueEDrYVVa64YUrQeSeIhnK53hKxp7mNFhiPRfK6WZZb%2BC8Fbl5oDyj0JlhLk0Jl4QTquP0kWxBLBDnvz6xo38xspWc9%2BCL4bTGF1ceZMhPo8mL8HhJ3EdVrH4ks4QyiY4z4rjZDGVMA8m%2BLYM2fkTL05J9EjZ4Cg6Q6sZp7gNLmb4%2BNtrBbTSxS1m9mhvByKBrMnaCVX7KBW7PNt0F7tu%2Bj2MnLlaGxOywInitlNLjeJEXD0Db1Cgm0zvIVVx%2BPc2%2F51BzEHetfxglKFrfPmkzgk553RHFrozHRcMhx5lEYXaWKN4mTpfzGDF1NzTQoPw%3D%3D&union_lens=lensId%3APUB%401708877132%402132b6c1_0d4d_18de103b431_7176%40023tYsbj43IzfeR7s373UeL0%40eyJmbG9vcklkIjo4MDY3NCwiic3BtQiiI6Il9wb3J0YWxfdjJfcGFnZXNfcHJvbW9fZ29vZHNfaW5kZXhfaHRtIiiwiic3JjRmxvb3JJZCI6IjgwNjc0In0ie%3Bscm%3A1007.30148.329090.pub_search-item_cfd89e5a-6719-4e0b-9631-719f1e445d1b_)
- 杜邦线：[https://s.click.taobao.com/VMkDvwt](https://s.click.taobao.com/t?e=m%3D2%26s%3DNAQNF5W5JbZw4vFB6t2Z2ueEDrYVVa64g3vZOarmkFi53hKxp7mNFhiPRfK6WZZbOdGYsaoillH0JlhLk0Jl4QTquP0kWxBLBDnvz6xo38xspWc9%2BCL4bTGF1ceZMhPo8mL8HhJ3EdVrH4ks4QyiY4z4rjZDGVMAhscfsB2%2FyzZJq71CBMBeP%2F1SarTXhIOTsgIpc1WFZiJNubylQlnZt9XuJrvisfUaLg8yhgHrwuW0bEeio6m796ZlQTRAZFsjdATSYpxt2P0VoXLgisw42qM70AliNjwJcn7ARWQ6ocV0hb0k2TPv%2BG5KHOQOD12OUoYNCSEtOZtWO1Zo39Y1p8Yl7w3%2FA2kb&union_lens=lensId%3APUB%401708877204%402104c34a_0d04_18de104cdd7_2053%40023jT5YfQJHA0mMOCZCKibC7%40eyJmbG9vcklkIjo4MDY3NCwiic3BtQiiI6Il9wb3J0YWxfdjJfcGFnZXNfcHJvbW9fZ29vZHNfaW5kZXhfaHRtIiiwiic3JjRmxvb3JJZCI6IjgwNjc0In0ie%3Bscm%3A1007.30148.329090.pub_search-item_9377ad37-ef13-44ca-8eea-bb37827b0d66_)
- 面包板：[https://s.click.taobao.com/bhg8Txt](https://s.click.taobao.com/t?e=m%3D2%26s%3DGUrId01gcUhw4vFB6t2Z2ueEDrYVVa64g3vZOarmkFi53hKxp7mNFhiPRfK6WZZbGlx1ZdvmWmb0JlhLk0Jl4QTquP0kWxBLBDnvz6xo38xspWc9%2BCL4bTGF1ceZMhPo8mL8HhJ3EdVrH4ks4QyiY4z4rjZDGVMA%2FXC6lFkCpYM56ZoUzm0cdkhUSIdDrY3ktWAKfhx9%2FCLZz2VyWhvCA7kq3xPS4D6oQhyywG7R2aIIas13MCLHCTVP5mUBCPs0MuvUHnPLiLAjTjU2N3HfFqM70AliNjwJcn7ARWQ6ocV0hb0k2TPv%2BG5KHOQOD12Onw4oeBHKRI6DInB1KCeXWcYl7w3%2FA2kb&union_lens=lensId%3APUB%401708877311%4021049f66_0d0d_18de1066ebf_e6c4%4002pOznnaNIB3wQbFtUC5sTM%40eyJmbG9vcklkIjo4MDY3NCwiic3BtQiiI6Il9wb3J0YWxfdjJfcGFnZXNfcHJvbW9fZ29vZHNfaW5kZXhfaHRtIiiwiic3JjRmxvb3JJZCI6IjgwNjc0In0ie%3Bscm%3A1007.30148.329090.pub_search-item_99474595-28e3-4d3b-8fa6-da3aa5a181ff_)
- DAPLink（可代替ST-Link，带虚拟串口）：[https://s.click.taobao.com/QVQ8Txt](https://s.click.taobao.com/t?e=m%3D2%26s%3DBRVDjoJNnqRw4vFB6t2Z2ueEDrYVVa64YUrQeSeIhnK53hKxp7mNFhiPRfK6WZZb9FlOLwLkNcT0JlhLk0Jl4QTquP0kWxBLBDnvz6xo38xspWc9%2BCL4bTGF1ceZMhPo8mL8HhJ3EdVrH4ks4QyiY4z4rjZDGVMAFBcM8wkWlGmBPeR%2FUFCetKLWMw3EOEsyJN2owMjhufwDudUsQ2T%2BdgqUOiHk7KHwCwr%2FNmk5d2u0vpJh576mRP8Cws%2FCg%2Fq0X%2FWmX2FNRIIYFRtWIu5mcU%2FuprW1TdmBLeMqtJBmsqDjUTeuQ%2BdMdzrtJLjN8V3%2FcSpj5qSCmbA%3D&union_lens=lensId%3APUB%401708877363%40210878e1_0d79_18de10737c0_d525%400238Bsi4blTj5vTJ7imyRHwg%40eyJmbG9vcklkIjo4MDY3NCwiic3BtQiiI6Il9wb3J0YWxfdjJfcGFnZXNfcHJvbW9fZ29vZHNfaW5kZXhfaHRtIiiwiic3JjRmxvb3JJZCI6IjgwNjc0In0ie%3Bscm%3A1007.30148.329090.pub_search-item_70c3e4a4-c44d-44a0-99c5-7136c519295e_)

**江协科技的STM32入门套件：[https://s.click.taobao.com/NTn9Txt](https://s.click.taobao.com/t?e=m%3D2%26s%3DFFF3WUPg2cpw4vFB6t2Z2ueEDrYVVa64g3vZOarmkFi53hKxp7mNFhiPRfK6WZZbuxz4Yx4FsL70JlhLk0Jl4QTquP0kWxBLBDnvz6xo38xspWc9%2BCL4bTGF1ceZMhPo8mL8HhJ3EdVrH4ks4QyiY4z4rjZDGVMAKhtnqJaQX2MflpVAuAy2VaLWMw3EOEsyJN2owMjhufwDudUsQ2T%2BdmTsy6cLY11yYexwAYiaHs2oS4Ml8iY1%2FxbzASfWQb%2B%2BKVVqWC8XTCluQ0m97%2BtRF0%2FuprW1TdmBLeMqtJBmsqAWDmQQxG5ZNlu9MBEPTelNcSpj5qSCmbA%3D&union_lens=lensId%3APUB%401708877026%40212c03c4_0d06_18de1021304_c90d%40024r1i4wvnsmoOt3Tx4i0nrb%40eyJmbG9vcklkIjo4MDY3NCwiic3BtQiiI6Il9wb3J0YWxfdjJfcGFnZXNfcHJvbW9fZ29vZHNfaW5kZXhfaHRtIiiwiic3JjRmxvb3JJZCI6IjgwNjc0In0ie%3Bscm%3A1007.30148.329090.pub_search-item_381225b4-c5f9-4e6b-ba67-2f9d1293b8c3_)**


## 推荐阅读

- **高性价比和便宜的VPS/云服务器推荐:** [https://blog.zeruns.tech/archives/383.html](https://blog.zeruns.tech/archives/383.html)
- 做了个三相电量采集器开源出来，可以方便监测家里用电情况：[https://blog.zeruns.tech/archives/771.html](https://blog.zeruns.tech/archives/771.html)
- 我的世界开服教程：[https://blog.zeruns.tech/tag/mc/](https://blog.zeruns.tech/tag/mc/)
- 幻兽帕鲁开服教程：[https://blog.zeruns.tech/tag/PalWorld/](https://blog.zeruns.tech/tag/PalWorld/)
- 睿登RD6012P数控可调电源简单开箱评测，60V 12A数控直流电源：[https://blog.zeruns.tech/archives/740.html](https://blog.zeruns.tech/archives/740.html)
- 拓竹P1SC 3D打印机开箱体验：[https://blog.zeruns.tech/archives/770.html](https://blog.zeruns.tech/archives/770.html)
- 不同品牌和种类的电容与电感实测对比（D值、Q值、ESR、X）：[https://blog.zeruns.tech/archives/765.html](https://blog.zeruns.tech/archives/765.html)
