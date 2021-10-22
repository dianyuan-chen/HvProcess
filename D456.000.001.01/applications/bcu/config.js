module.exports = {
    notes:[
        {section:"BatteryInfo", chs:"电池基本信息", comments:"描述电池的相关信息."},
        {section:"SystemConnection", chs:"系统连接配置", comments:"描述主机型号,从机型号, 以及电池温感连接情况."},
        {section:"CanDrv", chs:"Can驱动层配置", comments:"描述HOH与硬件Can的对应关系"},
        {section:"CanIf", chs:"Can接口层配置", comments:"描述上层需要通过CanIf发送或接受的数据帧ID以及使用的HOH, 不需要配置主从协议的"},
        {section:"CanTp", chs:"Can传输层配置", comments:"描述需要使用CanTp接受或发送的通道及对应的CanId, 不需要配置主从协议的"},
        {section:"CanTp", chs:"Can传输层配置", comments:"描述需要使用CanTp接受或发送的通道及对应的CanId, 不需要配置主从协议的"},
    ],

    AppInfo: {
        releaseType: "T",
        releaseType_comments: '"T"或"R", 请参考<<软件版本规范>>',

        comments: "如果为模版, 请保持下列配置都为空",
        pid: "D456.000.001.01",
        pid_comments: "项目编码, 请参考<<优旦项目编码规范>>",
        requireVer: "1.0",
        requireVer_comments: "需求版本, 请参考<<软件版本规范>>",
        buildVer: "3",
        buildVer_comments: "编译版本, 请参考<<软件版本规范>>",
    },

    BatteryInfo: {
        notes: [
            {section:"type", chs: "电池类型", comments:'可选:"铅酸","镍氢","磷酸铁锂","锰酸锂","钴酸锂","三元材料","聚合物锂离子","钛酸锂","其他"'},
            {section:"nominal", chs: "额定参数", comments:'电池的一些额定参数'},
            {section:"serialnum", chs: "电池串数"},
            {section:"parallelnum", chs: "电池并数"},
            {section:"celltempnum", chs: "电池单体温感数量"},
            {section:"poletempnum", chs: "电池极柱温感数量"},
            {section:"heattempnum", chs: "加热片温感数量"},
            {section:"initsoc", chs: "初始SOC, 单位1%"},
            {section:"initsoh", chs: "初始SOH, 单位1%"},
        ],
        type: "磷酸铁锂",
        nominal: {
            notes:[
                {section:"cap", chs:"额定容量, 单位Ah"},
                {section:"dischargecurrent", chs:"额定放电电流, 单位A"},
                {section:"dcchargecurrent", chs:"额定快充电流, 单位A"},
                {section:"acchargecurrent", chs:"额定慢充电流, 单位A"},
            ],
            cap:60.0,
            dischargecurrent: 150.0,
            totalvoltage: 336,
            dcchargecurrent: 20.0,
            acchargecurrent: 20.0,
        },
        serialnum: 105,
        parallelnum: 1,
        celltempnum: 36,
        heattempnum: 0,
        poletempnum: 0,
        initsoc: 50,
        initsoh: 100,
    },
    SystemConnection:{
        notes:[
            {section:"bcu", chs:"BCU配置", comments:"主机描述."},
            {section:"bmus", chs:"BMU配置", comments:"从机描述"},
        ],

        bcu:{
            notes:[
                {section:"type", chs:"BCU类型", comments:'可选:"C600", "C601", "A600", "A601", "A602", "A603", "A650", "A651", "A652", "A653", "A660", "A661".'},
                {section:"battconn", chs:"电池连接", comments:"电池连接, 只有型号为A60X的时候有效, 长度与型号相关."},
                {section:"tempconn", chs:"温感连接", comments:"只有型号为A60X的时候有效, 长度与型号相关; C标识电池单体温感,P表示电池极柱温感,H表示加热片温感,0表示没有链接温感."},
            ],
            type:"A603",
            battconn:"111111111111_111111111111_111111111111_111111111111",
            tempconn:"CCCC_CCCC_CCCC_CCCC",
        },

        bmus:[
            {
                notes:[
                    {section:"type", chs:"BMU类型", comments:'可选:"M600", "M601", "M602", "M603".'},
                    {section:"battconn", chs:"电池连接", comments:"电池连接, 长度与型号相关."},
                    {section:"tempconn", chs:"温感连接", comments:"长度与型号相关; C标识电池单体温感,P表示电池极柱温感,H表示加热片温感,0表示没有链接温感."},
                ],
                type:"M603",
                battconn:"111111111111_111111111111_111111111111_111111111111_111111111000",
                tempconn:"000000_CCCC_CCCC_CCCC_CCCC_CCCC"
            }/*,{
                type:"M601",
                battconn:"110000110000_110000110000_110000110000",
                tempconn:"00C000_CC00_CC00_C0CC"
            },{
                type:"M601",
                battconn:"110000110000_110000110000_110000110000",
                tempconn:"00C000_CC00_CC00_C0CC"
            },{
                type:"M601",
                battconn:"110000110000_110000110000_110000110000",
                tempconn:"00C000_CC00_CC00_C0CC"
            },{
                type:"M601",
                battconn:"110000110000_110000110000_110000110000",
                tempconn:"00C000_CC00_CC00_C0CC"
            },{
                type:"M601",
                battconn:"110000110000_110000110000_110000110000",
                tempconn:"00C000_CC00_CC00_C0CC"
            },{
                type:"M601",
                battconn:"110000110000_110000110000_110000110000",
                tempconn:"00C000_CC00_CC00_C0CC"
            },{
                type:"M601",
                battconn:"110000110000_110000110000_110000110000",
                tempconn:"00C000_CC00_CC00_C0CC"
            },{
                type:"M601",
                battconn:"110000110000_110000110000_110000110000",
                tempconn:"00C000_CC00_CC00_C0CC"
            },{
                type:"M601",
                battconn:"110000110000_110000110000_110000110000",
                tempconn:"00C000_CC00_CC00_C0CC"
            },{
                type:"M601",
                battconn:"110000110000_110000110000_110000110000",
                tempconn:"00C000_CC00_CC00_C0CC"
            },{
                type:"M601",
                battconn:"110000110000_110000110000_110000110000",
                tempconn:"00C000_CC00_CC00_C0CC"
            },{
                type:"M601",
                battconn:"110000110000_110000110000_110000110000",
                tempconn:"00C000_CC00_CC00_C0CC"
            },{
                type:"M601",
                battconn:"110000110000_110000110000_110000110000",
                tempconn:"00C000_CC00_CC00_C0CC"
            },{
                type:"M601",
                battconn:"110000110000_110000110000_110000110000",
                tempconn:"00C000_CC00_CC00_C0CC"
            },{
                type:"M601",
                battconn:"110000110000_110000110000_110000110000",
                tempconn:"00C000_CC00_CC00_C0CC"
            }*/
        ]
    },

    ModelConfig: {
    },

    RuntimeM: {
        maxTimeForWaitTaskPowerdown: 10,
        wakeupTimeForOTA: 90,
        wakeupTimeForData: "02:00",
        maxOnTimeForOTA: 60*60,
        maxOnTimeForData: 60*5,
        minBatteryVolForWakeup: 10,
        chargeEndOTA: true,
        userIsWakeup: {func:"", inc: ""},
        cpInvalidTimeFilter: 10*60,
        powerOffNotifiers: [
            {func:"Soc_PowerDownSaveCbk", inc: "Soc.h"},
            {func:"Statistic_PowerDownSaveCbk", inc: "Statistic.h"},
            {func:"SaveM_PowerDownSaveCbk", inc: "SaveM.h"},
            {func:"UserStrategy_SaftyOff", inc: "UserStrategy.h"},
            {func:"ParameterM_SyncFinished", inc: "ParameterM.h"},
            {func:"ChargeConnectM_SaftyOff", inc: "ChargeConnectM.h"},
        ],

        maxTimeForWaitTaskPowerdown_comments: "下电等待的最大时间, 单位秒",
        wakeupTimeForOTA_comments: '收到升级请求之后, 多长时间(什么时刻)唤醒开始升级, 单位秒或者指定时刻:"02:00"',
        wakeupTimeForData_comments: '关机之后, 多长时间唤醒开始向后台发送数据, 单位秒或者指定时刻:"02:00"',
        maxOnTimeForOTA_comments: "唤醒发送数据最长的工作时间, 单位秒",
        maxOnTimeForData_comments: "唤醒升级据最长的工作时间, 单位秒",
        minBatteryVolForWakeup_comments: "唤醒要求的最低供电电压, 单位v",
        chargeEndOTA_comments: "是否支持充电完成之后进行OTA, 针对没有常电的情况, 配置成true之后, 不会唤醒进行数据传输与OTA",
        cpInvalidTimeFilter_comments: "CP唤醒信号无效的过滤时间，单位秒",
        powerOffNotifiers_comments: "下电时需要调用的函数",
    },

    CurrentM:{
        // HALL传感器配置
        hall1: {
            // 通道1
            notes:[
                {section:"model", chs:"传感器型号", comments:'可选: "DHAB_S124_1"(DHAB_S124大量程), "DHAB_S124_2"(DHAB_S124小量程), DHAB_S118_1"(DHAB_S118大量程), "DHAB_S118_2"(DHAB_S118小量程), DHAB_S133_1"(DHAB_S133大量程 750A), "DHAB_S133_2"(DHAB_S133小量程 75A), DHAB_S137_1"(DHAB_S137大量程 1000A), "DHAB_S137_2"(DHAB_S137小量程 75A), "FS300E2T"(飞轩FS300E2T,300A量程), "FS500E2T"(飞轩FS500E2T,500A量程), "FS600E2T"(飞轩FS600E2T,600A量程), "FS700E2T"(飞轩FS700E2T,700A量程), "FS1200_EK2T"(飞轩FS1200_EK2T,1200A量程), "FS1500_EK4T"(飞轩FS1500_EK4T,1500A量程), "FS2000_EK2T"(飞轩FS2000_EK2T,2000A量程), "WHK30_350DHAB5S2L_1"(启东双赢30/350A大量程), "WHK30_350DHAB5S2L_2"(启东双赢30/350A小量程), "EHMWX911C500"(松下EHMWX911C500,500A量程), "HAH1BVW_S01"(LEM 100A单量程),  "HAH1BVW_S02"(LEM 200A单量程), "HAH1BVW_S03"(LEM 300A单量程), "HAH1BV_S02"(LEM 500A单量程),'
                                                                    +'"HAH1BVW_S12"(LEM 1200A单量程), "WHK20BS5S2"(启东双赢 20A单量程), "WHK50BS5S2"(启东双赢 50A单量程), "FS300BT"(飞轩300A单量程), "FS600BT"(飞轩600A单量程), "WHK300EA5S2S"(启东双赢300A单量程), "WHK500EA5S2S"(启东双赢500A单量程), "CS1000BT5"(茶花港联1000A单量程)'},
                {section:"filterNum", chs:"滤波的采集次数"},
                {section:"dropNum", chs:"极值丢弃的个数"},
            ],
            model: "DHAB_S118_1",
            filterNum: 20,
            dropNum: 2,
            zeroFilterValue: 1,
            autoCalibLimit:10,
            isReverse: false,
        },

        hall2: {
            // 通道2
            model: "DHAB_S118_2",
            filterNum: 20,
            dropNum: 2,
            zeroFilterValue: 1,
            autoCalibLimit:10,
            isReverse: false,
        },

        // 分流器配置
        shunt: {
            notes:[
                {section:"model", chs:"传感器型号", comments:'可选:"WSBM8518L1000", "FL2200A25mV", "FL2300A25mV", "FL2300A50mV", "FL2400A50mV", "FL2500A50mV", "FL2600A50mV", "FL2650A50mV", "FL230A75mV", "FL250A75mV", "FL2100A75mV", "FL2150A75mV", "FL2200A75mV", "FL2250A75mV", "FL2300A75mV", "FL2400A75mV", "FL2500A75mV", "FL2600A75mV", "FL2650A75mV", "FL2750A75mV", "FL2800A75mV", "FL21000A75mV", "FL21200A75mV", "FL22000A75mV"'},
            ],
            model: "FL2200A75mV",
            zeroFilterValue: 0.2,
            autoCalibLimit:10,
            isReverse: false,
        },

        // 主回路电流采集
        main: {
            // 可选 "hall1", "hall2", "shunt", "userdef1", "userdef2"
            channel: "shunt", //注：若使用分流器，需要关闭电流的所有上电自检。
            // 可选 "hall1", "hall2", "shunt", "none", "userdef1", "userdef2" 但是不能与channel相同,
            redundant: "none"

        },
        // 加热回路电流采集
        heater: {
            // 可选 "hall1", "hall2", "shunt", "userdef1", "userdef2", "none"
            channel: "none",
            redundant: "none"
        },
    },

    RelayM: [
        {name: "主正", def: "POSITIVE_MAIN", model: "UNKNOWN", hlss: "HLSS_BCU_HSS1", isSafeToOff: "NULL", hv: "HV1", isPositive:true, totalDecPercent: 90, continueDecPercent: 10, checkInterval: 20, checkTimeout: 1000, auxContactDio: "", ioLevelOfAuxContactWhenOn: "HIGH"},
        {name: "充电", def: "CHARGE", model: "UNKNOWN", hlss: "HLSS_BCU_HSS2", isSafeToOff: "NULL", hv: "HV2", isPositive:true, totalDecPercent: 90, continueDecPercent: 10, checkInterval: 20, checkTimeout: 1000},
        {name: "预充", def: "PRECHARGE", model: "UNKNOWN", hlss: "HLSS_BCU_HSS4", isSafeToOff: "NULL", hv: "HV1", isPositive:true, totalDecPercent: 90, continueDecPercent: 10, checkInterval: 20, checkTimeout: 1000,  auxContactDio: "", ioLevelOfAuxContactWhenOn: "HIGH"},
        // {name: "显示屏", def: "HMI", model: "UNKNOWN", hlss: "HLSS_BCU_HSS4"},
        {name: "蜂鸣器", def: "BUZZER", model: "UNKNOWN", hlss: "HLSS_BCU_HSS3"},
        // {name: "加热", def: "HEATER", model: "UNKNOWN", hlss: "HLSS_BCU_HSS6"},
        // {name: "预留", def: "RESERVE", model: "UNKNOWN", hlss: "HLSS_BCU_HSS7"},
        //{name: "放电正", def: "POSITIVE_DISCHRGE", model: "UNKNOWN", hlss: "HLSS_BCU_HSS1", hv: "BPOS"},
        //{name: "放电负", def: "NEGTIVE_DISCHARGE", model: "UNKNOWN", hlss: "HLSS_BCU_HSS5"},
        //{name: "充电负", def: "NEGTIVE_CHARGE", model: "UNKNOWN", hlss: "HLSS_BCU_HSS6"},
        // {name: "制冷", def: "COOLER", model: "UNKNOWN", hlss: "HLSS_BCU_HSS7"},
    ],

    Charge: {
        dc: {
            notes:[
                {section:"wakeup", chs:"唤醒信号", comments:'可选:"NONE", "ON", "DCC"'},
                {section:"protocol", chs:"协议", comments:'可选:"NONE", "USER", "GB2015"'},
                {section:"mode", chs:"连接模式", comments:'可选:"NONE", "USER", "COMM", "DIN", "CURRENT", "GB_DC"'},
                {section:"dintype", chs:"数字输入类型", comments:'只有mode为"DIN"时可用, 可选:"LEVEL", "SW", "WAKEUP_SIGNAL"'},
                {section:"dinChannel", chs:"数字输入通道", comments:'可选:"BCU_DIN1", "BCU_DIN2", "BCU_SW1", "BCU_SW2", "OBC", "DCC"'},
                {section:"userModeFunction", chs:"自定义充电连接", comments:'当mode为"USER"时，提供一个获取连接模式的头文件和函数'}
            ],
            wakeup: "DCC",
            protocol: "USER",
            mode: "GB_DC",
            dintype: "LEVEL",
            dinChannel: "BCU_DIN1",
            relay: "充电",
            userModeFunction: ["UserStrategy.h", "UserStrategy_DCConnected"],
        },

        dc2: {
            notes:[
                {section:"wakeup", chs:"唤醒信号", comments:'可选:"NONE", "ON", "OBC", "DCC"'},
                {section:"protocol", chs:"协议", comments:'可选:"NONE", "GB2015"'},
                {section:"mode", chs:"连接模式", comments:'可选:"NONE", "USER", "COMM", "DIN", "CURRENT", "GB_DC", "GB_MODE1_CONNECT_B", "GB_MODE2_CONNECT_B", "GB_MODE3_CONNECT_A", "GB_MODE3_CONNECT_B", "GB_MODE3_CONNECT_C"'},
                {section:"dintype", chs:"数字输入类型", comments:'只有mode为"DIN"时可用, 可选:"LEVEL", "SW", "WAKEUP_SIGNAL"'},
                {section:"dinChannel", chs:"数字输入通道", comments:'可选:"BCU_DIN1", "BCU_DIN2", "BCU_SW1", "BCU_SW2", "OBC", "DCC"'},
                {section:"userModeFunction", chs:"自定义充电连接", comments:'当mode为"USER"时，提供一个获取连接模式的头文件和函数'}
            ],
            wakeup: "NONE",
            protocol: "GB2015",
            mode: "NONE",
            dintype: "LEVEL",
            dinChannel: "BCU_DIN1",
            relay: "",
            userModeFunction: ["UserStrategy.h", "UserStrategy_DC2Connected"],
        },

        ac: {
            notes:[
                {section:"wakeup", chs:"唤醒信号", comments:'可选:"NONE", "ON", "CP", "OBC"'},
                {section:"protocol", chs:"协议", comments:'可选:"NONE", "USER", "GB2015"'},
                {section:"mode", chs:"连接模式", comments:'可选:"NONE", "USER", COMM", "DIN", "CURRENT", "GB_MODE1_CONNECT_B", "GB_MODE2_CONNECT_B", "GB_MODE3_CONNECT_A", "GB_MODE3_CONNECT_B", "GB_MODE3_CONNECT_C"'},
                {section:"dintype", chs:"数字输入类型", comments:'只有mode为"DIN"时可用, 可选:"LEVEL", "SW", "WAKEUP_SIGNAL"'},
                {section:"dinChannel", chs:"数字输入通道", comments:'可选:"BCU_DIN1", "BCU_DIN2", "BCU_SW1", "BCU_SW2", "OBC", "DCC"'},
                {section:"userModeFunction", chs:"自定义充电连接", comments:'当mode为"USER"时，提供一个获取连接模式的函数'}
            ],
            wakeup: "OBC",
            protocol: "USER",
            mode: "NONE",
            dintype: "LEVEL",
            dinChannel: "BCU_DIN2",
            relay: "",
            userModeFunction: ["UserStrategy.h", "UserStrategy_ACConnected"],
        },

        el: {
            enable: 0,
            driveType: "HBridge",
            driveType_comments: '驱动模式, 可选:"HBridge", "LowLevel", "HighLevel"',
            lockTime: 1,
            lockTime_comments: "锁止操作时间, 单位秒",
            unlockTime: 1,
            unlockTime_comments: "解锁操作时间, 单位秒",
            lockFeedback:['EL_FEEDBACK', 'HIGH'],
            lockFeedback_comments: "锁止时检查的DIO及状态",
            unlockFeedback:['EL_FEEDBACK', 'LOW'],
            unlockFeedback_comments: "解锁时检查的DIO及状态",
            ctlMax: 3,
            ctlMax_comments: "电子锁驱动最大驱动次数，大于1时驱动失败后会自动重试",
        }
    },

    Ntc: {
        //可选 "Shiheng_CWF4B_103F_3435B":时恒10K; "Soarwhale_10K3435B":由甲申田10K; "Kemit_CWF110KF3435":科敏10K; "Kemit_CWF110KF4150":科敏10K; Yonggui_YG691_51_00_50":永贵10K; "Shiheng_CWF4B_104F_3950":时恒100K; "MTG2_420F103H":MTG2_10K; "Kemit_CWF110KF3950":科敏10K; "BoDian_FW10K3950":铂电10K; "Soarwhale_SW_NTC_C4_103B1A1":由甲申田10K;
        //     "Shiheng_CWF4B_103F_3950":时恒10K; "Microtherm_TR29_NTC_ALW600_D3_2L15":麦柯泰姆10K; "Microtherm_RT29_NTC_ALW500_D3_2L15":麦柯泰姆100K-3950; "YiDa_BLMF103F3435F":苏州怡达10K; "CATL_10K_SMD":CATL 10K; "XLB_SK103F4R0300ST": 新立本10K; "Soarwhale_SW_NTC_104F_3590": 由甲申田100K; "Semitec_104KT1608_1P": Semitec100K; "TPS2_395F103F_150"：特普生10K；
        //     "Semitec_103KT1005_1P": Semitec10K; "Unknown1_10KRT13950": Unknown1 10K; "Karmo_KN1MF12140410_L400": 科润美10K; "Unknown2_10K_3950": Unknown2 10K; "Kemit_CWF1100KF4150": 科敏100K; "Thinking_NTSA3104FV057": 兴勤100K; "Ampron_APR_CWF103F3950FA250A": 安培龙10K;
        //     "PT1000_10K": PT1000, 10K下拉电阻分压; "PT1000_1K": PT1000, 1K下拉电阻分压; "HuaiDian_HA103F4R22": 淮电10K; "Kemit_CWF110KF3950_369ohm":科敏10K; "Kedite_MF5_4_103F3435F100MM": 科帝特10K; "WeiLian_TR29N313A4EL50": 上海维连100K; "Kedite_103F3950F100C": 科帝特10K; "TPS2_395F104F_150": 特普生100K;

        cellTempType: "XLB_SK103F4R0300ST", // 电池温感型号
        dcChgSckTempType:'Shiheng_CWF4B_103F_3435B', // 快充充电插座温感信号
        acChgSckTempType:'Shiheng_CWF4B_103F_3435B', // 慢充充电插座温感信号
        chgSckTempMap: {
            //SCH_T1,SCH_T2,SCH_T3,FCH_T1,FCH_T2,OFF
            AC_AL: 'OFF',
            AC_BN: 'OFF',
            AC_C: 'OFF',
            DC_POSITIVE: 'OFF',
            DC_NEGATIVE: 'OFF',
        }
    },

    BalanceM: {
        Charging: {
            enable: 1, // 是否使能
            startVoltage: 3500, // 开启电压
            minVoltage: 2700, // 开启最小电压
            minDiffVoltage: 10, // 开启的最小压差
            maxDiffVoltage: 800, // 开启的最大压差
        },

        Static: {
            enable: 0, // 是否使能
            startVoltage: 3500, // 开启电压
            minVoltage: 2700, // 开启最小电压
            minDiffVoltage: 10, // 开启的最小压差
            maxDiffVoltage: 800, // 开启的最大压差
        },
        Remote: {
            enable: 1, // 是否使能
            condition:{inc:"UserStrategy.h", func:"UserStrategy_RemoteBalanceConditionCheck"},
            enableDefaultBalanceTime:12*3600,//连续超过该时间没有接收到远程均衡指令，就打开默认均衡，单位S
        }
    },

    PwmCapture: {
        funcIncude: ['UserStrategy.h'],
        CP: {
            enable: true,
            risingFunc: '',
            fallingFunc: '',
        },

        SIGIN1: {
            enable: false, // 是否开启SIGIN1的占空比检测
            risingFunc: 'UserStrategy_CheckSRS', // 检测到上升沿调用的函数
            fallingFunc: '',  // 检测到下降沿调用的函数，如果与上升沿同一个函数，在函数里面可以判断沿
        },

        SIGIN2: {
            enable: false,
            risingFunc: '',
            fallingFunc: '',
        } // 请参考SIGIN2的注释
    },

    Diagnosis: {
        levelsupport: 4,
        configs: [
            {
                name: "充电单体电压高",
                levels: [2,3],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "SocDiagCalib_FullCalibCbk"},
                    {levels:[3], event: "deassert", action: "SocDiagCalib_FullCalibRelCbk"},
                    {levels:[3], event: "assert", action: "ChargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "ChargeM_DiagnosisCtlEnableEventCbk"},
                ],
                startDiagnosis: {
                    timeout: 1000,
                    level: 3,
                    events: [
                        {event: "assert", action: "ChargeM_StartDiagCtlDisableEventCbk"},
                        {event: "deassert", action: "ChargeM_StartDiagCtlEnableEventCbk"},
                    ],
                },
            }, {
                name: "放电单体电压高",
                levels: [3],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "DischargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "DischargeM_DiagnosisCtlEnableEventCbk"},
                ],
                startDiagnosis: {
                    timeout: 1000,
                    level: 3,
                    events:[
                        {event:"assert", action: "DischargeM_StartDiagCtlDisableEventCbk"},
                        {event:"deassert", action: "DischargeM_StartDiagCtlEnableEventCbk"},
                    ],
                },
            },{
                name: "充电单体电压低",
                levels: [3],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "ChargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "ChargeM_DiagnosisCtlEnableEventCbk"},
                ],
                startDiagnosis: {
                    timeout: 1000,
                    level: 3,
                    events: [
                        {event: "assert", action: "ChargeM_StartDiagCtlDisableEventCbk"},
                        {event: "deassert", action: "ChargeM_StartDiagCtlEnableEventCbk"},
                    ],
                },
            },{
                name: "放电单体电压低",
                levels: [2,3],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "SocDiagCalib_EmptyCalibCbk"},
                    {levels:[3], event: "deassert", action: "SocDiagCalib_EmptyCalibRelCbk"},
                    {levels:[3], event: "assert", action: "DischargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "DischargeM_DiagnosisCtlEnableEventCbk"},
                ],
                startDiagnosis: {
                    timeout: 1000,
                    level: 3,
                    events: [
                        {event: "assert", action: "DischargeM_StartDiagCtlDisableEventCbk"},
                        {event: "deassert", action: "DischargeM_StartDiagCtlEnableEventCbk"},
                    ],
                },
            }, {
                name: "充电总压高",
                levels: [2,3],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "SocDiagCalib_FullCalibCbk"},
                    {levels:[3], event: "deassert", action: "SocDiagCalib_FullCalibRelCbk"},
                    {levels:[3], event: "assert", action: "ChargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "ChargeM_DiagnosisCtlEnableEventCbk"},
                ],
                startDiagnosis: {
                    timeout: 1000,
                    level: 3,
                    events: [
                        {event: "assert", action: "ChargeM_StartDiagCtlDisableEventCbk"},
                        {event: "deassert", action: "ChargeM_StartDiagCtlEnableEventCbk"},
                    ],
                },
            }, {
                name: "放电总压高",
                levels: [3],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "DischargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "DischargeM_DiagnosisCtlEnableEventCbk"},
                ],
                startDiagnosis: {
                    timeout: 1000,
                    level: 3,
                    events:[
                        {event:"assert", action: "DischargeM_StartDiagCtlDisableEventCbk"},
                        {event:"deassert", action: "DischargeM_StartDiagCtlEnableEventCbk"},
                    ],
                },
            },{
                name: "充电总压低",
                levels: [3],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "ChargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "ChargeM_DiagnosisCtlEnableEventCbk"},
                ],
                startDiagnosis: {
                    timeout: 1000,
                    level: 3,
                    events: [
                        {event: "assert", action: "ChargeM_StartDiagCtlDisableEventCbk"},
                        {event: "deassert", action: "ChargeM_StartDiagCtlEnableEventCbk"},
                    ],
                },
            },{
                name: "放电总压低",
                levels: [2,3],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "SocDiagCalib_EmptyCalibCbk"},
                    {levels:[3], event: "deassert", action: "SocDiagCalib_EmptyCalibRelCbk"},
                    {levels:[3], event: "assert", action: "DischargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "DischargeM_DiagnosisCtlEnableEventCbk"},
                ],
                startDiagnosis: {
                    timeout: 1000,
                    level: 3,
                    events:[
                        {event: "assert", action: "DischargeM_StartDiagCtlDisableEventCbk"},
                        {event: "deassert", action: "DischargeM_StartDiagCtlEnableEventCbk"},
                    ],
                },
            }, {
                name: "充电单体压差",
                levels: [2],
                cycle: 100,
                // events: [
                //     {levels:[3], event: "assert", action: "ChargeM_DiagnosisCtlDisableEventCbk"},
                //     {levels:[3], event: "deassert", action: "ChargeM_DiagnosisCtlEnableEventCbk"},
                // ],
                // startDiagnosis: {
                //     timeout: 1000,
                //     level: 3,
                //     events:[
                //         {event: "assert", action: "ChargeM_StartDiagCtlDisableEventCbk"},
                //         {event: "deassert", action: "ChargeM_StartDiagCtlEnableEventCbk"},
                //     ],
                // },
            }, {
                name: "放电单体压差",
                levels: [2],
                cycle: 100,
                // events: [
                //     {levels:[3], event: "assert", action: "DischargeM_DiagnosisCtlDisableEventCbk"},
                //     {levels:[3], event: "deassert", action: "DischargeM_DiagnosisCtlEnableEventCbk"},
                // ],
                // startDiagnosis: {
                //     timeout: 1000,
                //     level: 3,
                //     events:[
                //         {event:"assert", action: "DischargeM_StartDiagCtlDisableEventCbk"},
                //         {event:"deassert", action: "DischargeM_StartDiagCtlEnableEventCbk"},
                //     ],
                // },
            },{
                name: "充电总压压差",
                levels: [],
                cycle: 100,
            },{
                name: "放电总压压差",
                levels: [],
                cycle: 100,
            },{
                name: "充电高温",
                levels: [2,3],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "ChargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "ChargeM_DiagnosisCtlEnableEventCbk"},
                ],
                startDiagnosis: {
                    timeout: 1000,
                    level: 3,
                    events:[
                        {event: "assert", action: "ChargeM_StartDiagCtlDisableEventCbk"},
                        {event: "deassert", action: "ChargeM_StartDiagCtlEnableEventCbk"},
                    ],
                },
            }, {
                name: "放电高温",
                levels: [2,3],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "DischargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "DischargeM_DiagnosisCtlEnableEventCbk"},
                ],
                startDiagnosis: {
                    timeout: 1000,
                    level: 3,
                    events:[
                        {event: "assert", action: "DischargeM_StartDiagCtlDisableEventCbk"},
                        {event: "deassert", action: "DischargeM_StartDiagCtlEnableEventCbk"},
                    ],
                },
            },{
                name: "充电低温",
                levels: [2,3],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "ChargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "ChargeM_DiagnosisCtlEnableEventCbk"},
                ],
                startDiagnosis: {
                    timeout: 1000,
                    level: 3,
                    events:[
                        {event: "assert", action: "ChargeM_StartDiagCtlDisableEventCbk"},
                        {event: "deassert", action: "ChargeM_StartDiagCtlEnableEventCbk"},
                    ],
                },
            }, {
                name: "放电低温",
                levels: [2,3],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "DischargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "DischargeM_DiagnosisCtlEnableEventCbk"},
                ],
                startDiagnosis: {
                    timeout: 1000,
                    level: 3,
                    events:[
                        {event:"assert", action: "DischargeM_StartDiagCtlDisableEventCbk"},
                        {event:"deassert", action: "DischargeM_StartDiagCtlEnableEventCbk"},
                    ],
                },
            },{
                name: "充电温差",
                levels: [2,3],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "ChargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "ChargeM_DiagnosisCtlEnableEventCbk"},
                ],
                startDiagnosis: {
                    timeout: 1000,
                    level: 3,
                    events:[
                        {event: "assert", action: "ChargeM_StartDiagCtlDisableEventCbk"},
                        {event: "deassert", action: "ChargeM_StartDiagCtlEnableEventCbk"},
                    ],
                },
            }, {
                name: "放电温差",
                levels: [2,3],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "DischargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "DischargeM_DiagnosisCtlEnableEventCbk"},
                ],
                startDiagnosis: {
                    timeout: 1000,
                    level: 3,
                    events:[
                        {event:"assert", action: "DischargeM_StartDiagCtlDisableEventCbk"},
                        {event:"deassert", action: "DischargeM_StartDiagCtlEnableEventCbk"},
                    ],
                },
            },{
                name: "快充过流",
                levels: [2,3],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "ChargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "ChargeM_DiagnosisCtlEnableEventCbk"},
                ],
            },{
                name: "慢充过流",
                levels: [],
                cycle: 100,
            },{
                name: "回馈过流",
                levels: [],
                cycle: 100,
                events: [
                ],
            },{
                name: "持续放电过流",
                levels: [2,3],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "DischargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "DischargeM_DiagnosisCtlEnableEventCbk"},
                ],
            },{
                name: "瞬时放电过流",
                levels: [],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "DischargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "DischargeM_DiagnosisCtlEnableEventCbk"},
                ],
            },{
                name: "充电电流异常",
                levels: [],
                cycle: 100,
            },{
                name: "SOC过高",
                levels: [],
                cycle: 100,
                events: [
                ],
            },{
                name: "SOC过低",
                levels: [2],
                cycle: 100,
                events: [
                ],
            },{
                name: "绝缘漏电",
                levels: [],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "DischargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "DischargeM_DiagnosisCtlEnableEventCbk"},
                    {levels:[3], event: "assert", action: "ChargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "ChargeM_DiagnosisCtlEnableEventCbk"},
                ],
            },{
                name: "电压排线脱落",
                levels: [2,3],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "DischargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "DischargeM_DiagnosisCtlEnableEventCbk"},
                    {levels:[3], event: "assert", action: "ChargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "ChargeM_DiagnosisCtlEnableEventCbk"},
                ],
                startDiagnosis: {
                    timeout: 1000,
                    level: 3,
                    events:[
                        {event:"assert", action: "DischargeM_StartDiagCtlDisableEventCbk"},
                        {event:"deassert", action: "DischargeM_StartDiagCtlEnableEventCbk"},
                        {event:"assert", action: "ChargeM_StartDiagCtlDisableEventCbk"},
                        {event:"deassert", action: "ChargeM_StartDiagCtlEnableEventCbk"},
                    ],
                },
            },{
                name: "温感排线脱落",
                levels: [2,3],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "DischargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "DischargeM_DiagnosisCtlEnableEventCbk"},
                    {levels:[3], event: "assert", action: "ChargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "ChargeM_DiagnosisCtlEnableEventCbk"},
                ],
                startDiagnosis: {
                    timeout: 1000,
                    level: 3,
                    events:[
                        {event:"assert", action: "DischargeM_StartDiagCtlDisableEventCbk"},
                        {event:"deassert", action: "DischargeM_StartDiagCtlEnableEventCbk"},
                        {event:"assert", action: "ChargeM_StartDiagCtlDisableEventCbk"},
                        {event:"deassert", action: "ChargeM_StartDiagCtlEnableEventCbk"},
                    ],
                },
            },{
                name: "内网通信",
                levels: [3],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "DischargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "DischargeM_DiagnosisCtlEnableEventCbk"},
                    {levels:[3], event: "assert", action: "ChargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "ChargeM_DiagnosisCtlEnableEventCbk"},
                ],
                startDiagnosis: {
                    timeout: 1000,
                    level: 3,
                    events:[
                        {event:"assert", action: "DischargeM_StartDiagCtlDisableEventCbk"},
                        {event:"deassert", action: "DischargeM_StartDiagCtlEnableEventCbk"},
                        {event:"assert", action: "ChargeM_StartDiagCtlDisableEventCbk"},
                        {event:"deassert", action: "ChargeM_StartDiagCtlEnableEventCbk"},
                    ],
                },
            },{
                name: "快充正极高温",
                levels: [],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "ChargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "ChargeM_DiagnosisCtlEnableEventCbk"},
                ],
                startDiagnosis: {
                    timeout: 1000,
                    level: 3,
                    events:[
                        {event: "assert", action: "ChargeM_StartDiagCtlDisableEventCbk"},
                        {event: "deassert", action: "ChargeM_StartDiagCtlEnableEventCbk"},
                    ],
                },
            },{
                name: "快充负极高温",
                levels: [],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "ChargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "ChargeM_DiagnosisCtlEnableEventCbk"},
                ],
                startDiagnosis: {
                    timeout: 1000,
                    level: 3,
                    events:[
                        {event: "assert", action: "ChargeM_StartDiagCtlDisableEventCbk"},
                        {event: "deassert", action: "ChargeM_StartDiagCtlEnableEventCbk"},
                    ],
                },
            },{
                name: "慢充AL极高温",
                levels: [],
                cycle: 100,
                events: [
                ],
            },{
                name: "慢充BN极高温",
                levels: [],
                cycle: 100,
                events: [
                ],
            },{
                name: "慢充C极高温",
                levels: [],
                cycle: 100,
                events: [
                ],
            },{
                name: "充电加热高温",
                levels: [],
                cycle:100,
            }, {
                name: "放电加热高温",
                levels: [],
                cycle:100,
            }, {
                name: "充电加热温差",
                levels: [],
                cycle:100,
            }, {
                name: "放电加热温差",
                levels: [],
                cycle:100,
            }, {
                name: "充电加热超时",
                levels: [],
                cycle:100,
            }, {
                name: "放电加热超时",
                levels: [],
                cycle:100,
            }, {
                name: "充电加热过流",
                levels: [],
                cycle: 100,
            },{
                name: "放电加热过流",
                levels: [],
                cycle: 100,
            },{
                name: "SOC跳变",
                levels: [],
                cycle: 100,
            },{
                name: "供电电压过低",
                levels: [],
                cycle: 500,
            },{
                name: "供电电压过高",
                levels: [],
                cycle:500,
            }, {
                name: "供电电压异常",
                levels: [],
                cycle:500,
            }, {
                name: "充电极柱高温",
                levels: [],
                cycle: 100,
            },{
                name: "放电极柱高温",
                levels: [],
                cycle: 100,
            },{
                name: "充电极柱温差",
                levels: [],
                cycle: 100,
            },{
                name: "放电极柱温差",
                levels: [],
                cycle: 100,
            },{
                name: "充电机通信",
                levels: [3],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "ChargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "ChargeM_DiagnosisCtlEnableEventCbk"},
                ],
                startDiagnosis: {
                    timeout: 1000,
                    level: 3,
                    events:[
                        {event: "assert", action: "ChargeM_StartDiagCtlDisableEventCbk"},
                        {event: "deassert", action: "ChargeM_StartDiagCtlEnableEventCbk"},
                    ],
                },
            },{
                name: "整车通信",
                levels: [],
                cycle: 100,
                events: [
                ],
            },{
                name: "满充",
                levels: [],
                cycle: 100,
            },{
                name: "充电插座温感异常",
                levels: [2,3],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "ChargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "ChargeM_DiagnosisCtlEnableEventCbk"},
                ],
                startDiagnosis: {
                    timeout: 1000,
                    level: 3,
                    events:[
                        {event: "assert", action: "ChargeM_StartDiagCtlDisableEventCbk"},
                        {event: "deassert", action: "ChargeM_StartDiagCtlEnableEventCbk"},
                    ],
                },
            },{
                name: "预充失败",
                levels: [3],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "DischargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "DischargeM_DiagnosisCtlEnableEventCbk"},
                ],
                startDiagnosis: {
                    timeout: 1000,
                    level: 3,
                    events:[
                        {event: "assert", action: "DischargeM_StartDiagCtlDisableEventCbk"},
                        {event: "deassert", action: "DischargeM_StartDiagCtlEnableEventCbk"},
                    ],
                },
            },{
                name: "电流异常",
                levels: [3],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "DischargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "DischargeM_DiagnosisCtlEnableEventCbk"},
                    {levels:[3], event: "assert", action: "ChargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "ChargeM_DiagnosisCtlEnableEventCbk"},
                ],
            },{
                name: "BMS初始化故障",
                levels: [3],
                cycle: 100,
                events: [
                    {levels:[3], event: "assert", action: "DischargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "DischargeM_DiagnosisCtlEnableEventCbk"},
                    {levels:[3], event: "assert", action: "ChargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "ChargeM_DiagnosisCtlEnableEventCbk"},
                ],
                startDiagnosis: {
                    timeout: 1000,
                    level: 3,
                    events:[
                        {event:"assert", action: "DischargeM_StartDiagCtlDisableEventCbk"},
                        {event:"deassert", action: "DischargeM_StartDiagCtlEnableEventCbk"},
                        {event:"assert", action: "ChargeM_StartDiagCtlDisableEventCbk"},
                        {event:"deassert", action: "ChargeM_StartDiagCtlEnableEventCbk"},
                    ],
                },
            }, {
                name: "HVIL故障",
                levels: [],
                cycle: 50,
                events: [
                ],
            },{
                name: "继电器故障",
                levels: [3],
                cycle: 50,
                events: [
                    {levels:[3], event: "assert", action: "DischargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "DischargeM_DiagnosisCtlEnableEventCbk"},
                    {levels:[3], event: "assert", action: "ChargeM_DiagnosisCtlDisableEventCbk"},
                    {levels:[3], event: "deassert", action: "ChargeM_DiagnosisCtlEnableEventCbk"},
                ],
                startDiagnosis: {
                    timeout: 1000,
                    level: 3,
                    events:[
                        {event:"assert", action: "DischargeM_StartDiagCtlDisableEventCbk"},
                        {event:"deassert", action: "DischargeM_StartDiagCtlEnableEventCbk"},
                        {event:"assert", action: "ChargeM_StartDiagCtlDisableEventCbk"},
                        {event:"deassert", action: "ChargeM_StartDiagCtlEnableEventCbk"},
                    ],
                },
            }, {
                name: "加热故障",
                levels: [],
                cycle: 100,
                events: [
                ],
            },{
                name: "CC2连接故障",
                levels: [],
                cycle: 100,
            },{
                name: "CC连接故障",
                levels: [],
                cycle: 100,
            },{
                name: "CP连接故障",
                levels: [],
                cycle: 100,
            },{
                name: "加热温感异常",
                levels: [],
                cycle: 100,
            },{
                name: "极柱温感异常",
                levels: [],
                cycle: 100,
            },{
                name: "电子锁故障",
                levels: [],
                cycle: 100,
            },{
                name: "多充电连接故障",
                levels: [],
                cycle: 100,
            },{
                name: "电池数不匹配",
                levels: [],
                cycle:100,
            }, {
                name: "温感数不匹配",
                levels: [],
                cycle:100,
            }, {
                name: "碰撞故障",
                levels: [],
                cycle: 50,
                events: [
                ],
            },
        ],
    },

    ParameterM: {
        Diagnosis: [
            {
                name: "电压排线脱落",
                levels_comment: "配置格式 [1, 1, 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                    [1, 1, 5, 30],
                    [1, 1, 5, 30],
                    [1, 0, 30, 5]
                ]
            }, {
                name: "温感排线脱落",
                levels_comment: "配置格式 [1, 1, 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                    [1, 1, 5, 30],
                    [1, 1, 5, 30],
                    [1, 0, 30, 5]
                ]
            }, {
                name: "内网通信",
                levels_comment: "配置格式 [1, 1, 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                    [1, 0, 5, 3],
                    [1, 0, 5, 3],
                    [1, 0, 5, 3]
                ]
            }, {
                name: "快充正极高温",
                levels_comment: "配置格式 [触发阈值(℃), 释放阈值(℃), 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                    // [75, 70, 5, 3],
                    // [75, 70, 5, 3],
                    // [85, 205, 5, 5]
                ]
            }, {
                name: "快充负极高温",
                levels_comment: "配置格式 [触发阈值(℃), 释放阈值(℃), 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                    // [75, 70, 5, 3],
                    // [75, 70, 5, 3],
                    // [85, 205, 5, 5]
                ]
            }, {
                name: "慢充AL极高温",
                levels_comment: "配置格式 [触发阈值(℃), 释放阈值(℃), 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                ]
            }, {
                name: "慢充BN极高温",
                levels_comment: "配置格式 [触发阈值(℃), 释放阈值(℃), 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                ]
            }, {
                name: "慢充C极高温",
                levels_comment: "配置格式 [触发阈值(℃), 释放阈值(℃), 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                ]
            }, {
                name: "充电机通信",
                levels_comment: "配置格式 [1, 1, 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                    [1, 1, 5, 1],
                    [1, 1, 5, 1],
                    [1, 1, 5, 1]
                ]
            }, {
                name: "整车通信",
                levels_comment: "配置格式 [1, 1, 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                ]
            }, {
                name: "满充",
                levels_comment: "配置格式 [1, 1, 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                ]
            }, {
                name: "充电插座温感异常",
                levels_comment: "配置格式 [1, 1, 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                    // [1, 1, 5, 30],
                    // [1, 1, 5, 30],
                    // [1, 0, 30, 5]
                ]
            }, {
                name: "预充失败",
                levels_comment: "配置格式 [1, 1, 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                    [1, 0, 2, 5],
                    [1, 0, 2, 5],
                    [1, 0, 2, 5]
                ]
            }, {
                name: "电流异常",
                levels_comment: "配置格式 [1, 1, 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                    [1, 1, 5, 5],
                    [1, 1, 5, 5],
                    [1, 1, 5, 5]
                ]
            }, {
                name: "BMS初始化故障",
                levels_comment: "配置格式 [1, 1, 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                    [1, 1, 5, 5],
                    [1, 1, 5, 5],
                    [1, 1, 5, 5]
                ]
            }, {
                name: "HVIL故障",
                levels_comment: "配置格式 [1, 1, 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                ]
            }, {
                name: "继电器故障",
                levels_comment: "配置格式 [1, 1, 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                    [1, 0, 2, 1],
                    [1, 0, 2, 1],
                    [1, 0, 2, 1]
                ]
            }, {
                name: "加热故障",
                levels_comment: "配置格式 [1, 1, 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                ]
            }, {
                name: "CC2连接故障",
                levels_comment: "配置格式 [1, 1, 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                ]
            }, {
                name: "CC连接故障",
                levels_comment: "配置格式 [1, 1, 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                ]
            }, {
                name: "CP连接故障",
                levels_comment: "配置格式 [1, 1, 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                ]
            }, {
                name: "加热温感异常",
                levels_comment: "配置格式 [1, 1, 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                ]
            }, {
                name: "极柱温感异常",
                levels_comment: "配置格式 [1, 1, 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                ]
            }, {
                name: "电子锁故障",
                levels_comment: "配置格式 [1, 1, 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                ]
            }, {
                name: "多充电连接故障",
                levels_comment: "配置格式 [1, 1, 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                ]
            }, {
                name: "电池数不匹配",
                levels_comment: "配置格式 [1, 1, 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                ]
            }, {
                name: "温感数不匹配",
                levels_comment: "配置格式 [1, 1, 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                ]
            }, {
                name: "供电电压异常",
                levels_comment: "配置格式 [1, 1, 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                ]
            }, {
                name: "碰撞故障",
                levels_comment: "配置格式 [1, 1, 触发持续时间(s), 释放持续时间(s)]",
                levels:[
                ]
            }
        ]
    },

    CanDrv:[
        {
            notes:[
                {section:"hw", chs:"硬件单元", comments:"硬件Can控制器单元."},
                {section:"baud", chs:"波特率", comments:"125000,250000,500000,1000000."},
                {section:"bor_time", chs:"busoff 自恢复时间", comments:"0:autorecovery, 单位 ms"},
            ],
            hw:0, baud:250000,
        },

        {hw:1, baud: 125000},
        {hw:2, baud: 250000},
        {hw:3, baud: 250000},
    ],



    /* CanIf层可以接收的Id列表, 从机的Id会自动根据从机个数添加, 这里不需要配置 */
    CanIf:{
        notes:[
            {section:"rxsduids", chs:"接收SDUID配置", comments:'上层使用CanIf接收的SDUID配置'},
            {section:"txsduids", chs:"发送SDUID配置", comments:'上层使用CanIf发送的SDUID配置'},
        ],
        rxsduids:[
            {
                notes:[
                    {section:"name", chs:"SDUID名称", comments:'该值会传给上层的RxIndication'},
                    {section:"to", chs:"上层模块名称", comments:'假设定义成"XXX", 接收到数据时调用XXX_RxIndication'},
                    {section:"id", chs:"CanId", comments:'接收指定的CanId'},
                    {section:"hw", chs:"硬件Can控制器", comments:'接收使用的硬件Can控制器'},
                    {section:"define", chs:"SDUID的值", comments:"该值会传给上层的RxIndication"},

                ],
                name:"CANIF_RX_CANTERMIO",
                to:"CanTermio",
                id:0x7fe,
                hw:0,
                define:0,
            },
            {name:"CANIF_RX_RUNTIMEM", to:"RuntimeM", id:0x7fd, hw:0, define:0},
            {name:"CANIF_RX_CANECHO_0", to:"CanEcho", id:0x7f0, hw:1, define:0},
            {name:"CANIF_RX_CANECHO_1", to:"CanEcho", id:0x7f1, hw:2, define:1},
            {name:"CANIF_RX_CANECHO_2", to:"CanEcho", id:0x7f2, hw:3, define:2},
            //{name:"CANIF_RX_USERCURRENTSENSOR_1", to:"UserCurrentSensor", id:0x3c0, hw:3, define:0},
            //{name:"CANIF_RX_USERCURRENTSENSOR_2", to:"UserCurrentSensor", id:0x3c1, hw:3, define:1},
        ],
        txsduids:[
            {
                notes:[
                    {section:"name", chs:"SDUID名称", comments:'该值用于上层传给CanIf_Transmit'},
                    {section:"to", chs:"上层模块名称", comments:'假设定义成"XXX", 接收到数据时调用XXX_TxComfirmation'},
                    {section:"id", chs:"CanId", comments:'接收指定的CanId'},
                    {section:"hw", chs:"硬件Can控制器", comments:'接收使用的硬件Can控制器'},
                ],
                name:"CANIF_TX_CANTERMIO",
                from:"CanTermio",
                id:0x7fe,
                hw:0
            },
            {name:"CANIF_TX_RUNTIMEM", from:"RuntimeM", id:0x7fd, hw:0},
            {name:"CANIF_TX_CANECHO_0", from:"CanEcho", id:0x7f0, hw:1},
            {name:"CANIF_TX_CANECHO_1", from:"CanEcho", id:0x7f1, hw:2},
            {name:"CANIF_TX_CANECHO_2", from:"CanEcho", id:0x7f2, hw:3},
        ]
    },

    /* CanTp层的配置, 从机通信会自动根据从机个数添加, 这里不需要配置  */
    CanTp:[
        {
            notes:[
                {section:"name", chs:"SDUID名称", comments:'该值PDUR的配置'},
                {section:"ch", chs:"CanTp通道", comments:'指定使用的CanTp通道'},
                {section:"rx", chs:"接收CanId", comments:'接收CanId'},
                {section:"tx", chs:"发送CanId", comments:'发送CanId'},
                {section:"hw", chs:"硬件Can控制器", comments:'接收使用的硬件Can控制器'},
            ],
            name:"UdsPhy",
            ch:0,
            rx:0x740,
            tx:0x748,
            hw:0
        },
        {name:"UdsFunc", ch:0, rx:0x7df, hw:0},
    ],

    /* J1930Tp的配置*/
    J1939Tp:[
        {
            name:"Charger",
            self:0xf4,
            remote:0x56,
            hw:1,
            pgs:[
                { pri:6, pgn: 0x2700, type:"tx"},
                { pri:7, pgn: 0x0200, type:"tx"},
                { pri:7, pgn: 0x0600, type:"tx"},
                { pri:4, pgn: 0x0900, type:"tx"},
                { pri:6, pgn: 0x1000, type:"tx"},
                { pri:7, pgn: 0x1100, type:"tx"},
                { pri:6, pgn: 0x1300, type:"tx"},
                { pri:7, pgn: 0x1500, type:"tx"},
                { pri:7, pgn: 0x1600, type:"tx"},
                { pri:7, pgn: 0x1700, type:"tx"},
                { pri:4, pgn: 0x1900, type:"tx"},
                { pri:6, pgn: 0x1C00, type:"tx"},
                { pri:2, pgn: 0x1E00, type:"tx"},
                { pri:6, pgn: 0x2600, type:"rx"},
                { pri:6, pgn: 0x0100, type:"rx"},
                { pri:6, pgn: 0x0700, type:"rx"},
                { pri:6, pgn: 0x0800, type:"rx"},
                { pri:4, pgn: 0x0A00, type:"rx"},
                { pri:6, pgn: 0x1200, type:"rx"},
                { pri:4, pgn: 0x1A00, type:"rx"},
                { pri:6, pgn: 0x1D00, type:"rx"},
                { pri:2, pgn: 0x1F00, type:"rx"},
                { id:0x112, type: "srx"},
                { id:0x111, type: "stx"},
                { id:0x115, type: "stx"},
            ]
        }, {
            name:"Vcu",
            hw:2,
            self:0x13,
            remote:0x14,
            pgs:[
                { pri: 7, pgn:0x0100, type:"rx"},
                { pri: 7, pgn:0x0200, type:"tx"},
                { id:0x1E1, type: "stx"},
                { id:0x1E2, type: "stx"},
                { id:0x1E3, type: "stx"},
                { id:0x1E4, type: "stx"},
                { id:0x1E5, type: "stx"},
                { id:0x1E6, type: "stx"},
                { id:0x1E7, type: "stx"},
            ]
        }, {
            name:"ExternCan",
            self:0xf4,
            remote:0x56,
            hw:3,
            pgs:[
                { pri:6, pgn: 0x2700, type:"tx"},
                { pri:7, pgn: 0x0200, type:"tx"},
                { pri:7, pgn: 0x0600, type:"tx"},
                { pri:4, pgn: 0x0900, type:"tx"},
                { pri:6, pgn: 0x1000, type:"tx"},
                { pri:7, pgn: 0x1100, type:"tx"},
                { pri:6, pgn: 0x1300, type:"tx"},
                { pri:7, pgn: 0x1500, type:"tx"},
                { pri:7, pgn: 0x1600, type:"tx"},
                { pri:7, pgn: 0x1700, type:"tx"},
                { pri:4, pgn: 0x1900, type:"tx"},
                { pri:6, pgn: 0x1C00, type:"tx"},
                { pri:2, pgn: 0x1E00, type:"tx"},
                { pri:6, pgn: 0x2600, type:"rx"},
                { pri:6, pgn: 0x0100, type:"rx"},
                { pri:6, pgn: 0x0700, type:"rx"},
                { pri:6, pgn: 0x0800, type:"rx"},
                { pri:4, pgn: 0x0A00, type:"rx"},
                { pri:6, pgn: 0x1200, type:"rx"},
                { pri:4, pgn: 0x1A00, type:"rx"},
                { pri:6, pgn: 0x1D00, type:"rx"},
                { pri:2, pgn: 0x1F00, type:"rx"},
                { id:0x1E1, type: "stx"},
                { id:0x1E4, type: "stx"},
                { id:0x1F3, type: "stx"},
                { id:0x1F5, type: "stx"},
                { id:0x360, type: "stx"},
                { id:0x361, type: "stx"},
                { id:0x208, type: "stx"},
                { id:0x351, type: "stx"},
                { id:0x358, type: "stx"},
                { id:0x352, type: "stx"},
                { id:0x353, type: "stx"},
                { id:0x354, type: "stx"},
                { id:0x355, type: "stx"},
                { id:0x3F6, type: "stx"},
                { id:0x211, type: "stx"},
                { id:0x1F4, type: "stx"},
                { id:0x356, type: "stx"},
                { id:0x357, type: "stx"},
                { id:0x3F3, type: "stx"},
                { id:0x3F4, type: "stx"},
                { id:0x3F5, type: "stx"},
                { id:0x3FF, type: "stx"},
                { id:0x201, type: "stx"},
                { id:0x202, type: "stx"},
                { id:0x205, type: "stx"},
                { id:0x206, type: "stx"},
                { id:0x207, type: "stx"},
                { id:0x203, type: "stx"},
                { id:0x204, type: "stx"},
            ]
        },
    ],

    GB32960: {
        apn: "",
        server: "dtu.udantech.com:30097",
        rtmsg_interval: 30,
    },

    /* DtuTp的配置, 目前只支持UDS的物理寻址数据连接 */
    DtuTp:{
        rxsduids:["UDS_PHYICAL"],
        txsduids:["UDS_PHYICAL"]
    },

    InnerTp: { },

    /* 数据路由表的配置 */
    PduR:{
        tx:[
            {upper:["Dcm", 0], middle:["CanTp", "UdsPhy"]},
            {upper:["Dcm", 1], middle:["CanTp", "UdsPhy"]},
            {upper:["Dcm", 2], middle:["DtuTp", "UDS_PHYICAL"]},
            {upper:["Dcm", 3], middle:["DtuTp", "UDS_PHYICAL"]},

            {upper:["ExternCanComm", "GB_BHM"], middle:["J1939Tp", "ExternCan_PG_2700"]},
            {upper:["ExternCanComm", "GB_BRM"], middle:["J1939Tp", "ExternCan_PG_0200"]},
            {upper:["ExternCanComm", "GB_BCP"], middle:["J1939Tp", "ExternCan_PG_0600"]},
            {upper:["ExternCanComm", "GB_BRO"], middle:["J1939Tp", "ExternCan_PG_0900"]},
            {upper:["ExternCanComm", "GB_BCL"], middle:["J1939Tp", "ExternCan_PG_1000"]},
            {upper:["ExternCanComm", "GB_BCS"], middle:["J1939Tp", "ExternCan_PG_1100"]},
            {upper:["ExternCanComm", "GB_BSM"], middle:["J1939Tp", "ExternCan_PG_1300"]},
            {upper:["ExternCanComm", "GB_BMV"], middle:["J1939Tp", "ExternCan_PG_1500"]},
            {upper:["ExternCanComm", "GB_BMT"], middle:["J1939Tp", "ExternCan_PG_1600"]},
            {upper:["ExternCanComm", "GB_BSP"], middle:["J1939Tp", "ExternCan_PG_1700"]},
            {upper:["ExternCanComm", "GB_BST"], middle:["J1939Tp", "ExternCan_PG_1900"]},
            {upper:["ExternCanComm", "GB_BSD"], middle:["J1939Tp", "ExternCan_PG_1C00"]},
            {upper:["ExternCanComm", "GB_BEM"], middle:["J1939Tp", "ExternCan_PG_1E00"]},
            {upper:["ExternCanComm", "1E1"], middle:["J1939Tp", "ExternCan_ID_000001E1"]},
            {upper:["ExternCanComm", "1E4"], middle:["J1939Tp", "ExternCan_ID_000001E4"]},
            {upper:["ExternCanComm", "1F3"], middle:["J1939Tp", "ExternCan_ID_000001F3"]},
            {upper:["ExternCanComm", "1F5"], middle:["J1939Tp", "ExternCan_ID_000001F5"]},
            {upper:["ExternCanComm", "360"], middle:["J1939Tp", "ExternCan_ID_00000360"]},
            {upper:["ExternCanComm", "361"], middle:["J1939Tp", "ExternCan_ID_00000361"]},
            {upper:["ExternCanComm", "208"], middle:["J1939Tp", "ExternCan_ID_00000208"]},
            {upper:["ExternCanComm", "351"], middle:["J1939Tp", "ExternCan_ID_00000351"]},
            {upper:["ExternCanComm", "358"], middle:["J1939Tp", "ExternCan_ID_00000358"]},
            {upper:["ExternCanComm", "352"], middle:["J1939Tp", "ExternCan_ID_00000352"]},
            {upper:["ExternCanComm", "353"], middle:["J1939Tp", "ExternCan_ID_00000353"]},
            {upper:["ExternCanComm", "354"], middle:["J1939Tp", "ExternCan_ID_00000354"]},
            {upper:["ExternCanComm", "355"], middle:["J1939Tp", "ExternCan_ID_00000355"]},
            {upper:["ExternCanComm", "3F6"], middle:["J1939Tp", "ExternCan_ID_000003F6"]},
            {upper:["ExternCanComm", "211"], middle:["J1939Tp", "ExternCan_ID_00000211"]},
            {upper:["ExternCanComm", "1F4"], middle:["J1939Tp", "ExternCan_ID_000001F4"]},
            {upper:["ExternCanComm", "356"], middle:["J1939Tp", "ExternCan_ID_00000356"]},
            {upper:["ExternCanComm", "357"], middle:["J1939Tp", "ExternCan_ID_00000357"]},
            {upper:["ExternCanComm", "3F3"], middle:["J1939Tp", "ExternCan_ID_000003F3"]},
            {upper:["ExternCanComm", "3F4"], middle:["J1939Tp", "ExternCan_ID_000003F4"]},
            {upper:["ExternCanComm", "3F5"], middle:["J1939Tp", "ExternCan_ID_000003F5"]},
            {upper:["ExternCanComm", "3FF"], middle:["J1939Tp", "ExternCan_ID_000003FF"]},
            {upper:["ExternCanComm", "201"], middle:["J1939Tp", "ExternCan_ID_00000201"]},
            {upper:["ExternCanComm", "202"], middle:["J1939Tp", "ExternCan_ID_00000202"]},
            {upper:["ExternCanComm", "205"], middle:["J1939Tp", "ExternCan_ID_00000205"]},
            {upper:["ExternCanComm", "206"], middle:["J1939Tp", "ExternCan_ID_00000206"]},
            {upper:["ExternCanComm", "207"], middle:["J1939Tp", "ExternCan_ID_00000207"]},
            {upper:["ExternCanComm", "203"], middle:["J1939Tp", "ExternCan_ID_00000203"]},
            {upper:["ExternCanComm", "204"], middle:["J1939Tp", "ExternCan_ID_00000204"]},

            {upper:["ChargerComm", "GB_BHM"], middle:["J1939Tp", "Charger_PG_2700"]},
            {upper:["ChargerComm", "GB_BRM"], middle:["J1939Tp", "Charger_PG_0200"]},
            {upper:["ChargerComm", "GB_BCP"], middle:["J1939Tp", "Charger_PG_0600"]},
            {upper:["ChargerComm", "GB_BRO"], middle:["J1939Tp", "Charger_PG_0900"]},
            {upper:["ChargerComm", "GB_BCL"], middle:["J1939Tp", "Charger_PG_1000"]},
            {upper:["ChargerComm", "GB_BCS"], middle:["J1939Tp", "Charger_PG_1100"]},
            {upper:["ChargerComm", "GB_BSM"], middle:["J1939Tp", "Charger_PG_1300"]},
            {upper:["ChargerComm", "GB_BMV"], middle:["J1939Tp", "Charger_PG_1500"]},
            {upper:["ChargerComm", "GB_BMT"], middle:["J1939Tp", "Charger_PG_1600"]},
            {upper:["ChargerComm", "GB_BSP"], middle:["J1939Tp", "Charger_PG_1700"]},
            {upper:["ChargerComm", "GB_BST"], middle:["J1939Tp", "Charger_PG_1900"]},
            {upper:["ChargerComm", "GB_BSD"], middle:["J1939Tp", "Charger_PG_1C00"]},
            {upper:["ChargerComm", "GB_BEM"], middle:["J1939Tp", "Charger_PG_1E00"]},
            {upper:["ChargerComm", "USER_TC"], middle:["J1939Tp", "Charger_ID_00000111"]},
            {upper:["ChargerComm", "USER_TC1"], middle:["J1939Tp", "Charger_ID_00000115"]},

            {upper:["VcuComm", 0], middle:["J1939Tp", "Vcu_ID_000001E1"]},
            {upper:["VcuComm", 1], middle:["J1939Tp", "Vcu_ID_000001E2"]},
            {upper:["VcuComm", 2], middle:["J1939Tp", "Vcu_ID_000001E3"]},
            {upper:["VcuComm", 3], middle:["J1939Tp", "Vcu_ID_000001E4"]},
            {upper:["VcuComm", 4], middle:["J1939Tp", "Vcu_ID_000001E5"]},
            {upper:["VcuComm", 5], middle:["J1939Tp", "Vcu_ID_000001E6"]},
            {upper:["VcuComm", 6], middle:["J1939Tp", "Vcu_ID_000001E7"]},
        ],


        rx:[
            {upper:["Dcm", 0], middle:["CanTp", "UdsPhy"]},
            {upper:["Dcm", 1], middle:["CanTp", "UdsFunc"]},
            {upper:["Dcm", 2], middle:["DtuTp", "UDS_PHYICAL"]},

            {upper:["ExternCanComm", "GB_CHM"], middle:["J1939Tp", "ExternCan_PG_2600"]},
            {upper:["ExternCanComm", "GB_CRM"], middle:["J1939Tp", "ExternCan_PG_0100"]},
            {upper:["ExternCanComm", "GB_CTS"], middle:["J1939Tp", "ExternCan_PG_0700"]},
            {upper:["ExternCanComm", "GB_CML"], middle:["J1939Tp", "ExternCan_PG_0800"]},
            {upper:["ExternCanComm", "GB_CRO"], middle:["J1939Tp", "ExternCan_PG_0A00"]},
            {upper:["ExternCanComm", "GB_CCS"], middle:["J1939Tp", "ExternCan_PG_1200"]},
            {upper:["ExternCanComm", "GB_CST"], middle:["J1939Tp", "ExternCan_PG_1A00"]},
            {upper:["ExternCanComm", "GB_CSD"], middle:["J1939Tp", "ExternCan_PG_1D00"]},
            {upper:["ExternCanComm", "GB_CEM"], middle:["J1939Tp", "ExternCan_PG_1F00"]},

            {upper:["ChargerComm", "GB_CHM"], middle:["J1939Tp", "Charger_PG_2600"]},
            {upper:["ChargerComm", "GB_CRM"], middle:["J1939Tp", "Charger_PG_0100"]},
            {upper:["ChargerComm", "GB_CTS"], middle:["J1939Tp", "Charger_PG_0700"]},
            {upper:["ChargerComm", "GB_CML"], middle:["J1939Tp", "Charger_PG_0800"]},
            {upper:["ChargerComm", "GB_CRO"], middle:["J1939Tp", "Charger_PG_0A00"]},
            {upper:["ChargerComm", "GB_CCS"], middle:["J1939Tp", "Charger_PG_1200"]},
            {upper:["ChargerComm", "GB_CST"], middle:["J1939Tp", "Charger_PG_1A00"]},
            {upper:["ChargerComm", "GB_CSD"], middle:["J1939Tp", "Charger_PG_1D00"]},
            {upper:["ChargerComm", "GB_CEM"], middle:["J1939Tp", "Charger_PG_1F00"]},
            {upper:["ChargerComm", "USER_TC"], middle:["J1939Tp", "Charger_ID_00000112"]},
        ],

    },
};
