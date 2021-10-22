module.exports = {
    process: function(cfgData, info) {
        var cfgs = JSON.parse(JSON.stringify(cfgData));

        //var indexmaps = [
        //    {name: '放电正', index: 0, def: 'POSITIVE_DISCHRGE'},
        //    {name: '慢充正', index: 1, def: 'POSITIVE_AC_CHARGE'},
        //    {name: '快充正', index: 2, def: 'POSITIVE_DC_CHARGE'},
        //    {name: '主正', index: 3, def: 'POSITIVE_MAIN'},
        //    {name: '预充', index: 4, def: 'PRECHARGE'},
        //    {name: '放电负', index: 5, def: 'NEGTIVE_DISCHARGE'},
        //    {name: '充电负', index: 6, def: 'NEGTIVE_CHARGE'},
        //    {name: '主负', index: 7, def: 'NEGTIVE_MAIN'},
        //    {name: '加热', index: 8, def: 'HEATER'},
        //    {name: '制冷', index: 9, def: 'COOLER'},
        //  {name: '用户1', index: 10, def: 'USER1'},
        //  {name: '用户2', index: 11, def: 'USER2'},
        //];

        var relayparams = {
            UNKNOWN: {name:'未知', onDelay: 30,  offDelay: 30, resistor: 'RELAYM_INVALID_RESISTOR', comments: '未知继电器' },
        };

        for (var cfg of cfgs) {
            if (!relayparams.hasOwnProperty(cfg.model)) {
                throw 'Unsupport relay model: ' + cfg.model;
            }
        }

        var relays = [];

        for (var cfg of cfgs) {
            var hv = 'HV_CHANNEL_NONE';
            var hv_user_function = false;
            var isPositive = true;
            var totalDecPercent = 40;
            var continueDecPercent = 20;
            var checkInterval = 20;
            var checkTimeout = 2000;
            var isSafeToOff = 'NULL';
            var auxContactDio = 'DIO_CHANNEL_NONE';
            var ioLevelOfAuxContactWhenOn = 'STD_HIGH';

            if (cfg.hasOwnProperty('hv')) hv = 'HV_CHANNEL_' + cfg.hv.toUpperCase();

            if (hv.endsWith ('()')) {
                hv = cfg.hv.slice(0,-2);
                hv_user_function = true;
            }

            if (cfg.hasOwnProperty('isPositive')) isPositive = cfg.isPositive
            if (cfg.hasOwnProperty('totalDecPercent')) totalDecPercent = cfg.totalDecPercent;
            if (cfg.hasOwnProperty('continueDecPercent')) continueDecPercent = cfg.continueDecPercent;
            if (cfg.hasOwnProperty('checkInterval')) checkInterval = cfg.checkInterval;
            if (cfg.hasOwnProperty('checkTimeout')) checkTimeout = cfg.checkTimeout;
            if (cfg.hasOwnProperty('isSafeToOff')) isSafeToOff = cfg.isSafeToOff;
            if (cfg.hasOwnProperty('auxContactDio') && cfg.auxContactDio != "") auxContactDio ='DIO_CHANNEL_' + cfg.auxContactDio;
            if (auxContactDio != 'DIO_CHANNEL_NONE') {
                if (!cfg.hasOwnProperty('ioLevelOfAuxContactWhenOn')) throw "You must define ioLevelOfAuxContactWhenOn";
                ioLevelOfAuxContactWhenOn = "STD_" + cfg.ioLevelOfAuxContactWhenOn.toUpperCase();
            }


            relays.push({
                name: cfg.name,
                def: 'RELAYM_FN_' + cfg.def,
                model: relayparams[cfg.model],
                hlss: cfg.hlss ? cfg.hlss : 'HLSS_CHANNEL_NONE',
                isSafeToOff: isSafeToOff,
                hv: hv,
                hvUserFunction: hv_user_function,
                isPositive: isPositive,
                totalDecPercent: totalDecPercent,
                continueDecPercent: continueDecPercent,
                checkInterval: checkInterval,
                checkTimeout: checkTimeout,
                auxContactDio: auxContactDio,
                ioLevelOfAuxContactWhenOn: ioLevelOfAuxContactWhenOn,
            });
        };

        var mdata = {
            relays: relays,
        }

        //console.log('================= mdata ==============')
        //console.log(JSON.stringify(mdata, null, '  '));

        info.render('RelayM_Lcfg.h', 'RelayM_Lcfg.h.tmpl', mdata);
        info.render('RelayM_Lcfg.c', 'RelayM_Lcfg.c.tmpl', mdata);

        return relays.map(x=>{return {name: x.name, def: x.def}});
    }
}
