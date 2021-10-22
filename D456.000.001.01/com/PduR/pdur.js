/*
configdata format
[
        {dir:"<=>", upper:["Dcm", 0], middle:["CanTp", "UDS_FUNCTION"]},
        {dir:"<==", upper:["Dcm", 1], middle:["CanTp", "UDS_PHYICAL"]},
        {dir:"<=>", upper:["Dcm", 2], middle:["DtuTp", "UDS_PHYICAL"]},
]
*/

Array.prototype.pushToUndefined = function(index, e) {
    while (this.length < index) {
        this.push(undefined);
    }
    if (this[index] != undefined) return false;
    this[index] = e;
    return true;
};

Array.prototype.fillUndefinedWith = function(e) {
    for (var i = 0; i < this.length; i++) {
        if (this[i] == undefined) {
            this[i] = e;
        }
    }
}

Array.prototype.pushIfNotExist = function(e) {
    if (this.indexOf(e) >= 0) {
        return false;
    }
    this.push(e);
    return true;
}

module.exports = {
    process: function(cfgData, info) {
        //console.log("===========PDUR============")
        //console.log(JSON.stringify(info.InnerTp, null, "  "));
        //console.log(cfg);

        var cfg = JSON.parse(JSON.stringify(cfgData));

        var rxs = cfg.rx;
        var txs = cfg.tx;

        var mdata = {
            uppers:[],
            middles:[],
        };

        try {
            var i = 0;

            if (info.SystemConnection.BcuType.startsWith("A6")) {
                rxs.push({upper:["InternalComm", i], middle:["InnerTp", "BMU_" + i]});
                txs.push({upper:["InternalComm", i], middle:["InnerTp", "BMU_" + i]});
                i++;
            } else if (info.SystemConnection.M36Num > 0) {
                for (; i < info.SystemConnection.M36Num; i++) {
                    rxs.push({upper:["InternalComm", i], middle:["InnerTp", "BMU_" + i]});
                    txs.push({upper:["InternalComm", i], middle:["InnerTp", "BMU_" + i]});
                }
            }

            for (; i < info.SystemConnection.BmuNum; i++) {
                rxs.push({upper:["InternalComm", i], middle:["CanTp", "BMU_" + i]});
                txs.push({upper:["InternalComm", i], middle:["CanTp", "BMU_" + i]});
            }
        } catch(e) {
        }

        rxs.forEach(x=>x.middle[2] = info[x.middle[0]].rxsduids.indexOf(x.middle[1]));
        txs.forEach(x=>x.middle[2] = info[x.middle[0]].txsduids.indexOf(x.middle[1]));

        var addmodule = function(x) {
            if (mdata.uppers.pushIfNotExist(x.upper[0])){
                mdata[x.upper[0]] = {module: x.upper[0], txs:[], txmiddles:[]};
            }
            if (mdata.middles.pushIfNotExist(x.middle[0])) {
                mdata[x.middle[0]] = {module: x.middle[0], rxs:[], txs:[], rxuppers:[], txuppers:[],};
            }
        }

        rxs.forEach(x=>addmodule(x));
        txs.forEach(x=>addmodule(x));
        //if (mdata.middles.pushIfNotExist('InnerTp')) {
        //    mdata['InnerTp'] = {module: 'InnerTp', rxs:[], txs:[], rxuppers:[], txuppers:[]};
        //}

        for (var upper of mdata.uppers) {
            var defType = undefined;
            var i = 0;

            rxs.forEach(x=>{
                if (x.upper[0] != upper) return;
                if (defType == undefined) {
                    defType = typeof(x.upper[1]);
                } else if (defType != typeof(x.upper[1])) {
                    throw "Can not mix define" + defType + typeof(x.upper[1]);
                }
                if (defType == "string") {
                    x.upper[2] = x.upper[1]
                    x.upper[1] = i;
                } else {
                    x.upper[2] = x.upper[1].toString()
                }
                i++;
            });


            var defType = undefined;
            var i = 0;

            txs.forEach(x=>{
                if (x.upper[0] != upper) return;
                if (defType == undefined) {
                    defType = typeof(x.upper[1]);
                } else if (defType != typeof(x.upper[1])) {
                    throw "Can not mix define" + defType + typeof(x.upper[1]);
                }
                if (defType == "string") {
                    x.upper[2] = x.upper[1]
                    x.upper[1] = i;
                } else {
                    x.upper[2] = x.upper[1].toString()
                }
                i++;
            });

        }

        for (var upper of mdata.uppers) {
            var thistxs = txs.filter(x=>x.upper[0] == upper);
            thistxs.forEach(x=>mdata[upper].txs.pushToUndefined(x.upper[1], {name:x.middle[0], id:x.middle[2]}));
            thistxs.forEach(x=>mdata[upper].txmiddles.pushIfNotExist(x.middle[0]));
            mdata[upper].txs.fillUndefinedWith({name:"None", id: 0})
        }

        for (var middle of mdata.middles) {
            var thistxs = txs.filter(x=>x.middle[0] == middle);
            var thisrxs = rxs.filter(x=>x.middle[0] == middle);
            thistxs.forEach(x=>mdata[middle].txs.pushToUndefined(x.middle[2], {name:x.upper[0], id:x.upper[1]}));
            thistxs.forEach(x=>mdata[middle].txuppers.pushIfNotExist(x.upper[0]));
            thisrxs.forEach(x=>mdata[middle].rxs.pushToUndefined(x.middle[2], {name:x.upper[0], id:x.upper[1]}));
            thisrxs.forEach(x=>mdata[middle].rxuppers.pushIfNotExist(x.upper[0]));
            mdata[middle].rxs.fillUndefinedWith({name:"None", id: 0});
            mdata[middle].txs.fillUndefinedWith({name:"None", id: 0});
        }

        mdata['txs'] = txs;
        mdata['rxs'] = rxs;

        //console.log("===========PDUR============")
        //console.log(JSON.stringify(mdata, null, "  "));

        for (var v of mdata.uppers) {
            info.render("PduR_" + v + ".c", "PduR_Upper.c.tmpl", mdata[v]);
        }
        for (var v of mdata.middles) {
            info.render("PduR_" + v + ".c", "PduR_Middle.c.tmpl", mdata[v]);
        }

        info.render("PduR_Lcfg.h", "PduR_Lcfg.h.tmpl", {data:mdata});
        info.render("PduR_Lcfg.c", "PduR_Lcfg.c.tmpl", {data:mdata});
        info.render("PduR_Types.h", "PduR_Types.h.tmpl", {data:mdata});
    }
}
