/****************************************************************************
*****************************************************************************
**
** File Name
** ----------
**
** AXHS.CS
**
** COPYRIGHT (c) AJINEXTEK Co., LTD
**
*****************************************************************************
*****************************************************************************
**
** Description
** -----------
** Resource Define Header File
** 
**
*****************************************************************************
*****************************************************************************
**
** Source Change Indices
** ---------------------
** 
** (None)
**
**
*****************************************************************************
*****************************************************************************
**
** Website
** ---------------------
**
** http://www.ajinextek.com
**
*****************************************************************************
*****************************************************************************
*/

using System.Runtime.InteropServices;

// 베이스보드 정의
public enum AXT_BASE_BOARD:uint
{
   AXT_UNKNOWN                                              = 0x00,    // Unknown Baseboard
    AXT_BIHR                                                = 0x01,    // ISA bus, Half size
    AXT_BIFR                                                = 0x02,    // ISA bus, Full size
    AXT_BPHR                                                = 0x03,    // PCI bus, Half size
    AXT_BPFR                                                = 0x04,    // PCI bus, Full size
    AXT_BV3R                                                = 0x05,    // VME bus, 3U size
    AXT_BV6R                                                = 0x06,    // VME bus, 6U size
    AXT_BC3R                                                = 0x07,    // cPCI bus, 3U size
    AXT_BC6R                                                = 0x08,    // cPCI bus, 6U size
    AXT_BEHR                                                = 0x09,    // PCIe bus, Half size
    AXT_BEFR                                                = 0x0A,    // PCIe bus, Full size
    AXT_BEHD                                                = 0x0B,    // PCIe bus, Half size, DB-32T
    AXT_FMNSH4D                                             = 0x52,    // ISA bus, Full size, DB-32T, SIO-2V03 * 2
    AXT_PCI_DI64R                                           = 0x43,    // PCI bus, Digital IN 64점
    AXT_PCIE_DI64R                                          = 0x44,    // PCIe bus, Digital IN 64점
    AXT_PCI_DO64R                                           = 0x53,    // PCI bus, Digital OUT 64점
    AXT_PCIE_DO64R                                          = 0x54,    // PCIe bus, Digital OUT 64점
    AXT_PCI_DB64R                                           = 0x63,    // PCI bus, Digital IN 32점, OUT 32점
    AXT_PCIE_DB64R                                          = 0x64,    // PCIe bus, Digital IN 32점, OUT 32점
    AXT_PCIN204                                             = 0x82,    // PCI bus, Half size On-Board 2 Axis controller.
    AXT_BPHD                                                = 0x83,    // PCI bus, Half size, DB-32T
    AXT_PCIN404                                             = 0x84,    // PCI bus, Half size On-Board 4 Axis controller.    
    AXT_PCIN804                                             = 0x85,    // PCI bus, Half size On-Board 8 Axis controller.
    AXT_PCIEN804                                            = 0x86,    // PCIe bus, Half size On-Board 8 Axis controller.
    AXT_PCIEN404                                            = 0x87,    // PCIe bus, Half size On-Board 4 Axis controller.
    AXT_PCI_AIO1602HR                                       = 0x93,    // PCI bus, Half size, AI-16ch, AO-2ch AI16HR
    AXT_PCI_R1604                                           = 0xC1,    // PCI bus[PCI9030], Half size, RTEX based 16 axis controller
    AXT_PCI_R3204                                           = 0xC2,    // PCI bus[PCI9030], Half size, RTEX based 32 axis controller
    AXT_PCI_R32IO                                           = 0xC3,    // PCI bus[PCI9030], Half size, RTEX based IO only.
    AXT_PCI_REV2                                            = 0xC4,    // Reserved.
    AXT_PCI_R1604MLII                                       = 0xC5,    // PCI bus[PCI9030], Half size, Mechatrolink-II 16/32 axis controller.
    AXT_PCI_R0804MLII                                       = 0xC6,    // PCI bus[PCI9030], Half size, Mechatrolink-II 08 axis controller.
    AXT_PCI_Rxx00MLIII                                      = 0xC7,    // Master PCI Board, Mechatrolink III AXT, PCI Bus[PCI9030], Half size, Max.32 Slave module support
    AXT_PCIE_Rxx00MLIII                                     = 0xC8,    // Master PCI Express Board, Mechatrolink III AXT, PCI Bus[], Half size, Max.32 Slave module support
    AXT_PCP2_Rxx00MLIII                                     = 0xC9,    // Master PCI/104-Plus Board, Mechatrolink III AXT, PCI Bus[], Half size, Max.32 Slave module support
    AXT_PCI_R1604SIIIH                                      = 0xCA,    // PCI bus[PCI9030], Half size, SSCNET III / H 16/32 axis controller.
    AXT_PCI_R32IOEV                                         = 0xCB,    // PCI bus[PCI9030], Half size, RTEX based IO only. Economic version.
    AXT_PCIE_R0804RTEX                                      = 0xCC,    // PCIe bus, Half size, Half size, RTEX based 08 axis controller.
    AXT_PCIE_R1604RTEX                                      = 0xCD,    // PCIe bus, Half size, Half size, RTEX based 16 axis controller.
    AXT_PCIE_R2404RTEX                                      = 0xCE,    // PCIe bus, Half size, Half size, RTEX based 24 axis controller.
    AXT_PCIE_R3204RTEX                                      = 0xCF,    // PCIe bus, Half size, Half size, RTEX based 32 axis controller.
    AXT_PCIE_Rxx04SIIIH                                     = 0xD0,    // PCIe bus, Half size, SSCNET III / H 16(or 32)-axis(CAMC-QI based) controller.
    AXT_PCIE_Rxx00SIIIH                                     = 0xD1,    // PCIe bus, Half size, SSCNET III / H Max. 32-axis(DSP Based) controller.
    AXT_ETHERCAT_RTOSV5                                     = 0xD2,    // EtherCAT, RTOS(On Time), Version 5.29
    AXT_PCI_Nx04_A                                          = 0xD3,	   // PCI bus, Half size On-Board x Axis controller For Rtos.
    AXT_PCI_R3200MLIII_IO                                   = 0xD4,    // PCI Board, Mechatrolink III AXT, PCI Bus[PCI9030], Half size, Max.32 IO only	controller
    AXT_PCIE_R3205MLIII                                     = 0xD5,    // PCIe bus, Half size, Mechatrolink III / H Max. 32-axis(DSP Based) controller.
    AXT_PCIE_Rxx05SIIIH                                     = 0xD6,    // PCIe bus, Half size, Sscnet III / H  32 axis(DSP Based) controller.
    AXT_PCIE_Rxx05RTEX                                      = 0xD7,    // PCIe bus, Half size, RTEX 32 axis(DSP Based) controller.
    AXT_PCIE_Rxx05ECAT                                      = 0xD8,    // PCIe bus, Half size, ECAT(DSP Based) controller.
    AXT_PCI_Rxx05MLIII                                      = 0xD9,    // PCI bus, Half size, Mechatrolink III 32 axis(DSP Based) controller.
    AXT_PCI_Rxx05SIIIH                                      = 0xDA,    // PCI bus, Half size, Sscnet III / H  32 axis(DSP Based) controller.
    AXT_PCI_Rxx05RTEX                                       = 0xDB,    // PCI bus, Half size, RTEX 32 axis(DSP Based) controller.
    AXT_PCI_Rxx05ECAT                                       = 0xDC     // PCI bus, Half size, ECAT(DSP Based) controller.
}                                               
                                                
