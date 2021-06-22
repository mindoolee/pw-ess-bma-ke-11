#include "stdafx.h"
#include "DAXA.h"

HINSTANCE    g_hAXA = NULL;

funcAxaInfoIsAIOModule                      *AxaInfoIsAIOModule;
funcAxaInfoGetModuleNo                      *AxaInfoGetModuleNo;
funcAxaInfoGetModuleCount                   *AxaInfoGetModuleCount;
funcAxaInfoGetInputCount                    *AxaInfoGetInputCount;
funcAxaInfoGetOutputCount                   *AxaInfoGetOutputCount;
funcAxaInfoGetChannelNoOfModuleNo           *AxaInfoGetChannelNoOfModuleNo;
funcAxaInfoGetChannelNoAdcOfModuleNo        *AxaInfoGetChannelNoAdcOfModuleNo;
funcAxaInfoGetChannelNoDacOfModuleNo        *AxaInfoGetChannelNoDacOfModuleNo;
funcAxaInfoGetModule                        *AxaInfoGetModule;
funcAxaInfoGetModuleStatus                  *AxaInfoGetModuleStatus;
funcAxaiInfoGetModuleNoOfChannelNo          *AxaiInfoGetModuleNoOfChannelNo;
funcAxaiInfoGetChannelCount                 *AxaiInfoGetChannelCount;
funcAxaiEventSetChannel                     *AxaiEventSetChannel;
funcAxaiEventSetChannelEnable               *AxaiEventSetChannelEnable;
funcAxaiEventGetChannelEnable               *AxaiEventGetChannelEnable;
funcAxaiEventSetMultiChannelEnable          *AxaiEventSetMultiChannelEnable;
funcAxaiEventSetChannelMask                 *AxaiEventSetChannelMask;
funcAxaiEventGetChannelMask                 *AxaiEventGetChannelMask;
funcAxaiEventSetMultiChannelMask            *AxaiEventSetMultiChannelMask;
funcAxaiEventRead                           *AxaiEventRead;
funcAxaiInterruptSetModuleMask              *AxaiInterruptSetModuleMask;
funcAxaiInterruptGetModuleMask              *AxaiInterruptGetModuleMask;
funcAxaiSetRange                            *AxaiSetRange;
funcAxaiGetRange                            *AxaiGetRange;
funcAxaiSetRangeModule                      *AxaiSetRangeModule;
funcAxaiGetRangeModule                      *AxaiGetRangeModule;
funcAxaiSetMultiRange                       *AxaiSetMultiRange;
funcAxaiSetTriggerMode                      *AxaiSetTriggerMode;
funcAxaiGetTriggerMode                      *AxaiGetTriggerMode;
funcAxaiSetModuleOffsetValue                *AxaiSetModuleOffsetValue;
funcAxaiGetModuleOffsetValue                *AxaiGetModuleOffsetValue;
funcAxaiSwReadVoltage                       *AxaiSwReadVoltage;
funcAxaiSwReadDigit                         *AxaiSwReadDigit;
funcAxaiSwReadMultiVoltage                  *AxaiSwReadMultiVoltage;
funcAxaiSwReadMultiDigit                    *AxaiSwReadMultiDigit;
funcAxaiHwSetMultiAccess                    *AxaiHwSetMultiAccess;
funcAxaiHwStartMultiAccess                  *AxaiHwStartMultiAccess;
funcAxaiHwSetSampleFreq                     *AxaiHwSetSampleFreq;
funcAxaiHwGetSampleFreq                     *AxaiHwGetSampleFreq;
funcAxaiHwSetSamplePeriod                   *AxaiHwSetSamplePeriod;
funcAxaiHwGetSamplePeriod                   *AxaiHwGetSamplePeriod;
funcAxaiHwSetBufferOverflowMode             *AxaiHwSetBufferOverflowMode;
funcAxaiHwGetBufferOverflowMode             *AxaiHwGetBufferOverflowMode;
funcAxaiHwSetMultiBufferOverflowMode        *AxaiHwSetMultiBufferOverflowMode;
funcAxaiHwSetLimit                          *AxaiHwSetLimit;
funcAxaiHwGetLimit                          *AxaiHwGetLimit;
funcAxaiHwSetMultiLimit                     *AxaiHwSetMultiLimit;
funcAxaiHwStartMultiChannel                 *AxaiHwStartMultiChannel;
funcAxaiHwStartMultiFilter                  *AxaiHwStartMultiFilter;
funcAxaiHwStopMultiChannel                  *AxaiHwStopMultiChannel;
funcAxaiHwReadDataLength                    *AxaiHwReadDataLength;
funcAxaiHwReadSampleVoltage                 *AxaiHwReadSampleVoltage;
funcAxaiHwReadSampleDigit                   *AxaiHwReadSampleDigit;
funcAxaiHwIsBufferEmpty                     *AxaiHwIsBufferEmpty;
funcAxaiHwIsBufferUpper                     *AxaiHwIsBufferUpper;
funcAxaiHwIsBufferLower                     *AxaiHwIsBufferLower;
funcAxaiExternalStartADC                    *AxaiExternalStartADC;
funcAxaiExternalStopADC                     *AxaiExternalStopADC;
funcAxaiExternalReadFifoStatus              *AxaiExternalReadFifoStatus;
funcAxaiExternalReadVoltage                 *AxaiExternalReadVoltage;

