Attribute VB_Name = "AXHS"
'****************************************************************************
'*****************************************************************************
'**
'** File Name
'** ---------
'**
'** AXHS.BAS
'**
'** COPYRIGHT (c) AJINEXTEK Co., LTD
'**
'*****************************************************************************
'*****************************************************************************
'**
'** Description
'** -----------
'** Resource Define Header File
'**
'**
'*****************************************************************************
'*****************************************************************************
'**
'** Source Change Indices
'** ---------------------
'**
'** (None)
'**
'**
'*****************************************************************************
'*****************************************************************************
'**
'** Website
'** ---------------------
'**
'** http:'www.ajinextek.com
'**
'*****************************************************************************
'*****************************************************************************
'*

' Define Baseboard
Public Const AXT_UNKNOWN = &H0                              ' Unknown Baseboard
Public Const AXT_BIHR = &H1                                 ' ISA bus, Half size
Public Const AXT_BIFR = &H2                                 ' ISA bus, Full size
Public Const AXT_BPHR = &H3                                 ' PCI bus, Half size
Public Const AXT_BPFR = &H4                                 ' PCI bus, Full size
Public Const AXT_BV3R = &H5                                 ' VME bus, 3U size
Public Const AXT_BV6R = &H6                                 ' VME bus, 6U size
Public Const AXT_BC3R = &H7                                 ' cPCI bus, 3U size
Public Const AXT_BC6R = &H8                                 ' cPCI bus, 6U size
Public Const AXT_BEHR = &H9                                 ' PCIe bus, Half size
Public Const AXT_BEFR = &HA                                 ' PCIe bus, Full size
Public Const AXT_BEHD = &HB                                ' PCIe bus, Half size, DB-32T
Public Const AXT_FMNSH4D = &H52                             ' ISA bus, Full size, DB-32T, SIO-2V03 * 2
Public Const AXT_PCI_DI64R = &H43                           ' PCI bus, Digital IN 64 point
Public Const AXT_PCIE_DI64R = &H44                         ' PCIe bus, Digital IN 64 point
Public Const AXT_PCI_DO64R = &H53                           ' PCI bus, Digital OUT 64 point
Public Const AXT_PCIE_DO64R = &H54                         ' PCIe bus, Digital OUT 64 point
Public Const AXT_PCI_DB64R = &H63                           ' PCI bus, Digital IN 32 point OUT point??
Public Const AXT_PCIE_DB64R = &H64                         ' PCIe bus, Digital IN 32 point OUT point??
Public Const AXT_PCIN204 = &H82                             ' PCI bus, Half size On-Board 2 Axis controller.
Public Const AXT_BPHD = &H83                                ' PCI bus, Half size, DB-32T
Public Const AXT_PCIN404 = &H84                             ' PCI bus, Half size On-Board 4 Axis controller.
Public Const AXT_PCIN804 = &H85                             ' PCI bus, Half size On-Board 8 Axis controller.
Public Const AXT_PCIEN804 = &H86                            ' PCIe bus, Half size On-Board 8 Axis controller.
Public Const AXT_PCIEN404 = &H87                            ' PCIe bus, Half size On-Board 4 Axis controller.
Public Const AXT_PCI_AIO1602HR = &H93                       ' PCI bus, Half size, AI-16ch, AO-2ch AI16HR
Public Const AXT_PCI_R1604 = &HC1                           ' PCI bus[PCI9030], Half size, RTEX based 16 axis controller
Public Const AXT_PCI_R3204 = &HC2                           ' PCI bus[PCI9030], Half size, RTEX based 32 axis controller
Public Const AXT_PCI_R32IO = &HC3                           ' PCI bus[PCI9030], Half size, RTEX based IO only.
Public Const AXT_PCI_REV2 = &HC4                            ' Reserved.
Public Const AXT_PCI_R1604MLII = &HC5                       ' PCI bus[PCI9030], Half size, Mechatrolink-II 16/32 axis controller.
Public Const AXT_PCI_R0804MLII = &HC6                      ' PCI bus[PCI9030], Half size, Mechatrolink-II 08 axis controller.
Public Const AXT_PCI_Rxx00MLIII = &HC7                     ' Master PCI Board, Mechatrolink III AXT, PCI Bus[PCI9030], Half size, Max.32 Slave module support
Public Const AXT_PCIE_Rxx00MLIII = &HC8                    ' Master PCI Express Board, Mechatrolink III AXT, PCI Bus[], Half size, Max.32 Slave module support
Public Const AXT_PCP2_Rxx00MLIII = &HC9                    ' Master PCI/104-Plus Board, Mechatrolink III AXT, PCI Bus[], Half size, Max.32 Slave module support
Public Const AXT_PCI_R1604SIIIH = &HCA                     ' PCI bus[PCI9030], Half size, SSCNET III / H 16/32 axis controller.
Public Const AXT_PCI_R32IOEV = &HCB                        ' PCI bus[PCI9030], Half size, RTEX based IO only. Economic version.
Public Const AXT_PCIE_R0804RTEX = &HCC                     ' PCIe bus, Half size, Half size, RTEX based 08 axis controller.
Public Const AXT_PCIE_R1604RTEX = &HCD                     ' PCIe bus, Half size, Half size, RTEX based 16 axis controller.
Public Const AXT_PCIE_R2404RTEX = &HCE                     ' PCIe bus, Half size, Half size, RTEX based 24 axis controller.
Public Const AXT_PCIE_R3204RTEX = &HCF                     ' PCIe bus, Half size, Half size, RTEX based 32 axis controller.
Public Const AXT_PCIE_Rxx04SIIIH = &HD0                    ' PCIe bus, Half size, SSCNET III / H 16(or 32)-axis(CAMC-QI based) controller.
Public Const AXT_PCIE_Rxx00SIIIH = &HD1                    ' PCIe bus, Half size, SSCNET III / H Max. 32-axis(DSP Based) controller.
Public Const AXT_ETHERCAT_RTOSV5 = &HD2                    ' EtherCAT, RTOS(On Time), Version 5.29
Public Const AXT_PCI_Nx04_A = &HD3                         ' PCI bus, Half size On-Board x Axis controller For Rtos.
Public Const AXT_PCI_R3200MLIII_IO = &HD4                  ' PCI Board, Mechatrolink III AXT, PCI Bus[PCI9030], Half size, Max.32 IO only	controller
Public Const AXT_PCIE_R3205MLIII = &HD5                    ' PCIe bus, Half size, Mechatrolink III / H Max. 32-axis(DSP Based) controller.

' Define Module
Public Const AXT_SMC_2V01 = &H1                             ' CAMC-5M, 2 Axis
Public Const AXT_SMC_2V02 = &H2                             ' CAMC-FS, 2 Axis
Public Const AXT_SMC_1V01 = &H3                             ' CAMC-5M, 1 Axis
Public Const AXT_SMC_1V02 = &H4                             ' CAMC-FS, 1 Axis
Public Const AXT_SMC_2V03 = &H5                             ' CAMC-IP, 2 Axis
Public Const AXT_SMC_4V04 = &H6                             ' CAMC-QI, 4 Axis
Public Const AXT_SMC_R1V04A4 = &H7                          ' CAMC-QI, 1 Axis, For RTEX A4 slave only
Public Const AXT_SMC_1V03 = &H8                             ' CAMC-IP, 1 Axis
Public Const AXT_SMC_R1V04 = &H9                            ' CAMC-QI, 1 Axis, For RTEX SLAVE only
Public Const AXT_SMC_R1V04MLIISV = &HA                      ' CAMC-QI, 1 Axis, For Sigma-X series.
Public Const AXT_SMC_R1V04MLIIPM = &HB                      ' 2 Axis, For Pulse output series(JEPMC-PL2910).
Public Const AXT_SMC_2V04 = &HC                             ' CAMC-QI, 2 Axis
Public Const AXT_SMC_R1V04A5 = &HD                          ' CAMC-QI, 1 Axis, For RTEX A5N slave only
Public Const AXT_SMC_R1V04MLIICL = &HE                      ' CAMC-QI, 1 Axis, For MLII Convex Linear Driver.
Public Const AXT_SMC_R1V04MLIICR = &HF                      ' CAMC-QI, 1 Axis, For MLII Convex Rotary Driver.
Public Const AXT_SMC_R1V04PM2Q = &H10                       ' CAMC-QI, 2 Axis, For RTEX SLAVE only(Pulse Output Module)
Public Const AXT_SMC_R1V04PM2QE = &H11                      ' CAMC-QI, 4 Axis, For RTEX SLAVE only(Pulse Output Module)
Public Const AXT_SMC_R1V04MLIIORI = &H12                    ' CAMC-QI, 1 Axis, For MLII Oriental Step Driver only
Public Const AXT_SMC_R1V04SIIIHMIV = &H14                   ' CAMC-QI, 1 Axis, For SSCNETIII/H MRJ4
Public Const AXT_SMC_R1V04SIIIHMIV_R = &H15                 ' CAMC-QI, 1 Axis, For SSCNETIII/H MRJ4
Public Const AXT_SMC_R1V04MLIIISV = &H20                    ' DSP, 1 Axis, For ML-3 SigmaV/YASKAWA only 
Public Const AXT_SMC_R1V04MLIIIPM = &H21                    ' DSP, 1 Axis, For ML-3 SLAVE/AJINEXTEK only(Pulse Output Module)
Public Const AXT_SMC_R1V04MLIIISV_MD = &H22                 ' DSP, 1 Axis, For ML-3 SigmaV-MD/YASKAWA only (Multi-Axis Control amp)
Public Const AXT_SMC_R1V04MLIIIS7S = &H23                   ' DSP, 1 Axis, For ML-3 Sigma7S/YASKAWA only
Public Const AXT_SMC_R1V04MLIIIS7W = &H24                   ' DSP, 2 Axis, For ML-3 Sigma7W/YASKAWA only(Dual-Axis control amp)
Public Const AXT_SMC_R1V04MLIIIRS2 = &H25                   ' DSP, 1 Axis, For ML-3 RS2A/SANYO DENKY
Public Const AXT_SMC_R1V04MLIIIS7_MD = &H26                 ' DSP, 1 Axis, For ML-3 Sigma7-MD/YASKAWA only (Multi-Axis Control amp)
Public Const AXT_SMC_PM2QSIIIH = &H60                       ' CAMC-QI, 2Axis For SSCNETIII/H SLAVE only(Pulse Output Module)
Public Const AXT_SMC_PM4QSIIIH = &H61                       ' CAMC-QI, 4Axis For SSCNETIII/H SLAVE only(Pulse Output Module)
Public Const AXT_SIO_CNT2SIIIH = &H62                       ' Counter slave module, Reversible counter, 2 channels, For SSCNETIII/H Only
Public Const AXT_SIO_DI32SIIIH = &H63                       ' DI slave module, SSCNETIII AXT, IN 32-Channel
Public Const AXT_SIO_DO32SIIIH = &H64                       ' DO slave module, SSCNETIII AXT, OUT 32-Channel
Public Const AXT_SIO_DB32SIIIH = &H65                       ' DB slave module, SSCNETIII AXT, IN 16-Channel, OUT 16-Channel
Public Const AXT_SIO_AI16SIIIH = &H66                       ' AI slave module, SSCNETIII AXT, Analog IN 16ch, 16 bit
Public Const AXT_SIO_AO08SIIIH = &H67                       ' A0 slave module, SSCNETIII AXT, Analog OUT 8ch, 16 bit
Public Const AXT_SMC_PM2QSIIIH_R = &H68                     ' AMC-QI, 2Axis For SSCNETIII/H SLAVE only(Pulse Output Module) 
Public Const AXT_SMC_PM4QSIIIH_R = &H69                     ' CAMC-QI, 4Axis For SSCNETIII/H SLAVE only(Pulse Output Module) 
Public Const AXT_SIO_CNT2SIIIH_R = &H6A                     ' Counter slave module, Reversible counter, 2 channels, For SSCNETIII/H Only 
Public Const AXT_SIO_DI32SIIIH_R = &H6B                     ' DI slave module, SSCNETIII AXT, IN 32-Channel 
Public Const AXT_SIO_DO32SIIIH_R = &H6C                     ' DO slave module, SSCNETIII AXT, OUT 32-Channel 
Public Const AXT_SIO_DB32SIIIH_R = &H6D                     ' DB slave module, SSCNETIII AXT, IN 16-Channel, OUT 16-Channel 
Public Const AXT_SIO_AI16SIIIH_R = &H6E                     ' AI slave module, SSCNETIII AXT, Analog IN 16ch, 16 bit 
Public Const AXT_SIO_AO08SIIIH_R = &H6F                     ' A0 slave module, SSCNETIII AXT, Analog OUT 8ch, 16 bit 
Public Const AXT_SIO_RDI32MLIII = &H70                      ' DI slave module, MechatroLink III AXT, IN 32-Channel NPN
Public Const AXT_SIO_RDO32MLIII = &H71                      ' DO slave module, MechatroLink III AXT, OUT 32-Channel  NPN
Public Const AXT_SIO_RDB32MLIII = &H72                      ' DB slave module, MechatroLink III AXT, IN 16-Channel, OUT 16-Channel  NPN
Public Const AXT_SIO_RDI32MSMLIII = &H73                    ' DI slave module, MechatroLink III M-SYSTEM, IN 32-Channel
Public Const AXT_SIO_RDO32AMSMLIII = &H74                   ' DO slave module, MechatroLink III M-SYSTEM, OUT 32-Channel
Public Const AXT_SIO_RDI32PMLIII = &H75                     ' DI slave module, MechatroLink III AXT, IN 32-Channel PNP
Public Const AXT_SIO_RDO32PMLIII = &H76                     ' DO slave module, MechatroLink III AXT, OUT 32-Channel  PNP
Public Const AXT_SIO_RDB32PMLIII = &H77                     ' DB slave module, MechatroLink III AXT, IN 16-Channel, OUT 16-Channel  PNP
Public Const AXT_SIO_RDB32PMLIII = &H78                     ' DI slave module, MechatroLink III M-SYSTEM, IN 16-Channel
Public Const AXT_SIO_UNDEFINEMLIII = &H79                   ' IO slave module, MechatroLink III Any, Max. IN 480-Channel, Max. OUT 480-Channel
Public Const AXT_SIO_RDI32MLIIISFA = &H7A                   ' DI slave module, MechatroLink III AXT(SFA), IN 32-Channel NPN
Public Const AXT_SIO_RDO32MLIIISFA = &H7B                   ' DO slave module, MechatroLink III AXT(SFA), OUT 32-Channel  NPN
Public Const AXT_SIO_RDB32MLIIISFA = &H7C                   ' DB slave module, MechatroLink III AXT(SFA), IN 16-Channel, OUT 16-Channel  NPN
Public Const AXT_SIO_RDB128MLIIIAI = &H7D                   ' Intelligent I/O (Product by IAI), For MLII only
Public Const AXT_SIO_RSIMPLEIOMLII = &H7E                   ' Digital IN/Out xxï¿½ï¿½, Simple I/O sereies, MLII ï¿½ï¿½ï¿½ï¿½.
Public Const AXT_SIO_RDO16AMLIII = &H7F                     ' DO slave module, MechatroLink III M-SYSTEM, OUT 16-Channel, NPN
Public Const AXT_SIO_RDI16MLII = &H80                       ' DISCRETE INPUT MODULE, 16 points (Product by M-SYSTEM), For MLII only
Public Const AXT_SIO_RDO16AMLII = &H81                      ' NPN TRANSISTOR OUTPUT MODULE, 16 points (Product by M-SYSTEM), For MLII only
Public Const AXT_SIO_RDO16BMLII = &H82                      ' PNP TRANSISTOR OUTPUT MODULE, 16 points (Product by M-SYSTEM), For MLII only
Public Const AXT_SIO_RDB96MLII = &H83                       ' Digital IN/OUT(Selectable), MAX 96 points, For MLII only
Public Const AXT_SIO_RDO32RTEX = &H84                       ' Digital OUT  32??
Public Const AXT_SIO_RDI32RTEX = &H85                       ' Digital IN  32??
Public Const AXT_SIO_RDB32RTEX = &H86                       ' Digital IN/OUT  32??
Public Const AXT_SIO_RDO16BMLIII = &H8A                     ' DO slave module, MechatroLink III M-SYSTEM, OUT 16-Channel, PNP
Public Const AXT_SIO_RDB32ML2NT1 = &H8B                     ' DB slave module, MechatroLink2 AJINEXTEK NT1 Series
Public Const AXT_SIO_RDB128YSMLIII = &H8C                   ' IO slave module, MechatroLink III Any, Max. IN 480-Channel, Max. OUT 480-Channel
Public Const AXT_SIO_DI32_P = &H92                          ' Digital IN  32?? PNP type(source type)
Public Const AXT_SIO_DO32T_P = &H93                         ' Digital OUT 32?? Power TR, PNT type(source type)
Public Const AXT_SIO_RDB128MLII = &H94                      ' Digital IN 64??/ OUT 64?? MLII ?„ìš©(JEPMC-IO2310)
Public Const AXT_SIO_RDI32 = &H95                           ' Digital IN  32?? For RTEX only
Public Const AXT_SIO_RDO32 = &H96                           ' Digital OUT 32?? For RTEX only
Public Const AXT_SIO_DI32 = &H97                            ' Digital IN  32??
Public Const AXT_SIO_DO32P = &H98                           ' Digital OUT 32??
Public Const AXT_SIO_DB32P = &H99                           ' Digital IN 16??/ OUT 16??
Public Const AXT_SIO_RDB32T = &H9A                          ' Digital IN 16??/ OUT 16?? For RTEX only
Public Const AXT_SIO_DO32T = &H9E                           ' Digital OUT 16?? Power TR ì¶œë ¥
Public Const AXT_SIO_DB32T = &H9F                           ' Digital IN 16??/ OUT 16?? Power TR ì¶œë ¥
Public Const AXT_SIO_AI4RB = &HA1                           ' A1h(161) : AI 4Ch, 12 bit
Public Const AXT_SIO_AO4RB = &HA2                           ' A2h(162) : AO 4Ch, 12 bit
Public Const AXT_SIO_AI16H = &HA3                           ' A3h(163) : AI 4Ch, 16 bit
Public Const AXT_SIO_AO8H = &HA4                            ' A4h(164) : AO 4Ch, 16 bit
Public Const AXT_SIO_AI16HB = &HA5                          ' A5h(165) : AI 16Ch, 16 bit (SIO-AI16HR(input module))
Public Const AXT_SIO_AO2HB = &HA6                           ' A6h(166) : AO 2Ch, 16 bit  (SIO-AI16HR(output module))
Public Const AXT_SIO_RAI8RB = &HA7                          ' A1h(167) : AI 8Ch, 16 bit, For RTEX only
Public Const AXT_SIO_RAO4RB = &HA8                          ' A2h(168) : AO 4Ch, 16 bit, For RTEX only
Public Const AXT_SIO_RAI4MLII = &HA9                        ' A9h(169) : AI 4Ch, 16 bit, For MLII only
Public Const AXT_SIO_RAI16RB = &HA0                         ' A0h(160) : AI 16Ch, 16 bit, For RTEX only
Public Const AXT_SIO_RAO2MLII = &HAA                        ' AAh(170) : AO 2Ch, 16 bit, For MLII only
Public Const AXT_SIO_RAVCI4MLII = &HAB                      ' DC VOLTAGE/CURRENT INPUT MODULE, 4 points (Product by M-SYSTEM), For MLII only
Public Const AXT_SIO_RAVO2MLII = &HAC                       ' DC VOLTAGE OUTPUT MODULE, 2 points (Product by M-SYSTEM), For MLII only
Public Const AXT_SIO_RACO2MLII = &HAD                       ' DC CURRENT OUTPUT MODULE, 2 points (Product by M-SYSTEM), For MLII only
Public Const AXT_SIO_RATI4MLII = &HAE                       ' THERMOCOUPLE INPUT MODULE, 4 points (Product by M-SYSTEM), For MLII only
Public Const AXT_SIO_RARTDI4MLII = &HAF                     ' RTD INPUT MODULE, 4 points (Product by M-SYSTEM), For MLII only
Public Const AXT_SIO_RCNT2MLII = &HB0                       ' Counter Module Reversible counter, 2 channels (Product by YASKWA)
Public Const AXT_SIO_CN2CH = &HB1                           ' Counter Module, 2 channels, Remapped ID, Actual ID is (0xA8)
Public Const AXT_SIO_RCNT2RTEX = &HB2                       ' Counter slave module, Reversible counter, 2 channels, For RTEX Only
Public Const AXT_SIO_RCNT2MLIII = &HB3                      ' Counter slave moudle, MechatroLink III AXT, 2 ch, Trigger per channel
Public Const AXT_SIO_RHPC4MLIII = &HB4                      ' Counter slave moudle, MechatroLink III AXT, 4 ch
Public Const AXT_SIO_RAI16RTEX = &HC0                       ' ANALOG VOLTAGE INPUT(+- 10V) 16 Channel RTEX
Public Const AXT_SIO_RAO08RTEX = &HC1                       ' ANALOG VOLTAGE OUTPUT(+- 10V) 08 Channel RTEX
Public Const AXT_SIO_RAI8MLIII = &HC2                       ' AI slave module, MechatroLink III AXT, Analog IN 8ch, 16 bit
Public Const AXT_SIO_RAI16MLIII = &HC3                      ' AI slave module, MechatroLink III AXT, Analog IN 16ch, 16 bit
Public Const AXT_SIO_RAO4MLIII = &HC4                       ' A0 slave module, MechatroLink III AXT, Analog OUT 4ch, 16 bit
Public Const AXT_SIO_RAO8MLIII = &HC5                       ' A0 slave module, MechatroLink III AXT, Analog OUT 8ch, 16 bit
Public Const AXT_SIO_RAVO4MLII = &HC6                       ' DC VOLTAGE OUTPUT MODULE, 4 points (Product by M-SYSTEM), For MLII only
Public Const AXT_SIO_RAV04MLIII = &HC7                      ' AO Slave module, MechatroLink III M-SYSTEM Voltage output module
Public Const AXT_SIO_RAVI4MLIII = &HC8                      ' AI Slave module, MechatroLink III M-SYSTEM Voltage/Current input module
Public Const AXT_SIO_RAI16MLIIISFA = &HC9                   ' AI slave module, MechatroLink III AXT(SFA), Analog IN 16ch, 16 bit
Public Const AXT_SIO_RDB32MSMLIII = &HCA                    ' DIO slave module, MechatroLink III M-SYSTEM, IN 16-Channel, OUT 16-Channel
Public Const AXT_COM_234R = &HD3                            ' COM-234R
Public Const AXT_COM_484R = &HD4                            ' COM-484R
Public Const AXT_SIO_RPI2 = &HD5                            ' Pulse counter module(JEPMC-2900)
Public Const AXT_SIO_HPC4 = &HD6                            ' External Encoder module for 4Channel with Trigger function.
Public Const AXT_SIO_AO4F = &HD7                            ' AO 4Ch, 16 bit
Public Const AXT_SIO_AI8F = &HD8                            ' AI 8Ch, 16 bit
Public Const AXT_SIO_AI8AO4F = &HD9                         ' AI 8Ch, AO 4Ch, 16 bit

