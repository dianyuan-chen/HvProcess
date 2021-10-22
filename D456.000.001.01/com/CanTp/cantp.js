/*
data format:
[
    {ch:0, rxid:0x7df, name:"UDS_FUNCTION"},
    {ch:0, rxid:0x740, txid:0x748, name:"UDS_PHYICAL"},
]
*/
module.exports = {
    process: function(cfgData, info) {

        //var datIf = {
        //    rxs: info.CanIf.rxs.filter(v=>v.upper.type=="CanTp").sort((a,b)=>a.upper.pduid-b.upper.pduid),
        //    txs: info.CanIf.txs.filter(v=>v.upper.type=="CanTp").sort((a,b)=>a.upper.pduid-b.upper.pduid),
        //};
        var cfg = JSON.parse(JSON.stringify(cfgData));
        var bmuch = cfg.reduce((a,x)=>(x.ch > a ? x.ch : a), 0) + 1;
        try {
            var i = info.SystemConnection.BcuType.startsWith("A6") ? 1 : 0;
            for (; i < info.SystemConnection.BmuNum; i++) {
                cfg.push({name:"BMU_"+i, hw: 0, dir:"rxtx", ch: bmuch+i%4, rx:0x780+i, tx:0x770+i});
            }
        } catch(e) {
        }

        var maxch = cfg.reduce((a,x)=>(x.ch > a ? x.ch : a), 0);
        var rxsdus = [];
        var txsdus = [];
        var rxnpdus = [];
        var txnpdus = [];
        var rxcfgs = cfg.filter(x=>x.hasOwnProperty("rx"));
        var txcfgs = cfg.filter(x=>x.hasOwnProperty("tx"));

        var rxsdus = rxcfgs.map(x=>{
            var name = x.name.toUpperCase();
            return {
                name: name,
                ch: x.ch,
                stmin: x.stmin ? x.stmin:2,
                bs: x.bs ? x.bs:0,
                wftmax: x.wftmax ? x.wftmax:10,
                rxnpdu: "CANIF_RX_CANTP_NPDU_"+name,
                txfcnpdu: x.hasOwnProperty("tx")?"CANIF_TX_CANTP_NPDU_"+name:"CANTP_UNUSED",
                tatype: x.hasOwnProperty("tx")?"CANTP_PHYSICAL":"CANTP_FUNCTIONAL",
            }
        });

        cfg.forEach(x=>{
            if(x.hasOwnProperty("rx")) {
                rxnpdus.push({
                    name: "CANIF_RX_CANTP_NPDU_"+x.name.toUpperCase(),
                    to: "CanTp",
                    hw: x.hw,
                    id: x.rx,
                    extended: false,
                    define: rxnpdus.length
                });
            }
            if(x.hasOwnProperty("tx")) {
                txnpdus.push({
                    name: "CANIF_TX_CANTP_NPDU_"+x.name.toUpperCase(),
                    from: "CanTp",
                    hw: x.hw,
                    id: x.tx,
                    extended: false
                });
            }

        });

        txsdus = txcfgs.map(x=>{
            var name = x.name.toUpperCase();
            return {
                name: name,
                ch: x.ch,
                txnpdu: "CANIF_TX_CANTP_NPDU_"+name,
                rxfcnpdu: x.hasOwnProperty("rx")?"CANIF_RX_CANTP_NPDU_"+name:"CANTP_UNUSED",
                tatype: x.hasOwnProperty("rx") ? "CANTP_PHYSICAL":"CANTP_FUNCTIONAL",
            }
        });

        var mdata = {
            channelnum: maxch + 1,
            rxsdus: rxsdus,
            txsdus: txsdus,
        }

        //console.log("=========== datIf ============")
        //console.log(datIf);
        //console.log("============ CanTp ============");
        //console.log(mdata);

        var path = require("path")

        info.render("CanTp_PBcfg.c", "CanTp_PBcfg.c.tmpl", mdata);

        return {
            canifrxnpdus: rxnpdus,
            caniftxnpdus: txnpdus,
            rxsduids: rxcfgs.map(x=>x.name),
            txsduids: txcfgs.map(x=>x.name),
        }
    }
}
