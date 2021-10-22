module.exports = {
    process: function(cfgData, info) {

        var rxsduids = [];
        var txsduids = [];

        if (info.SystemConnection.BcuIsAllInOne) {
            rxsduids.push("BMU_0");
            txsduids.push("BMU_0");
        } else if (info.SystemConnection.M36Num > 0) {
            for (var i=0; i<info.SystemConnection.M36Num; i++) {
                rxsduids.push("BMU_" + i);
                txsduids.push("BMU_" + i);
            }
        } else {
            rxsduids.push("BMU_0");
            txsduids.push("BMU_0");
        }

        var mdata = {
            UseLtcAllInOne: ((info.SystemConnection.BcuIsAllInOne || info.SystemConnection.M36Num) && info.SystemConnection.PCBA == 'UPC6000'),
            UseIslAllInOne: (info.SystemConnection.BcuIsAllInOne && info.SystemConnection.PCBA == 'UPA650'),
            M36Num: info.SystemConnection.M36Num,
        };

        info.render("InnerTp_Lcfg.c", "InnerTp_Lcfg.c.tmpl", mdata);
        info.render("InnerTp_Lcfg.h", "InnerTp_Lcfg.h.tmpl", mdata);
        return {
            rxsduids:rxsduids,
            txsduids:txsduids,
        }
    }
}