' Define Function Result
Public Const AXT_RT_SUCCESS = 0                             ' API ?¨ìˆ˜ ?˜í–‰ ?±ê³µ
Public Const AXT_RT_OPEN_ERROR = 1001                       ' ?¼ì´ë¸ŒëŸ¬ë¦??¤í”ˆ ?˜ì??ŠìŒ
Public Const AXT_RT_OPEN_ALREADY = 1002                     ' ?¼ì´ë¸ŒëŸ¬ë¦??¤í”ˆ ?˜ì–´?ˆê³  ?¬ìš© ì¤‘ì„
Public Const AXT_RT_NOT_OPEN = 1053                         ' ?¼ì´ë¸ŒëŸ¬ë¦?ì´ˆê¸°???¤íŒ¨
Public Const AXT_RT_NOT_SUPPORT_VERSION = 1054              ' ì§€?í•˜ì§€?ŠëŠ” ?˜ë“œ?¨ì–´
Public Const AXT_RT_LOCK_FILE_MISMATCH = 1055               ' Lock?Œì¼ê³??„ì¬ Scan?•ë³´ê°€ ?¼ì¹˜?˜ì? ?ŠìŒ

Public Const AXT_RT_INVALID_BOARD_NO = 1101                 ' ? íš¨?˜ì? ?ŠëŠ” ë³´ë“œ ë²ˆí˜¸
Public Const AXT_RT_INVALID_MODULE_POS = 1102               ' ? íš¨?˜ì? ?ŠëŠ” ëª¨ë“ˆ ?„ì¹˜
Public Const AXT_RT_INVALID_LEVEL = 1103                    ' ? íš¨?˜ì? ?ŠëŠ” ?ˆë²¨
Public Const AXT_RT_INVALID_VARIABLE = 1104                 ' ? íš¨?˜ì? ?ŠëŠ” ë³€??
Public Const AXT_RT_ERROR_VERSION_READ = 1151               ' ?¼ì´ë¸ŒëŸ¬ë¦?ë²„ì „???½ì„???†ìŒ
Public Const AXT_RT_NETWORK_ERROR = 1152                    ' ?˜ë“œ?¨ì–´ ?¤íŠ¸?Œí¬ ?ëŸ¬
Public Const AXT_RT_NETWORK_LOCK_MISMATCH = 1153            ' ë³´ë“œ Lock?•ë³´?€ ?„ì¬ Scan?•ë³´ê°€ ?¼ì¹˜?˜ì? ?ŠìŒ

Public Const AXT_RT_1ST_BELOW_MIN_VALUE = 1160              ' ì²«ë²ˆì§??¸ìê°’ì´ ìµœì†Œê°’ë³´?????‘ìŒ
Public Const AXT_RT_1ST_ABOVE_MAX_VALUE = 1161              ' ì²«ë²ˆì§??¸ìê°’ì´ ìµœë?ê°’ë³´??????
Public Const AXT_RT_2ND_BELOW_MIN_VALUE = 1170              ' ?ë²ˆì§??¸ìê°’ì´ ìµœì†Œê°’ë³´?????‘ìŒ
Public Const AXT_RT_2ND_ABOVE_MAX_VALUE = 1171              ' ?ë²ˆì§??¸ìê°’ì´ ìµœë?ê°’ë³´??????
Public Const AXT_RT_3RD_BELOW_MIN_VALUE = 1180              ' ?¸ë²ˆì§??¸ìê°’ì´ ìµœì†Œê°’ë³´?????‘ìŒ
Public Const AXT_RT_3RD_ABOVE_MAX_VALUE = 1181              ' ?¸ë²ˆì§??¸ìê°’ì´ ìµœë?ê°’ë³´??????
Public Const AXT_RT_4TH_BELOW_MIN_VALUE = 1190              ' ?¤ë²ˆì§??¸ìê°’ì´ ìµœì†Œê°’ë³´?????‘ìŒ
Public Const AXT_RT_4TH_ABOVE_MAX_VALUE = 1191              ' ?¤ë²ˆì§??¸ìê°’ì´ ìµœë?ê°’ë³´??????
Public Const AXT_RT_5TH_BELOW_MIN_VALUE = 1200              ' ?¤ì„¯ë²ˆì§¸ ?¸ìê°’ì´ ìµœì†Œê°’ë³´?????‘ìŒ
Public Const AXT_RT_5TH_ABOVE_MAX_VALUE = 1201              ' ?¤ì„¯ë²ˆì§¸ ?¸ìê°’ì´ ìµœë?ê°’ë³´??????
Public Const AXT_RT_6TH_BELOW_MIN_VALUE = 1210              ' ?¬ì„¯ë²ˆì§¸ ?¸ìê°’ì´ ìµœì†Œê°’ë³´?????‘ìŒ
Public Const AXT_RT_6TH_ABOVE_MAX_VALUE = 1211              ' ?¬ì„¯ë²ˆì§¸ ?¸ìê°’ì´ ìµœë?ê°’ë³´??????
Public Const AXT_RT_7TH_BELOW_MIN_VALUE = 1220              ' ?¼ê³±ë²ˆì§¸ ?¸ìê°’ì´ ìµœì†Œê°’ë³´?????‘ìŒ
Public Const AXT_RT_7TH_ABOVE_MAX_VALUE = 1221              ' ?¼ê³±ë²ˆì§¸ ?¸ìê°’ì´ ìµœë?ê°’ë³´??????
Public Const AXT_RT_8TH_BELOW_MIN_VALUE = 1230              ' ?¬ëŸë²ˆì§¸ ?¸ìê°’ì´ ìµœì†Œê°’ë³´?????‘ìŒ
Public Const AXT_RT_8TH_ABOVE_MAX_VALUE = 1231              ' ?¬ëŸë²ˆì§¸ ?¸ìê°’ì´ ìµœë?ê°’ë³´??????
Public Const AXT_RT_9TH_BELOW_MIN_VALUE = 1240              ' ?„í™‰ë²ˆì§¸ ?¸ìê°’ì´ ìµœì†Œê°’ë³´?????‘ìŒ
Public Const AXT_RT_9TH_ABOVE_MAX_VALUE = 1241              ' ?„í™‰ë²ˆì§¸ ?¸ìê°’ì´ ìµœë?ê°’ë³´??????
Public Const AXT_RT_10TH_BELOW_MIN_VALUE = 1250             ' ?´ë²ˆì§??¸ìê°’ì´ ìµœì†Œê°’ë³´?????‘ìŒ
Public Const AXT_RT_10TH_ABOVE_MAX_VALUE = 1251             ' ?´ë²ˆì§??¸ìê°’ì´ ìµœë?ê°’ë³´??????

Public Const AXT_RT_AIO_OPEN_ERROR = 2001                   ' AIO ëª¨ë“ˆ ?¤í”ˆ?¤íŒ¨
Public Const AXT_RT_AIO_NOT_MODULE = 2051                   ' AIO ëª¨ë“ˆ ?†ìŒ
Public Const AXT_RT_AIO_NOT_EVENT = 2052                    ' AIO ?´ë²¤???½ì? ëª»í•¨
Public Const AXT_RT_AIO_INVALID_MODULE_NO = 2101            ' ? íš¨?˜ì??Šì? AIOëª¨ë“ˆ
Public Const AXT_RT_AIO_INVALID_CHANNEL_NO = 2102           ' ? íš¨?˜ì??Šì? AIOì±„ë„ë²ˆí˜¸
Public Const AXT_RT_AIO_INVALID_USE = 2106                  ' AIO ?¨ìˆ˜ ?¬ìš©ëª»í•¨
Public Const AXT_RT_AIO_INVALID_TRIGGER_MODE = 2107         ' ? íš¨?˜ì??ŠëŠ” ?¸ë¦¬ê±?ëª¨ë“œ
Public Const AXT_RT_AIO_EXTERNAL_DATA_EMPTY = 2108

Public Const AXT_RT_DIO_OPEN_ERROR = 3001                   ' DIO ëª¨ë“ˆ ?¤í”ˆ?¤íŒ¨
Public Const AXT_RT_DIO_NOT_MODULE = 3051                   ' DIO ëª¨ë“ˆ ?†ìŒ
Public Const AXT_RT_DIO_NOT_INTERRUPT = 3052                ' DIO ?¸í„°?½íŠ¸ ?¤ì •?ˆë¨
Public Const AXT_RT_DIO_INVALID_MODULE_NO = 3101            ' ? íš¨?˜ì??ŠëŠ” DIO ëª¨ë“ˆ ë²ˆí˜¸
Public Const AXT_RT_DIO_INVALID_OFFSET_NO = 3102            ' ? íš¨?˜ì??ŠëŠ” DIO OFFSET ë²ˆí˜¸
Public Const AXT_RT_DIO_INVALID_LEVEL = 3103                ' ? íš¨?˜ì??ŠëŠ” DIO ?ˆë²¨
Public Const AXT_RT_DIO_INVALID_MODE = 3104                 ' ? íš¨?˜ì??ŠëŠ” DIO ëª¨ë“œ
Public Const AXT_RT_DIO_INVALID_VALUE = 3105                ' ? íš¨?˜ì??ŠëŠ” ê°??¤ì •
Public Const AXT_RT_DIO_INVALID_USE = 3106                  ' DIO ?¨ìˆ˜ ?¬ìš©ëª»í•¨

Public Const AXT_RT_CNT_OPEN_ERROR = 3201                   ' CNT ëª¨ë“ˆ ?¤í”ˆ?¤íŒ¨
Public Const AXT_RT_CNT_NOT_MODULE = 3251                   ' CNT ëª¨ë“ˆ ?†ìŒ
Public Const AXT_RT_CNT_NOT_INTERRUPT = 3252                ' CNT ?¸í„°?½íŠ¸ ?¤ì •?ˆë¨
Public Const AXT_RT_CNT_INVALID_MODULE_NO = 3301            ' ? íš¨?˜ì??ŠëŠ” CNT ëª¨ë“ˆ ë²ˆí˜¸
Public Const AXT_RT_CNT_INVALID_CHANNEL_NO = 3302           ' ? íš¨?˜ì??ŠëŠ” ì±„ë„ ë²ˆí˜¸
Public Const AXT_RT_CNT_INVALID_OFFSET_NO = 3303            ' ? íš¨?˜ì??ŠëŠ” CNT OFFSET ë²ˆí˜¸
Public Const AXT_RT_CNT_INVALID_LEVEL = 3304                ' ? íš¨?˜ì??ŠëŠ” CNT ?ˆë²¨
Public Const AXT_RT_CNT_INVALID_MODE = 3305                 ' ? íš¨?˜ì??ŠëŠ” CNT ëª¨ë“œ
Public Const AXT_RT_CNT_INVALID_VALUE = 3306                ' ? íš¨?˜ì??ŠëŠ” ê°??¤ì •
Public Const AXT_RT_CNT_INVALID_USE = 3307                  ' CNT ?¨ìˆ˜ ?¬ìš©ëª»í•¨

Public Const AXT_RT_MOTION_OPEN_ERROR = 4001                ' ëª¨ì…˜ ?¼ì´ë¸ŒëŸ¬ë¦?Open ?¤íŒ¨
Public Const AXT_RT_MOTION_NOT_MODULE = 4051                ' ?œìŠ¤?œì— ?¥ì°©??ëª¨ì…˜ ëª¨ë“ˆ???†ìŒ
Public Const AXT_RT_MOTION_NOT_INTERRUPT = 4052             ' ?¸í„°?½íŠ¸ ê²°ê³¼ ?½ê¸° ?¤íŒ¨
Public Const AXT_RT_MOTION_NOT_INITIAL_AXIS_NO = 4053       ' ?´ë‹¹ ì¶?ëª¨ì…˜ ì´ˆê¸°???¤íŒ¨
Public Const AXT_RT_MOTION_NOT_IN_CONT_INTERPOL = 4054      ' ?°ì† ë³´ê°„ êµ¬ë™ ì¤‘ì´ ?„ë‹Œ ?íƒœ?ì„œ ?°ì†ë³´ê°„ ì¤‘ì? ëª…ë ¹???˜í–‰ ?˜ì???
Public Const AXT_RT_MOTION_NOT_PARA_READ = 4055             ' ?ì  êµ¬ë™ ?¤ì • ?Œë¼ë¯¸í„° ë¡œë“œ ?¤íŒ¨
Public Const AXT_RT_MOTION_INVALID_AXIS_NO = 4101           ' ?´ë‹¹ ì¶•ì´ ì¡´ì¬?˜ì? ?ŠìŒ
Public Const AXT_RT_MOTION_INVALID_METHOD = 4102            ' ?´ë‹¹ ì¶?êµ¬ë™???„ìš”???¤ì •???˜ëª»??
Public Const AXT_RT_MOTION_INVALID_USE = 4103               ' 'uUse' ?¸ìê°’ì´ ?˜ëª» ?¤ì •??
Public Const AXT_RT_MOTION_INVALID_LEVEL = 4104             ' 'uLevel' ?¸ìê°’ì´ ?˜ëª» ?¤ì •??
Public Const AXT_RT_MOTION_INVALID_BIT_NO = 4105            ' ë²”ìš© ?…ì¶œ???´ë‹¹ ë¹„íŠ¸ê°€ ?˜ëª» ?¤ì •??
Public Const AXT_RT_MOTION_INVALID_STOP_MODE = 4106         ' ëª¨ì…˜ ?•ì? ëª¨ë“œ ?¤ì •ê°’ì´ ?˜ëª»??
Public Const AXT_RT_MOTION_INVALID_TRIGGER_MODE = 4107      ' ?¸ë¦¬ê±??¤ì • ëª¨ë“œê°€ ?˜ëª» ?¤ì •??
Public Const AXT_RT_MOTION_INVALID_TRIGGER_LEVEL = 4108     ' ?¸ë¦¬ê±?ì¶œë ¥ ?ˆë²¨ ?¤ì •???˜ëª»??
Public Const AXT_RT_MOTION_INVALID_SELECTION = 4109         ' 'uSelection' ?¸ìê°€ COMMAND ?ëŠ” ACTUAL ?´ì™¸??ê°’ìœ¼ë¡??¤ì •?˜ì–´ ?ˆìŒ
Public Const AXT_RT_MOTION_INVALID_TIME = 4110              ' Trigger ì¶œë ¥ ?œê°„ê°’ì´ ?˜ëª» ?¤ì •?˜ì–´ ?ˆìŒ
Public Const AXT_RT_MOTION_INVALID_FILE_LOAD = 4111         ' ëª¨ì…˜ ?¤ì •ê°’ì´ ?€?¥ëœ ?Œì¼??ë¡œë“œê°€ ?ˆë¨
Public Const AXT_RT_MOTION_INVALID_FILE_SAVE = 4112         ' ëª¨ì…˜ ?¤ì •ê°’ì„ ?€?¥í•˜???Œì¼ ?€?¥ì— ?¤íŒ¨??
Public Const AXT_RT_MOTION_INVALID_VELOCITY = 4113          ' ëª¨ì…˜ êµ¬ë™ ?ë„ê°’ì´ 0?¼ë¡œ ?¤ì •?˜ì–´ ëª¨ì…˜ ?ëŸ¬ ë°œìƒ
Public Const AXT_RT_MOTION_INVALID_ACCELTIME = 4114         ' ëª¨ì…˜ êµ¬ë™ ê°€???œê°„ê°’ì´ 0?¼ë¡œ ?¤ì •?˜ì–´ ëª¨ì…˜ ?ëŸ¬ ë°œìƒ
Public Const AXT_RT_MOTION_INVALID_PULSE_VALUE = 4115       ' ëª¨ì…˜ ?¨ìœ„ ?¤ì • ???…ë ¥ ?„ìŠ¤ê°’ì´ 0ë³´ë‹¤ ?‘ì?ê°’ìœ¼ë¡??¤ì •??
Public Const AXT_RT_MOTION_INVALID_NODE_NUMBER = 4116       ' ?„ì¹˜???ë„ ?¤ë²„?¼ì´???¨ìˆ˜ê°€ ëª¨ì…˜ ?•ì? ì¤‘ì— ?¤í–„??
Public Const AXT_RT_MOTION_INVALID_TARGET = 4117            ' ?¤ì¶• ëª¨ì…˜ ?•ì? ?ì¸??ê´€???Œë˜ê·¸ë? ë°˜í™˜?œë‹¤.

