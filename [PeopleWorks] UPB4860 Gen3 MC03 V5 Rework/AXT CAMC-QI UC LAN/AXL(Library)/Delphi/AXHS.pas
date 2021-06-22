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
    {  ���̽����� ����                  }
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
    AXT_PCI_DI64R                       = $43;          // PCI bus, Digital IN 64��
    AXT_PCIE_DI64R                      = $44;          // PCIe bus, Digital IN 64��
    AXT_PCI_DO64R                       = $53;          // PCI bus, Digital OUT 64��
    AXT_PCIE_DO64R                      = $54;          // PCIe bus, Digital OUT 64��
    AXT_PCI_DB64R                       = $63;          // PCI bus, Digital IN 32��, OUT 32��
    AXT_PCIE_DB64R                      = $64;          // PCIe bus, Digital IN 32��, OUT 32��
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

    { �����ǰ ����                     }
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
    AXT_SIO_RSIMPLEIOMLII               = $7E;          // Digital IN/Out xx��, Simple I/O sereies, MLII ����.
    AXT_SIO_RDO16AMLIII                 = $7F;          // DO slave module, MechatroLink III M-SYSTEM, OUT 16-Channel, NPN
    AXT_SIO_RDI16MLII                   = $80;          // DISCRETE INPUT MODULE, 16 points (Product by M-SYSTEM), For MLII only
    AXT_SIO_RDO16AMLII                  = $81;          // NPN TRANSISTOR OUTPUT MODULE, 16 points (Product by M-SYSTEM), For MLII only
    AXT_SIO_RDO16BMLII                  = $82;          // PNP TRANSISTOR OUTPUT MODULE, 16 points (Product by M-SYSTEM), For MLII only
    AXT_SIO_RDB96MLII                   = $83;          // Digital IN/OUT(Selectable), MAX 96 points, For MLII only
    AXT_SIO_RDO32RTE                    = $84;          // Digital OUT  32��
    AXT_SIO_RDI32RTEX                   = $85;          // Digital IN  32��
    AXT_SIO_RDB32RTEX                   = $86;          // Digital IN/OUT  32��
	AXT_SIO_RDO16BMLIII                 = $8A;          // DO slave module, MechatroLink III M-SYSTEM, OUT 16-Channel, PNP
	AXT_SIO_RDB32ML2NT1                 = $8B,          // DB slave module, MechatroLink2 AJINEXTEK NT1 Series
    AXT_SIO_RDB128YSMLIII               = $8C,          // IO slave module, MechatroLink III Any, Max. IN 480-Channel, Max. OUT 480-Channel
    AXT_SIO_DI32_P                      = $92;          // Digital IN  32��, PNP type(source type)
    AXT_SIO_DO32T_P                     = $93;          // Digital OUT 32��, Power TR, PNT type(source type)
    AXT_SIO_RDB128MLII                  = $94;          // Digital IN 64�� / OUT 64��, MLII ����(JEPMC-IO2310)
    AXT_SIO_RDI32                       = $95;          // Digital IN  32��, For RTEX only
    AXT_SIO_RDO32                       = $96;          // Digital OUT 32��, For RTEX only
    AXT_SIO_DI32                        = $97;          // Digital IN  32��
    AXT_SIO_DO32P                       = $98;          // Digital OUT 32��
    AXT_SIO_DB32P                       = $99;          // Digital IN 16�� / OUT 16��
    AXT_SIO_RDB32T                      = $9A;          // Digital IN 16�� / OUT 16��, For RTEX only
    AXT_SIO_DO32T                       = $9E;          // Digital OUT 16��, Power TR ���
    AXT_SIO_DB32T                       = $9F;          // Digital IN 16�� / OUT 16��, Power TR ���
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
    { �Լ� ��ȯ�� ����                  }
    AXT_RT_SUCCESS                      = 0;            // API �Լ� ���� ����
    AXT_RT_OPEN_ERROR                   = 1001;         // ���̺귯�� ���� ��������
    AXT_RT_OPEN_ALREADY                 = 1002;         // ���̺귯�� ���� �Ǿ��ְ� ��� ����
    AXT_RT_NOT_OPEN                     = 1053;         // ���̺귯�� �ʱ�ȭ ����
    AXT_RT_NOT_SUPPORT_VERSION          = 1054;         // ���������ʴ� �ϵ����
    AXT_RT_LOCK_FILE_MISMATCH           = 1055;         // Lock���ϰ� ���� Scan������ ��ġ���� ���� 

    AXT_RT_INVALID_BOARD_NO             = 1101;         // ��ȿ���� �ʴ� ���� ��ȣ
    AXT_RT_INVALID_MODULE_POS           = 1102;         // ��ȿ���� �ʴ� ��� ��ġ
    AXT_RT_INVALID_LEVEL                = 1103;         // ��ȿ���� �ʴ� ����
    AXT_RT_INVALID_VARIABLE             = 1104;         // ��ȿ���� �ʴ� ����
    AXT_RT_ERROR_VERSION_READ           = 1151;         // ���̺귯�� ������ ������ ����
    AXT_RT_NETWORK_ERROR                = 1152;         // �ϵ���� ��Ʈ��ũ ����
    AXT_RT_NETWORK_LOCK_MISMATCH        = 1153;         // ���� Lock������ ���� Scan������ ��ġ���� ����
    
    AXT_RT_1ST_BELOW_MIN_VALUE          = 1160;         // ù��° ���ڰ��� �ּҰ����� �� ����                                
    AXT_RT_1ST_ABOVE_MAX_VALUE          = 1161;         // ù��° ���ڰ��� �ִ밪���� �� ŭ                                  
    AXT_RT_2ND_BELOW_MIN_VALUE          = 1170;         // �ι�° ���ڰ��� �ּҰ����� �� ����                                
    AXT_RT_2ND_ABOVE_MAX_VALUE          = 1171;         // �ι�° ���ڰ��� �ִ밪���� �� ŭ                                  
    AXT_RT_3RD_BELOW_MIN_VALUE          = 1180;         // ����° ���ڰ��� �ּҰ����� �� ����                                
    AXT_RT_3RD_ABOVE_MAX_VALUE          = 1181;         // ����° ���ڰ��� �ִ밪���� �� ŭ                                  
    AXT_RT_4TH_BELOW_MIN_VALUE          = 1190;         // �׹�° ���ڰ��� �ּҰ����� �� ����                                
    AXT_RT_4TH_ABOVE_MAX_VALUE          = 1191;         // �׹�° ���ڰ��� �ִ밪���� �� ŭ                                  
    AXT_RT_5TH_BELOW_MIN_VALUE          = 1200;         // �ټ���° ���ڰ��� �ּҰ����� �� ����                              
    AXT_RT_5TH_ABOVE_MAX_VALUE          = 1201;         // �ټ���° ���ڰ��� �ִ밪���� �� ŭ                                
    AXT_RT_6TH_BELOW_MIN_VALUE          = 1210;         // ������° ���ڰ��� �ּҰ����� �� ����                              
    AXT_RT_6TH_ABOVE_MAX_VALUE          = 1211;         // ������° ���ڰ��� �ִ밪���� �� ŭ                                
    AXT_RT_7TH_BELOW_MIN_VALUE          = 1220;         // �ϰ���° ���ڰ��� �ּҰ����� �� ����                              
    AXT_RT_7TH_ABOVE_MAX_VALUE          = 1221;         // �ϰ���° ���ڰ��� �ִ밪���� �� ŭ                                
    AXT_RT_8TH_BELOW_MIN_VALUE          = 1230;         // ������° ���ڰ��� �ּҰ����� �� ����                              
    AXT_RT_8TH_ABOVE_MAX_VALUE          = 1231;         // ������° ���ڰ��� �ִ밪���� �� ŭ                                
    AXT_RT_9TH_BELOW_MIN_VALUE          = 1240;         // ��ȩ��° ���ڰ��� �ּҰ����� �� ����                              
    AXT_RT_9TH_ABOVE_MAX_VALUE          = 1241;         // ��ȩ��° ���ڰ��� �ִ밪���� �� ŭ                                
    AXT_RT_10TH_BELOW_MIN_VALUE         = 1250;         // ����° ���ڰ��� �ּҰ����� �� ����                                
    AXT_RT_10TH_ABOVE_MAX_VALUE         = 1251;         // ����° ���ڰ��� �ִ밪���� �� ŭ   
    AXT_RT_11TH_BELOW_MIN_VALUE         = 1252;         // ���ѹ�° ���ڰ��� �ּҰ����� �� ����                                
    AXT_RT_11TH_ABOVE_MAX_VALUE         = 1253;         // ���ѹ�° ���ڰ��� �ִ밪���� �� ŭ                                      
    AXT_RT_AIO_OPEN_ERROR               = 2001;         // AIO ��� ���½���                                                 
    AXT_RT_AIO_NOT_MODULE               = 2051;         // AIO ��� ����                                                     
    AXT_RT_AIO_NOT_EVENT                = 2052;         // AIO �̺�Ʈ ���� ����                                              
    AXT_RT_AIO_INVALID_MODULE_NO        = 2101;         // ��ȿ�������� AIO���                                              
    AXT_RT_AIO_INVALID_CHANNEL_NO       = 2102;         // ��ȿ�������� AIOä�ι�ȣ                                          
    AXT_RT_AIO_INVALID_USE              = 2106;         // AIO �Լ� ������                                                 
    AXT_RT_AIO_INVALID_TRIGGER_MODE     = 2107;         // ��ȿ�����ʴ� Ʈ���� ���       
    AXT_RT_AIO_EXTERNAL_DATA_EMPTY      = 2108;         // �ܺ� ������ ���� ���� ���
    AXT_RT_AIO_INVALID_VALUE            = 2109;         // ��ȿ�����ʴ� �� ����
    AXT_RT_AIO_UPG_ALEADY_ENABLED       = 2110;         // AO UPG ��� ����� ������

    AXT_RT_DIO_OPEN_ERROR               = 3001;         // DIO ��� ���½���                                                 
    AXT_RT_DIO_NOT_MODULE               = 3051;         // DIO ��� ����                                                     
    AXT_RT_DIO_NOT_INTERRUPT            = 3052;         // DIO ���ͷ�Ʈ �����ȵ�                                             
    AXT_RT_DIO_INVALID_MODULE_NO        = 3101;         // ��ȿ�����ʴ� DIO ��� ��ȣ                                        
    AXT_RT_DIO_INVALID_OFFSET_NO        = 3102;         // ��ȿ�����ʴ� DIO OFFSET ��ȣ                                      
    AXT_RT_DIO_INVALID_LEVEL            = 3103;         // ��ȿ�����ʴ� DIO ����                                             
    AXT_RT_DIO_INVALID_MODE             = 3104;         // ��ȿ�����ʴ� DIO ���                                             
    AXT_RT_DIO_INVALID_VALUE            = 3105;         // ��ȿ�����ʴ� �� ����                                              
    AXT_RT_DIO_INVALID_USE              = 3106;         // DIO �Լ� ������
    
    AXT_RT_CNT_OPEN_ERROR               = 3201;         // CNT ��� ���½���
    AXT_RT_CNT_NOT_MODULE               = 3251;         // CNT ��� ����
    AXT_RT_CNT_NOT_INTERRUPT            = 3252;         // CNT ���ͷ�Ʈ �����ȵ�
    AXT_RT_CNT_INVALID_MODULE_NO        = 3301;         // ��ȿ�����ʴ� CNT ��� ��ȣ
    AXT_RT_CNT_INVALID_CHANNEL_NO       = 3302;         // ��ȿ�����ʴ� ä�� ��ȣ
    AXT_RT_CNT_INVALID_OFFSET_NO        = 3303;         // ��ȿ�����ʴ� CNT OFFSET ��ȣ
    AXT_RT_CNT_INVALID_LEVEL            = 3304;         // ��ȿ�����ʴ� CNT ����
    AXT_RT_CNT_INVALID_MODE             = 3305;         // ��ȿ�����ʴ� CNT ���
    AXT_RT_CNT_INVALID_VALUE            = 3306;         // ��ȿ�����ʴ� �� ����
    AXT_RT_CNT_INVALID_USE              = 3307;         // CNT �Լ� ������      
                                            
    AXT_RT_MOTION_OPEN_ERROR            = 4001;         // ��� ���̺귯�� Open ����                                         
    AXT_RT_MOTION_NOT_MODULE            = 4051;         // �ý��ۿ� ������ ��� ����� ����                                  
    AXT_RT_MOTION_NOT_INTERRUPT         = 4052;         // ���ͷ�Ʈ ��� �б� ����                                           
    AXT_RT_MOTION_NOT_INITIAL_AXIS_NO   = 4053;         // �ش� �� ��� �ʱ�ȭ ����                                          
    AXT_RT_MOTION_NOT_IN_CONT_INTERPOL  = 4054;         // ���� ���� ���� ���� �ƴ� ���¿��� ���Ӻ��� ���� ����� ���� �Ͽ���
    AXT_RT_MOTION_NOT_PARA_READ         = 4055;         // ���� ���� ���� �Ķ���� �ε� ����                                 
    AXT_RT_MOTION_INVALID_AXIS_NO       = 4101;         // �ش� ���� �������� ����                                           
    AXT_RT_MOTION_INVALID_METHOD        = 4102;         // �ش� �� ������ �ʿ��� ������ �߸���                               
    AXT_RT_MOTION_INVALID_USE           = 4103;         // 'uUse' ���ڰ��� �߸� ������                                       
    AXT_RT_MOTION_INVALID_LEVEL         = 4104;         // 'uLevel' ���ڰ��� �߸� ������                                     
    AXT_RT_MOTION_INVALID_BIT_NO        = 4105;         // ���� ����� �ش� ��Ʈ�� �߸� ������                               
    AXT_RT_MOTION_INVALID_STOP_MODE     = 4106;         // ��� ���� ��� �������� �߸���                                    
    AXT_RT_MOTION_INVALID_TRIGGER_MODE  = 4107;         // Ʈ���� ���� ��尡 �߸� ������                                    
    AXT_RT_MOTION_INVALID_TRIGGER_LEVEL = 4108;         // Ʈ���� ��� ���� ������ �߸���                                        
    AXT_RT_MOTION_INVALID_SELECTION     = 4109;         // 'uSelection' ���ڰ� COMMAND �Ǵ� ACTUAL �̿��� ������ �����Ǿ� ����   
    AXT_RT_MOTION_INVALID_TIME          = 4110;         // Trigger ��� �ð����� �߸� �����Ǿ� ����                              
    AXT_RT_MOTION_INVALID_FILE_LOAD     = 4111;         // ��� �������� ����� ������ �ε尡 �ȵ�                               
    AXT_RT_MOTION_INVALID_FILE_SAVE     = 4112;         // ��� �������� �����ϴ� ���� ���忡 ������                             
    AXT_RT_MOTION_INVALID_VELOCITY      = 4113;         // ��� ���� �ӵ����� 0���� �����Ǿ� ��� ���� �߻�                      
    AXT_RT_MOTION_INVALID_ACCELTIME     = 4114;         // ��� ���� ���� �ð����� 0���� �����Ǿ� ��� ���� �߻�                 
    AXT_RT_MOTION_INVALID_PULSE_VALUE   = 4115;         // ��� ���� ���� �� �Է� �޽����� 0���� ���������� ������               
    AXT_RT_MOTION_INVALID_NODE_NUMBER   = 4116;         // ��ġ�� �ӵ� �������̵� �Լ��� ��� ���� �߿� ���ܵ�                   
    AXT_RT_MOTION_INVALID_TARGET        = 4117;         // ���� ��� ���� ���ο� ���� �÷��׸� ��ȯ�Ѵ�.                         

    AXT_RT_MOTION_ERROR_IN_NONMOTION    = 4151;         // ��� �������̾�� �Ǵµ� ��� �������� �ƴ� ��                        
    AXT_RT_MOTION_ERROR_IN_MOTION       = 4152;         // ��� ���� �߿� �ٸ� ��� ���� �Լ��� ������                           
    AXT_RT_MOTION_ERROR                 = 4153;         // ���� ���� ���� �Լ� ���� �� ���� �߻���                               
    AXT_RT_MOTION_ERROR_GANTRY_ENABLE   = 4154;         // ��Ʈ�� enable�� �Ǿ��־� ������� �� �� ��Ʈ�� enable�� ������ ��     
    AXT_RT_MOTION_ERROR_GANTRY_AXIS     = 4155;         // ��Ʈ�� ���� ������ä��(��) ��ȣ(0 ~ (�ִ���� - 1))�� �߸� ���� ��
    AXT_RT_MOTION_ERROR_MASTER_SERVOON  = 4156;         // ������ �� �������� �ȵǾ����� ��                                      
    AXT_RT_MOTION_ERROR_SLAVE_SERVOON   = 4157;         // �����̺� �� �������� �ȵǾ����� ��                                    
    AXT_RT_MOTION_INVALID_POSITION      = 4158;         // ��ȿ�� ��ġ�� ���� ��                                                 
    AXT_RT_ERROR_NOT_SAME_MODULE        = 4159;         // �� ���� ��⳻�� ���� �������                                        
    AXT_RT_ERROR_NOT_SAME_BOARD         = 4160;         // �� ���� ���峻�� ���� �ƴҰ��                                        
    AXT_RT_ERROR_NOT_SAME_PRODUCT       = 4161;         // ��ǰ�� ���� �ٸ����                                                  
    AXT_RT_NOT_CAPTURED                 = 4162;         // ��ġ�� ������� ���� ��                                               
    AXT_RT_ERROR_NOT_SAME_IC            = 4163;         // ���� Ĩ���� ������������ ��                                           
    AXT_RT_ERROR_NOT_GEARMODE           = 4164;         // ������ ��ȯ�� �ȵ� ��                                             
    AXT_ERROR_CONTI_INVALID_AXIS_NO     = 4165;         // ���Ӻ��� ����� �� ��ȿ�� ���� �ƴ� ��                                
    AXT_ERROR_CONTI_INVALID_MAP_NO      = 4166;         // ���Ӻ��� ���� �� ��ȿ�� ���� ��ȣ�� �ƴ� ��                           
    AXT_ERROR_CONTI_EMPTY_MAP_NO        = 4167;         // ���Ӻ��� ���� ��ȣ�� ��� ���� ��                                     
    AXT_RT_MOTION_ERROR_CACULATION      = 4168;         // ������ ������ �߻����� ��        
    AXT_RT_ERROR_MOVE_SENSOR_CHECK      = 4169;         // ���Ӻ��� ������ ����������(Alarm, EMG, Limit��) �����Ȱ��

    AXT_ERROR_HELICAL_INVALID_AXIS_NO   = 4170;         // �︮�� �� ���� �� ��ȿ�� ���� �ƴ� ��                                 
    AXT_ERROR_HELICAL_INVALID_MAP_NO    = 4171;         // �︮�� ���� �� ��ȿ�� ���� ��ȣ�� �ƴ�  ��                            
    AXT_ERROR_HELICAL_EMPTY_MAP_NO      = 4172;         // �︮�� ���� ��ȣ�� ��� ���� ��    

    AXT_ERROR_SPLINE_INVALID_AXIS_NO    = 4180;         // ���ö��� �� ���� �� ��ȿ�� ���� �ƴ� ��         
    AXT_ERROR_SPLINE_INVALID_MAP_NO     = 4181;         // ���ö��� ���� �� ��ȿ�� ���� ��ȣ�� �ƴ� ��     
    AXT_ERROR_SPLINE_EMPTY_MAP_NO       = 4182;         // ���ö��� ���� ��ȣ�� ������� ��                
    AXT_ERROR_SPLINE_NUM_ERROR          = 4183;         // ���ö��� �����ڰ� �������� ��                   
    AXT_RT_MOTION_INTERPOL_VALUE        = 4184;         // ������ �� �Է� ���� �߸��־����� ��             
    AXT_RT_ERROR_NOT_CONTIBEGIN         = 4185;         // ���Ӻ��� �� �� CONTIBEGIN�Լ��� ȣ������ ���� ��
    AXT_RT_ERROR_NOT_CONTIEND           = 4186;         // ���Ӻ��� �� �� CONTIEND�Լ��� ȣ������ ���� ��  
    
    AXT_RT_MOTION_HOME_SEARCHING        = 4201;         // Ȩ�� ã�� �ִ� ���� �� �ٸ� ��� �Լ����� ����� ��                            
    AXT_RT_MOTION_HOME_ERROR_SEARCHING  = 4202;         // Ȩ�� ã�� �ִ� ���� �� �ܺο��� ����ڳ� Ȥ�� ��Ϳ� ����  ������ �������� ��
    AXT_RT_MOTION_HOME_ERROR_START      = 4203;         // �ʱ�ȭ ������ Ȩ���� �Ұ��� ��                                                 
    AXT_RT_MOTION_HOME_ERROR_GANTRY     = 4204;         // Ȩ�� ã�� �ִ� ���� �� ��Ʈ�� enable �Ұ��� ��                                 

    AXT_RT_MOTION_READ_ALARM_WAITING    = 4210;         // ���������κ��� �˶��ڵ� ����� ��ٸ��� ��     
    AXT_RT_MOTION_READ_ALARM_NO_REQUEST = 4211;         // �����ѿ� �˶��ڵ� ��ȯ ����� ���������ʾ��� ��
    AXT_RT_MOTION_READ_ALARM_TIMEOUT    = 4212;         // ������ �˶��б� �ð��ʰ� ������(1sec�̻�)      
    AXT_RT_MOTION_READ_ALARM_FAILED     = 4213;         // ������ �˶��б⿡ ���� ���� ��                 
    AXT_RT_MOTION_READ_ALARM_UNKNOWN    = 4220;         // �˶��ڵ尡 �˼����� �ڵ��� ��                  
    AXT_RT_MOTION_READ_ALARM_FILES      = 4221;         // �˶����� ������ ��������ġ�� �������� ���� ��  
    AXT_RT_MOTION_READ_ALARM_NOT_DETECTED      = 4222;         // �˶��ڵ� Read ��; �˶��� �߻����� �ʾ��� ��
    AXT_RT_MOTION_POSITION_OUTOFBOUND   = 4251;         // ������ ��ġ���� ���� �ִ밪���� ũ�ų� �ּҰ����� ��������                     
    AXT_RT_MOTION_PROFILE_INVALID       = 4252;         // ���� �ӵ� �������� ������ �߸���                                               
    AXT_RT_MOTION_VELOCITY_OUTOFBOUND   = 4253;         // ���� �ӵ����� �ִ밪���� ũ�� ������                                           
    AXT_RT_MOTION_MOVE_UNIT_IS_ZERO     = 4254;         // ���� �������� 0���� ������                                                     
    AXT_RT_MOTION_SETTING_ERROR         = 4255;         // �ӵ�, ���ӵ�, ��ũ, �������� ������ �߸���                                     
    AXT_RT_MOTION_IN_CONT_INTERPOL      = 4256;         // ���� ���� ���� �� ���� ���� �Ǵ� ����� �Լ��� �����Ͽ���                      
    AXT_RT_MOTION_DISABLE_TRIGGER       = 4257;         // Ʈ���� ����� Disable ������                                                   
    AXT_RT_MOTION_INVALID_CONT_INDEX    = 4258;         // ���� ���� Index�� ������ �߸���                                                
    AXT_RT_MOTION_CONT_QUEUE_FULL       = 4259;         // ��� Ĩ�� ���� ���� ť�� Full ������                                           
    AXT_RT_PROTECTED_DURING_SERVOON     = 4260;         // ���� �� �Ǿ� �ִ� ���¿��� ��� �� ��                                          
    AXT_RT_HW_ACCESS_ERROR              = 4261;         // �޸� Read / Write ����

    AXT_RT_HW_DPRAM_CMD_WRITE_ERROR_LV1 = 4262;         // DPRAM Comamnd Write ���� Level1
    AXT_RT_HW_DPRAM_CMD_WRITE_ERROR_LV2 = 4263;         // DPRAM Comamnd Write ���� Level2
    AXT_RT_HW_DPRAM_CMD_WRITE_ERROR_LV3 = 4264;         // DPRAM Comamnd Write ���� Level3
    AXT_RT_HW_DPRAM_CMD_READ_ERROR_LV1  = 4265;         // DPRAM Comamnd Read ���� Level1
    AXT_RT_HW_DPRAM_CMD_READ_ERROR_LV2  = 4266;         // DPRAM Comamnd Read ���� Level2
    AXT_RT_HW_DPRAM_CMD_READ_ERROR_LV3  = 4267;         // DPRAM Comamnd Read ���� Level3

    AXT_RT_COMPENSATION_SET_PARAM_FIRST     = 4300;
    AXT_RT_COMPENSATION_NOT_INIT            = 4301;     // �������̺� ��� �ʱ�ȭ ��������
    AXT_RT_COMPENSATION_POS_OUTOFBOUND      = 4302;     // ��ġ ���� �������� �������� ����
    AXT_RT_COMPENSATION_BACKLASH_NOT_INIT   = 4303;     // �鷡�� ������� �ʱ�ȭ ��������
    AXT_RT_COMPENSATION_INVALID_ENTRY       = 4304;     //
        
    AXT_RT_SEQ_NOT_IN_SERVICE           = 4400;          // ���� ���� �Լ� ���� �� �ڿ� �Ҵ� ����
    AXT_ERROR_SEQ_INVALID_MAP_NO        = 4401;          // ���� ���� �Լ� ���� �� ���� ��ȣ �̻�.
    AXT_ERROR_INVALID_AXIS_NO           = 4402;          // �Լ� ���� ������ ���ȣ �̻�.
    AXT_RT_ERROR_NOT_SEQ_NODE_BEGIN     = 4403;          // ���� ���� ��� �Է� ���� �Լ��� ȣ������ ����.
    AXT_RT_ERROR_NOT_SEQ_NODE_END       = 4404;          // ���� ���� ��� �Է� ���� �Լ��� ȣ������ ����.
    AXT_RT_ERROR_NO_NODE                = 4405;          // ���� ���� ��� �Է��� ����.
    AXT_RT_ERROR_SEQ_STOP_TIMEOUT       = 4406;
    
    AXT_RT_M3_COMMUNICATION_FAILED             = 4500;   // ML3 ��� ����, ��� ����
    AXT_RT_MOTION_ONE_OF_AXES_IS_NOT_M3        = 4501;   // ML3 ��� ����, ������ ML3 ��� �߿��� ��� ��� ���� 
    AXT_RT_MOTION_BIGGER_VEL_THEN_MAX_VEL      = 4502;   // ML3 ��� ����, ������ ���� ������ �ִ� �ӵ����� ŭ
    AXT_RT_MOTION_SMALLER_VEL_THEN_MAX_VEL     = 4503;   // ML3 ��� ����, ������ ���� ������ �ִ� �ӵ����� ����
    AXT_RT_MOTION_ACCEL_MUST_BIGGER_THEN_ZERO  = 4504;   // ML3 ��� ����, ������ ���� ������ ���ӵ��� 0���� ŭ
    AXT_RT_MOTION_SMALL_ACCEL_WITH_UNIT_PULSE  = 4505;   // ML3 ��� ����, UnitPulse�� ����� ���ӵ��� 0���� ŭ
    AXT_RT_MOTION_INVALID_INPUT_ACCEL          = 4506;   // ML3 ��� ����, ������ ���� ���ӵ� �Է��� �߸���
    AXT_RT_MOTION_SMALL_DECEL_WITH_UNIT_PULSE  = 4507;   // ML3 ��� ����, UnitPulse�� ����� ���ӵ��� 0���� ŭ
    AXT_RT_MOTION_INVALID_INPUT_DECEL          = 4508;   // ML3 ��� ����, ������ ���� ���ӵ� �Է��� �߸���
    AXT_RT_MOTION_SAME_START_AND_CENTER_POS    = 4509;   // ML3 ��� ����, ��ȣ������ �������� �߽����� ����
    AXT_RT_MOTION_INVALID_JERK                 = 4510;   // ML3 ��� ����, ������ ���� ��ũ �Է��� �߸���
    AXT_RT_MOTION_INVALID_INPUT_VALUE          = 4511;   // ML3 ��� ����, ������ ���� �Է°��� �߸���
    AXT_RT_MOTION_NOT_SUPPORT_PROFILE          = 4512;   // ML3 ��� ����, �������� �ʴ� �ӵ� ����������
    AXT_RT_MOTION_INPOS_UNUSED                 = 4513;   // ML3 ��� ����, �������� ������� ����
    AXT_RT_MOTION_AXIS_IN_SLAVE_STATE          = 4514;   // ML3 ��� ����, ������ ���� �����̺� ���°� �ƴ�
    AXT_RT_MOTION_AXES_ARE_NOT_SAME_BOARD      = 4515;   // ML3 ��� ����, ������ ����� ���� ���� ���� ���� ����
    AXT_RT_MOTION_ERROR_IN_ALARM               = 4516;   // ML3 ��� ����, ������ ���� �˶� ������
    AXT_RT_MOTION_ERROR_IN_EMGN                = 4517;   // ML3 ��� ����, ������ ���� ������� ������
    AXT_RT_MOTION_CAN_NOT_CHANGE_COORD_NO      = 4518;   // ML3 ��� ����, �ڵ������ �ѹ� ��ȯ �Ұ���
    AXT_RT_MOTION_INVALID_INTERNAL_RADIOUS     = 4519;   // ML3 ��� ����, ��ȣ������ X, Y�� ������ ����ġ
    AXT_RT_MOTION_CONTI_QUEUE_FULL             = 4521;   // ML3 ��� ����, ������ ť�� ���� ��
    AXT_RT_MOTION_SAME_START_AND_END_POSITION  = 4522;   // ML3 ��� ����, ��ȣ������ �������� �������� ����
    AXT_RT_MOTION_INVALID_ANGLE                = 4523;   // ML3 ��� ����, ��ȣ������ ������ 360�� �ʰ���
    AXT_RT_MOTION_CONTI_QUEUE_EMPTY            = 4524;   // ML3 ��� ����, ������ ť�� �������
    AXT_RT_MOTION_ERROR_GEAR_ENABLE            = 4525;   // ML3 ��� ����, ������ ���� �̹� ��ũ ���� ������
    AXT_RT_MOTION_ERROR_GEAR_AXIS              = 4526;   // ML3 ��� ����, ������ ���� ��ũ���� �ƴ�
    AXT_RT_MOTION_ERROR_NO_GANTRY_ENABLE       = 4527;   // ML3 ��� ����, ������ ���� ��Ʈ�� ���� ���°� �ƴ�
    AXT_RT_MOTION_ERROR_NO_GEAR_ENABLE         = 4528;   // ML3 ��� ����, ������ ���� ��ũ ���� ���°� �ƴ�
    AXT_RT_MOTION_ERROR_GANTRY_ENABLE_FULL     = 4529;   // ML3 ��� ����, ��Ʈ�� ���� ������
    AXT_RT_MOTION_ERROR_GEAR_ENABLE_FULL       = 4530;   // ML3 ��� ����, ��ũ ���� ������
    AXT_RT_MOTION_ERROR_NO_GANTRY_SLAVE        = 4531;   // ML3 ��� ����, ������ ���� ��Ʈ�� �����̺� �������°� �ƴ�
    AXT_RT_MOTION_ERROR_NO_GEAR_SLAVE          = 4532;   // ML3 ��� ����, ������ ���� ��ũ �����̺� �������°� �ƴ�
    AXT_RT_MOTION_ERROR_MASTER_SLAVE_SAME      = 4533;   // ML3 ��� ����, ��������� �����̺� ���� ������
    AXT_RT_MOTION_NOT_SUPPORT_HOMESIGNAL       = 4534;   // ML3 ��� ����, ������ ���� Ȩ��ȣ�� �������� ����
    AXT_RT_MOTION_ERROR_NOT_SYNC_CONNECT       = 4535;   // ML3 ��� ����, ������ ���� ��ũ ���� ���°� �ƴ�
    AXT_RT_MOTION_OVERFLOW_POSITION            = 4536;   // ML3 ��� ����, ������ �࿡ ���� ���� ��ġ���� �����÷ο���
    AXT_RT_MOTION_ERROR_INVALID_CONTIMAPAXIS   = 4537;   // ML3 ��� ����, �����۾��� ���� ������ ��ǥ�� ������� ����
    AXT_RT_MOTION_ERROR_INVALID_CONTIMAPSIZE   = 4538;   // ML3 ��� ����, �����۾��� ������ ������ ��ǥ�� ����� ������ �߸���
    AXT_RT_MOTION_ERROR_IN_SERVO_OFF           = 4539;   // ML3 ��� ����, ������ ���� ���� OFF�Ǿ� ����
    AXT_RT_MOTION_ERROR_POSITIVE_LIMIT         = 4540;   // ML3 ��� ����, ������ ���� (+)���� ON�Ǿ� ����
    AXT_RT_MOTION_ERROR_NEGATIVE_LIMIT         = 4541;   // ML3 ��� ����, ������ ���� (-)���� ON�Ǿ� ����
    AXT_RT_MOTION_ERROR_OVERFLOW_SWPROFILE_NUM = 4542;   // ML3 ��� ����, ������ ��鿡 ���� ���� �������� ������ �����÷ο��
    AXT_RT_PROTECTED_DURING_INMOTION           = 4543;   // in_motion �Ǿ� �ִ� ���¿��� ��� �� ��


    AXT_RT_DATA_FLASH_NOT_EXIST                = 5000;
    AXT_RT_DATA_FLASH_BUSY                     = 5001;

    { �α׷��� ����                     }
    LEVEL_NONE                          = 0;
    LEVEL_ERROR                         = 1;
    LEVEL_RUNSTOP                       = 2;
    LEVEL_FUNCTION                      = 3;
    { �����ǰ �� ���� ����               }
    STATUS_NOTEXIST                     = 0;
    STATUS_EXIST                        = 1;
    { ��� ���� ����                    }
    DISABLE                             = 0;
    ENABLE                              = 1;
    { AI��ǰ Ʈ���� �������            }
    DISABLE_MODE                        = 0;
    NORMAL_MODE                         = 1;
    TIMER_MODE                          = 2;
    EXTERNAL_MODE                       = 3;
    { AI��ǰ ����Ÿť ����� ����     }
    NEW_DATA_KEEP                       = 0;
    CURR_DATA_KEEP                      = 1;
    { AI��ǰ ����Ÿť ���� ����         }
    DATA_EMPTY                          = $01;
    DATA_MANY                           = $02;
    DATA_SMALL                          = $04;
    DATA_FULL                           = $08;
    { AI(16H)��ǰ ����Ÿť ���� ����    }
    ADC_DONE                            = $00;
    SCAN_END                            = $01;
    FIFO_HALF_FULL                      = $02;
    NO_SIGNAL                           = $03;
    { AI��ǰ ���ͷ�Ʈ ���� ����         } 
    AIO_EVENT_DATA_RESET                = $00;
    AIO_EVENT_DATA_UPPER                = $1;
    AIO_EVENT_DATA_LOWER                = $2;
    AIO_EVENT_DATA_FULL                 = $3;
    AIO_EVENT_DATA_EMPTY                = $4;
    { AI Module H/W FIFO ���� ����      }   
    FIFO_DATA_EXIST                     = 0;
    FIFO_DATA_EMPTY                     = 1;
    FIFO_DATA_HALF                      = 2;
    FIFO_DATA_FULL                      = 6;
    { AI Module Conversion ��������     }   
    EXTERNAL_DATA_DONE                  = 0;
    EXTERNAL_DATA_FINE                  = 1;
    EXTERNAL_DATA_HALF                  = 2;
    EXTERNAL_DATA_FULL                  = 3;
    EXTERNAL_COMPLETE                   = 4;
    { DI��ǰ �Է� ���� ����             }
    DOWN_EDGE                           = 0;
    UP_EDGE                             = 1;
    { DIO��ǰ ���� ���� ����            }
    OFF_STATE                           = 0;
    ON_STATE                            = 1;
    { �����ǰ ���� ��� ����           }
    EMERGENCY_STOP                      = 0;
    SLOWDOWN_STOP                       = 1;
    { �����ǰ ��ȣ ���� ����           }
    SIGNAL_DOWN_EDGE                    = 0;
    SIGNAL_UP_EDGE                      = 1;
    SIGNAL_LOW_LEVEL                    = 2;
    SIGNAL_HIGH_LEVEL                   = 3;
    { �����ǰ ī��Ʈ ���� ����         }
    COMMAND                             = 0;
    ACTUAL                              = 1;
    { �����ǰ Ʈ���� ��� ����         }
    PERIOD_MODE                         = 0;
    ABS_POS_MODE                        = 1;
    { �����ǰ �Է½�ȣ ���� ����       }
    LOW                                 = 0;
    HIGH                                = 1;
    UNUSED                              = 2;
    USED                                = 3;
    { �����ǰ ���� ��ǥ�� ����         }
    POS_ABS_MODE                        = 0;
    POS_REL_MODE                        = 1;	
    POS_ABS_LONG_MODE                   = 2;

    { ���ڴ� ���� ����       }
	ENCODER_TYPE_INCREMENTAL            = 0;
    ENCODER_TYPE_ABSOLUTE               = 1;	
    ENCODER_TYPE_NONE                   = 2;

    { �����ǰ ���� �������� ����       }
    SYM_TRAPEZOIDE_MODE                 = 0;
    ASYM_TRAPEZOIDE_MODE                = 1;
    QUASI_S_CURVE_MODE                  = 2;
    SYM_S_CURVE_MODE                    = 3;
    ASYM_S_CURVE_MODE                   = 4;
	SYM_TRAP_M3_SW_MODE                 = 5;  //ML-3 Only, Support Velocity profile
	ASYM_TRAP_M3_SW_MODE                = 6;  //ML-3 Only, Support Velocity profile
	SYM_S_M3_SW_MODE                    = 7;  //ML-3 Only, Support Velocity profile
	ASYM_S_M3_SW_MODE                   = 8;  //ML-3 Only, Support Velocity profile
    { �����ǰ ��ȣ ���� ����           }
    INACTIVE                            = 0;
    ACTIVE                              = 1;
    { �����ǰ �����˻� ��� ����       }
    HOME_RESERVED                       = $00;          // ML3
    HOME_SUCCESS                        = $01;          // ���� �˻� �Ϸ� 
    HOME_SEARCHING                      = $02;	        // ���� �˻� ��
    HOME_ERR_GNT_RANGE                  = $10;          // ��Ʈ�� ���� �˻� ����, �� �� ������ �����̻� ���� �߻�
    HOME_ERR_USER_BREAK                 = $11;          // ���� �˻� ����� ������
    HOME_ERR_VELOCITY                   = $12;          // ���� �˻� �ӵ� �̻� ���� �߻�
    HOME_ERR_AMP_FAULT                  = $13;          // ������ �˶� �߻� ����                  
    HOME_ERR_NEG_LIMIT                  = $14;          // (-)���� ������ (+)����Ʈ ���� ���� ����
    HOME_ERR_POS_LIMIT                  = $15;          // (+)���� ������ (-)����Ʈ ���� ���� ����
    HOME_ERR_NOT_DETECT                 = $16;          // ������ ��ȣ �������� �� �� ��� ����
    HOME_ERR_SETTING                    = $17;          // ����� ���� �Ķ���Ͱ� ������ ���� ���� �߻���
	HOME_ERR_SERVO_OFF                  = $18;          // ���� Off�ϰ��
    HOME_ERR_TIMEOUT                    = $20;          // ������ �ð� �ʰ� �߻����� ���� �߻� 
    HOME_ERR_FUNCALL                    = $30;          // �Լ� ȣ�� ����
    HOME_ERR_COUPLING                   = $40;          // Gantry Master to Slave Over Distance protection
    HOME_ERR_UNKNOWN                    = $FF;          // ������ ����
    { �����ǰ �Է����� ����            }
    UIO_INP0                            = 0;
    UIO_INP1                            = 1;
    UIO_INP2                            = 2;
    UIO_INP3                            = 3;
    UIO_INP4                            = 4;
    UIO_INP5                            = 5;
    { �����ǰ ������� ����            }
    UIO_OUT0                            = 0;
    UIO_OUT1                            = 1;
    UIO_OUT2                            = 2;
    UIO_OUT3                            = 3;
    UIO_OUT4                            = 4;
    UIO_OUT5                            = 5;
    { �����ǰ ������ ��� ����         }
    AutoDetect                          = 0;
    RestPulse                           = 1;
    { �����ǰ �޽� ��¹�� ����       }
    OneHighLowHigh                      = $0;           // 1�޽� ���; PULSE(Active High), ������(DIR=Low)  / ������(DIR=High)    
    OneHighHighLow                      = $1;           // 1�޽� ���, PULSE(Active High), ������(DIR=High) / ������(DIR=Low)     
    OneLowLowHigh                       = $2;           // 1�޽� ���, PULSE(Active Low),  ������(DIR=Low)  / ������(DIR=High)    
    OneLowHighLow                       = $3;           // 1�޽� ���, PULSE(Active Low),  ������(DIR=High) / ������(DIR=Low)     
    TwoCcwCwHigh                        = $4;           // 2�޽� ���, PULSE(CCW:������),  DIR(CW:������),  Active High           
    TwoCcwCwLow                         = $5;           // 2�޽� ���, PULSE(CCW:������),  DIR(CW:������),  Active Low            
    TwoCwCcwHigh                        = $6;           // 2�޽� ���, PULSE(CW:������),   DIR(CCW:������), Active High           
    TwoCwCcwLow                         = $7;           // 2�޽� ���, PULSE(CW:������),   DIR(CCW:������), Active Low            
    TwoPhase                            = $8;           // 2��(90' ������),  PULSE lead DIR(CW: ������), PULSE lag DIR(CCW:������)
    TwoPhaseReverse                     = $9;           // 2��(90' ������),  PULSE lead DIR(CCW: ������), PULSE lag DIR(CW:������)
    { �����ǰ ���ڴ� �Է¹�� ����     }
    ObverseUpDownMode                   = $0;           // ������ Up/Down 
    ObverseSqr1Mode                     = $1;           // ������ 1ü��   
    ObverseSqr2Mode                     = $2;           // ������ 2ü��   
    ObverseSqr4Mode                     = $3;           // ������ 4ü��   
    ReverseUpDownMode                   = $4;           // ������ Up/Down 
    ReverseSqr1Mode                     = $5;           // ������ 1ü��   
    ReverseSqr2Mode                     = $6;           // ������ 2ü��   
    ReverseSqr4Mode                     = $7;           // ������ 4ü��   
    { �����ǰ ������ ���� ����         }
    UNIT_SEC2                           = $0;           // unit/sec2
    SEC                                 = $1;           // sec
    { �����ǰ �������� ����            }
    DIR_CCW                             = $0;           // �ݽð����
    DIR_CW                              = $1;           // �ð����  
    { �����ǰ ��ȣ���� ��� ����       }
    SHORT_DISTANCE                      = $0;           // ª�� �Ÿ��� ��ȣ �̵�
    LONG_DISTANCE                       = $1;           // �� �Ÿ��� ��ȣ �̵�  
    { ��ġī��Ʈ ��� ����              }
    POSITION_LIMIT                      = $0;           // ��ü �������
    POSITION_BOUND                      = $1;           // Pos ���� ���
    { �����ǰ ���� ����� ����         }
    INTERPOLATION_AXIS2                 = $0;           // 2���� �������� ����� ��
    INTERPOLATION_AXIS3                 = $1;           // 3���� �������� ����� ��
    INTERPOLATION_AXIS4                 = $2;           // 4���� �������� ����� ��
    { �����ǰ ���Ӻ��� ��� ����       }
    CONTI_NODE_VELOCITY                 = $0;           // �ӵ� ���� ���� ���  
    CONTI_NODE_MANUAL                   = $1;           // ��� ������ ���� ���
    CONTI_NODE_AUTO                     = $2;           // �ڵ� ������ ���� ���
    { �����ǰ �����ȣ ����            }
    PosEndLimit                         = $0;           // +Elm(End limit) +���� ����Ʈ ���� ��ȣ
    NegEndLimit                         = $1;           // -Elm(End limit) -���� ����Ʈ ���� ��ȣ
    PosSloLimit                         = $2;           // +Slm(Slow Down limit) ��ȣ - ������� ����
    NegSloLimit                         = $3;           // -Slm(Slow Down limit) ��ȣ - ������� ����
    HomeSensor                          = $4;           // IN0(ORG)  ���� ���� ��ȣ
    EncodZPhase                         = $5;           // IN1(Z��)  Encoder Z�� ��ȣ
    UniInput02                          = $6;           // IN2(����) ���� �Է� 2�� ��ȣ
    UniInput03                          = $7;           // IN3(����) ���� �Է� 3�� ��ȣ
    UniInput04                          = $8;           // IN4(����) ���� �Է� 4�� ��ȣ
    UniInput05                          = $9;           // IN5(����) ���� �Է� 5�� ��ȣ
    { �����ǰ �������� �Է����� ����   }
    END_LIMIT                           = $10;          // +Elm(End limit) +���� ����Ʈ ���� ��ȣ
    INP_ALARM                           = $11;          // -Elm(End limit) -���� ����Ʈ ���� ��ȣ
    UIN_00_01                           = $12;          // +Slm(Slow Down limit) ��ȣ - ������� ����
    UIN_02_04                           = $13;          // -Slm(Slow Down limit) ��ȣ - ������� ����
    { �����ǰ MPG ��ȣ �Է¹�� ����   }
    MPG_DIFF_ONE_PHASE                  = $0;           // MPG �Է� ��� One Phase       
    MPG_DIFF_TWO_PHASE_1X               = $1;           // MPG �Է� ��� TwoPhase1       
    MPG_DIFF_TWO_PHASE_2X               = $2;           // MPG �Է� ��� TwoPhase2       
    MPG_DIFF_TWO_PHASE_4X               = $3;           // MPG �Է� ��� TwoPhase4       
    MPG_LEVEL_ONE_PHASE                 = $4;           // MPG �Է� ��� Level One Phase 
    MPG_LEVEL_TWO_PHASE_1X              = $5;           // MPG �Է� ��� Level Two Phase1
    MPG_LEVEL_TWO_PHASE_2X              = $6;           // MPG �Է� ��� Level Two Phase2
    MPG_LEVEL_TWO_PHASE_4X              = $7;           // MPG �Է� ��� Level Two Phase4
    { �����ǰ �������� ������� ����   }
    SENSOR_METHOD1                      = $0;           // �Ϲ� ����                                            
    SENSOR_METHOD2                      = $1;           // ���� ��ȣ ���� ���� ���� ����. ��ȣ ���� �� �Ϲ� ����
    SENSOR_METHOD3                      = $2;           // ���� ����                                            
    { �����ǰ �ܿ��޽� ���� ��� ����  }
    CRC_SELECT1                         = $0;           // ��ġŬ���� ������, �ܿ��޽� Ŭ���� ��� ����
    CRC_SELECT2                         = $1;           // ��ġŬ���� �����, �ܿ��޽� Ŭ���� ��� ����  
    CRC_SELECT3                         = $2;           // ��ġŬ���� ������, �ܿ��޽� Ŭ���� �����   
    CRC_SELECT4                         = $3;           // ��ġŬ���� �����, �ܿ��޽� Ŭ���� �����     
    { �����ǰ(IP) ��ȣ���� ���� ����   }
    PElmNegativeEdge                    = $0;           // +Elm(End limit) �ϰ� edge     
    NElmNegativeEdge                    = $1;           // -Elm(End limit) �ϰ� edge     
    PSlmNegativeEdge                    = $2;           // +Slm(Slowdown limit) �ϰ� edge
    NSlmNegativeEdge                    = $3;           // -Slm(Slowdown limit) �ϰ� edge
    In0DownEdge                         = $4;           // IN0(ORG) �ϰ� edge            
    In1DownEdge                         = $5;           // IN1(Z��) �ϰ� edge            
    In2DownEdge                         = $6;           // IN2(����) �ϰ� edge           
    In3DownEdge                         = $7;           // IN3(����) �ϰ� edge           
    PElmPositiveEdge                    = $8;           // +Elm(End limit) ��� edge     
    NElmPositiveEdge                    = $9;           // -Elm(End limit) ��� edge     
    PSlmPositiveEdge                    = $a;           // +Slm(Slowdown limit) ��� edge
    NSlmPositiveEdge                    = $b;           // -Slm(Slowdown limit) ��� edge
    In0UpEdge                           = $c;           // IN0(ORG) ��� edge            
    In1UpEdge                           = $d;           // IN1(Z��) ��� edge            
    In2UpEdge                           = $e;           // IN2(����) ��� edge           
    In3UpEdge                           = $f;           // IN3(����) ��� edge           
    { �����ǰ(IP) �������� ���� ����   }               // When 0x0000 after normal drive end.
    IPEND_STATUS_SLM                    = $0001;        // Bit 0, limit �������� ��ȣ �Է¿� ���� ����                
    IPEND_STATUS_ELM                    = $0002;        // Bit 1, limit ������ ��ȣ �Է¿� ���� ����                  
    IPEND_STATUS_SSTOP_SIGNAL           = $0004;        // Bit 2, ���� ���� ��ȣ �Է¿� ���� ����                     
    IPEND_STATUS_ESTOP_SIGANL           = $0008;        // Bit 3, ������ ��ȣ �Է¿� ���� ����                        
    IPEND_STATUS_SSTOP_COMMAND          = $0010;        // Bit 4, ���� ���� ��ɿ� ���� ����                          
    IPEND_STATUS_ESTOP_COMMAND          = $0020;        // Bit 5, ������ ���� ��ɿ� ���� ����                        
    IPEND_STATUS_ALARM_SIGNAL           = $0040;        // Bit 6, Alarm ��ȣ �Է¿� ���� ����                         
    IPEND_STATUS_DATA_ERROR             = $0080;        // Bit 7, ������ ���� ������ ���� ����                        
    IPEND_STATUS_DEVIATION_ERROR        = $0100;        // Bit 8, Ż�� ������ ���� ����                               
    IPEND_STATUS_ORIGIN_DETECT          = $0200;        // Bit 9, ���� ���⿡ ���� ����                               
    IPEND_STATUS_SIGNAL_DETECT          = $0400;        // Bit 10, ��ȣ ���⿡ ���� ����(Signal search-1/2 drive ����)
    IPEND_STATUS_PRESET_PULSE_DRIVE     = $0800;        // Bit 11, Preset pulse drive ����                            
    IPEND_STATUS_SENSOR_PULSE_DRIVE     = $1000;        // Bit 12, Sensor pulse drive ����                            
    IPEND_STATUS_LIMIT                  = $2000;        // Bit 13, Limit ���������� ���� ����                         
    IPEND_STATUS_SOFTLIMIT              = $4000;        // Bit 14, Soft limit�� ���� ����                             
    IPEND_STATUS_INTERPOLATION_DRIVE    = $8000;        // Bit 15, Soft limit�� ���� ����                             
    { �����ǰ(IP) �������� ����        }
    IPDRIVE_STATUS_BUSY                 = $00001;       // Bit 0, BUSY(����̺� ���� ��)                         
    IPDRIVE_STATUS_DOWN                 = $00002;       // Bit 1, DOWN(���� ��)                                  
    IPDRIVE_STATUS_CONST                = $00004;       // Bit 2, CONST(��� ��)                                 
    IPDRIVE_STATUS_UP                   = $00008;       // Bit 3, UP(���� ��)                                    
    IPDRIVE_STATUS_ICL                  = $00010;       // Bit 4, ICL(���� ��ġ ī���� < ���� ��ġ ī���� �񱳰�)
    IPDRIVE_STATUS_ICG                  = $00020;       // Bit 5, ICG(���� ��ġ ī���� > ���� ��ġ ī���� �񱳰�)
    IPDRIVE_STATUS_ECL                  = $00040;       // Bit 6, ECL(�ܺ� ��ġ ī���� < �ܺ� ��ġ ī���� �񱳰�)
    IPDRIVE_STATUS_ECG                  = $00080;       // Bit 7, ECG(�ܺ� ��ġ ī���� > �ܺ� ��ġ ī���� �񱳰�)
    IPDRIVE_STATUS_DRIVE_DIRECTION      = $00100;       // Bit 8, ����̺� ���� ��ȣ(0=CW/1=CCW)                 
    IPDRIVE_STATUS_COMMAND_BUSY         = $00200;       // Bit 9, ��ɾ� ������                                  
    IPDRIVE_STATUS_PRESET_DRIVING       = $00400;       // Bit 10, Preset pulse drive ��                         
    IPDRIVE_STATUS_CONTINUOUS_DRIVING   = $00800;       // Bit 11, Continuouse speed drive ��                    
    IPDRIVE_STATUS_SIGNAL_SEARCH_DRIVING= $01000;       // Bit 12, Signal search-1/2 drive ��                    
    IPDRIVE_STATUS_ORG_SEARCH_DRIVING   = $02000;       // Bit 13, ���� ���� drive ��                            
    IPDRIVE_STATUS_MPG_DRIVING          = $04000;       // Bit 14, MPG drive ��                                  
    IPDRIVE_STATUS_SENSOR_DRIVING       = $08000;       // Bit 15, Sensor positioning drive ��                   
    IPDRIVE_STATUS_L_C_INTERPOLATION    = $10000;       // Bit 16, ����/��ȣ ���� ��                             
    IPDRIVE_STATUS_PATTERN_INTERPOLATION= $20000;       // Bit 17, ��Ʈ ���� ���� ��                             
    IPDRIVE_STATUS_INTERRUPT_BANK1      = $40000;       // Bit 18, ���ͷ�Ʈ bank1���� �߻�                       
    IPDRIVE_STATUS_INTERRUPT_BANK2      = $80000;       // Bit 19, ���ͷ�Ʈ bank2���� �߻�                       
    { �����ǰ(IP) ���ͷ�Ʈ ����        }
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
    { �����ǰ(IP) ��ȣ���� ���� ����   }
    IPMECHANICAL_PELM_LEVEL             = $0001;        // Bit 0, +Limit ������ ��ȣ�� ��Ƽ�� ��  
    IPMECHANICAL_NELM_LEVEL             = $0002;        // Bit 1, -Limit ������ ��ȣ ��Ƽ�� ��    
    IPMECHANICAL_PSLM_LEVEL             = $0004;        // Bit 2, +limit �������� ��ȣ ��Ƽ�� ��  
    IPMECHANICAL_NSLM_LEVEL             = $0008;        // Bit 3, -limit �������� ��ȣ ��Ƽ�� ��  
    IPMECHANICAL_ALARM_LEVEL            = $0010;        // Bit 4, Alarm ��ȣ ��Ƽ�� ��            
    IPMECHANICAL_INP_LEVEL              = $0020;        // Bit 5, Inposition ��ȣ ��Ƽ�� ��       
    IPMECHANICAL_ENC_DOWN_LEVEL         = $0040;        // Bit 6, ���ڴ� DOWN(B��) ��ȣ �Է� Level
    IPMECHANICAL_ENC_UP_LEVEL           = $0080;        // Bit 7, ���ڴ� UP(A��) ��ȣ �Է� Level  
    IPMECHANICAL_EXMP_LEVEL             = $0100;        // Bit 8, EXMP ��ȣ �Է� Level            
    IPMECHANICAL_EXPP_LEVEL             = $0200;        // Bit 9, EXPP ��ȣ �Է� Level            
    IPMECHANICAL_MARK_LEVEL             = $0400;        // Bit 10, MARK# ��ȣ ��Ƽ�� ��           
    IPMECHANICAL_SSTOP_LEVEL            = $0800;        // Bit 11, SSTOP ��ȣ ��Ƽ�� ��           
    IPMECHANICAL_ESTOP_LEVEL            = $1000;        // Bit 12, ESTOP ��ȣ ��Ƽ�� ��           
    IPMECHANICAL_SYNC_LEVEL             = $2000;        // Bit 13, SYNC ��ȣ �Է� Level           
    IPMECHANICAL_MODE8_16_LEVEL         = $4000;        // Bit 14, MODE8_16 ��ȣ �Է� Level       
    { �����ǰ(QI) ��ȣ���� ���� ����   }
    Signal_PosEndLimit                  = $0;           // +Elm(End limit) +���� ����Ʈ ���� ��ȣ    
    Signal_NegEndLimit                  = $1;           // -Elm(End limit) -���� ����Ʈ ���� ��ȣ    
    Signal_PosSloLimit                  = $2;           // +Slm(Slow Down limit) ��ȣ - ������� ����
    Signal_NegSloLimit                  = $3;           // -Slm(Slow Down limit) ��ȣ - ������� ����
    Signal_HomeSensor                   = $4;           // IN0(ORG)  ���� ���� ��ȣ                  
    Signal_EncodZPhase                  = $5;           // IN1(Z��)  Encoder Z�� ��ȣ                
    Signal_UniInput02                   = $6;           // IN2(����) ���� �Է� 2�� ��ȣ              
    Signal_UniInput03                   = $7;           // IN3(����) ���� �Է� 3�� ��ȣ              
    { �����ǰ(QI) ��ȣ���� ���� ����   }
    QIMECHANICAL_PELM_LEVEL             = $00001;       // Bit 0, +Limit ������ ��ȣ ���� ����    
    QIMECHANICAL_NELM_LEVEL             = $00002;       // Bit 1, -Limit ������ ��ȣ ���� ����    
    QIMECHANICAL_PSLM_LEVEL             = $00004;       // Bit 2, +limit �������� ���� ����.      
    QIMECHANICAL_NSLM_LEVEL             = $00008;       // Bit 3, -limit �������� ���� ����       
    QIMECHANICAL_ALARM_LEVEL            = $00010;       // Bit 4, Alarm ��ȣ ��ȣ ���� ����       
    QIMECHANICAL_INP_LEVEL              = $00020;       // Bit 5, Inposition ��ȣ ���� ����       
    QIMECHANICAL_ESTOP_LEVEL            = $00040;       // Bit 6, ��� ���� ��ȣ(ESTOP) ���� ����.
    QIMECHANICAL_ORG_LEVEL              = $00080;       // Bit 7, ���� ��ȣ ���� ����             
    QIMECHANICAL_ZPHASE_LEVEL           = $00100;       // Bit 8, Z �� �Է� ��ȣ ���� ����        
    QIMECHANICAL_ECUP_LEVEL             = $00200;       // Bit 9, ECUP �͹̳� ��ȣ ����.          
    QIMECHANICAL_ECDN_LEVEL             = $00400;       // Bit 10, ECDN �͹̳� ��ȣ ����.         
    QIMECHANICAL_EXPP_LEVEL             = $00800;       // Bit 11, EXPP �͹̳� ��ȣ ����          
    QIMECHANICAL_EXMP_LEVEL             = $01000;       // Bit 12, EXMP �͹̳� ��ȣ ����          
    QIMECHANICAL_SQSTR1_LEVEL           = $02000;       // Bit 13, SQSTR1 �͹̳� ��ȣ ����        
    QIMECHANICAL_SQSTR2_LEVEL           = $04000;       // Bit 14, SQSTR2 �͹̳� ��ȣ ����        
    QIMECHANICAL_SQSTP1_LEVEL           = $08000;       // Bit 15, SQSTP1 �͹̳� ��ȣ ����        
    QIMECHANICAL_SQSTP2_LEVEL           = $10000;       // Bit 16, SQSTP2 �͹̳� ��ȣ ����        
    QIMECHANICAL_MODE_LEVEL             = $20000;       // Bit 17, MODE �͹̳� ��ȣ ����.         
    {  �����ǰ(QI) �������� ���� ����  }               // When 0x0000 after normal drive end.
    QIEND_STATUS_0                      = $00000001;    // Bit 0, ������ ����Ʈ ��ȣ(PELM)�� ���� ����               
    QIEND_STATUS_1                      = $00000002;    // Bit 1, ������ ����Ʈ ��ȣ(NELM)�� ���� ����               
    QIEND_STATUS_2                      = $00000004;    // Bit 2, ������ �ΰ� ����Ʈ ��ȣ(PSLM)�� ���� ���� ����     
    QIEND_STATUS_3                      = $00000008;    // Bit 3, ������ �ΰ� ����Ʈ ��ȣ(NSLM)�� ���� ���� ����     
    QIEND_STATUS_4                      = $00000010;    // Bit 4, ������ ����Ʈ ����Ʈ ������ ��ɿ� ���� ���� ����  
    QIEND_STATUS_5                      = $00000020;    // Bit 5, ������ ����Ʈ ����Ʈ ������ ��ɿ� ���� ���� ����  
    QIEND_STATUS_6                      = $00000040;    // Bit 6, ������ ����Ʈ ����Ʈ �������� ��ɿ� ���� ���� ����
    QIEND_STATUS_7                      = $00000080;    // Bit 7, ������ ����Ʈ ����Ʈ �������� ��ɿ� ���� ���� ����
    QIEND_STATUS_8                      = $00000100;    // Bit 8, ���� �˶� ��ɿ� ���� ���� ����.                   
    QIEND_STATUS_9                      = $00000200;    // Bit 9, ��� ���� ��ȣ �Է¿� ���� ���� ����.              
    QIEND_STATUS_10                     = $00000400;    // Bit 10, �� ���� ��ɿ� ���� ���� ����.                    
    QIEND_STATUS_11                     = $00000800;    // Bit 11, ���� ���� ��ɿ� ���� ���� ����.                  
    QIEND_STATUS_12                     = $00001000;    // Bit 12, ���� ������ ��ɿ� ���� ���� ����                 
    QIEND_STATUS_13                     = $00002000;    // Bit 13, ���� ���� ��� #1(SQSTP1)�� ���� ���� ����.       
    QIEND_STATUS_14                     = $00004000;    // Bit 14, ���� ���� ��� #2(SQSTP2)�� ���� ���� ����.       
    QIEND_STATUS_15                     = $00008000;    // Bit 15, ���ڴ� �Է�(ECUP,ECDN) ���� �߻�                  
    QIEND_STATUS_16                     = $00010000;    // Bit 16, MPG �Է�(EXPP,EXMP) ���� �߻�                     
    QIEND_STATUS_17                     = $00020000;    // Bit 17, ���� �˻� ���� ����.                              
    QIEND_STATUS_18                     = $00040000;    // Bit 18, ��ȣ �˻� ���� ����.                              
    QIEND_STATUS_19                     = $00080000;    // Bit 19, ���� ������ �̻����� ���� ����.                   
    QIEND_STATUS_20                     = $00100000;    // Bit 20, ������ ���� �����߻�.                             
    QIEND_STATUS_21                     = $00200000;    // Bit 21, MPG ��� ��� �޽� ���� �����÷ο� �߻�           
    QIEND_STATUS_22                     = $00400000;    // Bit 22, DON'CARE                                          
    QIEND_STATUS_23                     = $00800000;    // Bit 23, DON'CARE                                          
    QIEND_STATUS_24                     = $01000000;    // Bit 24, DON'CARE                                          
    QIEND_STATUS_25                     = $02000000;    // Bit 25, DON'CARE                                          
    QIEND_STATUS_26                     = $04000000;    // Bit 26, DON'CARE                                          
    QIEND_STATUS_27                     = $08000000;    // Bit 27, DON'CARE                                          
    QIEND_STATUS_28                     = $10000000;    // Bit 28, ����/������ ���� ����̺� ����                    
    QIEND_STATUS_29                     = $20000000;    // Bit 29, �ܿ� �޽� ���� ��ȣ ��� ��.                      
    QIEND_STATUS_30                     = $40000000;    // Bit 30, ������ ���� ���� ���� ����                        
    QIEND_STATUS_31                     = $80000000;    // Bit 31, ���� ����̺� ����Ÿ ���� ����.                   
    {  �����ǰ(QI) �������� ����       }
    QIDRIVE_STATUS_0                    = $0000001;     // Bit 0, BUSY(����̺� ���� ��)                                      
    QIDRIVE_STATUS_1                    = $0000002;     // Bit 1, DOWN(���� ��)                                               
    QIDRIVE_STATUS_2                    = $0000004;     // Bit 2, CONST(��� ��)                                              
    QIDRIVE_STATUS_3                    = $0000008;     // Bit 3, UP(���� ��)                                                 
    QIDRIVE_STATUS_4                    = $0000010;     // Bit 4, ���� ����̺� ���� ��                                       
    QIDRIVE_STATUS_5                    = $0000020;     // Bit 5, ���� �Ÿ� ����̺� ���� ��                                  
    QIDRIVE_STATUS_6                    = $0000040;     // Bit 6, MPG ����̺� ���� ��                                        
    QIDRIVE_STATUS_7                    = $0000080;     // Bit 7, �����˻� ����̺� ������                                    
    QIDRIVE_STATUS_8                    = $0000100;     // Bit 8, ��ȣ �˻� ����̺� ���� ��                                  
    QIDRIVE_STATUS_9                    = $0000200;     // Bit 9, ���� ����̺� ���� ��                                       
    QIDRIVE_STATUS_10                   = $0000400;     // Bit 10, Slave ����̺� ������                                      
    QIDRIVE_STATUS_11                   = $0000800;     // Bit 11, ���� ���� ����̺� ����(���� ����̺꿡���� ǥ�� ���� �ٸ�)
    QIDRIVE_STATUS_12                   = $0001000;     // Bit 12, �޽� ����� ������ġ �Ϸ� ��ȣ �����.                     
    QIDRIVE_STATUS_13                   = $0002000;     // Bit 13, ���� ���� ����̺� ������.                                 
    QIDRIVE_STATUS_14                   = $0004000;     // Bit 14, ��ȣ ���� ����̺� ������.                                 
    QIDRIVE_STATUS_15                   = $0008000;     // Bit 15, �޽� ��� ��.                                              
    QIDRIVE_STATUS_16                   = $0010000;     // Bit 16, ���� ���� ������ ����(ó��)(0-7)                           
    QIDRIVE_STATUS_17                   = $0020000;     // Bit 17, ���� ���� ������ ����(�߰�)(0-7)                           
    QIDRIVE_STATUS_18                   = $0040000;     // Bit 18, ���� ���� ������ ����(��)(0-7)                             
    QIDRIVE_STATUS_19                   = $0080000;     // Bit 19, ���� ���� Queue ��� ����.                                 
    QIDRIVE_STATUS_20                   = $0100000;     // Bit 20, ���� ���� Queue ���� �H                                    
    QIDRIVE_STATUS_21                   = $0200000;     // Bit 21, ���� ���� ����̺��� �ӵ� ���(ó��)                       
    QIDRIVE_STATUS_22                   = $0400000;     // Bit 22, ���� ���� ����̺��� �ӵ� ���(��)                         
    QIDRIVE_STATUS_23                   = $0800000;     // Bit 23, MPG ���� #1 Full                                           
    QIDRIVE_STATUS_24                   = $1000000;     // Bit 24, MPG ���� #2 Full                                           
    QIDRIVE_STATUS_25                   = $2000000;     // Bit 25, MPG ���� #3 Full                                           
    QIDRIVE_STATUS_26                   = $4000000;     // Bit 26, MPG ���� ������ OverFlow                                   
    { �����ǰ(QI) ���ͷ�Ʈ ����1       }
    QIINTBANK1_DISABLE                  = $00000000;    // INTERRUT DISABLED.                                               
    QIINTBANK1_0                        = $00000001;    // Bit 0,  ���ͷ�Ʈ �߻� ��� ������ ���� �����.                   
    QIINTBANK1_1                        = $00000002;    // Bit 1,  ���� �����                                              
    QIINTBANK1_2                        = $00000004;    // Bit 2,  ���� ���۽�.                                             
    QIINTBANK1_3                        = $00000008;    // Bit 3,  ī���� #1 < �񱳱� #1 �̺�Ʈ �߻�                        
    QIINTBANK1_4                        = $00000010;    // Bit 4,  ī���� #1 = �񱳱� #1 �̺�Ʈ �߻�                        
    QIINTBANK1_5                        = $00000020;    // Bit 5,  ī���� #1 > �񱳱� #1 �̺�Ʈ �߻�                        
    QIINTBANK1_6                        = $00000040;    // Bit 6,  ī���� #2 < �񱳱� #2 �̺�Ʈ �߻�                        
    QIINTBANK1_7                        = $00000080;    // Bit 7,  ī���� #2 = �񱳱� #2 �̺�Ʈ �߻�                        
    QIINTBANK1_8                        = $00000100;    // Bit 8,  ī���� #2 > �񱳱� #2 �̺�Ʈ �߻�                        
    QIINTBANK1_9                        = $00000200;    // Bit 9,  ī���� #3 < �񱳱� #3 �̺�Ʈ �߻�                        
    QIINTBANK1_10                       = $00000400;    // Bit 10, ī���� #3 = �񱳱� #3 �̺�Ʈ �߻�                        
    QIINTBANK1_11                       = $00000800;    // Bit 11, ī���� #3 > �񱳱� #3 �̺�Ʈ �߻�                        
    QIINTBANK1_12                       = $00001000;    // Bit 12, ī���� #4 < �񱳱� #4 �̺�Ʈ �߻�                        
    QIINTBANK1_13                       = $00002000;    // Bit 13, ī���� #4 = �񱳱� #4 �̺�Ʈ �߻�                        
    QIINTBANK1_14                       = $00004000;    // Bit 14, ī���� #4 < �񱳱� #4 �̺�Ʈ �߻�                        
    QIINTBANK1_15                       = $00008000;    // Bit 15, ī���� #5 < �񱳱� #5 �̺�Ʈ �߻�                        
    QIINTBANK1_16                       = $00010000;    // Bit 16, ī���� #5 = �񱳱� #5 �̺�Ʈ �߻�                        
    QIINTBANK1_17                       = $00020000;    // Bit 17, ī���� #5 > �񱳱� #5 �̺�Ʈ �߻�                        
    QIINTBANK1_18                       = $00040000;    // Bit 18, Ÿ�̸� #1 �̺�Ʈ �߻�.                                   
    QIINTBANK1_19                       = $00080000;    // Bit 19, Ÿ�̸� #2 �̺�Ʈ �߻�.                                   
    QIINTBANK1_20                       = $00100000;    // Bit 20, ���� ���� ���� Queue �����.                             
    QIINTBANK1_21                       = $00200000;    // Bit 21, ���� ���� ���� Queue ����H                              
    QIINTBANK1_22                       = $00400000;    // Bit 22, Ʈ���� �߻��Ÿ� �ֱ�/������ġ Queue �����.              
    QIINTBANK1_23                       = $00800000;    // Bit 23, Ʈ���� �߻��Ÿ� �ֱ�/������ġ Queue ����H               
    QIINTBANK1_24                       = $01000000;    // Bit 24, Ʈ���� ��ȣ �߻� �̺�Ʈ                                  
    QIINTBANK1_25                       = $02000000;    // Bit 25, ��ũ��Ʈ #1 ��ɾ� ���� ���� Queue �����.               
    QIINTBANK1_26                       = $04000000;    // Bit 26, ��ũ��Ʈ #2 ��ɾ� ���� ���� Queue �����.               
    QIINTBANK1_27                       = $08000000;    // Bit 27, ��ũ��Ʈ #3 ��ɾ� ���� ���� �������� ����Ǿ� �ʱ�ȭ ��.
    QIINTBANK1_28                       = $10000000;    // Bit 28, ��ũ��Ʈ #4 ��ɾ� ���� ���� �������� ����Ǿ� �ʱ�ȭ ��.
    QIINTBANK1_29                       = $20000000;    // Bit 29, ���� �˶���ȣ �ΰ���.                                    
    QIINTBANK1_30                       = $40000000;    // Bit 30, |CNT1| - |CNT2| >= |CNT4| �̺�Ʈ �߻�.                   
    QIINTBANK1_31                       = $80000000;    // Bit 31, ���ͷ�Ʈ �߻� ��ɾ�|INTGEN| ����.                       
    { �����ǰ(QI) ���ͷ�Ʈ ����2       }
    QIINTBANK2_DISABLE                  = $00000000;    // INTERRUT DISABLED.                                                                   
    QIINTBANK2_0                        = $00000001;    // Bit 0,  ��ũ��Ʈ #1 �б� ��� ��� Queue �� ����H.                                  
    QIINTBANK2_1                        = $00000002;    // Bit 1,  ��ũ��Ʈ #2 �б� ��� ��� Queue �� ����H.                                  
    QIINTBANK2_2                        = $00000004;    // Bit 2,  ��ũ��Ʈ #3 �б� ��� ��� �������Ͱ� ���ο� �����ͷ� ���ŵ�.                
    QIINTBANK2_3                        = $00000008;    // Bit 3,  ��ũ��Ʈ #4 �б� ��� ��� �������Ͱ� ���ο� �����ͷ� ���ŵ�.                
    QIINTBANK2_4                        = $00000010;    // Bit 4,  ��ũ��Ʈ #1 �� ���� ��ɾ� �� ���� �� ���ͷ�Ʈ �߻����� ������ ��ɾ� �����.
    QIINTBANK2_5                        = $00000020;    // Bit 5,  ��ũ��Ʈ #2 �� ���� ��ɾ� �� ���� �� ���ͷ�Ʈ �߻����� ������ ��ɾ� �����.
    QIINTBANK2_6                        = $00000040;    // Bit 6,  ��ũ��Ʈ #3 �� ���� ��ɾ� ���� �� ���ͷ�Ʈ �߻����� ������ ��ɾ� �����.   
    QIINTBANK2_7                        = $00000080;    // Bit 7,  ��ũ��Ʈ #4 �� ���� ��ɾ� ���� �� ���ͷ�Ʈ �߻����� ������ ��ɾ� �����.   
    QIINTBANK2_8                        = $00000100;    // Bit 8,  ���� ����                                                                    
    QIINTBANK2_9                        = $00000200;    // Bit 9,  ���� ��ġ ���� �Ϸ�(Inposition)����� ����� ����,���� ���� �߻�.            
    QIINTBANK2_10                       = $00000400;    // Bit 10, �̺�Ʈ ī���ͷ� ���� �� ����� �̺�Ʈ ���� #1 ���� �߻�.                     
    QIINTBANK2_11                       = $00000800;    // Bit 11, �̺�Ʈ ī���ͷ� ���� �� ����� �̺�Ʈ ���� #2 ���� �߻�.                     
    QIINTBANK2_12                       = $00001000;    // Bit 12, SQSTR1 ��ȣ �ΰ� ��.                                                         
    QIINTBANK2_13                       = $00002000;    // Bit 13, SQSTR2 ��ȣ �ΰ� ��.                                                         
    QIINTBANK2_14                       = $00004000;    // Bit 14, UIO0 �͹̳� ��ȣ�� '1'�� ����.                                               
    QIINTBANK2_15                       = $00008000;    // Bit 15, UIO1 �͹̳� ��ȣ�� '1'�� ����.                                               
    QIINTBANK2_16                       = $00010000;    // Bit 16, UIO2 �͹̳� ��ȣ�� '1'�� ����.                                               
    QIINTBANK2_17                       = $00020000;    // Bit 17, UIO3 �͹̳� ��ȣ�� '1'�� ����.                                               
    QIINTBANK2_18                       = $00040000;    // Bit 18, UIO4 �͹̳� ��ȣ�� '1'�� ����.                                               
    QIINTBANK2_19                       = $00080000;    // Bit 19, UIO5 �͹̳� ��ȣ�� '1'�� ����.                                               
    QIINTBANK2_20                       = $00100000;    // Bit 20, UIO6 �͹̳� ��ȣ�� '1'�� ����.                                               
    QIINTBANK2_21                       = $00200000;    // Bit 21, UIO7 �͹̳� ��ȣ�� '1'�� ����.                                               
    QIINTBANK2_22                       = $00400000;    // Bit 22, UIO8 �͹̳� ��ȣ�� '1'�� ����.                                               
    QIINTBANK2_23                       = $00800000;    // Bit 23, UIO9 �͹̳� ��ȣ�� '1'�� ����.                                               
    QIINTBANK2_24                       = $01000000;    // Bit 24, UIO10 �͹̳� ��ȣ�� '1'�� ����.                                              
    QIINTBANK2_25                       = $02000000;    // Bit 25, UIO11 �͹̳� ��ȣ�� '1'�� ����.                                              
    QIINTBANK2_26                       = $04000000;    // Bit 26, ���� ���� ����(LMT, ESTOP, STOP, ESTOP, CMD, ALARM) �߻�.                    
    QIINTBANK2_27                       = $08000000;    // Bit 27, ���� �� ������ ���� ���� �߻�.                                               
    QIINTBANK2_28                       = $10000000;    // Bit 28, Don't Care                                                                   
    QIINTBANK2_29                       = $20000000;    // Bit 29, ����Ʈ ��ȣ(PELM, NELM)��ȣ�� �Է� ��.                                       
    QIINTBANK2_30                       = $40000000;    // Bit 30, �ΰ� ����Ʈ ��ȣ(PSLM, NSLM)��ȣ�� �Է� ��.                                  
    QIINTBANK2_31                       = $80000000;    // Bit 31, ��� ���� ��ȣ(ESTOP)��ȣ�� �Էµ�.                                          
    { RTEX ��ũ������ ����              }
    NET_STATUS_DISCONNECTED             = 1;
    NET_STATUS_LOCK_MISMATCH            = 5;
    NET_STATUS_CONNECTED                = 6;
    { �����ǰ(QI) Override ��ġ ����   }   
    OVERRIDE_POS_START                  = 0;
    OVERRIDE_POS_END                    = 1;
    { �����ǰ(QI) Profile �켱����     }   
    PRIORITY_VELOCITY                   = 0;
    PRIORITY_ACCELTIME                  = 1;
    { ����Լ� ��ȯ���� ����            }
    FUNC_RETURN_IMMEDIATE               = 0;
    FUNC_RETURN_BLOCKING                = 1;
    FUNC_RETURN_NON_BLOCKING            = 2;
    { ������ �˶��ڵ� ��� ��������     }
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
    CnSqr1Mode                         = 1;                            // 1ü��
    CnSqr2Mode                         = 2;                            // 2ü��
    CnSqr4Mode                         = 3;                            // 4ü��
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
