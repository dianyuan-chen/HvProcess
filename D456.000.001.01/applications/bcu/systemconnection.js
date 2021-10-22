/*
configdata format:
{
    // 主机
    bcu:{
        //型号: 可选: "C600", "C601", "A600", "A601", "A602", "A603".
        type:"C601"
        // 电池连接, 只有型号为A60X的时候有效, 长度与型号相关.
        battconn:"111110011111_111111111111_111111111111",
        // 温感连接, 只有型号为A60X的时候有效, 长度与型号相关.
        tempconn:"1111_1111_0011_111111"
    },
    // 从机列表
    bmus:[{
        //主机: 可选: "M600", "M601", "M602", "M603".
        type:"M601",
        // 电池连接, 长度与型号相关.
        battconn:"111110011111_111111111111_111111111111",
        // 温感连接, 长度与型号相关.
        tempconn:"1111_1111_0011_111111"
    },{
        type:"M601",
        battconn:"111110011111_111111111111_111111111111",
        tempconn:"1111_1111_0011_111111"
    }]
},
*/

String.prototype.countOfChar = function(c){ return this.match(/./g).filter(v=>v==c).length;};

function checkBmuConnection(bmu) {
    const condition_bmu = {
        //一体机
        A600: [/^[10]{12}_[10]{12}$/, /^[CPH0]{4}_[CPH0]{4}$/],
        A601: [/^[10]{12}_[10]{12}$/, /^[CPH0]{4}_[CPH0]{4}$/],
        A650: [/^[10]{12}_[10]{12}$/, /^[CPH0]{4}_[CPH0]{4}$/],
        A651: [/^[10]{12}_[10]{12}$/, /^[CPH0]{4}_[CPH0]{4}$/],
        A655: [/^[10]{12}_[10]{12}$/, /^[CPH0]{4}_[CPH0]{4}$/],
        A602: [/^[10]{12}_[10]{12}_[10]{12}_[10]{12}$/, /^[CPH0]{4}_[CPH0]{4}_[CPH0]{4}_[CPH0]{4}$/],
        A603: [/^[10]{12}_[10]{12}_[10]{12}_[10]{12}$/, /^[CPH0]{4}_[CPH0]{4}_[CPH0]{4}_[CPH0]{4}$/],
        A652: [/^[10]{12}_[10]{12}_[10]{12}_[10]{12}$/, /^[CPH0]{4}_[CPH0]{4}_[CPH0]{4}_[CPH0]{4}$/],
        A653: [/^[10]{12}_[10]{12}_[10]{12}_[10]{12}$/, /^[CPH0]{4}_[CPH0]{4}_[CPH0]{4}_[CPH0]{4}$/],
        A657: [/^[10]{12}_[10]{12}_[10]{12}_[10]{12}$/, /^[CPH0]{4}_[CPH0]{4}_[CPH0]{4}_[CPH0]{4}$/],
        A660: [/^[10]{12}_[10]{12}_[10]{12}$/, /^[CPH0]{4}_[CPH0]{4}_[CPH0]{4}$/],
        A661: [/^[10]{12}_[10]{12}_[10]{12}$/, /^[CPH0]{4}_[CPH0]{4}_[CPH0]{4}$/],
        A665: [/^[10]{12}_[10]{12}_[10]{12}$/, /^[CPH0]{4}_[CPH0]{4}_[CPH0]{4}$/],
        // 从机
        M600: [/^[10]{12}_[10]{12}$/, /^[CPH0]{6}_[CPH0]{4}_[CPH0]{4}$/],
        M601: [/^[10]{12}_[10]{12}_[10]{12}$/, /^[CPH0]{6}_[CPH0]{4}_[CPH0]{4}_[CPH0]{4}$/],
        M602: [/^[10]{12}_[10]{12}_[10]{12}_[10]{12}$/, /^[CPH0]{6}_[CPH0]{4}_[CPH0]{4}_[CPH0]{4}_[CPH0]{4}$/],
        M603: [/^[10]{12}_[10]{12}_[10]{12}_[10]{12}_[10]{12}$/, /^[CPH0]{6}_[CPH0]{4}_[CPH0]{4}_[CPH0]{4}_[CPH0]{4}_[CPH0]{4}$/],
        M630: [/^[10]{12}$/, /[CPH0]{4}$/]
    }
    var cond = condition_bmu[bmu.type];
    if (cond == undefined) throw "Wrong BMU type " + bmu.type;
    if (!cond[0].test(bmu.battconn)) throw bmu.type + " has wrong BMU battconn " + bmu.battconn;
    if (!cond[1].test(bmu.tempconn)) throw bmu.type + " has wrong BMU tempconn " + bmu.tempconn;
}