Public Const AXT_RT_MOTION_ERROR_IN_NONMOTION = 4151        ' ëª¨ì…˜ êµ¬ë™ì¤‘ì´?´ì•¼ ?˜ëŠ”??ëª¨ì…˜ êµ¬ë™ì¤‘ì´ ?„ë‹ ??
Public Const AXT_RT_MOTION_ERROR_IN_MOTION = 4152           ' ëª¨ì…˜ êµ¬ë™ ì¤‘ì— ?¤ë¥¸ ëª¨ì…˜ êµ¬ë™ ?¨ìˆ˜ë¥??¤í–‰??
Public Const AXT_RT_MOTION_ERROR = 4153                     ' ?¤ì¶• êµ¬ë™ ?•ì? ?¨ìˆ˜ ?¤í–‰ ì¤??ëŸ¬ ë°œìƒ??
Public Const AXT_RT_MOTION_ERROR_GANTRY_ENABLE = 4154       ' ê²íŠ¸ë¦?enable???˜ì–´?ˆì–´ ëª¨ì…˜ì¤‘ì¼ ????ê²íŠ¸ë¦?enable???Œë?????
Public Const AXT_RT_MOTION_ERROR_GANTRY_AXIS = 4155         ' ê²íŠ¸ë¦?ì¶•ì´ ë§ˆìŠ¤?°ì±„??ì¶? ë²ˆí˜¸(0 ~ (ìµœë?ì¶•ìˆ˜ - 1))ê°€ ?˜ëª» ?¤ì–´ê°”ì„ ??
Public Const AXT_RT_MOTION_ERROR_MASTER_SERVOON = 4156      ' ë§ˆìŠ¤??ì¶??œë³´?¨ì´ ?ˆë˜?´ìˆ????
Public Const AXT_RT_MOTION_ERROR_SLAVE_SERVOON = 4157       ' ?¬ë ˆ?´ë¸Œ ì¶??œë³´?¨ì´ ?ˆë˜?´ìˆ????
Public Const AXT_RT_MOTION_INVALID_POSITION = 4158          ' ? íš¨???„ì¹˜???†ì„ ??
Public Const AXT_RT_ERROR_NOT_SAME_MODULE = 4159            ' ??ê°™ì? ëª¨ë“ˆ?´ì— ?ˆì? ?Šì„ê²½ìš°
Public Const AXT_RT_ERROR_NOT_SAME_BOARD = 4160             ' ??ê°™ì? ë³´ë“œ?´ì— ?ˆì? ?„ë‹ê²½ìš°
Public Const AXT_RT_ERROR_NOT_SAME_PRODUCT = 4161           ' ?œí’ˆ???œë¡œ ?¤ë?ê²½ìš°
Public Const AXT_RT_NOT_CAPTURED = 4162                     ' ?„ì¹˜ê°€ ?€?¥ë˜ì§€ ?Šì„ ??
Public Const AXT_RT_ERROR_NOT_SAME_IC = 4163                ' ê°™ì? ì¹©ë‚´??ì¡´ì¬?˜ì??Šì„ ??
Public Const AXT_RT_ERROR_NOT_GEARMODE = 4164               ' ê¸°ì–´ëª¨ë“œë¡?ë³€?˜ì´ ?ˆë  ??
Public Const AXT_ERROR_CONTI_INVALID_AXIS_NO = 4165         ' ?°ì†ë³´ê°„ ì¶•ë§µ????? íš¨??ì¶•ì´ ?„ë‹ ??
Public Const AXT_ERROR_CONTI_INVALID_MAP_NO = 4166          ' ?°ì†ë³´ê°„ ë§µí•‘ ??? íš¨??ë§µí•‘ ë²ˆí˜¸ê°€ ?„ë‹ ??
Public Const AXT_ERROR_CONTI_EMPTY_MAP_NO = 4167            ' ?°ì†ë³´ê°„ ë§µí•‘ ë²ˆí˜¸ê°€ ë¹„ì›Œ ?ˆì„ ??
Public Const AXT_RT_MOTION_ERROR_CACULATION = 4168          ' ê³„ì‚°?ì˜ ?¤ì°¨ê°€ ë°œìƒ?ˆì„ ??
Public Const AXT_RT_ERROR_MOVE_SENSOR_CHECK = 4169          ' ?°ì†ë³´ê°„ êµ¬ë™???ëŸ¬?¼ì„œê°€(Alarm, EMG, Limit?? ê°ì??œê²½??

Public Const AXT_ERROR_HELICAL_INVALID_AXIS_NO = 4170       ' ?¬ë¦¬ì»?ì¶?ë§µí•‘ ??? íš¨??ì¶•ì´ ?„ë‹ ??
Public Const AXT_ERROR_HELICAL_INVALID_MAP_NO = 4171        ' ?¬ë¦¬ì»?ë§µí•‘ ??? íš¨??ë§µí•‘ ë²ˆí˜¸ê°€ ?„ë‹  ??
Public Const AXT_ERROR_HELICAL_EMPTY_MAP_NO = 4172          ' ?¬ë¦¬ì»?ë©¥í•‘ ë²ˆí˜¸ê°€ ë¹„ì›Œ ?ˆì„ ??

Public Const AXT_ERROR_SPLINE_INVALID_AXIS_NO = 4180        ' ?¤í”Œ?¼ì¸ ì¶?ë§µí•‘ ??? íš¨??ì¶•ì´ ?„ë‹ ??
Public Const AXT_ERROR_SPLINE_INVALID_MAP_NO = 4181         ' ?¤í”Œ?¼ì¸ ë§µí•‘ ??? íš¨??ë§µí•‘ ë²ˆí˜¸ê°€ ?„ë‹ ??
Public Const AXT_ERROR_SPLINE_EMPTY_MAP_NO = 4182           ' ?¤í”Œ?¼ì¸ ë§µí•‘ ë²ˆí˜¸ê°€ ë¹„ì›Œ?ˆì„ ??
Public Const AXT_ERROR_SPLINE_NUM_ERROR = 4183              ' ?¤í”Œ?¼ì¸ ?ìˆ«?ê? ë¶€?ë‹¹????
Public Const AXT_RT_MOTION_INTERPOL_VALUE = 4184            ' ë³´ê°„?????…ë ¥ ê°’ì´ ?˜ëª»?£ì–´ì¡Œì„ ??
Public Const AXT_RT_ERROR_NOT_CONTIBEGIN = 4185             ' ?°ì†ë³´ê°„ ????CONTIBEGIN?¨ìˆ˜ë¥??¸ì¶œ?˜ì? ?Šì„ ??
Public Const AXT_RT_ERROR_NOT_CONTIEND = 4186               ' ?°ì†ë³´ê°„ ????CONTIEND?¨ìˆ˜ë¥??¸ì¶œ?˜ì? ?Šì„ ??

Public Const AXT_RT_MOTION_HOME_SEARCHING = 4201            ' ?ˆì„ ì°¾ê³  ?ˆëŠ” ì¤‘ì¼ ???¤ë¥¸ ëª¨ì…˜ ?¨ìˆ˜?¤ì„ ?¬ìš©????
Public Const AXT_RT_MOTION_HOME_ERROR_SEARCHING = 4202      ' ?ˆì„ ì°¾ê³  ?ˆëŠ” ì¤‘ì¼ ???¸ë??ì„œ ?¬ìš©?ë‚˜ ?¹ì? ?´ë–¤ê²ƒì— ?˜í•œ  ê°•ì œë¡??•ì??¹í•  ??
Public Const AXT_RT_MOTION_HOME_ERROR_START = 4203          ' ì´ˆê¸°??ë¬¸ì œë¡??ˆì‹œ??ë¶ˆê?????
Public Const AXT_RT_MOTION_HOME_ERROR_GANTRY = 4204         ' ?ˆì„ ì°¾ê³  ?ˆëŠ” ì¤‘ì¼ ??ê²íŠ¸ë¦?enable ë¶ˆê?????

Public Const AXT_RT_MOTION_READ_ALARM_WAITING = 4210        ' ?œë³´?©ìœ¼ë¡œë????ŒëŒì½”ë“œ ê²°ê³¼ë¥?ê¸°ë‹¤ë¦¬ëŠ” ì¤?
Public Const AXT_RT_MOTION_READ_ALARM_NO_REQUEST = 4211     ' ?œë³´?©ì— ?ŒëŒì½”ë“œ ë°˜í™˜ ëª…ë ¹???´ë ¤ì§€ì§€?Šì•˜????
Public Const AXT_RT_MOTION_READ_ALARM_TIMEOUT = 4212        ' ?œë³´???ŒëŒ?½ê¸° ?œê°„ì´ˆê³¼ ?ˆì„??1sec?´ìƒ)
Public Const AXT_RT_MOTION_READ_ALARM_FAILED = 4213         ' ?œë³´???ŒëŒ?½ê¸°???¤íŒ¨ ?ˆì„ ??
Public Const AXT_RT_MOTION_READ_ALARM_UNKNOWN = 4220        ' ?ŒëŒì½”ë“œê°€ ?Œìˆ˜?†ëŠ” ì½”ë“œ????
Public Const AXT_RT_MOTION_READ_ALARM_FILES = 4221          ' ?ŒëŒ?•ë³´ ?Œì¼???•í•´ì§„ìœ„ì¹˜ì— ì¡´ì¬?˜ì? ?Šì„ ??

Public Const AXT_RT_MOTION_POSITION_OUTOFBOUND = 4251       ' ?¤ì •???„ì¹˜ê°’ì´ ?¤ì • ìµœë?ê°’ë³´???¬ê±°??ìµœì†Œê°’ë³´???‘ì?ê°’ì„
Public Const AXT_RT_MOTION_PROFILE_INVALID = 4252           ' êµ¬ë™ ?ë„ ?„ë¡œ?Œì¼ ?¤ì •???˜ëª»??
Public Const AXT_RT_MOTION_VELOCITY_OUTOFBOUND = 4253       ' êµ¬ë™ ?ë„ê°’ì´ ìµœë?ê°’ë³´???¬ê²Œ ?¤ì •??
Public Const AXT_RT_MOTION_MOVE_UNIT_IS_ZERO = 4254         ' êµ¬ë™ ?¨ìœ„ê°’ì´ 0?¼ë¡œ ?¤ì •??
Public Const AXT_RT_MOTION_SETTING_ERROR = 4255             ' ?ë„, ê°€?ë„, ?€?? ?„ë¡œ?Œì¼ ?¤ì •???˜ëª»??
Public Const AXT_RT_MOTION_IN_CONT_INTERPOL = 4256          ' ?°ì† ë³´ê°„ êµ¬ë™ ì¤?êµ¬ë™ ?œì‘ ?ëŠ” ?¬ì‹œ???¨ìˆ˜ë¥??¤í–‰?˜ì???
Public Const AXT_RT_MOTION_DISABLE_TRIGGER = 4257           ' ?¸ë¦¬ê±?ì¶œë ¥??Disable ?íƒœ??
Public Const AXT_RT_MOTION_INVALID_CONT_INDEX = 4258        ' ?°ì† ë³´ê°„ Indexê°??¤ì •???˜ëª»??
Public Const AXT_RT_MOTION_CONT_QUEUE_FULL = 4259           ' ëª¨ì…˜ ì¹©ì˜ ?°ì† ë³´ê°„ ?ê? Full ?íƒœ??
Public Const AXT_RT_PROTECTED_DURING_SERVOON = 4260         ' ?œë³´ ???˜ì–´ ?ˆëŠ” ?íƒœ?ì„œ ?¬ìš© ëª???
Public Const AXT_RT_HW_ACCESS_ERROR = 4261                  ' ë©”ëª¨ë¦?Read / Write ?¤íŒ¨

Public Const AXT_RT_HW_DPRAM_CMD_WRITE_ERROR_LV1 = 4262     ' DPRAM Comamnd Write ?¤íŒ¨ Level1
Public Const AXT_RT_HW_DPRAM_CMD_WRITE_ERROR_LV2 = 4263     ' DPRAM Comamnd Write ?¤íŒ¨ Level2
Public Const AXT_RT_HW_DPRAM_CMD_WRITE_ERROR_LV3 = 4264     ' DPRAM Comamnd Write ?¤íŒ¨ Level3
Public Const AXT_RT_HW_DPRAM_CMD_READ_ERROR_LV1 = 4265      ' DPRAM Comamnd Read ?¤íŒ¨ Level1
Public Const AXT_RT_HW_DPRAM_CMD_READ_ERROR_LV2 = 4266      ' DPRAM Comamnd Read ?¤íŒ¨ Level2
Public Const AXT_RT_HW_DPRAM_CMD_READ_ERROR_LV3 = 4267      ' DPRAM Comamnd Read ?¤íŒ¨ Level3

Public Const AXT_RT_COMPENSATION_SET_PARAM_FIRST = 4300
Public Const AXT_RT_COMPENSATION_NOT_INIT = 4301            ' ë³´ì •?Œì´ë¸?ê¸°ëŠ¥ ì´ˆê¸°???˜ì??ŠìŒ
Public Const AXT_RT_COMPENSATION_POS_OUTOFBOUND = 4302      ' ?„ì¹˜ ê°’ì´ ë²”ìœ„?´ì— ì¡´ì¬?˜ì? ?ŠìŒ
Public Const AXT_RT_COMPENSATION_BACKLASH_NOT_INIT = 4303   ' ë°±ë˜??ë³´ì •ê¸°ëŠ¥ ì´ˆê¸°???˜ì??ŠìŒ
Public Const AXT_RT_COMPENSATION_INVALID_ENTRY = 4304     

Public Const AXT_RT_SEQ_NOT_IN_SERVICE = 4400               ' ?œì°¨ êµ¬ë™ ?¨ìˆ˜ ?¤í–‰ ì¤??ì› ? ë‹¹ ?¤íŒ¨
Public Const AXT_ERROR_SEQ_INVALID_MAP_NO = 4401            ' ?œì°¨ êµ¬ë™ ?¨ìˆ˜ ?¤í–‰ ì¤?ë§µí•‘ ë²ˆí˜¸ ?´ìƒ.
Public Const AXT_ERROR_INVALID_AXIS_NO = 4402               ' ?¨ìˆ˜ ?¤ì • ?¸ìì¤?ì¶•ë²ˆ???´ìƒ.
Public Const AXT_RT_ERROR_NOT_SEQ_NODE_BEGIN = 4403         ' ?œì°¨ êµ¬ë™ ?¸ë“œ ?…ë ¥ ?œì‘ ?¨ìˆ˜ë¥??¸ì¶œ?˜ì? ?ŠìŒ.
Public Const AXT_RT_ERROR_NOT_SEQ_NODE_END = 4404           ' ?œì°¨ êµ¬ë™ ?¸ë“œ ?…ë ¥ ì¢…ë£Œ ?¨ìˆ˜ë¥??¸ì¶œ?˜ì? ?ŠìŒ.
Public Const AXT_RT_ERROR_NO_NODE = 4405                    ' ?œì°¨ êµ¬ë™ ?¸ë“œ ?…ë ¥???†ìŒ.
Public Const AXT_RT_ERROR_SEQ_STOP_TIMEOUT = 4406

