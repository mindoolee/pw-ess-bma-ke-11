Attribute VB_Name = "AXHD"

' { IP COMMAND LIST }
' PGM-1 Group Register
Public Const IPxyRANGERead = &H0                            ' PGM-1 RANGE READ 16bit = &HFFFF
Public Const IPxyRANGEWrite = &H80                          ' PGM-1 RANGE WRITE
Public Const IPxySTDRead = &H1                              ' PGM-1 START/STOP SPEED DATA READ 16bit
Public Const IPxySTDWrite = &H81                            ' PGM-1 START/STOP SPEED DATA WRITE
Public Const IPxyOBJRead = &H2                              ' PGM-1 OBJECT SPEED DATA READ 16bit
Public Const IPxyOBJWrite = &H82                            ' PGM-1 OBJECT SPEED DATA WRITE
Public Const IPxyRATE1Read = &H3                            ' PGM-1 RATE-1 DATA READ 16bit = &HFFFF
Public Const IPxyRATE1Write = &H83                          ' PGM-1 RATE-1 DATA WRITE
Public Const IPxyRATE2Read = &H4                            ' PGM-1 RATE-2 DATA READ 16bit = &HFFFF
Public Const IPxyRATE2Write = &H84                          ' PGM-1 RATE-2 DATA WRITE
Public Const IPxyRATE3Read = &H5                            ' PGM-1 RATE-3 DATA READ 16bit = &HFFFF
Public Const IPxyRATE3Write = &H85                          ' PGM-1 RATE-3 DATA WRITE
Public Const IPxyRCP12Read = &H6                            ' PGM-1 RATE CHANGE POINT 1-2 READ 16bit = &HFFFF
Public Const IPxyRCP12Write = &H86                          ' PGM-1 RATE CHANGE POINT 1-2 WRITE
Public Const IPxyRCP23Read = &H7                            ' PGM-1 RATE CHANGE POINT 2-3 READ 16bit = &HFFFF
Public Const IPxyRCP23Write = &H87                          ' PGM-1 RATE CHANGE POINT 2-3 WRITE
Public Const IPxySW1Read = &H8                              ' PGM-1 SW-1 DATA READ 15bit = &H7FFF
Public Const IPxySW1Write = &H88                            ' PGM-1 SW-1 DATA WRITE
Public Const IPxySW2Read = &H9                              ' PGM-1 SW-2 DATA READ 15bit = &H7FFF
Public Const IPxySW2Write = &H89                            ' PGM-1 SW-2 DATA WRITE
Public Const IPxyPWMRead = &HA                              ' PGM-1 PWM 출력 설정 DATA READ(0~6) 3bit = &H00
Public Const IPxyPWMWrite = &H8A                            ' PGM-1 PWM 출력 설정 DATA WRITE
Public Const IPxyREARRead = &HB                             ' PGM-1 SLOW DOWN/REAR PULSE READ 32bit = &H00000000
Public Const IPxyREARWrite = &H8B                           ' PGM-1 SLOW DOWN/REAR PULSE WRITE
Public Const IPxySPDRead = &HC                              ' PGM-1 현재 SPEED DATA READ 16bit = &H0000
Public Const IPxyNoOperation_8C = &H8C                      ' No operation
Public Const IPxySPDCMPRead = &HD                           ' PGM-1 현재 SPEED 비교 DATA READ 16bit = &H0000
Public Const IPxySPDCMPWrite = &H8D                         ' PGM-1 현재 SPEED 비교 DATA WRITE
Public Const IPxyDRVPULSERead = &HE                         ' PGM-1 DRIVE PULSE COUNTER READ 32bit = &H00000000
Public Const IPxyNoOperation_8E = &H8E                      ' No operation
Public Const IPxyPRESETPULSERead = &HF                      ' PGM-1 PRESET PULSE DATA READ 32bit = &H00000000
Public Const IPxyNoOperation_8F = &H8F                      ' No operation
' PGM-1 Update Group Register
Public Const IPxyURANGERead = &H10                          ' PGM-1 UP-DATE RANGE READ 16bit = &HFFFF
Public Const IPxyURANGEWrite = &H90                         ' PGM-1 UP-DATE RANGE WRITE
Public Const IPxyUSTDRead = &H11                            ' PGM-1 UP-DATE START/STOP SPEED DATA READ 16bit
Public Const IPxyUSTDWrite = &H91                           ' PGM-1 UP-DATE START/STOP SPEED DATA WRITE
Public Const IPxyUOBJRead = &H12                            ' PGM-1 UP-DATE OBJECT SPEED DATA READ 16bit
Public Const IPxyUOBJWrite = &H92                           ' PGM-1 UP-DATE OBJECT SPEED DATA WRITE
Public Const IPxyURATE1Read = &H13                          ' PGM-1 UP-DATE RATE-1 DATA READ 16bit = &HFFFF
Public Const IPxyURATE1Write = &H93                         ' PGM-1 UP-DATE RATE-1 DATA WRITE
Public Const IPxyURATE2Read = &H14                          ' PGM-1 UP-DATE RATE-2 DATA READ 16bit = &HFFFF
Public Const IPxyURATE2Write = &H94                         ' PGM-1 UP-DATE RATE-2 DATA WRITE
Public Const IPxyURATE3Read = &H15                          ' PGM-1 UP-DATE RATE-3 DATA READ 16bit = &HFFFF
Public Const IPxyURATE3Write = &H95                         ' PGM-1 UP-DATE RATE-3 DATA WRITE
Public Const IPxyURCP12Read = &H16                          ' PGM-1 UP-DATE RATE CHANGE POINT 1-2 READ 16bit = &HFFFF
Public Const IPxyURCP12Write = &H96                         ' PGM-1 UP-DATE RATE CHANGE POINT 1-2 WRITE
Public Const IPxyURCP23Read = &H17                          ' PGM-1 UP-DATE RATE CHANGE POINT 2-3 READ 16bit = &HFFFF
Public Const IPxyURCP23Write = &H97                         ' PGM-1 UP-DATE RATE CHANGE POINT 2-3 WRITE
Public Const IPxyUSW1Read = &H18                            ' PGM-1 UP-DATE SW-1 DATA READ 15bit = &H7FFF
Public Const IPxyUSW1Write = &H98                           ' PGM-1 UP-DATE SW-1 DATA WRITE
Public Const IPxyUSW2Read = &H19                            ' PGM-1 UP-DATE SW-2 DATA READ 15bit = &H7FFF
Public Const IPxyUSW2Write = &H99                           ' PGM-1 UP-DATE SW-2 DATA WRITE
Public Const IPxyNoOperation_1A = &H1A                      ' No operation
Public Const IPxyNoOperation_9A = &H9A                      ' No operation
Public Const IPxyUREARRead = &H1B                           ' PGM-1 UP-DATE SLOW DOWN/REAR PULSE READ 32bit = &H00000000
Public Const IPxyUREARWrite = &H9B                          ' PGM-1 UP-DATE SLOW DOWN/REAR PULSE WRITE
Public Const IPxySPDRead_1C = &H1C                          ' PGM-1 UP-DATA CURRENT SPEED READ(Same with = &H0C)
Public Const IPxyNoOperation_9C = &H9C                      ' No operation
Public Const IPxySPDCMPRead_1D = &H1D                       ' PGM-1 현재 SPEED 비교 DATA READ(Same with = &H0D)
Public Const IPxySPDCMPWrite_9D = &H9D                      ' PGM-1 현재 SPEED 비교 DATA WRITE(Same with = &H8D)
Public Const IPxyACCPULSERead = &H1E                        ' PGM-1 가속 PULSE COUNTER READ 32bit = &H00000000
Public Const IPxyNoOperation_9E = &H9E                      ' No operation
Public Const IPxyPRESETPULSERead_1F = &H1F                  ' PGM-1 PRESET PULSE DATA READ(Same with = &H0F)
Public Const IPxyNoOperation_9F = &H9F                      ' No operation
' PGM-2 Group Register
Public Const IPxyNoOperation_20 = &H20                      ' No operation
Public Const IPxyPPRESETDRV = &HA0                          ' +PRESET PULSE DRIVE 32
Public Const IPxyNoOperation_21 = &H21                      ' No operation
Public Const IPxyPCONTDRV = &HA1                            ' +CONTINUOUS DRIVE
Public Const IPxyNoOperation_22 = &H22                      ' No operation
Public Const IPxyPSCH1DRV = &HA2                            ' +SIGNAL SEARCH-1 DRIVE
Public Const IPxyNoOperation_23 = &H23                      ' No operation
Public Const IPxyPSCH2DRV = &HA3                            ' +SIGNAL SEARCH-2 DRIVE
Public Const IPxyNoOperation_24 = &H24                      ' No operation
Public Const IPxyPORGDRV = &HA4                             ' +ORIGIN(원점) SEARCH DRIVE
Public Const IPxyNoOperation_25 = &H25                      ' No operation
Public Const IPxyMPRESETDRV = &HA5                          ' -PRESET PULSE DRIVE 32
Public Const IPxyNoOperation_26 = &H26                      ' No operation
Public Const IPxyMCONTDRV = &HA6                            ' -CONTINUOUS DRIVE
Public Const IPxyNoOperation_27 = &H27                      ' No operation
Public Const IPxyMSCH1DRV = &HA7                            ' -SIGNAL SEARCH-1 DRIVE
Public Const IPxyNoOperation_28 = &H28                      ' No operation
Public Const IPxyMSCH2DRV = &HA8                            ' -SIGNAL SEARCH-2 DRIVE
Public Const IPxyNoOperation_29 = &H29                      ' No operation
Public Const IPxyMORGDRV = &HA9                             ' -ORIGIN(원점) SEARCH DRIVE
Public Const IPxyPULSEOVERRead = &H2A                       ' Preset/MPG drive override pulse data read
Public Const IPxyPULSEOVERWrite = &HAA                      ' PRESET PULSE DATA OVERRIDE(ON_BUSY)
Public Const IPxyNoOperation_2B = &H2B                      ' No operation
Public Const IPxySSTOPCMD = &HAB                            ' SLOW DOWN STOP
Public Const IPxyNoOperation_2C = &H2C                      ' No operation
Public Const IPxyESTOPCMD = &HAC                            ' EMERGENCY STOP
Public Const IPxyDRIVEMODERead = &H2D                       ' 드라이브 동작 설정 DATA READ
Public Const IPxyDRIVEMODEWrite = &HAD                      ' 드라이브 동작 설정 DATA WRITE
Public Const IPxyMPGCONRead = &H2E                          ' MPG OPERATION SETTING DATA READ 3bit = &H00
Public Const IPxyMPGCONWrite = &HAE                         ' MPG OPERATION SETTING DATA WRITE
Public Const IPxyPULSEMPGRead = &H2F                        ' MPG PRESET PULSE DATA READ 32bit = &H00000000
Public Const IPxyPULSEMPGWrite = &HAF                       ' MPG PRESET PULSE DATA WRITE
' Extension Group Register
Public Const IPxyNoOperation_30 = &H30                      ' No operation
Public Const IPxyPSPO1DRV = &HB0                            ' +SENSOR POSITIONING DRIVE I
Public Const IPxyNoOperation_31 = &H31                      ' No operation
Public Const IPxyMSPO1DRV = &HB1                            ' -SENSOR POSITIONING DRIVE I
Public Const IPxyNoOperation_32 = &H32                      ' No operation
Public Const IPxyPSPO2DRV = &HB2                            ' +SENSOR POSITIONING DRIVE II
Public Const IPxyNoOperation_33 = &H33                      ' No operation
Public Const IPxyMSPO2DRV = &HB3                            ' -SENSOR POSITIONING DRIVE II
Public Const IPxyNoOperation_34 = &H34                      ' No operation
Public Const IPxyPSPO3DRV = &HB4                            ' +SENSOR POSITIONING DRIVE III
Public Const IPxyNoOperation_35 = &H35                      ' No operation
Public Const IPxyMSPO3DRV = &HB5                            ' -SENSOR POSITIONING DRIVE III
Public Const IPxySWLMTCONRead = &H36                        ' SOFT LIMIT 설정 READ 3bit = &H00
Public Const IPxySWLMTCONWrite = &HB6                       ' SOFT LIMIT 설정 WRITE
Public Const IPxyMSWLMTCOMPRead = &H37                      ' -SOFT LIMIT 비교 레지스터 설정 READ 32bit = &H80000000
Public Const IPxyMSWLMTCOMPWrite = &HB7                     ' -SOFT LIMIT 비교 레지스터 설정 WRITE
Public Const IPxyPSWLMTCOMPRead = &H38                      ' +SOFT LIMIT 비교 레지스터 설정 READ 32bit = &H7FFFFFFF
Public Const IPxyPSWLMTCOMPWrite = &HB8                     ' +SOFT LIMIT 비교 레지스터 설정 WRITE
Public Const IPxyTRGCONRead = &H39                          ' TRIGGER MODE 설정 READ 32bit = &H00010000
Public Const IPxyTRGCONWrite = &HB9                         ' TRIGGER MODE 설정 WRITE
Public Const IPxyTRGCOMPRead = &H3A                         ' TRIGGER 비교 데이터 설정 READ 32bit = &H00000000
Public Const IPxyTRGCOMPWrite = &HBA                        ' TRIGGER 비교 데이터 설정 WRITE
Public Const IPxyICMRead = &H3B                             ' INTERNAL M-DATA 설정 READ 32bit = &H80000000
Public Const IPxyICMWrite = &HBB                            ' INTERNAL M-DATA 설정 WRITE
Public Const IPxyECMRead = &H3C                             ' EXTERNAL M-DATA 설정 READ 32bit = &H80000000
Public Const IPxyECMWrite = &HBC                            ' EXTERNAL M-DATA 설정 WRITE
Public Const IPxySTOPPWRead = &H3D                          ' Stop pulse width Read
Public Const IPxySTOPPWWrite = &HBD                         ' Stop pulse width Write
Public Const IPxyNoOperation_3E = &H3E                      ' No operation
Public Const IPxyNoOperation_BE = &HBE                      ' No operation
Public Const IPxyNoOperation_3F = &H3F                      ' No operation
Public Const IPxyTRGCMD = &HBF                              ' TRIG output signal generation command
' Interpolation Group    Registers
Public Const IPxCIRXCRead = &H40                            ' Circular interpolation X axis center point read
Public Const IPxCIRXCWrite = &HC0                           ' Circular interpolation X axis center point write
Public Const IPxCIRYCRead = &H41                            ' Circular interpolation Y axis center point read
Public Const IPxCIRYCWrite = &HC1                           ' Circular interpolation Y axis center point write
Public Const IPxENDXRead = &H42                             ' Interpolation X axis end point read
Public Const IPxENDXWrite = &HC2                            ' Interpolation X axis end point write
Public Const IPxENDYRead = &H43                             ' Interpolation Y axis end point read
Public Const IPxENDYWrite = &HC3                            ' Interpolation Y axis end point write
Public Const IPxPTXENDRead = &H44                           ' Pattern interpolation X Queue data read
Public Const IPxPTXENDWrite = &HC4                          ' Pattern interpolation X Queue data with queue push
Public Const IPxPTYENDRead = &H45                           ' Pattern interpolation Y Queue data read
Public Const IPxPTYENDWrite = &HC5                          ' Pattern interpolation Y Queue data write
Public Const IPxPTQUEUERead = &H46                          ' Pattern interpolation Queue index read
Public Const IPxNoOperation_C6 = &HC6                       ' No operation
Public Const IPxNoOperation_47 = &H47                       ' No operation
Public Const IPxNoOperation_C7 = &HC7                       ' No operation
Public Const IPxNoOperation_48 = &H48                       ' No operation
Public Const IPxNoOperation_C8 = &HC8                       ' No operation
Public Const IPxNoOperation_49 = &H49                       ' No operation
Public Const IPxNoOperation_C9 = &HC9                       ' No operation
Public Const IPxINPSTATUSRead = &H4A                        ' Interpolation Status register read
Public Const IPxNoOperation_CA = &HCA                       ' No operation
Public Const IPxINPMODE_4B = &H4B                           ' Interpolation mode in Queue TOP contets
Public Const IPxLINPDRV = &HCB                              ' Linear interpolation with Queue push
Public Const IPxINPMODE_4C = &H4C                           ' Interpolation mode in Queue TOP contets
Public Const IPxCINPDRV = &HCC                              ' Circular interpolation with Queue push
Public Const IPxBPINPMODE = &H4D                            ' Bit Pattern Interpolation mode in Queue TOP contets
Public Const IPxBPINPDRV = &HCD                             ' Bit pattern Drive
Public Const IPxNoOperation_4E = &H4E                       ' No Operation
Public Const IPxNoOperation_CE = &HCE                       ' No Operation
Public Const IPxNoOperation_4F = &H4F                       ' No Operation
Public Const IPxNoOperation_CF = &HCF                       ' No Operation
' Arithemetic Group Register
Public Const IPxNoOperation_50 = &H50                       ' No Operation
Public Const IPxINPCLR = &HD0                               ' Initialize all interpolation control block
Public Const IPxINPMPOINTRead = &H51                        ' Interpolation deceleration manual point(unsigned) read
Public Const IPxINPMPOINTWrite = &HD1                       ' Interpolation deceleration manual point(unsigned) write
Public Const IPxNoOperation_52 = &H52                       ' No Operation
Public Const IPxINPCLRSWrite = &HD2                         ' Initialize interpolation control block with target selection
Public Const IPxNoOperation_53 = &H53                       ' No Operation
Public Const IPxINPDRVWrite = &HD3                          ' linear/circular drive start with queue data(Hold on mode) Restart on pause
Public Const IPxNoOperation_54 = &H54                       ' No operation
Public Const IPxNoOperation_D4 = &HD4                       ' No operation
Public Const IPxNoOperation_55 = &H55                       ' No operation
Public Const IPxARTSHOT = &HD5                              ' Arithmetic block One time execution
Public Const IPxARTSHOPERRead = &H56                        ' Arithmetic block shift and operation selection Read
Public Const IPxARTSHOPERWrite = &HD6                       ' Arithmetic block shift and operation selection Write
Public Const IPxARTSHRead = &H57                            ' Arithmetic block shift amount data Read
Public Const IPxARTSHWrite = &HD7                           ' Arithmetic block shift amount data Write
Public Const IPxARTSOURCERead = &H58                        ' Arithmetic block operand configure data Read
Public Const IPxARTSOURCEWrite = &HD8                       ' Arithmetic block operand configure data Write
Public Const IPxARTCRESULT1Read = &H59                      ' Arithmetic first compare result data Read
Public Const IPxNoOperation_D9 = &HD9                       ' No Operation
Public Const IPxARTCRESULT2Read = &H5A                      ' Arithmetic second compare result data Read
Public Const IPxNoOperation_DA = &HDA                       ' No Operation
Public Const IPxARTARESULT1Read = &H5B                      ' Arithmetic first algebraic result data Read
Public Const IPxNoOperation_DB = &HDB                       ' No Operation
Public Const IPxARTARESULT2Read = &H5C                      ' Arithmetic second algebraic result data Read
Public Const IPxNoOperation_DC = &HDC                       ' No operation
Public Const IPxARTUSERARead = &H5D                         ' Arithmetic block User operand A Read
Public Const IPxARTUSERAWrite = &HDD                        ' Arithmetic block User operand A Write
Public Const IPxARTUSERBRead = &H5E                         ' Arithmetic block User operand B Read
Public Const IPxARTUSERBWrite = &HDE                        ' Arithmetic block User operand B Write
Public Const IPxARTUSERCRead = &H5F                         ' Arithmetic block User operand C Read
Public Const IPxARTUSERCWrite = &HDF                        ' Arithmetic block User operand C Write
' Scripter Group Register
Public Const IPySCRCON1Read = &H40                          ' 스크립트 동작 설정 레지스터-1 READ 32bit = &H00000000
Public Const IPySCRCON1Write = &HC0                         ' 스크립트 동작 설정 레지스터-1 WRITE
Public Const IPySCRCON2Read = &H41                          ' 스크립트 동작 설정 레지스터-2 READ 32bit = &H00000000
Public Const IPySCRCON2Write = &HC1                         ' 스크립트 동작 설정 레지스터-2 WRITE
Public Const IPySCRCON3Read = &H42                          ' 스크립트 동작 설정 레지스터-3 READ 32bit = &H00000000
Public Const IPySCRCON3Write = &HC2                         ' 스크립트 동작 설정 레지스터-3 WRITE
Public Const IPySCRCONQRead = &H43                          ' 스크립트 동작 설정 레지스터-Queue READ 32bit = &H00000000
Public Const IPySCRCONQWrite = &HC3                         ' 스크립트 동작 설정 레지스터-Queue WRITE
Public Const IPySCRDATA1Read = &H44                         ' 스크립트 동작 데이터 레지스터-1 READ 32bit = &H00000000
Public Const IPySCRDATA1Write = &HC4                        ' 스크립트 동작 데이터 레지스터-1 WRITE
Public Const IPySCRDATA2Read = &H45                         ' 스크립트 동작 데이터 레지스터-2 READ 32bit = &H00000000
Public Const IPySCRDATA2Write = &HC5                        ' 스크립트 동작 데이터 레지스터-2 WRITE
Public Const IPySCRDATA3Read = &H46                         ' 스크립트 동작 데이터 레지스터-3 READ 32bit = &H00000000
Public Const IPySCRDATA3Write = &HC6                        ' 스크립트 동작 데이터 레지스터-3 WRITE
Public Const IPySCRDATAQRead = &H47                         ' 스크립트 동작 데이터 레지스터-Queue READ 32bit = &H00000000
Public Const IPySCRDATAQWrite = &HC7                        ' 스크립트 동작 데이터 레지스터-Queue WRITE
Public Const IPyNoOperation_48 = &H48                       ' No operation
Public Const IPySCRQCLR = &HC8                              ' 스크립트 Queue clear
Public Const IPySCRCQSIZERead = &H49                        ' 스크립트 동작 설정 Queue 인덱스 READ 4bit = &H00
Public Const IPyNoOperation_C9 = &HC9                       ' No operation
Public Const IPySCRDQSIZERead = &H4A                        ' 스크립트 동작 데이터 Queue 인덱스 READ 4bit = &H00
Public Const IPyNoOperation_CA = &HCA                       ' No operation
Public Const IPySCRQFLAGRead = &H4B                         ' 스크립트 Queue Full/Empty Flag READ 4bit = &H05
Public Const IPyNoOperation_CB = &HCB                       ' No operation
Public Const IPySCRQSIZECONRead = &H4C                      ' 스크립트 Queue size 설정(0~13) READ 16bit = &HD0D0
Public Const IPySCRQSIZECONWrite = &HCC                     ' 스크립트 Queue size 설정(0~13) WRITE
Public Const IPySCRQSTATUSRead = &H4D                       ' 스크립트 Queue status READ 12bit = &H005
Public Const IPyNoOperation_CD = &HCD                       ' No operation
Public Const IPyNoOperation_4E = &H4E                       ' No operation
Public Const IPyNoOperation_CE = &HCE                       ' No operation
Public Const IPyNoOperation_4F = &H4F                       ' No operation
Public Const IPyNoOperation_CF = &HCF                       ' No operation
' Caption Group Register
Public Const IPyCAPCON1Read = &H50                          ' 갈무리 동작 설정 레지스터-1 READ 32bit = &H00000000
Public Const IPyCAPCON1Write = &HD0                         ' 갈무리 동작 설정 레지스터-1 WRITE
Public Const IPyCAPCON2Read = &H51                          ' 갈무리 동작 설정 레지스터-2 READ 32bit = &H00000000
Public Const IPyCAPCON2Write = &HD1                         ' 갈무리 동작 설정 레지스터-2 WRITE
Public Const IPyCAPCON3Read = &H52                          ' 갈무리 동작 설정 레지스터-3 READ 32bit = &H00000000
Public Const IPyCAPCON3Write = &HD2                         ' 갈무리 동작 설정 레지스터-3 WRITE
Public Const IPyCAPCONQRead = &H53                          ' 갈무리 동작 설정 레지스터-Queue READ 32bit = &H00000000
Public Const IPyCAPCONQWrite = &HD3                         ' 갈무리 동작 설정 레지스터-Queue WRITE
Public Const IPyCAPDATA1Read = &H54                         ' 갈무리 동작 데이터 레지스터-1 READ 32bit = &H00000000
Public Const IPyNoOperation_D4 = &HD4                       ' No operation
Public Const IPyCAPDATA2Read = &H55                         ' 갈무리 동작 데이터 레지스터-2 READ 32bit = &H00000000
Public Const IPyNoOperation_D5 = &HD5                       ' No operation
Public Const IPyCAPDATA3Read = &H56                         ' 갈무리 동작 데이터 레지스터-3 READ 32bit = &H00000000
Public Const IPyNoOperation_D6 = &HD6                       ' No operation
Public Const IPyCAPDATAQRead = &H57                         ' 갈무리 동작 데이터 레지스터-Queue READ 32bit = &H00000000
Public Const IPyNoOperation_D7 = &HD7                       ' No operation
Public Const IPyNoOperation_58 = &H58                       ' No operation
Public Const IPyCAPQCLR = &HD8                              ' 갈무리 Queue clear
Public Const IPyCAPCQSIZERead = &H59                        ' 갈무리 동작 설정 Queue 인덱스 READ 4bit = &H00
Public Const IPyNoOperation_D9 = &HD9                       ' No operation
Public Const IPyCAPDQSIZERead = &H5A                        ' 갈무리 동작 데이터 Queue 인덱스 READ 4bit = &H00
Public Const IPyNoOperation_DA = &HDA                       ' No operation
Public Const IPyCAPQFLAGRead = &H5B                         ' 갈무리 Queue Full/Empty Flag READ 4bit = &H05
Public Const IPyNoOperation_DB = &HDB                       ' No operation
Public Const IPyCAPQSIZECONRead = &H5C                      ' 갈무리 Queue size 설정(0~13) READ 16bit = &HD0D0
Public Const IPyCAPQSIZECONWrite = &HDC                     ' 갈무리 Queue size 설정(0~13) WRITE
Public Const IPyCAPQSTATUSRead = &H5D                       ' 갈무리 Queue status READ 12bit = &H005
Public Const IPyNoOperation_DD = &HDD                       ' No operation
Public Const IPyNoOperation_5E = &H5E                       ' No operation
Public Const IPyNoOperation_DE = &HDE                       ' No operation
Public Const IPyNoOperation_5F = &H5F                       ' No operation
Public Const IPyNoOperation_DF = &HDF                       ' No operation
' BUS - 1 Group Register
Public Const IPxyINCNTRead = &H60                           ' INTERNAL COUNTER DATA READ(Signed) 32bit = &H00000000
Public Const IPxyINCNTWrite = &HE0                          ' INTERNAL COUNTER DATA WRITE(Signed)
Public Const IPxyINCNTCMPRead = &H61                        ' INTERNAL COUNTER COMPARATE DATA READ(Signed) 32bit = &H00000000
Public Const IPxyINCNTCMPWrite = &HE1                       ' INTERNAL COUNTER COMPARATE DATA WRITE(Signed)
Public Const IPxyINCNTSCALERead = &H62                      ' INTERNAL COUNTER PRE-SCALE DATA READ 8bit = &H00
Public Const IPxyINCNTSCALEWrite = &HE2                     ' INTERNAL COUNTER PRE-SCALE DATA WRITE
Public Const IPxyICPRead = &H63                             ' INTERNAL COUNTER P-DATA READ 32bit = &H7FFFFFFF
Public Const IPxyICPWrite = &HE3                            ' INTERNAL COUNTER P-DATA WRITE
Public Const IPxyEXCNTRead = &H64                           ' EXTERNAL COUNTER DATA READ READ(Signed) 32bit = &H00000000
Public Const IPxyEXCNTWrite = &HE4                          ' EXTERNAL COUNTER DATA READ WRITE(Signed)
Public Const IPxyEXCNTCMPRead = &H65                        ' EXTERNAL COUNTER COMPARATE DATA READ(Signed) 32bit = &H00000000
Public Const IPxyEXCNTCMPWrite = &HE5                       ' EXTERNAL COUNTER COMPARATE DATA WRITE(Signed)
Public Const IPxyEXCNTSCALERead = &H66                      ' EXTERNAL COUNTER PRE-SCALE DATA READ 8bit = &H00
Public Const IPxyEXCNTSCALEWrite = &HE6                     ' EXTERNAL COUNTER PRE-SCALE DATA WRITE
Public Const IPxyEXPRead = &H67                             ' EXTERNAL COUNTER P-DATA READ 32bit = &H7FFFFFFF
Public Const IPxyEXPWrite = &HE7                            ' EXTERNAL COUNTER P-DATA WRITE
Public Const IPxyEXSPDRead = &H68                           ' EXTERNAL SPEED DATA READ 32bit = &H00000000
Public Const IPxyNoOperation_E8 = &HE8                      ' No operation
Public Const IPxyEXSPDCMPRead = &H69                        ' EXTERNAL SPEED COMPARATE DATA READ 32bit = &H00000000
Public Const IPxyEXSPDCMPWrite = &HE9                       ' EXTERNAL SPEED COMPARATE DATA WRITE
Public Const IPxyEXFILTERDRead = &H6A                       ' 외부 센서 필터 대역폭 설정 DATA READ 32bit = &H00050005
Public Const IPxyEXFILTERDWrite = &HEA                      ' 외부 센서 필터 대역폭 설정 DATA WRITE
Public Const IPxyOFFREGIONRead = &H6B                       ' OFF-RANGE DATA READ 8bit = &H00
Public Const IPxyOFFREGIONWrite = &HEB                      ' OFF-RANGE DATA WRITE
Public Const IPxyDEVIATIONRead = &H6C                       ' DEVIATION DATA READ 16bit = &H0000
Public Const IPxyNoOperation_EC = &HEC                      ' No operation
Public Const IPxyPGMCHRead = &H6D                           ' PGM REGISTER CHANGE DATA READ
Public Const IPxyPGMCHWrite = &HED                          ' PGM REGISTER CHANGE DATA WRITE
Public Const IPxyCOMPCONRead = &H6E                         ' COMPARE REGISTER INPUT CHANGE DATA READ
Public Const IPxyCOMPCONWrite = &HEE                        ' COMPARE REGISTER INPUT CHANGE DATA WRITE
Public Const IPxyNoOperation_6F = &H6F                      ' No operation
Public Const IPxyNoOperation_EF = &HEF                      ' No operation
' BUS - 2 Group Register
Public Const IPxyFUNCONRead = &H70                          ' 칩 기능 설정 DATA READ
Public Const IPxyFUNCONWrite = &HF0                         ' 칩 기능 설정 DATA WRITE
Public Const IPxyMODE1Read = &H71                           ' MODE1 DATA READ
Public Const IPxyMODE1Write = &HF1                          ' MODE1 DATA WRITE
Public Const IPxyMODE2Read = &H72                           ' MODE2 DATA READ
Public Const IPxyMODE2Write = &HF2                          ' MODE2 DATA WRITE
Public Const IPxyUIODATARead = &H73                         ' UNIVERSAL IN READ
Public Const IPxyUIODATAWrite = &HF3                        ' UNIVERSAL OUT WRITE
Public Const IPxyENDSTATUSRead = &H74                       ' END STATUS DATA READ
Public Const IPxyCLIMCLR = &HF4                             ' Complete limit stop clear command
Public Const IPxyMECHRead = &H75                            ' MECHANICAL SIGNAL DATA READ 13bit
Public Const IPxyNoOperation_F5 = &HF5                      ' No operation
Public Const IPxyDRVSTATUSRead = &H76                       ' DRIVE STATE DATA READ 20bit
Public Const IPxyNoOperation_F6 = &HF6                      ' No operation
Public Const IPxyEXCNTCLRRead = &H77                        ' EXTERNAL COUNTER 설정 DATA READ 9bit = &H00
Public Const IPxyEXCNTCLRWrite = &HF7                       ' EXTERNAL COUNTER 설정 DATA WRITE
Public Const IPxyNoOperation_78 = &H78                      ' No operation
Public Const IPxySWRESET = &HF8                             ' REGISTER CLEAR(INITIALIZATION) Software reset
Public Const IPxyINTFLAG1Read = &H79                        ' Interrupt Flag1 READ 32bit = &H00000000
Public Const IPxyINTFLAG1CLRWrite = &HF9                    ' Interrupt Flag1 Clear data write command.
Public Const IPxyINTMASK1Read = &H7A                        ' Interrupt Mask1 READ 32bit = &H00000001
Public Const IPxyINTMASK1Write = &HFA                       ' Interrupt Mask1 WRITE
Public Const IPxyUIOMODERead = &H7B                         ' UIO MODE DATA READ 12bit = &H01F
Public Const IPxyUIOMODEWrite = &HFB                        ' UIO MODE DATA WRITE
Public Const IPxyINTFLAG2Read = &H7C                        ' Interrupt Flag2 READ 32bit = &H00000000
Public Const IPxyINTFLAG2CLRWrite = &HFC                    ' Interrupt Flag2 Clear data write command.
Public Const IPxyINTMASK2Read = &H7D                        ' Interrupt Mask2 READ 32bit = &H00000001
Public Const IPxyINTMASK2Write = &HFD                       ' Interrupt Mask2 WRITE
Public Const IPxyINTUSERCONRead = &H7E                      ' User interrupt selection control.
Public Const IPxyINTUSERCONWrite = &HFE                     ' User interrupt selection control.
Public Const IPxyNoOperation_7F = &H7F                      ' No operation
Public Const IPxyINTGENCMD = &HFF                           ' Interrupt generation command.

