[~, p] = system('where gcc');
[p, ~, ~] = fileparts(p);
[p, ~, ~] = fileparts(p);
setenv('MW_MINGW64_LOC', p);

%mpath=getenv('MATLABPATH');
% cd(mpath);
mpath=getenv('TOPDIR');
fixpath_tlc='/bms_rte/matlab';
fixpath_lib='/bms_rte/matlab/udan_library';
addpath(strcat(mpath,fixpath_tlc));
addpath(strcat(mpath,fixpath_lib));
addpath(strcat(mpath,'/bms_rte/matlab/simsrc'));
run(fullfile(mpath ,'/bms_rte/matlab/simsrc/simsrc_native.m'));
run(fullfile(mpath ,'/bms_rte/matlab/simsrc/CalcSOP.m'));



open_system('Udan_SOC','loadonly');
rtwbuild('Udan_SOC');
close_system('Udan_SOC');

% open_system('Udan_SOP','loadonly');
% rtwbuild('Udan_SOP');
% close_system('Udan_SOP');

exit