// 모듈 정의                                    
public enum AXT_MODULE:uint                     
{                                               
    AXT_UNKNOWN                                             = 0x00,    // Unknown Baseboard                                            
    AXT_SMC_2V01                                            = 0x01,    // CAMC-5M, 2 Axis
    AXT_SMC_2V02                                            = 0x02,    // CAMC-FS, 2 Axis
    AXT_SMC_1V01                                            = 0x03,    // CAMC-5M, 1 Axis
    AXT_SMC_1V02                                            = 0x04,    // CAMC-FS, 1 Axis
    AXT_SMC_2V03                                            = 0x05,    // CAMC-IP, 2 Axis
    AXT_SMC_4V04                                            = 0x06,    // CAMC-QI, 4 Axis
    AXT_SMC_R1V04A4                                         = 0x07,    // CAMC-QI, 1 Axis, For RTEX A4 slave only
    AXT_SMC_1V03                                            = 0x08,    // CAMC-IP, 1 Axis
    AXT_SMC_R1V04                                           = 0x09,    // CAMC-QI, 1 Axis, For RTEX SLAVE only(Pulse Output Module)
    AXT_SMC_R1V04MLIISV                                     = 0x0A,    // CAMC-QI, 1 Axis, For Sigma-X series.
    AXT_SMC_R1V04MLIIPM                                     = 0x0B,    // 2 Axis, For Pulse output series(JEPMC-PL2910).
    AXT_SMC_2V04                                            = 0x0C,    // CAMC-QI, 2 Axis
    AXT_SMC_R1V04A5                                         = 0x0D,    // CAMC-QI, 1 Axis, For RTEX A5N slave only
    AXT_SMC_R1V04MLIICL                                     = 0x0E,    // CAMC-QI, 1 Axis, For MLII Convex Linear only
    AXT_SMC_R1V04MLIICR                                     = 0x0F,    // CAMC-QI, 1 Axis, For MLII Convex Rotary only
    AXT_SMC_R1V04PM2Q                                       = 0x10,    // CAMC-QI, 2 Axis, For RTEX SLAVE only(Pulse Output Module)
    AXT_SMC_R1V04PM2QE                                      = 0x11,    // CAMC-QI, 4 Axis, For RTEX SLAVE only(Pulse Output Module)
    AXT_SMC_R1V04MLIIORI                                    = 0x12,    // CAMC-QI, 1 Axis, For MLII Oriental Step Driver only
    AXT_SMC_R1V04SIIIHMIV                                   = 0x14,    // CAMC-QI, 1 Axis, For SSCNETIII/H MRJ4
    AXT_SMC_R1V04SIIIHMIV_R                                 = 0x15,    // CAMC-QI, 1 Axis, For SSCNETIII/H MRJ4
    AXT_SMC_R1V04MLIIISV                                    = 0x20,    // DSP, 1 Axis, For ML-3 SigmaV/YASKAWA only 
    AXT_SMC_R1V04MLIIIPM                                    = 0x21,    // DSP, 1 Axis, For ML-3 SLAVE/AJINEXTEK only(Pulse Output Module)
    AXT_SMC_R1V04MLIIISV_MD                                 = 0x22,    // DSP, 1 Axis, For ML-3 SigmaV-MD/YASKAWA only (Multi-Axis Control amp)
    AXT_SMC_R1V04MLIIIS7S                                   = 0x23,    // DSP, 1 Axis, For ML-3 Sigma7S/YASKAWA only
    AXT_SMC_R1V04MLIIIS7W                                   = 0x24,    // DSP, 2 Axis, For ML-3 Sigma7W/YASKAWA only(Dual-Axis control amp)
    AXT_SMC_R1V04MLIIIRS2                                   = 0x25,    // DSP, 1 Axis, For ML-3 RS2A/SANYO DENKY
	AXT_SMC_R1V04MLIIIS7_MD                                 = 0x26,    // DSP, 1 Axis, For ML-3 Sigma7-MD/YASKAWA only (Multi-Axis Control amp)
    AXT_SMC_PM2QSIIIH                                       = 0X60,    // CAMC-QI, 2Axis For SSCNETIII/H SLAVE only(Pulse Output Module)
    AXT_SMC_PM4QSIIIH                                       = 0X61,    // CAMC-QI, 4Axis For SSCNETIII/H SLAVE only(Pulse Output Module)
    AXT_SIO_CNT2SIIIH                                       = 0X62,    // Counter slave module, Reversible counter, 2 channels, For SSCNETIII/H Only
    AXT_SIO_DI32SIIIH                                       = 0X63,    // DI slave module, SSCNETIII AXT, IN 32-Channel
    AXT_SIO_DO32SIIIH                                       = 0X64,    // DO slave module, SSCNETIII AXT, OUT 32-Channel
    AXT_SIO_DB32SIIIH                                       = 0X65,    // DB slave module, SSCNETIII AXT, IN 16-Channel, OUT 16-Channel
    AXT_SIO_AI16SIIIH                                       = 0X66,    // AI slave module, SSCNETIII AXT, Analog IN 16ch, 16 bit
    AXT_SIO_AO08SIIIH                                       = 0X67,    // A0 slave module, SSCNETIII AXT, Analog OUT 8ch, 16 bit
    AXT_SMC_PM2QSIIIH_R                                     = 0X68,    // CAMC-QI, 2Axis For SSCNETIII/H SLAVE only(Pulse Output Module) 
    AXT_SMC_PM4QSIIIH_R                                     = 0X69,    // CAMC-QI, 4Axis For SSCNETIII/H SLAVE only(Pulse Output Module) 
    AXT_SIO_CNT2SIIIH_R                                     = 0X6A,    // Counter slave module, Reversible counter, 2 channels, For SSCNETIII/H Only 
    AXT_SIO_DI32SIIIH_R                                     = 0X6B,    // DI slave module, SSCNETIII AXT, IN 32-Channel 
    AXT_SIO_DO32SIIIH_R                                     = 0X6C,    // DO slave module, SSCNETIII AXT, OUT 32-Channel 
    AXT_SIO_DB32SIIIH_R                                     = 0X6D,    // DB slave module, SSCNETIII AXT, IN 16-Channel, OUT 16-Channel 
    AXT_SIO_AI16SIIIH_R                                     = 0X6E,    // AI slave module, SSCNETIII AXT, Analog IN 16ch, 16 bit 
    AXT_SIO_AO08SIIIH_R                                     = 0X6F,    // A0 slave module, SSCNETIII AXT, Analog OUT 8ch, 16 bit 
    AXT_SIO_RDI32MLIII                                      = 0x70,    // DI slave module, MechatroLink III AXT, IN 32-Channel NPN
    AXT_SIO_RDO32MLIII                                      = 0x71,    // DO slave module, MechatroLink III AXT, OUT 32-Channel  NPN
    AXT_SIO_RDB32MLIII                                      = 0x72,    // DB slave module, MechatroLink III AXT, IN 16-Channel, OUT 16-Channel  NPN
    AXT_SIO_RDI32MSMLIII                                    = 0x73,    // DI slave module, MechatroLink III M-SYSTEM, IN 32-Channel
    AXT_SIO_RDO32AMSMLIII                                   = 0x74,    // DO slave module, MechatroLink III M-SYSTEM, OUT 32-Channel
    AXT_SIO_RDI32PMLIII                                     = 0x75,    // DI slave module, MechatroLink III AXT, IN 32-Channel PNP
    AXT_SIO_RDO32PMLIII                                     = 0x76,    // DO slave module, MechatroLink III AXT, OUT 32-Channel  PNP
    AXT_SIO_RDB32PMLIII                                     = 0x77,    // DB slave module, MechatroLink III AXT, IN 16-Channel, OUT 16-Channel  PNP
    AXT_SIO_RDI16MLIII                                      = 0x78,    // DI slave module, MechatroLink III M-SYSTEM, IN 16-Channel
    AXT_SIO_UNDEFINEMLIII                                   = 0x79,    // IO slave module, MechatroLink III Any, Max. IN 480-Channel, Max. OUT 480-Channel
    AXT_SIO_RDI32MLIIISFA	                                = 0x7A,    // DI slave module, MechatroLink III AXT(SFA), IN 32-Channel NPN
	AXT_SIO_RDO32MLIIISFA	                                = 0x7B,    // DO slave module, MechatroLink III AXT(SFA), OUT 32-Channel  NPN
	AXT_SIO_RDB32MLIIISFA	                                = 0x7C,    // DB slave module, MechatroLink III AXT(SFA), IN 16-Channel, OUT 16-Channel  NPN
    AXT_SIO_RDB128MLIIIAI                                   = 0x7D,    // Intelligent I/O (Product by IAI), For MLII only
    AXT_SIO_RSIMPLEIOMLII                                   = 0x7E,    // Digital IN/Out xx점, Simple I/O sereies, MLII 전용.
    AXT_SIO_RDO16AMLIII                                     = 0x7F,    // DO slave module, MechatroLink III M-SYSTEM, OUT 16-Channel, NPN
    AXT_SIO_RDI16MLII                                       = 0x80,    // DISCRETE INPUT MODULE, 16 points (Product by M-SYSTEM), For MLII only
    AXT_SIO_RDO16AMLII                                      = 0x81,    // NPN TRANSISTOR OUTPUT MODULE, 16 points (Product by M-SYSTEM), For MLII only
    AXT_SIO_RDO16BMLII                                      = 0x82,    // PNP TRANSISTOR OUTPUT MODULE, 16 points (Product by M-SYSTEM), For MLII only 
    AXT_SIO_RDB96MLII                                       = 0x83,    // Digital IN/OUT(Selectable), MAX 96 points, For MLII only
    AXT_SIO_RDO32RTEX                                       = 0x84,    // Digital OUT  32점
    AXT_SIO_RDI32RTEX                                       = 0x85,    // Digital IN  32점
    AXT_SIO_RDB32RTEX                                       = 0x86,    // Digital IN/OUT  32점
    AXT_SIO_RDO16BMLIII                                   	= 0x8A,    // DO slave module, MechatroLink III M-SYSTEM, OUT 16-Channel, PNP
    AXT_SIO_RDB32ML2NT1                                     = 0x8B,    // DB slave module, MechatroLink2 AJINEXTEK NT1 Series
    AXT_SIO_RDB128YSMLIII                                   = 0x8C,    // IO slave module, MechatroLink III Any, Max. IN 480-Channel, Max. OUT 480-Channel
    AXT_SIO_DI32_P                                          = 0x92,    // Digital IN  32점, PNP type(source type)
    AXT_SIO_DO32T_P                                         = 0x93,    // Digital OUT 32점, Power TR, PNT type(source type)
    AXT_SIO_RDB128MLII                                      = 0x94,    // Digital IN 64점 / OUT 64점, MLII 전용(JEPMC-IO2310)
    AXT_SIO_RDI32                                           = 0x95,    // Digital IN  32점, For RTEX only
    AXT_SIO_RDO32                                           = 0x96,    // Digital OUT 32점, For RTEX only
    AXT_SIO_DI32                                            = 0x97,    // Digital IN  32점
    AXT_SIO_DO32P                                           = 0x98,    // Digital OUT 32점
    AXT_SIO_DB32P                                           = 0x99,    // Digital IN 16점 / OUT 16점
    AXT_SIO_RDB32T                                          = 0x9A,    // Digital IN 16점 / OUT 16점, For RTEX only
    AXT_SIO_DO32T                                           = 0x9E,    // Digital OUT 16점, Power TR OUTPUT
    AXT_SIO_DB32T                                           = 0x9F,    // Digital IN 16점 / OUT 16점, Power TR OUTPUT
    AXT_SIO_RAI16RB                                         = 0xA0,    // A0h(160) : AI 16Ch, 16 bit, For RTEX only
    AXT_SIO_AI4RB                                           = 0xA1,    // A1h(161) : AI 4Ch, 12 bit
    AXT_SIO_AO4RB                                           = 0xA2,    // A2h(162) : AO 4Ch, 12 bit
    AXT_SIO_AI16H                                           = 0xA3,    // A3h(163) : AI 4Ch, 16 bit
    AXT_SIO_AO8H                                            = 0xA4,    // A4h(164) : AO 4Ch, 16 bit
    AXT_SIO_AI16HB                                          = 0xA5,    // A5h(165) : AI 16Ch, 16 bit (SIO-AI16HR(input module))
    AXT_SIO_AO2HB                                           = 0xA6,    // A6h(166) : AO 2Ch, 16 bit  (SIO-AI16HR(output module))
    AXT_SIO_RAI8RB                                          = 0xA7,    // A7h(167) : AI 8Ch, 16 bit, For RTEX only        
    AXT_SIO_RAO4RB                                          = 0xA8,    // A8h(168) : AO 4Ch, 16 bit, For RTEX only
    AXT_SIO_RAI4MLII                                        = 0xA9,    // A9h(169) : AI 4Ch, 16 bit, For MLII only
    AXT_SIO_RAO2MLII                                        = 0xAA,    // AAh(170) : AO 2Ch, 16 bit, For MLII only
    AXT_SIO_RAVCI4MLII                                      = 0xAB,    // DC VOLTAGE/CURRENT INPUT MODULE, 4 points (Product by M-SYSTEM), For MLII only
    AXT_SIO_RAVO2MLII                                       = 0xAC,    // DC VOLTAGE OUTPUT MODULE, 2 points (Product by M-SYSTEM), For MLII only
    AXT_SIO_RACO2MLII                                       = 0xAD,    // DC CURRENT OUTPUT MODULE, 2 points (Product by M-SYSTEM), For MLII only
    AXT_SIO_RATI4MLII                                       = 0xAE,    // THERMOCOUPLE INPUT MODULE, 4 points (Product by M-SYSTEM), For MLII only
    AXT_SIO_RARTDI4MLII                                     = 0xAF,    // RTD INPUT MODULE, 4 points (Product by M-SYSTEM), For MLII only
    AXT_SIO_RCNT2MLII                                       = 0xB0,    // Counter slave module, Reversible counter, 2 channels (Product by YASKWA), For MLII only
    AXT_SIO_CN2CH                                           = 0xB1,    // Counter Module, 2 channels, Remapped ID, Actual ID is (0xA8)
    AXT_SIO_RCNT2RTEX                                       = 0xB2,    // Counter slave module, Reversible counter, 2 channels, For RTEX Only
    AXT_SIO_RCNT2MLIII                                      = 0xB3,    // Counter slave moudle, MechatroLink III AXT, 2 ch, Trigger per channel
    AXT_SIO_RHPC4MLIII                                      = 0xB4,    // Counter slave moudle, MechatroLink III AXT, 4 ch
    AXT_SIO_RAI16RTEX                                       = 0xC0,    // ANALOG VOLTAGE INPUT(+- 10V) 16 Channel RTEX 
    AXT_SIO_RAO08RTEX                                       = 0xC1,    // ANALOG VOLTAGE OUTPUT(+- 10V) 08 Channel RTEX
    AXT_SIO_RAI8MLIII                                       = 0xC2,    // AI slave module, MechatroLink III AXT, Analog IN 8ch, 16 bit
    AXT_SIO_RAI16MLIII                                      = 0xC3,    // AI slave module, MechatroLink III AXT, Analog IN 16ch, 16 bit
    AXT_SIO_RAO4MLIII                                       = 0xC4,    // A0 slave module, MechatroLink III AXT, Analog OUT 4ch, 16 bit
    AXT_SIO_RAO8MLIII                                       = 0xC5,    // A0 slave module, MechatroLink III AXT, Analog OUT 8ch, 16 bit
    AXT_SIO_RAVO4MLII                                       = 0xC6,    // DC VOLTAGE OUTPUT MODULE, 4 points (Product by M-SYSTEM), For MLII only
	AXT_SIO_RAV04MLIII										= 0xC7,    // AO Slave module, MechatroLink III M-SYSTEM Voltage output module
	AXT_SIO_RAVI4MLIII										= 0xC8,    // AI Slave module, MechatroLink III M-SYSTEM Voltage/Current input module
    AXT_SIO_RAI16MLIIISFA                                   = 0xC9,    // AI slave module, MechatroLink III AXT(SFA), Analog IN 16ch, 16 bit
    AXT_SIO_RDB32MSMLIII                                    = 0xCA,    // DIO slave module, MechatroLink III M-SYSTEM, IN 16-Channel, OUT 16-Channel
    AXT_SIO_RAVI4MLII                                       = 0xCB,    // DC VOLTAGE/CURRENT INPUT MODULE, 4 points (Product by M-SYSTEM), For MLII only
    AXT_SIO_RMEMORY_MLIII                                   = 0xCC,    // Memory Access type module, MechatroLink III
    AXT_COM_234R                                            = 0xD3,    // COM-234R
    AXT_COM_484R                                            = 0xD4,    // COM-484R
    AXT_SIO_RPI2                                            = 0xD5,    // Pulse counter module(JEPMC-2900)
    AXT_SIO_HPC4                                            = 0xD6,    // External Encoder module for 4Channel with Trigger function.
    AXT_SIO_AO4F                                            = 0xD7,    // AO 4Ch, 16 bit
    AXT_SIO_AI8F                                            = 0xD8,    // AI 8Ch, 16 bit
    AXT_SIO_AI8AO4F                                         = 0xD9     // AI 8Ch, AO 4Ch, 16 bit
}

public enum AXT_FUNC_RESULT:uint
{
    AXT_RT_SUCCESS                              = 0,        // API 함수 수행 성공
    AXT_RT_OPEN_ERROR                           = 1001,     // 라이브러리 오픈 되지않음
    AXT_RT_OPEN_ALREADY                         = 1002,     // 라이브러리 오픈 되어있고 사용 중임
    AXT_RT_NOT_OPEN                             = 1053,     // 라이브러리 초기화 실패
    AXT_RT_NOT_SUPPORT_VERSION                  = 1054,     // 지원하지않는 하드웨어
    AXT_RT_LOCK_FILE_MISMATCH                   = 1055,     // Lock파일과 현재 Scan정보가 일치하지 않음

    AXT_RT_INVALID_BOARD_NO                     = 1101,     // 유효하지 않는 보드 번호
    AXT_RT_INVALID_MODULE_POS                   = 1102,     // 유효하지 않는 모듈 위치
    AXT_RT_INVALID_LEVEL                        = 1103,     // 유효하지 않는 레벨
    AXT_RT_INVALID_VARIABLE                     = 1104,     // 유효하지 않는 변수
    AXT_RT_ERROR_VERSION_READ                   = 1151,     // 라이브러리 버전을 읽을수 없음
    AXT_RT_NETWORK_ERROR                        = 1152,     // 하드웨어 네트워크 에러
    AXT_RT_NETWORK_LOCK_MISMATCH                = 1153,     // 보드 Lock정보와 현재 Scan정보가 일치하지 않음
    
    AXT_RT_1ST_BELOW_MIN_VALUE                  = 1160,     // 첫번째 인자값이 최소값보다 더 작음
    AXT_RT_1ST_ABOVE_MAX_VALUE                  = 1161,     // 첫번째 인자값이 최대값보다 더 큼
    AXT_RT_2ND_BELOW_MIN_VALUE                  = 1170,     // 두번째 인자값이 최소값보다 더 작음
    AXT_RT_2ND_ABOVE_MAX_VALUE                  = 1171,     // 두번째 인자값이 최대값보다 더 큼
    AXT_RT_3RD_BELOW_MIN_VALUE                  = 1180,     // 세번째 인자값이 최소값보다 더 작음
    AXT_RT_3RD_ABOVE_MAX_VALUE                  = 1181,     // 세번째 인자값이 최대값보다 더 큼
    AXT_RT_4TH_BELOW_MIN_VALUE                  = 1190,     // 네번째 인자값이 최소값보다 더 작음
    AXT_RT_4TH_ABOVE_MAX_VALUE                  = 1191,     // 네번째 인자값이 최대값보다 더 큼
    AXT_RT_5TH_BELOW_MIN_VALUE                  = 1200,     // 다섯번째 인자값이 최소값보다 더 작음
    AXT_RT_5TH_ABOVE_MAX_VALUE                  = 1201,     // 다섯번째 인자값이 최대값보다 더 큼
    AXT_RT_6TH_BELOW_MIN_VALUE                  = 1210,     // 여섯번째 인자값이 최소값보다 더 작음 
    AXT_RT_6TH_ABOVE_MAX_VALUE                  = 1211,     // 여섯번째 인자값이 최대값보다 더 큼
    AXT_RT_7TH_BELOW_MIN_VALUE                  = 1220,     // 일곱번째 인자값이 최소값보다 더 작음
    AXT_RT_7TH_ABOVE_MAX_VALUE                  = 1221,     // 일곱번째 인자값이 최대값보다 더 큼
    AXT_RT_8TH_BELOW_MIN_VALUE                  = 1230,     // 여덟번째 인자값이 최소값보다 더 작음
    AXT_RT_8TH_ABOVE_MAX_VALUE                  = 1231,     // 여덟번째 인자값이 최대값보다 더 큼
    AXT_RT_9TH_BELOW_MIN_VALUE                  = 1240,     // 아홉번째 인자값이 최소값보다 더 작음
    AXT_RT_9TH_ABOVE_MAX_VALUE                  = 1241,     // 아홉번째 인자값이 최대값보다 더 큼
    AXT_RT_10TH_BELOW_MIN_VALUE                 = 1250,     // 열번째 인자값이 최소값보다 더 작음
    AXT_RT_10TH_ABOVE_MAX_VALUE                 = 1251,     // 열번째 인자값이 최대값보다 더 큼
    
