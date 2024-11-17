# 基于STM32的OLED屏驱动程序，支持软件或硬件I2C（HAL库）

**基于[STM32](https://blog.zeruns.tech/tag/stm32/)G474的0.96寸OLED(SSD1306)显示屏驱动程序（4针脚[I2C](https://blog.zeruns.tech/tag/I2C/)接口），支持硬件IIC/软件IIC，HAL库版。**

**这款驱动程序比较完善，可以实现 英文、整数、浮点数、汉字、图像、二进制数、十六进制数 等内容显示，可以画点、直线、矩形、圆、椭圆、三角形等，支持多种字体，差不多相当于一个简易版[图形库](https://blog.zeruns.tech/tag/图形库/)了。**

该程序是基于[zeruns](https://github.com/zeruns/STM32G4-OLED-SSD1306-I2C-HAL)三次修改的，原版基于江协科技v1.1版本代码，我修改后更新为江协科技v2.0版本代码
**测试硬件为STM32F103C8T6核心板**

关于OLED的驱动原理，以及驱动程序的使用教程可以看江协科技的视频：[https://url.zeruns.tech/L7j6y](https://www.bilibili.com/video/BV1EN41177Pc)

- STM32使用硬件I2C读取SHTC3温湿度传感器：[https://blog.zeruns.tech/archives/692.html](https://blog.zeruns.tech/archives/692.html)
- 移植好U8g2图形库的STM32F407标准库工程模板：[https://blog.zeruns.tech/archives/722.html](https://blog.zeruns.tech/archives/722.html)
- 基于STM32F1的0.96寸OLED显示屏驱动程序，支持硬件/软件I2C：[https://blog.zeruns.tech/archives/769.html](https://blog.zeruns.tech/archives/769.html)

电子/单片机技术交流群：[820537762](https://qm.qq.com/q/ZmTfBbFM4Y)

## 效果图

![](https://tc2.zeruns.tech/2024/03/17/1710612830448.gif)

![](https://tc2.zeruns.tech/2024/03/17/IMG_20240317_021954.jpeg)

![](https://tc2.zeruns.tech/2024/03/17/IMG_20240317_022008.jpeg)



## I2C协议简介

I2C 通讯协议(Inter－Integrated Circuit)是由 Phiilps 公司开发的，由于它引脚少，硬件实现简单，可扩展性强，不需要 USART、CAN 等通讯协议的外部收发设备（那些电平转化芯片），现在被广泛地使用在系统内多个集成电路(IC)间的通讯。

I2C只有一跟数据总线 SDA(Serial Data Line)，串行数据总线，只能一位一位的发送数据，属于串行通信，采用半双工通信。

半双工通信：可以实现双向的通信，但不能在两个方向上同时进行，必须轮流交替进行，其实也可以理解成一种可以切换方向的单工通信，同一时刻必须只能一个方向传输，只需一根数据线。

对于I2C通讯协议把它分为物理层和协议层物理层规定通讯系统中具有机械、电子功能部分的特性（硬件部分），确保原始数据在物理媒体的传输。协议层主要规定通讯逻辑，统一收发双方的数据打包、解包标准（软件层面）。

## I2C物理层

**I2C 通讯设备之间的常用连接方式**

![](https://tc.zeruns.tech/images/2022/11/03/image.png)

(1) 它是一个支持多设备的总线。“总线”指多个设备共用的信号线。在一个 I2C 通讯总线中，可连接多个 I2C 通讯设备，支持多个通讯主机及多个通讯从机。

(2) 一个 I2C 总线只使用两条总线线路，一条双向串行数据线SDA（Serial Data Line ），一条串行时钟线SCL（Serial Clock Line ）。数据线即用来表示数据，时钟线用于数据收发同步

(3) 总线通过上拉电阻接到电源。**当 I2C 设备空闲时会输出高阻态**，而当所有设备都空闲，都输出高阻态时，**由上拉电阻把总线拉成高电平**。

I2C通信时单片机GPIO口必须设置为开漏输出，否则可能会造成短路。

关于更多STM32的I2C相关信息和使用方法可以看这篇文章：[https://url.zeruns.tech/JC0Ah](https://url.zeruns.tech/JC0Ah)

还有江协科技的STM32入门教程：[https://www.bilibili.com/video/BV1th411z7sn?p=31](https://url.zeruns.tech/1zvY1)

我这里就不详细讲解了。

## 使用说明

工程使用Keil5创建，用Vscode+EIDE开发，两个软件都可以打开此工程。

工程文件全部使用UTF-8编码，如果打开显示乱码需要修改编辑器编码为UTF-8。

### 硬件I2C

第一步、STM32CubeMX配置I2C

启用对应的I2C外设，速度模式设置为 `Fast Mode`，其他默认就行。

![](https://imgcdn.qlqq.me/2024/11/17/6739b7ef7c844.png)

第二步、I2C的GPIO标签(User Label)定义分别改成`I2C_SCL`和`I2C_SDA`

![](https://imgcdn.qlqq.me/2024/11/17/6739b8d6536b0.png)

第三步、OLED.h文件里
1. 将 `#define OLED_USE_SW_I2C` 注释掉，将 `#define OLED_USE_HW_I2C` 取消注释
2. 修改红框中对应的定义

![](https://imgcdn.qlqq.me/2024/11/17/6739b94455e9c.png)

### 软件I2C

STM32CubeMX配置，设置两个引脚作为I2C的SCL和SDA信号线，修改IO口的 `User Lable` 分别为`I2C_SCL`和`I2C_SDA``，IO模式设置为开漏输出，默认输出电平高电平，上拉输出，速度设置到最高，如下图所示。改为后点击生成代码。

![](https://imgcdn.qlqq.me/2024/11/17/6739bb8a76c5e.png)

OLED.h文件里，将 `#define OLED_USE_HW_I2C` 注释掉，将 `#define OLED_USE_SW_I2C` 取消注释，如果你用的是别的引脚作为I2C引脚，并且定义了别的名字那就将代码里的 `I2C_SCL` 和 `I2C_SDA` 也改一下。

![](https://imgcdn.qlqq.me/2024/11/17/6739b94455e9c.png)

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
