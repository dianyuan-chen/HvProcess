classdef ParameterM_CalibParaType< Simulink.Parameter
 methods
    function setupCoderInfo(h)
      % Use custom storage classes from this package
      useLocalCustomStorageClasses(h, 'bms_rte');
    end
  end % methods
end