    AXT_RT_AIO_OPEN_ERROR                       = 2001,     // AIO 모듈 오픈실패
    AXT_RT_AIO_NOT_MODULE                       = 2051,     // AIO 모듈 없음
    AXT_RT_AIO_NOT_EVENT                        = 2052,     // AIO 이벤트 읽지 못함
    AXT_RT_AIO_INVALID_MODULE_NO                = 2101,     // 유효하지않은 AIO모듈
    AXT_RT_AIO_INVALID_CHANNEL_NO               = 2102,     // 유효하지않은 AIO채널번호
    AXT_RT_AIO_INVALID_USE                      = 2106,     // AIO 함수 사용못함
    AXT_RT_AIO_INVALID_TRIGGER_MODE             = 2107,     // 유효하지않는 트리거 모드
    AXT_RT_AIO_EXTERNAL_DATA_EMPTY              = 2108,     // 외부 데이터 값이 없을 경우
    AXT_RT_AIO_INVALID_VALUE                    = 2109,     // 유효하지않는 값 설정

    AXT_RT_DIO_OPEN_ERROR                       = 3001,     // DIO 모듈 오픈실패
    AXT_RT_DIO_NOT_MODULE                       = 3051,     // DIO 모듈 없음
    AXT_RT_DIO_NOT_INTERRUPT                    = 3052,     // DIO 인터럽트 설정안됨
    AXT_RT_DIO_INVALID_MODULE_NO                = 3101,     // 유효하지않는 DIO 모듈 번호
    AXT_RT_DIO_INVALID_OFFSET_NO                = 3102,     // 유효하지않는 DIO OFFSET 번호
    AXT_RT_DIO_INVALID_LEVEL                    = 3103,     // 유효하지않는 DIO 레벨
    AXT_RT_DIO_INVALID_MODE                     = 3104,     // 유효하지않는 DIO 모드
    AXT_RT_DIO_INVALID_VALUE                    = 3105,     // 유효하지않는 값 설정
    AXT_RT_DIO_INVALID_USE                      = 3106,     // DIO 함수 사용못함      

    AXT_RT_CNT_OPEN_ERROR                       = 3201,     // CNT 모듈 오픈실패
    AXT_RT_CNT_NOT_MODULE                       = 3251,     // CNT 모듈 없음
    AXT_RT_CNT_NOT_INTERRUPT                    = 3252,     // CNT 인터럽트 설정안됨
    AXT_RT_CNT_INVALID_MODULE_NO                = 3301,     // 유효하지않는 CNT 모듈 번호
    AXT_RT_CNT_INVALID_CHANNEL_NO               = 3302,     // 유효하지않는 채널 번호
    AXT_RT_CNT_INVALID_OFFSET_NO                = 3303,     // 유효하지않는 CNT OFFSET 번호
    AXT_RT_CNT_INVALID_LEVEL                    = 3304,     // 유효하지않는 CNT 레벨
    AXT_RT_CNT_INVALID_MODE                     = 3305,     // 유효하지않는 CNT 모드
    AXT_RT_CNT_INVALID_VALUE                    = 3306,     // 유효하지않는 값 설정
    AXT_RT_CNT_INVALID_USE                      = 3307,     // CNT 함수 사용못함
    
    AXT_RT_MOTION_OPEN_ERROR                    = 4001,     // 모션 라이브러리 Open 실패
    AXT_RT_MOTION_NOT_MODULE                    = 4051,     // 시스템에 장착된 모션 모듈이 없음
    AXT_RT_MOTION_NOT_INTERRUPT                 = 4052,     // 인터럽트 결과 읽기 실패
    AXT_RT_MOTION_NOT_INITIAL_AXIS_NO           = 4053,     // 해당 축 모션 초기화 실패
    AXT_RT_MOTION_NOT_IN_CONT_INTERPOL          = 4054,     // 연속 보간 구동 중이 아닌 상태에서 연속보간 중지 명령을 수행 하였음
    AXT_RT_MOTION_NOT_PARA_READ                 = 4055,     // 원점 구동 설정 파라미터 로드 실패
    AXT_RT_MOTION_INVALID_AXIS_NO               = 4101,     // 해당 축이 존재하지 않음
    AXT_RT_MOTION_INVALID_METHOD                = 4102,     // 해당 축 구동에 필요한 설정이 잘못됨
    AXT_RT_MOTION_INVALID_USE                   = 4103,     // 'uUse' 인자값이 잘못 설정됨
    AXT_RT_MOTION_INVALID_LEVEL                 = 4104,     // 'uLevel' 인자값이 잘못 설정됨
    AXT_RT_MOTION_INVALID_BIT_NO                = 4105,     // 범용 입출력 해당 비트가 잘못 설정됨
    AXT_RT_MOTION_INVALID_STOP_MODE             = 4106,     // 모션 정지 모드 설정값이 잘못됨
    AXT_RT_MOTION_INVALID_TRIGGER_MODE          = 4107,     // 트리거 설정 모드가 잘못 설정됨
    AXT_RT_MOTION_INVALID_TRIGGER_LEVEL         = 4108,     // 트리거 출력 레벨 설정이 잘못됨
    AXT_RT_MOTION_INVALID_SELECTION             = 4109,     // 'uSelection' 인자가 COMMAND 또는 ACTUAL 이외의 값으로 설정되어 있음
    AXT_RT_MOTION_INVALID_TIME                  = 4110,     // Trigger 출력 시간값이 잘못 설정되어 있음
    AXT_RT_MOTION_INVALID_FILE_LOAD             = 4111,     // 모션 설정값이 저장된 파일이 로드가 안됨
    AXT_RT_MOTION_INVALID_FILE_SAVE             = 4112,     // 모션 설정값을 저장하는 파일 저장에 실패함
    AXT_RT_MOTION_INVALID_VELOCITY              = 4113,     // 모션 구동 속도값이 0으로 설정되어 모션 에러 발생
    AXT_RT_MOTION_INVALID_ACCELTIME             = 4114,     // 모션 구동 가속 시간값이 0으로 설정되어 모션 에러 발생
    AXT_RT_MOTION_INVALID_PULSE_VALUE           = 4115,     // 모션 단위 설정 시 입력 펄스값이 0보다 작은값으로 설정됨
    AXT_RT_MOTION_INVALID_NODE_NUMBER           = 4116,     // 위치나 속도 오버라이드 함수가 모션 정지 중에 실햄됨
    AXT_RT_MOTION_INVALID_TARGET                = 4117,     // 다축 모션 정지 원인에 관한 플래그를 반환한다.
    
    AXT_RT_MOTION_ERROR_IN_NONMOTION            = 4151,     // 모션 구동중이어야 되는데 모션 구동중이 아닐 때
    AXT_RT_MOTION_ERROR_IN_MOTION               = 4152,     // 모션 구동 중에 다른 모션 구동 함수를 실행함
    AXT_RT_MOTION_ERROR                         = 4153,     // 다축 구동 정지 함수 실행 중 에러 발생함
    AXT_RT_MOTION_ERROR_GANTRY_ENABLE           = 4154,     // 겐트리 enable이 되어있을 때
    AXT_RT_MOTION_ERROR_GANTRY_AXIS             = 4155,     // 겐트리 축이 마스터채널(축) 번호(0 ~ (최대축수 - 1))가 잘못 들어갔을 때
    AXT_RT_MOTION_ERROR_MASTER_SERVOON          = 4156,     // 마스터 축 서보온이 안되어있을 때
    AXT_RT_MOTION_ERROR_SLAVE_SERVOON           = 4157,     // 슬레이브 축 서보온이 안되어있을 때
    AXT_RT_MOTION_INVALID_POSITION              = 4158,     // 유효한 위치에 없을 때          
    AXT_RT_ERROR_NOT_SAME_MODULE                = 4159,     // 똑 같은 모듈내에 있지 않을경우
    AXT_RT_ERROR_NOT_SAME_BOARD                 = 4160,     // 똑 같은 보드내에 있지 아닐경우
    AXT_RT_ERROR_NOT_SAME_PRODUCT               = 4161,     // 제품이 서로 다를경우
    AXT_RT_NOT_CAPTURED                         = 4162,     // 위치가 저장되지 않을 때
    AXT_RT_ERROR_NOT_SAME_IC                    = 4163,     // 같은 칩내에 존재하지않을 때
    AXT_RT_ERROR_NOT_GEARMODE                   = 4164,     // 기어모드로 변환이 안될 때
    AXT_ERROR_CONTI_INVALID_AXIS_NO             = 4165,     // 연속보간 축맵핑 시 유효한 축이 아닐 때
    AXT_ERROR_CONTI_INVALID_MAP_NO              = 4166,     // 연속보간 맵핑 시 유효한 맵핑 번호가 아닐 때
    AXT_ERROR_CONTI_EMPTY_MAP_NO                = 4167,     // 연속보간 맵핑 번호가 비워 있을 때
    AXT_RT_MOTION_ERROR_CACULATION              = 4168,     // 계산상의 오차가 발생했을 때
    AXT_RT_ERROR_MOVE_SENSOR_CHECK              = 4169,     // 연속보간 구동전 에러센서가(Alarm, EMG, Limit등) 감지된경우 
    
    AXT_ERROR_HELICAL_INVALID_AXIS_NO           = 4170,     // 헬리컬 축 맵핑 시 유효한 축이 아닐 때
    AXT_ERROR_HELICAL_INVALID_MAP_NO            = 4171,     // 헬리컬 맵핑 시 유효한 맵핑 번호가 아닐  때 
    AXT_ERROR_HELICAL_EMPTY_MAP_NO              = 4172,     // 헬리컬 멥핑 번호가 비워 있을 때
    
    AXT_ERROR_SPLINE_INVALID_AXIS_NO            = 4180,     // 스플라인 축 맵핑 시 유효한 축이 아닐 때
    AXT_ERROR_SPLINE_INVALID_MAP_NO             = 4181,     // 스플라인 맵핑 시 유효한 맵핑 번호가 아닐 때
    AXT_ERROR_SPLINE_EMPTY_MAP_NO               = 4182,     // 스플라인 맵핑 번호가 비워있을 때
    AXT_ERROR_SPLINE_NUM_ERROR                  = 4183,     // 스플라인 점숫자가 부적당할 때
    AXT_RT_MOTION_INTERPOL_VALUE                = 4184,     // 보간할 때 입력 값이 잘못넣어졌을 때
    AXT_RT_ERROR_NOT_CONTIBEGIN                 = 4185,     // 연속보간 할 때 CONTIBEGIN함수를 호출하지 않을 때
    AXT_RT_ERROR_NOT_CONTIEND                   = 4186,     // 연속보간 할 때 CONTIEND함수를 호출하지 않을 때
    
    AXT_RT_MOTION_HOME_SEARCHING                = 4201,     // 홈을 찾고 있는 중일 때 다른 모션 함수들을 사용할 때
    AXT_RT_MOTION_HOME_ERROR_SEARCHING          = 4202,     // 홈을 찾고 있는 중일 때 외부에서 사용자나 혹은 어떤것에 의한  강제로 정지당할 때
    AXT_RT_MOTION_HOME_ERROR_START              = 4203,     // 초기화 문제로 홈시작 불가할 때
    AXT_RT_MOTION_HOME_ERROR_GANTRY             = 4204,     // 홈을 찾고 있는 중일 때 겐트리 enable 불가할 때
    
    AXT_RT_MOTION_READ_ALARM_WAITING            = 4210,     // 서보팩으로부터 알람코드 결과를 기다리는 중
    AXT_RT_MOTION_READ_ALARM_NO_REQUEST         = 4211,     // 서보팩에 알람코드 반환 명령이 내려지지않았을 때
    AXT_RT_MOTION_READ_ALARM_TIMEOUT            = 4212,     // 서보팩 알람읽기 시간초과 했을때(1sec이상)
    AXT_RT_MOTION_READ_ALARM_FAILED             = 4213,     // 서보팩 알람읽기에 실패 했을 때
    AXT_RT_MOTION_READ_ALARM_UNKNOWN            = 4220,     // 알람코드가 알수없는 코드일 때
    AXT_RT_MOTION_READ_ALARM_FILES              = 4221,     // 알람정보 파일이 정해진위치에 존재하지 않을 때 
    
    AXT_RT_MOTION_POSITION_OUTOFBOUND           = 4251,     // 설정한 위치값이 설정 최대값보다 크거나 최소값보다 작은값임 
    AXT_RT_MOTION_PROFILE_INVALID               = 4252,     // 구동 속도 프로파일 설정이 잘못됨
    AXT_RT_MOTION_VELOCITY_OUTOFBOUND           = 4253,     // 구동 속도값이 최대값보다 크게 설정됨
    AXT_RT_MOTION_MOVE_UNIT_IS_ZERO             = 4254,     // 구동 단위값이 0으로 설정됨
    AXT_RT_MOTION_SETTING_ERROR                 = 4255,     // 속도, 가속도, 저크, 프로파일 설정이 잘못됨
    AXT_RT_MOTION_IN_CONT_INTERPOL              = 4256,     // 연속 보간 구동 중 구동 시작 또는 재시작 함수를 실행하였음
    AXT_RT_MOTION_DISABLE_TRIGGER               = 4257,     // 트리거 출력이 Disable 상태임 
    AXT_RT_MOTION_INVALID_CONT_INDEX            = 4258,     // 연속 보간 Index값 설정이 잘못됨
    AXT_RT_MOTION_CONT_QUEUE_FULL               = 4259,     // 모션 칩의 연속 보간 큐가 Full 상태임
    AXT_RT_PROTECTED_DURING_SERVOON             = 4260,     // 서보 온 되어 있는 상태에서 사용 못 함
    AXT_RT_HW_ACCESS_ERROR                      = 4261,     // 메모리 Read / Write 실패 

