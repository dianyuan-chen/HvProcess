module.exports = {
    process: function(cfgData, info) {
        var cfg = JSON.parse(JSON.stringify(cfgData));


        //console.log("================= Charge ==============")
        //console.log(JSON.stringify(cfg, null, "  "));
        var wakeupmap = [
            {wakeup:"NONE", def:"NONE"},
            {wakeup:"ON", def:"KEY_ON"},
            {wakeup:"CP", def:"CP_HIGH"},
            {wakeup:"OBC", def:"OBC_POWER"},
            {wakeup:"DCC", def:"CHARGER_READY"},
        ];

        var acmodemap = [
            {mode:"NONE", def: "CONNECT_NONE"},
            {mode:"USER", def: "CONNECT_SELF_DEFINE"},
            {mode:"COMM", def: "CONNECT_COMMUNICATION"},
            {mode:"DIN", def: "CONNECT_DIN"},
            {mode:"CURRENT", def: "CONNECT_CURRENT"},
            {mode:"GB_MODE1_CONNECT_B", def: "GB_AC_MODE1_CONNECT_B"},
            {mode:"GB_MODE2_CONNECT_B", def: "GB_AC_MODE2_CONNECT_B"},
            {mode:"GB_MODE3_CONNECT_A", def: "GB_AC_MODE3_CONNECT_A"},
            {mode:"GB_MODE3_CONNECT_B", def: "GB_AC_MODE3_CONNECT_B"},
            {mode:"GB_MODE3_CONNECT_C", def: "GB_AC_MODE3_CONNECT_C"},
        ];

        var dcmodemap = [
            {mode:"NONE", def: "CONNECT_NONE"},
            {mode:"USER", def: "CONNECT_SELF_DEFINE"},
            {mode:"COMM", def: "CONNECT_COMMUNICATION"},
            {mode:"DIN", def: "CONNECT_DIN"},
            {mode:"CURRENT", def: "CONNECT_CURRENT"},
            {mode:"GB_DC", def: "GB_DC_MODE"},
        ];

        var dc2modemap = [
            {mode:"NONE", def: "CONNECT_NONE"},
            {mode:"USER", def: "CONNECT_SELF_DEFINE"},
            {mode:"COMM", def: "CONNECT_COMMUNICATION"},
            {mode:"DIN", def: "CONNECT_DIN"},
            {mode:"CURRENT", def: "CONNECT_CURRENT"},
            {mode:"GB_DC", def: "GB_DC_MODE"},
            {mode:"GB_MODE1_CONNECT_B", def: "GB_AC_MODE1_CONNECT_B"},
            {mode:"GB_MODE2_CONNECT_B", def: "GB_AC_MODE2_CONNECT_B"},
            {mode:"GB_MODE3_CONNECT_A", def: "GB_AC_MODE3_CONNECT_A"},
            {mode:"GB_MODE3_CONNECT_B", def: "GB_AC_MODE3_CONNECT_B"},
            {mode:"GB_MODE3_CONNECT_C", def: "GB_AC_MODE3_CONNECT_C"},
        ];

        var elmodelmap = [
            {model: "EBUSBAR_FB_LOCK_SWON", driveType: "EL_LockerDriveHBridge", feedBackWhenLock:'HIGH', feedBackWhenLock:'LOW', lockTimeDuration:100, unlockTimeDuration: 1000, operationDuration: 100}
        ];

        if (["NONE", "USER", "GB2015"].indexOf(cfg.ac.protocol) < 0) {
            throw "Unsupport ac protocol: " + cfg.ac.protocol;
        }
        if (["NONE", "USER", "GB2015"].indexOf(cfg.dc.protocol) < 0) {
            throw "Unsupport dc protocol: " + cfg.dc.protocol;
        }
        if (cfg.hasOwnProperty('dc2')) {
            if (["NONE", "GB2015"].indexOf(cfg.dc2.protocol) < 0) {
                throw "Unsupport dc protocol: " + cfg.dc.protocol;
            }
        }

        //var el = elmodelmap.find(x=> x.model == cfg.el.model);
        //if (!el) {
        //    throw "Unsupport el model: " + cfg.el.model;
        //}
        var el = {};
        if (["HBridge", "HighLevel", "LowLevel"].indexOf(cfg.el.driveType) < 0) {
            throw "Unknow EL driveType:" + cfg.el.driveType;
        }

        el.enable = cfg.el.enable;
        el.driveType = "EL_LockerDrive" + cfg.el.driveType;
        el.lockTime = cfg.el.lockTime;
        el.unlockTime = cfg.el.unlockTime;
        el.lockFeedback = cfg.el.lockFeedback;
        el.unlockFeedback = cfg.el.unlockFeedback;
        el.ctlMax = cfg.el.ctlMax ? cfg.el.ctlMax : 1;

        var w = wakeupmap.find(x=> x.wakeup == cfg.ac.wakeup);
        if (!w) {
            throw "Unsupport AC wakeup: " + cfg.ac.wakeup;
        }

        var m = acmodemap.find(x=> x.mode == cfg.ac.mode);
        if (!m) {
            throw "Unsupport AC mode: " + cfg.ac.mode;
        }

        var acrelay = "RELAYM_FN_NONE";
        if (cfg.ac.relay) {
                acrelay = info.RelayM.find(x=>x.name == cfg.ac.relay);
            if (acrelay) {
                acrelay = acrelay.def;
            } else {
                throw "Can not find relay:" + cfg.ac.relay
            }
        }


        var ac = {
            wakeup: "RUNTIMEM_WAKEUP_SIGNAL_BIT_" + w.def,
            type: "CHARGECONNECTM_" + m.def,
            relay: acrelay,
            dinChannel: "DIGITALINPUT_CHANNEL_NONE",
            dinType: "DIGITALINPUT_TYPE_LEVEL",
            userModeFunction: ["", "NULL"],
        };
        if (ac.type == "CHARGECONNECTM_CONNECT_DIN") {
            if (cfg.ac.dintype == "LEVEL") {
                if (["BCU_DIN1", "BCU_DIN2"].indexOf(cfg.ac.dinChannel) < 0) {
                    throw "Unsupport dinChannel: " + cfg.ac.dinChannel;
                }
                ac.dinType = "DIGITALINPUT_TYPE_LEVEL";
                ac.dinChannel = "DIGITALINPUT_" + cfg.ac.dinChannel;
            } else if (cfg.ac.dintype == "SW") {
                if (["BCU_SW1", "BCU_SW2"].indexOf(cfg.ac.dinChannel) < 0) {
                    throw "Unsupport dinChannel: " + cfg.ac.dinChannel;
                }
                ac.dinChannel = "DIGITALINPUT_" + cfg.ac.dinChannel;
                ac.dinType = "DIGITALINPUT_TYPE_SWITCH";
            } else if (cfg.ac.dintype == "WAKEUP_SIGNAL") {
                if ("OBC" == cfg.ac.dinChannel) ac.dinChannel = "RUNTIMEM_WAKEUP_SIGNAL_BIT_OBC_POWER";
                else if ("DCC" == cfg.ac.dinChannel) ac.dinChannel = "RUNTIMEM_WAKEUP_SIGNAL_BIT_CHARGER_READY";
                else throw "Unsupport dinChannel: " + cfg.ac.dinChannel;
                ac.dinType = "DIGITALINPUT_TYPE_WAKEUP_SIGNAL";
            } else {
                throw "Unsupport dinType: " + cfg.ac.dintype;
            }
        }

        if (ac.type == 'CHARGECONNECTM_CONNECT_SELF_DEFINE') {
            ac.userModeFunction = cfg.ac.userModeFunction;
        }

        var w = wakeupmap.find(x=> x.wakeup == cfg.dc.wakeup);
        if (!w) {
            throw "Unsupport DC wakeup: " + cfg.dc.wakeup;
        }

        m = dcmodemap.find(x=> x.mode == cfg.dc.mode);
        if (!m) {
            throw "Unsupport DC mode: " + cfg.dc.mode;
        }

        var dcrelay = "RELAYM_FN_NONE";
        if (cfg.dc.relay) {
                dcrelay = info.RelayM.find(x=>x.name == cfg.dc.relay);
            if (dcrelay) {
                dcrelay = dcrelay.def;
            } else {
                throw "Can not find relay:" + cfg.dc.relay
            }
        }

        var dc = {
            wakeup: "RUNTIMEM_WAKEUP_SIGNAL_BIT_" + w.def,
            type: "CHARGECONNECTM_" + m.def,
            relay: dcrelay,
            dinChannel: "DIGITALINPUT_CHANNEL_NONE",
            dinType: "DIGITALINPUT_TYPE_LEVEL",
            userModeFunction: ["", "NULL"],
        };

        if (dc.type == "CHARGECONNECTM_CONNECT_DIN") {
            if (cfg.dc.dintype == "LEVEL") {
                if (["BCU_DIN1", "BCU_DIN2"].indexOf(cfg.dc.dinChannel) < 0) {
                    throw "Unsupport dinChannel: " + cfg.dc.dinChannel;
                }
                dc.dinType = "DIGITALINPUT_TYPE_LEVEL";
                dc.dinChannel = "DIGITALINPUT_" + cfg.dc.dinChannel;
            } else if (cfg.dc.dintype == "SW") {
                if (["BCU_SW1", "BCU_SW2"].indexOf(cfg.dc.dinChannel) < 0) {
                    throw "Unsupport dinChannel: " + cfg.dc.dinChannel;
                }
                dc.dinChannel = "DIGITALINPUT_" + cfg.dc.dinChannel;
                dc.dinType = "DIGITALINPUT_TYPE_SWITCH";
            } else if (cfg.dc.dintype == "WAKEUP_SIGNAL") {
                if ("OBC" == cfg.dc.dinChannel) dc.dinChannel = "RUNTIMEM_WAKEUP_SIGNAL_BIT_OBC_POWER";
                else if ("DCC" == cfg.dc.dinChannel) dc.dinChannel = "RUNTIMEM_WAKEUP_SIGNAL_BIT_CHARGER_READY";
                else throw "Unsupport dinChannel: " + cfg.dc.dinChannel;
                dc.dinType = "DIGITALINPUT_TYPE_WAKEUP_SIGNAL";
            } else {
                throw "Unsupport dinType: " + cfg.dc.dintype;
            }
        }


        if (dc.type == 'CHARGECONNECTM_CONNECT_SELF_DEFINE') {
            dc.userModeFunction = cfg.dc.userModeFunction;
        }

        //dc2
        if (cfg.hasOwnProperty('dc2')) {
            var w = wakeupmap.find(x=> x.wakeup == cfg.dc2.wakeup);
            if (!w) {
                throw "Unsupport DC2 wakeup: " + cfg.dc2.wakeup;
            }

            m = dc2modemap.find(x=> x.mode == cfg.dc2.mode);
            if (!m) {
                throw "Unsupport DC2 mode: " + cfg.dc2.mode;
            }

            var dcrelay = "RELAYM_FN_NONE";
            if (cfg.dc2.relay) {
                    dcrelay = info.RelayM.find(x=>x.name == cfg.dc2.relay);
                if (dcrelay) {
                    dcrelay = dcrelay.def;
                } else {
                    throw "Can not find relay:" + cfg.dc2.relay
                }
            }

            var dc2 = {
                protocol: "EXTERNCANCOMM_PROTOCOL_" + cfg.dc2.protocol,
                wakeup: "RUNTIMEM_WAKEUP_SIGNAL_BIT_" + w.def,
                type: "CHARGECONNECTM_" + m.def,
                relay: dcrelay,
                dinChannel: "DIGITALINPUT_CHANNEL_NONE",
                dinType: "DIGITALINPUT_TYPE_LEVEL",
                userModeFunction: ["", "NULL"],
            };

            if (dc2.type == "CHARGECONNECTM_CONNECT_DIN") {
                if (cfg.dc2.dintype == "LEVEL") {
                    if (["BCU_DIN1", "BCU_DIN2"].indexOf(cfg.dc2.dinChannel) < 0) {
                        throw "Unsupport dinChannel: " + cfg.dc2.dinChannel;
                    }
                    dc2.dinType = "DIGITALINPUT_TYPE_LEVEL";
                    dc2.dinChannel = "DIGITALINPUT_" + cfg.dc2.dinChannel;
                } else if (cfg.dc2.dintype == "SW") {
                    if (["BCU_SW1", "BCU_SW2"].indexOf(cfg.dc2.dinChannel) < 0) {
                        throw "Unsupport dinChannel: " + cfg.dc2.dinChannel;
                    }
                    dc2.dinChannel = "DIGITALINPUT_" + cfg.dc2.dinChannel;
                    dc2.dinType = "DIGITALINPUT_TYPE_SWITCH";
                } else if (cfg.dc2.dintype == "WAKEUP_SIGNAL") {
                    if ("OBC" == cfg.dc2.dinChannel) dc2.dinChannel = "RUNTIMEM_WAKEUP_SIGNAL_BIT_OBC_POWER";
                    else if ("DCC" == cfg.dc2.dinChannel) dc2.dinChannel = "RUNTIMEM_WAKEUP_SIGNAL_BIT_CHARGER_READY";
                    else throw "Unsupport dinChannel: " + cfg.dc2.dinChannel;
                    dc2.dinType = "DIGITALINPUT_TYPE_WAKEUP_SIGNAL";
                } else {
                    throw "Unsupport dinType: " + cfg.dc2.dintype;
                }
            }


            if (dc2.type == 'CHARGECONNECTM_CONNECT_SELF_DEFINE') {
                dc2.userModeFunction = cfg.dc2.userModeFunction;
            }
        } else {
            var dc2 = {
                wakeup: "RUNTIMEM_WAKEUP_SIGNAL_BIT_NONE",
                protocol: "EXTERNCANCOMM_PROTOCOL_NONE",
                type: "CHARGECONNECTM_CONNECT_NONE",
                relay: "RELAYM_FN_NONE",
                dinChannel: "DIGITALINPUT_CHANNEL_NONE",
                dinType: "DIGITALINPUT_TYPE_LEVEL",
                userModeFunction: ["", "NULL"],
            };
        }

        var mdata = {
            protocol: {
                ac: "CHARGERCOMM_PROTOCOL_" + cfg.ac.protocol,
                dc: "CHARGERCOMM_PROTOCOL_" + cfg.dc.protocol,
            },
            dc: dc,
            dc2: dc2,
            ac: ac,
            el: el,
        };

        //console.log("================= Charge ==============")
        //console.log(JSON.stringify(mdata, null, "  "));

        info.render("Charge_Lcfg.c", "Charge_Lcfg.c.tmpl", mdata);
    }
}
