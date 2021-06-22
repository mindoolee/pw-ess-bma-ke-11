//****************************************************************************
//****************************************************************************
//**
//** File Name
//** ---------
//**
//** AXHS.PAS
//**
//** COPYRIGHT (c) AJINEXTEK Co., LTD
//**
//*****************************************************************************
//*****************************************************************************
//**
//** Description
//** -----------
//** Resource Define Header File
//** 
//**
//*****************************************************************************
//*****************************************************************************
//**
//** Source Change Indices
//** ---------------------
//** 
//** (None)
//**
//**
//*****************************************************************************
//*****************************************************************************
//**
//** Website
//** ---------------------
//**
//** http://www.ajinextek.com
//**
//*****************************************************************************
//*****************************************************************************

unit AXHS;

interface
uses Windows, Messages;

    type AXT_INTERRUPT_PROC = procedure(lActiveNo : LongInt; uFlag : DWord); stdcall;
    type AXT_EVENT_PROC = procedure(lActiveNo : LongInt; uFlag : DWord); stdcall;

const
    WM_USER                             = $0400;
    WM_AXL_INTERRUPT                    = (WM_USER + 1001);
    {  베이스보드 정의                  }
    AXT_UNKNOWN                         = $00;          // Unknown Baseboard
    AXT_BIHR                            = $01;          // ISA bus, Half size
    AXT_BIFR                            = $02;          // ISA bus, Full size
    AXT_BPHR                            = $03;          // PCI bus, Half size
    AXT_BPFR                            = $04;          // PCI bus, Full size
    AXT_BV3R                            = $05;          // VME bus, 3U size
    AXT_BV6R                            = $06;          // VME bus, 6U size
    AXT_BC3R                            = $07;          // cPCI bus, 3U size
    AXT_BC6R                            = $08;          // cPCI bus, 6U size
    AXT_BEHR                            = $09;          // PCIe bus, Half size
    AXT_BEFR                            = $0A;          // PCIe bus, Full size
    AXT_BEHD                            = $0B;          // PCIe bus, Half size, DB-32T
    AXT_FMNSH4D                         = $52;          // ISA bus, Full size, DB-32T, SIO-2V03 * 2
    AXT_PCI_DI64R                       = $43;          // PCI bus, Digital IN 64점
    AXT_PCIE_DI64R                      = $44;          // PCIe bus, Digital IN 64점
    AXT_PCI_DO64R                       = $53;          // PCI bus, Digital OUT 64점
    AXT_PCIE_DO64R                      = $54;          // PCIe bus, Digital OUT 64점
    AXT_PCI_DB64R                       = $63;          // PCI bus, Digital IN 32점, OUT 32점
    AXT_PCIE_DB64R                      = $64;          // PCIe bus, Digital IN 32점, OUT 32점
    AXT_PCIN204                         = $82;          // PCI bus, Half size On-Board 2 Axis controller.    
    AXT_BPHD                            = $83;          // PCI bus, Half size, DB-32T
    AXT_PCIN404                         = $84;          // PCI bus, Half size On-Board 4 Axis controller.
    AXT_PCIN804                         = $85;          // PCI bus, Half size On-Board 8 Axis controller.
    AXT_PCIEN804                        = $86;          // PCIe bus, Half size On-Board 8 Axis controller.
    AXT_PCIEN404                        = $87;          // PCIe bus, Half size On-Board 4 Axis controller.
    AXT_PCI_AIO1602HR                   = $93;          // PCI bus, Half size, AI-16ch, AO-2ch AI16HR
    AXT_PCI_R1604                       = $C1;          // PCI bus[PCI9030], Half size, RTEX based 16 axis controller
    AXT_PCI_R3204                       = $C2;          // PCI bus[PCI9030], Half size, RTEX based 32 axis controller
    AXT_PCI_R32IO                       = $C3;          // PCI bus[PCI9030], Half size, RTEX based IO only.
    AXT_PCI_REV2                        = $C4;          // Reserved.
    AXT_PCI_R1604MLII                   = $C5;          // PCI bus[PCI9030], Half size, Mechatrolink-II 16/32 axis controller.
    AXT_PCI_R0804MLII                   = $C6;          // PCI bus[PCI9030], Half size, Mechatrolink-II 08 axis controller.
    AXT_PCI_Rxx00MLIII                  = $C7;          // Master PCI Board, Mechatrolink III AXT, PCI Bus[PCI9030], Half size, Max.32 Slave module support
    AXT_PCIE_Rxx00MLIII                 = $C8;          // Master PCI Express Board, Mechatrolink III AXT, PCI Bus[], Half size, Max.32 Slave module support
    AXT_PCP2_Rxx00MLIII                 = $C9;          // Master PCI/104-Plus Board, Mechatrolink III AXT, PCI Bus[], Half size, Max.32 Slave module support
    AXT_PCI_R1604SIIIH                  = $CA;          // PCI bus[PCI9030], Half size, SSCNET III / H 16/32 axis controller.
     AXT_PCI_R32IOEV                    = $CB;          // PCI bus[PCI9030], Half size, RTEX based IO only. Economic version.
    AXT_PCIE_R0804RTEX                  = $CC;          // PCIe bus, Half size, Half size, RTEX based 08 axis controller.
    AXT_PCIE_R1604RTEX                  = $CD;          // PCIe bus, Half size, Half size, RTEX based 16 axis controller.
    AXT_PCIE_R2404RTEX                  = $CE;          // PCIe bus, Half size, Half size, RTEX based 24 axis controller.
    AXT_PCIE_R3204RTEX                  = $CF;          // PCIe bus, Half size, Half size, RTEX based 32 axis controller.
    AXT_PCIE_Rxx04SIIIH                 = $D0;          // PCIe bus, Half size, SSCNET III / H 16(or 32)-axis(CAMC-QI based) controller.
    AXT_PCIE_Rxx00SIIIH                 = $D1;          // PCIe bus, Half size, SSCNET III / H Max. 32-axis(DSP Based) controller.
	AXT_ETHERCAT_RTOSV5                 = $D2;          // EtherCAT, RTOS(On Time), Version 5.29
    AXT_PCI_Nx04_A                      = $D3;	        // PCI bus, Half size On-Board x Axis controller For Rtos.
    AXT_PCI_R3200MLIII_IO               = $D4;          // PCI Board, Mechatrolink III AXT, PCI Bus[PCI9030], Half size, Max.32 IO only	controller
    AXT_PCIE_R3205MLIII                 = $D5;          // PCIe bus, Half size, Mechatrolink III / H Max. 32-axis(DSP Based) controller.

    { 모듈제품 정의                     }
    AXT_SMC_2V01                        = $01;          // CAMC-5M, 2 Axis
    AXT_SMC_2V02                        = $02;          // CAMC-FS, 2 Axis
    AXT_SMC_1V01                        = $03;          // CAMC-5M, 1 Axis
    AXT_SMC_1V02                        = $04;          // CAMC-FS, 1 Axis
    AXT_SMC_2V03                        = $05;          // CAMC-IP, 2 Axis
    AXT_SMC_4V04                        = $06;          // CAMC-QI, 4 Axis
    AXT_SMC_R1V04A4                     = $07;          // CAMC-QI, 1 Axis, For RTEX A4 slave only
    AXT_SMC_1V03                        = $08;          // CAMC-IP, 1 Axis
    AXT_SMC_R1V04                       = $09;          // CAMC-QI, 1 Axis, For RTEX SLAVE only
    AXT_SMC_R1V04MLIISV                 = $0A;          // CAMC-QI, 1 Axis, For Sigma-X series.
    AXT_SMC_R1V04MLIIPM                 = $0B;          // 2 Axis, For Pulse output series(JEPMC-PL2910).
    AXT_SMC_2V04                        = $0C;          // CAMC-QI, 2 Axis        
    AXT_SMC_R1V04A5                     = $0D;          // CAMC-QI, 1 Axis, For RTEX A5N slave only
    AXT_SMC_R1V04MLIICL                 = $0E;          // CAMC-QI, 1 Axis, For MLII Convex Linear only
    AXT_SMC_R1V04MLIICR                 = $0F;          // CAMC-QI, 1 Axis, For MLII Convex Rotary only
    AXT_SMC_R1V04PM2Q                   = $10;          // CAMC-QI, 2 Axis, For RTEX SLAVE only(Pulse Output Module)
    AXT_SMC_R1V04PM2QE                  = $11;          // CAMC-QI, 4 Axis, For RTEX SLAVE only(Pulse Output Module)
    AXT_SMC_R1V04MLIIORI                = $12;          // CAMC-QI, 1 Axis, For MLII Oriental Step Driver only
    AXT_SMC_R1V04SIIIHMIV               = $14;          // CAMC-QI, 1 Axis, For SSCNETIII/H MRJ4
    AXT_SMC_R1V04SIIIHMIV_R             = $15;          // CAMC-QI, 1 Axis, For SSCNETIII/H MRJ4
    AXT_SMC_R1V04MLIIISV                = $20;          // DSP, 1 Axis, For ML-3 SigmaV/YASKAWA only 
    AXT_SMC_R1V04MLIIIPM                = $21;          // DSP, 1 Axis, For ML-3 SLAVE/AJINEXTEK only(Pulse Output Module)
    AXT_SMC_R1V04MLIIISV_MD             = $22;          // DSP, 1 Axis, For ML-3 SigmaV-MD/YASKAWA only (Multi-Axis Control amp)
    AXT_SMC_R1V04MLIIIS7S               = $23;          // DSP, 1 Axis, For ML-3 Sigma7S/YASKAWA only
    AXT_SMC_R1V04MLIIIS7W               = $24;          // DSP, 2 Axis, For ML-3 Sigma7W/YASKAWA only(Dual-Axis control amp)
    AXT_SMC_R1V04MLIIIRS2               = $25;          // DSP, 1 Axis, For ML-3 RS2A/SANYO DENKY
    AXT_SMC_R1V04MLIIIS7_MD             = $26;          // DSP, 1 Axis, For ML-3 Sigma7-MD/YASKAWA only (Multi-Axis Control amp)
    AXT_SMC_PM2QSIIIH                   = $60;          // CAMC-QI, 2Axis For SSCNETIII/H SLAVE only(Pulse Output Module)
    AXT_SMC_PM4QSIIIH                   = $61;         // CAMC-QI, 4Axis For SSCNETIII/H SLAVE only(Pulse Output Module)
    AXT_SIO_CNT2SIIIH                   = $62;          // Counter slave module, Reversible counter, 2 channels, For SSCNETIII/H Only
    AXT_SIO_DI32SIIIH                   = $63;          // DI slave module, SSCNETIII AXT, IN 32-Channel
    AXT_SIO_DO32SIIIH                   = $64;          // DO slave module, SSCNETIII AXT, OUT 32-Channel
    AXT_SIO_DB32SIIIH                   = $65;          // DB slave module, SSCNETIII AXT, IN 16-Channel, OUT 16-Channel
    AXT_SIO_AI16SIIIH                   = $66;          // AI slave module, SSCNETIII AXT, Analog IN 16ch, 16 bit
    AXT_SIO_AO08SIIIH                   = $67;          // A0 slave module, SSCNETIII AXT, Analog OUT 8ch, 16 bit
    AXT_SMC_PM2QSIIIH_R                 = $68;          // CAMC-QI, 2Axis For SSCNETIII/H SLAVE only(Pulse Output Module)
    AXT_SMC_PM4QSIIIH_R                 = $69;          // CAMC-QI, 4Axis For SSCNETIII/H SLAVE only(Pulse Output Module)
    AXT_SIO_CNT2SIIIH_R                 = $6A;          // Counter slave module, Reversible counter, 2 channels, For SSCNETIII/H Only
    AXT_SIO_DI32SIIIH_R                 = $6B;          // DI slave module, SSCNETIII AXT, IN 32-Channel
    AXT_SIO_DO32SIIIH_R                 = $6C;          // DO slave module, SSCNETIII AXT, OUT 32-Channel
    AXT_SIO_DB32SIIIH_R                 = $6D;          // DB slave module, SSCNETIII AXT, IN 16-Channel, OUT 16-Channel
    AXT_SIO_AI16SIIIH_R                 = $6E;          // AI slave module, SSCNETIII AXT, Analog IN 16ch, 16 bit
    AXT_SIO_AO08SIIIH_R                 = $6F;          // A0 slave module, SSCNETIII AXT, Analog OUT 8ch, 16 bit
    AXT_SIO_RDI32MLIII                  = $70;          // DI slave module, MechatroLink III AXT, IN 32-Channel NPN
    AXT_SIO_RDO32MLIII                  = $71;          // DO slave module, MechatroLink III AXT, OUT 32-Channel  NPN
    AXT_SIO_RDB32MLIII                  = $72;          // DB slave module, MechatroLink III AXT, IN 16-Channel, OUT 16-Channel  NPN
    AXT_SIO_RDI32MSMLIII                = $73;          // DI slave module, MechatroLink III M-SYSTEM, IN 32-Channel
    AXT_SIO_RDO32AMSMLIII               = $74;          // DO slave module, MechatroLink III M-SYSTEM, OUT 32-Channel
    AXT_SIO_RDI32PMLIII                 = $75;          // DI slave module, MechatroLink III AXT, IN 32-Channel PNP
    AXT_SIO_RDO32PMLIII                 = $76;          // DO slave module, MechatroLink III AXT, OUT 32-Channel  PNP
    AXT_SIO_RDB32PMLIII                 = $77;          // DB slave module, MechatroLink III AXT, IN 16-Channel, OUT 16-Channel  PNP
    AXT_SIO_RDI16MLIII                  = $78;          // DI slave module, MechatroLink III M-SYSTEM, IN 16-Channel
    AXT_SIO_UNDEFINEMLIII               = $79;          // IO slave module, MechatroLink III Any, Max. IN 480-Channel, Max. OUT 480-Channel
    AXT_SIO_RDI32MLIIISFA	            = $7A;          // DI slave module, MechatroLink III AXT(SFA), IN 32-Channel NPN
	AXT_SIO_RDO32MLIIISFA	            = $7B;          // DO slave module, MechatroLink III AXT(SFA), OUT 32-Channel  NPN
	AXT_SIO_RDB32MLIIISFA	            = $7C;          // DB slave module, MechatroLink III AXT(SFA), IN 16-Channel, OUT 16-Channel  NPN
    AXT_SIO_RDB128MLIIIAI               = $7D;          // Intelligent I/O (Product by IAI), For MLII only
    AXT_SIO_RSIMPLEIOMLII               = $7E;          // Digital IN/Out xx점, Simple I/O sereies, MLII 전용.
    AXT_SIO_RDO16AMLIII                 = $7F;          // DO slave module, MechatroLink III M-SYSTEM, OUT 16-Channel, NPN
    AXT_SIO_RDI16MLII                   = $80;          // DISCRETE INPUT MODULE, 16 points (Product by M-SYSTEM), For MLII only
    AXT_SIO_RDO16AMLII                  = $81;          // NPN TRANSISTOR OUTPUT MODULE, 16 points (Product by M-SYSTEM), For MLII only
    AXT_SIO_RDO16BMLII                  = $82;          // PNP TRANSISTOR OUTPUT MODULE, 16 points (Product by M-SYSTEM), For MLII only
    AXT_SIO_RDB96MLII                   = $83;          // Digital IN/OUT(Selectable), MAX 96 points, For MLII only
    AXT_SIO_RDO32RTE                    = $84;          // Digital OUT  32점
    AXT_SIO_RDI32RTEX                   = $85;          // Digital IN  32점
    AXT_SIO_RDB32RTEX                   = $86;          // Digital IN/OUT  32점
	AXT_SIO_RDO16BMLIII                 = $8A;          // DO slave module, MechatroLink III M-SYSTEM, OUT 16-Channel, PNP
	AXT_SIO_RDB32ML2NT1                 = $8B,          // DB slave module, MechatroLink2 AJINEXTEK NT1 Series
    AXT_SIO_RDB128YSMLIII               = $8C,          // IO slave module, MechatroLink III Any, Max. IN 480-Channel, Max. OUT 480-Channel
    AXT_SIO_DI32_P                      = $92;          // Digital IN  32점, PNP type(source type)
    AXT_SIO_DO32T_P                     = $93;          // Digital OUT 32점, Power TR, PNT type(source type)
    AXT_SIO_RDB128MLII                  = $94;          // Digital IN 64점 / OUT 64점, MLII 전용(JEPMC-IO2310)
    AXT_SIO_RDI32                       = $95;          // Digital IN  32점, For RTEX only
    AXT_SIO_RDO32                       = $96;          // Digital OUT 32점, For RTEX only
    AXT_SIO_DI32                        = $97;          // Digital IN  32점
    AXT_SIO_DO32P                       = $98;          // Digital OUT 32점
    AXT_SIO_DB32P                       = $99;          // Digital IN 16점 / OUT 16점
    AXT_SIO_RDB32T                      = $9A;          // Digital IN 16점 / OUT 16점, For RTEX only
    AXT_SIO_DO32T                       = $9E;          // Digital OUT 16점, Power TR 출력
    AXT_SIO_DB32T                       = $9F;          // Digital IN 16점 / OUT 16점, Power TR 출력
    AXT_SIO_RAI16RB                     = $A0;          // A0h(160) : AI 16Ch, 16 bit, For RTEX only
    AXT_SIO_AI4RB                       = $A1;          // A1h(161) : AI 4Ch, 12 bit
    AXT_SIO_AO4RB                       = $A2;          // A2h(162) : AO 4Ch, 12 bit
    AXT_SIO_AI16H                       = $A3;          // A3h(163) : AI 4Ch, 16 bit
    AXT_SIO_AO8H                        = $A4;          // A4h(164) : AO 4Ch, 16 bit
    AXT_SIO_AI16HB                      = $A5;          // A5h(165) : AI 16Ch, 16 bit (SIO-AI16HR(input module))
    AXT_SIO_AO2HB                       = $A6;          // A6h(166) : AO 2Ch, 16 bit  (SIO-AI16HR(output module))
    AXT_SIO_RAI8RB                      = $A7;          // A1h(167) : AI 8Ch, 16 bit, For RTEX only
    AXT_SIO_RAO4RB                      = $A8;          // A2h(168) : AO 4Ch, 16 bit, For RTEX only
    AXT_SIO_RAI4MLII                    = $A9;          // A9h(169) : AI 4Ch, 16 bit, For MLII only
    AXT_SIO_RAI16RB                     = $A0;          // A0h(160) : AI 16Ch, 16 bit, For RTEX only
    AXT_SIO_RAO2MLII                    = $AA;          // AAh(170) : AO 2Ch, 16 bit, For MLII only
    AXT_SIO_RAVCI4MLII                  = $AB;          // DC VOLTAGE/CURRENT INPUT MODULE, 4 points (Product by M-SYSTEM), For MLII only
    AXT_SIO_RAVO2MLII                   = $AC;          // DC VOLTAGE OUTPUT MODULE, 2 points (Product by M-SYSTEM), For MLII only
    AXT_SIO_RACO2MLII                   = $AD;          // DC CURRENT OUTPUT MODULE, 2 points (Product by M-SYSTEM), For MLII only
    AXT_SIO_RATI4MLII                   = $AE;          // THERMOCOUPLE INPUT MODULE, 4 points (Product by M-SYSTEM), For MLII only
    AXT_SIO_RARTDI4MLII                 = $AF;          // RTD INPUT MODULE, 4 points (Product by M-SYSTEM), For MLII only
    AXT_SIO_RCNT2MLII                   = $B0;          // Counter Module Reversible counter, 2 channels (Product by YASKWA)    
    AXT_SIO_CN2CH                       = $B1;          // Counter Module, 2 channels, Remapped ID, Actual ID is (0xA8)
    AXT_SIO_RCNT2RTEX                   = $B2;          // Counter slave module, Reversible counter, 2 channels, For RTEX Only
    AXT_SIO_RCNT2MLIII                  = $B3;          // Counter slave moudle, MechatroLink III AXT, 2 ch, Trigger per channel
    AXT_SIO_RHPC4MLIII                  = $B4;          // Counter slave moudle, MechatroLink III AXT, 4 ch
    AXT_SIO_RAI16RTEX                   = $C0;          // ANALOG VOLTAGE INPUT(+- 10V) 16 Channel RTEX
    AXT_SIO_RAO08RTEX                   = $C1;          // ANALOG VOLTAGE OUTPUT(+- 10V) 08 Channel RTEX
    AXT_SIO_RAI8MLIII                   = $C2;          // AI slave module, MechatroLink III AXT, Analog IN 8ch, 16 bit
    AXT_SIO_RAI16MLIII                  = $C3;          // AI slave module, MechatroLink III AXT, Analog IN 16ch, 16 bit
    AXT_SIO_RAO4MLIII                   = $C4;          // A0 slave module, MechatroLink III AXT, Analog OUT 4ch, 16 bit
    AXT_SIO_RAO8MLIII                   = $C5;          // A0 slave module, MechatroLink III AXT, Analog OUT 8ch, 16 bit
    AXT_SIO_RAVO4MLII                   = $C6;          // DC VOLTAGE OUTPUT MODULE, 4 points (Product by M-SYSTEM), For MLII only
    AXT_SIO_RAV04MLIII                  = $C7;          // AO Slave module, MechatroLink III M-SYSTEM Voltage output module
    AXT_SIO_RAVI4MLIII                  = $C8;          // AI Slave module, MechatroLink III M-SYSTEM Voltage/Current input module
    AXT_SIO_RAI16MLIIISFA               = $C9;          // AI slave module, MechatroLink III AXT(SFA), Analog IN 16ch, 16 bit	
    AXT_SIO_RDB32MSMLIII                = $CA;          // DIO slave module; MechatroLink III M-SYSTEM; IN 16-Channel; OUT 16-Channel
    AXT_COM_234R                        = $D3;          // COM-234R
    AXT_COM_484R                        = $D4;          // COM-484R
    AXT_SIO_RPI2                        = $D5;          // Pulse counter module(JEPMC-2900)
    AXT_SIO_HPC4                        = $D6;          // D6h : External Encoder module for 4Channel with Trigger function.
    AXT_SIO_AO4F                        = $D7;          // D7h : AO 4Ch, 16 bit
    AXT_SIO_AI8F                        = $D8;          // D8h : AI 8Ch, 16 bit
    AXT_SIO_AI8AO4F                     = $D9;          // AI 8Ch, AO 4Ch, 16 bit
    AXT_ECAT_MOTION						= $E1;			// EtherCAT Motion Module
	AXT_ECAT_DIO						= $E2;			// EtherCAT DIO Module
	AXT_ECAT_AIO						= $E3;			// EtherCAT AIO Module
	AXT_ECAT_COM						= $E4;			// EtherCAT Serial COM(RS232C) Module
	AXT_ECAT_COUPLER					= $E5;			// EtherCAT Coupler Module
	AXT_ECAT_CNT						= $E6;			// EtherCAT Count Module
	AXT_ECAT_UNKNOWN					= $E7;			// EtherCAT Unknown Module
	AXT_SMC_4V04_A						= $EA;			// Nx04_A
    { 함수 반환값 정의                  }
    AXT_RT_SUCCESS                      = 0;            // API 함수 수행 성공
    AXT_RT_OPEN_ERROR                   = 1001;         // 라이브러리 오픈 되지않음
    AXT_RT_OPEN_ALREADY                 = 1002;         // 라이브러리 오픈 되어있고 사용 중임
    AXT_RT_NOT_OPEN                     = 1053;         // 라이브러리 초기화 실패
    AXT_RT_NOT_SUPPORT_VERSION          = 1054;         // 지원하지않는 하드웨어
    AXT_RT_LOCK_FILE_MISMATCH           = 1055;         // Lock파일과 현재 Scan정보가 일치하지 않음 

    AXT_RT_INVALID_BOARD_NO             = 1101;         // 유효하지 않는 보드 번호
    AXT_RT_INVALID_MODULE_POS           = 1102;         // 유효하지 않는 모듈 위치
    AXT_RT_INVALID_LEVEL                = 1103;         // 유효하지 않는 레벨
    AXT_RT_INVALID_VARIABLE             = 1104;         // 유효하지 않는 변수
    AXT_RT_ERROR_VERSION_READ           = 1151;         // 라이브러리 버전을 읽을수 없음
    AXT_RT_NETWORK_ERROR                = 1152;         // 하드웨어 네트워크 에러
    AXT_RT_NETWORK_LOCK_MISMATCH        = 1153;         // 보드 Lock정보와 현재 Scan정보가 일치하지 않음
    
    AXT_RT_1ST_BELOW_MIN_VALUE          = 1160;         // 첫번째 인자값이 최소값보다 더 작음                                
    AXT_RT_1ST_ABOVE_MAX_VALUE          = 1161;         // 첫번째 인자값이 최대값보다 더 큼                                  
    AXT_RT_2ND_BELOW_MIN_VALUE          = 1170;         // 두번째 인자값이 최소값보다 더 작음                                
    AXT_RT_2ND_ABOVE_MAX_VALUE          = 1171;         // 두번째 인자값이 최대값보다 더 큼                                  
    AXT_RT_3RD_BELOW_MIN_VALUE          = 1180;         // 세번째 인자값이 최소값보다 더 작음                                
    AXT_RT_3RD_ABOVE_MAX_VALUE          = 1181;         // 세번째 인자값이 최대값보다 더 큼                                  
    AXT_RT_4TH_BELOW_MIN_VALUE          = 1190;         // 네번째 인자값이 최소값보다 더 작음                                
    AXT_RT_4TH_ABOVE_MAX_VALUE          = 1191;         // 네번째 인자값이 최대값보다 더 큼                                  
    AXT_RT_5TH_BELOW_MIN_VALUE          = 1200;         // 다섯번째 인자값이 최소값보다 더 작음                              
    AXT_RT_5TH_ABOVE_MAX_VALUE          = 1201;         // 다섯번째 인자값이 최대값보다 더 큼                                
    AXT_RT_6TH_BELOW_MIN_VALUE          = 1210;         // 여섯번째 인자값이 최소값보다 더 작음                              
    AXT_RT_6TH_ABOVE_MAX_VALUE          = 1211;         // 여섯번째 인자값이 최대값보다 더 큼                                
    AXT_RT_7TH_BELOW_MIN_VALUE          = 1220;         // 일곱번째 인자값이 최소값보다 더 작음                              
    AXT_RT_7TH_ABOVE_MAX_VALUE          = 1221;         // 일곱번째 인자값이 최대값보다 더 큼                                
    AXT_RT_8TH_BELOW_MIN_VALUE          = 1230;         // 여덟번째 인자값이 최소값보다 더 작음                              
    AXT_RT_8TH_ABOVE_MAX_VALUE          = 1231;         // 여덟번째 인자값이 최대값보다 더 큼                                
    AXT_RT_9TH_BELOW_MIN_VALUE          = 1240;         // 아홉번째 인자값이 최소값보다 더 작음                              
    AXT_RT_9TH_ABOVE_MAX_VALUE          = 1241;         // 아홉번째 인자값이 최대값보다 더 큼                                
    AXT_RT_10TH_BELOW_MIN_VALUE         = 1250;         // 열번째 인자값이 최소값보다 더 작음                                
    AXT_RT_10TH_ABOVE_MAX_VALUE         = 1251;         // 열번째 인자값이 최대값보다 더 큼   
    AXT_RT_11TH_BELOW_MIN_VALUE         = 1252;         // 열한번째 인자값이 최소값보다 더 작음                                
    AXT_RT_11TH_ABOVE_MAX_VALUE         = 1253;         // 열한번째 인자값이 최대값보다 더 큼                                      
    AXT_RT_AIO_OPEN_ERROR               = 2001;         // AIO 모듈 오픈실패                                                 
    AXT_RT_AIO_NOT_MODULE               = 2051;         // AIO 모듈 없음                                                     
    AXT_RT_AIO_NOT_EVENT                = 2052;         // AIO 이벤트 읽지 못함                                              
    AXT_RT_AIO_INVALID_MODULE_NO        = 2101;         // 유효하지않은 AIO모듈                                              
    AXT_RT_AIO_INVALID_CHANNEL_NO       = 2102;         // 유효하지않은 AIO채널번호                                          
    AXT_RT_AIO_INVALID_USE              = 2106;         // AIO 함수 사용못함                                                 
    AXT_RT_AIO_INVALID_TRIGGER_MODE     = 2107;         // 유효하지않는 트리거 모드       
    AXT_RT_AIO_EXTERNAL_DATA_EMPTY      = 2108;         // 외부 데이터 값이 없을 경우
    AXT_RT_AIO_INVALID_VALUE            = 2109;         // 유효하지않는 값 설정
    AXT_RT_AIO_UPG_ALEADY_ENABLED       = 2110;         // AO UPG 기능 사용중 설정됨

    AXT_RT_DIO_OPEN_ERROR               = 3001;         // DIO 모듈 오픈실패                                                 
    AXT_RT_DIO_NOT_MODULE               = 3051;         // DIO 모듈 없음                                                     
    AXT_RT_DIO_NOT_INTERRUPT            = 3052;         // DIO 인터럽트 설정안됨                                             
    AXT_RT_DIO_INVALID_MODULE_NO        = 3101;         // 유효하지않는 DIO 모듈 번호                                        
    AXT_RT_DIO_INVALID_OFFSET_NO        = 3102;         // 유효하지않는 DIO OFFSET 번호                                      
    AXT_RT_DIO_INVALID_LEVEL            = 3103;         // 유효하지않는 DIO 레벨                                             
    AXT_RT_DIO_INVALID_MODE             = 3104;         // 유효하지않는 DIO 모드                                             
    AXT_RT_DIO_INVALID_VALUE            = 3105;         // 유효하지않는 값 설정                                              
    AXT_RT_DIO_INVALID_USE              = 3106;         // DIO 함수 사용못함
    
    AXT_RT_CNT_OPEN_ERROR               = 3201;         // CNT 모듈 오픈실패
    AXT_RT_CNT_NOT_MODULE               = 3251;         // CNT 모듈 없음
    AXT_RT_CNT_NOT_INTERRUPT            = 3252;         // CNT 인터럽트 설정안됨
    AXT_RT_CNT_INVALID_MODULE_NO        = 3301;         // 유효하지않는 CNT 모듈 번호
    AXT_RT_CNT_INVALID_CHANNEL_NO       = 3302;         // 유효하지않는 채널 번호
    AXT_RT_CNT_INVALID_OFFSET_NO        = 3303;         // 유효하지않는 CNT OFFSET 번호
    AXT_RT_CNT_INVALID_LEVEL            = 3304;         // 유효하지않는 CNT 레벨
    AXT_RT_CNT_INVALID_MODE             = 3305;         // 유효하지않는 CNT 모드
    AXT_RT_CNT_INVALID_VALUE            = 3306;         // 유효하지않는 값 설정
    AXT_RT_CNT_INVALID_USE              = 3307;         // CNT 함수 사용못함      
                                            
    AXT_RT_MOTION_OPEN_ERROR            = 4001;         // 모션 라이브러리 Open 실패                                         
    AXT_RT_MOTION_NOT_MODULE            = 4051;         // 시스템에 장착된 모션 모듈이 없음                                  
    AXT_RT_MOTION_NOT_INTERRUPT         = 4052;         // 인터럽트 결과 읽기 실패                                           
    AXT_RT_MOTION_NOT_INITIAL_AXIS_NO   = 4053;         // 해당 축 모션 초기화 실패                                          
    AXT_RT_MOTION_NOT_IN_CONT_INTERPOL  = 4054;         // 연속 보간 구동 중이 아닌 상태에서 연속보간 중지 명령을 수행 하였음
    AXT_RT_MOTION_NOT_PARA_READ         = 4055;         // 원점 구동 설정 파라미터 로드 실패                                 
    AXT_RT_MOTION_INVALID_AXIS_NO       = 4101;         // 해당 축이 존재하지 않음                                           
    AXT_RT_MOTION_INVALID_METHOD        = 4102;         // 해당 축 구동에 필요한 설정이 잘못됨                               
    AXT_RT_MOTION_INVALID_USE           = 4103;         // 'uUse' 인자값이 잘못 설정됨                                       
    AXT_RT_MOTION_INVALID_LEVEL         = 4104;         // 'uLevel' 인자값이 잘못 설정됨                                     
    AXT_RT_MOTION_INVALID_BIT_NO        = 4105;         // 범용 입출력 해당 비트가 잘못 설정됨                               
    AXT_RT_MOTION_INVALID_STOP_MODE     = 4106;         // 모션 정지 모드 설정값이 잘못됨                                    
    AXT_RT_MOTION_INVALID_TRIGGER_MODE  = 4107;         // 트리거 설정 모드가 잘못 설정됨                                    
    AXT_RT_MOTION_INVALID_TRIGGER_LEVEL = 4108;         // 트리거 출력 레벨 설정이 잘못됨                                        
    AXT_RT_MOTION_INVALID_SELECTION     = 4109;         // 'uSelection' 인자가 COMMAND 또는 ACTUAL 이외의 값으로 설정되어 있음   
    AXT_RT_MOTION_INVALID_TIME          = 4110;         // Trigger 출력 시간값이 잘못 설정되어 있음                              
    AXT_RT_MOTION_INVALID_FILE_LOAD     = 4111;         // 모션 설정값이 저장된 파일이 로드가 안됨                               
    AXT_RT_MOTION_INVALID_FILE_SAVE     = 4112;         // 모션 설정값을 저장하는 파일 저장에 실패함                             
    AXT_RT_MOTION_INVALID_VELOCITY      = 4113;         // 모션 구동 속도값이 0으로 설정되어 모션 에러 발생                      
    AXT_RT_MOTION_INVALID_ACCELTIME     = 4114;         // 모션 구동 가속 시간값이 0으로 설정되어 모션 에러 발생                 
    AXT_RT_MOTION_INVALID_PULSE_VALUE   = 4115;         // 모션 단위 설정 시 입력 펄스값이 0보다 작은값으로 설정됨               
    AXT_RT_MOTION_INVALID_NODE_NUMBER   = 4116;         // 위치나 속도 오버라이드 함수가 모션 정지 중에 실햄됨                   
    AXT_RT_MOTION_INVALID_TARGET        = 4117;         // 다축 모션 정지 원인에 관한 플래그를 반환한다.                         

    AXT_RT_MOTION_ERROR_IN_NONMOTION    = 4151;         // 모션 구동중이어야 되는데 모션 구동중이 아닐 때                        
    AXT_RT_MOTION_ERROR_IN_MOTION       = 4152;         // 모션 구동 중에 다른 모션 구동 함수를 실행함                           
    AXT_RT_MOTION_ERROR                 = 4153;         // 다축 구동 정지 함수 실행 중 에러 발생함                               
    AXT_RT_MOTION_ERROR_GANTRY_ENABLE   = 4154;         // 겐트리 enable이 되어있어 모션중일 때 또 겐트리 enable을 눌렀을 때     
    AXT_RT_MOTION_ERROR_GANTRY_AXIS     = 4155;         // 겐트리 축이 마스터채널(축) 번호(0 ~ (최대축수 - 1))가 잘못 들어갔을 때
    AXT_RT_MOTION_ERROR_MASTER_SERVOON  = 4156;         // 마스터 축 서보온이 안되어있을 때                                      
    AXT_RT_MOTION_ERROR_SLAVE_SERVOON   = 4157;         // 슬레이브 축 서보온이 안되어있을 때                                    
    AXT_RT_MOTION_INVALID_POSITION      = 4158;         // 유효한 위치에 없을 때                                                 
    AXT_RT_ERROR_NOT_SAME_MODULE        = 4159;         // 똑 같은 모듈내에 있지 않을경우                                        
    AXT_RT_ERROR_NOT_SAME_BOARD         = 4160;         // 똑 같은 보드내에 있지 아닐경우                                        
    AXT_RT_ERROR_NOT_SAME_PRODUCT       = 4161;         // 제품이 서로 다를경우                                                  
    AXT_RT_NOT_CAPTURED                 = 4162;         // 위치가 저장되지 않을 때                                               
    AXT_RT_ERROR_NOT_SAME_IC            = 4163;         // 같은 칩내에 존재하지않을 때                                           
    AXT_RT_ERROR_NOT_GEARMODE           = 4164;         // 기어모드로 변환이 안될 때                                             
    AXT_ERROR_CONTI_INVALID_AXIS_NO     = 4165;         // 연속보간 축맵핑 시 유효한 축이 아닐 때                                
    AXT_ERROR_CONTI_INVALID_MAP_NO      = 4166;         // 연속보간 맵핑 시 유효한 맵핑 번호가 아닐 때                           
    AXT_ERROR_CONTI_EMPTY_MAP_NO        = 4167;         // 연속보간 맵핑 번호가 비워 있을 때                                     
    AXT_RT_MOTION_ERROR_CACULATION      = 4168;         // 계산상의 오차가 발생했을 때        
    AXT_RT_ERROR_MOVE_SENSOR_CHECK      = 4169;         // 연속보간 구동전 에러센서가(Alarm, EMG, Limit등) 감지된경우

    AXT_ERROR_HELICAL_INVALID_AXIS_NO   = 4170;         // 헬리컬 축 맵핑 시 유효한 축이 아닐 때                                 
    AXT_ERROR_HELICAL_INVALID_MAP_NO    = 4171;         // 헬리컬 맵핑 시 유효한 맵핑 번호가 아닐  때                            
    AXT_ERROR_HELICAL_EMPTY_MAP_NO      = 4172;         // 헬리컬 멥핑 번호가 비워 있을 때    

    AXT_ERROR_SPLINE_INVALID_AXIS_NO    = 4180;         // 스플라인 축 맵핑 시 유효한 축이 아닐 때         
    AXT_ERROR_SPLINE_INVALID_MAP_NO     = 4181;         // 스플라인 맵핑 시 유효한 맵핑 번호가 아닐 때     
    AXT_ERROR_SPLINE_EMPTY_MAP_NO       = 4182;         // 스플라인 맵핑 번호가 비워있을 때                
    AXT_ERROR_SPLINE_NUM_ERROR          = 4183;         // 스플라인 점숫자가 부적당할 때                   
    AXT_RT_MOTION_INTERPOL_VALUE        = 4184;         // 보간할 때 입력 값이 잘못넣어졌을 때             
    AXT_RT_ERROR_NOT_CONTIBEGIN         = 4185;         // 연속보간 할 때 CONTIBEGIN함수를 호출하지 않을 때
    AXT_RT_ERROR_NOT_CONTIEND           = 4186;         // 연속보간 할 때 CONTIEND함수를 호출하지 않을 때  
    
    AXT_RT_MOTION_HOME_SEARCHING        = 4201;         // 홈을 찾고 있는 중일 때 다른 모션 함수들을 사용할 때                            
    AXT_RT_MOTION_HOME_ERROR_SEARCHING  = 4202;         // 홈을 찾고 있는 중일 때 외부에서 사용자나 혹은 어떤것에 의한  강제로 정지당할 때
    AXT_RT_MOTION_HOME_ERROR_START      = 4203;         // 초기화 문제로 홈시작 불가할 때                                                 
    AXT_RT_MOTION_HOME_ERROR_GANTRY     = 4204;         // 홈을 찾고 있는 중일 때 겐트리 enable 불가할 때                                 

    AXT_RT_MOTION_READ_ALARM_WAITING    = 4210;         // 서보팩으로부터 알람코드 결과를 기다리는 중     
    AXT_RT_MOTION_READ_ALARM_NO_REQUEST = 4211;         // 서보팩에 알람코드 반환 명령이 내려지지않았을 때
    AXT_RT_MOTION_READ_ALARM_TIMEOUT    = 4212;         // 서보팩 알람읽기 시간초과 했을때(1sec이상)      
    AXT_RT_MOTION_READ_ALARM_FAILED     = 4213;         // 서보팩 알람읽기에 실패 했을 때                 
    AXT_RT_MOTION_READ_ALARM_UNKNOWN    = 4220;         // 알람코드가 알수없는 코드일 때                  
    AXT_RT_MOTION_READ_ALARM_FILES      = 4221;         // 알람정보 파일이 정해진위치에 존재하지 않을 때  
    AXT_RT_MOTION_READ_ALARM_NOT_DETECTED      = 4222;         // 알람코드 Read 시; 알람이 발생하지 않았을 때
    AXT_RT_MOTION_POSITION_OUTOFBOUND   = 4251;         // 설정한 위치값이 설정 최대값보다 크거나 최소값보다 작은값임                     
    AXT_RT_MOTION_PROFILE_INVALID       = 4252;         // 구동 속도 프로파일 설정이 잘못됨                                               
    AXT_RT_MOTION_VELOCITY_OUTOFBOUND   = 4253;         // 구동 속도값이 최대값보다 크게 설정됨                                           
    AXT_RT_MOTION_MOVE_UNIT_IS_ZERO     = 4254;         // 구동 단위값이 0으로 설정됨                                                     
    AXT_RT_MOTION_SETTING_ERROR         = 4255;         // 속도, 가속도, 저크, 프로파일 설정이 잘못됨                                     
    AXT_RT_MOTION_IN_CONT_INTERPOL      = 4256;         // 연속 보간 구동 중 구동 시작 또는 재시작 함수를 실행하였음                      
    AXT_RT_MOTION_DISABLE_TRIGGER       = 4257;         // 트리거 출력이 Disable 상태임                                                   
    AXT_RT_MOTION_INVALID_CONT_INDEX    = 4258;         // 연속 보간 Index값 설정이 잘못됨                                                
    AXT_RT_MOTION_CONT_QUEUE_FULL       = 4259;         // 모션 칩의 연속 보간 큐가 Full 상태임                                           
    AXT_RT_PROTECTED_DURING_SERVOON     = 4260;         // 서보 온 되어 있는 상태에서 사용 못 함                                          
    AXT_RT_HW_ACCESS_ERROR              = 4261;         // 메모리 Read / Write 실패

    AXT_RT_HW_DPRAM_CMD_WRITE_ERROR_LV1 = 4262;         // DPRAM Comamnd Write 실패 Level1
    AXT_RT_HW_DPRAM_CMD_WRITE_ERROR_LV2 = 4263;         // DPRAM Comamnd Write 실패 Level2
    AXT_RT_HW_DPRAM_CMD_WRITE_ERROR_LV3 = 4264;         // DPRAM Comamnd Write 실패 Level3
    AXT_RT_HW_DPRAM_CMD_READ_ERROR_LV1  = 4265;         // DPRAM Comamnd Read 실패 Level1
    AXT_RT_HW_DPRAM_CMD_READ_ERROR_LV2  = 4266;         // DPRAM Comamnd Read 실패 Level2
    AXT_RT_HW_DPRAM_CMD_READ_ERROR_LV3  = 4267;         // DPRAM Comamnd Read 실패 Level3

    AXT_RT_COMPENSATION_SET_PARAM_FIRST     = 4300;
    AXT_RT_COMPENSATION_NOT_INIT            = 4301;     // 보정테이블 기능 초기화 되지않음
    AXT_RT_COMPENSATION_POS_OUTOFBOUND      = 4302;     // 위치 값이 범위내에 존재하지 않음
    AXT_RT_COMPENSATION_BACKLASH_NOT_INIT   = 4303;     // 백래쉬 보정기능 초기화 되지않음
    AXT_RT_COMPENSATION_INVALID_ENTRY       = 4304;     //
        
    AXT_RT_SEQ_NOT_IN_SERVICE           = 4400;          // 순차 구동 함수 실행 중 자원 할당 실패
    AXT_ERROR_SEQ_INVALID_MAP_NO        = 4401;          // 순차 구동 함수 실행 중 맵핑 번호 이상.
    AXT_ERROR_INVALID_AXIS_NO           = 4402;          // 함수 설정 인자중 축번호 이상.
    AXT_RT_ERROR_NOT_SEQ_NODE_BEGIN     = 4403;          // 순차 구동 노드 입력 시작 함수를 호출하지 않음.
    AXT_RT_ERROR_NOT_SEQ_NODE_END       = 4404;          // 순차 구동 노드 입력 종료 함수를 호출하지 않음.
    AXT_RT_ERROR_NO_NODE                = 4405;          // 순차 구동 노드 입력이 없음.
    AXT_RT_ERROR_SEQ_STOP_TIMEOUT       = 4406;
    
    AXT_RT_M3_COMMUNICATION_FAILED             = 4500;   // ML3 통신 기준, 통신 실패
    AXT_RT_MOTION_ONE_OF_AXES_IS_NOT_M3        = 4501;   // ML3 통신 기준, 구성된 ML3 노드 중에서 모션 노드 없음 
    AXT_RT_MOTION_BIGGER_VEL_THEN_MAX_VEL      = 4502;   // ML3 통신 기준, 지정된 축의 설정된 최대 속도보다 큼
    AXT_RT_MOTION_SMALLER_VEL_THEN_MAX_VEL     = 4503;   // ML3 통신 기준, 지정된 축의 설정된 최대 속도보다 작음
    AXT_RT_MOTION_ACCEL_MUST_BIGGER_THEN_ZERO  = 4504;   // ML3 통신 기준, 지정된 축의 설정된 가속도가 0보다 큼
    AXT_RT_MOTION_SMALL_ACCEL_WITH_UNIT_PULSE  = 4505;   // ML3 통신 기준, UnitPulse가 적용된 가속도가 0보다 큼
    AXT_RT_MOTION_INVALID_INPUT_ACCEL          = 4506;   // ML3 통신 기준, 지정된 축의 가속도 입력이 잘못됨
    AXT_RT_MOTION_SMALL_DECEL_WITH_UNIT_PULSE  = 4507;   // ML3 통신 기준, UnitPulse가 적용된 감속도가 0보다 큼
    AXT_RT_MOTION_INVALID_INPUT_DECEL          = 4508;   // ML3 통신 기준, 지정된 축의 감속도 입력이 잘못됨
    AXT_RT_MOTION_SAME_START_AND_CENTER_POS    = 4509;   // ML3 통신 기준, 원호보간의 시작점과 중심점이 같음
    AXT_RT_MOTION_INVALID_JERK                 = 4510;   // ML3 통신 기준, 지정된 축의 저크 입력이 잘못됨
    AXT_RT_MOTION_INVALID_INPUT_VALUE          = 4511;   // ML3 통신 기준, 지정된 축의 입력값이 잘못됨
    AXT_RT_MOTION_NOT_SUPPORT_PROFILE          = 4512;   // ML3 통신 기준, 제공되지 않는 속도 프로파일임
    AXT_RT_MOTION_INPOS_UNUSED                 = 4513;   // ML3 통신 기준, 인포지션 사용하지 않음
    AXT_RT_MOTION_AXIS_IN_SLAVE_STATE          = 4514;   // ML3 통신 기준, 지정된 축이 슬레이브 상태가 아님
    AXT_RT_MOTION_AXES_ARE_NOT_SAME_BOARD      = 4515;   // ML3 통신 기준, 지정된 축들이 같은 보드 내에 있지 않음
    AXT_RT_MOTION_ERROR_IN_ALARM               = 4516;   // ML3 통신 기준, 지정된 축이 알람 상태임
    AXT_RT_MOTION_ERROR_IN_EMGN                = 4517;   // ML3 통신 기준, 지정된 축이 비상정지 상태임
    AXT_RT_MOTION_CAN_NOT_CHANGE_COORD_NO      = 4518;   // ML3 통신 기준, 코디네이터 넘버 변환 불가임
    AXT_RT_MOTION_INVALID_INTERNAL_RADIOUS     = 4519;   // ML3 통신 기준, 원호보간의 X, Y축 반지름 불일치
    AXT_RT_MOTION_CONTI_QUEUE_FULL             = 4521;   // ML3 통신 기준, 보간의 큐가 가득 참
    AXT_RT_MOTION_SAME_START_AND_END_POSITION  = 4522;   // ML3 통신 기준, 원호보간의 시작점과 종료점이 같음
    AXT_RT_MOTION_INVALID_ANGLE                = 4523;   // ML3 통신 기준, 원호보간의 각도가 360도 초과됨
    AXT_RT_MOTION_CONTI_QUEUE_EMPTY            = 4524;   // ML3 통신 기준, 보간의 큐가 비어있음
    AXT_RT_MOTION_ERROR_GEAR_ENABLE            = 4525;   // ML3 통신 기준, 지정된 축이 이미 링크 설정 상태임
    AXT_RT_MOTION_ERROR_GEAR_AXIS              = 4526;   // ML3 통신 기준, 지정된 축이 링크축이 아님
    AXT_RT_MOTION_ERROR_NO_GANTRY_ENABLE       = 4527;   // ML3 통신 기준, 지정된 축이 겐트리 설정 상태가 아님
    AXT_RT_MOTION_ERROR_NO_GEAR_ENABLE         = 4528;   // ML3 통신 기준, 지정된 축이 링크 설정 상태가 아님
    AXT_RT_MOTION_ERROR_GANTRY_ENABLE_FULL     = 4529;   // ML3 통신 기준, 겐트리 설정 가득참
    AXT_RT_MOTION_ERROR_GEAR_ENABLE_FULL       = 4530;   // ML3 통신 기준, 링크 설정 가득참
    AXT_RT_MOTION_ERROR_NO_GANTRY_SLAVE        = 4531;   // ML3 통신 기준, 지정된 축이 겐트리 슬레이브 설정상태가 아님
    AXT_RT_MOTION_ERROR_NO_GEAR_SLAVE          = 4532;   // ML3 통신 기준, 지정된 축이 링크 슬레이브 설정상태가 아님
    AXT_RT_MOTION_ERROR_MASTER_SLAVE_SAME      = 4533;   // ML3 통신 기준, 마스터축과 슬레이브 축이 동일함
    AXT_RT_MOTION_NOT_SUPPORT_HOMESIGNAL       = 4534;   // ML3 통신 기준, 지정된 축의 홈신호는 지원되지 않음
    AXT_RT_MOTION_ERROR_NOT_SYNC_CONNECT       = 4535;   // ML3 통신 기준, 지정된 축이 싱크 연결 상태가 아님
    AXT_RT_MOTION_OVERFLOW_POSITION            = 4536;   // ML3 통신 기준, 지정된 축에 대한 구동 위치값이 오버플로우임
    AXT_RT_MOTION_ERROR_INVALID_CONTIMAPAXIS   = 4537;   // ML3 통신 기준, 보간작업을 위한 지정된 좌표계 축맵핑이 없음
    AXT_RT_MOTION_ERROR_INVALID_CONTIMAPSIZE   = 4538;   // ML3 통신 기준, 보간작업을 ㅜ이한 지정된 좌표계 축맵핑 축사이즈가 잘못됨
    AXT_RT_MOTION_ERROR_IN_SERVO_OFF           = 4539;   // ML3 통신 기준, 지정된 축이 서보 OFF되어 있음
    AXT_RT_MOTION_ERROR_POSITIVE_LIMIT         = 4540;   // ML3 통신 기준, 지정된 축이 (+)리밋 ON되어 있음
    AXT_RT_MOTION_ERROR_NEGATIVE_LIMIT         = 4541;   // ML3 통신 기준, 지정된 축이 (-)리밋 ON되어 있음
    AXT_RT_MOTION_ERROR_OVERFLOW_SWPROFILE_NUM = 4542;   // ML3 통신 기준, 지정된 축들에 대한 지원 프로파일 개수가 오버플로우됨
    AXT_RT_PROTECTED_DURING_INMOTION           = 4543;   // in_motion 되어 있는 상태에서 사용 못 함


    AXT_RT_DATA_FLASH_NOT_EXIST                = 5000;
    AXT_RT_DATA_FLASH_BUSY                     = 5001;

    { 로그레벨 정의                     }
    LEVEL_NONE                          = 0;
    LEVEL_ERROR                         = 1;
    LEVEL_RUNSTOP                       = 2;
    LEVEL_FUNCTION                      = 3;
    { 모션제품 축 상태 정의               }
    STATUS_NOTEXIST                     = 0;
    STATUS_EXIST                        = 1;
    { 사용 유무 정의                    }
    DISABLE                             = 0;
    ENABLE                              = 1;
    { AI제품 트리거 모드정의            }
    DISABLE_MODE                        = 0;
    NORMAL_MODE                         = 1;
    TIMER_MODE                          = 2;
    EXTERNAL_MODE                       = 3;
    { AI제품 데이타큐 운용방법 정의     }
    NEW_DATA_KEEP                       = 0;
    CURR_DATA_KEEP                      = 1;
    { AI제품 데이타큐 상태 정의         }
    DATA_EMPTY                          = $01;
    DATA_MANY                           = $02;
    DATA_SMALL                          = $04;
    DATA_FULL                           = $08;
    { AI(16H)제품 데이타큐 상태 정의    }
    ADC_DONE                            = $00;
    SCAN_END                            = $01;
    FIFO_HALF_FULL                      = $02;
    NO_SIGNAL                           = $03;
    { AI제품 인터럽트 상태 정의         } 
    AIO_EVENT_DATA_RESET                = $00;
    AIO_EVENT_DATA_UPPER                = $1;
    AIO_EVENT_DATA_LOWER                = $2;
    AIO_EVENT_DATA_FULL                 = $3;
    AIO_EVENT_DATA_EMPTY                = $4;
    { AI Module H/W FIFO 상태 정의      }   
    FIFO_DATA_EXIST                     = 0;
    FIFO_DATA_EMPTY                     = 1;
    FIFO_DATA_HALF                      = 2;
    FIFO_DATA_FULL                      = 6;
    { AI Module Conversion 상태정의     }   
    EXTERNAL_DATA_DONE                  = 0;
    EXTERNAL_DATA_FINE                  = 1;
    EXTERNAL_DATA_HALF                  = 2;
    EXTERNAL_DATA_FULL                  = 3;
    EXTERNAL_COMPLETE                   = 4;
    { DI제품 입력 에지 정의             }
    DOWN_EDGE                           = 0;
    UP_EDGE                             = 1;
    { DIO제품 접정 상태 정의            }
    OFF_STATE                           = 0;
    ON_STATE                            = 1;
    { 모션제품 정지 방법 정의           }
    EMERGENCY_STOP                      = 0;
    SLOWDOWN_STOP                       = 1;
    { 모션제품 신호 에지 정의           }
    SIGNAL_DOWN_EDGE                    = 0;
    SIGNAL_UP_EDGE                      = 1;
    SIGNAL_LOW_LEVEL                    = 2;
    SIGNAL_HIGH_LEVEL                   = 3;
    { 모션제품 카운트 종류 정의         }
    COMMAND                             = 0;
    ACTUAL                              = 1;
    { 모션제품 트리거 방법 정의         }
    PERIOD_MODE                         = 0;
    ABS_POS_MODE                        = 1;
    { 모션제품 입력신호 레벨 정의       }
    LOW                                 = 0;
    HIGH                                = 1;
    UNUSED                              = 2;
    USED                                = 3;
    { 모션제품 구동 좌표계 정의         }
    POS_ABS_MODE                        = 0;
    POS_REL_MODE                        = 1;	
    POS_ABS_LONG_MODE                   = 2;

    { 엔코더 종류 정의       }
	ENCODER_TYPE_INCREMENTAL            = 0;
    ENCODER_TYPE_ABSOLUTE               = 1;	
    ENCODER_TYPE_NONE                   = 2;

    { 모션제품 구동 프로파일 정의       }
    SYM_TRAPEZOIDE_MODE                 = 0;
    ASYM_TRAPEZOIDE_MODE                = 1;
    QUASI_S_CURVE_MODE                  = 2;
    SYM_S_CURVE_MODE                    = 3;
    ASYM_S_CURVE_MODE                   = 4;
	SYM_TRAP_M3_SW_MODE                 = 5;  //ML-3 Only, Support Velocity profile
	ASYM_TRAP_M3_SW_MODE                = 6;  //ML-3 Only, Support Velocity profile
	SYM_S_M3_SW_MODE                    = 7;  //ML-3 Only, Support Velocity profile
	ASYM_S_M3_SW_MODE                   = 8;  //ML-3 Only, Support Velocity profile
    { 모션제품 신호 상태 정의           }
    INACTIVE                            = 0;
    ACTIVE                              = 1;
    { 모션제품 원점검색 결과 정의       }
    HOME_RESERVED                       = $00;          // ML3
    HOME_SUCCESS                        = $01;          // 원점 검색 완료 
    HOME_SEARCHING                      = $02;	        // 원점 검색 중
    HOME_ERR_GNT_RANGE                  = $10;          // 갠트리 원점 검색 기준, 두 축 사이의 설정이상 오차 발생
    HOME_ERR_USER_BREAK                 = $11;          // 원점 검색 사용자 중지시
    HOME_ERR_VELOCITY                   = $12;          // 원점 검색 속도 이상 에러 발생
    HOME_ERR_AMP_FAULT                  = $13;          // 서보팩 알람 발생 에러                  
    HOME_ERR_NEG_LIMIT                  = $14;          // (-)방향 구동중 (+)리미트 센서 감지 에러
    HOME_ERR_POS_LIMIT                  = $15;          // (+)방향 구동중 (-)리미트 센서 감지 에러
    HOME_ERR_NOT_DETECT                 = $16;          // 지정한 신호 검출하지 못 할 경우 에러
    HOME_ERR_SETTING                    = $17;          // 사용자 설정 파라미터가 구동시 제약 조건 발생시
	HOME_ERR_SERVO_OFF                  = $18;          // 서보 Off일경우
    HOME_ERR_TIMEOUT                    = $20;          // 지정된 시간 초과 발생으로 오류 발생 
    HOME_ERR_FUNCALL                    = $30;          // 함수 호출 실패
    HOME_ERR_COUPLING                   = $40;          // Gantry Master to Slave Over Distance protection
    HOME_ERR_UNKNOWN                    = $FF;          // 미지정 에러
    { 모션제품 입력접점 정의            }
    UIO_INP0                            = 0;
    UIO_INP1                            = 1;
    UIO_INP2                            = 2;
    UIO_INP3                            = 3;
    UIO_INP4                            = 4;
    UIO_INP5                            = 5;
    { 모션제품 출력접점 정의            }
    UIO_OUT0                            = 0;
    UIO_OUT1                            = 1;
    UIO_OUT2                            = 2;
    UIO_OUT3                            = 3;
    UIO_OUT4                            = 4;
    UIO_OUT5                            = 5;
    { 모션제품 가감속 방법 정의         }
    AutoDetect                          = 0;
    RestPulse                           = 1;
    { 모션제품 펄스 출력방법 정의       }
    OneHighLowHigh                      = $0;           // 1펄스 방식; PULSE(Active High), 정방향(DIR=Low)  / 역방향(DIR=High)    
    OneHighHighLow                      = $1;           // 1펄스 방식, PULSE(Active High), 정방향(DIR=High) / 역방향(DIR=Low)     
    OneLowLowHigh                       = $2;           // 1펄스 방식, PULSE(Active Low),  정방향(DIR=Low)  / 역방향(DIR=High)    
    OneLowHighLow                       = $3;           // 1펄스 방식, PULSE(Active Low),  정방향(DIR=High) / 역방향(DIR=Low)     
    TwoCcwCwHigh                        = $4;           // 2펄스 방식, PULSE(CCW:역방향),  DIR(CW:정방향),  Active High           
    TwoCcwCwLow                         = $5;           // 2펄스 방식, PULSE(CCW:역방향),  DIR(CW:정방향),  Active Low            
    TwoCwCcwHigh                        = $6;           // 2펄스 방식, PULSE(CW:정방향),   DIR(CCW:역방향), Active High           
    TwoCwCcwLow                         = $7;           // 2펄스 방식, PULSE(CW:정방향),   DIR(CCW:역방향), Active Low            
    TwoPhase                            = $8;           // 2상(90' 위상차),  PULSE lead DIR(CW: 정방향), PULSE lag DIR(CCW:역방향)
    TwoPhaseReverse                     = $9;           // 2상(90' 위상차),  PULSE lead DIR(CCW: 정방향), PULSE lag DIR(CW:역방향)
    { 모션제품 엔코더 입력방법 정의     }
    ObverseUpDownMode                   = $0;           // 정방향 Up/Down 
    ObverseSqr1Mode                     = $1;           // 정방향 1체배   
    ObverseSqr2Mode                     = $2;           // 정방향 2체배   
    ObverseSqr4Mode                     = $3;           // 정방향 4체배   
    ReverseUpDownMode                   = $4;           // 역방향 Up/Down 
    ReverseSqr1Mode                     = $5;           // 역방향 1체배   
    ReverseSqr2Mode                     = $6;           // 역방향 2체배   
    ReverseSqr4Mode                     = $7;           // 역방향 4체배   
    { 모션제품 가감속 단위 정의         }
    UNIT_SEC2                           = $0;           // unit/sec2
    SEC                                 = $1;           // sec
    { 모션제품 구동방향 정의            }
    DIR_CCW                             = $0;           // 반시계방향
    DIR_CW                              = $1;           // 시계방향  
    { 모션제품 원호보간 방법 정의       }
    SHORT_DISTANCE                      = $0;           // 짧은 거리의 원호 이동
    LONG_DISTANCE                       = $1;           // 긴 거리의 원호 이동  
    { 위치카운트 방식 정의              }
    POSITION_LIMIT                      = $0;           // 전체 영역사용
    POSITION_BOUND                      = $1;           // Pos 지정 사용
    { 모션제품 보간 사용축 정의         }
    INTERPOLATION_AXIS2                 = $0;           // 2축을 보간으로 사용할 때
    INTERPOLATION_AXIS3                 = $1;           // 3축을 보간으로 사용할 때
    INTERPOLATION_AXIS4                 = $2;           // 4축을 보간으로 사용할 때
    { 모션제품 연속보간 방법 정의       }
    CONTI_NODE_VELOCITY                 = $0;           // 속도 지정 보간 모드  
    CONTI_NODE_MANUAL                   = $1;           // 노드 가감속 보간 모드
    CONTI_NODE_AUTO                     = $2;           // 자동 가감속 보간 모드
    { 모션제품 검출신호 정의            }
    PosEndLimit                         = $0;           // +Elm(End limit) +방향 리미트 센서 신호
    NegEndLimit                         = $1;           // -Elm(End limit) -방향 리미트 센서 신호
    PosSloLimit                         = $2;           // +Slm(Slow Down limit) 신호 - 사용하지 않음
    NegSloLimit                         = $3;           // -Slm(Slow Down limit) 신호 - 사용하지 않음
    HomeSensor                          = $4;           // IN0(ORG)  원점 센서 신호
    EncodZPhase                         = $5;           // IN1(Z상)  Encoder Z상 신호
    UniInput02                          = $6;           // IN2(범용) 범용 입력 2번 신호
    UniInput03                          = $7;           // IN3(범용) 범용 입력 3번 신호
    UniInput04                          = $8;           // IN4(범용) 범용 입력 4번 신호
    UniInput05                          = $9;           // IN5(범용) 범용 입력 5번 신호
    { 모션제품 필터적용 입력접점 정의   }
    END_LIMIT                           = $10;          // +Elm(End limit) +방향 리미트 센서 신호
    INP_ALARM                           = $11;          // -Elm(End limit) -방향 리미트 센서 신호
    UIN_00_01                           = $12;          // +Slm(Slow Down limit) 신호 - 사용하지 않음
    UIN_02_04                           = $13;          // -Slm(Slow Down limit) 신호 - 사용하지 않음
    { 모션제품 MPG 신호 입력방법 정의   }
    MPG_DIFF_ONE_PHASE                  = $0;           // MPG 입력 방식 One Phase       
    MPG_DIFF_TWO_PHASE_1X               = $1;           // MPG 입력 방식 TwoPhase1       
    MPG_DIFF_TWO_PHASE_2X               = $2;           // MPG 입력 방식 TwoPhase2       
    MPG_DIFF_TWO_PHASE_4X               = $3;           // MPG 입력 방식 TwoPhase4       
    MPG_LEVEL_ONE_PHASE                 = $4;           // MPG 입력 방식 Level One Phase 
    MPG_LEVEL_TWO_PHASE_1X              = $5;           // MPG 입력 방식 Level Two Phase1
    MPG_LEVEL_TWO_PHASE_2X              = $6;           // MPG 입력 방식 Level Two Phase2
    MPG_LEVEL_TWO_PHASE_4X              = $7;           // MPG 입력 방식 Level Two Phase4
    { 모션제품 센서검출 구동방법 정의   }
    SENSOR_METHOD1                      = $0;           // 일반 구동                                            
    SENSOR_METHOD2                      = $1;           // 센서 신호 검출 전은 저속 구동. 신호 검출 후 일반 구동
    SENSOR_METHOD3                      = $2;           // 저속 구동                                            
    { 모션제품 잔여펄스 제거 방법 정의  }
    CRC_SELECT1                         = $0;           // 위치클리어 사용않함, 잔여펄스 클리어 사용 안함
    CRC_SELECT2                         = $1;           // 위치클리어 사용함, 잔여펄스 클리어 사용 안함  
    CRC_SELECT3                         = $2;           // 위치클리어 사용안함, 잔여펄스 클리어 사용함   
    CRC_SELECT4                         = $3;           // 위치클리어 사용함, 잔여펄스 클리어 사용함     
    { 모션제품(IP) 신호검출 종류 정의   }
    PElmNegativeEdge                    = $0;           // +Elm(End limit) 하강 edge     
    NElmNegativeEdge                    = $1;           // -Elm(End limit) 하강 edge     
    PSlmNegativeEdge                    = $2;           // +Slm(Slowdown limit) 하강 edge
    NSlmNegativeEdge                    = $3;           // -Slm(Slowdown limit) 하강 edge
    In0DownEdge                         = $4;           // IN0(ORG) 하강 edge            
    In1DownEdge                         = $5;           // IN1(Z상) 하강 edge            
    In2DownEdge                         = $6;           // IN2(범용) 하강 edge           
    In3DownEdge                         = $7;           // IN3(범용) 하강 edge           
    PElmPositiveEdge                    = $8;           // +Elm(End limit) 상승 edge     
    NElmPositiveEdge                    = $9;           // -Elm(End limit) 상승 edge     
    PSlmPositiveEdge                    = $a;           // +Slm(Slowdown limit) 상승 edge
    NSlmPositiveEdge                    = $b;           // -Slm(Slowdown limit) 상승 edge
    In0UpEdge                           = $c;           // IN0(ORG) 상승 edge            
    In1UpEdge                           = $d;           // IN1(Z상) 상승 edge            
    In2UpEdge                           = $e;           // IN2(범용) 상승 edge           
    In3UpEdge                           = $f;           // IN3(범용) 상승 edge           
    { 모션제품(IP) 구동종료 상태 정의   }               // When 0x0000 after normal drive end.
    IPEND_STATUS_SLM                    = $0001;        // Bit 0, limit 감속정지 신호 입력에 의한 종료                
    IPEND_STATUS_ELM                    = $0002;        // Bit 1, limit 급정지 신호 입력에 의한 종료                  
    IPEND_STATUS_SSTOP_SIGNAL           = $0004;        // Bit 2, 감속 정지 신호 입력에 의한 종료                     
    IPEND_STATUS_ESTOP_SIGANL           = $0008;        // Bit 3, 급정지 신호 입력에 의한 종료                        
    IPEND_STATUS_SSTOP_COMMAND          = $0010;        // Bit 4, 감속 정지 명령에 의한 종료                          
    IPEND_STATUS_ESTOP_COMMAND          = $0020;        // Bit 5, 급정지 정지 명령에 의한 종료                        
    IPEND_STATUS_ALARM_SIGNAL           = $0040;        // Bit 6, Alarm 신호 입력에 희한 종료                         
    IPEND_STATUS_DATA_ERROR             = $0080;        // Bit 7, 데이터 설정 에러에 의한 종료                        
    IPEND_STATUS_DEVIATION_ERROR        = $0100;        // Bit 8, 탈조 에러에 의한 종료                               
    IPEND_STATUS_ORIGIN_DETECT          = $0200;        // Bit 9, 원점 검출에 의한 종료                               
    IPEND_STATUS_SIGNAL_DETECT          = $0400;        // Bit 10, 신호 검출에 의한 종료(Signal search-1/2 drive 종료)
    IPEND_STATUS_PRESET_PULSE_DRIVE     = $0800;        // Bit 11, Preset pulse drive 종료                            
    IPEND_STATUS_SENSOR_PULSE_DRIVE     = $1000;        // Bit 12, Sensor pulse drive 종료                            
    IPEND_STATUS_LIMIT                  = $2000;        // Bit 13, Limit 완전정지에 의한 종료                         
    IPEND_STATUS_SOFTLIMIT              = $4000;        // Bit 14, Soft limit에 의한 종료                             
    IPEND_STATUS_INTERPOLATION_DRIVE    = $8000;        // Bit 15, Soft limit에 의한 종료                             
    { 모션제품(IP) 구동상태 정의        }
    IPDRIVE_STATUS_BUSY                 = $00001;       // Bit 0, BUSY(드라이브 구동 중)                         
    IPDRIVE_STATUS_DOWN                 = $00002;       // Bit 1, DOWN(감속 중)                                  
    IPDRIVE_STATUS_CONST                = $00004;       // Bit 2, CONST(등속 중)                                 
    IPDRIVE_STATUS_UP                   = $00008;       // Bit 3, UP(가속 중)                                    
    IPDRIVE_STATUS_ICL                  = $00010;       // Bit 4, ICL(내부 위치 카운터 < 내부 위치 카운터 비교값)
    IPDRIVE_STATUS_ICG                  = $00020;       // Bit 5, ICG(내부 위치 카운터 > 내부 위치 카운터 비교값)
    IPDRIVE_STATUS_ECL                  = $00040;       // Bit 6, ECL(외부 위치 카운터 < 외부 위치 카운터 비교값)
    IPDRIVE_STATUS_ECG                  = $00080;       // Bit 7, ECG(외부 위치 카운터 > 외부 위치 카운터 비교값)
    IPDRIVE_STATUS_DRIVE_DIRECTION      = $00100;       // Bit 8, 드라이브 방향 신호(0=CW/1=CCW)                 
    IPDRIVE_STATUS_COMMAND_BUSY         = $00200;       // Bit 9, 명령어 수행중                                  
    IPDRIVE_STATUS_PRESET_DRIVING       = $00400;       // Bit 10, Preset pulse drive 중                         
    IPDRIVE_STATUS_CONTINUOUS_DRIVING   = $00800;       // Bit 11, Continuouse speed drive 중                    
    IPDRIVE_STATUS_SIGNAL_SEARCH_DRIVING= $01000;       // Bit 12, Signal search-1/2 drive 중                    
    IPDRIVE_STATUS_ORG_SEARCH_DRIVING   = $02000;       // Bit 13, 원점 검출 drive 중                            
    IPDRIVE_STATUS_MPG_DRIVING          = $04000;       // Bit 14, MPG drive 중                                  
    IPDRIVE_STATUS_SENSOR_DRIVING       = $08000;       // Bit 15, Sensor positioning drive 중                   
    IPDRIVE_STATUS_L_C_INTERPOLATION    = $10000;       // Bit 16, 직선/원호 보간 중                             
    IPDRIVE_STATUS_PATTERN_INTERPOLATION= $20000;       // Bit 17, 비트 패턴 보간 중                             
    IPDRIVE_STATUS_INTERRUPT_BANK1      = $40000;       // Bit 18, 인터럽트 bank1에서 발생                       
    IPDRIVE_STATUS_INTERRUPT_BANK2      = $80000;       // Bit 19, 인터럽트 bank2에서 발생                       
    { 모션제품(IP) 인터럽트 정의        }
    IPINTBANK1_DONTUSE                  = $00000000;    // INTERRUT DISABLED.                                                         
    IPINTBANK1_DRIVE_END                = $00000001;    // Bit 0, Drive end(default value : 1).                                       
    IPINTBANK1_ICG                      = $00000002;    // Bit 1, INCNT is greater than INCNTCMP.                                     
    IPINTBANK1_ICE                      = $00000004;    // Bit 2, INCNT is equal with INCNTCMP.                                       
    IPINTBANK1_ICL                      = $00000008;    // Bit 3, INCNT is less than INCNTCMP.                                        
    IPINTBANK1_ECG                      = $00000010;    // Bit 4, EXCNT is greater than EXCNTCMP.                                     
    IPINTBANK1_ECE                      = $00000020;    // Bit 5, EXCNT is equal with EXCNTCMP.                                       
    IPINTBANK1_ECL                      = $00000040;    // Bit 6, EXCNT is less than EXCNTCMP.                                        
    IPINTBANK1_SCRQEMPTY                = $00000080;    // Bit 7, Script control queue is empty.                                      
    IPINTBANK1_CAPRQEMPTY               = $00000100;    // Bit 8, Caption result data queue is empty.                                 
    IPINTBANK1_SCRREG1EXE               = $00000200;    // Bit 9, Script control register-1 command is executed.                      
    IPINTBANK1_SCRREG2EXE               = $00000400;    // Bit 10, Script control register-2 command is executed.                     
    IPINTBANK1_SCRREG3EXE               = $00000800;    // Bit 11, Script control register-3 command is executed.                     
    IPINTBANK1_CAPREG1EXE               = $00001000;    // Bit 12, Caption control register-1 command is executed.                    
    IPINTBANK1_CAPREG2EXE               = $00002000;    // Bit 13, Caption control register-2 command is executed.                    
    IPINTBANK1_CAPREG3EXE               = $00004000;    // Bit 14, Caption control register-3 command is executed.                    
    IPINTBANK1_INTGGENCMD               = $00008000;    // Bit 15, Interrupt generation command is executed(0xFF)                     
    IPINTBANK1_DOWN                     = $00010000;    // Bit 16, At starting point for deceleration drive.                          
    IPINTBANK1_CONT                     = $00020000;    // Bit 17, At starting point for constant speed drive.                        
    IPINTBANK1_UP                       = $00040000;    // Bit 18, At starting point for acceleration drive.                          
    IPINTBANK1_SIGNALDETECTED           = $00080000;    // Bit 19, Signal assigned in MODE1 is detected.                              
    IPINTBANK1_SP23E                    = $00100000;    // Bit 20, Current speed is equal with rate change point RCP23.               
    IPINTBANK1_SP12E                    = $00200000;    // Bit 21, Current speed is equal with rate change point RCP12.               
    IPINTBANK1_SPE                      = $00400000;    // Bit 22, Current speed is equal with speed comparison data(SPDCMP).         
    IPINTBANK1_INCEICM                  = $00800000;    // Bit 23, INTCNT(1'st counter) is equal with ICM(1'st count minus limit data)
    IPINTBANK1_SCRQEXE                  = $01000000;    // Bit 24, Script queue command is executed When SCRCONQ's 30 bit is '1'.     
    IPINTBANK1_CAPQEXE                  = $02000000;    // Bit 25, Caption queue command is executed When CAPCONQ's 30 bit is '1'.    
    IPINTBANK1_SLM                      = $04000000;    // Bit 26, NSLM/PSLM input signal is activated.                               
    IPINTBANK1_ELM                      = $08000000;    // Bit 27, NELM/PELM input signal is activated.                               
    IPINTBANK1_USERDEFINE1              = $10000000;    // Bit 28, Selectable interrupt source 0(refer "0xFE" command).               
    IPINTBANK1_USERDEFINE2              = $20000000;    // Bit 29, Selectable interrupt source 1(refer "0xFE" command).               
    IPINTBANK1_USERDEFINE3              = $40000000;    // Bit 30, Selectable interrupt source 2(refer "0xFE" command).               
    IPINTBANK1_USERDEFINE4              = $80000000;    // Bit 31, Selectable interrupt source 3(refer "0xFE" command).               
    IPINTBANK2_DONTUSE                  = $00000000;    // INTERRUT DISABLED.                                                   
    IPINTBANK2_L_C_INP_Q_EMPTY          = $00000001;    // Bit 0, Linear/Circular interpolation parameter queue is empty.       
    IPINTBANK2_P_INP_Q_EMPTY            = $00000002;    // Bit 1, Bit pattern interpolation queue is empty.                     
    IPINTBANK2_ALARM_ERROR              = $00000004;    // Bit 2, Alarm input signal is activated.                              
    IPINTBANK2_INPOSITION               = $00000008;    // Bit 3, Inposition input signal is activated.                         
    IPINTBANK2_MARK_SIGNAL_HIGH         = $00000010;    // Bit 4, Mark input signal is activated.                               
    IPINTBANK2_SSTOP_SIGNAL             = $00000020;    // Bit 5, SSTOP input signal is activated.                              
    IPINTBANK2_ESTOP_SIGNAL             = $00000040;    // Bit 6, ESTOP input signal is activated.                              
    IPINTBANK2_SYNC_ACTIVATED           = $00000080;    // Bit 7, SYNC input signal is activated.                               
    IPINTBANK2_TRIGGER_ENABLE           = $00000100;    // Bit 8, Trigger output is activated.                                  
    IPINTBANK2_EXCNTCLR                 = $00000200;    // Bit 9, External(2'nd) counter is cleard by EXCNTCLR setting.         
    IPINTBANK2_FSTCOMPARE_RESULT_BIT0   = $00000400;    // Bit 10, ALU1's compare result bit 0 is activated.                    
    IPINTBANK2_FSTCOMPARE_RESULT_BIT1   = $00000800;    // Bit 11, ALU1's compare result bit 1 is activated.                    
    IPINTBANK2_FSTCOMPARE_RESULT_BIT2   = $00001000;    // Bit 12, ALU1's compare result bit 2 is activated.                    
    IPINTBANK2_FSTCOMPARE_RESULT_BIT3   = $00002000;    // Bit 13, ALU1's compare result bit 3 is activated.                    
    IPINTBANK2_FSTCOMPARE_RESULT_BIT4   = $00004000;    // Bit 14, ALU1's compare result bit 4 is activated.                    
    IPINTBANK2_SNDCOMPARE_RESULT_BIT0   = $00008000;    // Bit 15, ALU2's compare result bit 0 is activated.                    
    IPINTBANK2_SNDCOMPARE_RESULT_BIT1   = $00010000;    // Bit 16, ALU2's compare result bit 1 is activated.                    
    IPINTBANK2_SNDCOMPARE_RESULT_BIT2   = $00020000;    // Bit 17, ALU2's compare result bit 2 is activated.                    
    IPINTBANK2_SNDCOMPARE_RESULT_BIT3   = $00040000;    // Bit 18, ALU2's compare result bit 3 is activated.                    
    IPINTBANK2_SNDCOMPARE_RESULT_BIT4   = $00080000;    // Bit 19, ALU2's compare result bit 4 is activated.                    
    IPINTBANK2_L_C_INP_Q_LESS_4         = $00100000;    // Bit 20, Linear/Circular interpolation parameter queue is less than 4.
    IPINTBANK2_P_INP_Q_LESS_4           = $00200000;    // Bit 21, Pattern interpolation parameter queue is less than 4.        
    IPINTBANK2_XSYNC_ACTIVATED          = $00400000;    // Bit 22, X axis sync input signal is activated.                       
    IPINTBANK2_YSYNC_ACTIVATED          = $00800000;    // Bit 23, Y axis sync input siangl is activated.                       
    IPINTBANK2_P_INP_END_BY_END_PATTERN = $01000000;    // Bit 24, Bit pattern interpolation is terminated by end pattern.      
    //IPINTBANK2_                       = 0x02000000,   // Bit 25, Don't care.
    //IPINTBANK2_                       = 0x04000000,   // Bit 26, Don't care.
    //IPINTBANK2_                       = 0x08000000,   // Bit 27, Don't care.
    //IPINTBANK2_                       = 0x10000000,   // Bit 28, Don't care.
    //IPINTBANK2_                       = 0x20000000,   // Bit 29, Don't care.
    //IPINTBANK2_                       = 0x40000000,   // Bit 30, Don't care.
    //IPINTBANK2_                       = 0x80000000    // Bit 31, Don't care.
    { 모션제품(IP) 신호레벨 상태 정의   }
    IPMECHANICAL_PELM_LEVEL             = $0001;        // Bit 0, +Limit 급정지 신호가 액티브 됨  
    IPMECHANICAL_NELM_LEVEL             = $0002;        // Bit 1, -Limit 급정지 신호 액티브 됨    
    IPMECHANICAL_PSLM_LEVEL             = $0004;        // Bit 2, +limit 감속정지 신호 액티브 됨  
    IPMECHANICAL_NSLM_LEVEL             = $0008;        // Bit 3, -limit 감속정지 신호 액티브 됨  
    IPMECHANICAL_ALARM_LEVEL            = $0010;        // Bit 4, Alarm 신호 액티브 됨            
    IPMECHANICAL_INP_LEVEL              = $0020;        // Bit 5, Inposition 신호 액티브 됨       
    IPMECHANICAL_ENC_DOWN_LEVEL         = $0040;        // Bit 6, 엔코더 DOWN(B상) 신호 입력 Level
    IPMECHANICAL_ENC_UP_LEVEL           = $0080;        // Bit 7, 엔코더 UP(A상) 신호 입력 Level  
    IPMECHANICAL_EXMP_LEVEL             = $0100;        // Bit 8, EXMP 신호 입력 Level            
    IPMECHANICAL_EXPP_LEVEL             = $0200;        // Bit 9, EXPP 신호 입력 Level            
    IPMECHANICAL_MARK_LEVEL             = $0400;        // Bit 10, MARK# 신호 액티브 됨           
    IPMECHANICAL_SSTOP_LEVEL            = $0800;        // Bit 11, SSTOP 신호 액티브 됨           
    IPMECHANICAL_ESTOP_LEVEL            = $1000;        // Bit 12, ESTOP 신호 액티브 됨           
    IPMECHANICAL_SYNC_LEVEL             = $2000;        // Bit 13, SYNC 신호 입력 Level           
    IPMECHANICAL_MODE8_16_LEVEL         = $4000;        // Bit 14, MODE8_16 신호 입력 Level       
    { 모션제품(QI) 신호검출 종류 정의   }
    Signal_PosEndLimit                  = $0;           // +Elm(End limit) +방향 리미트 센서 신호    
    Signal_NegEndLimit                  = $1;           // -Elm(End limit) -방향 리미트 센서 신호    
    Signal_PosSloLimit                  = $2;           // +Slm(Slow Down limit) 신호 - 사용하지 않음
    Signal_NegSloLimit                  = $3;           // -Slm(Slow Down limit) 신호 - 사용하지 않음
    Signal_HomeSensor                   = $4;           // IN0(ORG)  원점 센서 신호                  
    Signal_EncodZPhase                  = $5;           // IN1(Z상)  Encoder Z상 신호                
    Signal_UniInput02                   = $6;           // IN2(범용) 범용 입력 2번 신호              
    Signal_UniInput03                   = $7;           // IN3(범용) 범용 입력 3번 신호              
    { 모션제품(QI) 신호레벨 상태 정의   }
    QIMECHANICAL_PELM_LEVEL             = $00001;       // Bit 0, +Limit 급정지 신호 현재 상태    
    QIMECHANICAL_NELM_LEVEL             = $00002;       // Bit 1, -Limit 급정지 신호 현재 상태    
    QIMECHANICAL_PSLM_LEVEL             = $00004;       // Bit 2, +limit 감속정지 현재 상태.      
    QIMECHANICAL_NSLM_LEVEL             = $00008;       // Bit 3, -limit 감속정지 현재 상태       
    QIMECHANICAL_ALARM_LEVEL            = $00010;       // Bit 4, Alarm 신호 신호 현재 상태       
    QIMECHANICAL_INP_LEVEL              = $00020;       // Bit 5, Inposition 신호 현재 상태       
    QIMECHANICAL_ESTOP_LEVEL            = $00040;       // Bit 6, 비상 정지 신호(ESTOP) 현재 상태.
    QIMECHANICAL_ORG_LEVEL              = $00080;       // Bit 7, 원점 신호 헌재 상태             
    QIMECHANICAL_ZPHASE_LEVEL           = $00100;       // Bit 8, Z 상 입력 신호 현재 상태        
    QIMECHANICAL_ECUP_LEVEL             = $00200;       // Bit 9, ECUP 터미널 신호 상태.          
    QIMECHANICAL_ECDN_LEVEL             = $00400;       // Bit 10, ECDN 터미널 신호 상태.         
    QIMECHANICAL_EXPP_LEVEL             = $00800;       // Bit 11, EXPP 터미널 신호 상태          
    QIMECHANICAL_EXMP_LEVEL             = $01000;       // Bit 12, EXMP 터미널 신호 상태          
    QIMECHANICAL_SQSTR1_LEVEL           = $02000;       // Bit 13, SQSTR1 터미널 신호 상태        
    QIMECHANICAL_SQSTR2_LEVEL           = $04000;       // Bit 14, SQSTR2 터미널 신호 상태        
    QIMECHANICAL_SQSTP1_LEVEL           = $08000;       // Bit 15, SQSTP1 터미널 신호 상태        
    QIMECHANICAL_SQSTP2_LEVEL           = $10000;       // Bit 16, SQSTP2 터미널 신호 상태        
    QIMECHANICAL_MODE_LEVEL             = $20000;       // Bit 17, MODE 터미널 신호 상태.         
    {  모션제품(QI) 구동종료 상태 정의  }               // When 0x0000 after normal drive end.
    QIEND_STATUS_0                      = $00000001;    // Bit 0, 정방향 리미트 신호(PELM)에 의한 종료               
    QIEND_STATUS_1                      = $00000002;    // Bit 1, 역방향 리미트 신호(NELM)에 의한 종료               
    QIEND_STATUS_2                      = $00000004;    // Bit 2, 정방향 부가 리미트 신호(PSLM)에 의한 구동 종료     
    QIEND_STATUS_3                      = $00000008;    // Bit 3, 역방향 부가 리미트 신호(NSLM)에 의한 구동 종료     
    QIEND_STATUS_4                      = $00000010;    // Bit 4, 정방향 소프트 리미트 급정지 기능에 의한 구동 종료  
    QIEND_STATUS_5                      = $00000020;    // Bit 5, 역방향 소프트 리미트 급정지 기능에 의한 구동 종료  
    QIEND_STATUS_6                      = $00000040;    // Bit 6, 정방향 소프트 리미트 감속정지 기능에 의한 구동 종료
    QIEND_STATUS_7                      = $00000080;    // Bit 7, 역방향 소프트 리미트 감속정지 기능에 의한 구동 종료
    QIEND_STATUS_8                      = $00000100;    // Bit 8, 서보 알람 기능에 의한 구동 종료.                   
    QIEND_STATUS_9                      = $00000200;    // Bit 9, 비상 정지 신호 입력에 의한 구동 종료.              
    QIEND_STATUS_10                     = $00000400;    // Bit 10, 급 정지 명령에 의한 구동 종료.                    
    QIEND_STATUS_11                     = $00000800;    // Bit 11, 감속 정지 명령에 의한 구동 종료.                  
    QIEND_STATUS_12                     = $00001000;    // Bit 12, 전축 급정지 명령에 의한 구동 종료                 
    QIEND_STATUS_13                     = $00002000;    // Bit 13, 동기 정지 기능 #1(SQSTP1)에 의한 구동 종료.       
    QIEND_STATUS_14                     = $00004000;    // Bit 14, 동기 정지 기능 #2(SQSTP2)에 의한 구동 종료.       
    QIEND_STATUS_15                     = $00008000;    // Bit 15, 인코더 입력(ECUP,ECDN) 오류 발생                  
    QIEND_STATUS_16                     = $00010000;    // Bit 16, MPG 입력(EXPP,EXMP) 오류 발생                     
    QIEND_STATUS_17                     = $00020000;    // Bit 17, 원점 검색 성공 종료.                              
    QIEND_STATUS_18                     = $00040000;    // Bit 18, 신호 검색 성공 종료.                              
    QIEND_STATUS_19                     = $00080000;    // Bit 19, 보간 데이터 이상으로 구동 종료.                   
    QIEND_STATUS_20                     = $00100000;    // Bit 20, 비정상 구동 정지발생.                             
    QIEND_STATUS_21                     = $00200000;    // Bit 21, MPG 기능 블록 펄스 버퍼 오버플로우 발생           
    QIEND_STATUS_22                     = $00400000;    // Bit 22, DON'CARE                                          
    QIEND_STATUS_23                     = $00800000;    // Bit 23, DON'CARE                                          
    QIEND_STATUS_24                     = $01000000;    // Bit 24, DON'CARE                                          
    QIEND_STATUS_25                     = $02000000;    // Bit 25, DON'CARE                                          
    QIEND_STATUS_26                     = $04000000;    // Bit 26, DON'CARE                                          
    QIEND_STATUS_27                     = $08000000;    // Bit 27, DON'CARE                                          
    QIEND_STATUS_28                     = $10000000;    // Bit 28, 현재/마지막 구동 드라이브 방향                    
    QIEND_STATUS_29                     = $20000000;    // Bit 29, 잔여 펄스 제거 신호 출력 중.                      
    QIEND_STATUS_30                     = $40000000;    // Bit 30, 비정상 구동 정지 원인 상태                        
    QIEND_STATUS_31                     = $80000000;    // Bit 31, 보간 드라이브 데이타 오류 상태.                   
    {  모션제품(QI) 구동상태 정의       }
    QIDRIVE_STATUS_0                    = $0000001;     // Bit 0, BUSY(드라이브 구동 중)                                      
    QIDRIVE_STATUS_1                    = $0000002;     // Bit 1, DOWN(감속 중)                                               
    QIDRIVE_STATUS_2                    = $0000004;     // Bit 2, CONST(등속 중)                                              
    QIDRIVE_STATUS_3                    = $0000008;     // Bit 3, UP(가속 중)                                                 
    QIDRIVE_STATUS_4                    = $0000010;     // Bit 4, 연속 드라이브 구동 중                                       
    QIDRIVE_STATUS_5                    = $0000020;     // Bit 5, 지정 거리 드라이브 구동 중                                  
    QIDRIVE_STATUS_6                    = $0000040;     // Bit 6, MPG 드라이브 구동 중                                        
    QIDRIVE_STATUS_7                    = $0000080;     // Bit 7, 원점검색 드라이브 구동중                                    
    QIDRIVE_STATUS_8                    = $0000100;     // Bit 8, 신호 검색 드라이브 구동 중                                  
    QIDRIVE_STATUS_9                    = $0000200;     // Bit 9, 보간 드라이브 구동 중                                       
    QIDRIVE_STATUS_10                   = $0000400;     // Bit 10, Slave 드라이브 구동중                                      
    QIDRIVE_STATUS_11                   = $0000800;     // Bit 11, 현재 구동 드라이브 방향(보간 드라이브에서는 표시 정보 다름)
    QIDRIVE_STATUS_12                   = $0001000;     // Bit 12, 펄스 출력후 서보위치 완료 신호 대기중.                     
    QIDRIVE_STATUS_13                   = $0002000;     // Bit 13, 직선 보간 드라이브 구동중.                                 
    QIDRIVE_STATUS_14                   = $0004000;     // Bit 14, 원호 보간 드라이브 구동중.                                 
    QIDRIVE_STATUS_15                   = $0008000;     // Bit 15, 펄스 출력 중.                                              
    QIDRIVE_STATUS_16                   = $0010000;     // Bit 16, 구동 예약 데이터 개수(처음)(0-7)                           
    QIDRIVE_STATUS_17                   = $0020000;     // Bit 17, 구동 예약 데이터 개수(중간)(0-7)                           
    QIDRIVE_STATUS_18                   = $0040000;     // Bit 18, 구동 예약 데이터 갯수(끝)(0-7)                             
    QIDRIVE_STATUS_19                   = $0080000;     // Bit 19, 구동 예약 Queue 비어 있음.                                 
    QIDRIVE_STATUS_20                   = $0100000;     // Bit 20, 구동 예약 Queue 가득 찲                                    
    QIDRIVE_STATUS_21                   = $0200000;     // Bit 21, 현재 구동 드라이브의 속도 모드(처음)                       
    QIDRIVE_STATUS_22                   = $0400000;     // Bit 22, 현재 구동 드라이브의 속도 모드(끝)                         
    QIDRIVE_STATUS_23                   = $0800000;     // Bit 23, MPG 버퍼 #1 Full                                           
    QIDRIVE_STATUS_24                   = $1000000;     // Bit 24, MPG 버퍼 #2 Full                                           
    QIDRIVE_STATUS_25                   = $2000000;     // Bit 25, MPG 버퍼 #3 Full                                           
    QIDRIVE_STATUS_26                   = $4000000;     // Bit 26, MPG 버퍼 데이터 OverFlow                                   
    { 모션제품(QI) 인터럽트 정의1       }
    QIINTBANK1_DISABLE                  = $00000000;    // INTERRUT DISABLED.                                               
    QIINTBANK1_0                        = $00000001;    // Bit 0,  인터럽트 발생 사용 설정된 구동 종료시.                   
    QIINTBANK1_1                        = $00000002;    // Bit 1,  구동 종료시                                              
    QIINTBANK1_2                        = $00000004;    // Bit 2,  구동 시작시.                                             
    QIINTBANK1_3                        = $00000008;    // Bit 3,  카운터 #1 < 비교기 #1 이벤트 발생                        
    QIINTBANK1_4                        = $00000010;    // Bit 4,  카운터 #1 = 비교기 #1 이벤트 발생                        
    QIINTBANK1_5                        = $00000020;    // Bit 5,  카운터 #1 > 비교기 #1 이벤트 발생                        
    QIINTBANK1_6                        = $00000040;    // Bit 6,  카운터 #2 < 비교기 #2 이벤트 발생                        
    QIINTBANK1_7                        = $00000080;    // Bit 7,  카운터 #2 = 비교기 #2 이벤트 발생                        
    QIINTBANK1_8                        = $00000100;    // Bit 8,  카운터 #2 > 비교기 #2 이벤트 발생                        
    QIINTBANK1_9                        = $00000200;    // Bit 9,  카운터 #3 < 비교기 #3 이벤트 발생                        
    QIINTBANK1_10                       = $00000400;    // Bit 10, 카운터 #3 = 비교기 #3 이벤트 발생                        
    QIINTBANK1_11                       = $00000800;    // Bit 11, 카운터 #3 > 비교기 #3 이벤트 발생                        
    QIINTBANK1_12                       = $00001000;    // Bit 12, 카운터 #4 < 비교기 #4 이벤트 발생                        
    QIINTBANK1_13                       = $00002000;    // Bit 13, 카운터 #4 = 비교기 #4 이벤트 발생                        
    QIINTBANK1_14                       = $00004000;    // Bit 14, 카운터 #4 < 비교기 #4 이벤트 발생                        
    QIINTBANK1_15                       = $00008000;    // Bit 15, 카운터 #5 < 비교기 #5 이벤트 발생                        
    QIINTBANK1_16                       = $00010000;    // Bit 16, 카운터 #5 = 비교기 #5 이벤트 발생                        
    QIINTBANK1_17                       = $00020000;    // Bit 17, 카운터 #5 > 비교기 #5 이벤트 발생                        
    QIINTBANK1_18                       = $00040000;    // Bit 18, 타이머 #1 이벤트 발생.                                   
    QIINTBANK1_19                       = $00080000;    // Bit 19, 타이머 #2 이벤트 발생.                                   
    QIINTBANK1_20                       = $00100000;    // Bit 20, 구동 예약 설정 Queue 비워짐.                             
    QIINTBANK1_21                       = $00200000;    // Bit 21, 구동 예약 설정 Queue 가득찲                              
    QIINTBANK1_22                       = $00400000;    // Bit 22, 트리거 발생거리 주기/절대위치 Queue 비워짐.              
    QIINTBANK1_23                       = $00800000;    // Bit 23, 트리거 발생거리 주기/절대위치 Queue 가득찲               
    QIINTBANK1_24                       = $01000000;    // Bit 24, 트리거 신호 발생 이벤트                                  
    QIINTBANK1_25                       = $02000000;    // Bit 25, 스크립트 #1 명령어 예약 설정 Queue 비워짐.               
    QIINTBANK1_26                       = $04000000;    // Bit 26, 스크립트 #2 명령어 예약 설정 Queue 비워짐.               
    QIINTBANK1_27                       = $08000000;    // Bit 27, 스크립트 #3 명령어 예약 설정 레지스터 실행되어 초기화 됨.
    QIINTBANK1_28                       = $10000000;    // Bit 28, 스크립트 #4 명령어 예약 설정 레지스터 실행되어 초기화 됨.
    QIINTBANK1_29                       = $20000000;    // Bit 29, 서보 알람신호 인가됨.                                    
    QIINTBANK1_30                       = $40000000;    // Bit 30, |CNT1| - |CNT2| >= |CNT4| 이벤트 발생.                   
    QIINTBANK1_31                       = $80000000;    // Bit 31, 인터럽트 발생 명령어|INTGEN| 실행.                       
    { 모션제품(QI) 인터럽트 정의2       }
    QIINTBANK2_DISABLE                  = $00000000;    // INTERRUT DISABLED.                                                                   
    QIINTBANK2_0                        = $00000001;    // Bit 0,  스크립트 #1 읽기 명령 결과 Queue 가 가득찲.                                  
    QIINTBANK2_1                        = $00000002;    // Bit 1,  스크립트 #2 읽기 명령 결과 Queue 가 가득찲.                                  
    QIINTBANK2_2                        = $00000004;    // Bit 2,  스크립트 #3 읽기 명령 결과 레지스터가 새로운 데이터로 갱신됨.                
    QIINTBANK2_3                        = $00000008;    // Bit 3,  스크립트 #4 읽기 명령 결과 레지스터가 새로운 데이터로 갱신됨.                
    QIINTBANK2_4                        = $00000010;    // Bit 4,  스크립트 #1 의 예약 명령어 중 실행 시 인터럽트 발생으로 설정된 명령어 실행됨.
    QIINTBANK2_5                        = $00000020;    // Bit 5,  스크립트 #2 의 예약 명령어 중 실행 시 인터럽트 발생으로 설정된 명령어 실행됨.
    QIINTBANK2_6                        = $00000040;    // Bit 6,  스크립트 #3 의 예약 명령어 실행 시 인터럽트 발생으로 설정된 명령어 실행됨.   
    QIINTBANK2_7                        = $00000080;    // Bit 7,  스크립트 #4 의 예약 명령어 실행 시 인터럽트 발생으로 설정된 명령어 실행됨.   
    QIINTBANK2_8                        = $00000100;    // Bit 8,  구동 시작                                                                    
    QIINTBANK2_9                        = $00000200;    // Bit 9,  서보 위치 결정 완료(Inposition)기능을 사용한 구동,종료 조건 발생.            
    QIINTBANK2_10                       = $00000400;    // Bit 10, 이벤트 카운터로 동작 시 사용할 이벤트 선택 #1 조건 발생.                     
    QIINTBANK2_11                       = $00000800;    // Bit 11, 이벤트 카운터로 동작 시 사용할 이벤트 선택 #2 조건 발생.                     
    QIINTBANK2_12                       = $00001000;    // Bit 12, SQSTR1 신호 인가 됨.                                                         
    QIINTBANK2_13                       = $00002000;    // Bit 13, SQSTR2 신호 인가 됨.                                                         
    QIINTBANK2_14                       = $00004000;    // Bit 14, UIO0 터미널 신호가 '1'로 변함.                                               
    QIINTBANK2_15                       = $00008000;    // Bit 15, UIO1 터미널 신호가 '1'로 변함.                                               
    QIINTBANK2_16                       = $00010000;    // Bit 16, UIO2 터미널 신호가 '1'로 변함.                                               
    QIINTBANK2_17                       = $00020000;    // Bit 17, UIO3 터미널 신호가 '1'로 변함.                                               
    QIINTBANK2_18                       = $00040000;    // Bit 18, UIO4 터미널 신호가 '1'로 변함.                                               
    QIINTBANK2_19                       = $00080000;    // Bit 19, UIO5 터미널 신호가 '1'로 변함.                                               
    QIINTBANK2_20                       = $00100000;    // Bit 20, UIO6 터미널 신호가 '1'로 변함.                                               
    QIINTBANK2_21                       = $00200000;    // Bit 21, UIO7 터미널 신호가 '1'로 변함.                                               
    QIINTBANK2_22                       = $00400000;    // Bit 22, UIO8 터미널 신호가 '1'로 변함.                                               
    QIINTBANK2_23                       = $00800000;    // Bit 23, UIO9 터미널 신호가 '1'로 변함.                                               
    QIINTBANK2_24                       = $01000000;    // Bit 24, UIO10 터미널 신호가 '1'로 변함.                                              
    QIINTBANK2_25                       = $02000000;    // Bit 25, UIO11 터미널 신호가 '1'로 변함.                                              
    QIINTBANK2_26                       = $04000000;    // Bit 26, 오류 정지 조건(LMT, ESTOP, STOP, ESTOP, CMD, ALARM) 발생.                    
    QIINTBANK2_27                       = $08000000;    // Bit 27, 보간 중 데이터 설정 오류 발생.                                               
    QIINTBANK2_28                       = $10000000;    // Bit 28, Don't Care                                                                   
    QIINTBANK2_29                       = $20000000;    // Bit 29, 리미트 신호(PELM, NELM)신호가 입력 됨.                                       
    QIINTBANK2_30                       = $40000000;    // Bit 30, 부가 리미트 신호(PSLM, NSLM)신호가 입력 됨.                                  
    QIINTBANK2_31                       = $80000000;    // Bit 31, 비상 정지 신호(ESTOP)신호가 입력됨.                                          
    { RTEX 네크웍상태 정의              }
    NET_STATUS_DISCONNECTED             = 1;
    NET_STATUS_LOCK_MISMATCH            = 5;
    NET_STATUS_CONNECTED                = 6;
    { 모션제품(QI) Override 위치 조건   }   
    OVERRIDE_POS_START                  = 0;
    OVERRIDE_POS_END                    = 1;
    { 모션제품(QI) Profile 우선순위     }   
    PRIORITY_VELOCITY                   = 0;
    PRIORITY_ACCELTIME                  = 1;
    { 모션함수 반환형태 정의            }
    FUNC_RETURN_IMMEDIATE               = 0;
    FUNC_RETURN_BLOCKING                = 1;
    FUNC_RETURN_NON_BLOCKING            = 2;
    { 서보팩 알람코드 기록 개수정의     }
    MAX_SERVO_ALARM_HISTORY             = 15;
    
    F_50M_CLK                           = 50000000;
    
    {CNTPORT_DATA_WRITE}
    CnCommand                          = $10;
    CnData1                            = $12;
    CnData2                            = $14;
    CnData3                            = $16;
    CnData4                            = $18;
    CnData12                           = $44;
    CnData34                           = $46;
    {CNTRAM_DATA}
    CnRamAddr1                         = $28;
    CnRamAddr2                         = $2A;
    CnRamAddr3                         = $2C;
    CnRamAddrx1                        = $48;
    CnRamAddr23                        = $4A;
    {PHASE_SEL}
    CnAbPhase                          = 0;
    CnZPhase                           = 1;
    {COUNTER_INPUT}
    CnUpDownMode                       = 0;                            // Up/Down
    CnSqr1Mode                         = 1;                            // 1체배
    CnSqr2Mode                         = 2;                            // 2체배
    CnSqr4Mode                         = 3;                            // 4체배
    {CNTCOMMAND}
    CnCh1CounterRead                   = $10;                           // CH1 COUNTER READ, 24BIT
    CnCh1CounterWrite                  = $90;                           // CH1 COUNTER WRITE
    CnCh1CounterModeRead               = $11;                           // CH1 COUNTER MODE READ, 8BIT
    CnCh1CounterModeWrite              = $91;                           // CH1 COUNTER MODE WRITE
    CnCh1TriggerRegionLowerDataRead    = $12;                           // CH1 TRIGGER REGION LOWER DATA READ, 24BIT
    CnCh1TriggerRegionLowerDataWrite   = $92;                           // CH1 TRIGGER REGION LOWER DATA WRITE
    CnCh1TriggerRegionUpperDataRead    = $13;                           // CH1 TRIGGER REGION UPPER DATA READ, 24BIT
    CnCh1TriggerRegionUpperDataWrite   = $93;                           // CH1 TRIGGER REGION UPPER DATA WRITE
    CnCh1TriggerPeriodRead             = $14;                           // CH1 TRIGGER PERIOD READ, 24BIT, RESERVED
    CnCh1TriggerPeriodWrite            = $94;                           // CH1 TRIGGER PERIOD WRITE
    CnCh1TriggerPulseWidthRead         = $15;                           // CH1 TRIGGER PULSE WIDTH READ
    CnCh1TriggerPulseWidthWrite        = $95;                           // CH1 RIGGER PULSE WIDTH WRITE
    CnCh1TriggerModeRead               = $16;                           // CH1 TRIGGER MODE READ
    CnCh1TriggerModeWrite              = $96;                           // CH1 RIGGER MODE WRITE
    CnCh1TriggerStatusRead             = $17;                           // CH1 TRIGGER STATUS READ
    CnCh1NoOperation_97                = $97;
    CnCh1TriggerEnable                 = $98;
    CnCh1TriggerDisable                = $99;
    CnCh1TimeTriggerFrequencyRead      = $1A;
    CnCh1TimeTriggerFrequencyWrite     = $9A;
    CnCh1ComparatorValueRead           = $1B;
    CnCh1ComparatorValueWrite          = $9B;
    CnCh1CompareatorConditionRead      = $1D;
    CnCh1CompareatorConditionWrite     = $9D;

    // CH-2 Group Register
    CnCh2CounterRead                   = $20;                           // CH2 COUNTER READ, 24BIT
    CnCh2CounterWrite                  = $A1;                           // CH2 COUNTER WRITE
    CnCh2CounterModeRead               = $21;                           // CH2 COUNTER MODE READ, 8BIT
    CnCh2CounterModeWrite              = $A1;                           // CH2 COUNTER MODE WRITE
    CnCh2TriggerRegionLowerDataRead    = $22;                           // CH2 TRIGGER REGION LOWER DATA READ, 24BIT
    CnCh2TriggerRegionLowerDataWrite   = $A2;                           // CH2 TRIGGER REGION LOWER DATA WRITE
    CnCh2TriggerRegionUpperDataRead    = $23;                           // CH2 TRIGGER REGION UPPER DATA READ, 24BIT
    CnCh2TriggerRegionUpperDataWrite   = $A3;                           // CH2 TRIGGER REGION UPPER DATA WRITE
    CnCh2TriggerPeriodRead             = $24;                           // CH2 TRIGGER PERIOD READ, 24BIT, RESERVED
    CnCh2TriggerPeriodWrite            = $A4;                           // CH2 TRIGGER PERIOD WRITE
    CnCh2TriggerPulseWidthRead         = $25;                           // CH2 TRIGGER PULSE WIDTH READ, 24BIT
    CnCh2TriggerPulseWidthWrite        = $A5;                           // CH2 RIGGER PULSE WIDTH WRITE
    CnCh2TriggerModeRead               = $26;                           // CH2 TRIGGER MODE READ
    CnCh2TriggerModeWrite              = $A6;                           // CH2 RIGGER MODE WRITE
    CnCh2TriggerStatusRead             = $27;                           // CH2 TRIGGER STATUS READ
    CnCh2NoOperation_A7	               = $A7;
    CnCh2TriggerEnable                 = $A8;
    CnCh2TriggerDisable                = $A9;
    CnCh2TimeTriggerFrequencyRead      = $2A;
    CnCh2TimeTriggerFrequencyWrite     = $AA;
    CnCh2ComparatorValueRead           = $2B;
    CnCh2ComparatorValueWrite          = $AB;
    CnCh2CompareatorConditionRead      = $2D;
    CnCh2CompareatorConditionWrite     = $AD;

    // Ram Access Group Register
    CnRamDataWithRamAddress            = $30;                           // READ RAM DATA WITH RAM ADDR PORT ADDRESS
    CnRamDataWrite                     = $B0;                           // RAM DATA WRITE
    CnRamDataRead                      = $31;                           // RAM DATA READ, 32BIT
    
    { HPCPORT DATA WRITE }
	HpcReset          = $06;            // Software reset.
    HpcCommand        = $10;
    HpcData12         = $12;            // MSB of data port(31 ~ 16 bit)
    HpcData34         = $14;            // LSB of data port(15 ~ 0 bit)
    HpcCmStatus       = $1C;
	
	{ HPCPORT CH STATUS }
	HpcCh1Mech        = $20;
    HpcCh1Status      = $22;
    HpcCh2Mech        = $30;
    HpcCh2Status      = $32;
    HpcCh3Mech        = $40;
    HpcCh3Status      = $42;
    HpcCh4Mech        = $50;
    HpcCh4Status      = $52;
	
	{ HPCPORT ETC }
	HpcDiIntFlag      = $60;
    HpcDiIntRiseMask  = $62;
    HpcDiIntFallMask  = $64;
    HpcCompIntFlag    = $66;
    HpcCompIntMask    = $68;
    HpcDinData        = $6A;
    HpcDoutData       = $6C;
	
	{ HPCRAM DATA }
	HpcRamAddr1        = $70;            // MSB of Ram address(31  ~ 16 bit)
    HpcRamAddr2        = $72;            // LSB of Ram address(15  ~ 0 bit)
	