    AXT_RT_HW_DPRAM_CMD_WRITE_ERROR_LV1         = 4262,     // DPRAM Comamnd Write 실패 Level1
    AXT_RT_HW_DPRAM_CMD_WRITE_ERROR_LV2         = 4263,     // DPRAM Comamnd Write 실패 Level2
    AXT_RT_HW_DPRAM_CMD_WRITE_ERROR_LV3         = 4264,     // DPRAM Comamnd Write 실패 Level3
    AXT_RT_HW_DPRAM_CMD_READ_ERROR_LV1          = 4265,     // DPRAM Comamnd Read 실패 Level1
    AXT_RT_HW_DPRAM_CMD_READ_ERROR_LV2          = 4266,     // DPRAM Comamnd Read 실패 Level2
    AXT_RT_HW_DPRAM_CMD_READ_ERROR_LV3          = 4267,     // DPRAM Comamnd Read 실패 Level3

    AXT_RT_COMPENSATION_SET_PARAM_FIRST         = 4300,     // 보정 파라미터 중 첫번째 값이 잘못 설정되었음
    AXT_RT_COMPENSATION_NOT_INIT                = 4301,     // 보정테이블 기능 초기화 되지않음
    AXT_RT_COMPENSATION_POS_OUTOFBOUND          = 4302,     // 위치 값이 범위내에 존재하지 않음
    AXT_RT_COMPENSATION_BACKLASH_NOT_INIT       = 4303,     // 백래쉬 보정기능 초기화 되지않음
    AXT_RT_COMPENSATION_INVALID_ENTRY           = 4304,     //

    AXT_RT_SEQ_NOT_IN_SERVICE                   = 4400,     // 순차 구동 함수 실행 중 자원 할당 실패
    AXT_ERROR_SEQ_INVALID_MAP_NO                = 4401,     // 순차 구동 함수 실행 중 맵핑 번호 이상.
    AXT_ERROR_INVALID_AXIS_NO                   = 4402,     // 함수 설정 인자중 축번호 이상.
    AXT_RT_ERROR_NOT_SEQ_NODE_BEGIN             = 4403,     // 순차 구동 노드 입력 시작 함수를 호출하지 않음.
    AXT_RT_ERROR_NOT_SEQ_NODE_END               = 4404,     // 순차 구동 노드 입력 종료 함수를 호출하지 않음.
    AXT_RT_ERROR_NO_NODE                        = 4405,     // 순차 구동 노드 입력이 없음.
    AXT_RT_ERROR_SEQ_STOP_TIMEOUT               = 4406,

    AXT_RT_M3_COMMUNICATION_FAILED              = 4500,    // ML3 통신 기준, 통신 실패
    AXT_RT_MOTION_ONE_OF_AXES_IS_NOT_M3         = 4501,    // ML3 통신 기준, 구성된 ML3 노드 중에서 모션 노드 없음 
    AXT_RT_MOTION_BIGGER_VEL_THEN_MAX_VEL       = 4502,    // ML3 통신 기준, 지정된 축의 설정된 최대 속도보다 큼
    AXT_RT_MOTION_SMALLER_VEL_THEN_MAX_VEL      = 4503,    // ML3 통신 기준, 지정된 축의 설정된 최대 속도보다 작음
    AXT_RT_MOTION_ACCEL_MUST_BIGGER_THEN_ZERO   = 4504,    // ML3 통신 기준, 지정된 축의 설정된 가속도가 0보다 큼
    AXT_RT_MOTION_SMALL_ACCEL_WITH_UNIT_PULSE   = 4505,    // ML3 통신 기준, UnitPulse가 적용된 가속도가 0보다 큼
    AXT_RT_MOTION_INVALID_INPUT_ACCEL           = 4506,    // ML3 통신 기준, 지정된 축의 가속도 입력이 잘못됨
    AXT_RT_MOTION_SMALL_DECEL_WITH_UNIT_PULSE   = 4507,    // ML3 통신 기준, UnitPulse가 적용된 감속도가 0보다 큼
    AXT_RT_MOTION_INVALID_INPUT_DECEL           = 4508,    // ML3 통신 기준, 지정된 축의 감속도 입력이 잘못됨
    AXT_RT_MOTION_SAME_START_AND_CENTER_POS     = 4509,    // ML3 통신 기준, 원호보간의 시작점과 중심점이 같음
    AXT_RT_MOTION_INVALID_JERK                  = 4510,    // ML3 통신 기준, 지정된 축의 저크 입력이 잘못됨
    AXT_RT_MOTION_INVALID_INPUT_VALUE           = 4511,    // ML3 통신 기준, 지정된 축의 입력값이 잘못됨
    AXT_RT_MOTION_NOT_SUPPORT_PROFILE           = 4512,    // ML3 통신 기준, 제공되지 않는 속도 프로파일임
    AXT_RT_MOTION_INPOS_UNUSED                  = 4513,    // ML3 통신 기준, 인포지션 사용하지 않음
    AXT_RT_MOTION_AXIS_IN_SLAVE_STATE           = 4514,    // ML3 통신 기준, 지정된 축이 슬레이브 상태가 아님
    AXT_RT_MOTION_AXES_ARE_NOT_SAME_BOARD       = 4515,    // ML3 통신 기준, 지정된 축들이 같은 보드 내에 있지 않음
    AXT_RT_MOTION_ERROR_IN_ALARM                = 4516,    // ML3 통신 기준, 지정된 축이 알람 상태임
    AXT_RT_MOTION_ERROR_IN_EMGN                 = 4517,    // ML3 통신 기준, 지정된 축이 비상정지 상태임
    AXT_RT_MOTION_CAN_NOT_CHANGE_COORD_NO       = 4518,    // ML3 통신 기준, 코디네이터 넘버 변환 불가임
    AXT_RT_MOTION_INVALID_INTERNAL_RADIOUS      = 4519,    // ML3 통신 기준, 원호보간의 X, Y축 반지름 불일치
    AXT_RT_MOTION_CONTI_QUEUE_FULL              = 4521,    // ML3 통신 기준, 보간의 큐가 가득 참
    AXT_RT_MOTION_SAME_START_AND_END_POSITION   = 4522,    // ML3 통신 기준, 원호보간의 시작점과 종료점이 같음
    AXT_RT_MOTION_INVALID_ANGLE                 = 4523,    // ML3 통신 기준, 원호보간의 각도가 360도 초과됨
    AXT_RT_MOTION_CONTI_QUEUE_EMPTY             = 4524,    // ML3 통신 기준, 보간의 큐가 비어있음
    AXT_RT_MOTION_ERROR_GEAR_ENABLE             = 4525,    // ML3 통신 기준, 지정된 축이 이미 링크 설정 상태임
    AXT_RT_MOTION_ERROR_GEAR_AXIS               = 4526,    // ML3 통신 기준, 지정된 축이 링크축이 아님
    AXT_RT_MOTION_ERROR_NO_GANTRY_ENABLE        = 4527,    // ML3 통신 기준, 지정된 축이 겐트리 설정 상태가 아님
    AXT_RT_MOTION_ERROR_NO_GEAR_ENABLE          = 4528,    // ML3 통신 기준, 지정된 축이 링크 설정 상태가 아님
    AXT_RT_MOTION_ERROR_GANTRY_ENABLE_FULL      = 4529,    // ML3 통신 기준, 겐트리 설정 가득참
    AXT_RT_MOTION_ERROR_GEAR_ENABLE_FULL        = 4530,    // ML3 통신 기준, 링크 설정 가득참
    AXT_RT_MOTION_ERROR_NO_GANTRY_SLAVE         = 4531,    // ML3 통신 기준, 지정된 축이 겐트리 슬레이브 설정상태가 아님
    AXT_RT_MOTION_ERROR_NO_GEAR_SLAVE           = 4532,    // ML3 통신 기준, 지정된 축이 링크 슬레이브 설정상태가 아님
    AXT_RT_MOTION_ERROR_MASTER_SLAVE_SAME       = 4533,    // ML3 통신 기준, 마스터축과 슬레이브 축이 동일함
    AXT_RT_MOTION_NOT_SUPPORT_HOMESIGNAL        = 4534,    // ML3 통신 기준, 지정된 축의 홈신호는 지원되지 않음
    AXT_RT_MOTION_ERROR_NOT_SYNC_CONNECT        = 4535,    // ML3 통신 기준, 지정된 축이 싱크 연결 상태가 아님
    AXT_RT_MOTION_OVERFLOW_POSITION             = 4536,    // ML3 통신 기준, 지정된 축에 대한 구동 위치값이 오버플로우임
    AXT_RT_MOTION_ERROR_INVALID_CONTIMAPAXIS    = 4537,    // ML3 통신 기준, 보간작업을 위한 지정된 좌표계 축맵핑이 없음
    AXT_RT_MOTION_ERROR_INVALID_CONTIMAPSIZE    = 4538,    // ML3 통신 기준, 보간작업을 ㅜ이한 지정된 좌표계 축맵핑 축사이즈가 잘못됨
    AXT_RT_MOTION_ERROR_IN_SERVO_OFF            = 4539,    // ML3 통신 기준, 지정된 축이 서보 OFF되어 있음
    AXT_RT_MOTION_ERROR_POSITIVE_LIMIT          = 4540,    // ML3 통신 기준, 지정된 축이 (+)리밋 ON되어 있음
    AXT_RT_MOTION_ERROR_NEGATIVE_LIMIT          = 4541,    // ML3 통신 기준, 지정된 축이 (-)리밋 ON되어 있음
    AXT_RT_MOTION_ERROR_OVERFLOW_SWPROFILE_NUM  = 4542,    // ML3 통신 기준, 지정된 축들에 대한 지원 프로파일 개수가 오버플로우됨
    AXT_RT_PROTECTED_DURING_INMOTION            = 4543,    // in_motion 되어 있는 상태에서 사용 못 함

    AXT_RT_DATA_FLASH_NOT_EXIST                 = 5000,
    AXT_RT_DATA_FLASH_BUSY                      = 5001
}

public enum AXT_BOOLEAN:uint
{
    FALSE,
    TRUE
}

public enum AXT_LOG_LEVEL:uint
{
    LEVEL_NONE,
    LEVEL_ERROR,
    LEVEL_RUNSTOP,
    LEVEL_FUNCTION
}

public enum AXT_EXISTENCE:uint
{
    STATUS_NOTEXIST,
    STATUS_EXIST
}

public enum AXT_USE:uint
{
    DISABLE,
    ENABLE
}

public enum AXT_AIO_TRIGGER_MODE:uint
{
    DISABLE_MODE    = 0,
    NORMAL_MODE     = 1,
    TIMER_MODE      = 2,
    EXTERNAL_MODE   = 3
}

public enum AXT_AIO_FULL_MODE:uint
{
    NEW_DATA_KEEP,
    CURR_DATA_KEEP
}

public enum AXT_AIO_EVENT_MASK:uint
{
    DATA_EMPTY      = 0x01,
    DATA_MANY       = 0x02,
    DATA_SMAL       = 0x04,
    DATA_FULL       = 0x08
}

public enum AXT_AIO_INTERRUPT_MASK:uint
{
    ADC_DONE        = 0x01,
    SCAN_END        = 0x02,
    FIFO_HALF_FULL  = 0x02,
    NO_SIGNAL       = 0x03
}

public enum AXT_AIO_EVENT_MODE:uint
{
    AIO_EVENT_DATA_RESET     = 0x00,
    AIO_EVENT_DATA_UPPER     = 0x01,
    AIO_EVENT_DATA_LOWER     = 0x02,
    AIO_EVENT_DATA_FULL      = 0x03,
    AIO_EVENT_DATA_EMPTY     = 0x04
}

public enum AXT_AIO_FIFO_STATUS:uint
{
    FIFO_DATA_EXIST   = 0,
    FIFO_DATA_EMPTY   = 1,
    FIFO_DATA_HALF    = 2,
    FIFO_DATA_FULL    = 6
}

public enum AXT_AIO_EXTERNAL_STATUS:uint
{
    EXTERNAL_DATA_DONE      = 0,
    EXTERNAL_DATA_FINE      = 1,
    EXTERNAL_DATA_HALF      = 2,
    EXTERNAL_DATA_FULL      = 3,
    EXTERNAL_COMPLETE       = 4
}

public enum AXT_DIO_EDGE:uint
{
    DOWN_EDGE,
    UP_EDGE
}

public enum AXT_DIO_STATE:uint
{
    OFF_STATE,
    ON_STATE
}

public enum AXT_MOTION_STOPMODE:uint
{
    EMERGENCY_STOP,
    SLOWDOWN_STOP
}

public enum AXT_MOTION_EDGE:uint
{    
    SIGNAL_DOWN_EDGE,
    SIGNAL_UP_EDGE,
    SIGNAL_LOW_LEVEL,
    SIGNAL_HIGH_LEVEL
}

public enum AXT_MOTION_SELECTION:uint
{
    COMMAND,
    ACTUAL
}

public enum AXT_MOTION_TRIGGER_MODE:uint
{
    PERIOD_MODE,
    ABS_POS_MODE
}

public enum AXT_MOTION_LEVEL_MODE:uint
{
    LOW,
    HIGH,
    UNUSED,
    USED
}

public enum AXT_MOTION_ABSREL:uint
{
    POS_ABS_MODE,
    POS_REL_MODE,
    POS_ABS_LONG_MODE
}

public enum AXT_MOTION_PROFILE_MODE:uint
{
    SYM_TRAPEZOIDE_MODE,
    ASYM_TRAPEZOIDE_MODE,
    QUASI_S_CURVE_MODE,
    SYM_S_CURVE_MODE,
    ASYM_S_CURVE_MODE
}

