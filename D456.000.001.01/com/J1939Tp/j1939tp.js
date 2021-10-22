module.exports = {
    process: function(cfgData, info) {

        var cfg = JSON.parse(JSON.stringify(cfgData));

        var rxsduids = [];
        var txsduids = [];

        var canifrxnpdus = [];
        var caniftxnpdus = [];

        var channels = [];
        var pgs = [];
        var rxpdus = [];
        var rxpduRelations = [];

        // 生成所有的可以传给上层的SDUID
        cfg.forEach(v=>{
            v.pgs.forEach(pg=>{
                if (pg.type == "tx") {
                    var pgname;
                    if (pg.pgn > 0xFFFF) {
                        pgname = ("000000" + pg.pgn.toString(16)).slice(-6).toUpperCase();
                    } else {
                        pgname = ("0000" + pg.pgn.toString(16)).slice(-4).toUpperCase();
                    }
                    txsduids.push(v.name+"_PG_" + pgname);
                    rxsduids.push("None");
                }

                if (pg.type == "bam_tx") {
                    var pgname;
                    if (pg.pgn > 0xFFFF) {
                        pgname = ("000000" + pg.pgn.toString(16)).slice(-6).toUpperCase();
                    } else {
                        pgname = ("0000" + pg.pgn.toString(16)).slice(-4).toUpperCase();
                    }
                    txsduids.push(v.name+"_PG_BAM_" + pgname);
                    rxsduids.push("None");
                }

                if (pg.type == "rx") {
                    var pgname;
                    if (pg.pgn > 0xFFFF) {
                        pgname = ("000000" + pg.pgn.toString(16)).slice(-6).toUpperCase();
                    } else {
                        pgname = ("0000" + pg.pgn.toString(16)).slice(-4).toUpperCase();
                    }
                    rxsduids.push(v.name+"_PG_" + pgname);
                    txsduids.push("None");
                }

                if (pg.type == "bam_rx") {
                    var pgname;
                    if (pg.pgn > 0xFFFF) {
                        pgname = ("000000" + pg.pgn.toString(16)).slice(-6).toUpperCase();
                    } else {
                        ("0000" + pg.pgn.toString(16)).slice(-4).toUpperCase();
                    }
                    rxsduids.push(v.name+"_PG_BAM_" + pgname);
                    txsduids.push("None");
                }


                if (pg.type == "stx") {
                    var idname = ("00000000" + pg.id.toString(16)).slice(-8).toUpperCase();
                    txsduids.push(v.name+"_ID_" + idname);
                    rxsduids.push("None");
                }

                if (pg.type == "srx") {
                    var idname = ("00000000" + pg.id.toString(16)).slice(-8).toUpperCase();
                    rxsduids.push(v.name+"_ID_" + idname);
                    txsduids.push("None");
                }
            });
        });

        for (var v of cfg) {
            var hascm = false;

            var thispgs = v.pgs.map(x=>({name:v.name, pgn:x.hasOwnProperty("pgn")? x.pgn : x.id, type:x.type, id: x.id}));
            var rxpgs = thispgs.filter(x=>x.type=="rx");
            var txpgs = thispgs.filter(x=>x.type=="tx");
            var bamtxpgs = thispgs.filter(x=>(x.type=="bam_tx"));
            var bamrxpgs = thispgs.filter(x=>(x.type=="bam_rx"));
            var srxpgs = thispgs.filter(x=>x.type=="srx");
            var stxpgs = thispgs.filter(x=>x.type=="stx");
            var rxpgsindex = thispgs.reduce((a, x, index)=>{if (x.type == "rx") a.push(index + pgs.length); return a}, []);
            var txpgsindex = thispgs.reduce((a, x, index)=>{if (x.type == "tx") a.push(index + pgs.length); return a}, []);
            var bamtxpgsindex = thispgs.reduce((a, x, index)=>{if (x.type == "bam_tx") a.push(index + pgs.length); return a}, []);
            var bamrxpgsindex = thispgs.reduce((a, x, index)=>{if (x.type == "bam_rx") a.push(index + pgs.length); return a}, []);

            var rxchannel = channels.length;
            if (rxpgs.length > 0) {
                rxpdus.push({name:v.name, type:"CM", channel:channels.length})
                rxpdus.push({name:v.name, type:"DT", channel:channels.length})
                rxpdus.push({name:v.name, type:"REVERSE_CM", channel:channels.length})
                rxpgs.forEach(x=>x.channel=rxchannel);
                channels.push({name:v.name, dir: "rx", pgs:rxpgsindex, protocol:"CMDT"});
            }
            srxpgs.forEach(x=>x.channel=rxchannel);

            if (bamrxpgs.length > 0) {
                rxpdus.push({name:v.name, type:"CM_BAM", channel:channels.length})
                rxpdus.push({name:v.name, type:"DT_BAM", channel:channels.length})
                bamrxpgs.forEach(x=>x.channel=channels.length);
                channels.push({name:v.name, dir: "bam_rx", pgs:bamrxpgsindex, protocol:"BAM"});
            }

            var txchannel = channels.length;
            if (txpgs.length > 0) {
                rxpdus.push({name:v.name, type:"CM", channel:channels.length});
                rxpdus.push({name:v.name, type:"DT", channel:channels.length})
                rxpdus.push({name:v.name, type:"REVERSE_CM", channel:channels.length});
                txpgs.forEach(x=>x.channel=txchannel);
                channels.push({name:v.name, dir: "tx", pgs:txpgsindex, protocol:"CMDT"})
            }
            stxpgs.forEach(x=>x.channel=txchannel);

            if (bamtxpgs.length > 0) {
                rxpdus.push({name:v.name, type:"CM_BAM", channel:channels.length});
                rxpdus.push({name:v.name, type:"DT_BAM", channel:channels.length});
                bamtxpgs.forEach(x=>x.channel=channels.length);
                channels.push({name:v.name, dir: "bam_tx", pgs:bamtxpgsindex, protocol:"BAM"})
            }


            var rxpducm = rxpdus.reduce((a,x,index)=>{if (x.name == v.name && (x.type=="CM" || x.type=="REVERSE_CM")) a.push(index); return a}, []);
            var rxpdudt = rxpdus.reduce((a,x,index)=>{if (x.name == v.name && x.type=="DT") a.push(index); return a}, []);
            var rxpducmbam = rxpdus.reduce((a,x,index)=>{if (x.name == v.name && x.type=="CM_BAM")  a.push(index); return a}, []);
            var rxpdudtbam = rxpdus.reduce((a,x,index)=>{if (x.name == v.name && x.type=="DT_BAM") a.push(index); return a}, []);

            var upper = rxpduRelations.length;

            canifrxnpdus.push({
                name: "CANIF_RX_J1939TP_NPDU_"+v.name.toUpperCase()+"_CM",
                hw:v.hw,
                id:0x9CEC0000 + v.self*256 + v.remote,
                define: rxpduRelations.length,
            });

            caniftxnpdus.push({
                name: "CANIF_TX_J1939TP_NPDU_"+v.name.toUpperCase()+"_CM",
                hw:v.hw,
                id:0x9CEC0000 + v.self + v.remote*256,
                define: rxpduRelations.length,
            });
            rxpduRelations.push({name: v.name, type:"CM", rxpdus:rxpducm});


            canifrxnpdus.push({
                name: "CANIF_RX_J1939TP_NPDU_"+v.name.toUpperCase()+"_DT",
                hw:v.hw,
                id:0x9CEB0000 + v.self*256 + v.remote,
                define: rxpduRelations.length
            });

            caniftxnpdus.push({
                name: "CANIF_TX_J1939TP_NPDU_"+v.name.toUpperCase()+"_DT",
                hw:v.hw,
                id:0x9CEB0000 + v.self + v.remote*256,
                define: rxpduRelations.length
            });
            rxpduRelations.push({name: v.name, type:"DT", rxpdus:rxpdudt});

            if (bamtxpgs.length > 0) {
                caniftxnpdus.push({
                    name: "CANIF_TX_J1939TP_NPDU_"+v.name.toUpperCase()+"_CM_BAM",
                    hw:v.hw,
                    id:0x9CECFF00 + v.self,
                    define: rxpduRelations.length
                });
            }
            if (bamrxpgs.length > 0) {
                canifrxnpdus.push({
                    name: "CANIF_RX_J1939TP_NPDU_"+v.name.toUpperCase()+"_CM_BAM",
                    hw:v.hw,
                    id:0x9CECFF00 + v.remote,
                    define: rxpduRelations.length
                });
            }
            if (bamtxpgs.length > 0 || bamrxpgs.length > 0) {
                rxpduRelations.push({name: v.name, type:"CM_BAM", rxpdus:rxpducmbam});
            }

            if (bamtxpgs.length > 0) {
                caniftxnpdus.push({
                    name: "CANIF_TX_J1939TP_NPDU_"+v.name.toUpperCase()+"_DT_BAM",
                    hw:v.hw,
                    id:0x9CEBFF00 + v.self,
                    define: rxpduRelations.length
                });
            }
            if (bamrxpgs.length > 0) {
                canifrxnpdus.push({
                    name: "CANIF_RX_J1939TP_NPDU_"+v.name.toUpperCase()+"_DT_BAM",
                    hw:v.hw,
                    id:0x9CEBFF00 + v.remote,
                    define: rxpduRelations.length
                });
            }
            if (bamtxpgs.length > 0 || bamrxpgs.length > 0) {
                rxpduRelations.push({name: v.name, type:"DT_BAM", rxpdus:rxpdudtbam});
            }

            v.pgs.forEach(function(pg, index){
                if (pg.type == "rx") {
                    let id;
                    var pgname;
                    if (pg.pgn > 0xFFFF) {
                        pgname = ("000000" + pg.pgn.toString(16)).slice(-6).toUpperCase();
                    } else {
                        pgname = ("0000" + pg.pgn.toString(16)).slice(-4).toUpperCase();
                    }
                    if (((pg.pgn >> 8) & 0xFF) < 240) {
                        id = 0x80000000 + (pg.pri << 26) + ((pg.pgn & 0xFF00) << 8) + (v.self << 8) + v.remote
                    } else {
                        id = 0x80000000 + (pg.pri << 26) + ((pg.pgn & 0xFFFF) << 8) + v.remote
                    }
                    canifrxnpdus.push({
                        name: "CANIF_RX_J1939TP_NPDU_" + v.name.toUpperCase() +"_PG_" + pgname,
                        hw:v.hw,
                        id: id,
                        define: rxpduRelations.length,
                    });
                    rxpduRelations.push({name: v.name, type:"DIRECT_RX_" + pgname, rxpdus:[rxpdus.length]});
                    rxpdus.push({name:v.name, type:"DIRECT", channel:rxchannel, pg:pgs.length+index});
                }

                if (pg.type == "bam_rx") {
                    let id;
                    var pgname;
                    if (pg.pgn > 0xFFFF) {
                        pgname = ("000000" + pg.pgn.toString(16)).slice(-6).toUpperCase();
                    } else {
                        pgname = ("0000" + pg.pgn.toString(16)).slice(-4).toUpperCase();
                    }
                    if (((pg.pgn >> 8) & 0xFF) < 240) {
                        id = 0x80000000 + (pg.pri << 26) + ((pg.pgn & 0xFF00) << 8) + (0xFF << 8) + v.remote
                    } else {
                        id = 0x80000000 + (pg.pri << 26) + ((pg.pgn & 0xFFFF) << 8) + v.remote
                    }
                    canifrxnpdus.push({
                        name: "CANIF_RX_J1939TP_NPDU_" + v.name.toUpperCase() +"_PG_BAM_" + pgname,
                        hw:v.hw,
                        id: id,
                        define: rxpduRelations.length,
                    });
                    rxpduRelations.push({name: v.name, type:"DIRECT_RX_" + pgname, rxpdus:[rxpdus.length]});
                    rxpdus.push({name:v.name, type:"DIRECT", channel:rxchannel, pg:pgs.length+index});
                }

                if (pg.type == "srx") {
                    var idname = ("00000000" + pg.id.toString(16)).slice(-8).toUpperCase();
                    canifrxnpdus.push({
                        name: "CANIF_RX_J1939TP_NPDU_" + v.name.toUpperCase() +"_ID_" + idname,
                        hw:v.hw,
                        id: pg.id,
                        define: rxpduRelations.length,
                    });
                    rxpduRelations.push({name: v.name, type:"DIRECT_RX_" + idname, rxpdus:[rxpdus.length]});
                    rxpdus.push({name:v.name, type:"DIRECT", channel:txchannel, pg:pgs.length+index});
                }
            });

            v.pgs.forEach((pg, index) => {
                if (pg.type == "tx") {
                    let id;
                    var pgname;
                    if (pg.pgn > 0xFFFF) {
                        pgname = ("000000" + pg.pgn.toString(16)).slice(-6).toUpperCase();
                    } else {
                        pgname = ("0000" + pg.pgn.toString(16)).slice(-4).toUpperCase();
                    }
                    if (((pg.pgn >> 8) & 0xFF) < 240) {
                        id = 0x80000000 + (pg.pri << 26) + ((pg.pgn & 0xFF00) << 8) + (v.remote << 8) + v.self
                    } else {
                        id = 0x80000000 + (pg.pri << 26) + ((pg.pgn & 0xFFFF) << 8) + v.self
                    }
                    caniftxnpdus.push({
                        name: "CANIF_TX_J1939TP_NPDU_" + v.name.toUpperCase() +"_PG_" + pgname,
                        hw:v.hw,
                        id: id,
                        define: rxpduRelations.length,
                    });
                    rxpduRelations.push({name: v.name, type:"DIRECT_TX_" + pgname, rxpdus:[rxpdus.length]});
                    rxpdus.push({name:v.name, type:"DIRECT", channel:txchannel, pg:pgs.length+index});
                }

                if (pg.type == "bam_tx") {
                    let id;
                    var pgname;
                    if (pg.pgn > 0xFFFF) {
                        pgname = ("000000" + pg.pgn.toString(16)).slice(-6).toUpperCase();
                    } else {
                        pgname = ("0000" + pg.pgn.toString(16)).slice(-4).toUpperCase();
                    }
                    if (((pg.pgn >> 8) & 0xFF) < 240) {
                        id = 0x80000000 + (pg.pri << 26) + ((pg.pgn & 0xFF00) << 8) + (0xFF << 8) + v.self
                    } else {
                        id = 0x80000000 + (pg.pri << 26) + ((pg.pgn & 0xFFFF) << 8) + v.self
                    }
                    caniftxnpdus.push({
                        name: "CANIF_TX_J1939TP_NPDU_" + v.name.toUpperCase() +"_PG_BAM_" + pgname,
                        hw:v.hw,
                        id: id,
                        define: rxpduRelations.length,
                    });
                    rxpduRelations.push({name: v.name, type:"DIRECT_TX_" + pgname, rxpdus:[rxpdus.length]});
                    rxpdus.push({name:v.name, type:"DIRECT", channel:txchannel, pg:pgs.length+index});
                }

                if (pg.type == "stx") {
                    var idname = ("00000000" + pg.id.toString(16)).slice(-8).toUpperCase();
                    caniftxnpdus.push({
                        name: "CANIF_TX_J1939TP_NPDU_" + v.name.toUpperCase() +"_ID_" + idname,
                        hw:v.hw,
                        id: pg.id,
                        define: rxpduRelations.length,
                    });
                    rxpduRelations.push({name: v.name, type:"DIRECT_TX_" + idname, rxpdus:[rxpdus.length]});
                    rxpdus.push({name:v.name, type:"DIRECT", channel:txchannel, pg:pgs.length+index});
                }
            });

            thispgs.forEach((pg, index) => {
                if (pg.type == "tx" || pg.type == "rx") {
                    var pgname;
                    if (pg.pgn > 0xFFFF) {
                        pgname = ("000000" + pg.pgn.toString(16)).slice(-6).toUpperCase();
                    } else {
                        pgname = ("0000" + pg.pgn.toString(16)).slice(-4).toUpperCase();
                    }
                    pg.nsdu = "J1939TP_NSDU_" + pg.type.toUpperCase() + "_" + pg.name.toUpperCase() + "_PG_" + pgname;
                } else if (pg.type == "stx" || pg.type == "srx") {
                    var idname = ("00000000" + pg.id.toString(16)).slice(-8).toUpperCase();
                    pg.nsdu = ("J1939TP_NSDU_" + pg.type.slice(-2) + "_" + pg.name + "_ID_" + idname).toUpperCase();
                } else if  (pg.type == "bam_tx" || pg.type == "bam_rx") {
                    var pgname;
                    if (pg.pgn > 0xFFFF) {
                        pgname = ("000000" + pg.pgn.toString(16)).slice(-6).toUpperCase();
                    } else {
                        pgname = ("0000" + pg.pgn.toString(16)).slice(-4).toUpperCase();
                    }
                    pg.nsdu = "J1939TP_NSDU_" + pg.type.slice(-2).toUpperCase() + "_" + pg.name.toUpperCase() + "_PG_BAM_" + pgname;
                }
            });

            pgs = pgs.concat(thispgs);
        }

        pgs.forEach(pg=>{
            var x;

            if (pg.type == "tx" || pg.type == "rx") {
                if (pg.pgn > 0xFFFF) {
                    x="CANIF_" + pg.type + "_J1939TP_NPDU_"+ pg.name +"_PG_" + ("000000" + pg.pgn.toString(16)).slice(-6);
                } else {
                    x="CANIF_" + pg.type + "_J1939TP_NPDU_"+ pg.name +"_PG_" + ("0000" + pg.pgn.toString(16)).slice(-4);
                }
            } else if (pg.type == "stx" || pg.type == "srx") {
                x="CANIF_" + pg.type.slice(-2) + "_J1939TP_NPDU_"+ pg.name +"_ID_" + ("00000000" + pg.id.toString(16)).slice(-8);
            } else if  (pg.type == "bam_tx" || pg.type == "bam_rx") {
                if (pg.pgn > 0xFFFF) {
                    x= "CANIF_" + pg.type.slice(-2) + "_J1939TP_NPDU_" + pg.name.toUpperCase() +"_PG_BAM_" + ("000000" + pg.pgn.toString(16)).slice(-6).toUpperCase();
                } else {
                    x= "CANIF_" + pg.type.slice(-2) + "_J1939TP_NPDU_" + pg.name.toUpperCase() +"_PG_BAM_" + ("0000" + pg.pgn.toString(16)).slice(-4).toUpperCase();
                }
            }
            pg.npdu = x.toUpperCase();
        });

        channels.forEach(ch=>{
            if (ch.dir == "bam_tx") {
                ch.dtnpdu = ("CANIF_TX_J1939TP_NPDU_" + ch.name + "_DT_BAM").toUpperCase();
                ch.cmnpdu = ("CANIF_TX_J1939TP_NPDU_" + ch.name + "_CM_BAM").toUpperCase();
                 ch.fcnpdu = "0U";
                ch.direction = "J1939TP_TX";
            } else if (ch.dir ==  "tx") {
                ch.dtnpdu = ("CANIF_TX_J1939TP_NPDU_" + ch.name + "_DT").toUpperCase();
                ch.cmnpdu = ("CANIF_TX_J1939TP_NPDU_" + ch.name + "_CM").toUpperCase();
                ch.fcnpdu = ("CANIF_RX_J1939TP_NPDU_" + ch.name + "_CM").toUpperCase();
                ch.direction = "J1939TP_TX";
            } else if (ch.dir == "rx"){
                ch.dtnpdu = ("CANIF_RX_J1939TP_NPDU_" + ch.name + "_DT").toUpperCase();
                ch.cmnpdu = ("CANIF_RX_J1939TP_NPDU_" + ch.name + "_CM").toUpperCase();
                ch.fcnpdu = ("CANIF_TX_J1939TP_NPDU_" + ch.name + "_CM").toUpperCase();
                ch.direction = "J1939TP_RX";
            } else if (ch.dir == "bam_rx") {
                ch.dtnpdu = ("CANIF_RX_J1939TP_NPDU_" + ch.name + "_DT_BAM").toUpperCase();
                ch.cmnpdu = ("CANIF_RX_J1939TP_NPDU_" + ch.name + "_CM_BAM").toUpperCase();
                ch.fcnpdu = "0U"
                ch.direction = "J1939TP_RX";

            }
        });

        canifrxnpdus.forEach(x=>{x.extended = true; x.to = "J1939Tp";}),
        caniftxnpdus.forEach(x=>{x.extended = true; x.from = "J1939Tp";})

        var mdata = {
            channels:channels,
            rxsduids: rxsduids,
            txsduids: txsduids,
            pgs: pgs,
            rxpdus: rxpdus,
            rxpduRelations: rxpduRelations,
        };

        //console.log("=========== J1939Tp ============")
        //console.log(JSON.stringify(mdata, null, "  "));
        info.render("J1939Tp_Lcfg.h", "J1939Tp_Lcfg.h.tmpl", mdata);
        info.render("J1939Tp_Lcfg.c", "J1939Tp_Lcfg.c.tmpl", mdata);

        return {
            rxsduids: rxsduids,
            txsduids: txsduids,
            canifrxnpdus: canifrxnpdus,
            caniftxnpdus: caniftxnpdus,
        }
    }
}
