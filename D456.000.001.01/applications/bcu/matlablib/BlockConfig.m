
%---------------------------------------------------------------------------
%  MATLAB function for configuration set generated on 09-Feb-2018 10:53:36
%  MATLAB version: 9.3.0.713579 (R2017b)
%---------------------------------------------------------------------------

cs = getActiveConfigSet(bdroot(gcs));

% Original configuration set version: 1.17.1
if cs.versionCompare('1.17.1') < 0
    error('Simulink:MFileVersionViolation', 'The version of the target configuration set is older than the original configuration set.');
end

% Original environment character encoding: GBK
if ~strcmpi(get_param(0, 'CharacterEncoding'), 'GBK')
    warning('Simulink:EncodingUnMatched', 'The target character encoding (%s) is different from the original (%s).',  get_param(0, 'CharacterEncoding'), 'GBK');
end

% Do not change the order of the following commands. There are dependencies between the parameters.
set_param(cs,'Name', 'Configuration'); % Name
set_param(cs,'Description', ''); % Description

% Original configuration set target is ert.tlc
cs.switchTarget('ert.tlc','');

set_param(cs,'HardwareBoard', 'None');   % Hardware board

set_param(cs,'Solver', 'FixedStepAuto');   % Solver

% Solver
set_param(cs,'StartTime', '0.0');   % Start time
set_param(cs,'StopTime', '1000');   % Stop time
set_param(cs,'ConcurrentTasks', 'off');   % Allow tasks to execute concurrently on target
set_param(cs,'SampleTimeConstraint', 'Unconstrained');   % Periodic sample time constraint
set_param(cs,'SolverType', 'Fixed-step');   % Type
set_param(cs,'FixedStep', '0.1');   % Fixed-step size (fundamental sample time)
set_param(cs,'EnableMultiTasking', 'off');   % Treat each discrete rate as a separate task
set_param(cs,'DecoupledContinuousIntegration', 'off');   % Enable decoupled continuous integration
set_param(cs,'AutoInsertRateTranBlk', 'off');   % Automatically handle rate transition for data transfer
set_param(cs,'PositivePriorityOrder', 'off');   % Higher priority value indicates higher task priority

% Data Import/Export
set_param(cs,'LoadExternalInput', 'off');   % Load external input
set_param(cs,'LoadInitialState', 'off');   % Load initial state
set_param(cs,'SaveTime', 'on');   % Save time
set_param(cs,'TimeSaveName', 'tout');   % Time variable
set_param(cs,'SaveState', 'off');   % Save states
set_param(cs,'SaveFormat', 'Dataset');   % Format
set_param(cs,'SaveOutput', 'on');   % Save output
set_param(cs,'OutputSaveName', 'yout');   % Output variable
set_param(cs,'SaveFinalState', 'off');   % Save final state
set_param(cs,'SignalLogging', 'on');   % Signal logging
set_param(cs,'SignalLoggingName', 'logsout');   % Signal logging name
set_param(cs,'DSMLogging', 'on');   % Data stores
set_param(cs,'DSMLoggingName', 'dsmout');   % Data stores logging name
set_param(cs,'LoggingToFile', 'off');   % Log Dataset data to file
set_param(cs,'DatasetSignalFormat', 'timeseries');   % Dataset signal format
set_param(cs,'ReturnWorkspaceOutputs', 'off');   % Single simulation output
set_param(cs,'InspectSignalLogs', 'off');   % Record logged workspace data in Simulation Data Inspector
set_param(cs,'LimitDataPoints', 'off');   % Limit data points
set_param(cs,'Decimation', '1');   % Decimation

