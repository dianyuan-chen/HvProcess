module.exports = {
    process: function(cfgData, info) {
        var cfg = JSON.parse(JSON.stringify(cfgData));

        var xx = cfg.server.match(/([\.0-9_a-zA-Z]*):([0-9]*)/);
        if (!xx || parseInt(xx[2]) >= 65535) {
            throw "server format error:" + server;
        }



        var mdata = {
            rtMsgInterval: Math.round(cfg.rtmsg_interval * 1000),
            serverAddr: xx[1],
            serverPort: xx[2],
        };

        if (cfg.hasOwnProperty('apn')) {
            mdata.apn = cfg.apn;
        }


        //console.log("================= gb32960 ==============")
        //console.log(JSON.stringify(mdata, null, "  "));

        info.render("GB32960_Lcfg.c", "GB32960_Lcfg.c.tmpl", {dat:mdata});
    }
}