' { QI COMMAND LIST }
' Previous register and etc Registers
Public Const QiPRANGERead = &H0                             ' Previous RANGE READ
Public Const QiPRANGEWrite = &H80                           ' Previous RANGE WRITE
Public Const QiPSTDRead = &H1                               ' Previous START/STOP SPEED DATA READ
Public Const QiPSTDWrite = &H81                             ' Previous START/STOP SPEED DATA WRITE
Public Const QiPOBJRead = &H2                               ' Previous OBJECT SPEED DATA READ
Public Const QiPOBJWrite = &H82                             ' Previous OBJECT SPEED DATA WRITE
Public Const QiPRATE1Read = &H3                             ' Previous RATE-1 DATA READ
Public Const QiPRATE1Write = &H83                           ' Previous RATE-1 DATA WRITE
Public Const QiPRATE2Read = &H4                             ' Previous RATE-2 DATA READ
Public Const QiPRATE2Write = &H84                           ' Previous RATE-2 DATA WRITE
Public Const QiPSW1Read = &H5                               ' Previous SW-1 DATA READ
Public Const QiPSW1Write = &H85                             ' Previous SW-1 DATA WRITE
Public Const QiPSW2Read = &H6                               ' Previous SW-2 DATA READ
Public Const QiPSW2Write = &H86                             ' Previous SW-2 DATA WRITE
Public Const QiPDCFGRead = &H7                              ' Previous Drive configure data READ
Public Const QiPDCFGWrite = &H87                            ' Previous Drive configure data WRITE
Public Const QiPREARRead = &H8                              ' Previous SLOW DOWN/REAR PULSE READ
Public Const QiPREARWrite = &H88                            ' Previous SLOW DOWN/REAR PULSE WRITE
Public Const QiPPOSRead = &H9                               ' Previous Drive pulse amount data/Interpolation end position READ
Public Const QiPPOSWrite = &H89                             ' Previous Drive pulse amount data/Interpolation end position WRITE
Public Const QiPCENTRead = &HA                              ' Previous Circular Int. center/Master axis target position for multiple chip linear int. READ
Public Const QiPCENTWrite = &H8A                            ' Previous Circular Int. center/Master axis target position for multiple chip linear int. WRITE
Public Const QiPISNUMRead = &HB                             ' Previous Interpolation step number READ
Public Const QiPISNUMWrite = &H8B                           ' Previous Interpolation step number WRITE
Public Const QiNoOperation_0C = &HC                         ' No operation
Public Const QiCLRPRE = &H8C                                ' Clear previous driving data Queue.
Public Const QiNoOperation_0D = &HD                         ' No operation
Public Const QiPOPPRE = &H8D                                ' Pop and shift data of previous driving data Queue.
Public Const QiPPORTMARestore = &HE                         ' Restore data ports.
Public Const QiPPORTMABackup = &H8E                         ' Backup data ports.
Public Const QiCURSPDRead = &HF                             ' Current SPEED DATA READ
Public Const QiNoOperation_8F = &H8F                        ' No operation
' Working Registers
Public Const QiRANGERead = &H10                             ' RANGE READ
Public Const QiRANGEWrite = &H90                            ' RANGE WRITE
Public Const QiSTDRead = &H11                               ' START/STOP SPEED DATA READ
Public Const QiSTDWrite = &H91                              ' START/STOP SPEED DATA WRITE
Public Const QiOBJRead = &H12                               ' OBJECT SPEED DATA READ
Public Const QiOBJWrite = &H92                              ' OBJECT SPEED DATA WRITE
Public Const QiRATE1Read = &H13                             ' RATE-1 DATA READ
Public Const QiRATE1Write = &H93                            ' RATE-1 DATA WRITE
Public Const QiRATE2Read = &H14                             ' RATE-2 DATA READ
Public Const QiRATE2Write = &H94                            ' RATE-2 DATA WRITE
Public Const QiSW1Read = &H15                               ' SW-1 DATA READ
Public Const QiSW1Write = &H95                              ' SW-1 DATA WRITE
Public Const QiSW2Read = &H16                               ' SW-2 DATA READ
Public Const QiSW2Write = &H96                              ' SW-2 DATA WRITE
Public Const QiDCFGRead = &H17                              ' Drive configure data READ
Public Const QiDCFGWrite = &H97                             ' Drive configure data WRITE
Public Const QiREARRead = &H18                              ' SLOW DOWN/REAR PULSE READ
Public Const QiREARWrite = &H98                             ' SLOW DOWN/REAR PULSE WRITE
Public Const QiPOSRead = &H19                               ' Drive pulse amount data/Interpolation end position READ
Public Const QiPOSWrite = &H99                              ' Drive pulse amount data/Interpolation end position WRITE
Public Const QiCENTRead = &H1A                              ' Circular Int. center/Master axis target position for multiple chip linear int. READ
Public Const QiCENTWrite = &H9A                             ' Circular Int. center/Master axis target position for multiple chip linear int. WRITE
Public Const QiISNUMRead = &H1B                             ' Interpolation step number READ
Public Const QiISNUMWrite = &H9B                            ' Interpolation step number WRITE
Public Const QiREMAIN = &H1C                                ' Remain pulse data after stopping preset drive function abnormally.
Public Const QiNoOperation_9C = &H9C                        ' No operation
Public Const QiOBJORGRead = &H1F                            ' Original search object speed READ
Public Const QiOBJORGWrite = &H9F                           ' Original search object speed WRITE
' Universal in/out setting
Public Const QiUIOMRead = &H1D                              ' Universal in/out terminal mode READ
Public Const QiUIOMWrite = &H9D                             ' Universal in/out terminal mode WRITE
Public Const QiUIORead = &H1E                               ' Universal in/out terminal mode READ
Public Const QiUIOWrite = &H9E                              ' Universal in/out terminal mode WRIT
' Drive start command
Public Const QiNoOperation_20 = &H20                        ' No operation.
Public Const QiSTRN = &HA0                                  ' Normal profile mode drive start.(STD => OBJ => STD)
Public Const QiNoOperation_21 = &H21                        ' No operation.
Public Const QiSTRO = &HA0                                  ' Start at OBJ profile mode drive start.(OBJ => STD)
Public Const QiNoOperation_22 = &H22                        ' No operation.
Public Const QiSTRCO = &HA0                                 ' Constant speed profile #1 drive start.(OBJ)
Public Const QiNoOperation_23 = &H23                        ' No operation.
Public Const QiSTRCS = &HA0                                 ' Constant speed profile #2 drive start.(STD)
Public Const QiNoOperation_60 = &H5C                        ' No operation.
Public Const QiASTRN = &HDC                                 ' Normal profile mode drive start with DCFG7~0 bit data in DATAPL0 port.(STD => OBJ => STD)
Public Const QiNoOperation_61 = &H5D                        ' No operation.
Public Const QiASTRO = &HDD                                 ' Start at OBJ profile mode drive start with DCFG7~0 bit data in DATAPL0 port.(OBJ => STD)
Public Const QiNoOperation_62 = &H5E                        ' No operation.
Public Const QiASTRCO = &HDE                                ' Constant speed profile #1 drive start with DCFG7~0 bit data in DATAPL0 port.(OBJ)
Public Const QiNoOperation_63 = &H5F                        ' No operation.
Public Const QiASTRCS = &HDF                                ' Constant speed profile #2 drive start with DCFG7~0 bit data in DATAPL0 port.(STD)
' Drive control command
Public Const QiNoOperation_24 = &H24                        ' No operation.
Public Const QiSSTOP = &HA4                                 ' Slow Down stop.
Public Const QiNoOperation_25 = &H25                        ' No operation.
Public Const QiSTOP = &HA5                                  ' Immediately stop.
Public Const QiNoOperation_26 = &H26                        ' No operation.
Public Const QiSQRO1 = &HA6                                 ' Output one shot of the start pulse form SQSTR1 terminal.
Public Const QiNoOperation_27 = &H27                        ' No operation.
Public Const QiSQRO2 = &HA7                                 ' Output one shot of the start pulse form SQSTR2 terminal.
Public Const QiNoOperation_28 = &H28                        ' No operation.
Public Const QiSQRI1 = &HA8                                 ' Execution sync start function same as SQSTR1 input.
Public Const QiNoOperation_29 = &H29                        ' No operation.
Public Const QiSQRI2 = &HA9                                 ' Execution sync start function same as  SQSTR2 input.
Public Const QiNoOperation_2A = &H2A                        ' No operation
Public Const QiSQSTP1 = &HAA                                ' Output one shot of the stop pulse from SQSTP1 terminal.
Public Const QiNoOperation_2B = &H2B                        ' No operation.
Public Const QiSQSTP2 = &HAB                                ' Output one shot of the stop pulse from SQSTP2 terminal.
Public Const QiISCNTRead = &H2C                             ' Interpolation stop counter value READ.
Public Const QiNoOperation_AC = &HAC                        ' No operation.
Public Const QiISACNTRead = &H2D                            ' Interpolation step counter READ for advanced deceleration mode .
Public Const QiNoOperation_AD = &HAD                        ' No operation.
Public Const QiNoOperation_2E = &H2E                        ' No operation.
Public Const QiESTOP = &HAE                                 ' Emergency stop all axis.
Public Const QiNoOperation_2F = &H2F                        ' No operation
Public Const QiSWRESET = &HAF                               ' Software reset(all axis).
'Public Const QiNoOperation_30 = &H30                       ' Driven pulse amount during last driving(Interpolation step counter for path move).
'Public Const QiDRPCNTRead = &HB0                           ' No operation
Public Const QiDRPCNTRead = &H30                            ' No operation
Public Const QiNoOperation_B0 = &HB0                        ' Driven pulse amount during last driving(Interpolation step counter for path move).
Public Const QiNoOperation_31 = &H31                        ' No operation
Public Const QiINTGEN = &HB1                                ' Interrupt generation command.
' Peripheral function setting
Public Const QiNoOperation_33 = &H32                        ' No operation.
Public Const QiTRGQPOP = &HB2                               ' Pop and shift data in trigger position queue.
Public Const QiTRTMCFRead = &H33                            ' Trigger/Timer configure READ.
Public Const QiTRTMCFWrite = &HB3                           ' Trigger/Timer configure WRITE.
Public Const QiSNSMTRead = &H34                             ' Software negative limit position READ.
Public Const QiSNSMTWrite = &HB4                            ' Software negative limit position WRITE.
Public Const QiSPSMTRead = &H35                             ' Software positive limit position READ.
Public Const QiSPSMTWrite = &HB5                            ' Software positive limit position WRITE.
Public Const QiTRGPWRead = &H36                             ' Trigger pulse width READ.
Public Const QiTRGPWWrite = &HB6                            ' Trigger pulse width WRITE.
Public Const QiTRGSPRead = &H37                             ' Trigger function start position READ.
Public Const QiTRGSPWrite = &HB7                            ' Trigger function start position WRITE.
Public Const QiTRGEPRead = &H38                             ' Trigger function end position READ.
Public Const QiTRGEPWrite = &HB8                            ' Trigger function end position WRITE.
Public Const QiPTRGPOSRead = &H39                           ' Trigger position or period queue data READ.
Public Const QiPTRGPOSWrite = &HB9                          ' Push trigger position or period queue.
Public Const QiNoOperation_3A = &H3A                        ' No operation.
Public Const QiCLRTRIG = &HBA                               ' Clear trigger position or period queue.
Public Const QiNoOperation_3B = &H3B                        ' No operation.
Public Const QiTRGGEN = &HBB                                ' Generate one shot trigger pulse.
Public Const QiTMRP1Read = &H3C                             ' Timer #1 period data READ.
Public Const QiTMRP1Write = &HBC                            ' Timer #1 period data WRITE.
Public Const QiTMRP2Read = &H3D                             ' Timer #2 period data READ.
Public Const QiTMRP2Write = &HBD                            ' Timer #2 period data WRITE.
Public Const QiTMR1GENstop = &H3E                           ' Timer #1 stop.
Public Const QiTMR1GENstart = &HBE                          ' Timer #1 start.
Public Const QiTMR2GENstop = &H3F                           ' Timer #2 stop.
Public Const QiTMR2GENstart = &HBF                          ' Timer #2 start.
Public Const QiERCReset = &H60                              ' ERC signal reset.
Public Const QiERCSet = &HE0                                ' ERC signal set.
' Script1/2/3 setting registers
Public Const QiSCRCON1Read = &H40                           ' Script1 control queue register READ.
Public Const QiSCRCON1Write = &HC0                          ' Script1 control queue register WRITE.
Public Const QiSCRCMD1Read = &H41                           ' Script1 command queue register READ.
Public Const QiSCRCMD1Write = &HC1                          ' Script1 command queue register WRITE.
Public Const QiSCRDAT1Read = &H42                           ' Script1 execution data queue register READ.
Public Const QiSCRDAT1Write = &HC2                          ' Script1 execution data queue register WRITE.
Public Const QiCQ1Read = &H43                               ' Script1 captured data queue register(top of depth 15 Queue)READ.
Public Const QiNoOperation_C3 = &HC3                        ' No operation.
Public Const QiSCRCFG1Read = &H44                           ' Script1 flag control register READ.
Public Const QiSCRCFG1Write = &HC4                          ' Script1 flag control register WRITE.
Public Const QiSCRCON2Read = &H45                           ' Script2 control queue register READ.
Public Const QiSCRCON2Write = &HC5                          ' Script2 control queue register WRITE.
Public Const QiSCRCMD2Read = &H46                           ' Script2 command queue register READ.
Public Const QiSCRCMD2Write = &HC6                          ' Script2 command queue register WRITE.
Public Const QiSCRDAT2Read = &H47                           ' Script2 execution data queue register READ.
Public Const QiSCRDAT2Write = &HC7                          ' Script2 execution data queue register WRITE.
Public Const QiCQ2Read = &H48                               ' Script2 captured data queue register(top of depth 15 Queue)READ.
Public Const QiNoOperation_C8 = &HC8                        ' No operation.
Public Const QiSCRCFG2Read = &H49                           ' Script2 flag control register READ.
Public Const QiSCRCFG2Write = &HC9                          ' Script2 flag control register WRITE.
Public Const QiSCRCON3Read = &H4A                           ' Script3 control register READ.
Public Const QiSCRCON3Write = &HCA                          ' Script3 control register WRITE.
Public Const QiSCRCMD3Read = &H4B                           ' Script3 command register READ.
Public Const QiSCRCMD3Write = &HCB                          ' Script3 command register WRITE.
Public Const QiSCRDAT3Read = &H4C                           ' Script3 execution data register READ.
Public Const QiSCRDAT3Write = &HCC                          ' Script3 execution data register WRITE.
Public Const QiCQ3Read = &H4D                               ' Script3 captured data register READ.
Public Const QiNoOperation_CD = &HCD                        ' No operation.
Public Const QiNoOperation_4E = &H4E                        ' No operation.
Public Const QiNoOperation_CE = &HCE                        ' No operation.
Public Const QiNoOperation_4F = &H4F                        ' No operation.
Public Const QiNoOperation_CF = &HCF                        ' [No operation code for script reservation command].
' Script4 and Script status setting registers
Public Const QiSCRCON4Read = &H50                           ' Script4 control register READ.
Public Const QiSCRCON4Write = &HD0                          ' Script4 control register WRITE.
Public Const QiSCRCMD4Read = &H51                           ' Script4 command register READ.
Public Const QiSCRCMD4Write = &HD1                          ' Script4 command register WRITE.
Public Const QiSCRDAT4Read = &H52                           ' Script4 execution data register READ.
Public Const QiSCRDAT4Write = &HD2                          ' Script4 execution data register WRITE.
Public Const QiCQ4Read = &H53                               ' Script4 captured data register READ.
Public Const QiNoOperation_D3 = &HD3                        ' No operation.
Public Const QiSCRTGRead = &H54                             ' Target source data setting READ.
Public Const QiSCRTGWrite = &HD4                            ' Target source data setting WRITE.
Public Const QiSCRSTAT1Read = &H55                          ' Script status #1 READ.
Public Const QiNoOperation_D5 = &HD5                        ' No operation.
Public Const QiSCRSTAT2Read = &H56                          ' Script status #2 READ.
Public Const QiNoOperation_D6 = &HD6                        ' No operation.
Public Const QiNoOperation_57 = &H57                        ' No operation.
Public Const QiINITSQWrite = &HD7                           ' Initialize script queues with target selection.
Public Const QiNoOperation_58 = &H58                        ' No operation.
Public Const QiINITCQWrite = &HD8                           ' Initialize captured data queue with target selection.
Public Const QiSCRMRead = &H59                              ' Set enable mode with target selection READ.
Public Const QiSCRMWrite = &HD9                             ' Set enable mode with target selection WRITE.
Public Const QiNoOperation_5A = &H5A                        ' No operation.
Public Const QiSQ1POP = &HDA                                ' Pop and shift data of script1 queue.
Public Const QiNoOperation_5B = &H5B                        ' No operation.
Public Const QiSQ2POP = &HDB                                ' Pop and shift data of script2 queue.
' Counter function registers
Public Const QiCNTLBRead = &H61                             ' Counter lower bound data READ.
Public Const QiCNTLBWrite = &HE1                            ' Counter lower bound data WRITE.
Public Const QiCNTUBRead = &H62                             ' Counter upper bound data READ.
Public Const QiCNTUBWrite = &HE2                            ' Counter upper bound data WRITE.
Public Const QiCNTCF1Read = &H63                            ' Counter configure #1 READ.
Public Const QiCNTCF1Write = &HE3                           ' Counter configure #1 WRITE.
Public Const QiCNTCF2Read = &H64                            ' Counter configure #2 READ.
Public Const QiCNTCF2Write = &HE4                           ' Counter configure #2 WRITE.
Public Const QiCNTCF3Read = &H65                            ' Counter configure #3 READ.
Public Const QiCNTCF3Write = &HE5                           ' Counter configure #3 WRITE.
Public Const QiCNT1Read = &H66                              ' Counter #1 data READ.
Public Const QiCNT1Write = &HE6                             ' Counter #1 data WRITE.
Public Const QiCNT2Read = &H67                              ' Counter #2 data READ.
Public Const QiCNT2Write = &HE7                             ' Counter #2 data WRITE.
Public Const QiCNT3Read = &H68                              ' Counter #3 data READ.
Public Const QiCNT3Write = &HE8                             ' Counter #3 data WRITE.
Public Const QiCNT4Read = &H69                              ' Counter #4 data READ.
Public Const QiCNT4Write = &HE9                             ' Counter #4 data WRITE.
Public Const QiCNT5Read = &H6A                              ' Counter #5 data READ.
Public Const QiCNT5Write = &HEA                             ' Counter #5 data WRITE.
Public Const QiCNTC1Read = &H6B                             ' Counter #1 comparator's data READ.
Public Const QiCNTC1Write = &HEB                            ' Counter #1 comparator's data WRITE.
Public Const QiCNTC2Read = &H6C                             ' Counter #2 comparator's data READ.
Public Const QiCNTC2Write = &HEC                            ' Counter #2 comparator's data WRITE.
Public Const QiCNTC3Read = &H6D                             ' Counter #3 comparator's data READ.
Public Const QiCNTC3Write = &HED                            ' Counter #3 comparator's data WRITE.
Public Const QiCNTC4Read = &H6E                             ' Counter #4 comparator's data READ.
Public Const QiCNTC4Write = &HEE                            ' Counter #4 comparator's data WRITE.
Public Const QiCNTC5Read = &H6F                             ' Counter #5 comparator's data READ.
Public Const QiCNTC5Write = &HEF                            ' Counter #5 comparator's data WRITE.
' Configure and Status registers
Public Const QiUCFG1Read = &H70                             ' Configure register #1 READ.
Public Const QiUCFG1Write = &HF0                            ' Configure register #1 WRITE.
Public Const QiUCFG2Read = &H71                             ' Configure register #2 READ.
Public Const QiUCFG2Write = &HF1                            ' Configure register #2 WRITE.
Public Const QiUCFG3Read = &H72                             ' Configure register #3 READ.
Public Const QiUCFG3Write = &HF2                            ' Configure register #3 WRITE.
Public Const QiUCFG4Read = &H73                             ' Configure register #4 READ.
Public Const QiUCFG4Write = &HF3                            ' Configure register #4 WRITE.
Public Const QiNoOperation_74 = &H74                        ' No operation.
Public Const QiNoOperation_F4 = &HF4                        ' No operation.
Public Const QiNoOperation_75 = &H75                        ' No operation.
Public Const QiNoOperation_F5 = &HF5                        ' No operation.
Public Const QiNoOperation_76 = &H76                        ' No operation.
Public Const QiNoOperation_F6 = &HF6                        ' No operation.
Public Const QiIMASK1Read = &H77                            ' Interrupt bank#1 mask register READ.
Public Const QiIMASK1Write = &HF7                           ' Interrupt bank#1 mask register WRITE.
Public Const QiIMASK2Read = &H78                            ' Interrupt bank#2 mask register READ.
Public Const QiIMASK2Write = &HF8                           ' Interrupt bank#2 mask register WRITE.
Public Const QiSTAT1Read = &H79                             ' Status register #1(END STATUS)READ.
Public Const QiESCLR = &HF9                                 ' Status register #1(END STATUS) Clear.
Public Const QiSTAT2Read = &H7A                             ' Status register #2 READ.
Public Const QiNoOperation_FA = &HFA                        ' No operation.
Public Const QiSTAT3Read = &H7B                             ' Status register #3 READ.
Public Const QiNoOperation_FB = &HFB                        ' No operation.
Public Const QiSTAT4Read = &H7C                             ' Status register #4 READ.
Public Const QiNoOperation_FC = &HFC                        ' No operation.
Public Const QiSTAT5Read = &H7D                             ' Status register #5 READ.
Public Const QiNoOperation_FD = &HFD                        ' No operation.
Public Const QiIFLAG1Read = &H7E                            ' Interrupt bank #1 flag READ.
Public Const QiIFLAG1Clear = &HFE                           ' Interrupt bank #1 flag Clear.
Public Const QiIFLAG2Read = &H7F                            ' Interrupt bank #2 flag READ.
Public Const QiIFLAG2Clear = &HFF                           ' Interrupt bank #2 flag Clear.