% Optimization
set_param(cs,'BlockReduction', 'on');   % Block reduction
set_param(cs,'ConditionallyExecuteInputs', 'on');   % Conditional input branch execution
set_param(cs,'BooleanDataType', 'on');   % Implement logic signals as Boolean data (vs. double)
set_param(cs,'LifeSpan', 'inf');   % Application lifespan (days)
set_param(cs,'UseDivisionForNetSlopeComputation', 'on');   % Use division for fixed-point net slope computation
set_param(cs,'UseFloatMulNetSlope', 'off');   % Use floating-point multiplication to handle net slope corrections
set_param(cs,'DefaultUnderspecifiedDataType', 'double');   % Default for underspecified data type
set_param(cs,'UseSpecifiedMinMax', 'off');   % Optimize using the specified minimum and maximum values
set_param(cs,'ZeroExternalMemoryAtStartup', 'on');   % Remove root level I/O zero initialization
set_param(cs,'InitFltsAndDblsToZero', 'off');   % Use memset to initialize floats and doubles to 0.0
set_param(cs,'ZeroInternalMemoryAtStartup', 'on');   % Remove internal data zero initialization
set_param(cs,'EfficientFloat2IntCast', 'off');   % Remove code from floating-point to integer conversions that wraps out-of-range values
set_param(cs,'EfficientMapNaN2IntZero', 'on');   % Remove code from floating-point to integer conversions with saturation that maps NaN to zero
set_param(cs,'NoFixptDivByZeroProtection', 'off');   % Remove code that protects against division arithmetic exceptions
set_param(cs,'SimCompilerOptimization', 'off');   % Compiler optimization level
set_param(cs,'AccelVerboseBuild', 'off');   % Verbose accelerator builds
set_param(cs,'DefaultParameterBehavior', 'Inlined');   % Default parameter behavior
set_param(cs,'OptimizeBlockIOStorage', 'on');   % Signal storage reuse
set_param(cs,'LocalBlockOutputs', 'on');   % Enable local block outputs
set_param(cs,'ExpressionFolding', 'on');   % Eliminate superfluous local variables (expression folding)
set_param(cs,'BufferReuse', 'on');   % Reuse local block outputs
set_param(cs,'GlobalBufferReuse', 'on');   % Reuse global block outputs
set_param(cs,'GlobalVariableUsage', 'None');   % Optimize global data access
set_param(cs,'OptimizeBlockOrder', 'off');   % Optimize block operation order in the generated code
set_param(cs,'OptimizeDataStoreBuffers', 'on');   % Reuse buffers for Data Store Read and Data Store Write blocks
set_param(cs,'BusAssignmentInplaceUpdate', 'on');   % Perform inplace updates for Bus Assignment blocks
set_param(cs,'DifferentSizesBufferReuse', 'off');   % Reuse buffers of different sizes and dimensions
set_param(cs,'StrengthReduction', 'off');   % Simplify array indexing
set_param(cs,'EnableMemcpy', 'on');   % Use memcpy for vector assignment
set_param(cs,'MemcpyThreshold', 64);   % Memcpy threshold (bytes)
set_param(cs,'BooleansAsBitfields', 'off');   % Pack Boolean data into bitfields
set_param(cs,'InlineInvariantSignals', 'off');   % Inline invariant signals
set_param(cs,'RollThreshold', 5);   % Loop unrolling threshold
set_param(cs,'MaxStackSize', 'Inherit from target');   % Maximum stack size (bytes)
set_param(cs,'PassReuseOutputArgsAs', 'Individual arguments');   % Pass reusable subsystem outputs as
set_param(cs,'StateBitsets', 'off');   % Use bitsets for storing state configuration
set_param(cs,'DataBitsets', 'off');   % Use bitsets for storing Boolean data
set_param(cs,'ActiveStateOutputEnumStorageType', 'Native Integer');   % Base storage type for automatically created enumerations
set_param(cs,'AdvancedOptControl', '');   % Disable incompatible optimizations
set_param(cs,'BufferReusableBoundary', 'on');   % Buffer for reusable subsystems
set_param(cs,'PassReuseOutputArgsThreshold', 12);   % Maximum number of arguments for subsystem outputs

