module.exports = {
    process: function(cfgData, info) {
        /*
         * 增加代码，验证配置参数
         */

        var mdata = {
            Charging: cfgData.Charging,
            Static: cfgData.Static,
        };

        if (cfgData.hasOwnProperty('Remote')) {
            mdata.Remote = cfgData.Remote
        } else {
            mdata.Remote = {enable: 0}
        }
        info.render("BalanceM_LCfg.c", "BalanceM_LCfg.c.tmpl", mdata);

        return {}
    }
}
