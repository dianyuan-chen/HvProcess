module.exports = {
    process: function(cfgData, info) {
        var cfg = JSON.parse(JSON.stringify(cfgData));

        //console.log("================= currentm ==============")
        //console.log(JSON.stringify(cfg, null, "  "));

        var hallparams = {
            DHAB_S124_1: {name:"DHAB_S124大量程通道", offset: -2500,  mul: 5, div: 2, voltMin: 240, voltMax: 4800, supplyVolAdj: true, comments: "[0.5V, 4.5V] <=> [-500A, 500A]" },
            DHAB_S124_2: {name:"DHAB_S124小量程通道", offset: -2500,  mul: 3, div: 8, voltMin: 240, voltMax: 4800, supplyVolAdj: true, lowerHallMaxValue: 75, comments: "[0.5V, 4.5V] <=> [-75A, 75A]" },
            DHAB_S118_1: {name:"DHAB_S118大量程通道", offset: -2500,  mul: 7, div: 4, voltMin: 240, voltMax: 4800, supplyVolAdj: true, comments: "[0.5V, 4.5V] <=> [-350A, 350A]" },
            DHAB_S118_2: {name:"DHAB_S118小量程通道", offset: -2500,  mul: 3, div: 20, voltMin: 240, voltMax: 4800, supplyVolAdj: true, lowerHallMaxValue: 30, comments: "[0.5V, 4.5V] <=> [-30A, 30A]" },
            DHAB_S133_1: {name:"DHAB_S133大量程通道", offset: -2500,  mul: 15, div: 4, voltMin: 240, voltMax: 4800, supplyVolAdj: true, comments: "[0.5V, 4.5V] <=> [-750A, 750A]" },
            DHAB_S133_2: {name:"DHAB_S133小量程通道", offset: -2500,  mul: 3, div: 8, voltMin: 240, voltMax: 4800, supplyVolAdj: true, lowerHallMaxValue: 30, comments: "[0.5V, 4.5V] <=> [-75A, 75A]" },
            DHAB_S137_1: {name:"DHAB_S137大量程通道", offset: -2500,  mul: 5, div: 1, voltMin: 240, voltMax: 4800, supplyVolAdj: true, comments: "[0.5V, 4.5V] <=> [-1000A, 1000A]" },
            DHAB_S137_2: {name:"DHAB_S137小量程通道", offset: -2500,  mul: 3, div: 8, voltMin: 240, voltMax: 4800, supplyVolAdj: true, lowerHallMaxValue: 30, comments: "[0.5V, 4.5V] <=> [-75A, 75A]" },
            FS300E2T: {name:"飞轩FS300E2T,300A量程", offset: -2500,  mul: 3, div: 2, voltMin: 240, voltMax: 4800, supplyVolAdj: false, comments: "[0.5V, 4.5V] <=> [-300A, 300A]" },
            FS500E2T: {name:"飞轩FS500E2T,500A量程", offset: -2500,  mul: 5, div: 2, voltMin: 240, voltMax: 4800, supplyVolAdj: false, comments: "[0.5V, 4.5V] <=> [-500A, 500A]" },
            FS600E2T: {name:"飞轩FS600E2T,600A量程", offset: -2500,  mul: 6, div: 2, voltMin: 240, voltMax: 4800, supplyVolAdj: false, comments: "[0.5V, 4.5V] <=> [-600A, 600A]" },
            FS700E2T: {name:"飞轩FS700E2T,700A量程", offset: -2500,  mul: 7, div: 2, voltMin: 240, voltMax: 4800, supplyVolAdj: false, comments: "[0.5V, 4.5V] <=> [-700A, 700A]" },
            FS300BT: {name:"飞轩FS300BT,300A量程", offset: -2500,  mul: 3, div: 2, voltMin: 240, voltMax: 4800, supplyVolAdj: false, comments: "[0.5V, 4.5V] <=> [-300A, 300A]" },
            FS600BT: {name:"飞轩FS600BT,600A量程", offset: -2500,  mul: 6, div: 2, voltMin: 240, voltMax: 4800, supplyVolAdj: false, comments: "[0.5V, 4.5V] <=> [-600A, 600A]" },
            FS1200_EK2T: {name:"飞轩FS1200-EK2T,1200A量程", offset: -2500,  mul: 12, div: 2, voltMin: 240, voltMax: 4800, supplyVolAdj: false, comments: "[0.5V, 4.5V] <=> [-1200A, 1200A]" },
            FS1500_EK4T: {name:"飞轩FS1500-EK4T,1500A量程", offset: -2500,  mul: 15, div: 2, voltMin: 240, voltMax: 4800, supplyVolAdj: false, comments: "[0.5V, 4.5V] <=> [-1500A, 1500A]" },
            FS2000_EK2T: {name:"飞轩FS2000-EK2T,2000A量程", offset: -2500,  mul: 20, div: 2, voltMin: 240, voltMax: 4800, supplyVolAdj: false, comments: "[0.5V, 4.5V] <=> [-2000A, 2000A]" },
            WHK30_350DHAB5S2L_1: {name:"启东双赢30/350A大量程", offset: -2500,  mul: 7, div: 4, voltMin: 50, voltMax: 5200, supplyVolAdj: true, comments: "[0.5V, 4.5V] <=> [-350A, 350A]" },
            WHK30_350DHAB5S2L_2: {name:"启东双赢30/350A小量程", offset: -2500,  mul: 3, div: 20, voltMin: 50, voltMax: 5200, supplyVolAdj: true, lowerHallMaxValue: 30, comments: "[0.5V, 4.5V] <=> [-30A, 30A]" },
            EHMWX911C500: {name:"松下EHMWX911C500,500A量程", offset: -2500,  mul: 5, div: 2, voltMin: 240, voltMax: 4800, supplyVolAdj: false, comments: "[0.5V, 4.5V] <=> [-500A, 500A]" },
            HAH1BVW_S01: {name:"LEM 100A单量程", offset: -2500,  mul: 1, div: 2, voltMin: 260, voltMax: 4740, supplyVolAdj: true, comments: "[0.5V, 4.5V] <=> [-100A, 100A]" },
            HAH1BVW_S02: {name:"LEM 200A单量程", offset: -2500,  mul: 2, div: 2, voltMin: 260, voltMax: 4740, supplyVolAdj: true, comments: "[0.5V, 4.5V] <=> [-200A, 200A]" },
            HAH1BVW_S03: {name:"LEM 300A单量程", offset: -2500,  mul: 3, div: 2, voltMin: 260, voltMax: 4740, supplyVolAdj: true, comments: "[0.5V, 4.5V] <=> [-300A, 300A]" },
            HAH1BVW_S12: {name:"LEM 1200A单量程", offset: -2500,  mul: 6, div: 1, voltMin: 260, voltMax: 4740, supplyVolAdj: true, comments: "[0.5V, 4.5V] <=> [-1200A, 1200A]" },
            HAH1BV_S02: {name:"LEM 500A单量程", offset: -2500,  mul: 5, div: 2, voltMin: 260, voltMax: 4740, supplyVolAdj: true, comments: "[0.5V, 4.5V] <=> [-500A, 500A]" },
            WHK20BS5S2: {name:"启东双赢20A单量程", offset: -2500,  mul: 1, div: 10, voltMin: 50, voltMax: 5200, supplyVolAdj: true, comments: "[0.5V, 4.5V] <=> [-20A, 20A]" },
            WHK50BS5S2: {name:"启东双赢50A单量程", offset: -2500,  mul: 1, div: 4, voltMin: 50, voltMax: 5200, supplyVolAdj: true, comments: "[0.5V, 4.5V] <=> [-50A, 50A]" },
            WHK300EA5S2S: {name:"启东双赢300A单量程", offset: -2500, mul: 3, div: 2, voltMin: 240, voltMax: 4800, supplyVolAdj: true, comments:"[0.5V, 4.5V] <=> [-300A, 300A]" },
            WHK500EA5S2S: {name:"启东双赢500A单量程", offset: -2500, mul: 5, div: 2, voltMin: 240, voltMax: 4800, supplyVolAdj: true, comments:"[0.5V, 4.5V] <=> [-500A, 500A]" },
            CS1000BT5: {name:"茶花港联1000A单量程", offset: -2500, mul: 5, div: 1, voltMin: 240, voltMax: 4800, supplyVolAdj: true, comments:"[0.5V, 4.5V] <=> [-1000A, 1000A]" },
        };

        var shuntparams = {
            WSBM8518L1000: {name: "WSBM8518,500A, 50mv", maxVol: 60000, resistor: 100, tempDrift: 0},
            FL2200A25mV: {name:"福来2型,200A,25mV", maxVol: 35000, resistor: 125, tempDrift: 0},
            FL2300A25mV: {name:"福来2型,300A,25mV", maxVol: 35000, resistor: 83.3, tempDrift: 0},
            FL2300A50mV: {name:"福来2型,300A,50mV", maxVol: 60000, resistor: 166.7, tempDrift: 0},
            FL2400A50mV: {name:"福来2型,400A,50mV", maxVol: 60000, resistor: 125, tempDrift: 0},
            FL2500A50mV: {name:"福来2型,500A,50mV", maxVol: 60000, resistor: 100, tempDrift: 0},
            FL2600A50mV: {name:"福来2型,600A,50mV", maxVol: 60000, resistor: 83.3, tempDrift: 0},
            FL2650A50mV: {name:"福来2型,650A,50mV", maxVol: 60000, resistor: 76.9, tempDrift: 0},
            FL230A75mV: {name:"福来2型,30A,75mV", maxVol: 100000, resistor: 2500, tempDrift: 0},
            FL250A75mV: {name:"福来2型,50A,75mV", maxVol: 100000, resistor: 1500, tempDrift: 0},
            FL2100A75mV: {name:"福来2型,100A,75mV", maxVol: 100000, resistor: 750, tempDrift: 0},
            FL2150A75mV: {name:"福来2型,150A,75mV", maxVol: 100000, resistor: 500, tempDrift: 0},
            FL2200A75mV: {name:"福来2型,200A,75mV", maxVol: 100000, resistor: 375, tempDrift: 0},
            FL2250A75mV: {name:"福来2型,250A,75mV", maxVol: 100000, resistor: 300, tempDrift: 0},
            FL2300A75mV: {name:"福来2型,300A,75mV", maxVol: 100000, resistor: 250, tempDrift: 0},
            FL2400A75mV: {name:"福来2型,400A,75mV", maxVol: 100000, resistor: 187.5, tempDrift: 0},
            FL2500A75mV: {name:"福来2型,500A,75mV", maxVol: 100000, resistor: 150, tempDrift: 0},
            FL2600A75mV: {name:"福来2型,600A,75mV", maxVol: 100000, resistor: 125, tempDrift: 0},
            FL2650A75mV: {name:"福来2型,650A,75mV", maxVol: 100000, resistor: 115.4, tempDrift: 0},
            FL2750A75mV: {name:"福来2型,750A,75mV", maxVol: 100000, resistor: 100, tempDrift: 0},
            FL2800A75mV: {name:"福来2型,800A,75mV", maxVol: 100000, resistor: 93.75, tempDrift: 0},
            FL21000A75mV: {name:"福来2型,1000A,75mV", maxVol: 100000, resistor: 75, tempDrift: 0},
            FL21200A75mV: {name:"福来2型,1200A,75mV", maxVol: 100000, resistor: 62.5, tempDrift: 0},
            FL22000A75mV: {name:"福来2型,2000A,75mV", maxVol: 100000, resistor: 37.5, tempDrift: 0},
        };

        if (!hallparams.hasOwnProperty(cfg.hall1.model)) {
            throw "Hall model not support for channel 1: " + cfg.hall1.model;
        }

        if (!hallparams.hasOwnProperty(cfg.hall2.model)) {
            throw "Hall model not support for channel 2: " + cfg.hall2.model;
        }

        if (!shuntparams.hasOwnProperty(cfg.shunt.model)) {
            throw "Shunt model not support: " + cfg.shunt.model
        }

        var shuntsensor = cfg.shunt;
        for (var x in shuntparams[cfg.shunt.model]) {
            shuntsensor[x] = shuntparams[cfg.shunt.model][x];
        }

        var hall1sensor = cfg.hall1;
        for (var x in hallparams[cfg.hall1.model]) {
            hall1sensor[x] = hallparams[cfg.hall1.model][x];
        }

        var hall2sensor = cfg.hall2;
        for (var x in hallparams[cfg.hall2.model]) {
            hall2sensor[x] = hallparams[cfg.hall2.model][x];
        }

        var isDualRange = false;
        var lowerHallMaxValue = 0;
        var h1model = cfg.hall1.model.match(/(.*)_1$/);
        var h2model = cfg.hall2.model.match(/(.*)_2$/);
        if (h1model && h1model && h1model[1] == h2model[1]) {
            isDualRange = true;
            lowerHallMaxValue = cfg.hall2.lowerHallMaxValue * 10;
        }

        var mainIndex = ['hall1', 'hall2', 'shunt', 'userdef1', 'userdef2'].indexOf(cfg.main.channel);
        var mainRedundantIndex = ['hall1', 'hall2', 'shunt', 'userdef1', 'userdef2'].indexOf(cfg.main.redundant);
        var heaterIndex = ['hall1', 'hall2', 'shunt', 'userdef1', 'userdef2'].indexOf(cfg.heater.channel);
        var heaterRedundantIndex = ['hall1', 'hall2', 'shunt', 'userdef1', 'userdef2'].indexOf(cfg.heater.redundant);

        if (mainIndex < 0) throw 'Current channel main must be one of "hall1", "hall2", "shunt", "userdef1" or "userdef2"';
        if (mainIndex == mainRedundantIndex || mainIndex == heaterIndex || mainIndex == heaterRedundantIndex) throw cfg.main.channel + " selected by multi";
        if (mainRedundantIndex >=0 && (mainRedundantIndex == heaterIndex || mainRedundantIndex == heaterRedundantIndex)) throw cfg.main.redundant + " selected by multi";
        if (heaterIndex >= 0 && heaterIndex == heaterRedundantIndex)   throw cfg.heater.channel + " selected by multi";

        var currentmcfg = {
            isDualRange: isDualRange,
            lowerHallMaxValue: lowerHallMaxValue,
            main: {
                enable: mainIndex >= 0,
                channel: cfg.main.channel.toUpperCase(),
                redundancyEnable: mainRedundantIndex >= 0,
                redundancyChannel: cfg.main.redundant.toUpperCase(),
            },
            heater: {
                enable: heaterIndex >= 0,
                channel: cfg.heater.channel.toUpperCase(),
                redundancyEnable: heaterRedundantIndex >= 0,
                redundancyChannel: cfg.heater.redundant.toUpperCase(),
            },
            autoCalibLimit: {
                hall1: cfg.hall1.autoCalibLimit * 10,
                hall2: cfg.hall2.autoCalibLimit * 10,
                shunt: cfg.shunt.autoCalibLimit * 10,
            },
            zeroFilter: {
                hall1: cfg.hall1.zeroFilterValue * 10,
                hall2: cfg.hall2.zeroFilterValue * 10,
                shunt: cfg.shunt.zeroFilterValue * 10,
            },
        };

        var mdata = {
            hall1sensor: hall1sensor,
            hall2sensor: hall2sensor,
            shuntsensor: shuntsensor,
            currentmcfg: currentmcfg,
            usersensor1_enable: cfg.main.channel.toUpperCase() == 'USERDEF1' || cfg.main.redundant.toUpperCase() == 'USERDEF1' || cfg.heater.channel.toUpperCase() == 'USERDEF1' || cfg.heater.redundant.toUpperCase() == 'USERDEF1',
            usersensor2_enable: cfg.main.channel.toUpperCase() == 'USERDEF2' || cfg.main.redundant.toUpperCase() == 'USERDEF2' || cfg.heater.channel.toUpperCase() == 'USERDEF2' || cfg.heater.redundant.toUpperCase() == 'USERDEF2',
        };

        //console.log("================= currentm ==============")
        //console.log(JSON.stringify(mdata, null, "  "));

        info.render("CurrentM_Lcfg.c", "CurrentM_Lcfg.c.tmpl", mdata);
        info.render("CurrentM_Lcfg.h", "CurrentM_Lcfg.h.tmpl", mdata);
    }
}
