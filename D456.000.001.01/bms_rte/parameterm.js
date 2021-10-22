module.exports = {
    process: function(cfgData, info) {
        var nomapper = x=> [Math.round(x[0]), Math.round(x[1]), Math.round(x[2]*100), Math.round(x[3]*100)];
        var mvMapper = x=> [Math.round(x[0]*1000), Math.round(x[1]*1000), Math.round(x[2]*100), Math.round(x[3]*100)];
        var x10mapper = x => [Math.round(x[0]*10), Math.round(x[1]*10), Math.round(x[2]*100), Math.round(x[3]*100)];
        var tempmapper = x => [Math.round(x[0]+50), Math.round(x[1]+50), Math.round(x[2]*100), Math.round(x[3]*100)];
        var socgmapper = x10mapper
        var hvmapper = x10mapper;
        var currentmapper = x10mapper;
        var percentmapper = x10mapper;

        var defaultDefault = [65535,65535,65535,65535];
        var tempDefault = [255,255,65535,65535];
        var curDefault = [32768,32768,65535,65535];
        var socDefault = defaultDefault;
        var leakDefault = defaultDefault;
        var timeoutDefault = defaultDefault;


        var diagnosisitems = [
            {name:"充电单体电压高", mapper: mvMapper, default:defaultDefault, calibrate: true},
            {name:"放电单体电压高", mapper: mvMapper, default:defaultDefault, calibrate: true},
            {name:"充电单体电压低", mapper: mvMapper, default:defaultDefault, calibrate: true},
            {name:"放电单体电压低", mapper: mvMapper, default:defaultDefault, calibrate: true},
            {name:"充电总压高", mapper: hvmapper, default:defaultDefault, calibrate: true},
            {name:"放电总压高", mapper: hvmapper, default:defaultDefault, calibrate: true},
            {name:"充电总压低", mapper: hvmapper, default:defaultDefault, calibrate: true},
            {name:"放电总压低", mapper: hvmapper, default:defaultDefault, calibrate: true},
            {name:"充电总压压差", mapper: hvmapper, default:defaultDefault, calibrate: true},
            {name:"放电总压压差", mapper: hvmapper, default:defaultDefault, calibrate: true},
            {name:"充电单体压差", mapper: mvMapper, default:defaultDefault, calibrate: true},
            {name:"放电单体压差", mapper: mvMapper, default:defaultDefault, calibrate: true},
            {name:"充电高温", mapper: tempmapper, default:tempDefault, calibrate: true},
            {name:"放电高温", mapper: tempmapper, default:tempDefault, calibrate: true},
            {name:"充电低温", mapper: tempmapper, default:tempDefault, calibrate: true},
            {name:"放电低温", mapper: tempmapper, default:tempDefault, calibrate: true},
            {name:"充电温差", mapper: tempmapper, default:tempDefault, calibrate: true},
            {name:"放电温差", mapper: tempmapper, default:tempDefault, calibrate: true},
            {name:"快充过流", mapper: currentmapper, default:curDefault, calibrate: true},
            {name:"慢充过流", mapper: currentmapper, default:curDefault, calibrate: true},
            {name:"回馈过流", mapper: currentmapper, default:curDefault, calibrate: true},
            {name:"持续放电过流", mapper: currentmapper, default:curDefault, calibrate: true},
            {name:"瞬时放电过流", mapper: currentmapper, default:curDefault, calibrate: true},
            {name:"SOC过高", mapper: percentmapper, default:socDefault, calibrate: true},
            {name:"SOC过低", mapper: percentmapper, default:socDefault, calibrate: true},
            {name:"绝缘漏电", mapper: nomapper, default:leakDefault, calibrate: true},
            {name:"充电加热高温", mapper: tempmapper, default:tempDefault, calibrate: true},
            {name:"放电加热高温", mapper: tempmapper, default:tempDefault, calibrate: true},
            {name:"充电加热温差", mapper: tempmapper, default:tempDefault, calibrate: true},
            {name:"放电加热温差", mapper: tempmapper, default:tempDefault, calibrate: true},
            {name:"充电加热超时", mapper: nomapper, default:timeoutDefault, calibrate: true},
            {name:"放电加热超时", mapper: nomapper, default:timeoutDefault, calibrate: true},
            {name:"充电加热过流", mapper: currentmapper, default:curDefault, calibrate: true},
            {name:"放电加热过流", mapper: currentmapper, default:curDefault, calibrate: true},
            {name:"SOC跳变", mapper: nomapper, default:defaultDefault, calibrate: true},
            {name:"供电电压过低", mapper: mvMapper, default:defaultDefault, calibrate: true},
            {name:"充电极柱高温", mapper: tempmapper, default:tempDefault, calibrate: true},
            {name:"放电极柱高温", mapper: tempmapper, default:tempDefault, calibrate: true},
            {name:"充电极柱温差", mapper: tempmapper, default:tempDefault, calibrate: true},
            {name:"放电极柱温差", mapper: tempmapper, default:tempDefault, calibrate: true},
            {name:"充电电流异常", mapper: currentmapper, default:curDefault, calibrate: true},
            {name:"供电电压过高", mapper: mvMapper, default:defaultDefault, calibrate: true},
            {name:"电压排线脱落", mapper: nomapper, default:defaultDefault, calibrate: false},
            {name:"温感排线脱落", mapper: nomapper, default:defaultDefault, calibrate: false},
            {name:"内网通信", mapper: nomapper, default:defaultDefault, calibrate: false},
            {name:"快充正极高温", mapper: tempmapper, default:tempDefault, calibrate: false},
            {name:"快充负极高温", mapper: tempmapper, default:tempDefault, calibrate: false},
            {name:"慢充AL极高温", mapper: tempmapper, default:tempDefault, calibrate: false},
            {name:"慢充BN极高温", mapper: tempmapper, default:tempDefault, calibrate: false},
            {name:"慢充C极高温", mapper: tempmapper, default:tempDefault, calibrate: false},
            {name:"充电机通信", mapper: nomapper, default:defaultDefault, calibrate: false},
            {name:"整车通信", mapper: nomapper, default:defaultDefault, calibrate: false},
            {name:"满充", mapper: nomapper, default:defaultDefault, calibrate: false},
            {name:"充电插座温感异常", mapper: nomapper, default:defaultDefault, calibrate: false},
            {name:"预充失败", mapper: nomapper, default:defaultDefault, calibrate: false},
            {name:"电流异常", mapper: nomapper, default:defaultDefault, calibrate: false},
            {name:"BMS初始化故障", mapper: nomapper, default:defaultDefault, calibrate: false},
            {name:"HVIL故障", mapper: nomapper, default:defaultDefault, calibrate: false},
            {name:"继电器故障", mapper: nomapper, default:defaultDefault, calibrate: false},
            {name:"加热故障", mapper: nomapper, default:defaultDefault, calibrate: false},
            {name:"CC2连接故障", mapper: nomapper, default:defaultDefault, calibrate: false},
            {name:"CC连接故障", mapper: nomapper, default:defaultDefault, calibrate: false},
            {name:"CP连接故障", mapper: nomapper, default:defaultDefault, calibrate: false},
            {name:"加热温感异常", mapper: nomapper, default:defaultDefault, calibrate: false},
            {name:"极柱温感异常", mapper: nomapper, default:defaultDefault, calibrate: false},
            {name:"电子锁故障", mapper: nomapper, default:defaultDefault, calibrate: false},
            {name:"多充电连接故障", mapper: nomapper, default:defaultDefault, calibrate: false},
            {name:"电池数不匹配", mapper: nomapper, default:defaultDefault, calibrate: false},
            {name:"温感数不匹配", mapper: nomapper, default:defaultDefault, calibrate: false},
            {name:"供电电压异常", mapper: nomapper, default:defaultDefault, calibrate: false},
            {name:"碰撞故障", mapper: nomapper, default:defaultDefault, calibrate: false},
        ]

        // var calibrateparam = require(cfgData.calibrateparam);
        var calibrateparam = JSON.parse(JSON.stringify(cfgData));
        var diagparams = [];

        for (var index = 0; index < diagnosisitems.length; index++) {
            var item = diagnosisitems[index];
            var param = calibrateparam.Diagnosis.find(x=>x.name == item.name);
            var levels = param ? param.levels : [];
            var validLevels = levels.length;
            for (var i=levels.length; i<4; i++) {
                levels.push(item.default);
            }

            diagparams.push({
                name: item.name,
                validLevels: validLevels,
                levels: levels,
                calibrate: item.calibrate,
                mapper: item.mapper,
            });
        }

        var tempmparammapper = x => {
            return {
                name: x.name,
                temperatureOn: Math.round(x.temperatureOn+50),
                deltaTemperatureOn: Math.round(x.deltaTemperatureOn+50),
                temperatureOnDelay: Math.round(x.temperatureOnDelay*100),
                deltaTemperatureOnDelay: Math.round(x.deltaTemperatureOnDelay*100),
                temperatureOff: Math.round(x.temperatureOff+50),
                deltaTemperatureOff: Math.round(x.deltaTemperatureOff+50),
                temperatureOffDelay: Math.round(x.temperatureOffDelay*100),
                deltaTemperatureOffDelay: Math.round(x.deltaTemperatureOffDelay*100),
            }
        }


        var mdata = {
            EeepParaDefault: {
                totalCap: info.BatteryInfo.totalCap,
                leftCap: info.BatteryInfo.initCap,
                nominalCap: info.BatteryInfo.nominalCap,
            },
            diagparams: diagparams,
            SocEfficiency: calibrateparam.SocEfficiency,
            SocCalibParam: calibrateparam.SocCalibParam,
            DCChargeParam: calibrateparam.ChargeParam.find(x=>x.name == "直流快充"),
            ACChargeParam: calibrateparam.ChargeParam.find(x=>x.name == "交流慢充"),
            TemperatureMPara: {
                ChargeHeat: tempmparammapper(calibrateparam.TemperatureMParam.find(x=>x.name == "充电加热")),
                DischargeHeat: tempmparammapper(calibrateparam.TemperatureMParam.find(x=>x.name == "放电加热")),
                ChargeRefrigeration: tempmparammapper(calibrateparam.TemperatureMParam.find(x=>x.name == "充电制冷")),
                DischargeRefrigeration: tempmparammapper(calibrateparam.TemperatureMParam.find(x=>x.name == "放电制冷")),
            }
        };

        if (!mdata.DCChargeParam.hasOwnProperty('chargeCurrentMax')) {
            mdata.DCChargeParam['chargeCurrentMax'] = info.BatteryInfo.dcchargecurrent;
        }

        if (!mdata.ACChargeParam.hasOwnProperty('chargeCurrentMax')) {
            mdata.ACChargeParam['chargeCurrentMax'] = info.BatteryInfo.acchargecurrent;
        }

        //console.log("================= parameterm ==============")
        //console.log(JSON.stringify(mdata, null, "  "));
        //console.log(JSON.stringify(diagparams, null, "  "));

        info.render("ParameterM_Lcfg.c", "ParameterM_Lcfg.c.tmpl", mdata);
    }
}