funcAxaoInfoGetModuleNoOfChannelNo          *AxaoInfoGetModuleNoOfChannelNo;
funcAxaoInfoGetChannelCount                 *AxaoInfoGetChannelCount;
funcAxaoSetRange                            *AxaoSetRange;
funcAxaoGetRange                            *AxaoGetRange;
funcAxaoSetMultiRange                       *AxaoSetMultiRange;
funcAxaoWriteVoltage                        *AxaoWriteVoltage;
funcAxaoWriteMultiVoltage                   *AxaoWriteMultiVoltage;
funcAxaoReadVoltage                         *AxaoReadVoltage;
funcAxaoReadMultiVoltage                    *AxaoReadMultiVoltage;

BOOL LoadAXA()
{
    g_hAXA    = LoadLibrary("Axl.dll");
    if (g_hAXA)
    {
        AxaInfoIsAIOModule                  = (funcAxaInfoIsAIOModule *)GetProcAddress(g_hAXA, "AxaInfoIsAIOModule");
        AxaInfoGetModuleNo                  = (funcAxaInfoGetModuleNo *)GetProcAddress(g_hAXA, "AxaInfoGetModuleNo");
        AxaInfoGetModuleCount               = (funcAxaInfoGetModuleCount *)GetProcAddress(g_hAXA, "AxaInfoGetModuleCount");
        AxaInfoGetInputCount                = (funcAxaInfoGetInputCount *)GetProcAddress(g_hAXA, "AxaInfoGetInputCount");
        AxaInfoGetOutputCount               = (funcAxaInfoGetOutputCount *)GetProcAddress(g_hAXA, "AxaInfoGetOutputCount");
        AxaInfoGetChannelNoOfModuleNo       = (funcAxaInfoGetChannelNoOfModuleNo *)GetProcAddress(g_hAXA, "AxaInfoGetChannelNoOfModuleNo");
        AxaInfoGetChannelNoAdcOfModuleNo    = (funcAxaInfoGetChannelNoAdcOfModuleNo *)GetProcAddress(g_hAXA, "AxaInfoGetChannelNoAdcOfModuleNo");
        AxaInfoGetChannelNoDacOfModuleNo    = (funcAxaInfoGetChannelNoDacOfModuleNo *)GetProcAddress(g_hAXA, "AxaInfoGetChannelNoDacOfModuleNo");
        AxaInfoGetModule                    = (funcAxaInfoGetModule *)GetProcAddress(g_hAXA, "AxaInfoGetModule");
        AxaInfoGetModuleStatus              = (funcAxaInfoGetModuleStatus *)GetProcAddress(g_hAXA, "AxaInfoGetModuleStatus");
        AxaiInfoGetModuleNoOfChannelNo      = (funcAxaiInfoGetModuleNoOfChannelNo *)GetProcAddress(g_hAXA, "AxaiInfoGetModuleNoOfChannelNo");
        AxaiInfoGetChannelCount             = (funcAxaiInfoGetChannelCount *)GetProcAddress(g_hAXA, "AxaiInfoGetChannelCount");
        AxaiEventSetChannel                 = (funcAxaiEventSetChannel *)GetProcAddress(g_hAXA, "AxaiEventSetChannel");
        AxaiEventSetChannelEnable           = (funcAxaiEventSetChannelEnable *)GetProcAddress(g_hAXA, "AxaiEventSetChannelEnable");
        AxaiEventGetChannelEnable           = (funcAxaiEventGetChannelEnable *)GetProcAddress(g_hAXA, "AxaiEventGetChannelEnable");
        AxaiEventSetMultiChannelEnable      = (funcAxaiEventSetMultiChannelEnable *)GetProcAddress(g_hAXA, "AxaiEventSetMultiChannelEnable");
        AxaiEventSetChannelMask             = (funcAxaiEventSetChannelMask *)GetProcAddress(g_hAXA, "AxaiEventSetChannelMask");
        AxaiEventGetChannelMask             = (funcAxaiEventGetChannelMask *)GetProcAddress(g_hAXA, "AxaiEventGetChannelMask");
        AxaiEventSetMultiChannelMask        = (funcAxaiEventSetMultiChannelMask *)GetProcAddress(g_hAXA, "AxaiEventSetMultiChannelMask");
        AxaiEventRead                       = (funcAxaiEventRead *)GetProcAddress(g_hAXA, "AxaiEventRead");
        AxaiInterruptSetModuleMask          = (funcAxaiInterruptSetModuleMask *)GetProcAddress(g_hAXA, "AxaiInterruptSetModuleMask");
        AxaiInterruptGetModuleMask          = (funcAxaiInterruptGetModuleMask *)GetProcAddress(g_hAXA, "AxaiInterruptGetModuleMask");
        AxaiSetRange                        = (funcAxaiSetRange *)GetProcAddress(g_hAXA, "AxaiSetRange");
        AxaiGetRange                        = (funcAxaiGetRange *)GetProcAddress(g_hAXA, "AxaiGetRange");
        AxaiSetRangeModule                  = (funcAxaiSetRangeModule *)GetProcAddress(g_hAXA, "AxaiSetRangeModule");
        AxaiGetRangeModule                  = (funcAxaiGetRangeModule *)GetProcAddress(g_hAXA, "AxaiGetRangeModule");
        AxaiSetMultiRange                   = (funcAxaiSetMultiRange *)GetProcAddress(g_hAXA, "AxaiSetMultiRange");
        AxaiSetTriggerMode                  = (funcAxaiSetTriggerMode *)GetProcAddress(g_hAXA, "AxaiSetTriggerMode");
        AxaiGetTriggerMode                  = (funcAxaiGetTriggerMode *)GetProcAddress(g_hAXA, "AxaiGetTriggerMode");
        AxaiSetModuleOffsetValue            = (funcAxaiSetModuleOffsetValue *)GetProcAddress(g_hAXA, "AxaiSetModuleOffsetValue");
        AxaiGetModuleOffsetValue            = (funcAxaiGetModuleOffsetValue *)GetProcAddress(g_hAXA, "AxaiGetModuleOffsetValue");
        AxaiSwReadVoltage                   = (funcAxaiSwReadVoltage *)GetProcAddress(g_hAXA, "AxaiSwReadVoltage");
        AxaiSwReadDigit                     = (funcAxaiSwReadDigit *)GetProcAddress(g_hAXA, "AxaiSwReadDigit");
        AxaiSwReadMultiVoltage              = (funcAxaiSwReadMultiVoltage *)GetProcAddress(g_hAXA, "AxaiSwReadMultiVoltage");
        AxaiSwReadMultiDigit                = (funcAxaiSwReadMultiDigit *)GetProcAddress(g_hAXA, "AxaiSwReadMultiDigit");
        AxaiHwSetMultiAccess                = (funcAxaiHwSetMultiAccess *)GetProcAddress(g_hAXA, "AxaiHwSetMultiAccess");
        AxaiHwStartMultiAccess              = (funcAxaiHwStartMultiAccess *)GetProcAddress(g_hAXA, "AxaiHwStartMultiAccess");
        AxaiHwSetSampleFreq                 = (funcAxaiHwSetSampleFreq *)GetProcAddress(g_hAXA, "AxaiHwSetSampleFreq");
        AxaiHwGetSampleFreq                 = (funcAxaiHwGetSampleFreq *)GetProcAddress(g_hAXA, "AxaiHwGetSampleFreq");
        AxaiHwSetSamplePeriod               = (funcAxaiHwSetSamplePeriod *)GetProcAddress(g_hAXA, "AxaiHwSetSamplePeriod");
        AxaiHwGetSamplePeriod               = (funcAxaiHwGetSamplePeriod *)GetProcAddress(g_hAXA, "AxaiHwGetSamplePeriod");
        AxaiHwSetBufferOverflowMode         = (funcAxaiHwSetBufferOverflowMode *)GetProcAddress(g_hAXA, "AxaiHwSetBufferOverflowMode");
        AxaiHwGetBufferOverflowMode         = (funcAxaiHwGetBufferOverflowMode *)GetProcAddress(g_hAXA, "AxaiHwGetBufferOverflowMode");
        AxaiHwSetMultiBufferOverflowMode    = (funcAxaiHwSetMultiBufferOverflowMode *)GetProcAddress(g_hAXA, "AxaiHwSetMultiBufferOverflowMode");
        AxaiHwSetLimit                      = (funcAxaiHwSetLimit *)GetProcAddress(g_hAXA, "AxaiHwSetLimit");
        AxaiHwGetLimit                      = (funcAxaiHwGetLimit *)GetProcAddress(g_hAXA, "AxaiHwGetLimit");
        AxaiHwSetMultiLimit                 = (funcAxaiHwSetMultiLimit *)GetProcAddress(g_hAXA, "AxaiHwSetMultiLimit");
        AxaiHwStartMultiChannel             = (funcAxaiHwStartMultiChannel *)GetProcAddress(g_hAXA, "AxaiHwStartMultiChannel");
        AxaiHwStartMultiFilter              = (funcAxaiHwStartMultiFilter *)GetProcAddress(g_hAXA, "AxaiHwStartMultiFilter");
        AxaiHwStopMultiChannel              = (funcAxaiHwStopMultiChannel *)GetProcAddress(g_hAXA, "AxaiHwStopMultiChannel");
        AxaiHwReadDataLength                = (funcAxaiHwReadDataLength *)GetProcAddress(g_hAXA, "AxaiHwReadDataLength");
        AxaiHwReadSampleVoltage             = (funcAxaiHwReadSampleVoltage *)GetProcAddress(g_hAXA, "AxaiHwReadSampleVoltage");
        AxaiHwReadSampleDigit               = (funcAxaiHwReadSampleDigit *)GetProcAddress(g_hAXA, "AxaiHwReadSampleDigit");
        AxaiHwIsBufferEmpty                 = (funcAxaiHwIsBufferEmpty *)GetProcAddress(g_hAXA, "AxaiHwIsBufferEmpty");
        AxaiHwIsBufferUpper                 = (funcAxaiHwIsBufferUpper *)GetProcAddress(g_hAXA, "AxaiHwIsBufferUpper");
        AxaiHwIsBufferLower                 = (funcAxaiHwIsBufferLower *)GetProcAddress(g_hAXA, "AxaiHwIsBufferLower");
        AxaiExternalStartADC                = (funcAxaiExternalStartADC *)GetProcAddress(g_hAXA, "AxaiExternalStartADC");
        AxaiExternalStopADC                 = (funcAxaiExternalStopADC *)GetProcAddress(g_hAXA, "AxaiExternalStopADC");
        AxaiExternalReadFifoStatus          = (funcAxaiExternalReadFifoStatus *)GetProcAddress(g_hAXA, "AxaiExternalReadFifoStatus");
        AxaiExternalReadVoltage             = (funcAxaiExternalReadVoltage *)GetProcAddress(g_hAXA, "AxaiExternalReadVoltage");

        AxaoInfoGetModuleNoOfChannelNo      = (funcAxaoInfoGetModuleNoOfChannelNo *)GetProcAddress(g_hAXA, "AxaoInfoGetModuleNoOfChannelNo");
        AxaoInfoGetChannelCount             = (funcAxaoInfoGetChannelCount *)GetProcAddress(g_hAXA, "AxaoInfoGetChannelCount");
        AxaoSetRange                        = (funcAxaoSetRange *)GetProcAddress(g_hAXA, "AxaoSetRange");
        AxaoGetRange                        = (funcAxaoGetRange *)GetProcAddress(g_hAXA, "AxaoGetRange");
        AxaoSetMultiRange                   = (funcAxaoSetMultiRange *)GetProcAddress(g_hAXA, "AxaoSetMultiRange");
        AxaoWriteVoltage                    = (funcAxaoWriteVoltage *)GetProcAddress(g_hAXA, "AxaoWriteVoltage");
        AxaoWriteMultiVoltage               = (funcAxaoWriteMultiVoltage *)GetProcAddress(g_hAXA, "AxaoWriteMultiVoltage");
        AxaoReadVoltage                     = (funcAxaoReadVoltage *)GetProcAddress(g_hAXA, "AxaoReadVoltage");
        AxaoReadMultiVoltage                = (funcAxaoReadMultiVoltage *)GetProcAddress(g_hAXA, "AxaoReadMultiVoltage");
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL FreeAXA()
{
    if (g_hAXA)
    {
        FreeLibrary(g_hAXA);
        g_hAXA     = NULL;

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
