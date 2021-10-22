module.exports = {
    process: function(cfgData, info) {
        var cfg = JSON.parse(JSON.stringify(cfgData));

        var toTime = (str) => {
            xx = str.match(/^(\d+):(\d+)$/);
            if (!xx) throw "Wrong time string format";
            var h = parseInt(xx[1], 10);
            var m = parseInt(xx[2], 10);
            if (h <0 || h >= 24 || m < 0 || m > 59) {
                throw "Wrong time string format";
            }

            return h *3600 + m * 60;
        }

        if (typeof(cfg.wakeupTimeForOTA) == 'number') {
            cfg['timeOrDelayToWakeupForOTA'] = 'RUNTIMEM_WAKEUP_PARAM_IS_DELAY';
            if (cfg.wakeupTimeForOTA < 90) cfg.wakeupTimeForOTA = 90;
        } else if (typeof(cfg.wakeupTimeForOTA) == 'string') {
            cfg['timeOrDelayToWakeupForOTA'] = 'RUNTIMEM_WAKEUP_PARAM_IS_TIME';
            cfg.wakeupTimeForOTA = toTime(cfg.wakeupTimeForOTA);
        } else {
            throw "wakeupTimeForOTA format error";
        }

        if (cfg.chargeEndOTA) {
            cfg.wakeupTimeForOTA = 0;
            cfg['timeOrDelayToWakeupForOTA'] = 'RUNTIMEM_WAKEUP_OFF';
            cfg.wakeupTimeForData = 0;
            cfg['timeOrDelayToWakeupForData'] = 'RUNTIMEM_WAKEUP_OFF';
        }

        if (!cfg.userIsWakeup || !cfg.userIsWakeup.func) {
            cfg.userIsWakeup = {func: 'NULL', inc: ''};
        }

        if (! cfg.cpInvalidTimeFilter) {
            cfg.cpInvalidTimeFilter = 0;
        }

        if (typeof(cfg.wakeupTimeForData) == 'number') {
            if (cfg.wakeupTimeForData == 0) {
                cfg['timeOrDelayToWakeupForData'] = 'RUNTIMEM_WAKEUP_OFF';
            } else {
                cfg['timeOrDelayToWakeupForData'] = 'RUNTIMEM_WAKEUP_PARAM_IS_DELAY';
                if (cfg.wakeupTimeForData < 90) cfg.wakeupTimeForData = 90;
            }
        } else if (typeof(cfg.wakeupTimeForData) == 'string') {
            cfg['timeOrDelayToWakeupForData'] = 'RUNTIMEM_WAKEUP_PARAM_IS_TIME';
            cfg.wakeupTimeForData = toTime(cfg.wakeupTimeForData);
        } else {
            throw "wakeupTimeForData format error";
        }

        //console.log("================= runtimem ==============")
        //console.log(JSON.stringify(cfg, null, "  "));
        info.render("RuntimeM_Cfg.h", "RuntimeM_Cfg.h.tmpl", {dat:cfg});
        info.render("RuntimeM_Lcfg.c", "RuntimeM_Lcfg.c.tmpl", {dat:cfg});
    }
}
