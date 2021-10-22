module.exports = {
    process: function (cfgData, info) {
        var XLSX = require('xlsx')
        var path = require("path");
        var workbook = XLSX.readFile(path.join(process.env.TOPDIR, 'applications/bcu/ModelConfigure.xlsx'));
        var sheet_name_list = workbook.SheetNames;
        var worksheet = workbook.Sheets[sheet_name_list[0]];
        var range = XLSX.utils.decode_range(worksheet['!ref']);

        var enableModelSOXCell;
        var enableCycleSOHCell;
        var enableSOCJumpShortTimeOCVCell;
        var enableOCVAtDischargeEndCell;
        var enableOCVCell
        var realSOCUpperLimitCell;
        var realSOCLowerLimitCell;
        var ocvTableSOCIndexStartCell;
        var ocvTableTIndexStartCell;
        var cycleToSOHTableCycleStartCell;
        var cycleToSOHTableSOHStartCell;
        var tToCAPTableTStartCell;
        var tToCAPTableCapStartCell;
        var CulumCapPerCycleCell;
        var ocvTempHighLimit;
        var ocvTempLowLimit;
        var dSOCJumpMaxCell;
        var sohCalcShortTimeCell;
        var sohCalcShortTempCell;
        var ocvMinDiffVoltCell;

        var enableModelSOX;
        var enableCycleSOH;
        var enableSOCJumpShortTimeOCV;
        var enableOCVAtDischargeEnd;
        var enableOCV;
        var realSOCUpperLimit;
        var realSOCLowerLimit;
        var CulumCapPerCycle;
        var dSOCJumpMax;
        var sohCalcShortTime;
        var sohCalcShortTemp;
        var ocvMinDiffVolt;
        var cycleToSOHTableCycleList = [];
        var cycleToSOHTableSOHList = [];
        var tToCAPTableTList = [];
        var tToCAPTableCapList = [];
        var ocvTableSOCIndexList = [];
        var ocvTableTIndexList = [];
        var ocvTableList = [];

        function debugout(msg) {
             // console.log(msg); 
        }


        for (var R = range.s.r; R <= range.e.r; ++R) {
            for (var C = range.s.c; C <= range.e.c; ++C) {
                var cell_address = { c: C, r: R };
                /* if an A1-style address is needed, encode the address */
                var cell_ref = XLSX.utils.encode_cell(cell_address);
                var cell = worksheet[cell_ref];
                if (!cell) {
                    continue;
                }
                var cellv = cell['v'];
                if (!cellv) {
                    continue
                }

                //debugout(cell_ref + ':' + JSON.stringify(cell));

                if (cellv == 'EnableModelSOX') {
                    enableModelSOXCell = { c: C + 1, r: R }
                } else if (cellv == 'EnableCycleSOH') {
                    enableCycleSOHCell = { c: C + 1, r: R }
                } else if (cellv == 'CulumCapPerCycle'){
                    CulumCapPerCycleCell = { c: C + 1, r: R }
                }else if (cellv == 'EnableSOCJumpShortTimeOCV') {
                    enableSOCJumpShortTimeOCVCell = { c: C + 1, r: R }
                } else if (cellv == 'EnableOCVAtDischargeEnd') {
                    enableOCVAtDischargeEndCell = { c: C + 1, r: R }
                } else if (cellv == 'RealSOCUpperLimit') {
                    realSOCUpperLimitCell = { c: C + 1, r: R }
                } else if (cellv == 'RealSOCLowerLimit') {
                    realSOCLowerLimitCell = { c: C + 1, r: R }
                } else if (cellv == 'T-SOC-OCV') {
                    ocvTableSOCIndexStartCell = { c: C + 1, r: R + 1 };
                    ocvTableTIndexStartCell = { c: C, r: R + 2 };
                } else if (cellv == 'CYCLE-SOH') {
                    cycleToSOHTableCycleStartCell = { c: C + 1, r: R + 1 };
                    cycleToSOHTableSOHStartCell = { c: C + 1, r: R + 2 };
                } else if (cellv == 'T-CAP') {
                    tToCAPTableTStartCell = { c: C + 1, r: R + 1 };
                    tToCAPTableCapStartCell = { c: C + 1, r: R + 2 };
                } else if (cellv == 'DSOCJump'){
                    dSOCJumpMaxCell = { c: C + 1, r: R }
                } else if (cellv == 'SOHCalcShortTimeDiffLimit'){
                    sohCalcShortTimeCell = { c: C + 1, r: R }
                } else if (cellv == 'SOHCalcShortTempLimit'){
                    sohCalcShortTempCell = { c: C + 1, r: R }
                } else if (cellv == 'EnableSOCOCV'){
                    enableOCVCell = { c: C + 1, r: R }
                } else if (cellv == 'OcvDiffVoltMin'){
                    ocvMinDiffVoltCell = { c: C + 1, r: R }
                }
            }
        }



        if (!enableModelSOXCell) {
            throw "Can not find EnableCycleSOH definition";
        } else {
            enableModelSOX = (worksheet[XLSX.utils.encode_cell(enableModelSOXCell)]['v'] != '0');
            debugout("enableModelSOXCell = " + enableModelSOXCell);
        }

        if (!enableCycleSOHCell) {
            throw "Can not find EnableCycleSOH definition";
        } else {
            enableCycleSOH = (worksheet[XLSX.utils.encode_cell(enableCycleSOHCell)]['v'] != '0');
            debugout("enableCycleSOH = " + enableCycleSOH);
        }

        if (!CulumCapPerCycleCell) {
            throw "Can not find EnableCycleSOH definition";
        } else {
            CulumCapPerCycle = (worksheet[XLSX.utils.encode_cell(CulumCapPerCycleCell)]['v']);
            debugout("enableCycleSOH = " + enableCycleSOH);
        }
        if (CulumCapPerCycle < 50){
            throw "CulumCapPerCycleCell is less than 50";
        }

        if (!enableSOCJumpShortTimeOCVCell) {
            throw "Can not find EnableSOCJumpShortTimeOCV definition";
        } else {
            enableSOCJumpShortTimeOCV = (worksheet[XLSX.utils.encode_cell(enableSOCJumpShortTimeOCVCell)]['v'] != '0');
            debugout("enableSOCJumpShortTimeOCV = " + enableSOCJumpShortTimeOCV);
        }


        if (!enableOCVAtDischargeEndCell) {
            throw "Can not find EnableOCVAtDischargeEnd definition";
        } else {
            enableOCVAtDischargeEnd = (worksheet[XLSX.utils.encode_cell(enableOCVAtDischargeEndCell)]['v'] != '0');
            debugout("enableOCVAtDischargeEnd = " + enableOCVAtDischargeEnd);
        }


        if (!realSOCUpperLimitCell) {
            throw "Can not find RealSOCUpperLimit definition";
        } else {
            realSOCUpperLimit = parseInt(worksheet[XLSX.utils.encode_cell(realSOCUpperLimitCell)]['v']);
            debugout("enableOCVAtDischargeEnd = " + realSOCUpperLimit);
        }


        if (!realSOCLowerLimitCell) {
            throw "Can not find RealSOCLowerLimit definition";
        } else {
            realSOCLowerLimit = parseInt(worksheet[XLSX.utils.encode_cell(realSOCLowerLimitCell)]['v']);
            debugout("enableOCVAtDischargeEnd = " + realSOCLowerLimit);
        }

        if (!dSOCJumpMaxCell) {
            throw "Can not find dSOCJumpMax definition";
        } else {
            dSOCJumpMax = (worksheet[XLSX.utils.encode_cell(dSOCJumpMaxCell)]['v']);
            debugout("enableCycleSOH = " + dSOCJumpMax);
        }

        if (!enableOCVCell) {
            throw "Can not find EnableOCV definition";
        } else {
            enableOCV = parseInt(worksheet[XLSX.utils.encode_cell(enableOCVCell)]['v']);
            debugout("enableOCVAtDischargeEnd = " + realSOCUpperLimit);
        }

        if (!ocvMinDiffVoltCell) {
            throw "Can not find ocvMinDiffVolt definition";
        } else {
            ocvMinDiffVolt = parseInt(worksheet[XLSX.utils.encode_cell(ocvMinDiffVoltCell)]['v']);
            debugout("enableOCVAtDischargeEnd = " + realSOCUpperLimit);
        }
        // if (!sohCalcShortTempCell) {
        //     throw "Can not find dSOCJumpMax definition";
        // } else {
        //     sohCalcShortTime = (worksheet[XLSX.utils.encode_cell(sohCalcShortTimeCell)]['v']);
        //     debugout("enableCycleSOH = " + sohCalcShortTimeCell);
        // }

        // if (!dSOCJumpMaxCell) {
        //     throw "Can not find dSOCJumpMax definition";
        // } else {
        //     sohCalcShortTemp = (worksheet[XLSX.utils.encode_cell(sohCalcShortTempCell)]['v']);
        //     debugout("enableCycleSOH = " + sohCalcShortTempCell);
        // }

        if (!ocvTableSOCIndexStartCell || !ocvTableTIndexStartCell) {
            throw "Can not find T-SOC-OCV definition";
        } else {
            for (var C = ocvTableSOCIndexStartCell.c; ; C++) {
                var cell = worksheet[XLSX.utils.encode_cell({ c: C, r: ocvTableSOCIndexStartCell.r })]
                if (!cell) {
                    break;
                }
                ocvTableSOCIndexList.push(Math.round(parseFloat(cell['v'])));
            }

            for (var R = ocvTableTIndexStartCell.r; ; R++) {
                var cell = worksheet[XLSX.utils.encode_cell({ c: ocvTableTIndexStartCell.c, r: R })]
                if (!cell) {
                    break;
                }
                ocvTableTIndexList.push(Math.round(parseFloat(cell['v'])));

            }
            ocvTempHighLimit = ocvTableTIndexList[ocvTableTIndexList.length-1] + 10;
            ocvTempLowLimit = Math.max(ocvTableTIndexList[0] - 10,-49);
            if (ocvTableTIndexList.length < 2){
                ocvTempHighLimit = 150;
                ocvTempLowLimit = -48;
            }
            for (var i = 0; i < ocvTableTIndexList.length; i++) {
                var x = new Array();
                for (var j = 0; j < ocvTableSOCIndexList.length; j++) {
                    var cell = worksheet[XLSX.utils.encode_cell({ c: ocvTableSOCIndexStartCell.c + j, r: ocvTableTIndexStartCell.r + i })];
                    if (!cell || !cell['v']) {
                        throw "Undefine at " + [j, i];
                    }
                    x.push(Math.round(parseFloat(cell['v'])));
                    debugout(cell['v']);

                }
                ocvTableList.push(x);
            }

            debugout("ocvTableSOCIndexList:" + ocvTableSOCIndexList);
            debugout("ocvTableTIndexList:" + ocvTableTIndexList);
            debugout("ocvTableList:" + JSON.stringify(ocvTableList));
        }
        if (ocvTableTIndexList.length > 18 || ocvTableSOCIndexList.length > 21){
            throw "OCVTable Length Error";
        }

        if (!cycleToSOHTableCycleStartCell || !cycleToSOHTableSOHStartCell) {
            throw "Can not find CYCLE-SOH definition";
        } else {
            for (var C = cycleToSOHTableCycleStartCell.c; ; C++) {
                var cell = worksheet[XLSX.utils.encode_cell({ c: C, r: cycleToSOHTableCycleStartCell.r })]
                if (!cell) {
                    break;
                }
                cycleToSOHTableCycleList.push(Math.round(parseFloat(cell['v'])));
            }


            for (var C = cycleToSOHTableSOHStartCell.c; ; C++) {
                var cell = worksheet[XLSX.utils.encode_cell({ c: C, r: cycleToSOHTableSOHStartCell.r })]
                if (!cell) {
                    break;
                }
                cycleToSOHTableSOHList.push(Math.round(parseFloat(cell['v'])));
            }

            debugout("cycleToSOHTableCycleList:" + cycleToSOHTableCycleList);
            debugout("cycleToSOHTableSOHList:" + cycleToSOHTableSOHList);
        }

        if (!tToCAPTableTStartCell || !tToCAPTableCapStartCell) {
            throw "Can not find T-CAP definition";
        } else {
            for (var C = tToCAPTableTStartCell.c; ; C++) {
                var cell = worksheet[XLSX.utils.encode_cell({ c: C, r: tToCAPTableTStartCell.r })]
                if (!cell) {
                    break;
                }
                tToCAPTableTList.push(Math.round(parseFloat(cell['v'])));
            }


            for (var C = tToCAPTableCapStartCell.c; ; C++) {
                var cell = worksheet[XLSX.utils.encode_cell({ c: C, r: tToCAPTableCapStartCell.r })]
                if (!cell) {
                    break;
                }
                tToCAPTableCapList.push(parseFloat(cell['v']));
            }

            debugout("tToCAPTableTList:" + tToCAPTableTList);
            debugout("tToCAPTableCapList:" + tToCAPTableCapList);
        }

        var linear = require('everpolate').linear;


        // 最低温度，最搞温度
        var tMin = tToCAPTableTList[0];
        var tMax = tToCAPTableTList[tToCAPTableTList.length - 1];

        // 由最低温度，最高温度，线性插值出均匀分布的7个温度点
        var N = 18;
        var tToCAPTableTListFull = [];
        var tToCAPTableCapListFull = [];
        if (tToCAPTableTList.length > N) {
            throw "T-CAP over length";
        }
        // var tToCAPTableTListFull = linear(Array.from({ length: N }, (v, k) => k), [0, N - 1], [tMin, tMax]).map(x => parseInt(x.toFixed()));
        // // 计算这7个温度点对应的容量
        // var tToCAPTableCapListFull = linear(tToCAPTableTListFull, tToCAPTableTList, tToCAPTableCapList);
         for (var num = 0 ; num < tToCAPTableTList.length;num++){
            tToCAPTableTListFull.push(tToCAPTableTList[num]);
            tToCAPTableCapListFull.push(tToCAPTableCapList[num]);
         }

        for (var num = tToCAPTableTList.length;num < N ; num ++){
            tToCAPTableCapListFull.push(tToCAPTableCapList[tToCAPTableTList.length - 1]);
            tToCAPTableTListFull.push(tToCAPTableTList[tToCAPTableTList.length - 1]+num-tToCAPTableTList.length+1);
        }

        debugout('tToCAPTableTListFull:' + tToCAPTableTListFull);
        debugout('tToCAPTableCapListFull:' + tToCAPTableCapListFull);


        // 最小循环次数，最大循环次数
        var cycleMin = cycleToSOHTableCycleList[0];
        var cycleMax = cycleToSOHTableCycleList[cycleToSOHTableCycleList.length - 1];
        if ((cycleMax - cycleMin) < 162){
            throw "SOH Cycle Max-Min must not less than 162";
        }
        // 由小循环次数，最大循环次数，线性插值出均匀分布163个循环次数
        N = 163;
        var cycleToSOHTableCycleListFull = linear(Array.from({ length: N }, (v, k) => k), [0, N - 1], [cycleMin, cycleMax]).map(x => parseInt(x.toFixed()));
        // 计算这163个循环次数对应的SOH
        var cycleToSOHTableSOHListFull = linear(cycleToSOHTableCycleListFull, cycleToSOHTableCycleList, cycleToSOHTableSOHList);

        debugout('cycleToSOHTableCycleListFull:' + cycleToSOHTableCycleListFull);
        debugout('cycleToSOHTableSOHListFull:' + cycleToSOHTableSOHListFull);

        transpose = m => m[0].map((x, i) => m.map(x => x[i]));

        // SOC 方向插值
        /*
        var socMin = ocvTableSOCIndexList[0];
        var socMax = ocvTableSOCIndexList[ocvTableSOCIndexList.length - 1];
        N = 21;
        var ocvTableSOCIndexListFull = linear(Array.from({ length: N }, (v, k) => k), [0, N - 1], [socMin, socMax]).map(x => parseInt(x.toFixed()));

        var ocvTableListSOCFull = [];
        for (var i = 0; i < ocvTableList.length; i++) {
            var tmp = linear(ocvTableSOCIndexListFull, ocvTableSOCIndexList, ocvTableList[i]);
            ocvTableListSOCFull.push(tmp);
        }

        var ocvTableListSOCFullTransposed = transpose(ocvTableListSOCFull);

        debugout('ocvTableListSOCFull:' + JSON.stringify(ocvTableListSOCFull));
        debugout('ocvTableListSOCFullTransposed:' + JSON.stringify(ocvTableListSOCFullTransposed));


        tMin = ocvTableTIndexList[0];
        tMax = ocvTableTIndexList[ocvTableTIndexList.length - 1];
        N = 15;
        var ocvTableTIndexListFull = linear(Array.from({ length: N }, (v, k) => k), [0, N - 1], [tMin, tMax]).map(x => parseInt(x.toFixed()));

        var ocvTableListFull = [];
        for (var i = 0; i < ocvTableListSOCFullTransposed.length; i++) {
            var tmp = linear(ocvTableTIndexListFull, ocvTableTIndexList, ocvTableListSOCFullTransposed[i]);
            ocvTableListFull.push(tmp);
        }
        var ocvTableListFullTransposed = transpose(ocvTableListFull);

        // checkIncreasable = function(arr) {
        //     var last = 0;
        //     if (! arr.every(v => {var ret = (x > last); last = x; return ret;})) {
        //         throw "OCV table increasable by SOC not meet";
        //     }
        // }

        // ocvTableListFullTransposed.every(checkIncreasable);


        for (var x of ocvTableListFullTransposed) {
            var last = 0;
            var incresed = x.every((x) => { var ret = (x > last); last = x; return ret;});
            if (!incresed) {
                throw "OCV table increasable by SOC not meet";
            }

            debugout(incresed);
            debugout(JSON.stringify(x.map(v=>v.toFixed())));
        }

        debugout('ocvTableSOCIndexListFull:' + ocvTableSOCIndexListFull);
        debugout('ocvTableTIndexListFull:' + ocvTableTIndexListFull);
        debugout('ocvTableListFull:' + JSON.stringify(ocvTableListFull));

        */

        var N1 = 21;
        var ocvTableSOCIndexListFull = new Array(N1);
        if (ocvTableSOCIndexList.length > N1){
            throw "ocvTable SOC over length 21";
        }
        var gain = 1;
        if (ocvTableSOCIndexList[ocvTableSOCIndexList.length-1] <= 1){
            gain = 100;
        }
        for (var i = 0; i < N1; i++) {
            if (i < ocvTableSOCIndexList.length) {
                ocvTableSOCIndexListFull[i] = ocvTableSOCIndexList[i] * gain;
            } else {
                ocvTableSOCIndexListFull[i] = ocvTableSOCIndexListFull[ocvTableSOCIndexList.length -1] + i - ocvTableSOCIndexList.length + 1;
            }
        }
        N2 = 18;
        var ocvTableTIndexListFull = new Array(N2);
        if (ocvTableTIndexList.length > N2){
            throw "ocvTable Temp over length 21";
        }
        for (var i = 0; i < N2; i++) {
            if (i < ocvTableTIndexList.length) {
                ocvTableTIndexListFull[i] = ocvTableTIndexList[i];
            } else {
                ocvTableTIndexListFull[i] = ocvTableTIndexList[ocvTableTIndexList.length -1] + i - ocvTableTIndexList.length+1;
            }
        }

        var ocvTableListFull1 = new Array(N1 * N2);

        for (var i = 0; i < N2; i++) {
            var ii, jj, vol;
            if (i >= ocvTableTIndexList.length) {
                ii = ocvTableTIndexList.length - 1;
            } else {
                ii = i;
            }

            for (var j = 0; j < N1; j++) {
                if (j >= ocvTableSOCIndexList.length) {
                    jj = ocvTableSOCIndexList.length - 1;
                    ocvTableListFull1[i * N1 + j] = ocvTableList[ii][jj] + j - ocvTableSOCIndexList.length + 1;
                } else {
                    jj = j;
                    ocvTableListFull1[i * N1 + j] = ocvTableList[ii][jj];
                }
                if (j >= 1){
                    if (ocvTableListFull1[i * N1 + j] <= ocvTableListFull1[i * N1 + j-1]){
                        throw "OCVTable is not increased";
                    }
                }

            }
        }
        var ocvTableListFull = new Array(N1 * N2);
        for (var i = 0; i < N1; i++){
            for (var j = 0; j < N2; j++){
                ocvTableListFull[i*N2+j] = ocvTableListFull1[N1*j+i];
            }
        }

        debugout('ocvTableSOCIndexListFull:' + ocvTableSOCIndexListFull);
        debugout('ocvTableTIndexListFull:' + ocvTableTIndexListFull);
        debugout('ocvTableListFull:' + JSON.stringify(ocvTableListFull));


        var mdata = {
            enableModelSOX: enableModelSOX,
            totalCap:info.BatteryInfo.totalCap,
            enableCycleSOH:enableCycleSOH,
            CulumCapPerCycle:CulumCapPerCycle,
            enableSOCJumpShortTimeOCV:enableSOCJumpShortTimeOCV,
            enableOCVAtDischargeEnd:enableOCVAtDischargeEnd,
            realSOCUpperLimit:realSOCUpperLimit,
            realSOCLowerLimit:realSOCLowerLimit,
            tToCAPTableTListFull:tToCAPTableTListFull,
            tToCAPTableCapListFull:tToCAPTableCapListFull,
            cycleToSOHTableCycleListFull:cycleToSOHTableCycleListFull,
            cycleToSOHTableSOHListFull:cycleToSOHTableSOHListFull,
            ocvTableSOCIndexListFull:ocvTableSOCIndexListFull,
            ocvTableTIndexListFull:ocvTableTIndexListFull,
            ocvTableListFull:ocvTableListFull,
            ocvTempHighLimit:ocvTempHighLimit,
            ocvTempLowLimit:ocvTempLowLimit,
            dSOCJumpMax:dSOCJumpMax,
            sohCalcShortTime:sohCalcShortTime,
            sohCalcShortTemp:sohCalcShortTemp,
            enableSocOcv:enableOCV,
            ocvMinDiffVolt:ocvMinDiffVolt,
            totalvol:info.BatteryInfo.totalvoltage,
        };

        //console.log(JSON.stringify(mdata, null, "  "));
        //console.log(JSON.stringify(mdata));
        info.render("ModelConfigure.c", "ModelConfigure.c.tmpl", mdata);
        return {};
    }
}
