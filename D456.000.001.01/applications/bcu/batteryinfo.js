module.exports = {
    process: function(cfgData, info) {
        var cfg = JSON.parse(JSON.stringify(cfgData));

        //console.log("============== batteryinfo =============")
        //console.log(cfg);

        var typeToDescMap = [
        // [电池类型宏，电池类型，极限保护高压，极限保护低压，极限保护高温，极限保护延时]
            ["APP_BATTERY_TYPE_LEAD_ACID", "铅酸", 3000, 1000, 63, 5000],
            ["APP_BATTERY_TYPE_NIMH", "镍氢", 1800, 700, 63, 5000],
            ["APP_BATTERY_TYPE_LIFEPO4", "磷酸铁锂", 3900, 1999, 63, 5000],
            ["APP_BATTERY_TYPE_LIMN2O4", "锰酸锂", 4400, 2200, 63, 5000],
            ["APP_BATTERY_TYPE_LICOO2", "钴酸锂", 4300, 2200, 63, 5000],
            ["APP_BATTERY_TYPE_TERNARY", "三元材料", 4300, 2700, 63, 5000],
            ["APP_BATTERY_TYPE_POLYMER_LI_LON", "聚合物锂离子", 4300, 2700, 63, 5000],
            ["APP_BATTERY_TYPE_LI4O4TI", "钛酸锂", 3000, 1500, 65, 5000],
            ["APP_BATTERY_TYPE_OTHERS", "其他", 0xffff, 0xffff, 0xff, 5000],
        ];

        var type = "APP_BATTERY_TYPE_UNKNOWN";
        var desc = ["APP_BATTERY_TYPE_UNKNOWN", "未知", 0xffff, 0xffff, 0xff, 0xffff];
        for (var t of typeToDescMap) {
            if (t[1] == cfg.type) {
                desc = t
                break;
            }
        }

        if (cfg.serialnum > 400) {
            throw "Dose not support serialnum > 400";
        }

        if (cfg.celltempnum + cfg.heattempnum + cfg.poletempnum > 200) {
            throw "Dose not support celltempnum + heattempnum + poletempnum > 200";
        }

        var mdata = {
            batttype: desc[0],
            capAH: cfg.nominal.cap,
            dischargecurrent: cfg.nominal.dischargecurrent,
            acchargecurrent: cfg.nominal.acchargecurrent,
            dcchargecurrent: cfg.nominal.dcchargecurrent,
            totalvoltage: cfg.nominal.totalvoltage,
            serialnum: cfg.serialnum,
            parallelnum: cfg.parallelnum,
            celltempnum: cfg.celltempnum,
            heattempnum: cfg.heattempnum,
            poletempnum: cfg.poletempnum,
            initsoc: cfg.initsoc,
            initsoh: cfg.initsoh,
            highVoltLimit: desc[2],
            lowVoltLimit: desc[3],
            highTempLimit: desc[4],
            limitProtectDelay: desc[5],
        };

        var colors = require('colors');
        var lvparam = new Array();
        var htparam = new Array();
        lvparam = lvparam.concat(cfg.Diagnosis.find(x=>x.name == "充电单体电压低"));
        lvparam = lvparam.concat(cfg.Diagnosis.find(x=>x.name == "放电单体电压低"));
        htparam = htparam.concat(cfg.Diagnosis.find(x=>x.name == "充电高温"));
        htparam = htparam.concat(cfg.Diagnosis.find(x=>x.name == "放电高温"));
        var lv = 65535;
        var ht = 255;
        var haveWarn = false;
        var warnInfo = "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Warning!!! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        for (var param of lvparam) {
            if (param) {
                for (var level of param.levels) {
                    lv = level[0] * 1000;
                    if (lv != 65535 && mdata.lowVoltLimit != 65535) {
                        if (lv <= mdata.lowVoltLimit) {
                            haveWarn = true;
                            warnInfo += "\n                     " + param.name + ": " + lv + "mV <= limit " + mdata.lowVoltLimit + "mV";
                            break;
                        }
                    }
                }
            }
        }
        for (var param of htparam) {
            if (param) {
                for (var level of param.levels) {
                    ht = level[0];
                    if (ht != 205 && mdata.highTempLimit != 255) {
                        if (ht >= mdata.highTempLimit) {
                            haveWarn = true;
                            warnInfo += "\n                     " + param.name + ":         "+ ht + "°C >= limit " + mdata.highTempLimit + "°C";
                            break;
                        }
                    }
                }
            }
        }
        if (haveWarn == true) {
            warnInfo += "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            console.warn(warnInfo.yellow);
        }

        info.render("BatteryInfo_Lcfg.c", "BatteryInfo_Lcfg.c.tmpl", mdata);

        return {
            battnum: cfg.serialnum,
            celltempnum: cfg.celltempnum,
            heattempnum: cfg.heattempnum,
            poletempnum: cfg.poletempnum,
            totalCap: cfg.nominal.cap * cfg.initsoh / 100,
            initCap: cfg.nominal.cap * cfg.initsoc * cfg.initsoh / 10000,
            nominalCap: cfg.nominal.cap,
            acchargecurrent: cfg.nominal.acchargecurrent,
            dcchargecurrent: cfg.nominal.dcchargecurrent,
            totalvoltage: cfg.nominal.totalvoltage,
        }
    }
}
