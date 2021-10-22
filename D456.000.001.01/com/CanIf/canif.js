module.exports = {
    process: function(cfgData, info) {

        var cfg = JSON.parse(JSON.stringify(cfgData));

        var rxsduids = cfg.rxsduids;
        var txsduids = cfg.txsduids;
        var canhohs = [];

        for (var x in info) {
            if (!info[x]) continue;
            if (info[x].hasOwnProperty("canifrxnpdus")) rxsduids = rxsduids.concat(info[x].canifrxnpdus);
            if (info[x].hasOwnProperty("caniftxnpdus")) txsduids = txsduids.concat(info[x].caniftxnpdus);
        }


        rxsduids.forEach(x=>{
            if (canhohs.findIndex(hoh=>hoh.hw==x.hw && hoh.dir=="rx") < 0) {
                canhohs.push({hw: x.hw, dir: "rx", ids:[]})
            }
        });

        txsduids.forEach(x=>{
            if (canhohs.findIndex(hoh=>hoh.hw==x.hw && hoh.dir=="tx") < 0) {
                canhohs.push({hw: x.hw, dir: "tx"})
            }
        });

        canhohs.sort((a, b)=>{
            if (a.hw == b.hw) {
                if (a.dir == "tx") {
                    return -1;
                } else {
                    return 1;
                }
            }

            return a.hw - b.hw;
        });

        rxsduids.forEach(x=>{
            x.hoh = canhohs.findIndex(hoh=>hoh.hw==x.hw && hoh.dir=="rx");
            if (x.hoh < 0) throw x.name + " No HRH";
            x.extended = ((x.id & 0x80000000) != 0);
            canhohs[x.hoh].ids.push(x.id);
        })

        txsduids.forEach(x=>{
            x.hoh = canhohs.findIndex(hoh=>hoh.hw==x.hw && hoh.dir=="tx");
            if (x.hoh < 0) throw x.name + " No HTH"
            x.extended = ((x.id & 0x80000000) != 0);
            //x.id = x.id & 0x7fffffff;
        })

        rxsduids.sort((a, b) => a.hoh - b.hoh);
        txsduids.sort((a, b) => a.hoh - b.hoh);

        //txsduids = txsduids.map((v, i)=> {v.npdu = i; return v});
        rxsduids = rxsduids.map((v, i, xx)=>{
            if (i == xx.length - 1) {
                v.next = "CANIF_LAST_HRH_RXPDUID";
            } else {
                v.next = (xx[i+1].hoh == v.hoh ? i + 1 : "CANIF_LAST_HRH_RXPDUID");
            }
            return v;
        });

        var hrhFirstRxPduID = [];
        for (var i = 0; i < canhohs.length; i++) {
            if (canhohs[i].dir != "rx") {
                hrhFirstRxPduID[i] = "CANIF_LAST_HRH_RXPDUID";
            } else {
                hrhFirstRxPduID[i] = rxsduids.findIndex(v=>v.hoh==i)+"U";
            }
        }

        var mdat = {
            rxsduids: rxsduids,
            txsduids: txsduids,
            hrhNum: canhohs.length,
            hrhFirstRxPduID: hrhFirstRxPduID,
        };

        //console.log("============= cfg =============")
        //console.log(mdat);
        //console.log(hrhFirstRxPduID);
        // console.log(txCanIds);

        info.render("CanIf_Lcfg.h", "CanIf_Lcfg.h.tmpl", mdat);
        info.render("CanIf_Lcfg.c", "CanIf_Lcfg.c.tmpl", mdat);

        return {
            rxsduids: rxsduids,
            txsduids: txsduids,
            canhohs: canhohs,
        };
    }
}
