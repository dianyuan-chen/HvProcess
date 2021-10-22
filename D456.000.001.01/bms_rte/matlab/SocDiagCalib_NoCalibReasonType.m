classdef SocDiagCalib_NoCalibReasonType < Simulink.IntEnumType
    % MATLAB enumeration class definition generated from template
    
    enumeration
    SOC_NO_CALIB_REASON_NO_TRIGGER(0),
    SOC_NO_CALIB_REASON_NORMAL(1),
    SOC_NO_CALIB_REASON_NOT_REL(2),
    SOC_NO_CALIB_REASON_SOC_HIGH(3),
    SOC_NO_CALIB_REASON_SOC_LOW(4),
    SOC_NO_CALIB_REASON_HAV(5),
    SOC_NO_CALIB_REASON_LAV(6),
    SOC_NO_CALIB_REASON_DELAY(7),
    SOC_NO_CALIB_REASON_MEMORY(8),
    SOC_NO_CALIB_REASON_OTHERS(9)
    end

    methods (Static)
        
        function defaultValue = getDefaultValue()
            % GETDEFAULTVALUE  Returns the default enumerated value.
            %   If this method is not defined, the first enumeration is used.
            defaultValue = SocDiagCalib_NoCalibReasonType.SOC_NO_CALIB_REASON_NO_TRIGGER;
        end

        function dScope = getDataScope()
            % GETDATASCOPE  Specifies whether the data type definition should be imported from,
            %               or exported to, a header file during code generation.
            dScope = 'Imported';
        end

        function desc = getDescription()
            % GETDESCRIPTION  Returns a description of the enumeration.
            desc = '';
        end
        
        function headerFile = getHeaderFile()
            % GETHEADERFILE  Specifies the name of a header file. 
            headerFile = 'SocDiagCalib.h';
        end
        
        function flag = addClassNameToEnumNames()
            % ADDCLASSNAMETOENUMNAMES  Indicate whether code generator applies the class name as a prefix
            %                          to the enumeration.
            flag = false;
        end

    end

end