function processConn(dat, conn, tstr) {
    var sum = dat.LogicIdMax.length == 0 ? 0: dat.LogicIdMax.slice(-1)[0];
    dat.LogicIdMax.push(conn.countOfChar(tstr) + sum);
    dat.BoardLogicIdMax = dat.BoardLogicIdMax.concat(conn.split('_').map(x=>x.countOfChar(tstr).toString() + 'U'));
    dat.LogicToPhyIdMap = dat.LogicToPhyIdMap.concat(conn.replace(/_/g, '').match(/./g).map((x, i)=> x==tstr ? ""+i+"U," : "/*"+i+"U,*/"));
}

function processBmuData(mdata, bmu) {
    mdata.Bmus.push(bmu.type);
    processConn(mdata.BmuBatt, bmu.battconn, '1');
    processConn(mdata.BmuCellTemp, bmu.tempconn, 'C');
    processConn(mdata.BmuHeatTemp, bmu.tempconn, 'H');
    processConn(mdata.BmuPoleTemp, bmu.tempconn, 'P');
}

module.exports = {
    process: function(cfgData, info) {
        var util = require("util");
        const bcus = {
            C600: {PCBA:'UPC6000', DtuSupport:0, AllInOne:0, MaxBmu:16, M630Support:0, NeedDaisyChainBatConnInfo:false},
            C601: {PCBA:'UPC6000', DtuSupport:1, AllInOne:0, MaxBmu:16, M630Support:0, NeedDaisyChainBatConnInfo:false},
            C602: {PCBA:'UPC6000', DtuSupport:0, AllInOne:0, MaxBmu:10, M630Support:1, NeedDaisyChainBatConnInfo:false},
            C603: {PCBA:'UPC6000', DtuSupport:1, AllInOne:0, MaxBmu:10, M630Support:1, NeedDaisyChainBatConnInfo:false},
            A600: {PCBA:'UPC6000', DtuSupport:0, AllInOne:1, MaxBmu:15, M630Support:0, NeedDaisyChainBatConnInfo:false},
            A601: {PCBA:'UPC6000', DtuSupport:1, AllInOne:1, MaxBmu:15, M630Support:0, NeedDaisyChainBatConnInfo:false},
            A602: {PCBA:'UPC6000', DtuSupport:0, AllInOne:1, MaxBmu:15, M630Support:0, NeedDaisyChainBatConnInfo:false},
            A603: {PCBA:'UPC6000', DtuSupport:1, AllInOne:1, MaxBmu:15, M630Support:0, NeedDaisyChainBatConnInfo:false},
            A650: {PCBA:'UPA650', DtuSupport:0, AllInOne:1, MaxBmu:0, M630Support:0, NeedDaisyChainBatConnInfo:true},
            A651: {PCBA:'UPA650', DtuSupport:1, AllInOne:1, MaxBmu:0, M630Support:0, NeedDaisyChainBatConnInfo:true},
            A655: {PCBA:'UPA650', DtuSupport:2, AllInOne:1, MaxBmu:0, M630Support:0, NeedDaisyChainBatConnInfo:true},
            A652: {PCBA:'UPA650', DtuSupport:0, AllInOne:1, MaxBmu:0, M630Support:0, NeedDaisyChainBatConnInfo:true},
            A653: {PCBA:'UPA650', DtuSupport:1, AllInOne:1, MaxBmu:0, M630Support:0, NeedDaisyChainBatConnInfo:true},
            A657: {PCBA:'UPA650', DtuSupport:2, AllInOne:1, MaxBmu:0, M630Support:0, NeedDaisyChainBatConnInfo:true},
            A660: {PCBA:'UPA650', DtuSupport:0, AllInOne:1, MaxBmu:0, M630Support:0, NeedDaisyChainBatConnInfo:true},
            A661: {PCBA:'UPA650', DtuSupport:1, AllInOne:1, MaxBmu:0, M630Support:0, NeedDaisyChainBatConnInfo:true},
            A665: {PCBA:'UPA650', DtuSupport:2, AllInOne:1, MaxBmu:0, M630Support:0, NeedDaisyChainBatConnInfo:true},
        };

        const typeToNumTable = {
            A600: {SlaveSampleBoardNum:2, SlaveCellNum:24, SlaveTempNum:8},
            A601: {SlaveSampleBoardNum:2, SlaveCellNum:24, SlaveTempNum:8},
            A602: {SlaveSampleBoardNum:4, SlaveCellNum:48, SlaveTempNum:16},
            A603: {SlaveSampleBoardNum:4, SlaveCellNum:48, SlaveTempNum:16},
            M600: {SlaveSampleBoardNum:2, SlaveCellNum:24, SlaveTempNum:14},
            M601: {SlaveSampleBoardNum:3, SlaveCellNum:36, SlaveTempNum:18},
            M602: {SlaveSampleBoardNum:4, SlaveCellNum:48, SlaveTempNum:22},
            M603: {SlaveSampleBoardNum:5, SlaveCellNum:60, SlaveTempNum:26},
            M630: {SlaveSampleBoardNum:1, SlaveCellNum:12, SlaveTempNum:8},
            A650: {SlaveSampleBoardNum:2, SlaveCellNum:24, SlaveTempNum:8},
            A651: {SlaveSampleBoardNum:2, SlaveCellNum:24, SlaveTempNum:8},
            A655: {SlaveSampleBoardNum:2, SlaveCellNum:24, SlaveTempNum:8},
            A652: {SlaveSampleBoardNum:4, SlaveCellNum:48, SlaveTempNum:16},
            A653: {SlaveSampleBoardNum:4, SlaveCellNum:48, SlaveTempNum:16},
            A657: {SlaveSampleBoardNum:4, SlaveCellNum:48, SlaveTempNum:16},
            A660: {SlaveSampleBoardNum:3, SlaveCellNum:36, SlaveTempNum:12},
            A661: {SlaveSampleBoardNum:3, SlaveCellNum:36, SlaveTempNum:12},
            A665: {SlaveSampleBoardNum:3, SlaveCellNum:36, SlaveTempNum:12},
        };

        if (!bcus.hasOwnProperty(cfgData.bcu.type)) {
            throw util.format("Wrong bcutype %s", cfgData.bcu.type);
        }
        if (cfgData.bmus.length > bcus[cfgData.bcu.type].MaxBmu) {
            throw util.format("BMU to many, %d > MaxBmu(%d)", cfgData.bmus.length, bcus[cfgData.bcu.type].MaxBmu)
        }

        var BcuSupportDtu = bcus[cfgData.bcu.type].DtuSupport;
        var BcuIsAllInOne = bcus[cfgData.bcu.type].AllInOne;
        var NeedDaisyChainBatConnInfo = bcus[cfgData.bcu.type].NeedDaisyChainBatConnInfo;
        var BcuAllInOneModuleNum = BcuIsAllInOne ? typeToNumTable[cfgData.bcu.type].SlaveSampleBoardNum : 0;

        var m630Num = cfgData.bmus.reduce((sum, val) => val.type == 'M630' ? sum + 1 : sum, 0);
        if (m630Num != 0 && m630Num != cfgData.bmus.length) {
            throw "mix M630 and other BMU not support."
        }

        if (m630Num != 0 && !bcus[cfgData.bcu.type].M630Support) {
            throw util.format("%s does not support M630", cfgData.bcu.type);
        }

        if (m630Num == 0 && bcus[cfgData.bcu.type].M630Support) {
            throw util.format("%s does not support M630", cfgData.bcu.type);
        }


        mdata = {
            Bcu: cfgData.bcu.type,
            BcuSupportDtu: BcuSupportDtu,
            BcuIsAllInOne: BcuIsAllInOne,
            M630Num: m630Num,
            SampleBoardNumOnDaisyChain: BcuIsAllInOne ? BcuAllInOneModuleNum : m630Num,
            NeedDaisyChainBatConnInfo: NeedDaisyChainBatConnInfo,
            Bmus: [],
            SlaveSampleBoardNum: [],
            SlaveCellNum: [],
            SlaveTempNum: [],
            BmuBatt: {
                LogicIdMax: [],
                BoardLogicIdMax: [],
                LogicToPhyIdMap: [],
            },
            BmuCellTemp: {
                LogicIdMax: [],
                BoardLogicIdMax: [],
                LogicToPhyIdMap: [],
            },
            BmuHeatTemp: {
                LogicIdMax: [],
                BoardLogicIdMax: [],
                LogicToPhyIdMap: [],
            },
            BmuPoleTemp: {
                LogicIdMax: [],
                BoardLogicIdMax: [],
                LogicToPhyIdMap: [],
            },
            CellsSetup: [],
            TempsSetup: []
        }

        if (BcuIsAllInOne) {
            checkBmuConnection(cfgData.bcu);
            processBmuData(mdata, cfgData.bcu);
            mdata.CellsSetup = cfgData.bcu.battconn.split('_').map(x=>x.split('').reverse().join(''))
            mdata.TempsSetup = cfgData.bcu.tempconn.replace(/[CHP]/g,'1').split('_').map(x=>x.split('').reverse().join(''))
            mdata.Bmus[0] = "UNKNOWN";
            mdata.SlaveSampleBoardNum.push(typeToNumTable[cfgData.bcu.type].SlaveSampleBoardNum + 'U');
            mdata.SlaveCellNum.push(typeToNumTable[cfgData.bcu.type].SlaveCellNum + 'U');
            mdata.SlaveTempNum.push(typeToNumTable[cfgData.bcu.type].SlaveTempNum + 'U');
        }

        for (var bmu of cfgData.bmus) {
            checkBmuConnection(bmu);
            if (bmu.type.startsWith("M60")) {
                var xx = bmu.tempconn.match(/([0CPH]{6})_([0CPH_]*)/);
                bmu.tempconn = xx[2] + "_" + xx[1];
            }
            processBmuData(mdata, bmu);
            mdata.SlaveSampleBoardNum.push(typeToNumTable[bmu.type].SlaveSampleBoardNum + 'U');
            mdata.SlaveCellNum.push(typeToNumTable[bmu.type].SlaveCellNum + 'U');
            mdata.SlaveTempNum.push(typeToNumTable[bmu.type].SlaveTempNum + 'U');
        }

        //console.log("=============== SystemConnection ============")
        //console.log(info)
        //console.log(JSON.stringify(mdata, null, "  "));


        if (mdata.BmuBatt.LogicIdMax.slice(-1)[0] != info.BatteryInfo.battnum) {
            throw util.format("Battery Cell number(%d) !=  BatteryInfo.battnum(%d)", mdata.BmuBatt.LogicIdMax.slice(-1)[0], info.BatteryInfo.battnum);
        }

        if (mdata.BmuCellTemp.LogicIdMax.slice(-1)[0] != info.BatteryInfo.celltempnum) {
            throw util.format("Cell temperature number(%d) !=  BatteryInfo.celltempnum(%d)", mdata.BmuCellTemp.LogicIdMax.slice(-1)[0], info.BatteryInfo.celltempnum);
        }

        if (mdata.BmuPoleTemp.LogicIdMax.slice(-1)[0] != info.BatteryInfo.poletempnum) {
            throw util.format("Pole temperature number(%d) !=  BatteryInfo.poletempnum(%d)", mdata.BmuPoleTemp.LogicIdMax.slice(-1)[0], info.BatteryInfo.poletempnum);
        }

        if (mdata.BmuHeatTemp.LogicIdMax.slice(-1)[0] != info.BatteryInfo.heattempnum) {
            throw util.format("Heat temperature number(%d) !=  BatteryInfo.heattempnum(%d)", mdata.BmuHeatTemp.LogicIdMax.slice(-1)[0], info.BatteryInfo.heattempnum);
        }

        info.render("SystemConnection_Lcfg.h", "SystemConnection_Lcfg.h.tmpl", mdata);
        info.render("SystemConnection_Lcfg.c", "SystemConnection_Lcfg.c.tmpl", mdata);
        return {
            BcuType: cfgData.bcu.type,
            BcuIsAllInOne: BcuIsAllInOne,
            M36Num: m630Num,
            BcuAllInOneModuleNum : BcuIsAllInOne ? BcuAllInOneModuleNum : m630Num,
            BmuNum: mdata.Bmus.length,
            PCBA: bcus[cfgData.bcu.type].PCBA,
        };
    }
}
