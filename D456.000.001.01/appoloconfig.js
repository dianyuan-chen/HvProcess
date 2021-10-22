#!/usr/bin/env node

modules = [
    {name: "BatteryInfo", dir: "applications/bcu", js: "batteryinfo.js"},
    {name: "SystemConnection", dir: "applications/bcu", js: "systemconnection.js"},
    {name: "BalanceM", dir: "applications/bcu", js: "balancem.js"},
    {name: "LibInfo"},
    {name: "AppInfo", dir: "applications", js: "appinfo.js"},
    {name: "CanTp", dir: "com/CanTp", js: "cantp.js"},
    {name: "DtuTp"},
    {name: "LtcTp"},
    {name: "InnerTp", dir: "com/InnerTp", js: "innertp.js"},
    {name: "J1939Tp", dir: "com/J1939Tp", js: "j1939tp.js"},
    {name: "CanIf", dir: "com/CanIf", js: "canif.js"},
    {name: "CanDrv", dir: "arch/hcs12x", js:"candrv.js"},
    {name: "PwmCapture", dir: "arch/hcs12x", js: "pwmcapture.js"},
    {name: "PduR", dir: "com/PduR", js: "pdur.js"},
    {name: "GB32960", dir: "com/DtuTp", js: "gb32960.js"},
    {name: "Diagnosis", dir: "bms_rte", js: "diagnosis.js"},
    {name: "ParameterM", dir: "bms_rte", js: "parameterm.js"},
    {name: "CurrentM", dir: "bms_rte", js: "currentm.js"},
    {name: "RelayM", dir: "bms_rte", js: "relaym.js"},
    {name: "Charge", dir: "applications/bcu", js: "charge.js"},
    {name: "RuntimeM", dir: "bms_rte", js: "runtimem.js"},
    {name: "Ntc", dir: "bms_rte", js: "ntc.js"},
    {name: "ModelConfig", dir: "applications/bcu", js: "ModelConfigure.js"},
];

var ejs = require("ejs");
var fs = require("fs");
var fx = require('mkdir-recursive');
var libconfig = {};
try {
    libconfig = require('./libconfig.js')
} catch(err) {

}

var path = require("path");

var program = require('commander');
var getJsonPath = (obj, path) => {
    return path.split(".").reduce((v,k) => {
        var ks = k.match(/(.+)\[(\d*)\]/);
        if (ks == null) return v[k];
        return v[ks[1]][parseInt(ks[2])];
    }, obj);
}

var defcalfile = path.join(__dirname, "applications/bcu/calibrate.json");
var defcfgfile = path.join(__dirname, "applications/bcu/config.js");
var defoutdir = path.join(__dirname, "config");

var appendCalibrate = (cfgfile, calfile) => {
  var cfg = require(cfgfile);
  if (!cfg.hasOwnProperty('ParameterM')) return cfg;
  cfgParamterM = cfg.ParameterM;
  cfg.ParameterM = require(calfile);
  cfg.ParameterM.Diagnosis = cfg.ParameterM.Diagnosis.concat(cfgParamterM.Diagnosis);
  if (!cfg.hasOwnProperty('BatteryInfo')) return cfg;
  calInfo = require(calfile);
  cfg.BatteryInfo.Diagnosis = calInfo.Diagnosis;
  return cfg;
}

program
  .version("0.0.1")
  .option('-o, --outdir [dir]', 'The output directory, default [' + defoutdir + ']', defoutdir)
  .option('-c, --config [file]', 'The config file, default [' + defcfgfile + ']', defcfgfile)
  .option('--calibrate [calibratefile]', 'Calibrate JSON file, default [' + defcalfile + ']', defcalfile)
  .command("getcfg [key]")
  .action(function(key){
      var value = appendCalibrate(program.config, program.calibrate);
      if (key) value = getJsonPath(value, key);
      console.log(JSON.stringify(value));
      process.exit(0);
  });

program.parse(process.argv);
var config = appendCalibrate(program.config, program.calibrate);
if (libconfig.hasOwnProperty('LibInfo')) {
    config['LibInfo'] = libconfig['LibInfo'];
}
var info = {};

modules.forEach(m => {
    if (!config.hasOwnProperty(m.name)) {
        return;
    }
    if (!m.hasOwnProperty("dir")) {
        info[m.name] = config[m.name];
        return;
    }
    if (!m.hasOwnProperty("js")) {
        info[m.name] = config[m.name];
        return;
    }
    var mod;
    try  {
        mod = require("./" + m.dir + "/" + m.js);
    } catch (err) {
        mod = require(process.env.TOPDIR + "/"  + m.dir + "/" + m.js);
    }

    info.render = function(destFile, tmplFile, data) {
        var head = '/*\r\n' +
        ' * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n' +
        ' * Generate by template render, DONOT edit it\r\n' +
        ' * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n' +
        ' */\r\n\r\n';

        var destPath = path.join(program.outdir, destFile);
        fx.mkdirSync(path.dirname(destPath));
        try {
            fs.writeFileSync(
                destPath,
                head + ejs.render(
                    fs.readFileSync(path.join(__dirname, m.dir, tmplFile)).toString(),
                    data));
        } catch(err) {
            fs.appendFileSync(
                destPath,
                head + ejs.render(
                    fs.readFileSync(path.join(process.env.TOPDIR, m.dir, tmplFile)).toString(),
                    data));
        }
    };
    info[m.name] = mod.process(config[m.name], info);
});

try {
    var pcba = 'UPC600'
    var bcutype = 'C600'
    if (info.hasOwnProperty('SystemConnection') && info.SystemConnection.hasOwnProperty('PCBA')) {
        pcba = info.SystemConnection.PCBA;
        bcutype = info.SystemConnection.BcuType;

    }
    console.log(info.AppInfo.releaseFileName + ';' + pcba + ';' + bcutype);
} catch (err) {
}
