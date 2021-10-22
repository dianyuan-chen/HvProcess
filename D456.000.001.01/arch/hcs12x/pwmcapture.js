module.exports = {
    process: function(cfgData, info) {
        if (info.SystemConnection.PCBA == 'UPA650') {
            cfgData['SIGIN2'].enable = false;
        }

        var d =  {
            mdata: cfgData
        }
        // console.log(info);
        info.render("PwmCapture_Lcfg.h", "PwmCapture_Lcfg.h.tmpl", d);
        info.render("PwmCapture_Lcfg.c", "PwmCapture_Lcfg.c.tmpl", d);

        return {};
    }
}