Public Const EVENT_IPNONE = &H0
Public Const EVENT_IPDRIVE_END = &H1
Public Const EVENT_IPPRESETDRIVE_START = &H2
Public Const EVENT_IPPRESETDRIVE_END = &H3
Public Const EVENT_IPCONTINOUSDRIVE_START = &H4
Public Const EVENT_IPCONTINOUSDRIVE_END = &H5
Public Const EVENT_IPSIGNAL_SEARCH_1_START = &H6
Public Const EVENT_IPSIGNAL_SEARCH_1_END = &H7
Public Const EVENT_IPSIGNAL_SEARCH_2_START = &H8
Public Const EVENT_IPSIGNAL_SEARCH_2_END = &H9
Public Const EVENT_IPORIGIN_DETECT_START = &HA
Public Const EVENT_IPORIGIN_DETECT_END = &HB
Public Const EVENT_IPSPEED_UP = &HC
Public Const EVENT_IPSPEED_CONST = &HD
Public Const EVENT_IPSPEED_DOWN = &HE
Public Const EVENT_IPICL = &HF
Public Const EVENT_IPICE = &H10
Public Const EVENT_IPICG = &H11
Public Const EVENT_IPECL = &H12
Public Const EVENT_IPECE = &H13
Public Const EVENT_IPECG = &H14
Public Const EVENT_IPEPCE = &H15
Public Const EVENT_IPEPCL = &H16
Public Const EVENT_IPEPCG = &H17
Public Const EVENT_IPSPL = &H18
Public Const EVENT_IPSPE = &H19
Public Const EVENT_IPSPG = &H1A
Public Const EVENT_IPSP12L = &H1B
Public Const EVENT_IPSP12E = &H1C
Public Const EVENT_IPSP12G = &H1D
Public Const EVENT_IPSP23L = &H1E
Public Const EVENT_IPSP23E = &H1F
Public Const EVENT_IPSP23G = &H20
Public Const EVENT_IPOBJECT_SPEED = &H21
Public Const EVENT_IPSS_SPEED = &H22
Public Const EVENT_IPESTOP = &H23
Public Const EVENT_IPSSTOP = &H24
Public Const EVENT_IPPELM = &H25
Public Const EVENT_IPNELM = &H26
Public Const EVENT_IPPSLM = &H27
Public Const EVENT_IPNSLM = &H28
Public Const EVENT_IPDEVIATION_ERROR = &H29
Public Const EVENT_IPDATA_ERROR = &H2A
Public Const EVENT_IPALARM_ERROR = &H2B
Public Const EVENT_IPESTOP_COMMAND = &H2C
Public Const EVENT_IPSSTOP_COMMAND = &H2D
Public Const EVENT_IPESTOP_SIGNAL = &H2E
Public Const EVENT_IPSSTOP_SIGNAL = &H2F
Public Const EVENT_IPELM = &H30
Public Const EVENT_IPSLM = &H31
Public Const EVENT_IPINPOSITION = &H32
Public Const EVENT_IPINOUT0_HIGH = &H33
Public Const EVENT_IPINOUT0_LOW = &H34
Public Const EVENT_IPINOUT1_HIGH = &H35
Public Const EVENT_IPINOUT1_LOW = &H36
Public Const EVENT_IPINOUT2_HIGH = &H37
Public Const EVENT_IPINOUT2_LOW = &H38
Public Const EVENT_IPINOUT3_HIGH = &H39
Public Const EVENT_IPINOUT3_LOW = &H3A
Public Const EVENT_IPINOUT4_HIGH = &H3B
Public Const EVENT_IPINOUT4_LOW = &H3C
Public Const EVENT_IPINOUT5_HIGH = &H3D
Public Const EVENT_IPINOUT5_LOW = &H3E
Public Const EVENT_IPINOUT6_HIGH = &H3F
Public Const EVENT_IPINOUT6_LOW = &H40
Public Const EVENT_IPINOUT7_HIGH = &H41
Public Const EVENT_IPINOUT7_LOW = &H42
Public Const EVENT_IPINOUT8_HIGH = &H43
Public Const EVENT_IPINOUT8_LOW = &H44
Public Const EVENT_IPINOUT9_HIGH = &H45
Public Const EVENT_IPINOUT9_LOW = &H46
Public Const EVENT_IPINOUT10_HIGH = &H47
Public Const EVENT_IPINOUT10_LOW = &H48
Public Const EVENT_IPINOUT11_HIGH = &H49
Public Const EVENT_IPINOUT11_LOW = &H4A
Public Const EVENT_IPSENSOR_DRIVE1_START = &H4B
Public Const EVENT_IPSENSOR_DRIVE1_END = &H4C
Public Const EVENT_IPSENSOR_DRIVE2_START = &H4D
Public Const EVENT_IPSENSOR_DRIVE2_END = &H4E
Public Const EVENT_IPSENSOR_DRIVE3_START = &H4F
Public Const EVENT_IPSENSOR_DRIVE3_END = &H50
Public Const EVENT_IP1STCOUNTER_NDATA_CLEAR = &H51
Public Const EVENT_IP2NDCOUNTER_NDATA_CLEAR = &H52
Public Const EVENT_IPMARK_SIGNAL_HIGH = &H53
Public Const EVENT_IPMARK_SIGNAL_LOW = &H54
Public Const EVENT_IPSOFTWARE_PLIMIT = &H55
Public Const EVENT_IPSOFTWARE_NLIMIT = &H56
Public Const EVENT_IPSOFTWARE_LIMIT = &H57
Public Const EVENT_IPTRIGGER_ENABLE = &H58
Public Const EVENT_IPINT_GEN_SOURCE = &H59
Public Const EVENT_IPINT_GEN_CMDF9 = &H5A
Public Const EVENT_IPPRESETDRIVE_TRI_START = &H5B
Public Const EVENT_IPBUSY_HIGH = &H5C
Public Const EVENT_IPBUSY_LOW = &H5D
Public Const EVENT_IPLINP_START = &H5E
Public Const EVENT_IPLINP_END = &H5F
Public Const EVENT_IPCINP_START = &H60
Public Const EVENT_IPCINP_END = &H61
Public Const EVENT_IPPINP_START = &H62
Public Const EVENT_IPPINP_END = &H63
Public Const EVENT_IPPDATA_Q_EMPTY = &H64
Public Const EVENT_IPS_C_INTERNAL_COMMAND_Q_EMPTY = &H65
Public Const EVENT_IPS_C_INTERNAL_COMMAND_Q_FULL = &H66
Public Const EVENT_IPxSYNC_ACTIVATED = &H67
Public Const EVENT_IPySYNC_ACTIVATED = &H68
Public Const EVENT_IPINTERRUPT_GENERATED = &H69
Public Const EVENT_IPINP_START = &H6A
Public Const EVENT_IPINP_END = &H6B
Public Const EVENT_IPALGEBRIC_RESULT_BIT0 = &H6C
Public Const EVENT_IPALGEBRIC_RESULT_BIT1 = &H6D
Public Const EVENT_IPALGEBRIC_RESULT_BIT2 = &H6E
Public Const EVENT_IPALGEBRIC_RESULT_BIT3 = &H6F
Public Const EVENT_IPALGEBRIC_RESULT_BIT4 = &H70
Public Const EVENT_IPALGEBRIC_RESULT_BIT5 = &H71
Public Const EVENT_IPALGEBRIC_RESULT_BIT6 = &H72
Public Const EVENT_IPALGEBRIC_RESULT_BIT7 = &H73
Public Const EVENT_IPALGEBRIC_RESULT_BIT8 = &H74
Public Const EVENT_IPALGEBRIC_RESULT_BIT9 = &H75
Public Const EVENT_IPALGEBRIC_RESULT_BIT10 = &H76
Public Const EVENT_IPALGEBRIC_RESULT_BIT11 = &H77
Public Const EVENT_IPALGEBRIC_RESULT_BIT12 = &H78
Public Const EVENT_IPALGEBRIC_RESULT_BIT13 = &H79
Public Const EVENT_IPALGEBRIC_RESULT_BIT14 = &H7A
Public Const EVENT_IPALGEBRIC_RESULT_BIT15 = &H7B
Public Const EVENT_IPALGEBRIC_RESULT_BIT16 = &H7C
Public Const EVENT_IPALGEBRIC_RESULT_BIT17 = &H7D
Public Const EVENT_IPALGEBRIC_RESULT_BIT18 = &H7E
Public Const EVENT_IPALGEBRIC_RESULT_BIT19 = &H7F
Public Const EVENT_IPALGEBRIC_RESULT_BIT20 = &H80
Public Const EVENT_IPALGEBRIC_RESULT_BIT21 = &H81
Public Const EVENT_IPALGEBRIC_RESULT_BIT22 = &H82
Public Const EVENT_IPALGEBRIC_RESULT_BIT23 = &H83
Public Const EVENT_IPALGEBRIC_RESULT_BIT24 = &H84
Public Const EVENT_IPALGEBRIC_RESULT_BIT25 = &H85
Public Const EVENT_IPALGEBRIC_RESULT_BIT26 = &H86
Public Const EVENT_IPALGEBRIC_RESULT_BIT27 = &H87
Public Const EVENT_IPALGEBRIC_RESULT_BIT28 = &H88
Public Const EVENT_IPALGEBRIC_RESULT_BIT29 = &H89
Public Const EVENT_IPALGEBRIC_RESULT_BIT30 = &H8A
Public Const EVENT_IPALGEBRIC_RESULT_BIT31 = &H8B
Public Const EVENT_IPCOMPARE_RESULT_BIT0 = &H8C
Public Const EVENT_IPCOMPARE_RESULT_BIT1 = &H8D
Public Const EVENT_IPCOMPARE_RESULT_BIT2 = &H8E
Public Const EVENT_IPCOMPARE_RESULT_BIT3 = &H8F
Public Const EVENT_IPCOMPARE_RESULT_BIT4 = &H90
Public Const EVENT_IPON_INTERPOLATION = &H91
Public Const EVENT_IPON_LINEAR_INTERPOLATION = &H92
Public Const EVENT_IPON_CIRCULAR_INTERPOLATION = &H93
Public Const EVENT_IPON_PATTERN_INTERPOLATION = &H94
Public Const EVENT_IPNONE_95 = &H95
Public Const EVENT_IPL_C_INP_Q_EMPTY = &H96
Public Const EVENT_IPL_C_INP_Q_LESS_4 = &H97
Public Const EVENT_IPP_INP_Q_EMPTY = &H98
Public Const EVENT_IPP_INP_Q_LESS_4 = &H99
Public Const EVENT_IPINTERPOLATION_PAUSED = &H9A
Public Const EVENT_IPP_INP_END_BY_END_PATTERN = &H9B
Public Const EVENT_IPARITHMETIC_DATA_SEL = &HEE
Public Const EVENT_IPEXECUTION_ALWAYS = &HFF