{
--1) count_mode
--  0 bit : reverse.(0: normal, 1:reverse)
--  1 bit : count source selection.(0 : A/B 2 phase signal, 1 :  Z phase signal)
--  2~3 bit : count mode
--      "00" up/Down mode 
--      "01" 2 phase, 1times
--      "10" 2 phase, 2times
--      "11" 2 phase, 4times
}

{
-- Description : Trigger pulse generation block for SIO-CN2CH
-- trig_mode
-- 0 bit : trigger signal active level.
-- 1 bit : reserved.
-- 2 bit : trigger signal output method, valid when trig_mode(1) = '0', (0 : pulse out, 1 : level out)
-- 3 bit : reserved.
-- 5~4 bit : Trigger method
--    "00" : absolute mode[with ram data].
--    "01" : timer mode.
--    "10" : absolute mode[with fifo].
--    "11" : periodic mode.
-- 6 bit : direction valid check enable/disable when periodic mode.
-- 7 bit : direction valid when periodic mode.
}

	{ HPCCOMMAND }
	// CH-1 Group Register
    HpcCh1CounterRead                   = $10;                // CH1 COUNTER READ, 32BIT
    HpcCh1CounterWrite                  = $90;                // CH1 COUNTER WRITE, 32BIT
    HpcCh1CounterModeRead               = $11;                // CH1 COUNTER MODE READ, 4BIT
    HpcCh1CounterModeWrite              = $91;                // CH1 COUNTER MODE WRITE, 4BIT
    HpcCh1TriggerRegionLowerDataRead    = $12;                // CH1 TRIGGER REGION LOWER DATA READ, 31BIT
    HpcCh1TriggerRegionLowerDataWrite   = $92;                // CH1 TRIGGER REGION LOWER DATA WRITE
    HpcCh1TriggerRegionUpperDataRead    = $13;                // CH1 TRIGGER REGION UPPER DATA READ, 31BIT
    HpcCh1TriggerRegionUpperDataWrite   = $93;                // CH1 TRIGGER REGION UPPER DATA WRITE
    HpcCh1TriggerPeriodRead             = $14;                // CH1 TRIGGER PERIOD READ, 31BIT
    HpcCh1TriggerPeriodWrite            = $94;                // CH1 TRIGGER PERIOD WRITE
    HpcCh1TriggerPulseWidthRead         = $15;                // CH1 TRIGGER PULSE WIDTH READ, 31BIT
    HpcCh1TriggerPulseWidthWrite        = $95;                // CH1 RIGGER PULSE WIDTH WRITE
    HpcCh1TriggerModeRead               = $16;                // CH1 TRIGGER MODE READ, 8BIT
    HpcCh1TriggerModeWrite              = $96;                // CH1 RIGGER MODE WRITE
    HpcCh1TriggerStatusRead             = $17;                // CH1 TRIGGER STATUS READ, 8BIT
    HpcCh1NoOperation_97                = $97;                // Reserved.
    HpcCh1NoOperation_18                = $17;                // Reserved.
    HpcCh1TriggerEnable                 = $98;                // CH1 TRIGGER ENABLE.
    HpcCh1NoOperation_19                = $19;                // Reserved.
    HpcCh1TriggerDisable                = $99;                // CH1 TRIGGER DISABLE.
    HpcCh1TimeTriggerFrequencyRead      = $1A;                // CH1 TRIGGER FREQUNCE INFO. WRITE, 28BIT
    HpcCh1TimeTriggerFrequencyWrite     = $9A;                // CH1 TRIGGER FREQUNCE INFO. READ
    HpcCh1Comparator1ValueRead          = $1B;                // CH1 COMPAREATOR1 READ, 31BIT
    HpcCh1Comparator1ValueWrite         = $9B;                // CH1 COMPAREATOR1 WRITE, 31BIT
    HpcCh1Comparator2ValueRead          = $1C;                // CH1 COMPAREATOR2 READ, 31BIT
    HpcCh1Comparator2ValueWrite         = $9C;                // CH1 COMPAREATOR2 WRITE, 31BIT
    HpcCh1CompareatorConditionRead      = $1D;                // CH1 COMPAREATOR CONDITION READ, 4BIT
    HpcCh1CompareatorConditionWrite     = $9D;                // CH1 COMPAREATOR CONDITION WRITE, 4BIT
    HpcCh1AbsTriggerTopPositionRead     = $1E;                // CH1 ABS TRIGGER POSITION READ, 31BIT
    HpcCh1AbsTriggerPositionWrite       = $9E;                // CH1 ABS TRIGGER POSITION WRITE, 31BIT
    HpcCh1AbsTriggerFifoStatusRead      = $1F;                // CH1 ABS TRIGGER POSITION FIFO STATUS READ, 16BIT
    HpcCh1AbsTriggerPositionClear       = $9F;                // CH1 ABS TRIGGER POSITION FIFO CLEAR

    // CH-2 Group Register
    HpcCh2CounterRead                   = $20;                // CH2 COUNTER READ, 32BIT
    HpcCh2CounterWrite                  = $A0;                // CH2 COUNTER WRITE, 32BIT
    HpcCh2CounterModeRead               = $21;                // CH2 COUNTER MODE READ, 4BIT
    HpcCh2CounterModeWrite              = $A1;                // CH2 COUNTER MODE WRITE, 4BIT
    HpcCh2TriggerRegionLowerDataRead    = $22;                // CH2 TRIGGER REGION LOWER DATA READ, 31BIT
    HpcCh2TriggerRegionLowerDataWrite   = $A2;                // CH2 TRIGGER REGION LOWER DATA WRITE
    HpcCh2TriggerRegionUpperDataRead    = $23;                // CH2 TRIGGER REGION UPPER DATA READ, 31BIT
    HpcCh2TriggerRegionUpperDataWrite   = $A3;                // CH2 TRIGGER REGION UPPER DATA WRITE
    HpcCh2TriggerPeriodRead             = $24;                // CH2 TRIGGER PERIOD READ, 31BIT
    HpcCh2TriggerPeriodWrite            = $A4;                // CH2 TRIGGER PERIOD WRITE
    HpcCh2TriggerPulseWidthRead         = $25;                // CH2 TRIGGER PULSE WIDTH READ, 31BIT
    HpcCh2TriggerPulseWidthWrite        = $A5;                // CH2 RIGGER PULSE WIDTH WRITE
    HpcCh2TriggerModeRead               = $26;                // CH2 TRIGGER MODE READ, 8BIT
    HpcCh2TriggerModeWrite              = $A6;                // CH2 RIGGER MODE WRITE
    HpcCh2TriggerStatusRead             = $27;                // CH2 TRIGGER STATUS READ, 8BIT
    HpcCh2NoOperation_97                = $A7;                // Reserved.
    HpcCh2NoOperation_18                = $27;                // Reserved.
    HpcCh2TriggerEnable                 = $A8;                // CH2 TRIGGER ENABLE.
    HpcCh2NoOperation_19                = $29;                // Reserved.
    HpcCh2TriggerDisable                = $A9;                // CH2 TRIGGER DISABLE.
    HpcCh2TimeTriggerFrequencyRead      = $2A;                // CH2 TRIGGER FREQUNCE INFO. WRITE, 28BIT
    HpcCh2TimeTriggerFrequencyWrite     = $AA;                // CH2 TRIGGER FREQUNCE INFO. READ
    HpcCh2Comparator1ValueRead          = $2B;                // CH2 COMPAREATOR1 READ, 31BIT
    HpcCh2Comparator1ValueWrite         = $AB;                // CH2 COMPAREATOR1 WRITE, 31BIT
    HpcCh2Comparator2ValueRead          = $2C;                // CH2 COMPAREATOR2 READ, 31BIT
    HpcCh2Comparator2ValueWrite         = $AC;                // CH2 COMPAREATOR2 WRITE, 31BIT
    HpcCh2CompareatorConditionRead      = $2D;                // CH2 COMPAREATOR CONDITION READ, 4BIT
    HpcCh2CompareatorConditionWrite     = $AD;                // CH2 COMPAREATOR CONDITION WRITE, 4BIT
    HpcCh2AbsTriggerTopPositionRead     = $2E;                // CH2 ABS TRIGGER POSITION READ, 31BIT
    HpcCh2AbsTriggerPositionWrite       = $AE;                // CH2 ABS TRIGGER POSITION WRITE, 31BIT
    HpcCh2AbsTriggerFifoStatusRead      = $2F;                // CH2 ABS TRIGGER POSITION FIFO STATUS READ, 16BIT
    HpcCh2AbsTriggerPositionClear       = $AF;                // CH2 ABS TRIGGER POSITION FIFO CLEAR

    // CH-3 Group Register
    HpcCh3CounterRead                   = $30;                // CH3 COUNTER READ, 32BIT
    HpcCh3CounterWrite                  = $B0;                // CH3 COUNTER WRITE, 32BIT
    HpcCh3CounterModeRead               = $31;                // CH3 COUNTER MODE READ, 4BIT
    HpcCh3CounterModeWrite              = $B1;                // CH3 COUNTER MODE WRITE, 4BIT
    HpcCh3TriggerRegionLowerDataRead    = $32;                // CH3 TRIGGER REGION LOWER DATA READ, 31BIT
    HpcCh3TriggerRegionLowerDataWrite   = $B2;                // CH3 TRIGGER REGION LOWER DATA WRITE
    HpcCh3TriggerRegionUpperDataRead    = $33;                // CH3 TRIGGER REGION UPPER DATA READ, 31BIT
    HpcCh3TriggerRegionUpperDataWrite   = $B3;                // CH3 TRIGGER REGION UPPER DATA WRITE
    HpcCh3TriggerPeriodRead             = $34;                // CH3 TRIGGER PERIOD READ, 31BIT
    HpcCh3TriggerPeriodWrite            = $B4;                // CH3 TRIGGER PERIOD WRITE
    HpcCh3TriggerPulseWidthRead         = $35;                // CH3 TRIGGER PULSE WIDTH READ, 31BIT
    HpcCh3TriggerPulseWidthWrite        = $B5;                // CH3 RIGGER PULSE WIDTH WRITE
    HpcCh3TriggerModeRead               = $36;                // CH3 TRIGGER MODE READ, 8BIT
    HpcCh3TriggerModeWrite              = $B6;                // CH3 RIGGER MODE WRITE
    HpcCh3TriggerStatusRead             = $37;                // CH3 TRIGGER STATUS READ, 8BIT
    HpcCh3NoOperation_97                = $B7;                // Reserved.
    HpcCh3NoOperation_18                = $37;                // Reserved.
    HpcCh3TriggerEnable                 = $B8;                // CH3 TRIGGER ENABLE.
    HpcCh3NoOperation_19                = $39;                // Reserved.
    HpcCh3TriggerDisable                = $B9;                // CH3 TRIGGER DISABLE.
    HpcCh3TimeTriggerFrequencyRead      = $3A;                // CH3 TRIGGER FREQUNCE INFO. WRITE, 28BIT
    HpcCh3TimeTriggerFrequencyWrite     = $BA;                // CH3 TRIGGER FREQUNCE INFO. READ
    HpcCh3Comparator1ValueRead          = $3B;                // CH3 COMPAREATOR1 READ, 31BIT
    HpcCh3Comparator1ValueWrite         = $BB;                // CH3 COMPAREATOR1 WRITE, 31BIT
    HpcCh3Comparator2ValueRead          = $3C;                // CH3 COMPAREATOR2 READ, 31BIT
    HpcCh3Comparator2ValueWrite         = $BC;                // CH3 COMPAREATOR2 WRITE, 31BIT
    HpcCh3CompareatorConditionRead      = $3D;                // CH3 COMPAREATOR CONDITION READ, 4BIT
    HpcCh3CompareatorConditionWrite     = $BD;                // CH3 COMPAREATOR CONDITION WRITE, 4BIT
    HpcCh3AbsTriggerTopPositionRead     = $3E;                // CH3 ABS TRIGGER POSITION READ, 31BIT
    HpcCh3AbsTriggerPositionWrite       = $BE;                // CH3 ABS TRIGGER POSITION WRITE, 31BIT
    HpcCh3AbsTriggerFifoStatusRead      = $3F;                // CH3 ABS TRIGGER POSITION FIFO STATUS READ, 16BIT
    HpcCh3AbsTriggerPositionClear       = $BF;                // CH3 ABS TRIGGER POSITION FIFO CLEAR

    // CH-4 Group Register
    HpcCh4CounterRead                   = $40;                // CH4 COUNTER READ, 32BIT
    HpcCh4CounterWrite                  = $C0;                // CH4 COUNTER WRITE, 32BIT
    HpcCh4CounterModeRead               = $41;                // CH4 COUNTER MODE READ, 4BIT
    HpcCh4CounterModeWrite              = $C1;                // CH4 COUNTER MODE WRITE, 4BIT
    HpcCh4TriggerRegionLowerDataRead    = $42;                // CH4 TRIGGER REGION LOWER DATA READ, 31BIT
    HpcCh4TriggerRegionLowerDataWrite   = $C2;                // CH4 TRIGGER REGION LOWER DATA WRITE
    HpcCh4TriggerRegionUpperDataRead    = $43;                // CH4 TRIGGER REGION UPPER DATA READ, 31BIT
    HpcCh4TriggerRegionUpperDataWrite   = $C3;                // CH4 TRIGGER REGION UPPER DATA WRITE
    HpcCh4TriggerPeriodRead             = $44;                // CH4 TRIGGER PERIOD READ, 31BIT
    HpcCh4TriggerPeriodWrite            = $C4;                // CH4 TRIGGER PERIOD WRITE
    HpcCh4TriggerPulseWidthRead         = $45;                // CH4 TRIGGER PULSE WIDTH READ, 31BIT
    HpcCh4TriggerPulseWidthWrite        = $C5;                // CH4 RIGGER PULSE WIDTH WRITE
    HpcCh4TriggerModeRead               = $46;                // CH4 TRIGGER MODE READ, 8BIT
    HpcCh4TriggerModeWrite              = $C6;                // CH4 RIGGER MODE WRITE
    HpcCh4TriggerStatusRead             = $47;                // CH4 TRIGGER STATUS READ, 8BIT
    HpcCh4NoOperation_97                = $C7;                // Reserved.
    HpcCh4NoOperation_18                = $47;                // Reserved.
    HpcCh4TriggerEnable                 = $C8;                // CH4 TRIGGER ENABLE.
    HpcCh4NoOperation_19                = $49;                // Reserved.
    HpcCh4TriggerDisable                = $C9;                // CH4 TRIGGER DISABLE.
    HpcCh4TimeTriggerFrequencyRead      = $4A;                // CH4 TRIGGER FREQUNCE INFO. WRITE, 28BIT
    HpcCh4TimeTriggerFrequencyWrite     = $CA;                // CH4 TRIGGER FREQUNCE INFO. READ
    HpcCh4Comparator1ValueRead          = $4B;                // CH4 COMPAREATOR1 READ, 31BIT
    HpcCh4Comparator1ValueWrite         = $CB;                // CH4 COMPAREATOR1 WRITE, 31BIT
    HpcCh4Comparator2ValueRead          = $4C;                // CH4 COMPAREATOR2 READ, 31BIT
    HpcCh4Comparator2ValueWrite         = $CC;                // CH4 COMPAREATOR2 WRITE, 31BIT
    HpcCh4CompareatorConditionRead      = $4D;                // CH4 COMPAREATOR CONDITION READ, 4BIT
    HpcCh4CompareatorConditionWrite     = $CD;                // CH4 COMPAREATOR CONDITION WRITE, 4BIT
    HpcCh4AbsTriggerTopPositionRead     = $4E;                // CH4 ABS TRIGGER POSITION READ, 31BIT
    HpcCh4AbsTriggerPositionWrite       = $CE;                // CH4 ABS TRIGGER POSITION WRITE, 31BIT
    HpcCh4AbsTriggerFifoStatusRead      = $4F;                // CH4 ABS TRIGGER POSITION FIFO STATUS READ, 16BIT
    HpcCh4AbsTriggerPositionClear       = $CF;                // CH4 ABS TRIGGER POSITION FIFO CLEAR

    // Ram Access Group Register
    HpcRamDataWithRamAddress            = $51;                // READ RAM DATA WITH RAM ADDR PORT ADDRESS
    HpcRamDataWrite                     = $D0;                // RAM DATA WRITE
    HpcRamDataRead                      = $50;                // RAM DATA READ, 32BIT

    // Debugging Registers    
    HpcCh1TrigPosIndexRead              = $60;                // CH1 Current RAM trigger index position on 32Bit data, 8BIT
    HpcCh1TrigBackwardDataRead          = $61;                // CH1 Current RAM trigger backward position data, 32BIT
    HpcCh1TrigCurrentDataRead           = $62;                // CH1 Current RAM trigger current position data, 32BIT
    HpcCh1TrigForwardDataRead           = $63;                // CH1 Current RAM trigger next position data, 32BIT
    HpcCh1TrigRamAddressRead            = $64;                // CH1 Current RAM trigger address, 20BIT

    HpcCh2TrigPosIndexRead              = $65;                // CH2 Current RAM trigger index position on 32Bit data, 8BIT
    HpcCh2TrigBackwardDataRead          = $66;                // CH2 Current RAM trigger backward position data, 32BIT
    HpcCh2TrigCurrentDataRead           = $67;                // CH2 Current RAM trigger current position data, 32BIT
    HpcCh2TrigForwardDataRead           = $68;                // CH2 Current RAM trigger next position data, 32BIT
    HpcCh2TrigRamAddressRead            = $69;                // CH2 Current RAM trigger address, 20BIT

    HpcCh3TrigPosIndexRead              = $70;                // CH3 Current RAM trigger index position on 32Bit data, 8BIT
    HpcCh3TrigBackwardDataRead          = $71;                // CH3 Current RAM trigger backward position data, 32BIT
    HpcCh3TrigCurrentDataRead           = $72;                // CH3 Current RAM trigger current position data, 32BIT
    HpcCh3TrigForwardDataRead           = $73;                // CH3 Current RAM trigger next position data, 32BIT
    HpcCh3TrigRamAddressRead            = $74;                // CH3 Current RAM trigger address, 20BIT

    HpcCh4TrigPosIndexRead              = $75;                // CH4 Current RAM trigger index position on 32Bit data, 8BIT
    HpcCh4TrigBackwardDataRead          = $76;                // CH4 Current RAM trigger backward position data, 32BIT
    HpcCh4TrigCurrentDataRead           = $77;                // CH4 Current RAM trigger current position data, 32BIT
    HpcCh4TrigForwardDataRead           = $78;                // CH4 Current RAM trigger next position data, 32BIT
    HpcCh4TrigRamAddressRead            = $79;                // CH4 Current RAM trigger address, 20BIT

    HpcCh1TestEnable                    = $81;                // CH1 test enable(Manufacturer only)
    HpcCh2TestEnable                    = $82;                // CH2 test enable(Manufacturer only)
    HpcCh3TestEnable                    = $83;                // CH3 test enable(Manufacturer only)
    HpcCh4TestEnable                    = $84;                // CH4 test enable(Manufacturer only)

    HpcTestFrequency                    = $8C;                // Test counter output frequency(32bit)
    HpcTestCountStart                   = $8D;                // Start test counter output with position(32bit signed).
    HpcTestCountEnd                     = $8E;                // End counter output.

    HpcCh1TrigVectorTopDataOfFifo       = $54;                // CH1 UnitVector X positin of FIFO top.
    HpcCh1TrigVectorFifoStatus          = $55;                // CH1 UnitVector X FIFO Status.
    HpcCh2TrigVectorTopDataOfFifo       = $56;                // CH2 UnitVector Y positin of FIFO top.
    HpcCh2TrigVectorFifoStatus          = $57;                // CH2 UnitVector Y FIFO Status.
    HpcCh1TrigVectorFifoPush            = $D2;                // CH1 UnitVector X position, fifo data push.
    HpcCh2TrigVectorFifoPush            = $D3;                // CH2 UnitVector Y position, fifo data push.
    
implementation
end.
