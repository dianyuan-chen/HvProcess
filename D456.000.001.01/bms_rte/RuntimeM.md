# 运行时管理

## 运行流程
```mermaid
graph TD

init(初始化) --> isOnlyRtcWake{只有RTC唤醒信号?}
subgraph 预处理
isOnlyRtcWake -- N --> DirectToData{直接进入数据模式?}
DirectToData -- N --> supportChargeEndOTA1{支持充电末端升级?}
supportChargeEndOTA1 -- Y --> DirectToDtu{直接进入DTU模式?}

end

subgraph 正常工作模式,标定模式,数据模式

supportChargeEndOTA1 -- N --> queryDongle[查询Dongle,等待应答]
DirectToDtu -- N -->  queryDongle
DirectToData -- Y --> requestPowerDownOrReset{请求下电或复位}

queryDongle --> hasDongle{有Dongle应答?}
hasDongle -- Y --> setMode[设置对应模式]
hasDongle -- N --> setDefaultMode[设置为工作模式]
setMode --> requestPowerDownOrReset
requestPowerDownOrReset -- Y -->stopAll
requestPowerDownOrReset -- N --> hasWakeup{存在唤醒信号?}

setDefaultMode --> requestPowerDownOrReset
hasWakeup -- N --> confirm[连续确认唤醒信号丢失,<br>10次,5ms/次]
confirm --> isConfirm{确认唤醒信号丢失?}
isConfirm -- N --> requestPowerDownOrReset
isConfirm -- Y --> stopAll[结束所有任务]
stopAll --> requestReset{请求复位?}
requestReset -- N --> setWakeupTime[根据情况设置下次唤醒时间]
requestReset -- Y --> setFlagAndReset[设置标记并复位]
setWakeupTime --> powerOff1[关闭电源]
hasWakeup -- Y --> delay5ms2[延时5ms]
delay5ms2 --> requestPowerDownOrReset

end

subgraph DTU模式
DirectToDtu -- Y --> dtuMode
isOnlyRtcWake -- Y --> dtuMode[设置DTU模式]
dtuMode --> supportChargeEndOTA2{支持充电末端升级?}
supportChargeEndOTA2 -- N --> anyOtherWakeup{存在唤醒信号?}
supportChargeEndOTA2 -- Y --> timeout{运行超时?}

anyOtherWakeup -- Y --> reset[复位进入应用程序]
anyOtherWakeup -- N --> timeout

timeout -- Y -->  stopAll2[结束所有任务]
stopAll2 --> setWakeupTime2[根据情况设置下次唤醒时间]
setWakeupTime2 --> powreOff2[关闭电源]
timeout -- N --> requestPowerDown{有请求下电?}
requestPowerDown -- Y --> stopAll2
requestPowerDown-- N --> delay5ms1
delay5ms1[延时5ms] --> supportChargeEndOTA2

end
powerOff1 --> xend(结束)
setFlagAndReset --> xend
powreOff2 --> xend
reset-->xend
```


## 配置参数

```javascript
RuntimeM: {
    maxTimeForWaitTaskPowerdown: 10,
    wakeupTimeForOTA: 90,
    wakeupTimeForData: "02:00",
    maxOnTimeForOTA: 60*60,
    maxOnTimeForData: 60*5,
    minBatteryVolForWakeup: 10,
    chargeEndOTA: true,
    powerOffNotifiers: [
        {func:"Soc_PowerDownSaveCbk", inc: "Soc.h"},
        {func:"SaveM_PowerDownSaveCbk", inc: "SaveM.h"}
    ]
},
```

1. maxTimeForWaitTaskPowerdown: 下电等待的最大时间(单位秒), 指上面流程图中结束所有任务所需要的最大时间, 如果在这个时间内仍有任务没有结束, 也是强制下电;

1. wakeupTimeForOTA: 收到升级请求之后, 多长时间(什么时刻)唤醒开始升级, 单位秒或者指定时刻(例如:"02:00");

1. wakeupTimeForData: 关机之后, 多长时间唤醒开始向后台发送数据, 单位秒或者指定时刻(例如:"02:00");

1. maxOnTimeForOTA: 唤醒发送数据最长的工作时间(单位秒), 指唤醒之后开始数据传输; 如果由于网络等原因导致数据不能正常发出, 从而不能主动下电, 那么当运行这么长时间之后会强制下电;

1. maxOnTimeForData: 唤醒升级据最长的工作时间(单位秒), 指唤醒之后开始OTA传输; 如果由于网络等原因导致数据不能正常进行, 从而不能主动下电, 那么当运行这么长时间之后会强制下电;

1. minBatteryVolForWakeup: 唤醒要求的最低供电电压(单位v), 下电时设置下次唤醒所需要的供电电压的一个条件, 当供电电压低于这个值时, 不会设置下次的唤醒时间, 以保证铅酸电池的电量;

1. chargeEndOTA: 是否支持充电完成时候进行OTA;

1. powerOffNotifiers: 下电时需要调用的函数列表, 指上面流程图中结束所有任务所需要执行的函数;