% Diagnostics
set_param(cs,'AlgebraicLoopMsg', 'warning');   % Algebraic loop
set_param(cs,'ArtificialAlgebraicLoopMsg', 'warning');   % Minimize algebraic loop
set_param(cs,'BlockPriorityViolationMsg', 'warning');   % Block priority violation
set_param(cs,'MinStepSizeMsg', 'warning');   % Min step size violation
set_param(cs,'TimeAdjustmentMsg', 'none');   % Sample hit time adjusting
set_param(cs,'MaxConsecutiveZCsMsg', 'error');   % Consecutive zero crossings violation
set_param(cs,'UnknownTsInhSupMsg', 'warning');   % Unspecified inheritability of sample time
set_param(cs,'ConsistencyChecking', 'none');   % Solver data inconsistency
set_param(cs,'SolverPrmCheckMsg', 'none');   % Automatic solver parameter selection
set_param(cs,'ModelReferenceExtraNoncontSigs', 'error');   % Extraneous discrete derivative signals
set_param(cs,'StateNameClashWarn', 'none');   % State name clash
set_param(cs,'SimStateInterfaceChecksumMismatchMsg', 'warning');   % SimState interface checksum mismatch
set_param(cs,'SimStateOlderReleaseMsg', 'error');   % SimState object from earlier release
set_param(cs,'InheritedTsInSrcMsg', 'warning');   % Source block specifies -1 sample time
set_param(cs,'MultiTaskRateTransMsg', 'error');   % Multitask rate transition
set_param(cs,'SingleTaskRateTransMsg', 'none');   % Single task rate transition
set_param(cs,'MultiTaskCondExecSysMsg', 'error');   % Multitask conditionally executed subsystem
set_param(cs,'TasksWithSamePriorityMsg', 'warning');   % Tasks with equal priority
set_param(cs,'SigSpecEnsureSampleTimeMsg', 'warning');   % Enforce sample times specified by Signal Specification blocks
set_param(cs,'SignalResolutionControl', 'UseLocalSettings');   % Signal resolution
set_param(cs,'CheckMatrixSingularityMsg', 'none');   % Division by singular matrix
set_param(cs,'IntegerSaturationMsg', 'warning');   % Saturate on overflow
set_param(cs,'UnderSpecifiedDataTypeMsg', 'none');   % Underspecified data types
set_param(cs,'SignalRangeChecking', 'none');   % Simulation range checking
set_param(cs,'IntegerOverflowMsg', 'error');   % Wrap on overflow
set_param(cs,'SignalInfNanChecking', 'error');   % Inf or NaN block output
set_param(cs,'RTPrefix', 'error');   % "rt" prefix for identifiers
set_param(cs,'ParameterDowncastMsg', 'error');   % Detect downcast
set_param(cs,'ParameterOverflowMsg', 'error');   % Detect overflow
set_param(cs,'ParameterUnderflowMsg', 'none');   % Detect underflow
set_param(cs,'ParameterPrecisionLossMsg', 'warning');   % Detect precision loss
set_param(cs,'ParameterTunabilityLossMsg', 'error');   % Detect loss of tunability
set_param(cs,'ReadBeforeWriteMsg', 'UseLocalSettings');   % Detect read before write
set_param(cs,'WriteAfterReadMsg', 'UseLocalSettings');   % Detect write after read
set_param(cs,'WriteAfterWriteMsg', 'UseLocalSettings');   % Detect write after write
set_param(cs,'MultiTaskDSMMsg', 'error');   % Multitask data store
set_param(cs,'UniqueDataStoreMsg', 'none');   % Duplicate data store names
set_param(cs,'UnderspecifiedInitializationDetection', 'Simplified');   % Underspecified initialization detection
set_param(cs,'ArrayBoundsChecking', 'none');   % Array bounds exceeded
set_param(cs,'AssertControl', 'DisableAll');   % Model Verification block enabling
set_param(cs,'AllowSymbolicDim', 'on');   % Allow symbolic dimension specification
set_param(cs,'UnnecessaryDatatypeConvMsg', 'none');   % Unnecessary type conversions
set_param(cs,'VectorMatrixConversionMsg', 'none');   % Vector/matrix block input conversion
set_param(cs,'Int32ToFloatConvMsg', 'warning');   % 32-bit integer to single precision float conversion
set_param(cs,'FixptConstUnderflowMsg', 'none');   % Detect underflow
set_param(cs,'FixptConstOverflowMsg', 'none');   % Detect overflow
set_param(cs,'FixptConstPrecisionLossMsg', 'none');   % Detect precision loss
set_param(cs,'SignalLabelMismatchMsg', 'none');   % Signal label mismatch
set_param(cs,'UnconnectedInputMsg', 'warning');   % Unconnected block input ports
set_param(cs,'UnconnectedOutputMsg', 'warning');   % Unconnected block output ports
set_param(cs,'UnconnectedLineMsg', 'warning');   % Unconnected line
set_param(cs,'RootOutportRequireBusObject', 'warning');   % Unspecified bus object at root Outport block
set_param(cs,'BusObjectLabelMismatch', 'warning');   % Element name mismatch
set_param(cs,'StrictBusMsg', 'ErrorLevel1');   % Bus signal treated as vector
set_param(cs,'NonBusSignalsTreatedAsBus', 'none');   % Non-bus signals treated as bus signals
set_param(cs,'BusNameAdapt', 'WarnAndRepair');   % Repair bus selections
set_param(cs,'InvalidFcnCallConnMsg', 'error');   % Invalid function-call connection
set_param(cs,'FcnCallInpInsideContextMsg', 'error');   % Context-dependent inputs
set_param(cs,'SFcnCompatibilityMsg', 'none');   % S-function upgrades needed
set_param(cs,'FrameProcessingCompatibilityMsg', 'error');   % Block behavior depends on frame status of signal
set_param(cs,'ModelReferenceVersionMismatchMessage', 'none');   % Model block version mismatch
set_param(cs,'ModelReferenceIOMismatchMessage', 'none');   % Port and parameter mismatch
set_param(cs,'ModelReferenceIOMsg', 'none');   % Invalid root Inport/Outport block connection
set_param(cs,'ModelReferenceDataLoggingMessage', 'warning');   % Unsupported data logging
set_param(cs,'SaveWithDisabledLinksMsg', 'warning');   % Block diagram contains disabled library links
set_param(cs,'SaveWithParameterizedLinksMsg', 'warning');   % Block diagram contains parameterized library links
set_param(cs,'SFUnusedDataAndEventsDiag', 'warning');   % Unused data, events, messages and functions
set_param(cs,'SFUnexpectedBacktrackingDiag', 'error');   % Unexpected backtracking
set_param(cs,'SFInvalidInputDataAccessInChartInitDiag', 'warning');   % Invalid input data access in chart initialization
set_param(cs,'SFNoUnconditionalDefaultTransitionDiag', 'error');   % No unconditional default transitions
set_param(cs,'SFTransitionOutsideNaturalParentDiag', 'warning');   % Transition outside natural parent
set_param(cs,'SFUnreachableExecutionPathDiag', 'warning');   % Unreachable execution path
set_param(cs,'SFUndirectedBroadcastEventsDiag', 'warning');   % Undirected event broadcasts
set_param(cs,'SFTransitionActionBeforeConditionDiag', 'warning');   % Transition action specified before condition action
set_param(cs,'SFOutputUsedAsStateInMooreChartDiag', 'error');   % Read-before-write to output in Moore chart
set_param(cs,'SFTemporalDelaySmallerThanSampleTimeDiag', 'warning');   % Absolute time temporal value shorter than sampling period
set_param(cs,'SFSelfTransitionDiag', 'warning');   % Self-transition on leaf state
set_param(cs,'SFExecutionAtInitializationDiag', 'none');   % 'Execute-at-initialization' disabled in presence of input events
set_param(cs,'SFMachineParentedDataDiag', 'warning');   % Use of machine-parented data instead of Data Store Memory
set_param(cs,'IgnoredZcDiagnostic', 'warning');   % Ignored zero crossings
set_param(cs,'InitInArrayFormatMsg', 'warning');   % Initial state is array
set_param(cs,'MaskedZcDiagnostic', 'warning');   % Masked zero crossings
set_param(cs,'ModelReferenceSymbolNameMessage', 'warning');   % Insufficient maximum identifier length
set_param(cs,'AllowedUnitSystems', 'all');   % Allowed unit systems
set_param(cs,'UnitsInconsistencyMsg', 'warning');   % Units inconsistency messages
set_param(cs,'AllowAutomaticUnitConversions', 'on');   % Allow automatic unit conversions
set_param(cs,'RCSCObservableMsg', 'warning');   % Detect ambiguous custom storage class final values
set_param(cs,'RCSCRenamedMsg', 'warning');   % Detect non-reused custom storage classes
set_param(cs,'ForceCombineOutputUpdateInSim', 'off');   % Combine output and update methods for code generation and simulation