public enum AXT_MOTION_SIGNAL_LEVEL:uint
{
    INACTIVE,
    ACTIVE
}

public enum AXT_MOTION_HOME_RESULT:uint
{
    HOME_RESERVED       = 0x00,    // ML3
    HOME_SUCCESS        = 0x01,    // 원점 검색 완료
    HOME_SEARCHING      = 0x02,    // 원점 검색 중
    HOME_ERR_GNT_RANGE  = 0x10,    // 갠트리 원점 검색 기준, 두 축 사이의 설정이상 오차 발생
    HOME_ERR_USER_BREAK = 0x11,    // 원점 검색 사용자 중지시
    HOME_ERR_VELOCITY   = 0x12,    // 원점 검색 속도 이상 에러 발생
    HOME_ERR_AMP_FAULT  = 0x13,    // 서보팩 알람 발생 에러
    HOME_ERR_NEG_LIMIT  = 0x14,    // (-)방향 구동중 (+)리미트 센서 감지 에러
    HOME_ERR_POS_LIMIT  = 0x15,    // (+)방향 구동중 (-)리미트 센서 감지 에러
    HOME_ERR_NOT_DETECT = 0x16,    // 지정한 신호 검출하지 못 할 경우 에러
    HOME_ERR_SETTING    = 0x17,    // 사용자 설정 파라미터가 구동시 제약 조건 발생시
    HOME_ERR_SERVO_OFF  = 0x18,    // 서보 Off일경우
    HOME_ERR_TIMEOUT    = 0x20,    // 지정된 시간 초과 발생으로 오류 발생 
    HOME_ERR_FUNCALL    = 0x30,    // 함수 호출 실패
    HOME_ERR_COUPLING   = 0x40,    // Gantry Master to Slave Over Distance protection
    HOME_ERR_UNKNOWN    = 0xFF     // 미지정 에러
}

public enum AXT_MOTION_UNIV_INPUT:uint
{
    UIO_INP0,
    UIO_INP1,
    UIO_INP2,
    UIO_INP3,
    UIO_INP4,
    UIO_INP5
}

public enum AXT_MOTION_UNIV_OUTPUT:uint
{
    UIO_OUT0,
    UIO_OUT1,
    UIO_OUT2,
    UIO_OUT3,
    UIO_OUT4,
    UIO_OUT5
}

public enum AXT_MOTION_DETECT_DOWN_START_POINT:uint
{
    AutoDetect,
    RestPulse
}

public enum AXT_MOTION_PULSE_OUTPUT:uint
{
    OneHighLowHigh,                // 1펄스 방식, PULSE(Active High), 정방향(DIR=Low)  / 역방향(DIR=High)
    OneHighHighLow,                 // 1펄스 방식, PULSE(Active High), 정방향(DIR=High) / 역방향(DIR=Low)
    OneLowLowHigh,                  // 1펄스 방식, PULSE(Active Low),  정방향(DIR=Low)  / 역방향(DIR=High)
    OneLowHighLow,                  // 1펄스 방식, PULSE(Active Low),  정방향(DIR=High) / 역방향(DIR=Low)
    TwoCcwCwHigh,                   // 2펄스 방식, PULSE(CCW:역방향),  DIR(CW:정방향),  Active High     
    TwoCcwCwLow,                    // 2펄스 방식, PULSE(CCW:역방향),  DIR(CW:정방향),  Active Low     
    TwoCwCcwHigh,                   // 2펄스 방식, PULSE(CW:정방향),   DIR(CCW:역방향), Active High
    TwoCwCcwLow,                    // 2펄스 방식, PULSE(CW:정방향),   DIR(CCW:역방향), Active Low
    TwoPhase,                       // 2상(90' 위상차),  PULSE lead DIR(CW: 정방향), PULSE lag DIR(CCW:역방향)
    TwoPhaseReverse                 // 2상(90' 위상차),  PULSE lead DIR(CCW: 정방향), PULSE lag DIR(CW:역방향)
}

public enum AXT_MOTION_EXTERNAL_COUNTER_INPUT:uint
{
    ObverseUpDownMode,              // 정방향 Up/Down
    ObverseSqr1Mode,                // 정방향 1체배
    ObverseSqr2Mode,                // 정방향 2체배
    ObverseSqr4Mode,                // 정방향 4체배
    ReverseUpDownMode,              // 역방향 Up/Down
    ReverseSqr1Mode,                // 역방향 1체배
    ReverseSqr2Mode,                // 역방향 2체배
    ReverseSqr4Mode                 // 역방향 4체배
}

public enum AXT_MOTION_ACC_UNIT:uint
{
    UNIT_SEC2 = 0x0,                // unit/sec2
    SEC       = 0x1                 // sec
}

public enum AXT_MOTION_MOVE_DIR:uint
{
    DIR_CCW   = 0x0,                // 반시계방향
    DIR_CW    = 0x1                 // 시계방향
}

public enum AXT_MOTION_RADIUS_DISTANCE:uint
{
    SHORT_DISTANCE  = 0x0,          // 짧은 거리의 원호 이동 
    LONG_DISTANCE   = 0x1           // 긴 거리의 원호 이동 
}

public enum AXT_MOTION_POS_TYPE:uint
{
    POSITION_LIMIT   = 0x0,         // 전체 영역사용
    POSITION_BOUND   = 0x1          // Pos 지정 사용
}

public enum AXT_MOTION_INTERPOLATION_AXIS:uint
{
    INTERPOLATION_AXIS2   = 0x2,    // 2축을 보간으로 사용할 때
    INTERPOLATION_AXIS3   = 0x3,    // 3축을 보간으로 사용할 때
    INTERPOLATION_AXIS4   = 0x4     // 4축을 보간으로 사용할 때
}

public enum AXT_MOTION_CONTISTART_NODE:uint
{
    CONTI_NODE_VELOCITY                    = 0x0,           // 속도 지정 보간 모드
    CONTI_NODE_MANUAL                      = 0x1,           // 노드 가감속 보간 모드
    CONTI_NODE_AUTO                        = 0x2            // 자동 가감속 보간 모드
}

public enum AXT_MOTION_HOME_DETECT:uint
{
    PosEndLimit                            = 0x0,           // +Elm(End limit) +방향 리미트 센서 신호
    NegEndLimit                            = 0x1,           // -Elm(End limit) -방향 리미트 센서 신호
    PosSloLimit                            = 0x2,           // +Slm(Slow Down limit) 신호 - 사용하지 않음
    NegSloLimit                            = 0x3,           // -Slm(Slow Down limit) 신호 - 사용하지 않음
    HomeSensor                             = 0x4,           // IN0(ORG)  원점 센서 신호
    EncodZPhase                            = 0x5,           // IN1(Z상)  Encoder Z상 신호
    UniInput02                             = 0x6,           // IN2(범용) 범용 입력 2번 신호
    UniInput03                             = 0x7,           // IN3(범용) 범용 입력 3번 신호
    UniInput04                             = 0x8,           // IN4(범용) 범용 입력 4번 신호
    UniInput05                             = 0x9            // IN5(범용) 범용 입력 5번 신호
}

public enum AXT_MOTION_INPUT_FILTER_SIGNAL_DEF:uint
{
    END_LIMIT                              = 0x10,          // 위치클리어 사용않함, 잔여펄스 클리어 사용 안함
    INP_ALARM                              = 0x11,          // 위치클리어 사용함, 잔여펄스 클리어 사용 안함
    UIN_00_01                              = 0x12,          // 위치클리어 사용안함, 잔여펄스 클리어 사용함
    UIN_02_04                              = 0x13           // 위치클리어 사용함, 잔여펄스 클리어 사용함
}

public enum AXT_MOTION_MPG_INPUT_METHOD:uint
{
    MPG_DIFF_ONE_PHASE                     = 0x0,           // MPG 입력 방식 One Phase
    MPG_DIFF_TWO_PHASE_1X                  = 0x1,           // MPG 입력 방식 TwoPhase1
    MPG_DIFF_TWO_PHASE_2X                  = 0x2,           // MPG 입력 방식 TwoPhase2
    MPG_DIFF_TWO_PHASE_4X                  = 0x3,           // MPG 입력 방식 TwoPhase4
    MPG_LEVEL_ONE_PHASE                    = 0x4,           // MPG 입력 방식 Level One Phase
    MPG_LEVEL_TWO_PHASE_1X                 = 0x5,           // MPG 입력 방식 Level Two Phase1
    MPG_LEVEL_TWO_PHASE_2X                 = 0x6,           // MPG 입력 방식 Level Two Phase2
    MPG_LEVEL_TWO_PHASE_4X                 = 0x7            // MPG 입력 방식 Level Two Phase4
}

public enum AXT_MOTION_SENSOR_INPUT_METHOD:uint
{
    SENSOR_METHOD1                         = 0x0,           // 일반 구동
    SENSOR_METHOD2                         = 0x1,           // 센서 신호 검출 전은 저속 구동. 신호 검출 후 일반 구동
    SENSOR_METHOD3                         = 0x2            // 저속 구동
}

public enum AXT_MOTION_HOME_CRC_SELECT:uint
{
    CRC_SELECT1                            = 0x0,           // 위치클리어 사용않함, 잔여펄스 클리어 사용 안함
    CRC_SELECT2                            = 0x1,           // 위치클리어 사용함, 잔여펄스 클리어 사용 안함
    CRC_SELECT3                            = 0x2,           // 위치클리어 사용안함, 잔여펄스 클리어 사용함
    CRC_SELECT4                            = 0x3            // 위치클리어 사용함, 잔여펄스 클리어 사용함
}

public enum AXT_MOTION_IPDETECT_DESTINATION_SIGNAL:uint
{
    PElmNegativeEdge                       = 0x0,           // +Elm(End limit) 하강 edge
    NElmNegativeEdge                       = 0x1,           // -Elm(End limit) 하강 edge
    PSlmNegativeEdge                       = 0x2,           // +Slm(Slowdown limit) 하강 edge
    NSlmNegativeEdge                       = 0x3,           // -Slm(Slowdown limit) 하강 edge
    In0DownEdge                            = 0x4,           // IN0(ORG) 하강 edge
    In1DownEdge                            = 0x5,           // IN1(Z상) 하강 edge
    In2DownEdge                            = 0x6,           // IN2(범용) 하강 edge
    In3DownEdge                            = 0x7,           // IN3(범용) 하강 edge
    PElmPositiveEdge                       = 0x8,           // +Elm(End limit) 상승 edge
    NElmPositiveEdge                       = 0x9,           // -Elm(End limit) 상승 edge
    PSlmPositiveEdge                       = 0xa,           // +Slm(Slowdown limit) 상승 edge
    NSlmPositiveEdge                       = 0xb,           // -Slm(Slowdown limit) 상승 edge
    In0UpEdge                              = 0xc,           // IN0(ORG) 상승 edge
    In1UpEdge                              = 0xd,           // IN1(Z상) 상승 edge
    In2UpEdge                              = 0xe,           // IN2(범용) 상승 edge
    In3UpEdge                              = 0xf            // IN3(범용) 상승 edge
}

public enum AXT_MOTION_IPEND_STATUS:uint
{
    IPEND_STATUS_SLM                       = 0x0001,        // Bit 0, limit 감속정지 신호 입력에 의한 종료
    IPEND_STATUS_ELM                       = 0x0002,        // Bit 1, limit 급정지 신호 입력에 의한 종료
    IPEND_STATUS_SSTOP_SIGNAL              = 0x0004,        // Bit 2, 감속 정지 신호 입력에 의한 종료
    IPEND_STATUS_ESTOP_SIGANL              = 0x0008,        // Bit 3, 급정지 신호 입력에 의한 종료
    IPEND_STATUS_SSTOP_COMMAND             = 0x0010,        // Bit 4, 감속 정지 명령에 의한 종료
    IPEND_STATUS_ESTOP_COMMAND             = 0x0020,        // Bit 5, 급정지 정지 명령에 의한 종료
    IPEND_STATUS_ALARM_SIGNAL              = 0x0040,        // Bit 6, Alarm 신호 입력에 희한 종료
    IPEND_STATUS_DATA_ERROR                = 0x0080,        // Bit 7, 데이터 설정 에러에 의한 종료
    IPEND_STATUS_DEVIATION_ERROR           = 0x0100,        // Bit 8, 탈조 에러에 의한 종료
    IPEND_STATUS_ORIGIN_DETECT             = 0x0200,        // Bit 9, 원점 검출에 의한 종료
    IPEND_STATUS_SIGNAL_DETECT             = 0x0400,        // Bit 10, 신호 검출에 의한 종료(Signal search-1/2 drive 종료)
    IPEND_STATUS_PRESET_PULSE_DRIVE        = 0x0800,        // Bit 11, Preset pulse drive 종료
    IPEND_STATUS_SENSOR_PULSE_DRIVE        = 0x1000,        // Bit 12, Sensor pulse drive 종료
    IPEND_STATUS_LIMIT                     = 0x2000,        // Bit 13, Limit 완전정지에 의한 종료
    IPEND_STATUS_SOFTLIMIT                 = 0x4000,        // Bit 14, Soft limit에 의한 종료
    IPEND_STATUS_INTERPOLATION_DRIVE       = 0x8000         // Bit 15, Soft limit에 의한 종료
}