'{ QI Event Define }
Public Const EVENT_QINOOP = &H0                             ' No operation.
Public Const EVENT_QIDRVEND = &H1                           ' Drive end event(inposition function excluded).
Public Const EVENT_QIDECEL = &H2                            ' Deceleration state.
Public Const EVENT_QICONST = &H3                            ' Constant speed state.
Public Const EVENT_QIACCEL = &H4                            ' Acceleration state.
Public Const EVENT_QICNT1L = &H5                            ' Counter1 < Comparater1 state.
Public Const EVENT_QICNT1E = &H6                            ' Counter1 = Comparater1 state.
Public Const EVENT_QICNT1G = &H7                            ' Counter1 > Comparater1 state.
Public Const EVENT_QICNT1LE = &H8                           ' Counter1 ≤ Comparater1 state.
Public Const EVENT_QICNT1GE = &H9                           ' Counter1 ≥ Comparater1 state.
Public Const EVENT_QICNT1EUP = &HA                          ' Counter1 = Comparater1 event during counting up.
Public Const EVENT_QICNT1EDN = &HB                          ' Counter1 = Comparater1 event during counting down.
Public Const EVENT_QICNT1BND = &HC                          ' Counter1 is same with boundary value.
Public Const EVENT_QICNT2L = &HD                            ' Counter2 < Comparater2 state.
Public Const EVENT_QICNT2E = &HE                            ' Counter2 = Comparater2 state.
Public Const EVENT_QICNT2G = &HF                            ' Counter2 > Comparater2 state.
Public Const EVENT_QICNT2LE = &H10                          ' Counter2 ≤ Comparater2 state.
Public Const EVENT_QICNT2GE = &H11                          ' Counter2 ≥ Comparater2 state.
Public Const EVENT_QICNT2EUP = &H12                         ' Counter2 = Comparater2 event during counting up.
Public Const EVENT_QICNT2EDN = &H13                         ' Counter2 = Comparater2 event during counting down.
Public Const EVENT_QICNT2BND = &H14                         ' Counter2 is same with boundary value.
Public Const EVENT_QICNT3L = &H15                           ' Counter3 < Comparater3 state.
Public Const EVENT_QICNT3E = &H16                           ' Counter3 = Comparater3 state.
Public Const EVENT_QICNT3G = &H17                           ' Counter3 > Comparater3 state.
Public Const EVENT_QICNT3LE = &H18                          ' Counter3 ≤ Comparater3 state.
Public Const EVENT_QICNT3GE = &H19                          ' Counter3 ≥ Comparater3 state.
Public Const EVENT_QICNT3EUP = &H1A                         ' Counter3 = Comparater3 event during counting up.
Public Const EVENT_QICNT3EDN = &H1B                         ' Counter3 = Comparater3 event during counting down.
Public Const EVENT_QICNT3BND = &H1C                         ' Counter3 is same with boundary value.
Public Const EVENT_QICNT4L = &H1D                           ' Counter4 < Comparater4 state.
Public Const EVENT_QICNT4E = &H1E                           ' Counter4 = Comparater4 state.
Public Const EVENT_QICNT4G = &H1F                           ' Counter4 > Comparater4 state.
Public Const EVENT_QICNT4LE = &H20                          ' Counter4 ≤ Comparater4 state.
Public Const EVENT_QICNT4GE = &H21                          ' Counter4 ≥ Comparater4 state.
Public Const EVENT_QICNT4EUP = &H22                         ' Counter4 = Comparater4 event during counting up.
Public Const EVENT_QICNT4EDN = &H23                         ' Counter4 = Comparater4 event during counting down.
Public Const EVENT_QICNT4BND = &H24                         ' Counter4 is same with boundary value.
Public Const EVENT_QICNT5L = &H25                           ' Counter5 < Comparater5 state.
Public Const EVENT_QICNT5E = &H26                           ' Counter5 = Comparater5 state.
Public Const EVENT_QICNT5G = &H27                           ' Counter5 > Comparater5 state.
Public Const EVENT_QICNT5LE = &H28                          ' Counter5 ≤ Comparater5 state.
Public Const EVENT_QICNT5GE = &H29                          ' Counter5 ≥ Comparater5 state.
Public Const EVENT_QICNT5EUP = &H2A                         ' Counter5 = Comparater5 event during counting up.
Public Const EVENT_QICNT5EDN = &H2B                         ' Counter5 = Comparater5 event during counting down.
Public Const EVENT_QICNT5BND = &H2C                         ' Counter5 is same with boundary value.
Public Const EVENT_QIDEVL = &H2D                            ' DEVIATION value < Comparater4 state.
Public Const EVENT_QIDEVE = &H2E                            ' DEVIATION value = Comparater4 state.
Public Const EVENT_QIDEVG = &H2F                            ' DEVIATION value > Comparater4 state.
Public Const EVENT_QIDEVLE = &H30                           ' DEVIATION value ≤ Comparater4 state.
Public Const EVENT_QIDEVGE = &H31                           ' DEVIATION value ≥ Comparater4 state.
Public Const EVENT_QIPELM = &H32                            ' PELM input signal is activated state.
Public Const EVENT_QINELM = &H33                            ' NELM input signal is activated state.
Public Const EVENT_QIPSLM = &H34                            ' PSLM input signal is activated state.
Public Const EVENT_QINSLM = &H35                            ' NSLM input signal is activated state.
Public Const EVENT_QIALARM = &H36                           ' ALAMR input signal is activated state.
Public Const EVENT_QIINPOS = &H37                           ' INPOSITION input signal ia activated state.
Public Const EVENT_QIESTOP = &H38                           ' ESTOP input signal is activated state.
Public Const EVENT_QIORG = &H39                             ' ORG input signal is activated state.
Public Const EVENT_QIZ_PHASE = &H3A                         ' Z_PHASE input signal is activated state.
Public Const EVENT_QIECUP = &H3B                            ' ECUP input signal is high level state.
Public Const EVENT_QIECDN = &H3C                            ' ECDN input signal is high level state.
Public Const EVENT_QIEXPP = &H3D                            ' EXPP input signal is high level state.
Public Const EVENT_QIEXMP = &H3E                            ' EXMP input signal is high level state.
Public Const EVENT_QISQSTR1 = &H3F                          ' SYNC Start1 input signal is activated state(activated).
Public Const EVENT_QISQSTR2 = &H40                          ' SYNC Start2 input signal is activated state(activated).
Public Const EVENT_QISQSTP1 = &H41                          ' SYNC STOP1 input signal is activated state(activated).
Public Const EVENT_QISQSTP2 = &H42                          ' SYNC STOP2 input signal is activated state(activated).
Public Const EVENT_QIALARMS = &H43                          ' At least one alarm signal of each axis is activated state.
Public Const EVENT_QIUIO0 = &H44                            ' UIO0 data is high state.
Public Const EVENT_QIUIO1 = &H45                            ' UIO1 data is high state.
Public Const EVENT_QIUIO2 = &H46                            ' UIO2 data is high state.
Public Const EVENT_QIUIO3 = &H47                            ' UIO3 data is high state.
Public Const EVENT_QIUIO4 = &H48                            ' UIO4 data is high state.
Public Const EVENT_QIUIO5 = &H49                            ' UIO5 data is high state.
Public Const EVENT_QIUIO6 = &H4A                            ' UIO6 data is high state.
Public Const EVENT_QIUIO7 = &H4B                            ' UIO7 data is high state.
Public Const EVENT_QIUIO8 = &H4C                            ' UIO8 data is high state.
Public Const EVENT_QIUIO9 = &H4D                            ' UIO9 data is high state.
Public Const EVENT_QIUIO10 = &H4E                           ' UIO10 data is high state.
Public Const EVENT_QIUIO11 = &H4F                           ' UIO11 data is high state.
Public Const EVENT_QIERC = &H50                             ' ERC output is activated.
Public Const EVENT_QITRG = &H51                             ' TRIGGER signal is activated.
Public Const EVENT_QIPREQI0 = &H52                          ' Previous queue data index 0 bit is high state.
Public Const EVENT_QIPREQI1 = &H53                          ' Previous queue data index 1 bit is high state.
Public Const EVENT_QIPREQI2 = &H54                          ' Previous queue data index 2 bit is high state.
Public Const EVENT_QIPREQZ = &H55                           ' Previous queue is empty state.
Public Const EVENT_QIPREQF = &H56                           ' Previous queue is full state.
Public Const EVENT_QIMPGE1 = &H57                           ' MPG first stage is overflowed state.
Public Const EVENT_QIMPGE2 = &H58                           ' MPG second stage is overflowed state.
Public Const EVENT_QIMPGE3 = &H59                           ' MPG third stage is overflowed state.
Public Const EVENT_QIMPGERR = &H5A                          ' MPG all state is overflowed state.
Public Const EVENT_QITRGCNT0 = &H5B                         ' TRIGGER queue index bit 0 is high state.
Public Const EVENT_QITRGCNT1 = &H5C                         ' TRIGGER queue index bit 1 is high state.
Public Const EVENT_QITRGCNT2 = &H5D                         ' TRIGGER queue index bit 2 is high state.
Public Const EVENT_QITRGCNT3 = &H5E                         ' TRIGGER queue index bit 3 is high state.
Public Const EVENT_QITRGQEPT = &H5F                         ' TRIGGER queue is empty state.
Public Const EVENT_QITRGQFULL = &H60                        ' TRIGGER queue is full state.
Public Const EVENT_QIDPAUSE = &H61                          ' Drive paused state.
Public Const EVENT_QIESTOPEXE = &H62                        ' Emergency stop occurred
Public Const EVENT_QISSTOPEXE = &H63                        ' Slowdown stop occurred
Public Const EVENT_QIPLMTSTOP = &H64                        ' Limit stop event occurred during positive driving.
Public Const EVENT_QINLMTSTOP = &H65                        ' Limit stop event occurred during negative driving.
Public Const EVENT_QIOPLMTSTOP = &H66                       ' Optional limit stop event occurred during positive driving.
Public Const EVENT_QIONLMTSTOP = &H67                       ' Optional limit stop event occurred during negative driving.
Public Const EVENT_QIPSWESTOP = &H68                        ' Software emergency limit stop event occurred.(CW)
Public Const EVENT_QINSWESTOP = &H69                        ' Software emergency limit stop event occurred.(CCW)
Public Const EVENT_QIPSWSSTOP = &H6A                        ' Software slowdown limit stop event occurred.(CW)
Public Const EVENT_QINSWSSTOP = &H6B                        ' Software slowdown limit stop event occurred.(CCW)
Public Const EVENT_QIALMSTOP = &H6C                         ' Emergency stop event occurred by alarm signal function.
Public Const EVENT_QIESTOPSTOP = &H6D                       ' Emergency stop event occurred by estop signal function.
Public Const EVENT_QIESTOPCMD = &H6E                        ' Emergency stop event occurred by command.
Public Const EVENT_QISSTOPCMD = &H6F                        ' Slowdown stop event occurred by command.
Public Const EVENT_QIALLSTCMD = &H70                        ' Emergency stop event occurred by all stop command.
Public Const EVENT_QISYSTOP1 = &H71                         ' SYNC stop1 event occurred.
Public Const EVENT_QISYSTOP2 = &H72                         ' SYNC stop2 event occurred.
Public Const EVENT_QIENCODERR = &H73                        ' Encoder input error event occurred.
Public Const EVENT_QIMPGOVERFLOW = &H74                     ' MPG input error event occurred.
Public Const EVENT_QIORGOK = &H75                           ' Original drive is executed successfully.
Public Const EVENT_QISSCHOK = &H76                          ' Signal search drive is executed successfully.
Public Const EVENT_QIUIO0LOW = &H77                         ' UIO0 data is low state.
Public Const EVENT_QIUIO1LOW = &H78                         ' UIO1 data is low state.
Public Const EVENT_QIUIO2LOW = &H79                         ' UIO2 data is low state.
Public Const EVENT_QIUIO3LOW = &H7A                         ' UIO3 data is low state.
Public Const EVENT_QIUIO4LOW = &H7B                         ' UIO4 data is low state.
Public Const EVENT_QIUIO5LOW = &H7C                         ' UIO5 data is low state.
Public Const EVENT_QIUIO6LOW = &H7D                         ' UIO6 data is low state.
Public Const EVENT_QIUIO7LOW = &H7E                         ' UIO7 data is low state.
Public Const EVENT_QIUIO8LOW = &H7F                         ' UIO8 data is low state.
Public Const EVENT_QIUIO9LOW = &H80                         ' UIO9 data is low state.
Public Const EVENT_QIUIO10LOW = &H81                        ' UIO10 data is low state.
Public Const EVENT_QIUIO11LOW = &H82                        ' UIO11 data is low state.
Public Const EVENT_QIUIO0RISING = &H83                      ' UIO0 rising edge event occurred.
Public Const EVENT_QIUIO1RISING = &H84                      ' UIO1 rising edge event occurred.
Public Const EVENT_QIUIO2RISING = &H85                      ' UIO2 rising edge event occurred.
Public Const EVENT_QIUIO3RISING = &H86                      ' UIO3 rising edge event occurred.
Public Const EVENT_QIUIO4RISING = &H87                      ' UIO4 rising edge event occurred.
Public Const EVENT_QIUIO5RISING = &H88                      ' UIO5 rising edge event occurred.
Public Const EVENT_QIUIO6RISING = &H89                      ' UIO6 rising edge event occurred.
Public Const EVENT_QIUIO7RISING = &H8A                      ' UIO7 rising edge event occurred.
Public Const EVENT_QIUIO8RISING = &H8B                      ' UIO8 rising edge event occurred.
Public Const EVENT_QIUIO9RISING = &H8C                      ' UIO9 rising edge event occurred.
Public Const EVENT_QIUIO10RISING = &H8D                     ' UIO10 rising edge event occurred.
Public Const EVENT_QIUIO11RISING = &H8E                     ' UIO11 rising edge event occurred.
Public Const EVENT_QIUIO0FALLING = &H8F                     ' UIO0 falling edge event occurred.
Public Const EVENT_QIUIO1FALLING = &H90                     ' UIO1 falling edge event occurred.
Public Const EVENT_QIUIO2FALLING = &H91                     ' UIO2 falling edge event occurred.
Public Const EVENT_QIUIO3FALLING = &H92                     ' UIO3 falling edge event occurred.
Public Const EVENT_QIUIO4FALLING = &H93                     ' UIO4 falling edge event occurred.
Public Const EVENT_QIUIO5FALLING = &H94                     ' UIO5 falling edge event occurred.
Public Const EVENT_QIUIO6FALLING = &H95                     ' UIO6 falling edge event occurred.
Public Const EVENT_QIUIO7FALLING = &H96                     ' UIO7 falling edge event occurred.
Public Const EVENT_QIUIO8FALLING = &H97                     ' UIO8 falling edge event occurred.
Public Const EVENT_QIUIO9FALLING = &H98                     ' UIO9 falling edge event occurred.
Public Const EVENT_QIUIO10FALLING = &H99                    ' UIO10 falling edge event occurred.
Public Const EVENT_QIUIO11FALLING = &H9A                    ' UIO11 falling edge event occurred.
Public Const EVENT_QIDRVSTR = &H9B                          ' Drive started.
Public Const EVENT_QIDNSTR = &H9C                           ' Speed down event occurred.
Public Const EVENT_QICOSTR = &H9D                           ' Constant speed event occurred.
Public Const EVENT_QIUPSTR = &H9E                           ' Speed up event occurred.
Public Const EVENT_QICONTISTR = &H9F                        ' Continuous drive started.
Public Const EVENT_QIPRESETSTR = &HA0                       ' Preset drive started.
Public Const EVENT_QIMPGSTR = &HA1                          ' MPG drive started.
Public Const EVENT_QIORGSTR = &HA2                          ' Original drive started.
Public Const EVENT_QISSCHSTR = &HA3                         ' Signal search drive started.
Public Const EVENT_QIPATHSTR = &HA4                         ' Interpolation drive started.
Public Const EVENT_QISLAVESTR = &HA5                        ' Slave drive started.
Public Const EVENT_QICCWSTR = &HA6                          ' CCW direction drive started.
Public Const EVENT_QIINPWAIT = &HA7                         ' Inposition wait event occurred.
Public Const EVENT_QILINSTR = &HA8                          ' Linear drive stated.
Public Const EVENT_QICIRSTR = &HA9                          ' Circular drive started.
Public Const EVENT_QIDRVENDII = &HAA                        ' Drive stopped.(Inposition state included)
Public Const EVENT_QIDNEND = &HAB                           ' Speed down end event occurred.
Public Const EVENT_QICOEND = &HAC                           ' Constant speed end event occurred.
Public Const EVENT_QIUPEND = &HAD                           ' Speed up end event occurred.
Public Const EVENT_QICONTIEND = &HAE                        ' Continuous drive ended.
Public Const EVENT_QIPRESETEND = &HAF                       ' Preset drive ended.
Public Const EVENT_QIMPGEND = &HB0                          ' MPG drive ended.
Public Const EVENT_QIORGEND = &HB1                          ' Original drive ended.
Public Const EVENT_QISSCHEND = &HB2                         ' Signal search drive ended.
Public Const EVENT_QIPATHEND = &HB3                         ' Interpolation drive ended.
Public Const EVENT_QISLAVEEND = &HB4                        ' Slave drive ended.
Public Const EVENT_QICCWEND = &HB5                          ' CCW direction drive ended.
Public Const EVENT_QIINPEND = &HB6                          ' Escape from Inposition waiting.
Public Const EVENT_QILINEND = &HB7                          ' Linear drive ended.
Public Const EVENT_QICIREND = &HB8                          ' Circular drive ended.
Public Const EVENT_QIBUSY = &HB9                            ' During driving state.
Public Const EVENT_QINBUSY = &HBA                           ' During not driving state.
Public Const EVENT_QITMR1EX = &HBB                          ' Timer1 expired event.
Public Const EVENT_QITMR2EX = &HBC                          ' Timer2 expired event.
Public Const EVENT_QIDRVENDIII = &HBD                       ' Drive(that interrupt enable bit is set to high) end event
Public Const EVENT_QIERROR = &HBE                           ' Error stop occurred.
'Public Const EVENT_QINOP = &HBF                            ' NOP.
Public Const EVENT_QIALWAYS = &HFF                          ' Always Generate.