% Hardware Implementation
set_param(cs,'ProdHWDeviceType', 'Freescale->HC(S)12');   % Production device vendor and type
set_param(cs,'ProdLongLongMode', 'off');   % Support long long
set_param(cs,'ProdLargestAtomicInteger', 'Char');   % Largest atomic integer size
set_param(cs,'ProdLargestAtomicFloat', 'None');   % Largest atomic floating-point size
set_param(cs,'ProdIntDivRoundTo', 'Zero');   % Production hardware signed integer division rounds to
set_param(cs,'ProdEqTarget', 'on');   % Test hardware is the same as production hardware
set_param(cs,'TargetPreprocMaxBitsSint', 32);   % Maximum bits for signed integer in C preprocessor
set_param(cs,'TargetPreprocMaxBitsUint', 32);   % Maximum bits for unsigned integer in C preprocessor

% Model Referencing
set_param(cs,'UpdateModelReferenceTargets', 'IfOutOfDateOrStructuralChange');   % Rebuild
set_param(cs,'EnableParallelModelReferenceBuilds', 'off');   % Enable parallel model reference builds
set_param(cs,'ModelReferenceNumInstancesAllowed', 'Multi');   % Total number of instances allowed per top model
set_param(cs,'PropagateVarSize', 'Infer from blocks in model');   % Propagate sizes of variable-size signals
set_param(cs,'ModelReferenceMinAlgLoopOccurrences', 'off');   % Minimize algebraic loop occurrences
set_param(cs,'EnableRefExpFcnMdlSchedulingChecks', 'on');   % Enable strict scheduling checks for referenced models
set_param(cs,'PropagateSignalLabelsOutOfModel', 'on');   % Propagate all signal labels out of the model
set_param(cs,'ModelReferencePassRootInputsByReference', 'on');   % Pass fixed-size scalar root inputs by value for code generation
set_param(cs,'ModelDependencies', '');   % Model dependencies
set_param(cs,'ParallelModelReferenceErrorOnInvalidPool', 'on');   % Perform consistency check on parallel pool
set_param(cs,'SupportModelReferenceSimTargetCustomCode', 'off');   % Include custom code for referenced models

% Simulation Target
set_param(cs,'MATLABDynamicMemAlloc', 'off');   % Dynamic memory allocation in MATLAB Function blocks
set_param(cs,'CompileTimeRecursionLimit', 50);   % Compile-time recursion limit for MATLAB functions
set_param(cs,'EnableRuntimeRecursion', 'on');   % Enable run-time recursion for MATLAB functions
set_param(cs,'SFSimEcho', 'on');   % Echo expressions without semicolons
set_param(cs,'SimCtrlC', 'on');   % Ensure responsiveness
set_param(cs,'SimIntegrity', 'on');   % Ensure memory integrity
set_param(cs,'SimGenImportedTypeDefs', 'off');   % Generate typedefs for imported bus and enumeration types
set_param(cs,'SimBuildMode', 'sf_incremental_build');   % Simulation target build mode
set_param(cs,'SimReservedNameArray', []);   % Reserved names
set_param(cs,'SimParseCustomCode', 'on');   % Parse custom code symbols
set_param(cs,'SimCustomSourceCode', '');   % Source file
set_param(cs,'SimCustomHeaderCode', '');   % Header file
set_param(cs,'SimCustomInitializer', '');   % Initialize function
set_param(cs,'SimCustomTerminator', '');   % Terminate function
set_param(cs,'SimUserIncludeDirs', '');   % Include directories
set_param(cs,'SimUserSources', '');   % Source files
set_param(cs,'SimUserLibraries', '');   % Libraries
set_param(cs,'SimUserDefines', '');   % Defines
set_param(cs,'SFSimEnableDebug', 'off');   % Allow setting breakpoints during simulation