public enum AXT_MOTION_IPDRIVE_STATUS:uint
{
    IPDRIVE_STATUS_BUSY                    = 0x00001,       // Bit 0, BUSY(드라이브 구동 중)
    IPDRIVE_STATUS_DOWN                    = 0x00002,       // Bit 1, DOWN(감속 중)
    IPDRIVE_STATUS_CONST                   = 0x00004,       // Bit 2, CONST(등속 중)
    IPDRIVE_STATUS_UP                      = 0x00008,       // Bit 3, UP(가속 중)
    IPDRIVE_STATUS_ICL                     = 0x00010,       // Bit 4, ICL(내부 위치 카운터 < 내부 위치 카운터 비교값)
    IPDRIVE_STATUS_ICG                     = 0x00020,       // Bit 5, ICG(내부 위치 카운터 > 내부 위치 카운터 비교값)
    IPDRIVE_STATUS_ECL                     = 0x00040,       // Bit 6, ECL(외부 위치 카운터 < 외부 위치 카운터 비교값)
    IPDRIVE_STATUS_ECG                     = 0x00080,       // Bit 7, ECG(외부 위치 카운터 > 외부 위치 카운터 비교값)
    IPDRIVE_STATUS_DRIVE_DIRECTION         = 0x00100,       // Bit 8, 드라이브 방향 신호(0=CW/1=CCW)
    IPDRIVE_STATUS_COMMAND_BUSY            = 0x00200,       // Bit 9, 명령어 수행중
    IPDRIVE_STATUS_PRESET_DRIVING          = 0x00400,       // Bit 10, Preset pulse drive 중
    IPDRIVE_STATUS_CONTINUOUS_DRIVING      = 0x00800,       // Bit 11, Continuouse speed drive 중
    IPDRIVE_STATUS_SIGNAL_SEARCH_DRIVING   = 0x01000,       // Bit 12, Signal search-1/2 drive 중
    IPDRIVE_STATUS_ORG_SEARCH_DRIVING      = 0x02000,       // Bit 13, 원점 검출 drive 중
    IPDRIVE_STATUS_MPG_DRIVING             = 0x04000,       // Bit 14, MPG drive 중
    IPDRIVE_STATUS_SENSOR_DRIVING          = 0x08000,       // Bit 15, Sensor positioning drive 중
    IPDRIVE_STATUS_L_C_INTERPOLATION       = 0x10000,       // Bit 16, 직선/원호 보간 중
    IPDRIVE_STATUS_PATTERN_INTERPOLATION   = 0x20000,       // Bit 17, 비트 패턴 보간 중
    IPDRIVE_STATUS_INTERRUPT_BANK1         = 0x40000,       // Bit 18, 인터럽트 bank1에서 발생
    IPDRIVE_STATUS_INTERRUPT_BANK2         = 0x80000        // Bit 19, 인터럽트 bank2에서 발생
}

public enum AXT_MOTION_IPINTERRUPT_BANK1:uint
{
    IPINTBANK1_DONTUSE                     = 0x00000000,    // INTERRUT DISABLED.
    IPINTBANK1_DRIVE_END                   = 0x00000001,    // Bit 0, Drive end(default value : 1).
    IPINTBANK1_ICG                         = 0x00000002,    // Bit 1, INCNT is greater than INCNTCMP.
    IPINTBANK1_ICE                         = 0x00000004,    // Bit 2, INCNT is equal with INCNTCMP.
    IPINTBANK1_ICL                         = 0x00000008,    // Bit 3, INCNT is less than INCNTCMP.
    IPINTBANK1_ECG                         = 0x00000010,    // Bit 4, EXCNT is greater than EXCNTCMP.
    IPINTBANK1_ECE                         = 0x00000020,    // Bit 5, EXCNT is equal with EXCNTCMP.
    IPINTBANK1_ECL                         = 0x00000040,    // Bit 6, EXCNT is less than EXCNTCMP.
    IPINTBANK1_SCRQEMPTY                   = 0x00000080,    // Bit 7, Script control queue is empty.
    IPINTBANK1_CAPRQEMPTY                  = 0x00000100,    // Bit 8, Caption result data queue is empty.
    IPINTBANK1_SCRREG1EXE                  = 0x00000200,    // Bit 9, Script control register-1 command is executed.
    IPINTBANK1_SCRREG2EXE                  = 0x00000400,    // Bit 10, Script control register-2 command is executed.
    IPINTBANK1_SCRREG3EXE                  = 0x00000800,    // Bit 11, Script control register-3 command is executed.
    IPINTBANK1_CAPREG1EXE                  = 0x00001000,    // Bit 12, Caption control register-1 command is executed.
    IPINTBANK1_CAPREG2EXE                  = 0x00002000,    // Bit 13, Caption control register-2 command is executed.
    IPINTBANK1_CAPREG3EXE                  = 0x00004000,    // Bit 14, Caption control register-3 command is executed.
    IPINTBANK1_INTGGENCMD                  = 0x00008000,    // Bit 15, Interrupt generation command is executed(0xFF)
    IPINTBANK1_DOWN                        = 0x00010000,    // Bit 16, At starting point for deceleration drive.
    IPINTBANK1_CONT                        = 0x00020000,    // Bit 17, At starting point for constant speed drive.
    IPINTBANK1_UP                          = 0x00040000,    // Bit 18, At starting point for acceleration drive.
    IPINTBANK1_SIGNALDETECTED              = 0x00080000,    // Bit 19, Signal assigned in MODE1 is detected.
    IPINTBANK1_SP23E                       = 0x00100000,    // Bit 20, Current speed is equal with rate change point RCP23.
    IPINTBANK1_SP12E                       = 0x00200000,    // Bit 21, Current speed is equal with rate change point RCP12.
    IPINTBANK1_SPE                         = 0x00400000,    // Bit 22, Current speed is equal with speed comparison data(SPDCMP).
    IPINTBANK1_INCEICM                     = 0x00800000,    // Bit 23, INTCNT(1'st counter) is equal with ICM(1'st count minus limit data)
    IPINTBANK1_SCRQEXE                     = 0x01000000,    // Bit 24, Script queue command is executed When SCRCONQ's 30 bit is '1'.
    IPINTBANK1_CAPQEXE                     = 0x02000000,    // Bit 25, Caption queue command is executed When CAPCONQ's 30 bit is '1'.
    IPINTBANK1_SLM                         = 0x04000000,    // Bit 26, NSLM/PSLM input signal is activated.
    IPINTBANK1_ELM                         = 0x08000000,    // Bit 27, NELM/PELM input signal is activated.
    IPINTBANK1_USERDEFINE1                 = 0x10000000,    // Bit 28, Selectable interrupt source 0(refer "0xFE" command).
    IPINTBANK1_USERDEFINE2                 = 0x20000000,    // Bit 29, Selectable interrupt source 1(refer "0xFE" command).
    IPINTBANK1_USERDEFINE3                 = 0x40000000,    // Bit 30, Selectable interrupt source 2(refer "0xFE" command).
    IPINTBANK1_USERDEFINE4                 = 0x80000000     // Bit 31, Selectable interrupt source 3(refer "0xFE" command).
}

public enum AXT_MOTION_IPINTERRUPT_BANK2:uint
{
    IPINTBANK2_DONTUSE                     = 0x00000000,    // INTERRUT DISABLED.
    IPINTBANK2_L_C_INP_Q_EMPTY             = 0x00000001,    // Bit 0, Linear/Circular interpolation parameter queue is empty.
    IPINTBANK2_P_INP_Q_EMPTY               = 0x00000002,    // Bit 1, Bit pattern interpolation queue is empty.
    IPINTBANK2_ALARM_ERROR                 = 0x00000004,    // Bit 2, Alarm input signal is activated.
    IPINTBANK2_INPOSITION                  = 0x00000008,    // Bit 3, Inposition input signal is activated.
    IPINTBANK2_MARK_SIGNAL_HIGH            = 0x00000010,    // Bit 4, Mark input signal is activated.
    IPINTBANK2_SSTOP_SIGNAL                = 0x00000020,    // Bit 5, SSTOP input signal is activated.
    IPINTBANK2_ESTOP_SIGNAL                = 0x00000040,    // Bit 6, ESTOP input signal is activated.
    IPINTBANK2_SYNC_ACTIVATED              = 0x00000080,    // Bit 7, SYNC input signal is activated.
    IPINTBANK2_TRIGGER_ENABLE              = 0x00000100,    // Bit 8, Trigger output is activated.
    IPINTBANK2_EXCNTCLR                    = 0x00000200,    // Bit 9, External(2'nd) counter is cleard by EXCNTCLR setting.
    IPINTBANK2_FSTCOMPARE_RESULT_BIT0      = 0x00000400,    // Bit 10, ALU1's compare result bit 0 is activated.
    IPINTBANK2_FSTCOMPARE_RESULT_BIT1      = 0x00000800,    // Bit 11, ALU1's compare result bit 1 is activated.
    IPINTBANK2_FSTCOMPARE_RESULT_BIT2      = 0x00001000,    // Bit 12, ALU1's compare result bit 2 is activated.
    IPINTBANK2_FSTCOMPARE_RESULT_BIT3      = 0x00002000,    // Bit 13, ALU1's compare result bit 3 is activated.
    IPINTBANK2_FSTCOMPARE_RESULT_BIT4      = 0x00004000,    // Bit 14, ALU1's compare result bit 4 is activated.
    IPINTBANK2_SNDCOMPARE_RESULT_BIT0      = 0x00008000,    // Bit 15, ALU2's compare result bit 0 is activated.
    IPINTBANK2_SNDCOMPARE_RESULT_BIT1      = 0x00010000,    // Bit 16, ALU2's compare result bit 1 is activated.
    IPINTBANK2_SNDCOMPARE_RESULT_BIT2      = 0x00020000,    // Bit 17, ALU2's compare result bit 2 is activated.
    IPINTBANK2_SNDCOMPARE_RESULT_BIT3      = 0x00040000,    // Bit 18, ALU2's compare result bit 3 is activated.
    IPINTBANK2_SNDCOMPARE_RESULT_BIT4      = 0x00080000,    // Bit 19, ALU2's compare result bit 4 is activated.
    IPINTBANK2_L_C_INP_Q_LESS_4            = 0x00100000,    // Bit 20, Linear/Circular interpolation parameter queue is less than 4.
    IPINTBANK2_P_INP_Q_LESS_4              = 0x00200000,    // Bit 21, Pattern interpolation parameter queue is less than 4.
    IPINTBANK2_XSYNC_ACTIVATED             = 0x00400000,    // Bit 22, X axis sync input signal is activated.
    IPINTBANK2_YSYNC_ACTIVATED             = 0x00800000,    // Bit 23, Y axis sync input siangl is activated.
    IPINTBANK2_P_INP_END_BY_END_PATTERN    = 0x01000000     // Bit 24, Bit pattern interpolation is terminated by end pattern.
    //IPINTBANK2_                          = 0x02000000,    // Bit 25, Don't care.
    //IPINTBANK2_                          = 0x04000000,    // Bit 26, Don't care.
    //IPINTBANK2_                          = 0x08000000,    // Bit 27, Don't care.
    //IPINTBANK2_                          = 0x10000000,    // Bit 28, Don't care.
    //IPINTBANK2_                          = 0x20000000,    // Bit 29, Don't care.
    //IPINTBANK2_                          = 0x40000000,    // Bit 30, Don't care.
    //IPINTBANK2_                          = 0x80000000     // Bit 31, Don't care.
}

public enum AXT_MOTION_IPMECHANICAL_SIGNAL:uint
{
    IPMECHANICAL_PELM_LEVEL                = 0x0001,        // Bit 0, +Limit 급정지 신호가 액티브 됨
    IPMECHANICAL_NELM_LEVEL                = 0x0002,        // Bit 1, -Limit 급정지 신호 액티브 됨
    IPMECHANICAL_PSLM_LEVEL                = 0x0004,        // Bit 2, +limit 감속정지 신호 액티브 됨
    IPMECHANICAL_NSLM_LEVEL                = 0x0008,        // Bit 3, -limit 감속정지 신호 액티브 됨
    IPMECHANICAL_ALARM_LEVEL               = 0x0010,        // Bit 4, Alarm 신호 액티브 됨
    IPMECHANICAL_INP_LEVEL                 = 0x0020,        // Bit 5, Inposition 신호 액티브 됨
    IPMECHANICAL_ENC_DOWN_LEVEL            = 0x0040,        // Bit 6, 엔코더 DOWN(B상) 신호 입력 Level
    IPMECHANICAL_ENC_UP_LEVEL              = 0x0080,        // Bit 7, 엔코더 UP(A상) 신호 입력 Level
    IPMECHANICAL_EXMP_LEVEL                = 0x0100,        // Bit 8, EXMP 신호 입력 Level
    IPMECHANICAL_EXPP_LEVEL                = 0x0200,        // Bit 9, EXPP 신호 입력 Level
    IPMECHANICAL_MARK_LEVEL                = 0x0400,        // Bit 10, MARK# 신호 액티브 됨
    IPMECHANICAL_SSTOP_LEVEL               = 0x0800,        // Bit 11, SSTOP 신호 액티브 됨
    IPMECHANICAL_ESTOP_LEVEL               = 0x1000,        // Bit 12, ESTOP 신호 액티브 됨
    IPMECHANICAL_SYNC_LEVEL                = 0x2000,        // Bit 13, SYNC 신호 입력 Level
    IPMECHANICAL_MODE8_16_LEVEL            = 0x4000         // Bit 14, MODE8_16 신호 입력 Level
}


public enum AXT_MOTION_QIDETECT_DESTINATION_SIGNAL:uint
{
    Signal_PosEndLimit                     = 0x0,           // +Elm(End limit) +방향 리미트 센서 신호
    Signal_NegEndLimit                     = 0x1,           // -Elm(End limit) -방향 리미트 센서 신호
    Signal_PosSloLimit                     = 0x2,           // +Slm(Slow Down limit) 신호 - 사용하지 않음
    Signal_NegSloLimit                     = 0x3,           // -Slm(Slow Down limit) 신호 - 사용하지 않음
    Signal_HomeSensor                      = 0x4,           // IN0(ORG)  원점 센서 신호
    Signal_EncodZPhase                     = 0x5,           // IN1(Z상)  Encoder Z상 신호
    Signal_UniInput02                      = 0x6,           // IN2(범용) 범용 입력 2번 신호
    Signal_UniInput03                      = 0x7            // IN3(범용) 범용 입력 3번 신호
}

