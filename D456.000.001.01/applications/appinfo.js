module.exports = {
    process: function(cfgData, info) {
        var cfg = JSON.parse(JSON.stringify(cfgData));
        var child_process = require("child_process");

        var srcCommitID;
        try {
            srcCommitID = child_process.execSync('git rev-parse HEAD', {cwd: __dirname}).toString().trim();
        } catch(err) {
            srcCommitID = "0000000000000000000000000000000000000000";
        }
        try {
            child_process.execSync('git diff --quiet', {cwd: __dirname});
            child_process.execSync('git diff --cached --quiet', {cwd: __dirname});
        } catch(err) {
            srcCommitID = srcCommitID.slice(0, 20);
        }

        var fwAddrSpace = ""

        try {
            fwAddrSpace = process.env.COPY;
        } catch (err) {
        }

        if (fwAddrSpace == "B") {
            fwAddrSpace = "Boot_FWCopyBAddrSpace"
        } else {
            fwAddrSpace = "Boot_FWCopyAAddrSpace"
        }


        const isValidOid = (oid) => {
            var ymd = oid.match(/^U[DO](\d{4})(\d{2})(\d{2})\d{3}$/)
            if (!ymd) return false;
            var isoString = ymd.slice(1).join('-');
            var d;
            if (!((d = new Date(isoString)) | 0)) return false;
            return d.toISOString().slice(0, 10) == isoString;
        }

        if (cfg.releaseType != "T" && cfg.releaseType != "R") throw "AppInfo.releaseType has wrong format";

        var releaseName;
        try {
            releaseName = info.SystemConnection.BcuType;
        } catch(e) {
            releaseName = cfg.releaseName;
        }

        if (!releaseName) {
            throw "What's the releaseName?!"
        }

        var appVersion = "";

        if (cfg.pid != "" || cfg.requireVer != "") {
            if (!/^[C,S,D]\d{3}\.\d{3}\.\d{3}\.\d{2}$/.test(cfg.pid)) throw "AppInfo.pid has wrong format";
            if (!/^\d+\.\d+$/.test(cfg.requireVer)) throw "AppInfo.requireVer has wrong format";

            releaseName += "_" + cfg.pid;
            //releaseName += "_" + cfg.oid;
            releaseName += "_" + cfg.releaseType;
            releaseName += cfg.requireVer + "." + cfg.buildVer;
            appVersion = "{" + (cfg.requireVer + "." + cfg.buildVer).split(".").map(x=>x+'U').join() + "}";
        } else {
            releaseName += "_" + cfg.releaseType;
            releaseName += info.LibInfo.masterVersion;
        }

        const compatibleHWList = {
            'UPA650': ['V1.03'],
            'UPC6000': ['V1.03', 'V1.02_FOR_CHUHAN', 'V1.03_FOR_DIANKA'],
        }

        const compatibleHwMap = {
            'UPA650': {
                "V1.00": 1<<2,
                "V1.01": 1<<7,
                "V1.02": 1<<7,
                "V1.03": 1<<7,
            },
            'UPC6000': {
                "V1.02": 1<<1,
                "V1.03": 1<<1,
                "V1.02_FOR_CHUHAN": 1<<2,
                "V1.03_FOR_DIANKA": 1<<3,
            }
        }
        var pcba = info.SystemConnection.PCBA;
        var compatibleHW = compatibleHWList[pcba].reduce((sum, x) => sum | compatibleHwMap[pcba][x], 0x00);

        var buildTime = new Date();
        var buildTimeStr =
            buildTime.getFullYear().toString()
            + ("0" + (buildTime.getMonth() + 1).toString()).slice(-2)
            + ("0" + buildTime.getDate().toString()).slice(-2)
            + ("0" + buildTime.getHours().toString()).slice(-2)
            + ("0" + buildTime.getMinutes().toString()).slice(-2)
            + ("0" + buildTime.getSeconds().toString()).slice(-2);


        var releaseFileName = releaseName + "_" + buildTimeStr;
        releaseFileName = releaseFileName.slice(0, releaseFileName.length - 2)

        var mdata = {
            isTestVersion: cfg.releaseType == 'T' ? 1 : 0,
            fwAddrSpace: fwAddrSpace,
            buildTime: buildTime,
            buildTimeStr: buildTimeStr,
            compatibleHW: compatibleHW,
            releaseName: releaseName,
            srcCommitID: srcCommitID,
            releaseFileName: releaseFileName,
            appVersion: appVersion,
        }

        info.render("AppInfo.h", "AppInfo.h.tmpl", mdata);
        info.render("AppInfo.c", "AppInfo.c.tmpl", mdata);

        return {
            compatibleHW: compatibleHW,
            releaseName: releaseName,
            releaseFileName: releaseFileName,
        }
    }
}