% Code Generation
set_param(cs,'RemoveResetFunc', 'on');   % Remove reset function
set_param(cs,'ExistingSharedCode', '');   % Existing shared code
set_param(cs,'TargetLang', 'C');   % Language
set_param(cs,'Toolchain', 'MinGW64 | gmake (64-bit Windows)');   % Toolchain
set_param(cs,'BuildConfiguration', 'Faster Builds');   % Build configuration
set_param(cs,'ObjectivePriorities', {'MISRA C:2012 guidelines'});   % Prioritized objectives
set_param(cs,'CheckMdlBeforeBuild', 'Off');   % Check model before generating code
set_param(cs,'SILDebugging', 'off');   % Enable source-level debugging for SIL
set_param(cs,'GenCodeOnly', 'on');   % Generate code only
set_param(cs,'PackageGeneratedCodeAndArtifacts', 'off');   % Package code and artifacts
set_param(cs,'RTWVerbose', 'on');   % Verbose build
set_param(cs,'RetainRTWFile', 'off');   % Retain .rtw file
set_param(cs,'ProfileTLC', 'off');   % Profile TLC
set_param(cs,'TLCDebug', 'off');   % Start TLC debugger when generating code
set_param(cs,'TLCCoverage', 'off');   % Start TLC coverage when generating code
set_param(cs,'TLCAssert', 'off');   % Enable TLC assertion
set_param(cs,'RTWUseSimCustomCode', 'off');   % Use the same custom code settings as Simulation Target
set_param(cs,'CustomSourceCode', '/*lint -e* -w0 */');   % Source file
set_param(cs,'CustomHeaderCode', '/*lint -e* -w0 */');   % Header file
set_param(cs,'CustomInclude', '');   % Include directories
set_param(cs,'CustomSource', '');   % Source files
set_param(cs,'CustomLibrary', '');   % Libraries
set_param(cs,'CustomLAPACKCallback', '');   % Custom LAPACK library callback
set_param(cs,'CustomFFTCallback', '');   % Custom FFT library callback
set_param(cs,'CustomDefine', '');   % Defines
set_param(cs,'CustomInitializer', '');   % Initialize function
set_param(cs,'CustomTerminator', '');   % Terminate function
set_param(cs,'CodeExecutionProfiling', 'off');   % Measure task execution time
set_param(cs,'CodeProfilingInstrumentation', 'off');   % Measure function execution times
set_param(cs,'CodeCoverageSettings', coder.coverage.CodeCoverageSettings([],'off','off','None'));   % Third-party tool
set_param(cs,'CreateSILPILBlock', 'None');   % Create block
set_param(cs,'PortableWordSizes', 'off');   % Enable portable word sizes
set_param(cs,'PostCodeGenCommand', '');   % Post code generation command
set_param(cs,'SaveLog', 'off');   % Save build log
set_param(cs,'TLCOptions', '');   % TLC command line options
set_param(cs,'GenerateReport', 'on');   % Create code generation report
set_param(cs,'LaunchReport', 'off');   % Open report automatically
set_param(cs,'IncludeHyperlinkInReport', 'on');   % Code-to-model
set_param(cs,'GenerateTraceInfo', 'on');   % Model-to-code
set_param(cs,'GenerateWebview', 'off');   % Generate model Web view
set_param(cs,'GenerateTraceReport', 'on');   % Eliminated / virtual blocks
set_param(cs,'GenerateTraceReportSl', 'on');   % Traceable Simulink blocks
set_param(cs,'GenerateTraceReportSf', 'on');   % Traceable Stateflow objects
set_param(cs,'GenerateTraceReportEml', 'on');   % Traceable MATLAB functions
set_param(cs,'GenerateCodeMetricsReport', 'off');   % Static code metrics
set_param(cs,'GenerateCodeReplacementReport', 'off');   % Summarize which blocks triggered code replacements
set_param(cs,'GenerateComments', 'on');   % Include comments
set_param(cs,'SimulinkBlockComments', 'on');   % Simulink block comments
set_param(cs,'StateflowObjectComments', 'on');   % Stateflow object comments
set_param(cs,'MATLABSourceComments', 'off');   % MATLAB source code as comments
set_param(cs,'ShowEliminatedStatement', 'on');   % Show eliminated blocks
set_param(cs,'ForceParamTrailComments', 'on');   % Verbose comments for SimulinkGlobal storage class
set_param(cs,'OperatorAnnotations', 'on');   % Operator annotations
set_param(cs,'InsertBlockDesc', 'on');   % Simulink block descriptions
set_param(cs,'SFDataObjDesc', 'on');   % Stateflow object descriptions
set_param(cs,'SimulinkDataObjDesc', 'on');   % Simulink data object descriptions
set_param(cs,'ReqsInCode', 'off');   % Requirements in block comments
set_param(cs,'EnableCustomComments', 'off');   % Custom comments (MPT objects only)
set_param(cs,'MATLABFcnDesc', 'off');   % MATLAB user comments
set_param(cs,'CustomSymbolStrGlobalVar', '$R$N$M');   % Global variables
set_param(cs,'CustomSymbolStrType', '$N$R$M_T');   % Global types
set_param(cs,'CustomSymbolStrField', '$N$M');   % Field name of global types
set_param(cs,'CustomSymbolStrFcn', '$R$N$M$F');   % Subsystem methods
set_param(cs,'CustomSymbolStrFcnArg', 'rt$I$N$M');   % Subsystem method arguments
set_param(cs,'CustomSymbolStrTmpVar', '$N$M');   % Local temporary variables
set_param(cs,'CustomSymbolStrBlkIO', 'rtb_$N$M');   % Local block output variables
set_param(cs,'CustomSymbolStrMacro', '$R$N$M');   % Constant macros
set_param(cs,'CustomSymbolStrUtil', '$N$C');   % Shared utilities
set_param(cs,'CustomSymbolStrEmxType', 'emxArray_$M$N');   % EMX array types identifier format
set_param(cs,'CustomSymbolStrEmxFcn', 'emx$M$N');   % EMX array utility functions identifier format
set_param(cs,'MangleLength', 1);   % Minimum mangle length
set_param(cs,'SharedChecksumLength', 8);   % Shared checksum length
set_param(cs,'MaxIdLength', 31);   % Maximum identifier length
set_param(cs,'InternalIdentifier', 'Shortened');   % System-generated identifiers
set_param(cs,'InlinedPrmAccess', 'Literals');   % Generate scalar inlined parameters as
set_param(cs,'SignalNamingRule', 'None');   % Signal naming
set_param(cs,'ParamNamingRule', 'None');   % Parameter naming
set_param(cs,'DefineNamingRule', 'None');   % #define naming
set_param(cs,'UseSimReservedNames', 'off');   % Use the same reserved names as Simulation Target
set_param(cs,'ReservedNameArray', []);   % Reserved names
set_param(cs,'IgnoreCustomStorageClasses', 'off');   % Ignore custom storage classes
set_param(cs,'IgnoreTestpoints', 'off');   % Ignore test point signals
set_param(cs,'CommentStyle', 'Auto');   % Comment style
set_param(cs,'InsertPolySpaceComments', 'off');   % Insert Polyspace comments
set_param(cs,'CustomUserTokenString', '');   % Custom token text
set_param(cs,'TargetLangStandard', 'C99 (ISO)');   % Standard math library
set_param(cs,'CodeReplacementLibrary', 'None');   % Code replacement library
set_param(cs,'UtilityFuncGeneration', 'Shared location');   % Shared code placement
set_param(cs,'CodeInterfacePackaging', 'Nonreusable function');   % Code interface packaging
set_param(cs,'GRTInterface', 'off');   % Classic call interface
set_param(cs,'PurelyIntegerCode', 'off');   % Support floating-point numbers
set_param(cs,'SupportNonFinite', 'off');   % Support non-finite numbers
set_param(cs,'SupportComplex', 'on');   % Support complex numbers
set_param(cs,'SupportAbsoluteTime', 'on');   % Support absolute time
set_param(cs,'SupportContinuousTime', 'off');   % Support continuous time
set_param(cs,'SupportNonInlinedSFcns', 'off');   % Support non-inlined S-functions
set_param(cs,'SupportVariableSizeSignals', 'on');   % Support variable-size signals
set_param(cs,'MultiwordTypeDef', 'System defined');   % Multiword type definitions
set_param(cs,'CombineOutputUpdateFcns', 'on');   % Single output/update function
set_param(cs,'IncludeMdlTerminateFcn', 'on');   % Terminate function required
set_param(cs,'MatFileLogging', 'off');   % MAT-file logging
set_param(cs,'SuppressErrorStatus', 'off');   % Remove error status field in real-time model data structure
set_param(cs,'CombineSignalStateStructs', 'off');   % Combine signal/state structures
set_param(cs,'ParenthesesLevel', 'Maximum');   % Parentheses level
set_param(cs,'CastingMode', 'Standards');   % Casting modes
set_param(cs,'GenerateSampleERTMain', 'off');   % Generate an example main program
set_param(cs,'IncludeFileDelimiter', 'Auto');   % #include file delimiter
set_param(cs,'ERTCustomFileBanners', 'on');   % Enable custom file banner
set_param(cs,'GenerateFullHeader', 'on');   % Generate full file banner
set_param(cs,'InferredTypesCompatibility', 'off');   % Create preprocessor directive in rtwtypes.h
set_param(cs,'GenerateSharedConstants', 'on');   % Generate shared constants
set_param(cs,'TargetLibSuffix', '');   % Suffix applied to target library name
set_param(cs,'TargetPreCompLibLocation', '');   % Precompiled library location
set_param(cs,'RemoveDisableFunc', 'off');   % Remove disable function
set_param(cs,'LUTObjectStructOrderExplicitValues', 'Size,Breakpoints,Table');   % LUT object struct order for explicit value specification
set_param(cs,'LUTObjectStructOrderEvenSpacing', 'Size,Breakpoints,Table');   % LUT object struct order for even spacing specification
set_param(cs,'MemSecPackage', '--- None ---');   % Memory sections package for model data and functions
set_param(cs,'MemSecFuncSharedUtil', 'Default');   % Memory section for shared utility functions
set_param(cs,'MemSecFuncInitTerm', 'Default');   % Memory section for initialize/terminate functions
set_param(cs,'MemSecFuncExecute', 'Default');   % Memory section for execution functions
set_param(cs,'MemSecDataParameters', 'Default');   % Memory section for parameters
set_param(cs,'MemSecDataInternal', 'Default');   % Memory section for internal data
set_param(cs,'MemSecDataIO', 'Default');   % Memory section for inputs/outputs
set_param(cs,'MemSecDataConstants', 'Default');   % Memory section for constants
set_param(cs,'GlobalDataDefinition', 'InSeparateSourceFile');   % Data definition
set_param(cs,'GlobalDataReference', 'Auto');   % Data declaration
set_param(cs,'ExtMode', 'off');   % External mode
set_param(cs,'ERTFilePackagingFormat', 'Modular');   % File packaging format
set_param(cs,'EnableUserReplacementTypes', 'off');   % Replace data type names in the generated code
set_param(cs,'ConvertIfToSwitch', 'on');   % Convert if-elseif-else patterns to switch-case statements
set_param(cs,'DataDefinitionFile', 'UDAN_SOCCalibdata.c');   % Data definition filename
set_param(cs,'ERTCustomFileTemplate', 'example_file_process.tlc');   % File customization template
set_param(cs,'ERTDataHdrFileTemplate', 'ert_code_template.cgt');   % Header file template
set_param(cs,'ERTDataSrcFileTemplate', 'ert_code_template.cgt');   % Source file template
set_param(cs,'ERTHdrFileBannerTemplate', 'ert_code_template.cgt');   % Header file template
set_param(cs,'ERTSrcFileBannerTemplate', 'ert_code_template.cgt');   % Source file template
set_param(cs,'EnableDataOwnership', 'off');   % Use owner from data object for data definition placement
set_param(cs,'GenerateASAP2', 'off');   % ASAP2 interface
set_param(cs,'IndentSize', '2');   % Indent size
set_param(cs,'IndentStyle', 'K&R');   % Indent style
set_param(cs,'InlinedParameterPlacement', 'NonHierarchical');   % Parameter structure
set_param(cs,'ParamTuneLevel', 10);   % Parameter tune level
set_param(cs,'EnableSignedLeftShifts', 'off');   % Replace multiplications by powers of two with signed bitwise shifts
set_param(cs,'EnableSignedRightShifts', 'off');   % Allow right shifts on signed integers
set_param(cs,'PreserveExpressionOrder', 'off');   % Preserve operand order in expression
set_param(cs,'PreserveExternInFcnDecls', 'on');   % Preserve extern keyword in function declarations
set_param(cs,'PreserveIfCondition', 'off');   % Preserve condition expression in if statement
set_param(cs,'RTWCAPIParams', 'off');   % Generate C API for parameters
set_param(cs,'RTWCAPIRootIO', 'off');   % Generate C API for root-level I/O
set_param(cs,'RTWCAPISignals', 'off');   % Generate C API for signals
set_param(cs,'RTWCAPIStates', 'off');   % Generate C API for states
set_param(cs,'SignalDisplayLevel', 10);   % Signal display level
set_param(cs,'SuppressUnreachableDefaultCases', 'on');   % Suppress generation of default cases for Stateflow switch statements if unreachable
set_param(cs,'BooleanTrueId', 'true');   % Boolean true identifier
set_param(cs,'BooleanFalseId', 'false');   % Boolean false identifier
set_param(cs,'MaxIdInt32', 'MAX_int32_T');   % 32-bit integer maximum identifier
set_param(cs,'MinIdInt32', 'MIN_int32_T');   % 32-bit integer minimum identifier
set_param(cs,'MaxIdUint32', 'MAX_uint32_T');   % 32-bit unsigned integer maximum identifier
set_param(cs,'MaxIdInt16', 'MAX_int16_T');   % 16-bit integer maximum identifier
set_param(cs,'MinIdInt16', 'MIN_int16_T');   % 16-bit integer minimum identifier
set_param(cs,'MaxIdUint16', 'MAX_uint16_T');   % 16-bit unsigned integer maximum identifier
set_param(cs,'MaxIdInt8', 'MAX_int8_T');   % 8-bit integer maximum identifier
set_param(cs,'MinIdInt8', 'MIN_int8_T');   % 8-bit integer minimum identifier
set_param(cs,'MaxIdUint8', 'MAX_uint8_T');   % 8-bit unsigned integer maximum identifier
set_param(cs,'TypeLimitIdReplacementHeaderFile', '');   % Type limit identifier replacement header file