public enum AXT_MOTION_QIMECHANICAL_SIGNAL:uint
{
    QIMECHANICAL_PELM_LEVEL                = 0x00001,       // Bit 0, +Limit 급정지 신호 현재 상태
    QIMECHANICAL_NELM_LEVEL                = 0x00002,       // Bit 1, -Limit 급정지 신호 현재 상태
    QIMECHANICAL_PSLM_LEVEL                = 0x00004,       // Bit 2, +limit 감속정지 현재 상태.
    QIMECHANICAL_NSLM_LEVEL                = 0x00008,       // Bit 3, -limit 감속정지 현재 상태
    QIMECHANICAL_ALARM_LEVEL               = 0x00010,       // Bit 4, Alarm 신호 신호 현재 상태
    QIMECHANICAL_INP_LEVEL                 = 0x00020,       // Bit 5, Inposition 신호 현재 상태
    QIMECHANICAL_ESTOP_LEVEL               = 0x00040,       // Bit 6, 비상 정지 신호(ESTOP) 현재 상태.
    QIMECHANICAL_ORG_LEVEL                 = 0x00080,       // Bit 7, 원점 신호 헌재 상태
    QIMECHANICAL_ZPHASE_LEVEL              = 0x00100,       // Bit 8, Z 상 입력 신호 현재 상태
    QIMECHANICAL_ECUP_LEVEL                = 0x00200,       // Bit 9, ECUP 터미널 신호 상태.
    QIMECHANICAL_ECDN_LEVEL                = 0x00400,       // Bit 10, ECDN 터미널 신호 상태.
    QIMECHANICAL_EXPP_LEVEL                = 0x00800,       // Bit 11, EXPP 터미널 신호 상태
    QIMECHANICAL_EXMP_LEVEL                = 0x01000,       // Bit 12, EXMP 터미널 신호 상태
    QIMECHANICAL_SQSTR1_LEVEL              = 0x02000,       // Bit 13, SQSTR1 터미널 신호 상태
    QIMECHANICAL_SQSTR2_LEVEL              = 0x04000,       // Bit 14, SQSTR2 터미널 신호 상태
    QIMECHANICAL_SQSTP1_LEVEL              = 0x08000,       // Bit 15, SQSTP1 터미널 신호 상태
    QIMECHANICAL_SQSTP2_LEVEL              = 0x10000,       // Bit 16, SQSTP2 터미널 신호 상태
    QIMECHANICAL_MODE_LEVEL                = 0x20000        // Bit 17, MODE 터미널 신호 상태.
}

public enum AXT_MOTION_QIEND_STATUS:uint
{
    QIEND_STATUS_0                         = 0x00000001,    // Bit 0, 정방향 리미트 신호(PELM)에 의한 종료
    QIEND_STATUS_1                         = 0x00000002,    // Bit 1, 역방향 리미트 신호(NELM)에 의한 종료
    QIEND_STATUS_2                         = 0x00000004,    // Bit 2, 정방향 부가 리미트 신호(PSLM)에 의한 구동 종료
    QIEND_STATUS_3                         = 0x00000008,    // Bit 3, 역방향 부가 리미트 신호(NSLM)에 의한 구동 종료
    QIEND_STATUS_4                         = 0x00000010,    // Bit 4, 정방향 소프트 리미트 급정지 기능에 의한 구동 종료
    QIEND_STATUS_5                         = 0x00000020,    // Bit 5, 역방향 소프트 리미트 급정지 기능에 의한 구동 종료
    QIEND_STATUS_6                         = 0x00000040,    // Bit 6, 정방향 소프트 리미트 감속정지 기능에 의한 구동 종료
    QIEND_STATUS_7                         = 0x00000080,    // Bit 7, 역방향 소프트 리미트 감속정지 기능에 의한 구동 종료
    QIEND_STATUS_8                         = 0x00000100,    // Bit 8, 서보 알람 기능에 의한 구동 종료.
    QIEND_STATUS_9                         = 0x00000200,    // Bit 9, 비상 정지 신호 입력에 의한 구동 종료.
    QIEND_STATUS_10                        = 0x00000400,    // Bit 10, 급 정지 명령에 의한 구동 종료.
    QIEND_STATUS_11                        = 0x00000800,    // Bit 11, 감속 정지 명령에 의한 구동 종료.
    QIEND_STATUS_12                        = 0x00001000,    // Bit 12, 전축 급정지 명령에 의한 구동 종료
    QIEND_STATUS_13                        = 0x00002000,    // Bit 13, 동기 정지 기능 #1(SQSTP1)에 의한 구동 종료.
    QIEND_STATUS_14                        = 0x00004000,    // Bit 14, 동기 정지 기능 #2(SQSTP2)에 의한 구동 종료.
    QIEND_STATUS_15                        = 0x00008000,    // Bit 15, 인코더 입력(ECUP,ECDN) 오류 발생
    QIEND_STATUS_16                        = 0x00010000,    // Bit 16, MPG 입력(EXPP,EXMP) 오류 발생
    QIEND_STATUS_17                        = 0x00020000,    // Bit 17, 원점 검색 성공 종료.
    QIEND_STATUS_18                        = 0x00040000,    // Bit 18, 신호 검색 성공 종료.
    QIEND_STATUS_19                        = 0x00080000,    // Bit 19, 보간 데이터 이상으로 구동 종료.
    QIEND_STATUS_20                        = 0x00100000,    // Bit 20, 비정상 구동 정지발생.
    QIEND_STATUS_21                        = 0x00200000,    // Bit 21, MPG 기능 블록 펄스 버퍼 오버플로우 발생
    QIEND_STATUS_22                        = 0x00400000,    // Bit 22, DON'CARE
    QIEND_STATUS_23                        = 0x00800000,    // Bit 23, DON'CARE
    QIEND_STATUS_24                        = 0x01000000,    // Bit 24, DON'CARE
    QIEND_STATUS_25                        = 0x02000000,    // Bit 25, DON'CARE
    QIEND_STATUS_26                        = 0x04000000,    // Bit 26, DON'CARE
    QIEND_STATUS_27                        = 0x08000000,    // Bit 27, DON'CARE
    QIEND_STATUS_28                        = 0x10000000,    // Bit 28, 현재/마지막 구동 드라이브 방향
    QIEND_STATUS_29                        = 0x20000000,    // Bit 29, 잔여 펄스 제거 신호 출력 중.
    QIEND_STATUS_30                        = 0x40000000,    // Bit 30, 비정상 구동 정지 원인 상태
    QIEND_STATUS_31                        = 0x80000000     // Bit 31, 보간 드라이브 데이타 오류 상태.
}

public enum AXT_MOTION_QIDRIVE_STATUS:uint
{
    QIDRIVE_STATUS_0                       = 0x0000001,     // Bit 0, BUSY(드라이브 구동 중)
    QIDRIVE_STATUS_1                       = 0x0000002,     // Bit 1, DOWN(감속 중)
    QIDRIVE_STATUS_2                       = 0x0000004,     // Bit 2, CONST(등속 중)
    QIDRIVE_STATUS_3                       = 0x0000008,     // Bit 3, UP(가속 중)
    QIDRIVE_STATUS_4                       = 0x0000010,     // Bit 4, 연속 드라이브 구동 중
    QIDRIVE_STATUS_5                       = 0x0000020,     // Bit 5, 지정 거리 드라이브 구동 중
    QIDRIVE_STATUS_6                       = 0x0000040,     // Bit 6, MPG 드라이브 구동 중
    QIDRIVE_STATUS_7                       = 0x0000080,     // Bit 7, 원점검색 드라이브 구동중
    QIDRIVE_STATUS_8                       = 0x0000100,     // Bit 8, 신호 검색 드라이브 구동 중
    QIDRIVE_STATUS_9                       = 0x0000200,     // Bit 9, 보간 드라이브 구동 중
    QIDRIVE_STATUS_10                      = 0x0000400,     // Bit 10, Slave 드라이브 구동중
    QIDRIVE_STATUS_11                      = 0x0000800,     // Bit 11, 현재 구동 드라이브 방향(보간 드라이브에서는 표시 정보 다름)
    QIDRIVE_STATUS_12                      = 0x0001000,     // Bit 12, 펄스 출력후 서보위치 완료 신호 대기중.
    QIDRIVE_STATUS_13                      = 0x0002000,     // Bit 13, 직선 보간 드라이브 구동중.
    QIDRIVE_STATUS_14                      = 0x0004000,     // Bit 14, 원호 보간 드라이브 구동중.
    QIDRIVE_STATUS_15                      = 0x0008000,     // Bit 15, 펄스 출력 중.
    QIDRIVE_STATUS_16                      = 0x0010000,     // Bit 16, 구동 예약 데이터 개수(처음)(0-7)
    QIDRIVE_STATUS_17                      = 0x0020000,     // Bit 17, 구동 예약 데이터 개수(중간)(0-7)
    QIDRIVE_STATUS_18                      = 0x0040000,     // Bit 18, 구동 예약 데이터 갯수(끝)(0-7)
    QIDRIVE_STATUS_19                      = 0x0080000,     // Bit 19, 구동 예약 Queue 비어 있음.
    QIDRIVE_STATUS_20                      = 0x0100000,     // Bit 20, 구동 예약 Queue 가득 ?
    QIDRIVE_STATUS_21                      = 0x0200000,     // Bit 21, 현재 구동 드라이브의 속도 모드(처음)
    QIDRIVE_STATUS_22                      = 0x0400000,     // Bit 22, 현재 구동 드라이브의 속도 모드(끝)
    QIDRIVE_STATUS_23                      = 0x0800000,     // Bit 23, MPG 버퍼 #1 Full
    QIDRIVE_STATUS_24                      = 0x1000000,     // Bit 24, MPG 버퍼 #2 Full
    QIDRIVE_STATUS_25                      = 0x2000000,     // Bit 25, MPG 버퍼 #3 Full
    QIDRIVE_STATUS_26                      = 0x4000000      // Bit 26, MPG 버퍼 데이터 OverFlow
}

public enum AXT_MOTION_QIINTERRUPT_BANK1:uint
{
    QIINTBANK1_DISABLE                     = 0x00000000,    // INTERRUT DISABLED.
    QIINTBANK1_0                           = 0x00000001,    // Bit 0,  인터럽트 발생 사용 설정된 구동 종료시.
    QIINTBANK1_1                           = 0x00000002,    // Bit 1,  구동 종료시
    QIINTBANK1_2                           = 0x00000004,    // Bit 2,  구동 시작시.
    QIINTBANK1_3                           = 0x00000008,    // Bit 3,  카운터 #1 < 비교기 #1 이벤트 발생
    QIINTBANK1_4                           = 0x00000010,    // Bit 4,  카운터 #1 = 비교기 #1 이벤트 발생
    QIINTBANK1_5                           = 0x00000020,    // Bit 5,  카운터 #1 > 비교기 #1 이벤트 발생
    QIINTBANK1_6                           = 0x00000040,    // Bit 6,  카운터 #2 < 비교기 #2 이벤트 발생
    QIINTBANK1_7                           = 0x00000080,    // Bit 7,  카운터 #2 = 비교기 #2 이벤트 발생
    QIINTBANK1_8                           = 0x00000100,    // Bit 8,  카운터 #2 > 비교기 #2 이벤트 발생
    QIINTBANK1_9                           = 0x00000200,    // Bit 9,  카운터 #3 < 비교기 #3 이벤트 발생
    QIINTBANK1_10                          = 0x00000400,    // Bit 10, 카운터 #3 = 비교기 #3 이벤트 발생
    QIINTBANK1_11                          = 0x00000800,    // Bit 11, 카운터 #3 > 비교기 #3 이벤트 발생
    QIINTBANK1_12                          = 0x00001000,    // Bit 12, 카운터 #4 < 비교기 #4 이벤트 발생
    QIINTBANK1_13                          = 0x00002000,    // Bit 13, 카운터 #4 = 비교기 #4 이벤트 발생
    QIINTBANK1_14                          = 0x00004000,    // Bit 14, 카운터 #4 < 비교기 #4 이벤트 발생
    QIINTBANK1_15                          = 0x00008000,    // Bit 15, 카운터 #5 < 비교기 #5 이벤트 발생
    QIINTBANK1_16                          = 0x00010000,    // Bit 16, 카운터 #5 = 비교기 #5 이벤트 발생
    QIINTBANK1_17                          = 0x00020000,    // Bit 17, 카운터 #5 > 비교기 #5 이벤트 발생
    QIINTBANK1_18                          = 0x00040000,    // Bit 18, 타이머 #1 이벤트 발생.
    QIINTBANK1_19                          = 0x00080000,    // Bit 19, 타이머 #2 이벤트 발생.
    QIINTBANK1_20                          = 0x00100000,    // Bit 20, 구동 예약 설정 Queue 비워짐.
    QIINTBANK1_21                          = 0x00200000,    // Bit 21, 구동 예약 설정 Queue 가득?
    QIINTBANK1_22                          = 0x00400000,    // Bit 22, 트리거 발생거리 주기/절대위치 Queue 비워짐.
    QIINTBANK1_23                          = 0x00800000,    // Bit 23, 트리거 발생거리 주기/절대위치 Queue 가득?
    QIINTBANK1_24                          = 0x01000000,    // Bit 24, 트리거 신호 발생 이벤트
    QIINTBANK1_25                          = 0x02000000,    // Bit 25, 스크립트 #1 명령어 예약 설정 Queue 비워짐.
    QIINTBANK1_26                          = 0x04000000,    // Bit 26, 스크립트 #2 명령어 예약 설정 Queue 비워짐.
    QIINTBANK1_27                          = 0x08000000,    // Bit 27, 스크립트 #3 명령어 예약 설정 레지스터 실행되어 초기화 됨.
    QIINTBANK1_28                          = 0x10000000,    // Bit 28, 스크립트 #4 명령어 예약 설정 레지스터 실행되어 초기화 됨.
    QIINTBANK1_29                          = 0x20000000,    // Bit 29, 서보 알람신호 인가됨.
    QIINTBANK1_30                          = 0x40000000,    // Bit 30, |CNT1| - |CNT2| >= |CNT4| 이벤트 발생.
    QIINTBANK1_31                          = 0x80000000     // Bit 31, 인터럽트 발생 명령어|INTGEN| 실행.
}

