#### 项目介绍
项目：STM32FlowMeter_SCL3300
硬件：Hw3
初始版本：STM32L152X_FlowMeter_Hw3_V1.0.5_20220112
创建日期：2022-01-12
项目说明：角度模块传感器：SCL3300(作为SCA100T替代品)

#### 更新日志
2022-01-12:
1. 修改算法参考<<角度模块温度补偿 算法更新220112.pdf>>
2. 以25C为补偿基准：>25C 升高1C -0.00286 <25 降低1C 补偿+0.00286
3. 修改bug：零点/系数补偿应该以算法补偿后的数值为原始值
4. Gitee的初始版本 xxx


#### 历史版本 
#### 详见<<\3. stm32+FlowMeter\3. STM32L152_SoftWare\STM32L152X_FlowMeter_SCL3300>>
*************************************************************************************************		
1. STM32L152X_FlowMeter_Hw3_V0.0.1 
a. 基于版本<<STM32L152X_FlowMeter_Hw2_V2.5.0>>
b. 硬件调整为SCL3300-D1
c. STM32L152相应IO口要做处理
d. X轴/Y轴零点附近转换时会出现较大的值(原因：AD先平均再算角度有问题)

2. STM32L152X_FlowMeter_Hw3_V0.0.2 
a. X轴/Y轴每次都计算出温度后再做平滑处理(解决零点附件出现较大值问题)
b. 2019.12.04输出给吴信超一版
								   
3. STM32L152X_FlowMeter_Hw3_V0.0.3 
a. 输出XYZ轴数据提供一版本
b. Z轴零点和标定数据存入E2中
c. Y轴输出正负调整angle_task.c L171:C68
								   
4. STM32L152X_FlowMeter_Hw3_V0.0.4 
a. Y轴输出恢复以前
b. Z轴输出改为arctan(fabs(Y/X))且符号与X轴相反2019.12.29
c. Z轴输出改为arctan(fabs(Y/X))且符号与Y轴相反2019.12.30(2基础上修改)
d. 解决Z轴零点无法清零BUG
								   
5. STM32L152X_FlowMeter_Hw3_V0.0.5 
a. A轴关闭输出
b. Y轴符号取反
c. 最终角度的计算放在angle_task.c中,原先放在Uart_task.c中存在bug
								   
6. STM32L152X_FlowMeter_Hw3_V0.0.6 
a. X轴改为Z轴输出
b. Y轴符号取反
c. 其他与V0.0.5版本保持一致
								   
7. STM32L152X_FlowMeter_Hw3_V1.0.0 
a. X轴Y轴Z轴都输出原始数据不做任何取反
b. 20200420输出版本
c. Rs485通讯模块ADM2587干扰到角度模块传感器需要做相应处理
								   
8. STM32L152X_FlowMeter_Hw3_V1.0.1 
a. 更新于2020-06-07
b. 增加Y轴温度补偿(记录设置相对零点时的温度值,温度降低,角度输出增加)
c. 温度距离标定时温度每下降1°,输出上升0.007°
								   
9. STM32L152X_FlowMeter_Hw3_V1.0.1_20200612
a. 温度补偿调整为0.0056
								   
10.STM32L152X_FlowMeter_Hw3_V1.0.2_20200628
a. 最终温度补偿确定为0.0056
								   
11.STM32L152X_FlowMeter_Hw3_V1.0.3_20200717
a. 添加X/Y/Z轴的温度补偿系数0.0056
b. 1E命令输出XYZ轴的零点标定K值及补偿温度
c. Hex和字符串切换
								  
12.STM32L152X_FlowMeter_Hw3_V1.0.4_20201020
a. 添加1F命令读取MCU唯一ID
   发送：68 04 00 1F 23
   回复：68 10 00 8F 33 34 47 02 39 34 33 36 00 75 71 76 81
   ID为：767175003633343902473433(12Bytes)
								   
12.1 STM32L152X_FlowMeter_Hw3_V1.0.4_20201020_X 
a. 临时修改的X轴输出版本
*************************************************************************************************
13.STM32L152X_FlowMeter_Hw3_V1.0.5_20220112   
a. 修改算法参考<<角度模块温度补偿 算法更新220112.pdf>>
b. 以25C为补偿基准：>25C 升高1C -0.00286 <25 降低1C 补偿+0.00286
c. 修改bug：零点/系数补偿应该以算法补偿后的数值为原始值
d. Gitee的初始版本
*************************************************************************************************