% Simulink Coverage
set_param(cs,'CovModelRefEnable', 'off');   % Record coverage for referenced models
set_param(cs,'RecordCoverage', 'off');   % Record coverage for this model
set_param(cs,'CovEnable', 'off');   % Enable coverage analysis

% HDL Coder
try 
	cs_componentCC = hdlcoderui.hdlcc;
	cs_componentCC.createCLI();
	cs.attachComponent(cs_componentCC);
catch ME
	warning('Simulink:ConfigSet:AttachComponentError', ME.message);
end

% Design Verifier
try
  cs_componentCC = Sldv.ConfigComp;
  cs.attachComponent(cs_componentCC);
  set_param(cs,'DVMode', 'TestGeneration');   % Mode
  set_param(cs,'DVMaxProcessTime', 30000);   % Maximum analysis time (s)
  set_param(cs,'DVDisplayUnsatisfiableObjectives', 'off');   % Display unsatisfiable test objectives
  set_param(cs,'DVAutomaticStubbing', 'on');   % Automatic stubbing of unsupported blocks and functions
  set_param(cs,'DVDesignMinMaxConstraints', 'on');   % Use specified input minimum and maximum values
  set_param(cs,'DVOutputDir', 'sldv_output/$ModelName$');   % Output folder
  set_param(cs,'DVMakeOutputFilesUnique', 'on');   % Make output file names unique by adding a suffix
  set_param(cs,'DVBlockReplacement', 'off');   % Apply block replacements
  set_param(cs,'DVParameters', 'off');   % Enable parameter configuration
  set_param(cs,'DVModelCoverageObjectives', 'ConditionDecision');   % Model coverage objectives
  set_param(cs,'DVTestConditions', 'UseLocalSettings');   % Test conditions
  set_param(cs,'DVTestObjectives', 'UseLocalSettings');   % Test objectives
  set_param(cs,'DVMaxTestCaseSteps', 10000);   % Maximum test case steps
  set_param(cs,'DVTestSuiteOptimization', 'CombinedObjectives (Nonlinear Extended)');   % Test suite optimization
  set_param(cs,'DVExtendExistingTests', 'off');   % Extend existing test cases
  set_param(cs,'DVIgnoreCovSatisfied', 'off');   % Ignore objectives satisfied in existing coverage data
  set_param(cs,'DVCovFilter', 'off');   % Ignore objective based on filter
  set_param(cs,'DVIncludeRelationalBoundary', 'off');   % Include relational boundary objectives
  set_param(cs,'DVDetectDeadLogic', 'off');   % Dead logic
  set_param(cs,'DVDetectIntegerOverflow', 'on');   % Integer overflow
  set_param(cs,'DVDetectDivisionByZero', 'on');   % Division by zero
  set_param(cs,'DVDesignMinMaxCheck', 'off');   % Check specified intermediate minimum and maximum values
  set_param(cs,'DVDetectOutOfBounds', 'off');   % Out of bound array access
  set_param(cs,'DVAssertions', 'UseLocalSettings');   % Assertion blocks
  set_param(cs,'DVProofAssumptions', 'UseLocalSettings');   % Proof assumptions
  set_param(cs,'DVProvingStrategy', 'Prove');   % Strategy
  set_param(cs,'DVSaveDataFile', 'on');   % Save test data to file
  set_param(cs,'DVDataFileName', '$ModelName$_sldvdata');   % Data file name
  set_param(cs,'DVSaveExpectedOutput', 'off');   % Include expected output values
  set_param(cs,'DVRandomizeNoEffectData', 'off');   % Randomize data that do not affect the outcome
  set_param(cs,'DVSaveHarnessModel', 'off');   % Generate separate harness model after analysis
  set_param(cs,'DVSlTestFileName', '$ModelName$_test');   % Test File name
  set_param(cs,'DVSlTestHarnessName', '$ModelName$_sldvharness');   % Test Harness name
  set_param(cs,'DVSaveReport', 'on');   % Generate report of the results
  set_param(cs,'DVReportPDFFormat', 'off');   % Generate additional report in PDF format
  set_param(cs,'DVReportFileName', '$ModelName$_report');   % Report file name
  set_param(cs,'DVReportIncludeGraphics', 'off');   % Include screen shots of properties
  set_param(cs,'DVDisplayReport', 'on');   % Display report
  set_param(cs,'DVSFcnSupport', 'on');   % Support S-Functions in the analysis
  set_param(cs,'DVSFcnExtraOptions', '');   % Additional options for S-Functions