Public Const AXT_RT_M3_COMMUNICATION_FAILED = 4500             ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_ONE_OF_AXES_IS_NOT_M3 = 4501        ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ML3 ï¿½ï¿½ï¿?ï¿½ß¿ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿?ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ 
Public Const AXT_RT_MOTION_BIGGER_VEL_THEN_MAX_VEL = 4502      ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ö´ï¿½ ï¿½Óµï¿½ï¿½ï¿½ï¿½ï¿½ Å­
Public Const AXT_RT_MOTION_SMALLER_VEL_THEN_MAX_VEL = 4503     ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ö´ï¿½ ï¿½Óµï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_ACCEL_MUST_BIGGER_THEN_ZERO = 4504  ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Óµï¿½ï¿½ï¿½ 0ï¿½ï¿½ï¿½ï¿½ Å­
Public Const AXT_RT_MOTION_SMALL_ACCEL_WITH_UNIT_PULSE = 4505  ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, UnitPulseï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½Óµï¿½ï¿½ï¿½ 0ï¿½ï¿½ï¿½ï¿½ Å­
Public Const AXT_RT_MOTION_INVALID_INPUT_ACCEL = 4506          ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Óµï¿½ ï¿½Ô·ï¿½ï¿½ï¿½ ï¿½ß¸ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_SMALL_DECEL_WITH_UNIT_PULSE = 4507  ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, UnitPulseï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½Óµï¿½ï¿½ï¿½ 0ï¿½ï¿½ï¿½ï¿½ Å­
Public Const AXT_RT_MOTION_INVALID_INPUT_DECEL = 4508          ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Óµï¿½ ï¿½Ô·ï¿½ï¿½ï¿½ ï¿½ß¸ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_SAME_START_AND_CENTER_POS = 4509    ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½È£ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ß½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_INVALID_JERK = 4510                 ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Å© ï¿½Ô·ï¿½ï¿½ï¿½ ï¿½ß¸ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_INVALID_INPUT_VALUE = 4511          ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ô·Â°ï¿½ï¿½ï¿½ ï¿½ß¸ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_NOT_SUPPORT_PROFILE = 4512          ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ê´ï¿½ ï¿½Óµï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_INPOS_UNUSED = 4513                 ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_AXIS_IN_SLAVE_STATE = 4514          ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ìºï¿½ ï¿½ï¿½ï¿½Â°ï¿½ ï¿½Æ´ï¿½
Public Const AXT_RT_MOTION_AXES_ARE_NOT_SAME_BOARD = 4515      ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_ERROR_IN_ALARM = 4516               ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ë¶ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_ERROR_IN_EMGN = 4517                ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_CAN_NOT_CHANGE_COORD_NO = 4518      ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½Úµï¿½ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½Ñ¹ï¿½ ï¿½ï¿½È¯ ï¿½Ò°ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_INVALID_INTERNAL_RADIOUS = 4519     ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½È£ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ X, Yï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½Ä¡
Public Const AXT_RT_MOTION_CONTI_QUEUE_FULL = 4521             ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ Å¥ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½
Public Const AXT_RT_MOTION_SAME_START_AND_END_POSITION = 4522  ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½È£ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_INVALID_ANGLE = 4523                ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½È£ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ 360ï¿½ï¿½ ï¿½Ê°ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_CONTI_QUEUE_EMPTY = 4524            ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ Å¥ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?
Public Const AXT_RT_MOTION_ERROR_GEAR_ENABLE = 4525            ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½Ì¹ï¿½ ï¿½ï¿½Å© ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_ERROR_GEAR_AXIS = 4526              ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Å©ï¿½ï¿½ï¿½ï¿½ ï¿½Æ´ï¿½
Public Const AXT_RT_MOTION_ERROR_NO_GANTRY_ENABLE = 4527       ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Æ®ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Â°ï¿½ ï¿½Æ´ï¿½
Public Const AXT_RT_MOTION_ERROR_NO_GEAR_ENABLE = 4528         ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Å© ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Â°ï¿½ ï¿½Æ´ï¿½
Public Const AXT_RT_MOTION_ERROR_GANTRY_ENABLE_FULL = 4529     ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½Æ®ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_ERROR_GEAR_ENABLE_FULL = 4530       ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½Å© ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_ERROR_NO_GANTRY_SLAVE = 4531        ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Æ®ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ìºï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Â°ï¿½ ï¿½Æ´ï¿½
Public Const AXT_RT_MOTION_ERROR_NO_GEAR_SLAVE = 4532          ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Å© ï¿½ï¿½ï¿½ï¿½ï¿½Ìºï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Â°ï¿½ ï¿½Æ´ï¿½
Public Const AXT_RT_MOTION_ERROR_MASTER_SLAVE_SAME = 4533      ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ï¿½Ìºï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_NOT_SUPPORT_HOMESIGNAL = 4534       ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ È¨ï¿½ï¿½È£ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_ERROR_NOT_SYNC_CONNECT = 4535       ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Å© ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Â°ï¿½ ï¿½Æ´ï¿½
Public Const AXT_RT_MOTION_OVERFLOW_POSITION = 4536            ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½à¿¡ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Ä¡ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ã·Î¿ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_ERROR_INVALID_CONTIMAPAXIS = 4537   ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½Û¾ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Ç¥ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_ERROR_INVALID_CONTIMAPSIZE = 4538   ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½Û¾ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½Ç¥ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½î°?ï¿½ß¸ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_ERROR_IN_SERVO_OFF = 4539           ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ OFFï¿½Ç¾ï¿½ ï¿½ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_ERROR_POSITIVE_LIMIT = 4540         ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ (+)ï¿½ï¿½ï¿½ï¿½ ONï¿½Ç¾ï¿½ ï¿½ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_ERROR_NEGATIVE_LIMIT = 4541         ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ (-)ï¿½ï¿½ï¿½ï¿½ ONï¿½Ç¾ï¿½ ï¿½ï¿½ï¿½ï¿½
Public Const AXT_RT_MOTION_ERROR_OVERFLOW_SWPROFILE_NUM = 4542 ' ML3 ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½, ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½é¿?ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½Ã·Î¿ï¿½ï¿?
Public Const AXT_RT_PROTECTED_DURING_INMOTION = 4543           ' in_motion ï¿½Ç¾ï¿½ ï¿½Ö´ï¿½ ï¿½ï¿½ï¿½Â¿ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿?ï¿½ï¿½ ï¿½ï¿½

Public Const AXT_RT_DATA_FLASH_NOT_EXIST = 5000
Public Const AXT_RT_DATA_FLASH_BUSY = 5001