public enum AXT_MOTION_QIINTERRUPT_BANK2:uint
{
    QIINTBANK2_DISABLE                     = 0x00000000,    // INTERRUT DISABLED.
    QIINTBANK2_0                           = 0x00000001,    // Bit 0,  스크립트 #1 읽기 명령 결과 Queue 가 가득?.
    QIINTBANK2_1                           = 0x00000002,    // Bit 1,  스크립트 #2 읽기 명령 결과 Queue 가 가득?.
    QIINTBANK2_2                           = 0x00000004,    // Bit 2,  스크립트 #3 읽기 명령 결과 레지스터가 새로운 데이터로 갱신됨.
    QIINTBANK2_3                           = 0x00000008,    // Bit 3,  스크립트 #4 읽기 명령 결과 레지스터가 새로운 데이터로 갱신됨.
    QIINTBANK2_4                           = 0x00000010,    // Bit 4,  스크립트 #1 의 예약 명령어 중 실행 시 인터럽트 발생으로 설정된 명령어 실행됨.
    QIINTBANK2_5                           = 0x00000020,    // Bit 5,  스크립트 #2 의 예약 명령어 중 실행 시 인터럽트 발생으로 설정된 명령어 실행됨.
    QIINTBANK2_6                           = 0x00000040,    // Bit 6,  스크립트 #3 의 예약 명령어 실행 시 인터럽트 발생으로 설정된 명령어 실행됨.
    QIINTBANK2_7                           = 0x00000080,    // Bit 7,  스크립트 #4 의 예약 명령어 실행 시 인터럽트 발생으로 설정된 명령어 실행됨.
    QIINTBANK2_8                           = 0x00000100,    // Bit 8,  구동 시작
    QIINTBANK2_9                           = 0x00000200,    // Bit 9,  서보 위치 결정 완료(Inposition)기능을 사용한 구동,종료 조건 발생.
    QIINTBANK2_10                          = 0x00000400,    // Bit 10, 이벤트 카운터로 동작 시 사용할 이벤트 선택 #1 조건 발생.
    QIINTBANK2_11                          = 0x00000800,    // Bit 11, 이벤트 카운터로 동작 시 사용할 이벤트 선택 #2 조건 발생.
    QIINTBANK2_12                          = 0x00001000,    // Bit 12, SQSTR1 신호 인가 됨.
    QIINTBANK2_13                          = 0x00002000,    // Bit 13, SQSTR2 신호 인가 됨.
    QIINTBANK2_14                          = 0x00004000,    // Bit 14, UIO0 터미널 신호가 '1'로 변함.
    QIINTBANK2_15                          = 0x00008000,    // Bit 15, UIO1 터미널 신호가 '1'로 변함.
    QIINTBANK2_16                          = 0x00010000,    // Bit 16, UIO2 터미널 신호가 '1'로 변함.
    QIINTBANK2_17                          = 0x00020000,    // Bit 17, UIO3 터미널 신호가 '1'로 변함.
    QIINTBANK2_18                          = 0x00040000,    // Bit 18, UIO4 터미널 신호가 '1'로 변함.
    QIINTBANK2_19                          = 0x00080000,    // Bit 19, UIO5 터미널 신호가 '1'로 변함.
    QIINTBANK2_20                          = 0x00100000,    // Bit 20, UIO6 터미널 신호가 '1'로 변함.
    QIINTBANK2_21                          = 0x00200000,    // Bit 21, UIO7 터미널 신호가 '1'로 변함.
    QIINTBANK2_22                          = 0x00400000,    // Bit 22, UIO8 터미널 신호가 '1'로 변함.
    QIINTBANK2_23                          = 0x00800000,    // Bit 23, UIO9 터미널 신호가 '1'로 변함.
    QIINTBANK2_24                          = 0x01000000,    // Bit 24, UIO10 터미널 신호가 '1'로 변함.
    QIINTBANK2_25                          = 0x02000000,    // Bit 25, UIO11 터미널 신호가 '1'로 변함.
    QIINTBANK2_26                          = 0x04000000,    // Bit 26, 오류 정지 조건(LMT, ESTOP, STOP, ESTOP, CMD, ALARM) 발생.
    QIINTBANK2_27                          = 0x08000000,    // Bit 27, 보간 중 데이터 설정 오류 발생.
    QIINTBANK2_28                          = 0x10000000,    // Bit 28, Don't Care
    QIINTBANK2_29                          = 0x20000000,    // Bit 29, 리미트 신호(PELM, NELM)신호가 입력 됨.
    QIINTBANK2_30                          = 0x40000000,    // Bit 30, 부가 리미트 신호(PSLM, NSLM)신호가 입력 됨.
    QIINTBANK2_31                          = 0x80000000     // Bit 31, 비상 정지 신호(ESTOP)신호가 입력됨.
}
public enum AXT_EVENT:uint
{
    WM_USER                                = 0x0400,
    WM_AXL_INTERRUPT                       = (WM_USER + 1001)
}

public enum AXT_NETWORK_STATUS : uint
{
    NET_STATUS_DISCONNECTED  = 1,
    NET_STATUS_LOCK_MISMATCH = 5,
    NET_STATUS_CONNECTED     = 6
}

public enum AXT_MOTION_OVERRIDE_MODE : uint
{
    OVERRIDE_POS_START       = 0,
    OVERRIDE_POS_END         = 1
}

public enum AXT_MOTION_PROFILE_PRIORITY : uint
{
    PRIORITY_VELOCITY        = 0,
    PRIORITY_ACCELTIME       = 1
}

public enum AXT_MOTION_FUNC_RETURN_MODE_DEF : uint
{
    FUNC_RETURN_IMMEDIATE       = 0,
    FUNC_RETURN_BLOCKING        = 1,
    FUNC_RETURN_NON_BLOCKING    = 2
}

public struct MOTION_INFO
{
    public double dCmdPos;      // Command 위치[0x01]
    public double dActPos;      // Encoder 위치[0x02]
    public uint uMechSig;       // Mechanical Signal[0x04]
    public uint uDrvStat;       // Driver Status[0x08]
    public uint uInput;         // Universal Signal Input[0x10]
    public uint uOutput;        // Universal Signal Output[0x10]
    public uint uMask;          // 읽기 설정 Mask Ex) 0x1F, 모든정보 읽기
}

public class CAXHS
{
    public delegate void AXT_INTERRUPT_PROC(int nActiveNo, uint uFlag);

    public readonly static uint WM_USER                     = 0x0400;
    public readonly static uint WM_AXL_INTERRUPT            = (WM_USER + 1001);
    public readonly static uint MAX_SERVO_ALARM_HISTORY     = 15;

    public static int  AXIS_EVN(int nAxisNo) 
    {
        nAxisNo = (nAxisNo - (nAxisNo % 2));                // 쌍을 이루는 축의 짝수축을 찾음
        return nAxisNo;
    }

    public static int  AXIS_ODD(int nAxisNo) 
    {
        nAxisNo = (nAxisNo + ((nAxisNo + 1) % 2));          // 쌍을 이루는 축의 홀수축을 찾음
        return nAxisNo;
    }

    public static int  AXIS_QUR(int nAxisNo) 
    {
        nAxisNo = (nAxisNo % 4);                            // 쌍을 이루는 축의 홀수축을 찾음
        return nAxisNo;
    }

    public static int  AXIS_N04(int nAxisNo, int nPos) 
    {
        nAxisNo = (((nAxisNo / 4) * 4) + nPos);             // 한 칩의 축 위치로 변경(0~3)
        return nAxisNo;
    }

    public static int  AXIS_N01(int nAxisNo) 
    {
        nAxisNo = ((nAxisNo % 4) >> 2);                     // 0, 1축을 0으로 2, 3축을 1로 변경
        return nAxisNo;
    }

    public static int  AXIS_N02(int nAxisNo) 
    {
        nAxisNo = ((nAxisNo % 4)  % 2);                       // 0, 2축을 0으로 1, 3축을 1로 변경
        return nAxisNo;
    }

    public static int    m_SendAxis            = 0;           // 현재 축번호

    public const int F_50M_CLK                 = 50000000;    /* 50.000 MHz */
}

public enum CNTPORT_DATA_WRITE : uint
{
    CnCommand   = 0x10,
    CnData1     = 0x12,
    CnData2     = 0x14,
    CnData3     = 0x16,
    CnData4     = 0x18,
    CnData12    = 0x44,
    CnData34    = 0x46
}

public enum _CNTRAM_DATA : uint
{
    CnRamAddr1  = 0x28,
    CnRamAddr2  = 0x2A,
    CnRamAddr3  = 0x2C,
    CnRamAddrx1 = 0x48,
    CnRamAddr23 = 0x4A
}

public enum _PHASE_SEL
{
    CnAbPhase   = 0x0,
    CnZPhase    = 0x1
}

public enum _COUNTER_INPUT
{
    CnUpDownMode = 0x0,                                 // Up/Down
    CnSqr1Mode   = 0x1,                                 // 1체배
    CnSqr2Mode   = 0x2,                                 // 2체배
    CnSqr4Mode   = 0x3                                  // 4체배
}

public enum _CNTCOMMAND
{
    // CH-1 Group Register
    CnCh1CounterRead                                    = 0x10,                         // CH1 COUNTER READ, 24BIT
    CnCh1CounterWrite                                   = 0x90,                         // CH1 COUNTER WRITE
    CnCh1CounterModeRead                                = 0x11,                         // CH1 COUNTER MODE READ, 8BIT
    CnCh1CounterModeWrite                               = 0x91,                         // CH1 COUNTER MODE WRITE
    CnCh1TriggerRegionLowerDataRead                     = 0x12,                         // CH1 TRIGGER REGION LOWER DATA READ, 24BIT
    CnCh1TriggerRegionLowerDataWrite                    = 0x92,                         // CH1 TRIGGER REGION LOWER DATA WRITE
    CnCh1TriggerRegionUpperDataRead                     = 0x13,                         // CH1 TRIGGER REGION UPPER DATA READ, 24BIT
    CnCh1TriggerRegionUpperDataWrite                    = 0x93,                         // CH1 TRIGGER REGION UPPER DATA WRITE
    CnCh1TriggerPeriodRead                              = 0x14,                         // CH1 TRIGGER PERIOD READ, 24BIT, RESERVED
    CnCh1TriggerPeriodWrite                             = 0x94,                         // CH1 TRIGGER PERIOD WRITE
    CnCh1TriggerPulseWidthRead                          = 0x15,                         // CH1 TRIGGER PULSE WIDTH READ
    CnCh1TriggerPulseWidthWrite                         = 0x95,                         // CH1 RIGGER PULSE WIDTH WRITE
    CnCh1TriggerModeRead                                = 0x16,                         // CH1 TRIGGER MODE READ
    CnCh1TriggerModeWrite                               = 0x96,                         // CH1 RIGGER MODE WRITE
    CnCh1TriggerStatusRead                              = 0x17,                         // CH1 TRIGGER STATUS READ
    CnCh1NoOperation_97                                 = 0x97,
    CnCh1TriggerEnable                                  = 0x98,
    CnCh1TriggerDisable                                 = 0x99,
    CnCh1TimeTriggerFrequencyRead                       = 0x1A,
    CnCh1TimeTriggerFrequencyWrite                      = 0x9A,
    CnCh1ComparatorValueRead                            = 0x1B,
    CnCh1ComparatorValueWrite                           = 0x9B,
    CnCh1CompareatorConditionRead                       = 0x1D,
    CnCh1CompareatorConditionWrite                      = 0x9D,
    
    // CH-2 Group Register
    CnCh2CounterRead                                    = 0x20,                         // CH2 COUNTER READ, 24BIT
    CnCh2CounterWrite                                   = 0xA1,                         // CH2 COUNTER WRITE
    CnCh2CounterModeRead                                = 0x21,                         // CH2 COUNTER MODE READ, 8BIT
    CnCh2CounterModeWrite                               = 0xA1,                         // CH2 COUNTER MODE WRITE
    CnCh2TriggerRegionLowerDataRead                     = 0x22,                         // CH2 TRIGGER REGION LOWER DATA READ, 24BIT
    CnCh2TriggerRegionLowerDataWrite                    = 0xA2,                         // CH2 TRIGGER REGION LOWER DATA WRITE
    CnCh2TriggerRegionUpperDataRead                     = 0x23,                         // CH2 TRIGGER REGION UPPER DATA READ, 24BIT
    CnCh2TriggerRegionUpperDataWrite                    = 0xA3,                         // CH2 TRIGGER REGION UPPER DATA WRITE
    CnCh2TriggerPeriodRead                              = 0x24,                         // CH2 TRIGGER PERIOD READ, 24BIT, RESERVED
    CnCh2TriggerPeriodWrite                             = 0xA4,                         // CH2 TRIGGER PERIOD WRITE
    CnCh2TriggerPulseWidthRead                          = 0x25,                         // CH2 TRIGGER PULSE WIDTH READ, 24BIT
    CnCh2TriggerPulseWidthWrite                         = 0xA5,                         // CH2 RIGGER PULSE WIDTH WRITE
    CnCh2TriggerModeRead                                = 0x26,                         // CH2 TRIGGER MODE READ
    CnCh2TriggerModeWrite                               = 0xA6,                         // CH2 RIGGER MODE WRITE
    CnCh2TriggerStatusRead                              = 0x27,                         // CH2 TRIGGER STATUS READ
    CnCh2NoOperation_A7                                 = 0xA7,
    CnCh2TriggerEnable                                  = 0xA8,
    CnCh2TriggerDisable                                 = 0xA9,
    CnCh2TimeTriggerFrequencyRead                       = 0x2A,
    CnCh2TimeTriggerFrequencyWrite                      = 0xAA,
    CnCh2ComparatorValueRead                            = 0x2B,
    CnCh2ComparatorValueWrite                           = 0xAB,
    CnCh2CompareatorConditionRead                       = 0x2D,
    CnCh2CompareatorConditionWrite                      = 0xAD,

    // Ram Access Group Register
    CnRamDataWithRamAddress                             = 0x30,                         // READ RAM DATA WITH RAM ADDR PORT ADDRESS
    CnRamDataWrite                                      = 0xB0,                         // RAM DATA WRITE
    CnRamDataRead                                       = 0x31                          // RAM DATA READ, 32BIT
}