catch ME
  warning('Simulink:ConfigSet:AttachComponentError', ME.message);
end

% Simscape
try
  cs_componentCC = SSC.SimscapeCC;
  cs.attachComponent(cs_componentCC);
  set_param(cs,'WarnOnRedundantConstraints', 'on');   % Warn if machine contains redundant constraints
  set_param(cs,'WarnOnSingularInitialAssembly', 'off');   % Warn if number of initial constraints is unstable
  set_param(cs,'ShowCutJoints', 'off');   % Mark automatically cut joints
  set_param(cs,'VisOnUpdateDiagram', 'off');   % Display machines after updating diagram
  set_param(cs,'VisDuringSimulation', 'off');   % Show animation during simulation
  set_param(cs,'ShowOnlyPortCS', 'off');   % Show only port coordinate systems
  set_param(cs,'DefaultBodyColor', '[1 0 0]');   % Default body color (RGB)
  set_param(cs,'MDLBodyVisualizationType', 'Convex hull from body CS locations');   % Default body geometries
  set_param(cs,'EditingMode', 'Full');   % Editing Mode
  set_param(cs,'ExplicitSolverDiagnosticOptions', 'warning');   % Explicit solver used in model containing Physical Networks blocks
  set_param(cs,'GlobalZcOffDiagnosticOptions', 'warning');   % Zero-crossing control is globally disabled in Simulink
  set_param(cs,'SimscapeNormalizeSystem', 'on');   % Normalize using nominal values
  set_param(cs,'SimscapeNominalValues', '[{"value":"1","unit":"A"},{"value":"1","unit":"bar"},{"value":"1","unit":"cm^2"},{"value":"1","unit":"cm^3/s"},{"value":"1","unit":"kJ/kg"},{"value":"1","unit":"kW"},{"value":"1","unit":"l"},{"value":"1","unit":"N"},{"value":"1","unit":"N*m"},{"value":"1","unit":"V"}]');   % Specify nominal values...
  set_param(cs,'SimscapeLogType', 'none');   % Log simulation data
  set_param(cs,'SimscapeUseOperatingPoints', 'off');   % Enable operating point initialization
  set_param(cs,'SimMechanicsInvalidVisualProperty', 'warning');   % Invalid visual properties
  set_param(cs,'SimMechanicsCrossSectionNullEdge', 'warning');   % Repeated vertices in a cross-section
  set_param(cs,'SimMechanicsUnconnectedFramePorts', 'warning');   % Unconnected frame port
  set_param(cs,'SimMechanicsUnconnectedGeometryPorts', 'warning');   % Unconnected geometry port
  set_param(cs,'SimMechanicsRedundantBlock', 'warning');   % Redundant block
  set_param(cs,'SimMechanicsConflictingReferenceFrames', 'warning');   % Conflicting reference frames
  set_param(cs,'SimMechanicsRigidlyBoundBlock', 'error');   % Rigidly constrained block
  set_param(cs,'SimMechanicsUnsatisfiedHighPriorityTargets', 'warning');   % Unsatisfied high priority state targets
  set_param(cs,'SimMechanicsJointTargetOverSpecification', 'error');   % Overspecified targets in kinematic loops
  set_param(cs,'SimMechanicsOpenEditorOnUpdate', 'on');   % Open Mechanics Explorer on model update or simulation
catch ME
  warning('Simulink:ConfigSet:AttachComponentError', ME.message);
end