'{ QI Register Define }
Public Const QI_SCR_REG1 = &H1
Public Const QI_SCR_REG2 = &H2
Public Const QI_SCR_REG3 = &H3
Public Const QI_SCR_REG4 = &H4
Public Const QI_OPERATION_ONCE_RUN = &H0                    ' bit 24 OFF
Public Const QI_OPERATION_CONTINUE_RUN = &H1000000          ' bit 24 ON
Public Const QI_INPUT_DATA_FROM_SCRIPT_DATA = &H0           ' bit 23 OFF
Public Const QI_INPUT_DATA_FROM_TARGET_REG = &H800000       ' bit 23 ON
'Public Const QI_INTERRUPT_GEN_ENABLE = &H00000000          ' bit 22 OFF
'Public Const QI_INTERRUPT_GEN_DISABLE = &H00400000         ' bit 22 ON
Public Const QI_INTERRUPT_GEN_ENABLE = &H400000             ' bit 22 ON
Public Const QI_INTERRUPT_GEN_DISABLE = &H0                 ' bit 22 OFF
Public Const QI_OPERATION_EVENT_NONE = &H0                  ' bit 21=OFF, 20=OFF
'Public Const QI_OPERATION_EVENT_OR = &H00100000            ' bit 21=OFF, 20=ON
'Public Const QI_OPERATION_EVENT_AND = &H00200000           ' bit 21=ON,  20=OF
Public Const QI_OPERATION_EVENT_AND = &H100000              ' bit 21=OFF, 20=ON
Public Const QI_OPERATION_EVENT_OR = &H200000               ' bit 21=ON,  20=OFF
Public Const QI_OPERATION_EVENT_XOR = &H300000              ' bit 21=ON,  20=ON
                           
Function QI_SND_EVENT_AXIS(Axis As Long) As Long            ' bit 19~18 (00:X, 01:Y, 10:Z, 11:U)
    QI_SND_EVENT_AXIS = ((Axis Mod 4) * (2 ^ 18))
End Function

Function QI_FST_EVENT_AXIS(Axis As Long) As Long            ' bit 17~16 (00:X, 01:Y, 10:Z, 11:U)
    QI_FST_EVENT_AXIS = ((Axis Mod 4) * (2 ^ 16))
End Function

Function QI_OPERATION_EVENT_2(iEvent As Long) As Long        ' bit 15..8
    QI_OPERATION_EVENT_2 = ((iEvent And &HFF) * (2 ^ 8))
End Function

Function QI_OPERATION_EVENT_1(iEvent As Long) As Long        ' bit 7..0
    QI_OPERATION_EVENT_1 = (iEvent And &HFF)
End Function

Function QI_OPERATION_COMMAND(Command As Long, Axis As Long) As Long
    QI_OPERATION_COMMAND = ((Command And &HFF) * (2 ^ ((Axis Mod 4) * 8)))
End Function