Public Const WM_USER = &H400
Public Const WM_AXL_INTERRUPT = (WM_USER + 1001)
' Define Log Level
Public Const LEVEL_NONE = 0
Public Const LEVEL_ERROR = 1
Public Const LEVEL_RUNSTOP = 2
Public Const LEVEL_FUNCTION = 3
' Define Axis Status
Public Const STATUS_NOTEXIST = 0
Public Const STATUS_EXIST = 1
' Define Use Flag
Public Const DISABLE = 0
Public Const ENABLE = 1
' Define Analog Input Trigger Mode
Public Const DISABLE_MODE = 0
Public Const NORMAL_MODE = 1
Public Const TIMER_MODE = 2
Public Const EXTERNAL_MODE = 3
' Define Analog Input Fifo Control
Public Const NEW_DATA_KEEP = 0
Public Const CURR_DATA_KEEP = 1
' Define Analog Input Event Mask
Public Const DATA_EMPTY = &H1
Public Const DATA_MANY = &H2
Public Const DATA_SMALL = &H4
Public Const DATA_FULL = &H8
' Define Analog Input Interrupt Mask
Public Const ADC_DONE = &H0
Public Const SCAN_END = &H1
Public Const FIFO_HALF_FULL = &H2
Public Const NO_SIGNAL = &H3
' Define Analog Input Queue Event
Public Const AIO_EVENT_DATA_RESET = &H0
Public Const AIO_EVENT_DATA_UPPER = &H1
Public Const AIO_EVENT_DATA_LOWER = &H2
Public Const AIO_EVENT_DATA_FULL = &H3
Public Const AIO_EVENT_DATA_EMPTY = &H4
' AI Module H/W FIFO ?íƒœ ?•ì˜
Public Const FIFO_DATA_EXIST = 0
Public Const FIFO_DATA_EMPTY = 1
Public Const FIFO_DATA_HALF = 2
Public Const FIFO_DATA_FULL = 6
' AI Module Conversion ?íƒœ?•ì˜
Public Const EXTERNAL_DATA_DONE = 0
Public Const EXTERNAL_DATA_FINE = 1
Public Const EXTERNAL_DATA_HALF = 2
Public Const EXTERNAL_DATA_FULL = 3
Public Const EXTERNAL_COMPLETE = 4
' Define Digital Input Edge
Public Const DOWN_EDGE = 0
Public Const UP_EDGE = 1
' Define DIO Contact Status
Public Const OFF_STATE = 0
Public Const ON_STATE = 1
' Define Motion Stop Mode
Public Const EMERGENCY_STOP = 0
Public Const SLOWDOWN_STOP = 1
' Define Motion Edge
Public Const SIGNAL_UP_EDGE = 0
Public Const SIGNAL_DOWN_EDGE = 1
Public Const SIGNAL_LOW_LEVEL = 2
Public Const SIGNAL_HIGH_LEVEL = 3
' Define Motion Position Type
Public Const COMMAND = 0
Public Const ACTUAL = 1
' Define Motion Trigger Type
Public Const PERIOD_MODE = 0
Public Const ABS_POS_MODE = 1
Public Const POS_ABS_LONG_MODE = 2
' Define Motion Signal Level
Public Const LOW = 0
Public Const HIGH = 1
Public Const UNUSED = 2
Public Const USED = 3
' Define Motion Coordinate Type
Public Const POS_ABS_MODE = 0
Public Const POS_REL_MODE = 1
' Define Motion Profile Type
Public Const SYM_TRAPEZOIDE_MODE = 0
Public Const ASYM_TRAPEZOIDE_MODE = 1
Public Const QUASI_S_CURVE_MODE = 2
Public Const SYM_S_CURVE_MODE = 3
Public Const ASYM_S_CURVE_MODE = 4
' Define Motion Signal Status
Public Const INACTIVE = 0
Public Const ACTIVE = 1
' Define Motion Home Result
Public Const HOME_RESERVED = &H0                            ' ML3
Public Const HOME_SUCCESS = &H1
Public Const HOME_SEARCHING = &H2
Public Const HOME_ERR_GNT_RANGE = &H10
Public Const HOME_ERR_USER_BREAK = &H11
Public Const HOME_ERR_VELOCITY = &H12
Public Const HOME_ERR_AMP_FAULT = &H13                      ' ?œë³´???ŒëŒ ë°œìƒ ?ëŸ¬
Public Const HOME_ERR_NEG_LIMIT = &H14                      ' (-)ë°©í–¥ êµ¬ë™ì¤?(+)ë¦¬ë????¼ì„œ ê°ì? ?ëŸ¬
Public Const HOME_ERR_POS_LIMIT = &H15                      ' (+)ë°©í–¥ êµ¬ë™ì¤?(-)ë¦¬ë????¼ì„œ ê°ì? ?ëŸ¬
Public Const HOME_ERR_NOT_DETECT = &H16                     ' ì§€?•í•œ ? í˜¸ ê²€ì¶œí•˜ì§€ ëª???ê²½ìš° ?ëŸ¬
Public Const HOME_ERR_SETTING = &H17                        ' ï¿½ï¿½ï¿½ï¿½ï¿?ï¿½ï¿½ï¿½ï¿½ ï¿½Ä¶ï¿½ï¿½ï¿½Í°ï¿ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ß»ï¿½ï¿½ï¿½
Public Const HOME_ERR_SERVO_OFF = &H18                      ' ¼­º¸ OffÀÏ°æ¿ì
Public Const HOME_ERR_TIMEOUT = &H20                        ' ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ã°ï¿½ ï¿½Ê°ï¿½ ï¿½ß»ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ ï¿½ß»ï¿½ 
Public Const HOME_ERR_FUNCALL = &H30                        ' ï¿½Ô¼ï¿½ È£ï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½
Public Const HOME_ERR_COUPLING = &H40                       ' Gantry Master to Slave Over Distance protection
Public Const HOME_ERR_UNKNOWN = &HFF
' Define Motion Universal Input
Public Const UIO_INP0 = 0
Public Const UIO_INP1 = 1
Public Const UIO_INP2 = 2
Public Const UIO_INP3 = 3
Public Const UIO_INP4 = 4
Public Const UIO_INP5 = 5
' Define Motion Universal Output
Public Const UIO_OUT0 = 0
Public Const UIO_OUT1 = 1
Public Const UIO_OUT2 = 2
Public Const UIO_OUT3 = 3
Public Const UIO_OUT4 = 4
Public Const UIO_OUT5 = 5
' Define Motion Deceleration Method
Public Const AutoDetect = 0
Public Const RestPulse = 1
' Define Motion Pulse Output Method
Public Const OneHighLowHigh = &H0                           ' 1?„ìŠ¤ ë°©ì‹, PULSE(Active High), ?•ë°©??DIR=Low)  / ??°©??DIR=High)
Public Const OneHighHighLow = &H1                           ' 1?„ìŠ¤ ë°©ì‹, PULSE(Active High), ?•ë°©??DIR=High) / ??°©??DIR=Low)
Public Const OneLowLowHigh = &H2                            ' 1?„ìŠ¤ ë°©ì‹, PULSE(Active Low),  ?•ë°©??DIR=Low)  / ??°©??DIR=High)
Public Const OneLowHighLow = &H3                            ' 1?„ìŠ¤ ë°©ì‹, PULSE(Active Low),  ?•ë°©??DIR=High) / ??°©??DIR=Low)
Public Const TwoCcwCwHigh = &H4                             ' 2?„ìŠ¤ ë°©ì‹, PULSE(CCW:??°©??,  DIR(CW:?•ë°©??,  Active High
Public Const TwoCcwCwLow = &H5                              ' 2?„ìŠ¤ ë°©ì‹, PULSE(CCW:??°©??,  DIR(CW:?•ë°©??,  Active Low
Public Const TwoCwCcwHigh = &H6                             ' 2?„ìŠ¤ ë°©ì‹, PULSE(CW:?•ë°©??,   DIR(CCW:??°©??, Active High
Public Const TwoCwCcwLow = &H7                              ' 2?„ìŠ¤ ë°©ì‹, PULSE(CW:?•ë°©??,   DIR(CCW:??°©??, Active Low
Public Const TwoPhase = &H8                                 ' 2??90' ?„ìƒì°?,  PULSE lead DIR(CW: ?•ë°©??, PULSE lag DIR(CCW:??°©??
Public Const TwoPhaseReverse = &H9                          ' 2??90' ?„ìƒì°?,  PULSE lead DIR(CCW: ?•ë°©??, PULSE lag DIR(CW:??°©??
' Define Motion Encoder Input Method
Public Const ObverseUpDownMode = &H0                        ' ?•ë°©??Up/Down
Public Const ObverseSqr1Mode = &H1                          ' ?•ë°©??1ì²´ë°°
Public Const ObverseSqr2Mode = &H2                          ' ?•ë°©??2ì²´ë°°
Public Const ObverseSqr4Mode = &H3                          ' ?•ë°©??4ì²´ë°°
Public Const ReverseUpDownMode = &H4                        ' ??°©??Up/Down
Public Const ReverseSqr1Mode = &H5                          ' ??°©??1ì²´ë°°
Public Const ReverseSqr2Mode = &H6                          ' ??°©??2ì²´ë°°
Public Const ReverseSqr4Mode = &H7                          ' ??°©??4ì²´ë°°
' Define Motion Acceleration Unit
Public Const UNIT_SEC2 = &H0                                ' unit/sec2
Public Const SEC = &H1                                      ' sec
' Define Motion Move Direction
Public Const DIR_CCW = &H0                                  ' ë°˜ì‹œê³„ë°©??
Public Const DIR_CW = &H1                                   ' ?œê³„ë°©í–¥
' Define Motion Move Circular Method
Public Const SHORT_DISTANCE = &H0                           ' ì§§ì? ê±°ë¦¬???í˜¸ ?´ë™
Public Const LONG_DISTANCE = &H1                            ' ê¸?ê±°ë¦¬???í˜¸ ?´ë™
' Define Position Counter Type
Public Const POSITION_LIMIT = &H0                           ' ?„ì²´ ?ì—­?¬ìš©
Public Const POSITION_BOUND = &H1                           ' Pos ì§€???¬ìš©
' Define Motion Interpolation Axis
Public Const INTERPOLATION_AXIS2 = &H0                      ' 2ì¶•ì„ ë³´ê°„?¼ë¡œ ?¬ìš©????
Public Const INTERPOLATION_AXIS3 = &H1                      ' 3ì¶•ì„ ë³´ê°„?¼ë¡œ ?¬ìš©????
Public Const INTERPOLATION_AXIS4 = &H2                      ' 4ì¶•ì„ ë³´ê°„?¼ë¡œ ?¬ìš©????
' Define Motion Interpolation Method
Public Const CONTI_NODE_VELOCITY = &H0                      ' ?ë„ ì§€??ë³´ê°„ ëª¨ë“œ
Public Const CONTI_NODE_MANUAL = &H1                        ' ?¸ë“œ ê°€ê°ì† ë³´ê°„ ëª¨ë“œ
Public Const CONTI_NODE_AUTO = &H2                          ' ?ë™ ê°€ê°ì† ë³´ê°„ ëª¨ë“œ
' Define Motion Home Detect Signal
Public Const PosEndLimit = &H0                              ' +Elm(End limit) +ë°©í–¥ ë¦¬ë????¼ì„œ ? í˜¸
Public Const NegEndLimit = &H1                              ' -Elm(End limit) -ë°©í–¥ ë¦¬ë????¼ì„œ ? í˜¸
Public Const PosSloLimit = &H2                              ' +Slm(Slow Down limit) ? í˜¸ - ?¬ìš©?˜ì? ?ŠìŒ
Public Const NegSloLimit = &H3                              ' -Slm(Slow Down limit) ? í˜¸ - ?¬ìš©?˜ì? ?ŠìŒ
Public Const HomeSensor = &H4                               ' IN0(ORG)  ?ì  ?¼ì„œ ? í˜¸
Public Const EncodZPhase = &H5                              ' IN1(Z??  Encoder Z??? í˜¸
Public Const UniInput02 = &H6                               ' IN2(ë²”ìš©) ë²”ìš© ?…ë ¥ 2ë²?? í˜¸
Public Const UniInput03 = &H7                               ' IN3(ë²”ìš©) ë²”ìš© ?…ë ¥ 3ë²?? í˜¸
Public Const UniInput04 = &H8                               ' IN4(ë²”ìš©) ë²”ìš© ?…ë ¥ 4ë²?? í˜¸
Public Const UniInput05 = &H9                               ' IN5(ë²”ìš©) ë²”ìš© ?…ë ¥ 5ë²?? í˜¸

' Define Motion Input Filter Signal
Public Const END_LIMIT = &H10                               ' End limit +/-ë°©í–¥ ë¦¬ë????¼ì„œ ? í˜¸
Public Const INP_ALARM = &H11                               ' Inposition/Alarm ? í˜¸
Public Const UIN_00_01 = &H12                               ' Home/Z-Phase ? í˜¸
Public Const UIN_02_04 = &H13                               ' UIN 2, 3, 4 ? í˜¸

' Define Motion MPG Input Method
Public Const MPG_DIFF_ONE_PHASE = &H0                       ' MPG ?…ë ¥ ë°©ì‹ One Phase
Public Const MPG_DIFF_TWO_PHASE_1X = &H1                    ' MPG ?…ë ¥ ë°©ì‹ TwoPhase1
Public Const MPG_DIFF_TWO_PHASE_2X = &H2                    ' MPG ?…ë ¥ ë°©ì‹ TwoPhase2
Public Const MPG_DIFF_TWO_PHASE_4X = &H3                    ' MPG ?…ë ¥ ë°©ì‹ TwoPhase4
Public Const MPG_LEVEL_ONE_PHASE = &H4                      ' MPG ?…ë ¥ ë°©ì‹ Level One Phase
Public Const MPG_LEVEL_TWO_PHASE_1X = &H5                   ' MPG ?…ë ¥ ë°©ì‹ Level Two Phase1
Public Const MPG_LEVEL_TWO_PHASE_2X = &H6                   ' MPG ?…ë ¥ ë°©ì‹ Level Two Phase2
Public Const MPG_LEVEL_TWO_PHASE_4X = &H7                   ' MPG ?…ë ¥ ë°©ì‹ Level Two Phase4
' Define Motion Sensor Move Mode
Public Const SENSOR_METHOD1 = &H0                           ' ?¼ë°˜ êµ¬ë™
Public Const SENSOR_METHOD2 = &H1                           ' ?¼ì„œ ? í˜¸ ê²€ì¶??„ì? ?€??êµ¬ë™. ? í˜¸ ê²€ì¶????¼ë°˜ êµ¬ë™
Public Const SENSOR_METHOD3 = &H2                           ' ?€??êµ¬ë™
' Define Motion CRC Use Method
Public Const CRC_SELECT1 = &H0                              ' ?„ì¹˜?´ë¦¬???¬ìš©?Ší•¨, ?”ì—¬?„ìŠ¤ ?´ë¦¬???¬ìš© ?ˆí•¨
Public Const CRC_SELECT2 = &H1                              ' ?„ì¹˜?´ë¦¬???¬ìš©?? ?”ì—¬?„ìŠ¤ ?´ë¦¬???¬ìš© ?ˆí•¨
Public Const CRC_SELECT3 = &H2                              ' ?„ì¹˜?´ë¦¬???¬ìš©?ˆí•¨, ?”ì—¬?„ìŠ¤ ?´ë¦¬???¬ìš©??
Public Const CRC_SELECT4 = &H3                              ' ?„ì¹˜?´ë¦¬???¬ìš©?? ?”ì—¬?„ìŠ¤ ?´ë¦¬???¬ìš©??
' Define Motion Detect Signal Type
Public Const PElmNegativeEdge = &H0                         ' +Elm(End limit) ?˜ê°• edge
Public Const NElmNegativeEdge = &H1                         ' -Elm(End limit) ?˜ê°• edge
Public Const PSlmNegativeEdge = &H2                         ' +Slm(Slowdown limit) ?˜ê°• edge
Public Const NSlmNegativeEdge = &H3                         ' -Slm(Slowdown limit) ?˜ê°• edge
Public Const In0DownEdge = &H4                              ' IN0(ORG) ?˜ê°• edge
Public Const In1DownEdge = &H5                              ' IN1(Z?? ?˜ê°• edge
Public Const In2DownEdge = &H6                              ' IN2(ë²”ìš©) ?˜ê°• edge
Public Const In3DownEdge = &H7                              ' IN3(ë²”ìš©) ?˜ê°• edge
Public Const PElmPositiveEdge = &H8                         ' +Elm(End limit) ?ìŠ¹ edge
Public Const NElmPositiveEdge = &H9                         ' -Elm(End limit) ?ìŠ¹ edge
Public Const PSlmPositiveEdge = &HA                         ' +Slm(Slowdown limit) ?ìŠ¹ edge
Public Const NSlmPositiveEdge = &HB                         ' -Slm(Slowdown limit) ?ìŠ¹ edge
Public Const In0UpEdge = &HC                                ' IN0(ORG) ?ìŠ¹ edge
Public Const In1UpEdge = &HD                                ' IN1(Z?? ?ìŠ¹ edge
Public Const In2UpEdge = &HE                                ' IN2(ë²”ìš©) ?ìŠ¹ edge
Public Const In3UpEdge = &HF                                ' IN3(ë²”ìš©) ?ìŠ¹ edge
' Define Motion IP(2V03) End Status
Public Const IPEND_STATUS_SLM = &H1                         ' Bit 0, limit ê°ì†?•ì? ? í˜¸ ?…ë ¥???˜í•œ ì¢…ë£Œ
Public Const IPEND_STATUS_ELM = &H2                         ' Bit 1, limit ê¸‰ì •ì§€ ? í˜¸ ?…ë ¥???˜í•œ ì¢…ë£Œ
Public Const IPEND_STATUS_SSTOP_SIGNAL = &H4                ' Bit 2, ê°ì† ?•ì? ? í˜¸ ?…ë ¥???˜í•œ ì¢…ë£Œ
Public Const IPEND_STATUS_ESTOP_SIGANL = &H8                ' Bit 3, ê¸‰ì •ì§€ ? í˜¸ ?…ë ¥???˜í•œ ì¢…ë£Œ
Public Const IPEND_STATUS_SSTOP_COMMAND = &H10              ' Bit 4, ê°ì† ?•ì? ëª…ë ¹???˜í•œ ì¢…ë£Œ
Public Const IPEND_STATUS_ESTOP_COMMAND = &H20              ' Bit 5, ê¸‰ì •ì§€ ?•ì? ëª…ë ¹???˜í•œ ì¢…ë£Œ
Public Const IPEND_STATUS_ALARM_SIGNAL = &H40               ' Bit 6, Alarm ? í˜¸ ?…ë ¥???¬í•œ ì¢…ë£Œ
Public Const IPEND_STATUS_DATA_ERROR = &H80                 ' Bit 7, ?°ì´???¤ì • ?ëŸ¬???˜í•œ ì¢…ë£Œ
Public Const IPEND_STATUS_DEVIATION_ERROR = &H100           ' Bit 8, ?ˆì¡° ?ëŸ¬???˜í•œ ì¢…ë£Œ
Public Const IPEND_STATUS_ORIGIN_DETECT = &H200             ' Bit 9, ?ì  ê²€ì¶œì— ?˜í•œ ì¢…ë£Œ
Public Const IPEND_STATUS_SIGNAL_DETECT = &H400             ' Bit 10, ? í˜¸ ê²€ì¶œì— ?˜í•œ ì¢…ë£Œ(Signal search-1/2 drive ì¢…ë£Œ)
Public Const IPEND_STATUS_PRESET_PULSE_DRIVE = &H800        ' Bit 11, Preset pulse drive ì¢…ë£Œ
Public Const IPEND_STATUS_SENSOR_PULSE_DRIVE = &H1000       ' Bit 12, Sensor pulse drive ì¢…ë£Œ
Public Const IPEND_STATUS_LIMIT = &H2000                    ' Bit 13, Limit ?„ì „?•ì????˜í•œ ì¢…ë£Œ
Public Const IPEND_STATUS_SOFTLIMIT = &H4000                ' Bit 14, Soft limit???˜í•œ ì¢…ë£Œ
Public Const IPEND_STATUS_INTERPOLATION_DRIVE = &H8000      ' Bit 15, Soft limit???˜í•œ ì¢…ë£Œ
' Define Motion IP(2V03)Drive Status
Public Const IPDRIVE_STATUS_BUSY = &H1                      ' Bit 0, BUSY(?œë¼?´ë¸Œ êµ¬ë™ ì¤?
Public Const IPDRIVE_STATUS_DOWN = &H2                      ' Bit 1, DOWN(ê°ì† ì¤?
Public Const IPDRIVE_STATUS_CONST = &H4                     ' Bit 2, CONST(?±ì† ì¤?
Public Const IPDRIVE_STATUS_UP = &H8                        ' Bit 3, UP(ê°€??ì¤?
Public Const IPDRIVE_STATUS_ICL = &H10                      ' Bit 4, ICL(?´ë? ?„ì¹˜ ì¹´ìš´??< ?´ë? ?„ì¹˜ ì¹´ìš´??ë¹„êµê°?
Public Const IPDRIVE_STATUS_ICG = &H20                      ' Bit 5, ICG(?´ë? ?„ì¹˜ ì¹´ìš´??> ?´ë? ?„ì¹˜ ì¹´ìš´??ë¹„êµê°?
Public Const IPDRIVE_STATUS_ECL = &H40                      ' Bit 6, ECL(?¸ë? ?„ì¹˜ ì¹´ìš´??< ?¸ë? ?„ì¹˜ ì¹´ìš´??ë¹„êµê°?
Public Const IPDRIVE_STATUS_ECG = &H80                      ' Bit 7, ECG(?¸ë? ?„ì¹˜ ì¹´ìš´??> ?¸ë? ?„ì¹˜ ì¹´ìš´??ë¹„êµê°?
Public Const IPDRIVE_STATUS_DRIVE_DIRECTION = &H100         ' Bit 8, ?œë¼?´ë¸Œ ë°©í–¥ ? í˜¸(0=CW/1=CCW)
Public Const IPDRIVE_STATUS_COMMAND_BUSY = &H200            ' Bit 9, ëª…ë ¹???˜í–‰ì¤?
Public Const IPDRIVE_STATUS_PRESET_DRIVING = &H400          ' Bit 10, Preset pulse drive ì¤?
Public Const IPDRIVE_STATUS_CONTINUOUS_DRIVING = &H800      ' Bit 11, Continuouse speed drive ì¤?
Public Const IPDRIVE_STATUS_SIGNAL_SEARCH_DRIVING = &H1000  ' Bit 12, Signal search-1/2 drive ì¤?
Public Const IPDRIVE_STATUS_ORG_SEARCH_DRIVING = &H2000     ' Bit 13, ?ì  ê²€ì¶?drive ì¤?
Public Const IPDRIVE_STATUS_MPG_DRIVING = &H4000            ' Bit 14, MPG drive ì¤?
Public Const IPDRIVE_STATUS_SENSOR_DRIVING = &H8000         ' Bit 15, Sensor positioning drive ì¤?
Public Const IPDRIVE_STATUS_L_C_INTERPOLATION = &H10000     ' Bit 16, ì§ì„ /?í˜¸ ë³´ê°„ ì¤?
Public Const IPDRIVE_STATUS_PATTERN_INTERPOLATION = &H20000 ' Bit 17, ë¹„íŠ¸ ?¨í„´ ë³´ê°„ ì¤?
Public Const IPDRIVE_STATUS_INTERRUPT_BANK1 = &H40000       ' Bit 18, ?¸í„°?½íŠ¸ bank1?ì„œ ë°œìƒ
Public Const IPDRIVE_STATUS_INTERRUPT_BANK2 = &H80000       ' Bit 19, ?¸í„°?½íŠ¸ bank2?ì„œ ë°œìƒ
' Define Motion IP(2V03)Int MASK1
Public Const IPINTBANK1_DONTUSE = &H0                       ' INTERRUT DISABLED.
Public Const IPINTBANK1_DRIVE_END = &H1                     ' Bit 0, Drive end(default value : 1).
Public Const IPINTBANK1_ICG = &H2                           ' Bit 1, INCNT is greater than INCNTCMP.
Public Const IPINTBANK1_ICE = &H4                           ' Bit 2, INCNT is equal with INCNTCMP.
Public Const IPINTBANK1_ICL = &H8                           ' Bit 3, INCNT is less than INCNTCMP.
Public Const IPINTBANK1_ECG = &H10                          ' Bit 4, EXCNT is greater than EXCNTCMP.
Public Const IPINTBANK1_ECE = &H20                          ' Bit 5, EXCNT is equal with EXCNTCMP.
Public Const IPINTBANK1_ECL = &H40                          ' Bit 6, EXCNT is less than EXCNTCMP.
Public Const IPINTBANK1_SCRQEMPTY = &H80                    ' Bit 7, Script control queue is empty.
Public Const IPINTBANK1_CAPRQEMPTY = &H100                  ' Bit 8, Caption result data queue is empty.
Public Const IPINTBANK1_SCRREG1EXE = &H200                  ' Bit 9, Script control register-1 command is executed.
Public Const IPINTBANK1_SCRREG2EXE = &H400                  ' Bit 10, Script control register-2 command is executed.
Public Const IPINTBANK1_SCRREG3EXE = &H800                  ' Bit 11, Script control register-3 command is executed.
Public Const IPINTBANK1_CAPREG1EXE = &H1000                 ' Bit 12, Caption control register-1 command is executed.
Public Const IPINTBANK1_CAPREG2EXE = &H2000                 ' Bit 13, Caption control register-2 command is executed.
Public Const IPINTBANK1_CAPREG3EXE = &H4000                 ' Bit 14, Caption control register-3 command is executed.
Public Const IPINTBANK1_INTGGENCMD = &H8000                 ' Bit 15, Interrupt generation command is executed(0xFF)
Public Const IPINTBANK1_DOWN = &H10000                      ' Bit 16, At starting point for deceleration drive.
Public Const IPINTBANK1_CONT = &H20000                      ' Bit 17, At starting point for constant speed drive.
Public Const IPINTBANK1_UP = &H40000                        ' Bit 18, At starting point for acceleration drive.
Public Const IPINTBANK1_SIGNALDETECTED = &H80000            ' Bit 19, Signal assigned in MODE1 is detected.
Public Const IPINTBANK1_SP23E = &H100000                    ' Bit 20, Current speed is equal with rate change point RCP23.
Public Const IPINTBANK1_SP12E = &H200000                    ' Bit 21, Current speed is equal with rate change point RCP12.
Public Const IPINTBANK1_SPE = &H400000                      ' Bit 22, Current speed is equal with speed comparison data(SPDCMP).
Public Const IPINTBANK1_INCEICM = &H800000                  ' Bit 23, INTCNT(1'st counter) is equal with ICM(1'st count minus limit data)
Public Const IPINTBANK1_SCRQEXE = &H1000000                 ' Bit 24, Script queue command is executed When SCRCONQ's 30 bit is '1'.
Public Const IPINTBANK1_CAPQEXE = &H2000000                 ' Bit 25, Caption queue command is executed When CAPCONQ's 30 bit is '1'.
Public Const IPINTBANK1_SLM = &H4000000                     ' Bit 26, NSLM/PSLM input signal is activated.
Public Const IPINTBANK1_ELM = &H8000000                     ' Bit 27, NELM/PELM input signal is activated.
Public Const IPINTBANK1_USERDEFINE1 = &H10000000            ' Bit 28, Selectable interrupt source 0(refer "0xFE" command).
Public Const IPINTBANK1_USERDEFINE2 = &H20000000            ' Bit 29, Selectable interrupt source 1(refer "0xFE" command).
Public Const IPINTBANK1_USERDEFINE3 = &H40000000            ' Bit 30, Selectable interrupt source 2(refer "0xFE" command).
Public Const IPINTBANK1_USERDEFINE4 = &H80000000            ' Bit 31, Selectable interrupt source 3(refer "0xFE" command).
' Define Motion IP(2V03)Int MASK2
Public Const IPINTBANK2_DONTUSE = &H0                       ' INTERRUT DISABLED.
Public Const IPINTBANK2_L_C_INP_Q_EMPTY = &H1               ' Bit 0, Linear/Circular interpolation parameter queue is empty.
Public Const IPINTBANK2_P_INP_Q_EMPTY = &H2                 ' Bit 1, Bit pattern interpolation queue is empty.
Public Const IPINTBANK2_ALARM_ERROR = &H4                   ' Bit 2, Alarm input signal is activated.
Public Const IPINTBANK2_INPOSITION = &H8                    ' Bit 3, Inposition input signal is activated.
Public Const IPINTBANK2_MARK_SIGNAL_HIGH = &H10             ' Bit 4, Mark input signal is activated.
Public Const IPINTBANK2_SSTOP_SIGNAL = &H20                 ' Bit 5, SSTOP input signal is activated.
Public Const IPINTBANK2_ESTOP_SIGNAL = &H40                 ' Bit 6, ESTOP input signal is activated.
Public Const IPINTBANK2_SYNC_ACTIVATED = &H80               ' Bit 7, SYNC input signal is activated.
Public Const IPINTBANK2_TRIGGER_ENABLE = &H100              ' Bit 8, Trigger output is activated.
Public Const IPINTBANK2_EXCNTCLR = &H200                    ' Bit 9, External(2'nd) counter is cleard by EXCNTCLR setting.
Public Const IPINTBANK2_FSTCOMPARE_RESULT_BIT0 = &H400      ' Bit 10, ALU1's compare result bit 0 is activated.
Public Const IPINTBANK2_FSTCOMPARE_RESULT_BIT1 = &H800      ' Bit 11, ALU1's compare result bit 1 is activated.
Public Const IPINTBANK2_FSTCOMPARE_RESULT_BIT2 = &H1000     ' Bit 12, ALU1's compare result bit 2 is activated.
Public Const IPINTBANK2_FSTCOMPARE_RESULT_BIT3 = &H2000     ' Bit 13, ALU1's compare result bit 3 is activated.
Public Const IPINTBANK2_FSTCOMPARE_RESULT_BIT4 = &H4000     ' Bit 14, ALU1's compare result bit 4 is activated.
Public Const IPINTBANK2_SNDCOMPARE_RESULT_BIT0 = &H8000     ' Bit 15, ALU2's compare result bit 0 is activated.
Public Const IPINTBANK2_SNDCOMPARE_RESULT_BIT1 = &H10000    ' Bit 16, ALU2's compare result bit 1 is activated.
Public Const IPINTBANK2_SNDCOMPARE_RESULT_BIT2 = &H20000    ' Bit 17, ALU2's compare result bit 2 is activated.
Public Const IPINTBANK2_SNDCOMPARE_RESULT_BIT3 = &H40000    ' Bit 18, ALU2's compare result bit 3 is activated.
Public Const IPINTBANK2_SNDCOMPARE_RESULT_BIT4 = &H80000    ' Bit 19, ALU2's compare result bit 4 is activated.
Public Const IPINTBANK2_L_C_INP_Q_LESS_4 = &H100000         ' Bit 20, Linear/Circular interpolation parameter queue is less than 4.
Public Const IPINTBANK2_P_INP_Q_LESS_4 = &H200000           ' Bit 21, Pattern interpolation parameter queue is less than 4.
Public Const IPINTBANK2_XSYNC_ACTIVATED = &H400000          ' Bit 22, X axis sync input signal is activated.
Public Const IPINTBANK2_YSYNC_ACTIVATED = &H800000          ' Bit 23, Y axis sync input siangl is activated.
Public Const IPINTBANK2_P_INP_END_BY_END_PATTERN = &H1000000 ' Bit 24, Bit pattern interpolation is terminated by end pattern.
'IPINTBANK2_ = 0x02000000,                                  ' Bit 25, Don't care.
'IPINTBANK2_ = 0x04000000,                                  ' Bit 26, Don't care.
'IPINTBANK2_ = 0x08000000,                                  ' Bit 27, Don't care.
'IPINTBANK2_ = 0x10000000,                                  ' Bit 28, Don't care.
'IPINTBANK2_ = 0x20000000,                                  ' Bit 29, Don't care.
'IPINTBANK2_ = 0x40000000,                                  ' Bit 30, Don't care.
'IPINTBANK2_ = 0x80000000                                   ' Bit 31, Don't care.
' Define Motion IP(2V03)Drive Status
Public Const IPMECHANICAL_PELM_LEVEL = &H1                  ' Bit 0, +Limit ê¸‰ì •ì§€ ? í˜¸ê°€ ?¡í‹°ë¸???
Public Const IPMECHANICAL_NELM_LEVEL = &H2                  ' Bit 1, -Limit ê¸‰ì •ì§€ ? í˜¸ ?¡í‹°ë¸???
Public Const IPMECHANICAL_PSLM_LEVEL = &H4                  ' Bit 2, +limit ê°ì†?•ì? ? í˜¸ ?¡í‹°ë¸???
Public Const IPMECHANICAL_NSLM_LEVEL = &H8                  ' Bit 3, -limit ê°ì†?•ì? ? í˜¸ ?¡í‹°ë¸???
Public Const IPMECHANICAL_ALARM_LEVEL = &H10                ' Bit 4, Alarm ? í˜¸ ?¡í‹°ë¸???
Public Const IPMECHANICAL_INP_LEVEL = &H20                  ' Bit 5, Inposition ? í˜¸ ?¡í‹°ë¸???
Public Const IPMECHANICAL_ENC_DOWN_LEVEL = &H40             ' Bit 6, ?”ì½”??DOWN(B?? ? í˜¸ ?…ë ¥ Level
Public Const IPMECHANICAL_ENC_UP_LEVEL = &H80               ' Bit 7, ?”ì½”??UP(A?? ? í˜¸ ?…ë ¥ Level
Public Const IPMECHANICAL_EXMP_LEVEL = &H100                ' Bit 8, EXMP ? í˜¸ ?…ë ¥ Level
Public Const IPMECHANICAL_EXPP_LEVEL = &H200                ' Bit 9, EXPP ? í˜¸ ?…ë ¥ Level
Public Const IPMECHANICAL_MARK_LEVEL = &H400                ' Bit 10, MARK# ? í˜¸ ?¡í‹°ë¸???
Public Const IPMECHANICAL_SSTOP_LEVEL = &H800               ' Bit 11, SSTOP ? í˜¸ ?¡í‹°ë¸???
Public Const IPMECHANICAL_ESTOP_LEVEL = &H1000              ' Bit 12, ESTOP ? í˜¸ ?¡í‹°ë¸???
Public Const IPMECHANICAL_SYNC_LEVEL = &H2000               ' Bit 13, SYNC ? í˜¸ ?…ë ¥ Level
Public Const IPMECHANICAL_MODE8_16_LEVEL = &H4000           ' Bit 14, MODE8_16 ? í˜¸ ?…ë ¥ Level
' Define Motion QI Detect Signal
Public Const Signal_PosEndLimit = &H0                       ' +Elm(End limit) +ë°©í–¥ ë¦¬ë????¼ì„œ ? í˜¸
Public Const Signal_NegEndLimit = &H1                       ' -Elm(End limit) -ë°©í–¥ ë¦¬ë????¼ì„œ ? í˜¸
Public Const Signal_PosSloLimit = &H2                       ' +Slm(Slow Down limit) ? í˜¸ - ?¬ìš©?˜ì? ?ŠìŒ
Public Const Signal_NegSloLimit = &H3                       ' -Slm(Slow Down limit) ? í˜¸ - ?¬ìš©?˜ì? ?ŠìŒ
Public Const Signal_HomeSensor = &H4                        ' IN0(ORG)  ?ì  ?¼ì„œ ? í˜¸
Public Const Signal_EncodZPhase = &H5                       ' IN1(Z??  Encoder Z??? í˜¸
Public Const Signal_UniInput02 = &H6                        ' IN2(ë²”ìš©) ë²”ìš© ?…ë ¥ 2ë²?? í˜¸
Public Const Signal_UniInput03 = &H7                        ' IN3(ë²”ìš©) ë²”ìš© ?…ë ¥ 3ë²?? í˜¸
' Define Motion QI Drive status
Public Const QIMECHANICAL_PELM_LEVEL = &H1                  ' Bit 0, +Limit ê¸‰ì •ì§€ ? í˜¸ ?„ì¬ ?íƒœ
Public Const QIMECHANICAL_NELM_LEVEL = &H2                  ' Bit 1, -Limit ê¸‰ì •ì§€ ? í˜¸ ?„ì¬ ?íƒœ
Public Const QIMECHANICAL_PSLM_LEVEL = &H4                  ' Bit 2, +limit ê°ì†?•ì? ?„ì¬ ?íƒœ.
Public Const QIMECHANICAL_NSLM_LEVEL = &H8                  ' Bit 3, -limit ê°ì†?•ì? ?„ì¬ ?íƒœ
Public Const QIMECHANICAL_ALARM_LEVEL = &H10                ' Bit 4, Alarm ? í˜¸ ? í˜¸ ?„ì¬ ?íƒœ
Public Const QIMECHANICAL_INP_LEVEL = &H20                  ' Bit 5, Inposition ? í˜¸ ?„ì¬ ?íƒœ
Public Const QIMECHANICAL_ESTOP_LEVEL = &H40                ' Bit 6, ë¹„ìƒ ?•ì? ? í˜¸(ESTOP) ?„ì¬ ?íƒœ.
Public Const QIMECHANICAL_ORG_LEVEL = &H80                  ' Bit 7, ?ì  ? í˜¸ ?Œì¬ ?íƒœ
Public Const QIMECHANICAL_ZPHASE_LEVEL = &H100              ' Bit 8, Z ???…ë ¥ ? í˜¸ ?„ì¬ ?íƒœ
Public Const QIMECHANICAL_ECUP_LEVEL = &H200                ' Bit 9, ECUP ?°ë???? í˜¸ ?íƒœ.
Public Const QIMECHANICAL_ECDN_LEVEL = &H400                ' Bit 10, ECDN ?°ë???? í˜¸ ?íƒœ.
Public Const QIMECHANICAL_EXPP_LEVEL = &H800                ' Bit 11, EXPP ?°ë???? í˜¸ ?íƒœ
Public Const QIMECHANICAL_EXMP_LEVEL = &H1000               ' Bit 12, EXMP ?°ë???? í˜¸ ?íƒœ
Public Const QIMECHANICAL_SQSTR1_LEVEL = &H2000             ' Bit 13, SQSTR1 ?°ë???? í˜¸ ?íƒœ
Public Const QIMECHANICAL_SQSTR2_LEVEL = &H4000             ' Bit 14, SQSTR2 ?°ë???? í˜¸ ?íƒœ
Public Const QIMECHANICAL_SQSTP1_LEVEL = &H8000             ' Bit 15, SQSTP1 ?°ë???? í˜¸ ?íƒœ
Public Const QIMECHANICAL_SQSTP2_LEVEL = &H10000            ' Bit 16, SQSTP2 ?°ë???? í˜¸ ?íƒœ
Public Const QIMECHANICAL_MODE_LEVEL = &H20000              ' Bit 17, MODE ?°ë???? í˜¸ ?íƒœ.
' Define Motion QI End Status
Public Const QIEND_STATUS_0 = &H1                           ' Bit 0, ?•ë°©??ë¦¬ë???? í˜¸(PELM)???˜í•œ ì¢…ë£Œ
Public Const QIEND_STATUS_1 = &H2                           ' Bit 1, ??°©??ë¦¬ë???? í˜¸(NELM)???˜í•œ ì¢…ë£Œ
Public Const QIEND_STATUS_2 = &H4                           ' Bit 2, ?•ë°©??ë¶€ê°€ ë¦¬ë???? í˜¸(PSLM)???˜í•œ êµ¬ë™ ì¢…ë£Œ
Public Const QIEND_STATUS_3 = &H8                           ' Bit 3, ??°©??ë¶€ê°€ ë¦¬ë???? í˜¸(NSLM)???˜í•œ êµ¬ë™ ì¢…ë£Œ
Public Const QIEND_STATUS_4 = &H10                          ' Bit 4, ?•ë°©???Œí”„??ë¦¬ë???ê¸‰ì •ì§€ ê¸°ëŠ¥???˜í•œ êµ¬ë™ ì¢…ë£Œ
Public Const QIEND_STATUS_5 = &H20                          ' Bit 5, ??°©???Œí”„??ë¦¬ë???ê¸‰ì •ì§€ ê¸°ëŠ¥???˜í•œ êµ¬ë™ ì¢…ë£Œ
Public Const QIEND_STATUS_6 = &H40                          ' Bit 6, ?•ë°©???Œí”„??ë¦¬ë???ê°ì†?•ì? ê¸°ëŠ¥???˜í•œ êµ¬ë™ ì¢…ë£Œ
Public Const QIEND_STATUS_7 = &H80                          ' Bit 7, ??°©???Œí”„??ë¦¬ë???ê°ì†?•ì? ê¸°ëŠ¥???˜í•œ êµ¬ë™ ì¢…ë£Œ
Public Const QIEND_STATUS_8 = &H100                         ' Bit 8, ?œë³´ ?ŒëŒ ê¸°ëŠ¥???˜í•œ êµ¬ë™ ì¢…ë£Œ.
Public Const QIEND_STATUS_9 = &H200                         ' Bit 9, ë¹„ìƒ ?•ì? ? í˜¸ ?…ë ¥???˜í•œ êµ¬ë™ ì¢…ë£Œ.
Public Const QIEND_STATUS_10 = &H400                        ' Bit 10, ê¸??•ì? ëª…ë ¹???˜í•œ êµ¬ë™ ì¢…ë£Œ.
Public Const QIEND_STATUS_11 = &H800                        ' Bit 11, ê°ì† ?•ì? ëª…ë ¹???˜í•œ êµ¬ë™ ì¢…ë£Œ.
Public Const QIEND_STATUS_12 = &H1000                       ' Bit 12, ?„ì¶• ê¸‰ì •ì§€ ëª…ë ¹???˜í•œ êµ¬ë™ ì¢…ë£Œ
Public Const QIEND_STATUS_13 = &H2000                       ' Bit 13, ?™ê¸° ?•ì? ê¸°ëŠ¥ #1(SQSTP1)???˜í•œ êµ¬ë™ ì¢…ë£Œ.
Public Const QIEND_STATUS_14 = &H4000                       ' Bit 14, ?™ê¸° ?•ì? ê¸°ëŠ¥ #2(SQSTP2)???˜í•œ êµ¬ë™ ì¢…ë£Œ.
Public Const QIEND_STATUS_15 = &H8000                       ' Bit 15, ?¸ì½”???…ë ¥(ECUP,ECDN) ?¤ë¥˜ ë°œìƒ
Public Const QIEND_STATUS_16 = &H10000                      ' Bit 16, MPG ?…ë ¥(EXPP,EXMP) ?¤ë¥˜ ë°œìƒ
Public Const QIEND_STATUS_17 = &H20000                      ' Bit 17, ?ì  ê²€???±ê³µ ì¢…ë£Œ.
Public Const QIEND_STATUS_18 = &H40000                      ' Bit 18, ? í˜¸ ê²€???±ê³µ ì¢…ë£Œ.
Public Const QIEND_STATUS_19 = &H80000                      ' Bit 19, ë³´ê°„ ?°ì´???´ìƒ?¼ë¡œ êµ¬ë™ ì¢…ë£Œ.
Public Const QIEND_STATUS_20 = &H100000                     ' Bit 20, ë¹„ì •??êµ¬ë™ ?•ì?ë°œìƒ.
Public Const QIEND_STATUS_21 = &H200000                     ' Bit 21, MPG ê¸°ëŠ¥ ë¸”ë¡ ?„ìŠ¤ ë²„í¼ ?¤ë²„?Œë¡œ??ë°œìƒ
Public Const QIEND_STATUS_22 = &H400000                     ' Bit 22, DON'CARE
Public Const QIEND_STATUS_23 = &H800000                     ' Bit 23, DON'CARE
Public Const QIEND_STATUS_24 = &H1000000                    ' Bit 24, DON'CARE
Public Const QIEND_STATUS_25 = &H2000000                    ' Bit 25, DON'CARE
Public Const QIEND_STATUS_26 = &H4000000                    ' Bit 26, DON'CARE
Public Const QIEND_STATUS_27 = &H8000000                    ' Bit 27, DON'CARE
Public Const QIEND_STATUS_28 = &H10000000                   ' Bit 28, ?„ì¬/ë§ˆì?ë§?êµ¬ë™ ?œë¼?´ë¸Œ ë°©í–¥
Public Const QIEND_STATUS_29 = &H20000000                   ' Bit 29, ?”ì—¬ ?„ìŠ¤ ?œê±° ? í˜¸ ì¶œë ¥ ì¤?
Public Const QIEND_STATUS_30 = &H40000000                   ' Bit 30, ë¹„ì •??êµ¬ë™ ?•ì? ?ì¸ ?íƒœ
Public Const QIEND_STATUS_31 = &H80000000                   ' Bit 31, ë³´ê°„ ?œë¼?´ë¸Œ ?°ì´?€ ?¤ë¥˜ ?íƒœ.
' Define Motion QI Drive Status
Public Const QIDRIVE_STATUS_0 = &H1                         ' Bit 0, BUSY(?œë¼?´ë¸Œ êµ¬ë™ ì¤?
Public Const QIDRIVE_STATUS_1 = &H2                         ' Bit 1, DOWN(ê°ì† ì¤?
Public Const QIDRIVE_STATUS_2 = &H4                         ' Bit 2, CONST(?±ì† ì¤?
Public Const QIDRIVE_STATUS_3 = &H8                         ' Bit 3, UP(ê°€??ì¤?
Public Const QIDRIVE_STATUS_4 = &H10                        ' Bit 4, ?°ì† ?œë¼?´ë¸Œ êµ¬ë™ ì¤?
Public Const QIDRIVE_STATUS_5 = &H20                        ' Bit 5, ì§€??ê±°ë¦¬ ?œë¼?´ë¸Œ êµ¬ë™ ì¤?
Public Const QIDRIVE_STATUS_6 = &H40                        ' Bit 6, MPG ?œë¼?´ë¸Œ êµ¬ë™ ì¤?
Public Const QIDRIVE_STATUS_7 = &H80                        ' Bit 7, ?ì ê²€???œë¼?´ë¸Œ êµ¬ë™ì¤?
Public Const QIDRIVE_STATUS_8 = &H100                       ' Bit 8, ? í˜¸ ê²€???œë¼?´ë¸Œ êµ¬ë™ ì¤?
Public Const QIDRIVE_STATUS_9 = &H200                       ' Bit 9, ë³´ê°„ ?œë¼?´ë¸Œ êµ¬ë™ ì¤?
Public Const QIDRIVE_STATUS_10 = &H400                      ' Bit 10, Slave ?œë¼?´ë¸Œ êµ¬ë™ì¤?
Public Const QIDRIVE_STATUS_11 = &H800                      ' Bit 11, ?„ì¬ êµ¬ë™ ?œë¼?´ë¸Œ ë°©í–¥(ë³´ê°„ ?œë¼?´ë¸Œ?ì„œ???œì‹œ ?•ë³´ ?¤ë¦„)
Public Const QIDRIVE_STATUS_12 = &H1000                     ' Bit 12, ?„ìŠ¤ ì¶œë ¥???œë³´?„ì¹˜ ?„ë£Œ ? í˜¸ ?€ê¸°ì¤‘.
Public Const QIDRIVE_STATUS_13 = &H2000                     ' Bit 13, ì§ì„  ë³´ê°„ ?œë¼?´ë¸Œ êµ¬ë™ì¤?
Public Const QIDRIVE_STATUS_14 = &H4000                     ' Bit 14, ?í˜¸ ë³´ê°„ ?œë¼?´ë¸Œ êµ¬ë™ì¤?
Public Const QIDRIVE_STATUS_15 = &H8000                     ' Bit 15, ?„ìŠ¤ ì¶œë ¥ ì¤?
Public Const QIDRIVE_STATUS_16 = &H10000                    ' Bit 16, êµ¬ë™ ?ˆì•½ ?°ì´??ê°œìˆ˜(ì²˜ìŒ)(0-7)
Public Const QIDRIVE_STATUS_17 = &H20000                    ' Bit 17, êµ¬ë™ ?ˆì•½ ?°ì´??ê°œìˆ˜(ì¤‘ê°„)(0-7)
Public Const QIDRIVE_STATUS_18 = &H40000                    ' Bit 18, êµ¬ë™ ?ˆì•½ ?°ì´??ê°?ˆ˜(??(0-7)
Public Const QIDRIVE_STATUS_19 = &H80000                    ' Bit 19, êµ¬ë™ ?ˆì•½ Queue ë¹„ì–´ ?ˆìŒ.
Public Const QIDRIVE_STATUS_20 = &H100000                   ' Bit 20, êµ¬ë™ ?ˆì•½ Queue ê°€??ì°?
Public Const QIDRIVE_STATUS_21 = &H200000                   ' Bit 21, ?„ì¬ êµ¬ë™ ?œë¼?´ë¸Œ???ë„ ëª¨ë“œ(ì²˜ìŒ)
Public Const QIDRIVE_STATUS_22 = &H400000                   ' Bit 22, ?„ì¬ êµ¬ë™ ?œë¼?´ë¸Œ???ë„ ëª¨ë“œ(??
Public Const QIDRIVE_STATUS_23 = &H800000                   ' Bit 23, MPG ë²„í¼ #1 Full
Public Const QIDRIVE_STATUS_24 = &H1000000                  ' Bit 24, MPG ë²„í¼ #2 Full
Public Const QIDRIVE_STATUS_25 = &H2000000                  ' Bit 25, MPG ë²„í¼ #3 Full
Public Const QIDRIVE_STATUS_26 = &H4000000                  ' Bit 26, MPG ë²„í¼ ?°ì´??OverFlow
' Define Motion QI Interrupt MASK1
Public Const QIINTBANK1_DISABLE = &H0                       ' INTERRUT DISABLED.
Public Const QIINTBANK1_0 = &H1                             ' Bit 0,  ?¸í„°?½íŠ¸ ë°œìƒ ?¬ìš© ?¤ì •??êµ¬ë™ ì¢…ë£Œ??
Public Const QIINTBANK1_1 = &H2                             ' Bit 1,  êµ¬ë™ ì¢…ë£Œ??
Public Const QIINTBANK1_2 = &H4                             ' Bit 2,  êµ¬ë™ ?œì‘??
Public Const QIINTBANK1_3 = &H8                             ' Bit 3,  ì¹´ìš´??#1 < ë¹„êµê¸?#1 ?´ë²¤??ë°œìƒ
Public Const QIINTBANK1_4 = &H10                            ' Bit 4,  ì¹´ìš´??#1 = ë¹„êµê¸?#1 ?´ë²¤??ë°œìƒ
Public Const QIINTBANK1_5 = &H20                            ' Bit 5,  ì¹´ìš´??#1 > ë¹„êµê¸?#1 ?´ë²¤??ë°œìƒ
Public Const QIINTBANK1_6 = &H40                            ' Bit 6,  ì¹´ìš´??#2 < ë¹„êµê¸?#2 ?´ë²¤??ë°œìƒ
Public Const QIINTBANK1_7 = &H80                            ' Bit 7,  ì¹´ìš´??#2 = ë¹„êµê¸?#2 ?´ë²¤??ë°œìƒ
Public Const QIINTBANK1_8 = &H100                           ' Bit 8,  ì¹´ìš´??#2 > ë¹„êµê¸?#2 ?´ë²¤??ë°œìƒ
Public Const QIINTBANK1_9 = &H200                           ' Bit 9,  ì¹´ìš´??#3 < ë¹„êµê¸?#3 ?´ë²¤??ë°œìƒ
Public Const QIINTBANK1_10 = &H400                          ' Bit 10, ì¹´ìš´??#3 = ë¹„êµê¸?#3 ?´ë²¤??ë°œìƒ
Public Const QIINTBANK1_11 = &H800                          ' Bit 11, ì¹´ìš´??#3 > ë¹„êµê¸?#3 ?´ë²¤??ë°œìƒ
Public Const QIINTBANK1_12 = &H1000                         ' Bit 12, ì¹´ìš´??#4 < ë¹„êµê¸?#4 ?´ë²¤??ë°œìƒ
Public Const QIINTBANK1_13 = &H2000                         ' Bit 13, ì¹´ìš´??#4 = ë¹„êµê¸?#4 ?´ë²¤??ë°œìƒ
Public Const QIINTBANK1_14 = &H4000                         ' Bit 14, ì¹´ìš´??#4 < ë¹„êµê¸?#4 ?´ë²¤??ë°œìƒ
Public Const QIINTBANK1_15 = &H8000                         ' Bit 15, ì¹´ìš´??#5 < ë¹„êµê¸?#5 ?´ë²¤??ë°œìƒ
Public Const QIINTBANK1_16 = &H10000                        ' Bit 16, ì¹´ìš´??#5 = ë¹„êµê¸?#5 ?´ë²¤??ë°œìƒ
Public Const QIINTBANK1_17 = &H20000                        ' Bit 17, ì¹´ìš´??#5 > ë¹„êµê¸?#5 ?´ë²¤??ë°œìƒ
Public Const QIINTBANK1_18 = &H40000                        ' Bit 18, ?€?´ë¨¸ #1 ?´ë²¤??ë°œìƒ.
Public Const QIINTBANK1_19 = &H80000                        ' Bit 19, ?€?´ë¨¸ #2 ?´ë²¤??ë°œìƒ.
Public Const QIINTBANK1_20 = &H100000                       ' Bit 20, êµ¬ë™ ?ˆì•½ ?¤ì • Queue ë¹„ì›Œì§?
Public Const QIINTBANK1_21 = &H200000                       ' Bit 21, êµ¬ë™ ?ˆì•½ ?¤ì • Queue ê°€?ì°²
Public Const QIINTBANK1_22 = &H400000                       ' Bit 22, ?¸ë¦¬ê±?ë°œìƒê±°ë¦¬ ì£¼ê¸°/?ˆë??„ì¹˜ Queue ë¹„ì›Œì§?
Public Const QIINTBANK1_23 = &H800000                       ' Bit 23, ?¸ë¦¬ê±?ë°œìƒê±°ë¦¬ ì£¼ê¸°/?ˆë??„ì¹˜ Queue ê°€?ì°²
Public Const QIINTBANK1_24 = &H1000000                      ' Bit 24, ?¸ë¦¬ê±?? í˜¸ ë°œìƒ ?´ë²¤??
Public Const QIINTBANK1_25 = &H2000000                      ' Bit 25, ?¤í¬ë¦½íŠ¸ #1 ëª…ë ¹???ˆì•½ ?¤ì • Queue ë¹„ì›Œì§?
Public Const QIINTBANK1_26 = &H4000000                      ' Bit 26, ?¤í¬ë¦½íŠ¸ #2 ëª…ë ¹???ˆì•½ ?¤ì • Queue ë¹„ì›Œì§?
Public Const QIINTBANK1_27 = &H8000000                      ' Bit 27, ?¤í¬ë¦½íŠ¸ #3 ëª…ë ¹???ˆì•½ ?¤ì • ?ˆì??¤í„° ?¤í–‰?˜ì–´ ì´ˆê¸°????
Public Const QIINTBANK1_28 = &H10000000                     ' Bit 28, ?¤í¬ë¦½íŠ¸ #4 ëª…ë ¹???ˆì•½ ?¤ì • ?ˆì??¤í„° ?¤í–‰?˜ì–´ ì´ˆê¸°????
Public Const QIINTBANK1_29 = &H20000000                     ' Bit 29, ?œë³´ ?ŒëŒ? í˜¸ ?¸ê???
Public Const QIINTBANK1_30 = &H40000000                     ' Bit 30, |CNT1| - |CNT2| >= |CNT4| ?´ë²¤??ë°œìƒ.
Public Const QIINTBANK1_31 = &H80000000                     ' Bit 31, ?¸í„°?½íŠ¸ ë°œìƒ ëª…ë ¹??INTGEN| ?¤í–‰.
' Define Motion QI Interrupt MASK2
Public Const QIINTBANK2_DISABLE = &H0                       ' INTERRUT DISABLED.
Public Const QIINTBANK2_0 = &H1                             ' Bit 0,  ?¤í¬ë¦½íŠ¸ #1 ?½ê¸° ëª…ë ¹ ê²°ê³¼ Queue ê°€ ê°€?ì°².
Public Const QIINTBANK2_1 = &H2                             ' Bit 1,  ?¤í¬ë¦½íŠ¸ #2 ?½ê¸° ëª…ë ¹ ê²°ê³¼ Queue ê°€ ê°€?ì°².
Public Const QIINTBANK2_2 = &H4                             ' Bit 2,  ?¤í¬ë¦½íŠ¸ #3 ?½ê¸° ëª…ë ¹ ê²°ê³¼ ?ˆì??¤í„°ê°€ ?ˆë¡œ???°ì´?°ë¡œ ê°±ì‹ ??
Public Const QIINTBANK2_3 = &H8                             ' Bit 3,  ?¤í¬ë¦½íŠ¸ #4 ?½ê¸° ëª…ë ¹ ê²°ê³¼ ?ˆì??¤í„°ê°€ ?ˆë¡œ???°ì´?°ë¡œ ê°±ì‹ ??
Public Const QIINTBANK2_4 = &H10                            ' Bit 4,  ?¤í¬ë¦½íŠ¸ #1 ???ˆì•½ ëª…ë ¹??ì¤??¤í–‰ ???¸í„°?½íŠ¸ ë°œìƒ?¼ë¡œ ?¤ì •??ëª…ë ¹???¤í–‰??
Public Const QIINTBANK2_5 = &H20                            ' Bit 5,  ?¤í¬ë¦½íŠ¸ #2 ???ˆì•½ ëª…ë ¹??ì¤??¤í–‰ ???¸í„°?½íŠ¸ ë°œìƒ?¼ë¡œ ?¤ì •??ëª…ë ¹???¤í–‰??
Public Const QIINTBANK2_6 = &H40                            ' Bit 6,  ?¤í¬ë¦½íŠ¸ #3 ???ˆì•½ ëª…ë ¹???¤í–‰ ???¸í„°?½íŠ¸ ë°œìƒ?¼ë¡œ ?¤ì •??ëª…ë ¹???¤í–‰??
Public Const QIINTBANK2_7 = &H80                            ' Bit 7,  ?¤í¬ë¦½íŠ¸ #4 ???ˆì•½ ëª…ë ¹???¤í–‰ ???¸í„°?½íŠ¸ ë°œìƒ?¼ë¡œ ?¤ì •??ëª…ë ¹???¤í–‰??
Public Const QIINTBANK2_8 = &H100                           ' Bit 8,  êµ¬ë™ ?œì‘
Public Const QIINTBANK2_9 = &H200                           ' Bit 9,  ?œë³´ ?„ì¹˜ ê²°ì • ?„ë£Œ(Inposition)ê¸°ëŠ¥???¬ìš©??êµ¬ë™,ì¢…ë£Œ ì¡°ê±´ ë°œìƒ.
Public Const QIINTBANK2_10 = &H400                          ' Bit 10, ?´ë²¤??ì¹´ìš´?°ë¡œ ?™ì‘ ???¬ìš©???´ë²¤??? íƒ #1 ì¡°ê±´ ë°œìƒ.
Public Const QIINTBANK2_11 = &H800                          ' Bit 11, ?´ë²¤??ì¹´ìš´?°ë¡œ ?™ì‘ ???¬ìš©???´ë²¤??? íƒ #2 ì¡°ê±´ ë°œìƒ.
Public Const QIINTBANK2_12 = &H1000                         ' Bit 12, SQSTR1 ? í˜¸ ?¸ê? ??
Public Const QIINTBANK2_13 = &H2000                         ' Bit 13, SQSTR2 ? í˜¸ ?¸ê? ??
Public Const QIINTBANK2_14 = &H4000                         ' Bit 14, UIO0 ?°ë???? í˜¸ê°€ '1'ë¡?ë³€??
Public Const QIINTBANK2_15 = &H8000                         ' Bit 15, UIO1 ?°ë???? í˜¸ê°€ '1'ë¡?ë³€??
Public Const QIINTBANK2_16 = &H10000                        ' Bit 16, UIO2 ?°ë???? í˜¸ê°€ '1'ë¡?ë³€??
Public Const QIINTBANK2_17 = &H20000                        ' Bit 17, UIO3 ?°ë???? í˜¸ê°€ '1'ë¡?ë³€??
Public Const QIINTBANK2_18 = &H40000                        ' Bit 18, UIO4 ?°ë???? í˜¸ê°€ '1'ë¡?ë³€??
Public Const QIINTBANK2_19 = &H80000                        ' Bit 19, UIO5 ?°ë???? í˜¸ê°€ '1'ë¡?ë³€??
Public Const QIINTBANK2_20 = &H100000                       ' Bit 20, UIO6 ?°ë???? í˜¸ê°€ '1'ë¡?ë³€??
Public Const QIINTBANK2_21 = &H200000                       ' Bit 21, UIO7 ?°ë???? í˜¸ê°€ '1'ë¡?ë³€??
Public Const QIINTBANK2_22 = &H400000                       ' Bit 22, UIO8 ?°ë???? í˜¸ê°€ '1'ë¡?ë³€??
Public Const QIINTBANK2_23 = &H800000                       ' Bit 23, UIO9 ?°ë???? í˜¸ê°€ '1'ë¡?ë³€??
Public Const QIINTBANK2_24 = &H1000000                      ' Bit 24, UIO10 ?°ë???? í˜¸ê°€ '1'ë¡?ë³€??
Public Const QIINTBANK2_25 = &H2000000                      ' Bit 25, UIO11 ?°ë???? í˜¸ê°€ '1'ë¡?ë³€??
Public Const QIINTBANK2_26 = &H4000000                      ' Bit 26, ?¤ë¥˜ ?•ì? ì¡°ê±´(LMT, ESTOP, STOP, ESTOP, CMD, ALARM) ë°œìƒ.
Public Const QIINTBANK2_27 = &H8000000                      ' Bit 27, ë³´ê°„ ì¤??°ì´???¤ì • ?¤ë¥˜ ë°œìƒ.
Public Const QIINTBANK2_28 = &H10000000                     ' Bit 28, Don't Care
Public Const QIINTBANK2_29 = &H20000000                     ' Bit 29, ë¦¬ë???? í˜¸(PELM, NELM)? í˜¸ê°€ ?…ë ¥ ??
Public Const QIINTBANK2_30 = &H40000000                     ' Bit 30, ë¶€ê°€ ë¦¬ë???? í˜¸(PSLM, NSLM)? í˜¸ê°€ ?…ë ¥ ??
Public Const QIINTBANK2_31 = &H80000000                     ' Bit 31, ë¹„ìƒ ?•ì? ? í˜¸(ESTOP)? í˜¸ê°€ ?…ë ¥??

' Network Status ?íƒœ?•ì˜
Public Const NET_STATUS_DISCONNECTED = 1
Public Const NET_STATUS_LOCK_MISMATCH = 5
Public Const NET_STATUS_CONNECTED = 6
' ëª¨ì…˜?œí’ˆ(QI) Override ?„ì¹˜ ì¡°ê±´
Public Const OVERRIDE_POS_START = 0
Public Const OVERRIDE_POS_END = 1
' ëª¨ì…˜?œí’ˆ(QI) Profile ?°ì„ ?œìœ„
Public Const PRIORITY_VELOCITY = 0
Public Const PRIORITY_ACCELTIME = 1
' ëª¨ì…˜?¨ìˆ˜ ë°˜í™˜?•íƒœ ?•ì˜
Public Const FUNC_RETURN_IMMEDIATE = 0
Public Const FUNC_RETURN_BLOCKING = 1
Public Const FUNC_RETURN_NON_BLOCKING = 2
' ?œë³´???ŒëŒì½”ë“œ ê¸°ë¡ ê°œìˆ˜?•ì˜
Public Const MAX_SERVO_ALARM_HISTORY = 15

' Counter Module Define
Public Const F_50M_CLK = 50000000

Public Const CnCommand = &H10
Public Const CnData1 = &H12
Public Const CnData2 = &H14
Public Const CnData3 = &H16
Public Const CnData4 = &H18
Public Const CnData12 = &H44
Public Const CnData34 = &H46

Public Const CnRamAddr1 = &H28
Public Const CnRamAddr2 = &H2A
Public Const CnRamAddr3 = &H2C
Public Const CnRamAddrx1 = &H48
Public Const CnRamAddr23 = &H4A

Public Const CnAbPhase = 0
Public Const CnZPhase = 1

Public Const CnUpDownMode = 0
Public Const CnSqr1Mode = 1
Public Const CnSqr2Mode = 2
Public Const CnSqr4Mode = 3

' CH-1 Group Register
Public Const CnCh1CounterRead = &H10                        ' CH1 COUNTER READ, 24BIT
Public Const CnCh1CounterWrite = &H90                       ' CH1 COUNTER WRITE
Public Const CnCh1CounterModeRead = &H11                    ' CH1 COUNTER MODE READ, 8BIT
Public Const CnCh1CounterModeWrite = &H91                   ' CH1 COUNTER MODE WRITE
Public Const CnCh1TriggerRegionLowerDataRead = &H12         ' CH1 TRIGGER REGION LOWER DATA READ, 24BIT
Public Const CnCh1TriggerRegionLowerDataWrite = &H92        ' CH1 TRIGGER REGION LOWER DATA WRITE
Public Const CnCh1TriggerRegionUpperDataRead = &H13         ' CH1 TRIGGER REGION UPPER DATA READ, 24BIT
Public Const CnCh1TriggerRegionUpperDataWrite = &H93        ' CH1 TRIGGER REGION UPPER DATA WRITE
Public Const CnCh1TriggerPeriodRead = &H14                  ' CH1 TRIGGER PERIOD READ, 24BIT, RESERVED
Public Const CnCh1TriggerPeriodWrite = &H94                 ' CH1 TRIGGER PERIOD WRITE
Public Const CnCh1TriggerPulseWidthRead = &H15              ' CH1 TRIGGER PULSE WIDTH READ
Public Const CnCh1TriggerPulseWidthWrite = &H95             ' CH1 RIGGER PULSE WIDTH WRITE
Public Const CnCh1TriggerModeRead = &H16                    ' CH1 TRIGGER MODE READ
Public Const CnCh1TriggerModeWrite = &H96                   ' CH1 RIGGER MODE WRITE
Public Const CnCh1TriggerStatusRead = &H17                  ' CH1 TRIGGER STATUS READ
Public Const CnCh1NoOperation_97 = &H97
Public Const CnCh1TriggerEnable = &H98
Public Const CnCh1TriggerDisable = &H99
Public Const CnCh1TimeTriggerFrequencyRead = &H1A
Public Const CnCh1TimeTriggerFrequencyWrite = &H9A
Public Const CnCh1ComparatorValueRead = &H1B
Public Const CnCh1ComparatorValueWrite = &H9B
Public Const CnCh1CompareatorConditionRead = &H1D
Public Const CnCh1CompareatorConditionWrite = &H9D

' CH-2 Group Register
Public Const CnCh2CounterRead = &H20                        ' CH2 COUNTER READ, 24BIT
Public Const CnCh2CounterWrite = &HA1                       ' CH2 COUNTER WRITE
Public Const CnCh2CounterModeRead = &H21                    ' CH2 COUNTER MODE READ, 8BIT
Public Const CnCh2CounterModeWrite = &HA1                   ' CH2 COUNTER MODE WRITE
Public Const CnCh2TriggerRegionLowerDataRead = &H22         ' CH2 TRIGGER REGION LOWER DATA READ, 24BIT
Public Const CnCh2TriggerRegionLowerDataWrite = &HA2        ' CH2 TRIGGER REGION LOWER DATA WRITE
Public Const CnCh2TriggerRegionUpperDataRead = &H23         ' CH2 TRIGGER REGION UPPER DATA READ, 24BIT
Public Const CnCh2TriggerRegionUpperDataWrite = &HA3        ' CH2 TRIGGER REGION UPPER DATA WRITE
Public Const CnCh2TriggerPeriodRead = &H24                  ' CH2 TRIGGER PERIOD READ, 24BIT, RESERVED
Public Const CnCh2TriggerPeriodWrite = &HA4                 ' CH2 TRIGGER PERIOD WRITE
Public Const CnCh2TriggerPulseWidthRead = &H25              ' CH2 TRIGGER PULSE WIDTH READ, 24BIT
Public Const CnCh2TriggerPulseWidthWrite = &HA5             ' CH2 RIGGER PULSE WIDTH WRITE
Public Const CnCh2TriggerModeRead = &H26                    ' CH2 TRIGGER MODE READ
Public Const CnCh2TriggerModeWrite = &HA6                   ' CH2 RIGGER MODE WRITE
Public Const CnCh2TriggerStatusRead = &H27                  ' CH2 TRIGGER STATUS READ
Public Const CnCh2NoOperation_A7 = &HA7
Public Const CnCh2TriggerEnable = &HA8
Public Const CnCh2TriggerDisable = &HA9
Public Const CnCh2TimeTriggerFrequencyRead = &H2A
Public Const CnCh2TimeTriggerFrequencyWrite = &HAA
Public Const CnCh2ComparatorValueRead = &H2B
Public Const CnCh2ComparatorValueWrite = &HAB
Public Const CnCh2CompareatorConditionRead = &H2D
Public Const CnCh2CompareatorConditionWrite = &HAD

' Ram Access Group Register
Public Const CnRamDataWithRamAddress = &H30                 ' READ RAM DATA WITH RAM ADDR PORT ADDRESS
Public Const CnRamDataWrite = &HB0                          ' RAM DATA WRITE
Public Const CnRamDataRead = &H31                           ' RAM DATA READ, 32BIT

' HPCPort Data WRITE
Public Const HpcReset = &H6                     ' Software reset.
Public Const HpcCommand = &H10
Public Const HpcData12 = &H12                    ' MSB of data port(31 ~ 16 bit)
Public Const HpcData34 = &H14                    ' LSB of data port(15 ~ 0 bit)
Public Const HpcCmStatus = &H1C

' HPCPort Channel STATUS
Public Const HpcCh1Mech = &H20
Public Const HpcCh1Status = &H22
Public Const HpcCh2Mech = &H30
Public Const HpcCh2Status = &H32
Public Const HpcCh3Mech = &H40
Public Const HpcCh3Status = &H42
Public Const HpcCh4Mech = &H50
Public Const HpcCh4Status = &H52

' HPCPort ETC
Public Const HpcDiIntFlag = &H60
Public Const HpcDiIntRiseMask = &H62
Public Const HpcDiIntFallMask = &H64
Public Const HpcCompIntFlag = &H66
Public Const HpcCompIntMask = &H68
Public Const HpcDinData = &H6A
Public Const HpcDoutData = &H6C

' HPCRAM data
Public Const HpcRamAddr1 = &H70                   ' MSB of Ram address(31  ~ 16 bit)
Public Const HpcRamAddr2 = &H72                   ' LSB of Ram address(15  ~ 0 bit)

' CNT COMMAND LIST
Public Const HpcCh1CounterRead = &H10                                  ' CH1 COUNTER READ, 32BIT
Public Const HpcCh1CounterWrite = &H90                                 ' CH1 COUNTER WRITE, 32BIT
Public Const HpcCh1CounterModeRead = &H11                              ' CH1 COUNTER MODE READ, 4BIT
Public Const HpcCh1CounterModeWrite = &H91                             ' CH1 COUNTER MODE WRITE, 4BIT
Public Const HpcCh1TriggerRegionLowerDataRead = &H12                   ' CH1 TRIGGER REGION LOWER DATA READ, 31BIT
Public Const HpcCh1TriggerRegionLowerDataWrite = &H92                  ' CH1 TRIGGER REGION LOWER DATA WRITE
Public Const HpcCh1TriggerRegionUpperDataRead = &H13                   ' CH1 TRIGGER REGION UPPER DATA READ, 31BIT
Public Const HpcCh1TriggerRegionUpperDataWrite = &H93                  ' CH1 TRIGGER REGION UPPER DATA WRITE
Public Const HpcCh1TriggerPeriodRead = &H14                            ' CH1 TRIGGER PERIOD READ, 31BIT
Public Const HpcCh1TriggerPeriodWrite = &H94                           ' CH1 TRIGGER PERIOD WRITE
Public Const HpcCh1TriggerPulseWidthRead = &H15                        ' CH1 TRIGGER PULSE WIDTH READ, 31BIT
Public Const HpcCh1TriggerPulseWidthWrite = &H95                       ' CH1 RIGGER PULSE WIDTH WRITE
Public Const HpcCh1TriggerModeRead = &H16                              ' CH1 TRIGGER MODE READ, 8BIT
Public Const HpcCh1TriggerModeWrite = &H96                             ' CH1 RIGGER MODE WRITE                 <<<<<<<<<<<<<<<<<<<<<<<<<  20160527 ¿©±â±îÁö ÀÛ¾÷
Public Const HpcCh1TriggerStatusRead = &H17                            ' CH1 TRIGGER STATUS READ, 8BIT
Public Const HpcCh1NoOperation_97 = &H97                               ' Reserved.
Public Const HpcCh1NoOperation_18 = &H17                               ' Reserved.
Public Const HpcCh1TriggerEnable = &H98                                ' CH1 TRIGGER ENABLE.
Public Const HpcCh1NoOperation_19 = &H19                               ' Reserved.
Public Const HpcCh1TriggerDisable = &H99                               ' CH1 TRIGGER DISABLE.
Public Const HpcCh1TimeTriggerFrequencyRead = &H1A                     ' CH1 TRIGGER FREQUNCE INFO. WRITE, 28BIT
Public Const HpcCh1TimeTriggerFrequencyWrite = &H9A                    ' CH1 TRIGGER FREQUNCE INFO. READ
Public Const HpcCh1Comparator1ValueRead = &H1B                         ' CH1 COMPAREATOR1 READ, 31BIT
Public Const HpcCh1Comparator1ValueWrite = &H9B                        ' CH1 COMPAREATOR1 WRITE, 31BIT
Public Const HpcCh1Comparator2ValueRead = &H1C                         ' CH1 COMPAREATOR2 READ, 31BIT
Public Const HpcCh1Comparator2ValueWrite = &H9C                        ' CH1 COMPAREATOR2 WRITE, 31BIT
Public Const HpcCh1CompareatorConditionRead = &H1D                     ' CH1 COMPAREATOR CONDITION READ, 4BIT
Public Const HpcCh1CompareatorConditionWrite = &H9D                    ' CH1 COMPAREATOR CONDITION WRITE, 4BIT
Public Const HpcCh1AbsTriggerTopPositionRead = &H1E                    ' CH1 ABS TRIGGER POSITION READ, 31BIT
Public Const HpcCh1AbsTriggerPositionWrite = &H9E                      ' CH1 ABS TRIGGER POSITION WRITE, 31BIT
Public Const HpcCh1AbsTriggerFifoStatusRead = &H1F                     ' CH1 ABS TRIGGER POSITION FIFO STATUS READ, 16BIT
Public Const HpcCh1AbsTriggerPositionClear = &H9F                      ' CH1 ABS TRIGGER POSITION FIFO CLEAR

    ' CH-2 Group Register
Public Const HpcCh2CounterRead = &H20                                  ' CH2 COUNTER READ, 32BIT
Public Const HpcCh2CounterWrite = &HA0                                 ' CH2 COUNTER WRITE, 32BIT
Public Const HpcCh2CounterModeRead = &H21                              ' CH2 COUNTER MODE READ, 4BIT
Public Const HpcCh2CounterModeWrite = &HA1                             ' CH2 COUNTER MODE WRITE, 4BIT
Public Const HpcCh2TriggerRegionLowerDataRead = &H22                   ' CH2 TRIGGER REGION LOWER DATA READ, 31BIT
Public Const HpcCh2TriggerRegionLowerDataWrite = &HA2                  ' CH2 TRIGGER REGION LOWER DATA WRITE
Public Const HpcCh2TriggerRegionUpperDataRead = &H23                   ' CH2 TRIGGER REGION UPPER DATA READ, 31BIT
Public Const HpcCh2TriggerRegionUpperDataWrite = &HA3                  ' CH2 TRIGGER REGION UPPER DATA WRITE
Public Const HpcCh2TriggerPeriodRead = &H24                            ' CH2 TRIGGER PERIOD READ, 31BIT
Public Const HpcCh2TriggerPeriodWrite = &HA4                           ' CH2 TRIGGER PERIOD WRITE
Public Const HpcCh2TriggerPulseWidthRead = &H25                        ' CH2 TRIGGER PULSE WIDTH READ, 31BIT
Public Const HpcCh2TriggerPulseWidthWrite = &HA5                       ' CH2 RIGGER PULSE WIDTH WRITE
Public Const HpcCh2TriggerModeRead = &H26                              ' CH2 TRIGGER MODE READ, 8BIT
Public Const HpcCh2TriggerModeWrite = &HA6                             ' CH2 RIGGER MODE WRITE
Public Const HpcCh2TriggerStatusRead = &H27                            ' CH2 TRIGGER STATUS READ, 8BIT
Public Const HpcCh2NoOperation_97 = &HA7                               ' Reserved.
Public Const HpcCh2NoOperation_18 = &H27                               ' Reserved.
Public Const HpcCh2TriggerEnable = &HA8                                ' CH2 TRIGGER ENABLE.
Public Const HpcCh2NoOperation_19 = &H29                               ' Reserved.
Public Const HpcCh2TriggerDisable = &HA9                               ' CH2 TRIGGER DISABLE.
Public Const HpcCh2TimeTriggerFrequencyRead = &H2A                     ' CH2 TRIGGER FREQUNCE INFO. WRITE, 28BIT
Public Const HpcCh2TimeTriggerFrequencyWrite = &HAA                    ' CH2 TRIGGER FREQUNCE INFO. READ
Public Const HpcCh2Comparator1ValueRead = &H2B                         ' CH2 COMPAREATOR1 READ, 31BIT
Public Const HpcCh2Comparator1ValueWrite = &HAB                        ' CH2 COMPAREATOR1 WRITE, 31BIT
Public Const HpcCh2Comparator2ValueRead = &H2C                         ' CH2 COMPAREATOR2 READ, 31BIT
Public Const HpcCh2Comparator2ValueWrite = &HAC                        ' CH2 COMPAREATOR2 WRITE, 31BIT
Public Const HpcCh2CompareatorConditionRead = &H2D                     ' CH2 COMPAREATOR CONDITION READ, 4BIT
Public Const HpcCh2CompareatorConditionWrite = &HAD                    ' CH2 COMPAREATOR CONDITION WRITE, 4BIT
Public Const HpcCh2AbsTriggerTopPositionRead = &H2E                    ' CH2 ABS TRIGGER POSITION READ, 31BIT
Public Const HpcCh2AbsTriggerPositionWrite = &HAE                      ' CH2 ABS TRIGGER POSITION WRITE, 31BIT
Public Const HpcCh2AbsTriggerFifoStatusRead = &H2F                     ' CH2 ABS TRIGGER POSITION FIFO STATUS READ, 16BIT
Public Const HpcCh2AbsTriggerPositionClear = &HAF                      ' CH2 ABS TRIGGER POSITION FIFO CLEAR

    ' CH-3 Group Register
Public Const HpcCh3CounterRead = &H30                                  ' CH3 COUNTER READ, 32BIT
Public Const HpcCh3CounterWrite = &HB0                                 ' CH3 COUNTER WRITE, 32BIT
Public Const HpcCh3CounterModeRead = &H31                              ' CH3 COUNTER MODE READ, 4BIT
Public Const HpcCh3CounterModeWrite = &HB1                             ' CH3 COUNTER MODE WRITE, 4BIT
Public Const HpcCh3TriggerRegionLowerDataRead = &H32                   ' CH3 TRIGGER REGION LOWER DATA READ, 31BIT
Public Const HpcCh3TriggerRegionLowerDataWrite = &HB2                  ' CH3 TRIGGER REGION LOWER DATA WRITE
Public Const HpcCh3TriggerRegionUpperDataRead = &H33                   ' CH3 TRIGGER REGION UPPER DATA READ, 31BIT
Public Const HpcCh3TriggerRegionUpperDataWrite = &HB3                  ' CH3 TRIGGER REGION UPPER DATA WRITE
Public Const HpcCh3TriggerPeriodRead = &H34                            ' CH3 TRIGGER PERIOD READ, 31BIT
Public Const HpcCh3TriggerPeriodWrite = &HB4                           ' CH3 TRIGGER PERIOD WRITE
Public Const HpcCh3TriggerPulseWidthRead = &H35                        ' CH3 TRIGGER PULSE WIDTH READ, 31BIT
Public Const HpcCh3TriggerPulseWidthWrite = &HB5                       ' CH3 RIGGER PULSE WIDTH WRITE
Public Const HpcCh3TriggerModeRead = &H36                              ' CH3 TRIGGER MODE READ, 8BIT
Public Const HpcCh3TriggerModeWrite = &HB6                             ' CH3 RIGGER MODE WRITE
Public Const HpcCh3TriggerStatusRead = &H37                            ' CH3 TRIGGER STATUS READ, 8BIT
Public Const HpcCh3NoOperation_97 = &HB7                               ' Reserved.
Public Const HpcCh3NoOperation_18 = &H37                               ' Reserved.
Public Const HpcCh3TriggerEnable = &HB8                                ' CH3 TRIGGER ENABLE.
Public Const HpcCh3NoOperation_19 = &H39                               ' Reserved.
Public Const HpcCh3TriggerDisable = &HB9                               ' CH3 TRIGGER DISABLE.
Public Const HpcCh3TimeTriggerFrequencyRead = &H3A                     ' CH3 TRIGGER FREQUNCE INFO. WRITE, 28BIT
Public Const HpcCh3TimeTriggerFrequencyWrite = &HBA                    ' CH3 TRIGGER FREQUNCE INFO. READ
Public Const HpcCh3Comparator1ValueRead = &H3B                         ' CH3 COMPAREATOR1 READ, 31BIT
Public Const HpcCh3Comparator1ValueWrite = &HBB                        ' CH3 COMPAREATOR1 WRITE, 31BIT
Public Const HpcCh3Comparator2ValueRead = &H3C                         ' CH3 COMPAREATOR2 READ, 31BIT
Public Const HpcCh3Comparator2ValueWrite = &HBC                        ' CH3 COMPAREATOR2 WRITE, 31BIT
Public Const HpcCh3CompareatorConditionRead = &H3D                     ' CH3 COMPAREATOR CONDITION READ, 4BIT
Public Const HpcCh3CompareatorConditionWrite = &HBD                    ' CH3 COMPAREATOR CONDITION WRITE, 4BIT
Public Const HpcCh3AbsTriggerTopPositionRead = &H3E                    ' CH3 ABS TRIGGER POSITION READ, 31BIT
Public Const HpcCh3AbsTriggerPositionWrite = &HBE                      ' CH3 ABS TRIGGER POSITION WRITE, 31BIT
Public Const HpcCh3AbsTriggerFifoStatusRead = &H3F                     ' CH3 ABS TRIGGER POSITION FIFO STATUS READ, 16BIT
Public Const HpcCh3AbsTriggerPositionClear = &HBF                      ' CH3 ABS TRIGGER POSITION FIFO CLEAR

    ' CH-4 Group Register
Public Const HpcCh4CounterRead = &H40                                  ' CH4 COUNTER READ, 32BIT
Public Const HpcCh4CounterWrite = &HC0                                 ' CH4 COUNTER WRITE, 32BIT
Public Const HpcCh4CounterModeRead = &H41                              ' CH4 COUNTER MODE READ, 4BIT
Public Const HpcCh4CounterModeWrite = &HC1                             ' CH4 COUNTER MODE WRITE, 4BIT
Public Const HpcCh4TriggerRegionLowerDataRead = &H42                   ' CH4 TRIGGER REGION LOWER DATA READ, 31BIT
Public Const HpcCh4TriggerRegionLowerDataWrite = &HC2                  ' CH4 TRIGGER REGION LOWER DATA WRITE
Public Const HpcCh4TriggerRegionUpperDataRead = &H43                   ' CH4 TRIGGER REGION UPPER DATA READ, 31BIT
Public Const HpcCh4TriggerRegionUpperDataWrite = &HC3                  ' CH4 TRIGGER REGION UPPER DATA WRITE
Public Const HpcCh4TriggerPeriodRead = &H44                            ' CH4 TRIGGER PERIOD READ, 31BIT
Public Const HpcCh4TriggerPeriodWrite = &HC4                           ' CH4 TRIGGER PERIOD WRITE
Public Const HpcCh4TriggerPulseWidthRead = &H45                        ' CH4 TRIGGER PULSE WIDTH READ, 31BIT
Public Const HpcCh4TriggerPulseWidthWrite = &HC5                       ' CH4 RIGGER PULSE WIDTH WRITE
Public Const HpcCh4TriggerModeRead = &H46                              ' CH4 TRIGGER MODE READ, 8BIT
Public Const HpcCh4TriggerModeWrite = &HC6                             ' CH4 RIGGER MODE WRITE
Public Const HpcCh4TriggerStatusRead = &H47                            ' CH4 TRIGGER STATUS READ, 8BIT
Public Const HpcCh4NoOperation_97 = &HC7                               ' Reserved.
Public Const HpcCh4NoOperation_18 = &H47                               ' Reserved.
Public Const HpcCh4TriggerEnable = &HC8                                ' CH4 TRIGGER ENABLE.
Public Const HpcCh4NoOperation_19 = &H49                               ' Reserved.
Public Const HpcCh4TriggerDisable = &HC9                               ' CH4 TRIGGER DISABLE.
Public Const HpcCh4TimeTriggerFrequencyRead = &H4A                     ' CH4 TRIGGER FREQUNCE INFO. WRITE, 28BIT
Public Const HpcCh4TimeTriggerFrequencyWrite = &HCA                    ' CH4 TRIGGER FREQUNCE INFO. READ
Public Const HpcCh4Comparator1ValueRead = &H4B                         ' CH4 COMPAREATOR1 READ, 31BIT
Public Const HpcCh4Comparator1ValueWrite = &HCB                        ' CH4 COMPAREATOR1 WRITE, 31BIT
Public Const HpcCh4Comparator2ValueRead = &H4C                         ' CH4 COMPAREATOR2 READ, 31BIT
Public Const HpcCh4Comparator2ValueWrite = &HCC                        ' CH4 COMPAREATOR2 WRITE, 31BIT
Public Const HpcCh4CompareatorConditionRead = &H4D                     ' CH4 COMPAREATOR CONDITION READ, 4BIT
Public Const HpcCh4CompareatorConditionWrite = &HCD                    ' CH4 COMPAREATOR CONDITION WRITE, 4BIT
Public Const HpcCh4AbsTriggerTopPositionRead = &H4E                    ' CH4 ABS TRIGGER POSITION READ, 31BIT
Public Const HpcCh4AbsTriggerPositionWrite = &HCE                      ' CH4 ABS TRIGGER POSITION WRITE, 31BIT
Public Const HpcCh4AbsTriggerFifoStatusRead = &H4F                     ' CH4 ABS TRIGGER POSITION FIFO STATUS READ, 16BIT
Public Const HpcCh4AbsTriggerPositionClear = &HCF                      ' CH4 ABS TRIGGER POSITION FIFO CLEAR

    ' Ram Access Group Register
Public Const HpcRamDataWithRamAddress = &H51                           ' READ RAM DATA WITH RAM ADDR PORT ADDRESS
Public Const HpcRamDataWrite = &HD0                                    ' RAM DATA WRITE
Public Const HpcRamDataRead = &H50                                     ' RAM DATA READ, 32BIT

    ' Debugging Registers
Public Const HpcCh1TrigPosIndexRead = &H60                             ' CH1 Current RAM trigger index position on 32Bit data, 8BIT
Public Const HpcCh1TrigBackwardDataRead = &H61                         ' CH1 Current RAM trigger backward position data, 32BIT
Public Const HpcCh1TrigCurrentDataRead = &H62                          ' CH1 Current RAM trigger current position data, 32BIT
Public Const HpcCh1TrigForwardDataRead = &H63                          ' CH1 Current RAM trigger next position data, 32BIT
Public Const HpcCh1TrigRamAddressRead = &H64                           ' CH1 Current RAM trigger address, 20BIT

Public Const HpcCh2TrigPosIndexRead = &H65                             ' CH2 Current RAM trigger index position on 32Bit data, 8BIT
Public Const HpcCh2TrigBackwardDataRead = &H66                         ' CH2 Current RAM trigger backward position data, 32BIT
Public Const HpcCh2TrigCurrentDataRead = &H67                          ' CH2 Current RAM trigger current position data, 32BIT
Public Const HpcCh2TrigForwardDataRead = &H68                          ' CH2 Current RAM trigger next position data, 32BIT
Public Const HpcCh2TrigRamAddressRead = &H69                           ' CH2 Current RAM trigger address, 20BIT

Public Const HpcCh3TrigPosIndexRead = &H70                             ' CH3 Current RAM trigger index position on 32Bit data, 8BIT
Public Const HpcCh3TrigBackwardDataRead = &H71                         ' CH3 Current RAM trigger backward position data, 32BIT
Public Const HpcCh3TrigCurrentDataRead = &H72                          ' CH3 Current RAM trigger current position data, 32BIT
Public Const HpcCh3TrigForwardDataRead = &H73                          ' CH3 Current RAM trigger next position data, 32BIT
Public Const HpcCh3TrigRamAddressRead = &H74                           ' CH3 Current RAM trigger address, 20BIT

Public Const HpcCh4TrigPosIndexRead = &H75                             ' CH4 Current RAM trigger index position on 32Bit data, 8BIT
Public Const HpcCh4TrigBackwardDataRead = &H76                         ' CH4 Current RAM trigger backward position data, 32BIT
Public Const HpcCh4TrigCurrentDataRead = &H77                          ' CH4 Current RAM trigger current position data, 32BIT
Public Const HpcCh4TrigForwardDataRead = &H78                          ' CH4 Current RAM trigger next position data, 32BIT
Public Const HpcCh4TrigRamAddressRead = &H79                           ' CH4 Current RAM trigger address, 20BIT

Public Const HpcCh1TestEnable = &H81                                   ' CH1 test enable(Manufacturer only)
Public Const HpcCh2TestEnable = &H82                                   ' CH2 test enable(Manufacturer only)
Public Const HpcCh3TestEnable = &H83                                   ' CH3 test enable(Manufacturer only)
Public Const HpcCh4TestEnable = &H84                                   ' CH4 test enable(Manufacturer only)

Public Const HpcTestFrequency = &H8C                                   ' Test counter output frequency(32bit)
Public Const HpcTestCountStart = &H8D                                  ' Start test counter output with position(32bit signed).
Public Const HpcTestCountEnd = &H8E                                    ' End counter output.

Public Const HpcCh1TrigVectorTopDataOfFifo = &H54                      ' CH1 UnitVector X positin of FIFO top.
Public Const HpcCh1TrigVectorFifoStatus = &H55                         ' CH1 UnitVector X FIFO Status.
Public Const HpcCh2TrigVectorTopDataOfFifo = &H56                      ' CH2 UnitVector Y positin of FIFO top.
Public Const HpcCh2TrigVectorFifoStatus = &H57                         ' CH2 UnitVector Y FIFO Status.
Public Const HpcCh1TrigVectorFifoPush = &HD2                           ' CH1 UnitVector X position, fifo data push.
Public Const HpcCh2TrigVectorFifoPush = &HD3                           ' CH2 UnitVector Y position, fifo data push.