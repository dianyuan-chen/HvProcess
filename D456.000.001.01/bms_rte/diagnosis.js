Array.prototype.toLevelMask = function() {
    var lst = this.reduce((a,e)=>{
        if (Number.isInteger(e) && e>=1 && e<=4 && a.findIndex(x=>x==e) < 0) {
            a.push(e);
        }
        return a;
    },[]);

    return lst.reduce((a, e) => a + (1<<(e-1)), 0);
}

module.exports = {
    process: function(cfgData, info) {
        var cfg = JSON.parse(JSON.stringify(cfgData));
        var makelib = cfg.hasOwnProperty('mklib') && cfg.mklib;

        var externEvent = e => {
            var es = e.event.replace(/\s*/g, '').split("|");
            e.leveMask = e.levels.toLevelMask();
            e.eventMask = es.indexOf("assert") >=0  ? "DIAGNOSIS_EVENT_MASK_ASSERT" : "0U";
            e.eventMask += es.indexOf("deassert") >=0 ? " | DIAGNOSIS_EVENT_MASK_DEASSERT" : "";
        }
        if (makelib) {
            cfg.configs = []
        }

        cfg.configs.forEach((c)=>{
            if (c.events) {
                c.events.forEach(externEvent);
            }

            if (c.startDiagnosis && c.startDiagnosis.events) {
                c.startDiagnosis.events.forEach((x) => {x.levels = [c.startDiagnosis.level], externEvent(x)});
            }
        });

        var diagnosisitems = [
            {name:"充电单体电压高", diagnosisType:"HIGH", condition:"CHG", def:"CHG_HV", altdef:["CALIBRATE_START", "VOLT_START"], getval: "Statistic_GetBcuHvMax", validate:"CellDataM_VoltageIsValid", valueReady:"CellDataM_AllSlaveVoltageIsValid"},
            {name:"放电单体电压高", diagnosisType:"HIGH", condition:"DCHG", def:"DCHG_HV", getval:"Statistic_GetBcuHvMax", validate:"CellDataM_VoltageIsValid", valueReady:"CellDataM_AllSlaveVoltageIsValid"},
            {name:"充电单体电压低", diagnosisType:"LOW", condition:"CHG", def:"CHG_LV", getval:"Statistic_GetBcuLvMax", validate:"CellDataM_VoltageIsValid", valueReady:"CellDataM_AllSlaveVoltageIsValid"},
            {name:"放电单体电压低", diagnosisType:"LOW", condition:"DCHG", def:"DCHG_LV", getval:"Statistic_GetBcuLvMax", validate:"CellDataM_VoltageIsValid", valueReady:"CellDataM_AllSlaveVoltageIsValid"},
            {name:"充电总压高", diagnosisType:"HIGH", condition:"CHG", def:"CHG_HTV", getval:"Statistic_GetBcu100mvTotalVoltage", validate:"Statistic_TotalVoltageIsValid", valueReady:"Statistic_Bcu100MvTotalVoltageIsReady"},
            {name:"放电总压高", diagnosisType:"HIGH", condition:"DCHG", def:"DCHG_HTV", getval:"Statistic_GetBcu100mvTotalVoltage", validate:"Statistic_TotalVoltageIsValid", valueReady:"Statistic_Bcu100MvTotalVoltageIsReady"},
            {name:"充电总压低", diagnosisType:"LOW", condition:"CHG", def:"CHG_LTV", getval:"Statistic_GetBcu100mvTotalVoltage", validate:"Statistic_TotalVoltageIsValid", valueReady:"Statistic_Bcu100MvTotalVoltageIsReady"},
            {name:"放电总压低", diagnosisType:"LOW", condition:"DCHG", def:"DCHG_LTV", getval:"Statistic_GetBcu100mvTotalVoltage", validate:"Statistic_TotalVoltageIsValid", valueReady:"Statistic_Bcu100MvTotalVoltageIsReady"},
            {name:"充电总压压差", diagnosisType:"HIGH", condition:"CHG", def:"CHG_DTV", getval:"Statistic_GetBcuDeltaTotalVoltage", validate:"Statistic_TotalVoltageIsValid", valueReady:"Statistic_Bcu100MvTotalVoltageIsReady"},
            {name:"放电总压压差", diagnosisType:"HIGH", condition:"DCHG", def:"DCHG_DTV", getval:"Statistic_GetBcuDeltaTotalVoltage", validate:"Statistic_TotalVoltageIsValid", valueReady:"Statistic_Bcu100MvTotalVoltageIsReady"},
            {name:"充电单体压差", diagnosisType:"HIGH", condition:"CHG", def:"CHG_DV", getval:"Statistic_GetBcuDvMax", validate:"CellDataM_VoltageIsValid", valueReady:"CellDataM_AllSlaveVoltageIsValid"},
            {name:"放电单体压差", diagnosisType:"HIGH", condition:"DCHG", def:"DCHG_DV",altdef:["VOLT_STOP"], getval:"Statistic_GetBcuDvMax", validate:"CellDataM_VoltageIsValid", valueReady:"CellDataM_AllSlaveVoltageIsValid"},
            {name:"充电高温", diagnosisType:"HIGH", condition:"CHG", def:"CHG_HT",altdef:["TEMPERATURE_START"], getval:"Statistic_GetBcuHtMax", validate:"CellDataM_TemperatureIsValid", valueReady:"CellDataM_AllSlaveTemperatureIsValid"},
            {name:"放电高温", diagnosisType:"HIGH", condition:"DCHG", def:"DCHG_HT", getval:"Statistic_GetBcuHtMax", validate:"CellDataM_TemperatureIsValid", valueReady:"CellDataM_AllSlaveTemperatureIsValid"},
            {name:"充电低温", diagnosisType:"LOW", condition:"CHG", def:"CHG_LT", getval:"Statistic_GetBcuLtMax", validate:"CellDataM_TemperatureIsValid", valueReady:"CellDataM_AllSlaveTemperatureIsValid"},
            {name:"放电低温", diagnosisType:"LOW", condition:"DCHG", def:"DCHG_LT", getval:"Statistic_GetBcuLtMax", validate:"CellDataM_TemperatureIsValid", valueReady:"CellDataM_AllSlaveTemperatureIsValid"},
            {name:"充电温差", diagnosisType:"HIGH", condition:"CHG", def:"CHG_DT", getval:"Statistic_GetBcuDtMax", validate:"CellDataM_TemperatureIsValid", valueReady:"CellDataM_AllSlaveTemperatureIsValid"},
            {name:"放电温差", diagnosisType:"HIGH", condition:"DCHG", def:"DCHG_DT",altdef:["TEMPERATURE_STOP"], getval:"Statistic_GetBcuDtMax", validate:"CellDataM_TemperatureIsValid", valueReady:"CellDataM_AllSlaveTemperatureIsValid"},
            {name:"快充过流", diagnosisType:"HIGH", condition:"DC_CHG", def:"DC_CHG_OC",altdef:["CURRENT_START"], getval:"CurrentM_GetMainDiagChgCurrent", validate:"CurrentM_DiagIsValidCurrent"},
            {name:"慢充过流", diagnosisType:"HIGH", condition:"AC_CHG", def:"AC_CHG_OC", getval:"CurrentM_GetMainDiagChgCurrent", validate:"CurrentM_DiagIsValidCurrent"},
            {name:"回馈过流", diagnosisType:"HIGH", condition:"DCHG", def:"FB_OC", getval:"CurrentM_GetMainDiagChgCurrent", validate:"CurrentM_DiagIsValidCurrent"},
            {name:"持续放电过流", diagnosisType:"HIGH", condition:"DCHG", def:"DCHG_OC", getval:"CurrentM_GetMainDiagDchgCurrent", validate:"CurrentM_DiagIsValidCurrent"},
            {name:"瞬时放电过流", diagnosisType:"HIGH", condition:"DCHG", def:"SP_OC",altdef:["CURRENT_STOP"], getval:"CurrentM_GetMainDiagDchgCurrent", validate:"CurrentM_DiagIsValidCurrent"},
            {name:"SOC过高", diagnosisType:"HIGH", condition:"ALL", def:"HSOC", altdef:["SOC_START"], getval:"Soc_Get", validate:"Soc_SocIsValid"},
            {name:"SOC过低", diagnosisType:"LOW", condition:"DCHG", def:"LSOC",altdef:["SOC_STOP"], getval:"Soc_Get", validate:"Soc_SocIsValid"},
            {name:"绝缘漏电", diagnosisType:"LOW", condition:"ALL", def:"LEAK", getval:"Insu_GetLeak", validate:"Insu_LeakIsValid", valueReady:"Insu_IsCalculated"},
            {name:"充电加热高温", diagnosisType:"HIGH", condition:"CHG", def:"CHG_HEAT_HT", getval:"TemperatureM_GetChgHeatTemperatureMax", validate:"CellDataM_TemperatureIsValid", valueReady:"CellDataM_AllSlaveTemperatureIsValid"},
            {name:"放电加热高温", diagnosisType:"HIGH", condition:"DCHG", def:"DCHG_HEAT_HT", getval:"TemperatureM_GetDchgHeatTemperatureMax", validate:"CellDataM_TemperatureIsValid", valueReady:"CellDataM_AllSlaveTemperatureIsValid"},
            {name:"充电加热温差", diagnosisType:"HIGH", condition:"CHG", def:"CHG_HEAT_DT", getval:"TemperatureM_GetChgHeatDeltaTemperatureMax", validate:"CellDataM_TemperatureIsValid", valueReady:"CellDataM_AllSlaveTemperatureIsValid"},
            {name:"放电加热温差", diagnosisType:"HIGH", condition:"DCHG", def:"DCHG_HEAT_DT", getval:"TemperatureM_GetDchgHeatDeltaTemperatureMax", validate:"CellDataM_TemperatureIsValid", valueReady:"CellDataM_AllSlaveTemperatureIsValid"},
            {name:"充电加热超时", diagnosisType:"HIGH", condition:"CHG", def:"CHG_HEAT_TIMEOUT", getval:"TemperatureM_GetChgHeatTime"},
            {name:"放电加热超时", diagnosisType:"HIGH", condition:"DCHG", def:"DCHG_HEAT_TIMEOUT", getval:"TemperatureM_GetDchgHeatTime"},
            {name:"充电加热过流", diagnosisType:"HIGH", condition:"CHG", def:"CHG_HEAT_OC", getval:"TemperatureM_GetChgHeatCurrent", validate:"CurrentM_DiagIsValidCurrent"},
            {name:"放电加热过流", diagnosisType:"HIGH", condition:"DCHG", def:"DCHG_HEAT_OC", getval:"TemperatureM_GetDchgHeatCurrent", validate:"CurrentM_DiagIsValidCurrent"},
            {name:"SOC跳变", diagnosisType:"LOW", condition:"ALL", def:"SOC_JUMP", getval:"Soc_GetJumpSocInternal", validate:"Soc_JumpSocInternalIsValid"},
            {name:"供电电压过低", diagnosisType:"LOW", condition:"ALL", def:"SUPPLY_VOL_LOW", getval:"HWDiagnosis_GetSupplyVoltage", validate:"CellDataM_VoltageIsValid"},
            {name:"充电极柱高温", diagnosisType:"HIGH", condition:"CHG", def:"CHG_POLE_HT", getval:"Statistic_GetBcuPoleHtMax", validate:"CellDataM_TemperatureIsValid", valueReady:"CellDataM_AllSlaveTemperatureIsValid"},
            {name:"放电极柱高温", diagnosisType:"HIGH", condition:"DCHG", def:"DCHG_POLE_HT", getval:"Statistic_GetBcuPoleHtMax", validate:"CellDataM_TemperatureIsValid", valueReady:"CellDataM_AllSlaveTemperatureIsValid"},
            {name:"充电极柱温差", diagnosisType:"HIGH", condition:"CHG", def:"CHG_POLE_DT", getval:"Statistic_GetBcuPoleDtMax", validate:"CellDataM_TemperatureIsValid", valueReady:"CellDataM_AllSlaveTemperatureIsValid"},
            {name:"放电极柱温差", diagnosisType:"HIGH", condition:"DCHG", def:"DCHG_POLE_DT", getval:"Statistic_GetBcuPoleDtMax", validate:"CellDataM_TemperatureIsValid", valueReady:"CellDataM_AllSlaveTemperatureIsValid"},
            {name:"充电电流异常", diagnosisType:"HIGH", condition:"CHG", def:"CHG_CUR_FAULT", getval:"ChargerComm_DiagGetDeltaCurWithChr", validate:"CurrentM_DiagIsValidCurrent"},
            {name:"供电电压过高", diagnosisType:"HIGH", condition:"ALL", def:"SUPPLY_VOL_HIGH", altdef:["CALIBRATE_STOP"], getval:"HWDiagnosis_GetSupplyVoltage", validate:"CellDataM_VoltageIsValid"},
            {name:"电压排线脱落", diagnosisType:"HIGH", condition:"ALL", def:"VOLT_LINE", altdef:["NONE_CALIBRATE_START","LINE_START"], getval:"Statistic_GetBcuInvalidVoltageNum", valueReady:"CellDataM_AllSlaveVoltageIsValid"},
            {name:"温感排线脱落", diagnosisType:"HIGH", condition:"ALL", def:"TEMP_LINE",altdef:["LINE_STOP"], getval:"Statistic_GetBcuInvalidTemperatureNum", valueReady:"CellDataM_AllSlaveTemperatureIsValid"},
            {name:"内网通信", diagnosisType:"HIGH", condition:"ALL", def:"INTER_COMM", getval:"InternalComm_SlaveIsNoComm", valueReady:"CellDataM_AllSlaveVoltageIsValid"},
            {name:"快充正极高温", diagnosisType:"HIGH", condition:"DC_CHG", def:"CHGSCKTMP_DC_POSITIVE", altdef:["CHGSCKTMP_START"], getval:"ChgSckTmpM_GetDCPositiveTemperature", validate:"CellDataM_TemperatureIsValid", valueReady:"ChgSckTmpM_AllTemperatureIsGet"},
            {name:"快充负极高温", diagnosisType:"HIGH", condition:"DC_CHG", def:"CHGSCKTMP_DC_NEGATIVE", getval:"ChgSckTmpM_GetDCNegativeTemperature", validate:"CellDataM_TemperatureIsValid", valueReady:"ChgSckTmpM_AllTemperatureIsGet"},
            {name:"慢充AL极高温", diagnosisType:"HIGH", condition:"AC_CHG", def:"CHGSCKTMP_AC_AL", getval:"ChgSckTmpM_GetACALTemperature", validate:"CellDataM_TemperatureIsValid", valueReady:"ChgSckTmpM_AllTemperatureIsGet"},
            {name:"慢充BN极高温", diagnosisType:"HIGH", condition:"AC_CHG", def:"CHGSCKTMP_AC_BN", getval:"ChgSckTmpM_GetACBNTemperature", validate:"CellDataM_TemperatureIsValid", valueReady:"ChgSckTmpM_AllTemperatureIsGet"},
            {name:"慢充C极高温", diagnosisType:"HIGH", condition:"AC_CHG", def:"CHGSCKTMP_AC_C",altdef:["CHGSCKTMP_STOP"], getval:"ChgSckTmpM_GetACCTemperature", validate:"CellDataM_TemperatureIsValid", valueReady:"ChgSckTmpM_AllTemperatureIsGet"},
            {name:"充电机通信", diagnosisType:"HIGH", condition:"CHG", def:"CHARGER_COMM", getval:"ChargerComm_DiagIsCommAbort"},
            {name:"整车通信", diagnosisType:"HIGH", condition:"ALL", def:"VCU_COMM", getval:"VcuComm_DiagIsCommAbort"},
            {name:"满充", diagnosisType:"HIGH", condition:"CHG", def:"FULL_CHARGE", getval:"FullCharge_GetStatus"},
            {name:"充电插座温感异常", diagnosisType:"HIGH", condition:"CHG", def:"CHGSCKTMP_ABNORMAL", getval:"ChgSckTmpM_GetAbnormalTemperatureNum", validate:"CellDataM_TemperatureIsValid", valueReady:"ChgSckTmpM_AllTemperatureIsGet"},
            {name:"预充失败", diagnosisType:"HIGH", condition:"DCHG", def:"PRECHARGE_FAILURE", getval:"PrechargeM_IsFailure"},
            {name:"电流异常", diagnosisType:"HIGH", condition:"ALL", def:"CURRENT_ABNORMAL", getval:"CurrentM_CurrentIsAbnormal"},
            {name:"BMS初始化故障", diagnosisType:"HIGH", condition:"ALL", def:"BMS_INIT_FAILURE", getval:"InitialDiagM_IsDiagFailure"},
            {name:"HVIL故障", diagnosisType:"HIGH", condition:"ALL", def:"HVIL_ABNORMAL", getval:"UserStrategy_IsDiagHvilAbnormal"},
            {name:"继电器故障", diagnosisType:"HIGH", condition:"ALL", def:"RELAY_ABNORMAL", getval:"RelayM_IsDiagAbnormal"},
            {name:"加热故障", diagnosisType:"HIGH", condition:"ALL", def:"HEAT_FAULT", getval:"TemperatureM_IsHeatingFault"},
            {name:"CC2连接故障", diagnosisType:"HIGH", condition:"ALL", def:"CC2_CONNECT_FAULT", getval:"ChargeConnectM_CC2ConnectIsFault"},
            {name:"CC连接故障", diagnosisType:"HIGH", condition:"ALL", def:"CC_CONNECT_FAULT", getval:"ChargeConnectM_CCConnectIsFault"},
            {name:"CP连接故障", diagnosisType:"HIGH", condition:"ALL", def:"CP_CONNECT_FAULT", getval:"ChargeConnectM_CPConnectIsFault"},
            {name:"加热温感异常", diagnosisType:"HIGH", condition:"ALL", def:"HEAT_TEMP_LINE_FAULT", getval:"Statistic_GetBcuInvalidHeatTemperatureNum", valueReady:"CellDataM_AllSlaveTemperatureIsValid"},
            {name:"极柱温感异常", diagnosisType:"HIGH", condition:"ALL", def:"POLE_TEMP_LINE_FAULT", getval:"Statistic_GetBcuInvalidPoleTemperatureNum", valueReady:"CellDataM_AllSlaveTemperatureIsValid"},
            {name:"电子锁故障", diagnosisType:"HIGH", condition:"ALL", def:"EL_FAULT", getval:"EL_DiagnosisIsError", valueReady:"EL_DiagsisIsFinishedForDiag"},
            {name:"多充电连接故障", diagnosisType:"HIGH", condition:"ALL", def:"DOUBLE_CHG_CONNECT_FAULT", getval:"ChargeConnectM_IsDoubleConnectFault"},
            {name:"电池数不匹配", diagnosisType:"HIGH", condition:"ALL", def:"ACT_BAT_NUM",getval:"Statistic_ActureBatNumIsNotMatch", valueReady:"CellDataM_AllSlaveVoltageIsValid"},
            {name:"温感数不匹配", diagnosisType:"HIGH", condition:"ALL", def:"ACT_TMP_NUM", getval:"Statistic_ActureTemperatureNumIsNotMatch", valueReady:"CellDataM_AllSlaveTemperatureIsValid"},
            {name:"供电电压异常", diagnosisType:"HIGH", condition:"ALL", def:"SUPPLY_VOL_ABNOMAL", getval:"HWDiagnosis_SupplyVoltageIsAbnomal"},
            {name:"碰撞故障", diagnosisType:"HIGH", condition:"ALL", def:"CRASH_FAULT",altdef:["NONE_CALIBRATE_STOP"], getval:"UserStrategy_GetCrashFault"},
        ];

        var noneCalibrateStart = '电压排线脱落';
        var infoconfig = [];
        var thresholdconfig = [];
        var noneCalibrateStartIndex = 128;

        for (var index = 0; index < diagnosisitems.length; index++) {
            var item = diagnosisitems[index];
            if (item.name == noneCalibrateStart) {
                noneCalibrateStartIndex = index;
                break;
            }
        }

        for (var index = 0; index < diagnosisitems.length; index++) {
            var item = diagnosisitems[index];
            var cfgItem = cfg.configs.find(x=>x.name == item.name);
            var enableFlag = cfgItem ? cfgItem.levels.toLevelMask() : 0;
            var startDiagnosis = {};
            if (cfgItem && cfgItem.startDiagnosis) {
                startDiagnosis = cfgItem.startDiagnosis;
                startDiagnosis.enableFlag = (1 << (cfgItem.startDiagnosis.level-1)) & enableFlag;
                startDiagnosis.valueReady = item.valueReady ? item.valueReady : "NULL";
            } else {
                startDiagnosis.enableFlag = 0;
            }

            if (startDiagnosis.enableFlag == 0) {
                startDiagnosis.timeout = 10000;
                startDiagnosis.valueReady = "NULL";
                startDiagnosis.events = [];
            }

            var levelParaGetFunc = "NULL";
            if (cfgItem && cfgItem.levelParaGetFunc) {
                levelParaGetFunc = cfgItem.levelParaGetFunc;
            }

            infoconfig.push({
                name: item.name,
                cycle: cfgItem ? cfgItem.cycle : 65535,
                conditionFlag: item.condition,
                diagnosisType: item.diagnosisType,
                enableFlag: enableFlag,
                itemDef: item.def,
                itemDefVal: (index >= noneCalibrateStartIndex) ? index - noneCalibrateStartIndex + 128 : index,
                itemAltdef: item.hasOwnProperty('altdef') ? item.altdef : [],
                getDataFunc: item.getval ? item.getval : "NULL",
                isvalidFunc: item.validate ? item.validate : "NULL",
                levelParaGetFunc: levelParaGetFunc,
                events: cfgItem ? cfgItem.events : null,
                startDiagnosis: startDiagnosis,
                isNoneCalibrate: parseInt(index) >= noneCalibrateStartIndex,
            });
        }

        var mdata = {
            infoconfig: infoconfig,
        }

        //console.log("================= diagnosis ==============")
        //console.log(JSON.stringify(mdata, null, "  "));
        info.render("Diagnosis_Cfg.h", "Diagnosis_Cfg.h.tmpl", mdata);
        if (!makelib) {
            info.render("Diagnosis_Lcfg.c", "Diagnosis_Lcfg.c.tmpl", mdata);
        }

        return {
            levelsupport: cfg.levelsupport,
        }
    }
}
