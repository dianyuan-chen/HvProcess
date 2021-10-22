classdef ParameterM_EeepParaIndexType < Simulink.IntEnumType
    % MATLAB enumeration class definition generated from template
    
    enumeration
        PARAMETERM_EEEP_PARA_START(0),
		PARAMETERM_EEEP_TOTAL_CAP_INDEX(0),
		PARAMETERM_EEEP_LEFT_CAP_INDEX(1),
		PARAMETERM_EEEP_DISCHARGE_CNT_INDEX(2),
		PARAMETERM_EEEP_DISCHARGE_CNT_STATE_INDEX(3),
		PARAMETERM_EEEP_HALL1_ZEROOFFSET_INDEX(4),
		PARAMETERM_EEEP_HALL2_ZEROOFFSET_INDEX(5),
		PARAMETERM_EEEP_SHUNT_ZEROOFFSET_INDEX(6),
		PARAMETERM_EEEP_OCVSOC_TIME_HIGH_INDEX(7),
		PARAMETERM_EEEP_OCVSOC_TIME_LOW_INDEX(8),
		PARAMETERM_EEEP_VIN1_INDEX(9),
		PARAMETERM_EEEP_VIN2_INDEX(10),
		PARAMETERM_EEEP_VIN3_INDEX(11),
		PARAMETERM_EEEP_VIN4_INDEX(12),
		PARAMETERM_EEEP_VIN5_INDEX(13),
		PARAMETERM_EEEP_VIN6_INDEX(14),
		PARAMETERM_EEEP_VIN7_INDEX(15),
		PARAMETERM_EEEP_VIN8_INDEX(16),
		PARAMETERM_EEEP_VIN9_INDEX(17),
		PARAMETERM_EEEP_LEFTCAP_INTEGRAL_L_INDEX(18),
		PARAMETERM_EEEP_LEFTCAP_INTEGRAL_H_INDEX(19),
		PARAMETERM_EEEP_CUMULATIVE_CHG_CAP_L_INDEX(20),
		PARAMETERM_EEEP_CUMULATIVE_CHG_CAP_H_INDEX(21),
		PARAMETERM_EEEP_CUMULATIVE_DCHG_CAP_L_INDEX(22),
		PARAMETERM_EEEP_CUMULATIVE_DCHG_CAP_H_INDEX(23),
		PARAMETERM_EEEP_SHUNT_GAIN_ERROR_INDEX(24),
		PARAMETERM_EEEP_HALL1_GAIN_ERROR_INDEX(25),
		PARAMETERM_EEEP_HALL2_GAIN_ERROR_INDEX(26),
		PARAMETERM_EEEP_HVBPOS_GAIN_ERROR_INDEX(27),
		PARAMETERM_EEEP_HV1_GAIN_ERROR_INDEX(28),
		PARAMETERM_EEEP_HV2_GAIN_ERROR_INDEX(29),
		PARAMETERM_EEEP_HV3_GAIN_ERROR_INDEX(30),
		PARAMETERM_EEEP_HV4_GAIN_ERROR_INDEX(31),
		PARAMETERM_EEEP_HV5_GAIN_ERROR_INDEX(32),

        PARAMETERM_EEEP_LEFTCAP_H_INDEX(33),
        PARAMETERM_EEEP_LEFTCAP_L_INDEX(34),
        PARAMETERM_EEEP_MODEL_DSOC_INDEX(35),
        PARAMETERM_EEEP_MODEL_TSOC_INDEX(36),
        PARAMETERM_EEEP_POWER_LIMIT_INDEX(37),
        PARAMETERM_EEEP_SOH_Full_INDEX(38),
        PARAMETERM_EEEP_SOH_INDEX(39),
        PARAMETERM_EEEP_LEFTCAP_WOCALIB_H_INDEX(40),
        PARAMETERM_EEEP_LEFTCAP_WOCALIB_L_INDEX(41),
        PARAMETERM_EEEP_PARA_STOP(41),
		PARAMETERM_EEEP_PARA_MAX(42)
    end

    methods (Static)
        
        function defaultValue = getDefaultValue()
            % GETDEFAULTVALUE  Returns the default enumerated value.
            %   If this method is not defined, the first enumeration is used.
            defaultValue = ParameterM_EeepParaIndexType.PARAMETERM_EEEP_PARA_START;
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
            headerFile = 'ParameterM.h';
        end
        
        function flag = addClassNameToEnumNames()
            % ADDCLASSNAMETOENUMNAMES  Indicate whether code generator applies the class name as a prefix
            %                          to the enumeration.
            flag = false;
        end

    end

end
