using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization;
using System.IO;
using System.Reflection;
using System.Windows.Forms;
using System.Drawing;
using Newtonsoft.Json;
using System.Security.Permissions;

namespace _PeopleWorks__UPB4860_Gen3_MC03_V4
{
    class _Define
    {
        public static DataTable[] DITable = new DataTable[3];
        public static DataTable[] DOTable = new DataTable[3];



        public static void CreateDIOInfo()
        {
            for(int i = 0; i < 3; i++)
            {
                DITable[i] = new DataTable();
                DOTable[i] = new DataTable();

                DITable[i].Columns.Add("Cate", typeof(string));
                DITable[i].Columns.Add("Comment", typeof(string));

                DOTable[i].Columns.Add("Cate", typeof(string));
                DOTable[i].Columns.Add("Comment", typeof(string));
            }


            for(int i = 0; i < 1024; i++)
            {
                DITable[0].Rows.Add("-", "-");
                DITable[1].Rows.Add("-", "-");
                DITable[2].Rows.Add("-", "-");

                DOTable[0].Rows.Add("-", "-");
                DOTable[1].Rows.Add("-", "-");
                DOTable[2].Rows.Add("-", "-");
            }


            /////////////////////////////
            // Digital Input
            /////////////////////////////

            IONaming(DI.EMG_SW,                       "메인 공통",            "비상 정지");
            IONaming(DI.AIR_PRESSURE,                 "메인 공통",            "공압 감지 #1");
            IONaming(DI.CV_ON_SW,                     "메인 공통",            "메인 컨베어 ON SW");
            IONaming(DI.CV_OFF_SW,                    "메인 공통",            "메인 컨베어 OFF SW");

            IONaming(DI.INVERTER1_ALARM,              "투입 리프트",          "인버터 알람");
            IONaming(DI.INVERTER1_RUN,                "투입 리프트",          "인버터 구동");
            IONaming(DI.INVERTER2_ALARM,              "배출 리프트",          "인버터 알람");
            IONaming(DI.INVERTER2_RUN,                "배출 리프트",          "인버터 구동");
            
            IONaming(DI.LOADING_START_SW,             "CMA 로딩",             "작업시작 스위치");
            
            IONaming(DI.CMA_LOADING_CLAMP1_ON,        "CMA 로딩",             "클램프 #1 ON");
            IONaming(DI.CMA_LOADING_CLAMP1_OFF,       "CMA 로딩",             "클램프 #1 OFF");
            IONaming(DI.CMA_LOADING_CLAMP2_ON,        "CMA 로딩",             "클램프 #2 ON");
            IONaming(DI.CMA_LOADING_CLAMP2_OFF,       "CMA 로딩",             "클램프 #2 OFF");
            
            IONaming(DI.INLIFT_UP,                    "투입 리프트",          "리프트 상승");
            IONaming(DI.INLIFT_DW,                    "투입 리프트",          "리프트 하강");
            IONaming(DI.INLIFT_PALLET_UP,             "투입 리프트",          "파레트 상승");
            IONaming(DI.INLIFT_PALLET_DW,             "투입 리프트",          "파레트 하강");
            IONaming(DI.INLIFT_PALLET_END,            "투입 리프트",          "파레트 종단감지");
            IONaming(DI.INLIFT_PALLET_SLOWPOINT,      "투입 리프트",          "파레트 감속포인트");
            IONaming(DI.INLIFT_PRODUCT_BASEPLATE,     "투입 리프트",          "베이스 플레이트 감지");
            IONaming(DI.INLIFT_PRODUCT_CMA,           "투입 리프트",          "CMA 유무 감지");
            
            IONaming(DI.UNDER_CV_PALLET_END,          "하층 컨베어",          "파레트 감지");
            IONaming(DI.UNDER_CV_STOPPER_UP,          "하층 컨베어",          "스토퍼 상승");
            IONaming(DI.UNDER_CV_STOPPER_DW,          "하층 컨베어",          "스토퍼 하강");
            
            IONaming(DI.LOADING_JIG_POSITION,         "CMA 로딩",             "클램프 위치 확인");
            
            IONaming(DI.BETWEEN_INLIFT_CV,            "투입 리프트",          "파레트 위치 확인");
            
            IONaming(DI.LOADING_DOOR1,                "CMA 로딩",             "문열림 감지 #1");
            IONaming(DI.LOADING_DOOR2,                "CMA 로딩",             "문열림 감지 #2");
            
            IONaming(DI.SMEMA_IN1,                    "SMEMA",                "SMEMA #1");
            IONaming(DI.SMEMA_IN2,                    "SMEMA",                "SMEMA #2");
            IONaming(DI.SMEMA_IN3,                    "SMEMA",                "SMEMA #3");
            
            IONaming(DI.STATION1_PALLET,              "STATION #1",           "파레트 감지");
            IONaming(DI.STATION1_CENTER,              "STATION #1",           "파레트 정위치 감지");
            IONaming(DI.STATION1_LOCK_OFF,            "STATION #1",           "하부 브레이크 해제");
            IONaming(DI.STATION1_BREAK_OFF,           "STATION #1",           "측면 브레이크 해제");
            IONaming(DI.STATION1_PALLET_UP,           "STATION #1",           "파레트 상승");
            IONaming(DI.STATION1_PALLET_DW,           "STATION #1",           "파레트 하강");
            IONaming(DI.STATION1_FINISH_SW,           "STATION #1",           "작업완료 스위치");
            IONaming(DI.STATION1_FOOT_SW,             "STATION #1",           "발판 스위치");
              
            IONaming(DI.STATION2_PALLET,              "STATION #2",           "파레트 감지");
            IONaming(DI.STATION2_CENTER,              "STATION #2",           "파레트 정위치 감지");
            IONaming(DI.STATION2_LOCK_OFF,            "STATION #2",           "하부 브레이크 해제");
            IONaming(DI.STATION2_BREAK_OFF,           "STATION #2",           "측면 브레이크 해제");
            IONaming(DI.STATION2_PALLET_UP,           "STATION #2",           "파레트 상승");
            IONaming(DI.STATION2_PALLET_DW,           "STATION #2",           "파레트 하강");
            IONaming(DI.STATION2_FINISH_SW,           "STATION #2",           "작업완료 스위치");
            IONaming(DI.STATION2_FOOT_SW,             "STATION #2",           "발판 스위치");
            
            IONaming(DI.STATION3_PALLET,              "STATION #3",           "파레트 감지");
            IONaming(DI.STATION3_CENTER,              "STATION #3",           "파레트 정위치 감지");
            IONaming(DI.STATION3_LOCK_OFF,            "STATION #3",           "하부 브레이크 해제");
            IONaming(DI.STATION3_BREAK_OFF,           "STATION #3",           "측면 브레이크 해제");
            IONaming(DI.STATION3_PALLET_UP,           "STATION #3",           "파레트 상승");
            IONaming(DI.STATION3_PALLET_DW,           "STATION #3",           "파레트 하강");
            IONaming(DI.STATION3_FINISH_SW,           "STATION #3",           "작업완료 스위치");
            IONaming(DI.STATION3_FOOT_SW,             "STATION #3",           "발판 스위치");
            
            IONaming(DI.STATION4_PALLET,              "STATION #4",           "파레트 감지");
            IONaming(DI.STATION4_CENTER,              "STATION #4",           "파레트 정위치 감지");
            IONaming(DI.STATION4_LOCK_OFF,            "STATION #4",           "하부 브레이크 해제");
            IONaming(DI.STATION4_BREAK_OFF,           "STATION #4",           "측면 브레이크 해제");
            IONaming(DI.STATION4_PALLET_UP,           "STATION #4",           "파레트 상승");
            IONaming(DI.STATION4_PALLET_DW,           "STATION #4",           "파레트 하강");
            IONaming(DI.STATION4_FINISH_SW,           "STATION #4",           "작업완료 스위치");
            IONaming(DI.STATION4_FOOT_SW,             "STATION #4",           "발판 스위치");
            
            IONaming(DI.STATION1_TIP1,                "STATION #1",           "팁감지 #1");
            IONaming(DI.STATION1_TIP2,                "STATION #1",           "팁감지 #2");
            IONaming(DI.STATION1_TIP3,                "STATION #1",           "팁감지 #3");
            IONaming(DI.STATION1_TIP4,                "STATION #1",           "팁감지 #4");
            IONaming(DI.STATION1_TIP5,                "STATION #1",           "팁감지 #5");
            IONaming(DI.STATION1_TIP6,                "STATION #1",           "팁감지 #6");
            IONaming(DI.STATION1_TIP7,                "STATION #1",           "팁감지 #7");
            IONaming(DI.STATION1_TIP8,                "STATION #1",           "팁감지 #8");
            
            IONaming(DI.STATION2_TIP1,                "STATION #2",           "팁감지 #1");
            IONaming(DI.STATION2_TIP2,                "STATION #2",           "팁감지 #2");
            IONaming(DI.STATION2_TIP3,                "STATION #2",           "팁감지 #3");
            IONaming(DI.STATION2_TIP4,                "STATION #2",           "팁감지 #4");
            IONaming(DI.STATION2_TIP5,                "STATION #2",           "팁감지 #5");
            IONaming(DI.STATION2_TIP6,                "STATION #2",           "팁감지 #6");
            IONaming(DI.STATION2_TIP7,                "STATION #2",           "팁감지 #7");
            IONaming(DI.STATION2_TIP8,                "STATION #2",           "팁감지 #8");
            
            IONaming(DI.STATION3_TIP1,                "STATION #3",           "팁감지 #1");
            IONaming(DI.STATION3_TIP2,                "STATION #3",           "팁감지 #2");
            IONaming(DI.STATION3_TIP3,                "STATION #3",           "팁감지 #3");
            IONaming(DI.STATION3_TIP4,                "STATION #3",           "팁감지 #4");
            IONaming(DI.STATION3_TIP5,                "STATION #3",           "팁감지 #5");
            IONaming(DI.STATION3_TIP6,                "STATION #3",           "팁감지 #6");
            IONaming(DI.STATION3_TIP7,                "STATION #3",           "팁감지 #7");
            IONaming(DI.STATION3_TIP8,                "STATION #3",           "팁감지 #8");
            
            IONaming(DI.STATION4_TIP1,                "STATION #4",           "팁감지 #1");
            IONaming(DI.STATION4_TIP2,                "STATION #4",           "팁감지 #2");
            IONaming(DI.STATION4_TIP3,                "STATION #4",           "팁감지 #3");
            IONaming(DI.STATION4_TIP4,                "STATION #4",           "팁감지 #4");
            IONaming(DI.STATION4_TIP5,                "STATION #4",           "팁감지 #5");
            IONaming(DI.STATION4_TIP6,                "STATION #4",           "팁감지 #6");
            IONaming(DI.STATION4_TIP7,                "STATION #4",           "팁감지 #7");
            IONaming(DI.STATION4_TIP8,                "STATION #4",           "팁감지 #8");
            
            IONaming(DI.NUTRUNNER1_IN1,               "NUTRUNNER #1",         "IN #1");
            IONaming(DI.NUTRUNNER1_IN2,               "NUTRUNNER #1",         "IN #2");
            IONaming(DI.NUTRUNNER1_IN3,               "NUTRUNNER #1",         "IN #3");
            IONaming(DI.NUTRUNNER1_IN4,               "NUTRUNNER #1",         "IN #4");
            
            IONaming(DI.NUTRUNNER2_IN1,               "NUTRUNNER #2",         "IN #1");
            IONaming(DI.NUTRUNNER2_IN2,               "NUTRUNNER #2",         "IN #2");
            IONaming(DI.NUTRUNNER2_IN3,               "NUTRUNNER #2",         "IN #3");
            IONaming(DI.NUTRUNNER2_IN4,               "NUTRUNNER #2",         "IN #4");
              
            IONaming(DI.NUTRUNNER3_IN1,               "NUTRUNNER #3",         "IN #1");
            IONaming(DI.NUTRUNNER3_IN2,               "NUTRUNNER #3",         "IN #2");
            IONaming(DI.NUTRUNNER3_IN3,               "NUTRUNNER #3",         "IN #3");
            IONaming(DI.NUTRUNNER3_IN4,               "NUTRUNNER #3",         "IN #4");
            
            IONaming(DI.NUTRUNNER4_IN1,               "NUTRUNNER #4",         "IN #1");
            IONaming(DI.NUTRUNNER4_IN2,               "NUTRUNNER #4",         "IN #2");
            IONaming(DI.NUTRUNNER4_IN3,               "NUTRUNNER #4",         "IN #3");
            IONaming(DI.NUTRUNNER4_IN4,               "NUTRUNNER #4",         "IN #4");
            
            IONaming(DI.ROBOT_IN1,                    "다관절 로봇",          "IN #1");
            IONaming(DI.ROBOT_IN2,                    "다관절 로봇",          "IN #2");
            IONaming(DI.ROBOT_IN3,                    "다관절 로봇",          "IN #3");
            IONaming(DI.ROBOT_IN4,                    "다관절 로봇",          "IN #4");
            
            IONaming(DI.STATION5_TIP1,                "STATION #5",           "팁감지 #1");
            IONaming(DI.STATION5_TIP2,                "STATION #5",           "팁감지 #2");
            IONaming(DI.STATION5_TIP3,                "STATION #5",           "팁감지 #3");
            IONaming(DI.STATION5_TIP4,                "STATION #5",           "팁감지 #4");
            IONaming(DI.STATION5_TIP5,                "STATION #5",           "팁감지 #5");
            IONaming(DI.STATION5_TIP6,                "STATION #5",           "팁감지 #6");
            IONaming(DI.STATION5_TIP7,                "STATION #5",           "팁감지 #7");
            IONaming(DI.STATION5_TIP8,                "STATION #5",           "팁감지 #8");
            
            IONaming(DI.LIFT_TIP1,                    "LIFT",                 "팁감지 #1");
            IONaming(DI.LIFT_TIP2,                    "LIFT",                 "팁감지 #2");
            IONaming(DI.LIFT_TIP3,                    "LIFT",                 "팁감지 #3");
            IONaming(DI.LIFT_TIP4,                    "LIFT",                 "팁감지 #4");
            IONaming(DI.LIFT_TIP5,                    "LIFT",                 "팁감지 #5");
            IONaming(DI.LIFT_TIP6,                    "LIFT",                 "팁감지 #6");
            IONaming(DI.LIFT_TIP7,                    "LIFT",                 "팁감지 #7");
            IONaming(DI.LIFT_TIP8,                    "LIFT",                 "팁감지 #8");
            
            IONaming(DI.NUTRUNNER5_IN1,               "NUTRUNNER #5",         "IN #1");
            IONaming(DI.NUTRUNNER5_IN2,               "NUTRUNNER #5",         "IN #2");
            IONaming(DI.NUTRUNNER5_IN3,               "NUTRUNNER #5",         "IN #3");
            IONaming(DI.NUTRUNNER5_IN4,               "NUTRUNNER #5",         "IN #4");
            
            IONaming(DI.NUTRUNNER6_IN1,               "NUTRUNNER #6",         "IN #1");
            IONaming(DI.NUTRUNNER6_IN2,               "NUTRUNNER #6",         "IN #2");
            IONaming(DI.NUTRUNNER6_IN3,               "NUTRUNNER #6",         "IN #3");
            IONaming(DI.NUTRUNNER6_IN4,               "NUTRUNNER #6",         "IN #4");
            
            IONaming(DI.HIPOT_CABLE1,                 "HIPOT",                "수동 컨텍 케이블 감지 #1");
            IONaming(DI.HIPOT_CABLE2,                 "HIPOT",                "수동 컨텍 케이블 감지 #2");
              
            IONaming(DI.EOL_CABLE1,                   "EOL",                  "수동 컨텍 케이블 감지 #1");
            IONaming(DI.EOL_CABLE2,                   "EOL",                  "수동 컨텍 케이블 감지 #2");
            IONaming(DI.EOL_CABLE3,                   "EOL",                  "수동 컨텍 케이블 감지 #3");
            IONaming(DI.EOL_CABLE4,                   "EOL",                  "수동 컨텍 케이블 감지 #4");
            IONaming(DI.EOL_CABLE5,                   "EOL",                  "수동 컨텍 케이블 감지 #5");
            
            IONaming(DI.HIPOT_PALLET,                 "HIPOT",                "파레트 감지");
            IONaming(DI.HIPOT_PRODUCT,                "HIPOT",                "제품 감지");
            IONaming(DI.HIPOT_PALLET_UP,              "HIPOT",                "파레트 상승");
            IONaming(DI.HIPOT_PALLET_DW,              "HIPOT",                "파레트 하강");
            IONaming(DI.HIPOT_CAN_ON,                 "HIPOT",                "CAN 통신 실린더 ON");
            IONaming(DI.HIPOT_CAN_OFF,                "HIPOT",                "CAN 통신 실린더 OFF");
            IONaming(DI.HIPOT_PRODUCT_PUSH1_ON,       "HIPOT",                "제품 고정 실린더1 ON");
            IONaming(DI.HIPOT_PRODUCT_PUSH1_OFF,      "HIPOT",                "제품 고정 실린더1 OFF");
            IONaming(DI.HIPOT_PRODUCT_PUSH2_ON,       "HIPOT",                "제품 고정 실런더2 ON");
            IONaming(DI.HIPOT_PRODUCT_PUSH2_OFF,      "HIPOT",                "제품 고정 실린더2 OFF");
            IONaming(DI.HIPOT_FINISH_SW,              "HIPOT",                "작업 완료 버튼");
            IONaming(DI.HIPOT_READY_SW,               "HIPOT",                "작업 준비 버튼");
            IONaming(DI.HIPOT_STOP_SW,                "HIPOT",                "작업 정지 버튼");
            
            IONaming(DI.EOL_PALLET,                   "EOL",                  "파레트 감지");
            IONaming(DI.EOL_PRODUCT,                  "EOL",                  "제품 감지");
            IONaming(DI.EOL_PALLET_UP,                "EOL",                  "파레트 상승");
            IONaming(DI.EOL_PALLET_DW,                "EOL",                  "파레트 하강");
            IONaming(DI.EOL_CAN_ON,                   "EOL",                  "CAN 통신 실린더 ON");
            IONaming(DI.EOL_CAN_OFF,                  "EOL",                  "CAN 통신 실린더 OFF");
            IONaming(DI.EOL_PRODUCT_PUSH1_ON,         "EOL",                  "제품 고정 실린더1 ON");
            IONaming(DI.EOL_PRODUCT_PUSH1_OFF,        "EOL",                  "제품 고정 실린더1 OFF");
            IONaming(DI.EOL_PRODUCT_PUSH2_ON,         "EOL",                  "제품 고정 실런더2 ON");
            IONaming(DI.EOL_PRODUCT_PUSH2_OFF,        "EOL",                  "제품 고정 실린더2 OFF");
            IONaming(DI.EOL_FINISH_SW,                "EOL",                  "작업 완료 버튼");
            IONaming(DI.EOL_READY_SW,                 "EOL",                  "작업 준비 버튼");
            IONaming(DI.EOL_STOP_SW,                  "EOL",                  "작업 정지 버튼");

            IONaming(DI.RELIFT_CAN_CABLE_ALIGN,       "배출 리프트",          "CAN 통신 케이블 위치확인센서 정위치");
            IONaming(DI.RELIFT_PALLET_END,            "배출 리프트",          "파레트 종단감지");
            IONaming(DI.RELIFT_PALLET_SLOWPOINT,      "배출 리프트",          "파레트 감속포인트");
            IONaming(DI.RELIFT_CAN_CABLE_CHECK,       "배출 리프트",          "CAN 통신 케이블 위치확인");
            IONaming(DI.RELIFT_SAFTY,                 "배출 리프트",          "리프트 안전센서");
            IONaming(DI.BETWEEN_RELIFT_CV,            "배출 리프트",          "파레트 위치 확인");
            IONaming(DI.RELIFT_UP,                    "배출 리프트",          "리프트 상승");
            IONaming(DI.RELIFT_DW,                    "배출 리프트",          "리프트 하강");
            IONaming(DI.RELIFT_PALLET_UP,             "배출 리프트",          "파레트 상승");
            IONaming(DI.RELIFT_PALLET_DW,             "배출 리프트",          "파레트 하강");
            IONaming(DI.RELIFT_FINISH_SW,             "배출 리프트",          "작업 완료 스위치");
            
            IONaming(DI.UNDER_CV_PALLET_FULL,         "하층 컨베어",          "파레트 만재 감지");
            
            IONaming(DI.CAMERA1_TOTAL,                "CAMERA #1",            "종합 판정");
            IONaming(DI.CAMERA1_BUSY,                 "CAMERA #1",            "BUSY");
            IONaming(DI.CAMERA1_ERROR,                "CAMERA #1",            "ERROR");
            IONaming(DI.CAMERA1_IN4,                  "CAMERA #1",            "IN4");
            
            IONaming(DI.CAMERA2_TOTAL,                "CAMERA #2",            "종합 판정");
            IONaming(DI.CAMERA2_BUSY,                 "CAMERA #2",            "BUSY");
            IONaming(DI.CAMERA2_ERROR,                "CAMERA #2",            "ERROR");
            IONaming(DI.CAMERA2_IN4,                  "CAMERA #2",            "IN4");
            
            IONaming(DI.HIPOT_N_POS1,                 "HIPOT",                "N 단자 위치 확인 #1");
            IONaming(DI.HIPOT_N_POS2,                 "HIPOT",                "N 단자 위치 확인 #2");
            IONaming(DI.HIPOT_G_POS1,                 "HIPOT",                "G 단자 위치 확인 #1");
            IONaming(DI.HIPOT_G_POS2,                 "HIPOT",                "G 단자 위치 확인 #2");
            IONaming(DI.HIPOT_G_POS3,                 "HIPOT",                "G 단자 위치 확인 #3");

            IONaming(DI.EOL_N_POS1,                   "EOL",                  "N 단자 위치 확인 #1");
            IONaming(DI.EOL_N_POS2,                   "EOL",                  "N 단자 위치 확인 #2");
            
            IONaming(DI.STATION5_PALLET,              "STATION #5",           "파레트 감지");
            IONaming(DI.STATION5_CENTER,              "STATION #5",           "파레트 정위치 감지");
            IONaming(DI.STATION5_LOCK_OFF,            "STATION #5",           "하부 브레이크 해제");
            IONaming(DI.STATION5_BREAK_OFF,           "STATION #5",           "측면 브레이크 해제");
            IONaming(DI.STATION5_PALLET_UP,           "STATION #5",           "파레트 상승");
            IONaming(DI.STATION5_PALLET_DW,           "STATION #5",           "파레트 하강");
            IONaming(DI.STATION5_FINISH_SW,           "STATION #5",           "작업완료 스위치");
            IONaming(DI.STATION5_FOOT_SW,             "STATION #5",           "발판 스위치");
            
            IONaming(DI.AIR_PRESSURE2,                "메인 공통",            "공압 감지 #2");
            IONaming(DI.VISION_OK,                    "OMRON 라벨검사",       "OK");
            IONaming(DI.VISION_NG,                    "OMRON 라벨검사",       "NG");
            
            IONaming(DI.INVERTER3_ALARM,              "배출 리프트",          "인버터 알람");
            IONaming(DI.INVERTER3_RUN,                "배출 리프트",          "인버터 구동");
            
            IONaming(DI.MAIN_DOOR1,                   "메인 공통",            "문열림 감지 #3");
            IONaming(DI.MAIN_DOOR2,                   "메인 공통",            "문열림 감지 #4");
            IONaming(DI.MAIN_DOOR3,                   "메인 공통",            "문열림 감지 #5");

            //IO OUTPUT
            IONaming(DO.LP1_SERVO_ON,                 "메인 공통",            "LP1 서보 ON");
            
            IONaming(DO.MAIN_CV_ON,                   "메인 공통",            "메인 컨베어 ON");
            
            IONaming(DO.INLIFT_CV_ON,                 "투입 리프트",          "컨베어 ON");
            IONaming(DO.INLIFT_CV_REV,                "투입 리프트",          "컨베어 역방향");
            IONaming(DO.INLIFT_CV_FAST,               "투입 리프트",          "컨베어 고속 운전");
            IONaming(DO.INLIFT_CV_SLOW,               "투입 리프트",          "컨베어 저속 운전");
            
            IONaming(DO.CV_ON_SW_LAMP,                "CMA 로딩",             "컨베어 ON 스위치 램프");
            IONaming(DO.CV_OFF_SW_LAMP,               "CMA 로딩",             "컨베어 OFF 스위치 램프");
            IONaming(DO.LOADING_START_SW_LAMP,        "CMA 로딩",             "작업 시작 스위치 램프");
            IONaming(DO.LOADING_START_SW_BUZZER,      "CMA 로딩",             "작업 시작 스위치 부저");
            
            IONaming(DO.CMA_LOADING_CLAMP_ON,         "CMA 로딩",             "로딩 클램프 ON");
            IONaming(DO.CMA_LOADING_CLAMP_OFF,        "CMA 로딩",             "로딩 클램프 OFF");
            
            IONaming(DO.INLIFT_UP,                    "투입 리프트",          "리프트 상승");
            IONaming(DO.INLIFT_DW,                    "투입 리프트",          "리프트 하강");
            IONaming(DO.INLIFT_PALLET_UP,             "투입 리프트",          "파레트 상승");
            IONaming(DO.INLIFT_PALLET_DW,             "투입 리프트",          "파레트 하강");
            
            IONaming(DO.UNDER_CV_STOPPER_DW,          "하층 컨베어",          "스토퍼 하강");
            
            IONaming(DO.MAIN_TOWERLAMP_RED,           "메인 공통",            "타워램프 #적색");
            IONaming(DO.MAIN_TOWERLAMP_YELLOW,        "메인 공통",            "타워램프 #황색");
            IONaming(DO.MAIN_TOWERLAMP_GREEN,         "메인 공통",            "타워램프 #녹색");
            IONaming(DO.MAIN_TOWERLAMP_BUZZER,        "메인 공통",            "타워램프 #부저");
            
            IONaming(DO.SMEMA_OUT1,                   "SMEMA",                "SMEMA #1");
            IONaming(DO.SMEMA_OUT2,                   "SMEMA",                "SMEMA #2");
            IONaming(DO.SMEMA_OUT3,                   "SMEMA",                "SMEMA #3");
            
            IONaming(DO.STATION1_PALLET_UP,           "STATION #1",           "파레트 상승");
            IONaming(DO.STATION1_PALLET_DW,           "STATION #1",           "파레트 하강");
            IONaming(DO.STATION1_LOCK_OFF,            "STATION #1",           "하부 브레이크 해제");
            IONaming(DO.STATION1_BREAK_OFF,           "STATION #1",           "측면 브레이크 해제");
            IONaming(DO.STATION1_STOPPER_DW,          "STATION #1",           "스토퍼 하강");
            IONaming(DO.STATION1_FINISH_SW_LAMP,      "STATION #1",           "작업완료 스위치 램프");
            IONaming(DO.STATION1_BUZZER,              "STATION #1",           "작업완료 스위치 부저");
              
            IONaming(DO.STATION2_PALLET_UP,           "STATION #2",           "파레트 상승");
            IONaming(DO.STATION2_PALLET_DW,           "STATION #2",           "파레트 하강");
            IONaming(DO.STATION2_LOCK_OFF,            "STATION #2",           "하부 브레이크 해제");
            IONaming(DO.STATION2_BREAK_OFF,           "STATION #2",           "측면 브레이크 해제");
            IONaming(DO.STATION2_STOPPER_DW,          "STATION #2",           "스토퍼 하강");
            IONaming(DO.STATION2_FINISH_SW_LAMP,      "STATION #2",           "작업완료 스위치 램프");
            IONaming(DO.STATION2_BUZZER,              "STATION #2",           "작업완료 스위치 부저");
            
            IONaming(DO.STATION3_PALLET_UP,           "STATION #3",           "파레트 상승");
            IONaming(DO.STATION3_PALLET_DW,           "STATION #3",           "파레트 하강");
            IONaming(DO.STATION3_LOCK_OFF,            "STATION #3",           "하부 브레이크 해제");
            IONaming(DO.STATION3_BREAK_OFF,           "STATION #3",           "측면 브레이크 해제");
            IONaming(DO.STATION3_STOPPER_DW,          "STATION #3",           "스토퍼 하강");
            IONaming(DO.STATION3_FINISH_SW_LAMP,      "STATION #3",           "작업완료 스위치 램프");
            IONaming(DO.STATION3_BUZZER,              "STATION #3",           "작업완료 스위치 부저");
            
            IONaming(DO.STATION4_PALLET_UP,           "STATION #4",           "파레트 상승");
            IONaming(DO.STATION4_PALLET_DW,           "STATION #4",           "파레트 하강");
            IONaming(DO.STATION4_LOCK_OFF,            "STATION #4",           "하부 브레이크 해제");
            IONaming(DO.STATION4_BREAK_OFF,           "STATION #4",           "측면 브레이크 해제");
            IONaming(DO.STATION4_STOPPER_DW,          "STATION #4",           "스토퍼 하강");
            IONaming(DO.STATION4_FINISH_SW_LAMP,      "STATION #4",           "작업완료 스위치 램프");
            IONaming(DO.STATION4_BUZZER,              "STATION #4",           "작업완료 스위치 부저");
            
            IONaming(DO.NUTRUNNER1_OUT1,              "NUTRUNNER #1",         "OUT #1");
            IONaming(DO.NUTRUNNER1_OUT2,              "NUTRUNNER #1",         "OUT #2");
            IONaming(DO.NUTRUNNER1_OUT3,              "NUTRUNNER #1",         "OUT #3");
            IONaming(DO.NUTRUNNER1_OUT4,              "NUTRUNNER #1",         "OUT #4");
              
            IONaming(DO.NUTRUNNER2_OUT1,              "NUTRUNNER #2",         "OUT #1");
            IONaming(DO.NUTRUNNER2_OUT2,              "NUTRUNNER #2",         "OUT #2");
            IONaming(DO.NUTRUNNER2_OUT3,              "NUTRUNNER #2",         "OUT #3");
            IONaming(DO.NUTRUNNER2_OUT4,              "NUTRUNNER #2",         "OUT #4");
              
            IONaming(DO.NUTRUNNER3_OUT1,              "NUTRUNNER #3",         "OUT #1");
            IONaming(DO.NUTRUNNER3_OUT2,              "NUTRUNNER #3",         "OUT #2");
            IONaming(DO.NUTRUNNER3_OUT3,              "NUTRUNNER #3",         "OUT #3");
            IONaming(DO.NUTRUNNER3_OUT4,              "NUTRUNNER #3",         "OUT #4");
              
            IONaming(DO.NUTRUNNER4_OUT1,              "NUTRUNNER #4",         "OUT #1");
            IONaming(DO.NUTRUNNER4_OUT2,              "NUTRUNNER #4",         "OUT #2");
            IONaming(DO.NUTRUNNER4_OUT3,              "NUTRUNNER #4",         "OUT #3");
            IONaming(DO.NUTRUNNER4_OUT4,              "NUTRUNNER #4",         "OUT #4");
            
            IONaming(DO.LP3_SERVO_ON,                 "메인 공통",            "LP3 서보 ON");
            
            IONaming(DO.RELIFT_CV_ON,                 "배출 리프트",          "컨베어 ON");
            IONaming(DO.RELIFT_CV_REV,                "배출 리프트",          "컨베어 역방향");
            IONaming(DO.RELIFT_CV_FAST,               "배출 리프트",          "컨베어 고속 운전");
            IONaming(DO.RELIFT_CV_SLOW,               "배출 리프트",          "컨베어 저속 운전");
            
            IONaming(DO.STATION5_PALLET_UP,           "STATION #5",           "파레트 상승");
            IONaming(DO.STATION5_PALLET_DW,           "STATION #5",           "파레트 하강");
            IONaming(DO.STATION5_LOCK_OFF,            "STATION #5",           "하부 브레이크 해제");
            IONaming(DO.STATION5_BREAK_OFF,           "STATION #5",           "측면 브레이크 해제");
            IONaming(DO.STATION5_STOPPER_DW,          "STATION #5",           "스토퍼 하강");
            IONaming(DO.STATION5_FINISH_SW_LAMP,      "STATION #5",           "작업완료 스위치 램프");
            IONaming(DO.STATION5_BUZZER,              "STATION #5",           "작업완료 스위치 부저");
              
            IONaming(DO.HIPOT_PALLET_UP,              "HIPOT",                "파레트 상승");
            IONaming(DO.HIPOT_PALLET_DW,              "HIPOT",                "파레트 하강");
            IONaming(DO.HIPOT_STOPPER_DW,             "HIPOT",                "스토퍼 하강");
            IONaming(DO.HIPOT_PRODUCT_PUSH_ON,        "HIPOT",                "측면 가압 실린더 ON");
            IONaming(DO.HIPOT_CAN_CONTACT_ON,         "HIPOT",                "CAN 통신 실린더 ON");
            IONaming(DO.HIPOT_FINISH_SW_LAMP,         "HIPOT",                "작업완료 스위치 램프");
            IONaming(DO.HIPOT_BUZZER,                 "HIPOT",                "작업완료 스위치 부저");
            IONaming(DO.HIPOT_START_SW_LAMP,          "HIPOT",                "작업시작 스위치 램프");
            IONaming(DO.HIPOT_STOP_SW_LAMP,           "HIPOT",                "작업정지 스위치 램프");
            
            IONaming(DO.EOL_PALLET_UP,                "EOL",                  "파레트 상승");
            IONaming(DO.EOL_PALLET_DW,                "EOL",                  "파레트 하강");
            IONaming(DO.EOL_STOPPER_DW,               "EOL",                  "스토퍼 하강");
            IONaming(DO.EOL_PRODUCT_PUSH_ON,          "EOL",                  "측면 가압 실린더 ON");
            IONaming(DO.EOL_CAN_CONTACT_ON,           "EOL",                  "CAN 통신 실린더 ON");
            IONaming(DO.EOL_FINISH_SW_LAMP,           "EOL",                  "작업완료 스위치 램프");
            IONaming(DO.EOL_BUZZER,                   "EOL",                  "작업완료 스위치 부저");
            IONaming(DO.EOL_START_SW_LAMP,            "EOL",                  "작업시작 스위치 램프");
            IONaming(DO.EOL_STOP_SW_LAMP,             "EOL",                  "작업정지 스위치 램프");
            
            IONaming(DO.RELIFT_FINISH_LAMP,           "배출 리프트",          "작업완료 스위치 램프");
            IONaming(DO.RELIFT_BUZZER,                "배출 리프트",          "작업완료 스위치 부저");
            
            IONaming(DO.HIPOT_TOWERLAMP_RED,          "HIPOT",                "타워램프 #적색");
            IONaming(DO.HIPOT_TOWERLAMP_YELLOW,       "HIPOT",                "타워램프 #황색");
            IONaming(DO.HIPOT_TOWERLAMP_GREEN,        "HIPOT",                "타워램프 #녹색");
            IONaming(DO.HIPOT_TOWERLAMP_BUZZER,       "HIPOT",                "타워램프 #부저");
            
            IONaming(DO.EOL_TOWERLAMP_RED,            "EOL",                  "타워램프 #적색");
            IONaming(DO.EOL_TOWERLAMP_YELLOW,         "EOL",                  "타워램프 #황색");
            IONaming(DO.EOL_TOWERLAMP_GREEN,          "EOL",                  "타워램프 #녹색");
            IONaming(DO.EOL_TOWERLAMP_BUZZER,         "EOL",                  "타워램프 #부저");
            
            IONaming(DO.NUTRUNNER5_OUT1,              "NUTRUNNER #5",         "OUT #1");
            IONaming(DO.NUTRUNNER5_OUT2,              "NUTRUNNER #5",         "OUT #2");
            IONaming(DO.NUTRUNNER5_OUT3,              "NUTRUNNER #5",         "OUT #3");
            IONaming(DO.NUTRUNNER5_OUT4,              "NUTRUNNER #5",         "OUT #4");
            
            IONaming(DO.NUTRUNNER_LIFT_OUT1,          "NUTRUNNER #LIFT",      "OUT #1");
            IONaming(DO.NUTRUNNER_LIFT_OUT2,          "NUTRUNNER #LIFT",      "OUT #2");
            IONaming(DO.NUTRUNNER_LIFT_OUT3,          "NUTRUNNER #LIFT",      "OUT #3");
            IONaming(DO.NUTRUNNER_LIFT_OUT4,          "NUTRUNNER #LIFT",      "OUT #4");
            
            IONaming(DO.RELIFT_UP,                    "배출 리프트",          "리프트 상승");
            IONaming(DO.RELIFT_DW,                    "배출 리프트",          "리프트 하강");
            IONaming(DO.RELIFT_PALLET_UP,             "배출 리프트",          "파레트 상승");
            IONaming(DO.RELIFT_PALLET_DW,             "배출 리프트",          "파레트 하강");
            IONaming(DO.VISION_CLEAR,                 "OMRON 라벨검사",       "CLEAR");
            
            IONaming(DO.CAMERA1_TRIG,                 "IV500 #1",          "TRIG");
            IONaming(DO.CAMERA1_OUT0,                 "IV500 #1",          "OUT #0");
            IONaming(DO.CAMERA1_OUT1,                 "IV500 #1",          "OUT #1");
            IONaming(DO.CAMERA1_OUT2,                 "IV500 #1",          "OUT #2");
            IONaming(DO.CAMERA1_OUT3,                 "IV500 #1",          "OUT #3");
            IONaming(DO.CAMERA1_OUT4,                 "IV500 #1",          "OUT #4");
              
            IONaming(DO.CAMERA2_TRIG,                 "IV500 #2",          "TRIG");
            IONaming(DO.CAMERA2_OUT0,                 "IV500 #2",          "OUT #0");
            IONaming(DO.CAMERA2_OUT1,                 "IV500 #2",          "OUT #1");
            IONaming(DO.CAMERA2_OUT2,                 "IV500 #2",          "OUT #2");
            IONaming(DO.CAMERA2_OUT3,                 "IV500 #2",          "OUT #3");
            IONaming(DO.CAMERA2_OUT4,                 "IV500 #2",          "OUT #4");


        }



        // 출력 메세지
        public static string[,] strOutPutMessage = { 
                                                   { "제품 검사가 이뤄지지 않았습니다."             , "-"               , "没进行产品检测" },                                         
                                                   { "바코드 리딩이 모두 이뤄지지 않았습니다."      , "-"               , "没阅读完条形码" },                                         
                                                   { "Fuse 검사가 이뤄지지 않았습니다."             , "-"               , "Fuse没进行检测" },                                         
                                                   { "파레트가 정위치가 아닙니다."                  , "-"               , "托盘位置不定位" },                                          
                                                   { "메인컨베어가 동작중이 아닙니다."              , "-"               , "主传送带不在运行" },                                        
                                                   { "다음 스테이션이 준비상태가 아닙니다."         , "-"               , "下一个工站还没准备状态" },                                 
                                                   { "제품 배출 타임아웃."                          , "-"               , "产品排出时间超过" },                                       
                                                   { "검사기 커뮤니케이션 실패."                    , "-"               , "检测机通讯失败" },                                         
                                                   { "바코드 리딩 실패."                            , "-"               , "条形码阅读失败" },                                         
                                                   { "컨택 상태 입니다."                            , "-"               , "连接状态" },                                                
                                                   { "미체결된 팁이 있습니다."                      , "-"               , "有未打的螺丝" },                                            
                                                   { "하층 컨베어 파레트가 가득 찼습니다."          , "-"               , "下层传送带的托盘满了" },                                   
                                                   { "리턴리프트 커넥트가 정위치가 아닙니다."       , "-"               , "通讯Cable没有感应" },                                       
                                                   { "팁 체결 불량."                                , "-"               , "打螺丝不良" },                                              
                                                   { "팁 선택 오류."                                , "-"               , "Tip选择错误" },                                            
                                                   { "해당 팁 체결 완료."                           , "-"               , "相应Tip的螺丝打完" },                                       
                                                   { "해당 CMA 모델 설정 에러."                     , "-"               , "相应CMA型号设定错误" },                                    
                                                   { "CMA 로딩 제품 감지 에러."                     , "-"               , "CMA感应错误" },                                             
                                                   { "파레트 준비가 이뤄지지 않았습니다."           , "-"               , "没有安装Base plate" },                                      
                                                   { "정상적인 바코드가 아닙니다."                  , "-"               , "不是正常的条形码" },                                        
                                                   { "중복 바코드 입니다."                          , "-"               , "条形码重复" },                                              
                                                   { "CMA 스캔 개수를 초과 하였습니다."             , "-"               , "超过了CMA扫描的个数" },                                    
                                                   { "CMA 검사 불량 제품 입니다."                   , "-"               , "是检查为CMA不良产品" },                                    
                                                   { "CMA 검사 정보가 없습니다."                    , "-"               , "CMA检测信息不存在" },                                       
                                                   { "CMA 검사 정보가 정확하지 않습니다."           , "-"               , "CMA检测信息不准确" },                                       
                                                   { "출력 실패."                                   , "-"               , "打印失败" },                                                
                                                   { "헤드 열림."                                   , "-"               , "打印头打开" },                                              
                                                   { "일시 정지."                                   , "-"               , "暂时停止" },                                                
                                                   //{ "리본 없음."                                   , "-"               , "没有碳带" },                                                
                                                   { "용지 없음."                                   , "-"               , "没有Label" },                                               
                                                   { "충방전 시험기가 응답하지 않습니다."           , "-"               , "充放电测试机没回应" },                                     
                                                   { "충방전 불량."                                 , "-"               , "充放电不良" },                                              
                                                   { "검사중 문열림 감지."                          , "-"               , "检测中开门感知" },                                         
                                                   { "검사기가 응답하지 않습니다."                  , "-"               , "测试机没回应" },                                           
                                                   { "Master PC Communication Fail."                , "-"               , "Master PC Communication Fail." },                           
                                                   };                                                                                                                                  



        // DI 네임할당
        public static void IONaming(DI nIndex, string str1, string str2)
        {
            DITable[0].Rows[(int)nIndex]["Cate"] = str1;
            DITable[0].Rows[(int)nIndex]["Comment"] = str2;
        }

        // DO 네임할당
        public static void IONaming(DO nIndex, string str1, string str2)
        {
            DOTable[0].Rows[(int)nIndex]["Cate"] = str1;
            DOTable[0].Rows[(int)nIndex]["Comment"] = str2;
        }
    }


    // TPC 스테이터스
    public enum TPC_STAT
    {
        READY,
        OK,
        VNG,
        TNG,
        PSELECTOK,
        FINISH,
        HOME,
        PSELECTNG,
        PSTARTOK,
    }


    public enum OutPutMessage
    {
        TEST_NOT_COMPLATE,
        READ_NOT_COMPLATE,
        FUSE_NOT_COMPLATE,
        PALLET_NOT_CENTER,
        MAIN_CV_NOT_RUNNING,
        NEXT_STATION_NOT_READY,
        PALLET_OUTPUT_TIMEOUT,
        TESTER_COM_FAIL,
        BCD_READ_FAIL,
        CONTACT_ING,
        TITE_NOT_COMPLATE,
        UNDER_CV_FULL,
        RELIFT_CONNECT_NOT_CENTER,
        TITE_NG,
        TIP_SELECT_ERROR,
        SELECT_TIP_COMPLATE,
        CMA_MODEL_ERROR,
        CMA_LOADING_PRODUCT_ERROR,
        EMPTY_BASEPLATE,
        BCD_NG,
        DUPLE_BCD,
        CMA_COUNT_OVER,
        CMA_TESTINFO_NG,
        CMA_TESTINFO_EMPTY,
        CMA_TESTINFO_ERROR,
        PRINT_FAIL,
        PRINT_HEAD_OPEN,
        PRINT_PAUSE,
        PRINT_LABEL_EMPTY,
        CHARGER_COM_FAIL,
        CHARGER_NG,
        TEST_DOOR_OPEN,
        TESTER_NOT_RETURN,
        MASTER_PC_NG,
    }


    enum DI
    {
        
        EMG_SW                      = 0x000,
        
        AIR_PRESSURE                = 0x001,
        
        CV_ON_SW                    = 0x002,
        CV_OFF_SW                   = 0x003,
        
        INVERTER1_ALARM             = 0x004,                // 메인 컨베어
        INVERTER1_RUN               = 0x005,                // 메인 컨베어
        INVERTER2_ALARM             = 0x006,                // 투입 리프트
        INVERTER2_RUN               = 0x007,                // 투입 리프트
        
        LOADING_START_SW            = 0x008,                
        
        CMA_LOADING_CLAMP1_ON       = 0x009,
        CMA_LOADING_CLAMP1_OFF      = 0x00A,
        CMA_LOADING_CLAMP2_ON       = 0x00B,
        CMA_LOADING_CLAMP2_OFF      = 0x00C,

        INLIFT_UP                   = 0x00D,
        INLIFT_DW                   = 0x00E,
        INLIFT_PALLET_UP            = 0x00F,
        INLIFT_PALLET_DW            = 0x010,
        INLIFT_PALLET_END           = 0x011,
        INLIFT_PALLET_SLOWPOINT     = 0x012,
        INLIFT_PRODUCT_BASEPLATE    = 0x013,
        INLIFT_PRODUCT_CMA          = 0x014,
        
        UNDER_CV_PALLET_END         = 0x015,
        UNDER_CV_STOPPER_UP         = 0x016,
        UNDER_CV_STOPPER_DW         = 0x017,
        
        LOADING_JIG_POSITION        = 0x018,
        
        BETWEEN_INLIFT_CV           = 0x019,

        LOADING_DOOR1               = 0x01B,
        LOADING_DOOR2               = 0x01C,
        
        SMEMA_IN1                   = 0x01D,
        SMEMA_IN2                   = 0x01E,
        SMEMA_IN3                   = 0x01F,

        STATION1_PALLET             = 0x020,
        STATION1_CENTER             = 0x021,
        STATION1_LOCK_OFF           = 0x022,
        STATION1_BREAK_OFF          = 0x023,
        STATION1_PALLET_UP          = 0x024,
        STATION1_PALLET_DW          = 0x025,
        STATION1_FINISH_SW          = 0x026,
        STATION1_FOOT_SW            = 0x027,

        STATION2_PALLET             = 0x028,
        STATION2_CENTER             = 0x029,
        STATION2_LOCK_OFF           = 0x02A,
        STATION2_BREAK_OFF          = 0x02B,
        STATION2_PALLET_UP          = 0x02C,
        STATION2_PALLET_DW          = 0x02D,
        STATION2_FINISH_SW          = 0x02E,
        STATION2_FOOT_SW            = 0x02F,

        STATION3_PALLET             = 0x030,
        STATION3_CENTER             = 0x031,
        STATION3_LOCK_OFF           = 0x032,
        STATION3_BREAK_OFF          = 0x033,
        STATION3_PALLET_UP          = 0x034,
        STATION3_PALLET_DW          = 0x035,
        STATION3_FINISH_SW          = 0x036,
        STATION3_FOOT_SW            = 0x037,
        
        STATION4_PALLET             = 0x038,
        STATION4_CENTER             = 0x039,
        STATION4_LOCK_OFF           = 0x03A,
        STATION4_BREAK_OFF          = 0x03B,
        STATION4_PALLET_UP          = 0x03C,
        STATION4_PALLET_DW          = 0x03D,
        STATION4_FINISH_SW          = 0x03E,
        STATION4_FOOT_SW            = 0x03F,

        STATION1_TIP1               = 0x040,
        STATION1_TIP2               = 0x041,
        STATION1_TIP3               = 0x042,
        STATION1_TIP4               = 0x043,
        STATION1_TIP5               = 0x044,
        STATION1_TIP6               = 0x045,
        STATION1_TIP7               = 0x046,
        STATION1_TIP8               = 0x047,

        STATION2_TIP1               = 0x048,
        STATION2_TIP2               = 0x049,
        STATION2_TIP3               = 0x04A,
        STATION2_TIP4               = 0x04B,
        STATION2_TIP5               = 0x04C,
        STATION2_TIP6               = 0x04D,
        STATION2_TIP7               = 0x04E,
        STATION2_TIP8               = 0x04F,

        STATION3_TIP1               = 0x050,
        STATION3_TIP2               = 0x051,
        STATION3_TIP3               = 0x052,
        STATION3_TIP4               = 0x053,
        STATION3_TIP5               = 0x054,
        STATION3_TIP6               = 0x055,
        STATION3_TIP7               = 0x056,
        STATION3_TIP8               = 0x057,
                                         
        STATION4_TIP1               = 0x058,
        STATION4_TIP2               = 0x059,
        STATION4_TIP3               = 0x05A,
        STATION4_TIP4               = 0x05B,
        STATION4_TIP5               = 0x05C,
        STATION4_TIP6               = 0x05D,
        STATION4_TIP7               = 0x05E,
        STATION4_TIP8               = 0x05F,


        NUTRUNNER1_IN1              = 0x060,
        NUTRUNNER1_IN2              = 0x061,
        NUTRUNNER1_IN3              = 0x062,
        NUTRUNNER1_IN4              = 0x063,

        NUTRUNNER2_IN1              = 0x064,
        NUTRUNNER2_IN2              = 0x065,
        NUTRUNNER2_IN3              = 0x066,
        NUTRUNNER2_IN4              = 0x067,

        
        NUTRUNNER3_IN1              = 0x068,
        NUTRUNNER3_IN2              = 0x069,
        NUTRUNNER3_IN3              = 0x06A,
        NUTRUNNER3_IN4              = 0x06B,

        
        NUTRUNNER4_IN1              = 0x06C,
        NUTRUNNER4_IN2              = 0x06D,
        NUTRUNNER4_IN3              = 0x06E,
        NUTRUNNER4_IN4              = 0x06F,

        ROBOT_IN1                   = 0x070,
        ROBOT_IN2                   = 0x071,
        ROBOT_IN3                   = 0x072,
        ROBOT_IN4                   = 0x073,

        STATION5_TIP1               = 0x080,
        STATION5_TIP2               = 0x081,
        STATION5_TIP3               = 0x082,
        STATION5_TIP4               = 0x083,
        STATION5_TIP5               = 0x084,
        STATION5_TIP6               = 0x085,
        STATION5_TIP7               = 0x086,
        STATION5_TIP8               = 0x087,

        LIFT_TIP1                   = 0x088,
        LIFT_TIP2                   = 0x089,
        LIFT_TIP3                   = 0x08A,
        LIFT_TIP4                   = 0x08B,
        LIFT_TIP5                   = 0x08C,
        LIFT_TIP6                   = 0x08D,
        LIFT_TIP7                   = 0x08E,
        LIFT_TIP8                   = 0x08F,

        NUTRUNNER5_IN1              = 0x090,
        NUTRUNNER5_IN2              = 0x091,
        NUTRUNNER5_IN3              = 0x092,
        NUTRUNNER5_IN4              = 0x093,

        NUTRUNNER6_IN1              = 0x094,
        NUTRUNNER6_IN2              = 0x095,
        NUTRUNNER6_IN3              = 0x096,
        NUTRUNNER6_IN4              = 0x097,

        HIPOT_CABLE1                = 0x098,
        HIPOT_CABLE2                = 0x099,

        EOL_CABLE1                  = 0x09A,
        EOL_CABLE2                  = 0x09B,
        EOL_CABLE3                  = 0x09C,
        EOL_CABLE4                  = 0x09D,
        EOL_CABLE5                  = 0x09E,

        HIPOT_PALLET                = 0x0A0,
        HIPOT_PRODUCT               = 0x0A1,
        HIPOT_PALLET_UP             = 0x0A2,
        HIPOT_PALLET_DW             = 0x0A3,
        HIPOT_CAN_ON                = 0x0A4,
        HIPOT_CAN_OFF               = 0x0A5,
        HIPOT_PRODUCT_PUSH1_ON      = 0x0A6,
        HIPOT_PRODUCT_PUSH1_OFF     = 0x0A7,
        HIPOT_PRODUCT_PUSH2_ON      = 0x0A8,
        HIPOT_PRODUCT_PUSH2_OFF     = 0x0A9,
        HIPOT_FINISH_SW             = 0x0AA,
        HIPOT_READY_SW              = 0x0AB,
        HIPOT_STOP_SW               = 0x0AC,

        EOL_PALLET                  = 0x0AE,
        EOL_PRODUCT                 = 0x0AF,
        EOL_PALLET_UP               = 0x0B0,
        EOL_PALLET_DW               = 0x0B1,
        EOL_CAN_ON                  = 0x0B2,
        EOL_CAN_OFF                 = 0x0B3,
        EOL_PRODUCT_PUSH1_ON        = 0x0B4,
        EOL_PRODUCT_PUSH1_OFF       = 0x0B5,
        EOL_PRODUCT_PUSH2_ON        = 0x0B6,
        EOL_PRODUCT_PUSH2_OFF       = 0x0B7,
        EOL_FINISH_SW               = 0x0B8,
        EOL_READY_SW                = 0x0B9,
        EOL_STOP_SW                 = 0x0BA,

        RELIFT_CAN_CABLE_ALIGN      = 0x0BB,
        RELIFT_PALLET_END           = 0x0BC,
        RELIFT_PALLET_SLOWPOINT     = 0x0BD,
        RELIFT_CAN_CABLE_CHECK      = 0x0BE,
        RELIFT_SAFTY                = 0x0BF,
        BETWEEN_RELIFT_CV           = 0x0C0,
        RELIFT_UP                   = 0x0C1,
        RELIFT_DW                   = 0x0C2,
        RELIFT_PALLET_UP            = 0x0C3,
        RELIFT_PALLET_DW            = 0x0C4,
        RELIFT_FINISH_SW            = 0x0C5,
        
        UNDER_CV_PALLET_FULL        = 0x0C6,

        CAMERA1_TOTAL               = 0x0C8,           
        CAMERA1_BUSY                = 0x0C9,
        CAMERA1_ERROR               = 0x0CA,
        CAMERA1_IN4                 = 0x0CB,

        CAMERA2_TOTAL               = 0x0CC,           
        CAMERA2_BUSY                = 0x0CD,
        CAMERA2_ERROR               = 0x0CE,
        CAMERA2_IN4                 = 0x0CF,

        HIPOT_N_POS1                = 0x0D0,
        HIPOT_N_POS2                = 0x0D1,
        HIPOT_G_POS1                = 0x0D2,
        HIPOT_G_POS2                = 0x0D3,
        HIPOT_G_POS3                = 0x0D4,
        EOL_N_POS1                  = 0x0D5,
        EOL_N_POS2                  = 0x0D6,
                
        STATION5_PALLET             = 0x0D8,
        STATION5_CENTER             = 0x0D9,
        STATION5_LOCK_OFF           = 0x0DA,
        STATION5_BREAK_OFF          = 0x0DB,
        STATION5_PALLET_UP          = 0x0DC,
        STATION5_PALLET_DW          = 0x0DD,
        STATION5_FINISH_SW          = 0x0DE,
        STATION5_FOOT_SW            = 0x0DF,

        AIR_PRESSURE2               = 0x0E0,
        VISION_OK                   = 0x0E1,
        VISION_NG                   = 0x0E2,

        INVERTER3_ALARM             = 0x0FB,
        INVERTER3_RUN               = 0x0FC,

        MAIN_DOOR1                  = 0x0FD,
        MAIN_DOOR2                  = 0x0FE,
        MAIN_DOOR3                  = 0x0FF,
    }




    enum DO
    {
        LP1_SERVO_ON                = 0x000,
        MAIN_CV_ON                  = 0x001,

        INLIFT_CV_ON                = 0x002,
        INLIFT_CV_REV               = 0x003,
        INLIFT_CV_FAST              = 0x004,
        INLIFT_CV_SLOW              = 0x005,

        CV_ON_SW_LAMP               = 0x006,
        CV_OFF_SW_LAMP              = 0x007,
        LOADING_START_SW_LAMP       = 0x008,
        LOADING_START_SW_BUZZER     = 0x009,

        CMA_LOADING_CLAMP_ON        = 0x00A,
        CMA_LOADING_CLAMP_OFF       = 0x00B,

        INLIFT_UP                   = 0x00C,
        INLIFT_DW                   = 0x00D,
        INLIFT_PALLET_UP            = 0x00E,
        INLIFT_PALLET_DW            = 0x00F,

        UNDER_CV_STOPPER_DW         = 0x010,

        MAIN_TOWERLAMP_RED          = 0x019,
        MAIN_TOWERLAMP_YELLOW       = 0x01A,
        MAIN_TOWERLAMP_GREEN        = 0x01B,
        MAIN_TOWERLAMP_BUZZER       = 0x01C,

        SMEMA_OUT1                  = 0x01D,
        SMEMA_OUT2                  = 0x01E,
        SMEMA_OUT3                  = 0x01F,

        STATION1_PALLET_UP          = 0x020,
        STATION1_PALLET_DW          = 0x021,
        STATION1_LOCK_OFF           = 0x022,
        STATION1_BREAK_OFF          = 0x023,
        STATION1_STOPPER_DW         = 0x024,
        STATION1_FINISH_SW_LAMP     = 0x025,
        STATION1_BUZZER             = 0x026,
        
        STATION2_PALLET_UP          = 0x027,
        STATION2_PALLET_DW          = 0x028,
        STATION2_LOCK_OFF           = 0x029,
        STATION2_BREAK_OFF          = 0x02A,
        STATION2_STOPPER_DW         = 0x02B,
        STATION2_FINISH_SW_LAMP     = 0x02C,
        STATION2_BUZZER             = 0x02D,
        
        STATION3_PALLET_UP          = 0x02E,
        STATION3_PALLET_DW          = 0x02F,
        STATION3_LOCK_OFF           = 0x030,
        STATION3_BREAK_OFF          = 0x031,
        STATION3_STOPPER_DW         = 0x032,
        STATION3_FINISH_SW_LAMP     = 0x033,
        STATION3_BUZZER             = 0x034,

        STATION4_PALLET_UP          = 0x035,
        STATION4_PALLET_DW          = 0x036,
        STATION4_LOCK_OFF           = 0x037,
        STATION4_BREAK_OFF          = 0x038,
        STATION4_STOPPER_DW         = 0x039,
        STATION4_FINISH_SW_LAMP     = 0x03A,
        STATION4_BUZZER             = 0x03B,
        
        NUTRUNNER1_OUT1             = 0x040,
        NUTRUNNER1_OUT2             = 0x041,
        NUTRUNNER1_OUT3             = 0x042,
        NUTRUNNER1_OUT4             = 0x043,

        NUTRUNNER2_OUT1             = 0x044,
        NUTRUNNER2_OUT2             = 0x045,
        NUTRUNNER2_OUT3             = 0x046,
        NUTRUNNER2_OUT4             = 0x047,

        NUTRUNNER3_OUT1             = 0x048,
        NUTRUNNER3_OUT2             = 0x049,
        NUTRUNNER3_OUT3             = 0x04A,
        NUTRUNNER3_OUT4             = 0x04B,

        NUTRUNNER4_OUT1             = 0x04C,
        NUTRUNNER4_OUT2             = 0x04D,
        NUTRUNNER4_OUT3             = 0x04E,
        NUTRUNNER4_OUT4             = 0x04F,
        
        ROBOT_OUT1                  = 0x050,
        ROBOT_OUT2                  = 0x051,
        ROBOT_OUT3                  = 0x052,
        ROBOT_OUT4                  = 0x053,

        

        LP3_SERVO_ON                = 0x060,

        RELIFT_CV_ON                = 0x061,
        RELIFT_CV_REV               = 0x062,
        RELIFT_CV_FAST              = 0x063,
        RELIFT_CV_SLOW              = 0x064,

        STATION5_PALLET_UP          = 0x065,
        STATION5_PALLET_DW          = 0x066,
        STATION5_LOCK_OFF           = 0x067,
        STATION5_BREAK_OFF          = 0x068,
        STATION5_STOPPER_DW         = 0x069,
        STATION5_FINISH_SW_LAMP     = 0x06A,
        STATION5_BUZZER             = 0x06B,

        HIPOT_PALLET_UP             = 0x06C,
        HIPOT_PALLET_DW             = 0x06D,
        HIPOT_STOPPER_DW            = 0x06E,
        HIPOT_PRODUCT_PUSH_ON       = 0x06F,
        HIPOT_CAN_CONTACT_ON        = 0x070,
        HIPOT_FINISH_SW_LAMP        = 0x071,
        HIPOT_BUZZER                = 0x072,
        HIPOT_START_SW_LAMP         = 0x073,
        HIPOT_STOP_SW_LAMP          = 0x074,

        EOL_PALLET_UP               = 0x075,
        EOL_PALLET_DW               = 0x076,
        EOL_STOPPER_DW              = 0x077,
        EOL_PRODUCT_PUSH_ON         = 0x078,
        EOL_CAN_CONTACT_ON          = 0x079,
        EOL_FINISH_SW_LAMP          = 0x07A,
        EOL_BUZZER                  = 0x07B,
        EOL_START_SW_LAMP           = 0x07C,
        EOL_STOP_SW_LAMP            = 0x07D,

        RELIFT_FINISH_LAMP          = 0x07E,
        RELIFT_BUZZER               = 0x07F,

        HIPOT_TOWERLAMP_RED         = 0x080,
        HIPOT_TOWERLAMP_YELLOW      = 0x081,
        HIPOT_TOWERLAMP_GREEN       = 0x082,
        HIPOT_TOWERLAMP_BUZZER      = 0x083,

        EOL_TOWERLAMP_RED           = 0x084,
        EOL_TOWERLAMP_YELLOW        = 0x085,
        EOL_TOWERLAMP_GREEN         = 0x086,
        EOL_TOWERLAMP_BUZZER        = 0x087,

        NUTRUNNER5_OUT1             = 0x088,
        NUTRUNNER5_OUT2             = 0x089,
        NUTRUNNER5_OUT3             = 0x08A,
        NUTRUNNER5_OUT4             = 0x08B,

        NUTRUNNER_LIFT_OUT1         = 0x08C,
        NUTRUNNER_LIFT_OUT2         = 0x08D,
        NUTRUNNER_LIFT_OUT3         = 0x08E,
        NUTRUNNER_LIFT_OUT4         = 0x08F,

        RELIFT_UP                   = 0x090,
        RELIFT_DW                   = 0x091,
        RELIFT_PALLET_UP            = 0x092,
        RELIFT_PALLET_DW            = 0x093,
        VISION_CLEAR                = 0x094,

        CAMERA1_TRIG                = 0x0A0,
        CAMERA1_OUT0                = 0x0A1,
        CAMERA1_OUT1                = 0x0A2,
        CAMERA1_OUT2                = 0x0A3,
        CAMERA1_OUT3                = 0x0A4,
        CAMERA1_OUT4                = 0x0A5,

        CAMERA2_TRIG                = 0x0A6,
        CAMERA2_OUT0                = 0x0A7,
        CAMERA2_OUT1                = 0x0A8,
        CAMERA2_OUT2                = 0x0A9,
        CAMERA2_OUT3                = 0x0AA,
        CAMERA2_OUT4                = 0x0AB,

        CABLE_INFO_OUT              = 0x0AF,
    }





    // 프로세스 리스트
    public enum PROC_LIST
    {
        MAIN,
        CMA_MOVE,
        INLIFT,
        ST1,
        ST2,
        ST3,
        ST4,
        ST5,
        ST6,
        ST7,
        RELIFT,
        HIPOT,
        SUB_TITE1,
        SUB_TITE2,
        SUB_TITE3,
        SUB_TITE4,
        SUB_TITE5,
        HIPOT_SW,
        EOL_SW,
        SUB_HOME_SEARCH,
        TOWER_LAMP,
        TOWER_BUZZER,
        COUNT_BUZZER1,
        COUNT_BUZZER2,
        COUNT_BUZZER3,
        COUNT_BUZZER4,
        COUNT_BUZZER5,
        COUNT_BUZZER6,
        COUNT_BUZZER7,
        COUNT_BUZZER8,
        COUNT_BUZZER9,
        STATION6_LAMP,
        STATION7_LAMP,
        COUNT_COMM1,
        COUNT_COMM2,
        COUNT_COMM3,
        COUNT_COMM4,
        COUNT_COMM5,
        COUNT_COMM6,
        SUB_LOADING_SW,
        SUB_LOADING,
        BARCODE_READ,
        ETC_BCD_READ,
        SMEMA,
        MANUAL,
        HIPOT_TL,
        EOL_TL,
        CMA_TURN,
        ST3_ROBOT,
        ROBOT_IO,
        SUB_ST1_BARCODE,
        MARKING,
        MARKING_READ,
    }




    // 모션 축
    public enum AXIS
    {
        X,
        Y,
        R,
        Z,
        HIPOT_1X,
        HIPOT_1Y,
        HIPOT_1Z,
        HIPOT_2X,
        HIPOT_2Y,
        HIPOT_2Z,
        EOL_X,
        EOL_Y,
        EOL_Z,
        ST3_R,
        CAMERA1_X,
        CAMERA1_Y,
        CAMERA1_Z,
        CAMERA2_X,
        CAMERA2_Y,
        CAMERA2_Z,
        MAX_COUNT,
    }



    // 에러 및 알람코드
    public enum ERR_CODE
    {
        NONE            = 0x00000000,
        NO_ORG          = 0x00000001,
        DIO_UNIT1       = 0x00000002,
        DIO_UNIT2       = 0x00000004,
        EMG_SW          = 0x00000008,
        AIR_PRESSURE    = 0x00000010,
        CYL_TIMEOUT     = 0x00000020,
        X               = 0x00000040,
        Y               = 0x00000080,
        R               = 0x00000100,
        Z               = 0x00000200,
        HIPOT_1X        = 0x00000400,
        HIPOT_1Y        = 0x00000800,
        HIPOT_1Z        = 0x00001000,
        HIPOT_2X        = 0x00002000,
        HIPOT_2Y        = 0x00004000,
        HIPOT_2Z        = 0x00008000,
        EOL_X           = 0x00010000,
        EOL_Y           = 0x00020000,
        EOL_Z           = 0x00040000,
        ST3_R           = 0x00080000,
        CAMERA1_X       = 0x00100000,
        CAMERA1_Y       = 0x00200000,
        CAMERA1_Z       = 0x00400000,
        CAMERA2_X       = 0x00800000,
        CAMERA2_Y       = 0x01000000,
        CAMERA2_Z       = 0x02000000,
    }



    public enum TEST_RESULT
    {
        READY,
        PASS,
        OK,
        NG,
        ING,
    }


    // 메인알람 타이머
    public enum MAINALAM_TIME
    {
        SERVO,
        MAIN,
        AIR,
        DOOR,
    }


    public enum ALARM_CODE
    {
        NONE = 0x00000000,
        CYL_TIMEOUT = 0x00000001,
        SAFE_SENSOR = 0x00000002,
        DOOR_SENSOR = 0x00000004,
    }

    public enum CONTACT_STATUS
    {
        CONTACT_READY,
        CONTACT_ING,
        CONTACT_OK,
        CONTACT_NG,
        CONTACT_ALARM,
    }

    // 메인 상태
    public enum MAIN_STATUS
    {
        NO_INIT,
        INIT,
        READY,
        RUNNING,
        PAUSE,
        STOPPING,
        STOP,
        SYSTEM_ERR,
        ALARM,
    }

    public enum LAMP_COLOR
    {
        TL_RED,
        TL_YELLOW,
        TL_GREEN,
        TL_BUZZER,
    }



    public enum BatteryTesterStat
    {
        READY,
        START,
        ING,
        END,
        NOREAD,
        READ,
        OK,
        NG,
        COMMNG,
        FOWARD,
        BACKWARD,
    }


    // 로그 스타일
    public enum LOG_TYPE
    {
        LOG,
        ERROR,
        INFO,
    }

    // 타워램프
    public enum TOWER_LAMP
    {
        TL_OFF,
        TL_ON,
        TL_BLINK,
    }

    public enum START_INFO
    {
        READY,
        OK,
        NG,
        CANCEL,
    }


    // 스테이션 리스트
    public enum STATION_LIST
    {
        //TR,
        LOADING,
        IN_LIFT,
        ST1,
        ST2,
        ST3,
        ST4,
        ST5,
        ST6,
        ST7,
        UNLOADING,

    }

    public static class _SysInfo
    {
        // MainProcess 관련
        public static bool bMainProcessStop;

        public static bool bPressStartButton;		    //작업시작버튼눌림
        public static bool bPressStopButton;			//작업중지버튼눌림
        public static bool bPressSystemInitButton;	    //시스템초기화 버튼눌림
        public static bool bErrorClear;				    //에러클리어
        public static bool bBuzzerOff;				    //부저끄기
        public static bool bAutoRunning;				//자동운전중
        public static bool bAutoRunStop;				//자동운전 정지
        public static bool bAutoCycleStop;			    //현재행정 완료후 정지

        public static short nManualCommand;				//매뉴얼 커맨드 인덱스
        public static bool bManualCommand_ing;		    //매뉴얼 커맨드 수행중	
        public static bool bManualCommand_stop;		//매뉴얼 커맨드 수행정지	
        public static bool bFirst;
        public static bool[] bAutoLock_ing = new bool[5];           // 체결존 작업중
        public static bool[] bAutoLockComplated = new bool[5];	    // 체결존 작업완료됨


        public static bool[] bContact_ing = new bool[2];            // 컨택 작업 중


        public static double[] dbManualMovePos = new double[10];    // 수동 조작시 임시 저장될 포지션

        // 타워 램프 
        public static TOWER_LAMP TL_Red;
        public static TOWER_LAMP TL_Yellow;
        public static TOWER_LAMP TL_Green;
        public static TOWER_LAMP TL_Buzzer;

        public static TOWER_LAMP[] ST_Red = new TOWER_LAMP[2];
        public static TOWER_LAMP[] ST_Yellow = new TOWER_LAMP[2];
        public static TOWER_LAMP[] ST_Green = new TOWER_LAMP[2];
        public static TOWER_LAMP[] ST_Buzzer = new TOWER_LAMP[2];

        public static TOWER_LAMP[] ST_TL_RED = new TOWER_LAMP[2];
        public static TOWER_LAMP[] ST_TL_YELLOW = new TOWER_LAMP[2];
        public static TOWER_LAMP[] ST_TL_GREEN = new TOWER_LAMP[2];

        public static int nTL_Beep;
        public static int[] nCount_Beep = new int[20];

        public static int nEOLRetryCount;


        // 에러 코드
        public static ERR_CODE Err_Code;
        public static ERR_CODE Old_Err_Code;

        // 알람코드
        public static ALARM_CODE Alarm_Code;
        public static ALARM_CODE Old_Alarm_Code;

        // 서보 에러 감시
        public static bool bServoErrMonitor;

        // 메인 상태
        public static MAIN_STATUS Main_Status;

        public static int[,] nTipMaxCount = new int[6, 10];
        public static int[,] nTipNowCount = new int[6, 10];


        public static bool[] bTiteOk = new bool[6];

        public static bool[] bTiteInfoClear = new bool[6];

        public static int[] nTiteLog = new int[6];

        // 체결작업 진행 여부
        public static bool[] bTite_Ing = new bool[6];

        // 현재 사용중인 팁
        public static int[] nNowUseTip = new int[6];
        public static int[] nNowUseTipCount = new int[6];

        public static bool bOutLiftPalletCall;


        public static bool[] bPrePalletCall = new bool[20];
        public static bool[] bNextPalletOut = new bool[20];
        public static bool[] bScanSTTestOKNG = new bool[20];

        public static bool bLoadingClampOn;

        public static bool bPackLoadFail;

        public static bool bInLiftReady;
        public static bool bLoadingReadySw;

        public static int nLoadingWorkIndex;

        public static bool bLoading_ing;
        public static bool bLoadingComplated;

        public static int nMotorCount;

        public static int nMotorSearchErrCnt;

        public static bool[] bOutTryPossible = new bool[9];

        public static bool bLiftOutComplated;


        public static bool[] bLoading_View_Ing = new bool[14];
        public static bool[] bLoading_View_Complated = new bool[14];

        public static string strReadBCDData = "";
        public static string strCompareBCD = "";
        public static string strReadPalletBCD = "";

        public static string strST1ReadBCDData = "";
        public static string strST1CompareBCD = "";

        public static string strSt1ReadPalletBarcode = "";
        public static bool bSt1ReadPalletBarcode;


        public static bool[] bAlarmFlag = new bool[30];


        public static int nST1CmaCount;
        public static bool bST1BCDReadAllOk;

        public static int nCmaCount;
        public static int nBmsCount;
        public static int nFuseCount;
        public static int nRearCount;
        public static bool bBCDReadAllOk;
        public static bool bBCDAddFlag;
        public static bool bST1BCDAddFlag;

        public static bool bPalletBCDReadOK;

        public static bool bBCDCMAReadOk;
        public static bool bBCDBMSReadOk;

        

        public static CONTACT_STATUS[] eContactStatus = new CONTACT_STATUS[2];


        public static bool[] bStationReservation = new bool[20];

        public static bool[] bContactTestOk = new bool[2];
        public static bool[] bAutoContactComplated = new bool[2];

        public static bool[] bContactTestNg = new bool[2];
        public static bool[] bContactOneTime = new bool[2]; // 컨택을 한번이라도 했는지 체크

        


        public static bool bManualEstop;

        public static bool bETCReadOk;
        public static string strETCReadData = "";


        public static bool bScanSTTesetFinish;
        public static bool bScanSTTesetOK;

        public static bool[] bStationAutoMode = new bool[50];

        public static START_INFO eLoadingInfoSetOk = new START_INFO();
        public static START_INFO[] eChargeStartInfo = new START_INFO[10];
        public static START_INFO eTRInfoSetOk = new START_INFO();


        public static int nNowPrintCount;


        public static bool bMoveClampPickUpReady;
        public static bool bMoveClampTRUnClampOk;
        public static bool bMoveClampClampOk;
        public static bool bMoveClampPickUpComplate;



        public static bool bPreMachinMoveIng;
        public static bool bPreMachinMoveCall;


        public static int[,] nBoltNeed = new int[4, 5];
        public static bool[,] bBoltSupply = new bool[4, 5];
        public static bool[,] bBoltReady = new bool[4, 6];

        public static bool[] bFeederStop = new bool[4];
        public static bool[] bFeederReady = new bool[4];

        public static bool[] bTransferRev = new bool[3];

        public static bool[] bCountUnlock = new bool[6];
        public static bool[] bUpCountUnlock = new bool[6];

        public static int nRevStep;

        public static bool[] bRevStatus = new bool[3];


        public static bool bModelChangeFirstLoading;

        public static int[] nPsetOldIndex = new int[6];

        public static bool bTurn_TR_Move_Able = new bool();





        public static bool bCVMainOn;

        public static int nFileWriteTestCount;


        public static bool bNeedHipotMessageView;
        public static bool bNeedEolMessageView;


        public static bool bETCScan1;
        public static bool bETCScan2;

        public static int nBlinkCount;


        public static bool bTRTurnUnitProduct;


        public static int nHipotTestStep;

        public static int nIRTestTimeCount;     // 절연저항 테스트 시간 카운트

        public static double dbIRTestMode;

        public static string strReWorkBCD;
        public static bool bReworkScanFinish;


        public static bool bETCScan3;
        public static bool bETCScan4;

        public static int nHipotStep;

        public static string strBpuBCD;

        public static string strST3NowWorkModel;
        public static int nST3ResumeResult;


        public static int bStation3NgOut;


        public static bool bST3Work2Finish;

        public static int nTPCRobotRetryCount;

        
        // EOL 재시도 관련
        public static int nEOLCommRetryCount;



        // Status관련 모니터링 용

        public static bool[] bInOldStatTm = new bool[4];
        public static bool[] bOutOldStatTm = new bool[4];


        public static bool[] bInOldStatNut = new bool[4];
        public static bool[] bOutOldStatNut = new bool[4];


        public static bool bTPCReadOK;

        public static int nTPCSendRetryCount;

        public static bool bChangeHipotInfo;


        public static double dbHipot1DistanceGap;
        public static double dbHipot2DistanceGap;
        public static double dbEolDistanceGap;


        public static int nST2EncoderX;
        public static int nST2EncoderY;

        // 스테이션 2번 작업 카운트
        public static int nST2TiteWorkCount;

        public static int[] nNowSch = new int[6];

        public static int nPreWorkCount;
        public static int nReworkCount;
        public static int nEPPReadCount;

        public static bool bAlive;

        public static string strLaserReadBarcode = "";
        public static bool bLaserBarcodeCompare = false;

        public static bool bCanLaserPrint = false;

        public static int nHioptContectP;
        public static int nHioptContectN;

        public static int nOSCRetryNowCount = 0;

        public static bool bST2TiteIng = false;
    }

    // 홈서치 파라메터
    public class SEARCH_HOME_PARAM
    {

        public int nAxisSize;                                                // 축갯수
        public int[] nAxis = new int[(int)AXIS.MAX_COUNT];                   // 홈찾기 작업할 축번호
        public int[] nWorkStep = new int[(int)AXIS.MAX_COUNT];           // 해당축 스텝
        public bool[] bResult = new bool[(int)AXIS.MAX_COUNT];               // 홈찾기 결과
        public bool[] bComplete = new bool[(int)AXIS.MAX_COUNT];         // 홉찾기 완료 플래그
        public Stopwatch[] tTimer = new Stopwatch[(int)AXIS.MAX_COUNT];       // 타이머

        public void InitParam()
        {
            for (int i = 0; i < tTimer.Length; i++) tTimer[i] = new Stopwatch();
        }
    }



    // 모터 데이터
    public struct MOTOR_DATA
    {
        public double dbNegativeLimit;             // - 한계점
        public double dbPositiveLimit;             // + 한계점
        public double dbMaxSpeed;                  // 최고속도( mm / Sec )
        public double dbAccelTime;                 // 가감속 시간 ( mm / Sec ) 최대 속도에 도달하는 시간 (초)
    }





    public static class _Config
    {
        // 마지막 작업한 모델이름
        public static string strCurrentModel = "";

        // 통신 포트
        public static int nMiraeDio1;
        public static int nMiraeDio2;
        public static int nBatteryComm1;
        public static int nBatteryComm2;
        public static int nNutRunner1;
        public static int nNutRunner2;
        public static int nNutRunner3;
        public static int nNutRunner4;
        public static int nNutRunner5;
        public static int nNutRunner6;
        public static int nBcdReader;
        public static int nBcdPrinter;
        public static int nETCReader;
        public static int nBatteryChargeTest;
        public static int nTPCRobot;
        public static int nTPCRobotBaudRate;
        public static int nArmPort;
        public static int nStation1Reader;
        public static int nStation1ReaderBaudRate;

        public static int nEolReader;
        public static int nHipotReader;

        public static int nOmronWHTesterPort;
        public static string strOmronWHTesterIP;

        public static int nHipotHnadReader;
        public static int nEOLHandReader;

        // 알람 감시
        public static bool bAirPressure;

        // 기본 실린더 타임아웃 시간
        public static int nCylTimeOut;

        // Motion 관련
        public static bool bUseSoftwareLimit;
        public static double dbMotorHomeSpeed;

        // 관리자 비밀번호
        public static string strAdminPass = "";

        // 체결 카운터 변경 비밀번호
        public static string strTitePass = "";

        // 바코드 제거 비밀번호
        public static string strBarcodeAdminPass = "";


        // 관리자 비밀번호 사용여부
        public static bool bUseAdminPass;




        public static int nChatteringTime;              // 채터링 방지 시간
        public static int nSMEMAChatteringTime;              // 채터링 방지 시간

        public static double dbTestZoneMoveSpeed;       // 검사존 이동 속도
        public static double dbTestZoneContactSpeed;    // 검사존 컨텍 속도
        public static double dbTestZoneContactMovePos;    // 검사존 컨텍 속도
        public static double dbTestZoneContactZSlowMovePos;    // 검사존  컨텍 속도
        public static double dbTestZoneContactZSlowMoveSpeed;    // 검사존  컨텍 속도

        public static int nContactStabilTime;           // 컨텍 실린더 안정화 시간

        public static int nLiftCylStabilTime;           // 리프트 실린더 안정화 시간

        public static int nLiftOutTime;         // 리프트 제품 배출 지연 시간
        public static int nLiftInTime;          // 리프트 제품 투입 지연 시간

        public static double dbSafeLoadZPos;            // Z축 안전 이동 높이
        public static double dbNoClampXYMoveSpeed;      // 클램프 안했을시 이동 속도
        public static double dbNoClampZMoveSpeed;       // 클램프 안했을시 Z 이동 속도
        public static double dbClampXYMoveSpeed;        // 제품 클램프시 이동 속도
        public static double dbClampZMoveSpeed;         // 제품 클램프시 Z 이동 속도
        public static double dbZSensingHeight;          // Z축 하강시 센서감지 추가이동 거리
        public static double dbZSensingSpeed;           // Z축 하강 추가이동 속도
        public static double dbShiftMoveSpeed;          // 하강후 시프트시 이동 속도
        public static int nClampStabilTime;             // 클램프 안정화 시간
        public static int nLiftTimeOut;                 // 리프트 타임아웃


        public static bool bUseContactAutoTestMode;            // 컨텍시 자동 테스트 모드 기능 사용함
        public static bool bUseSemea;

        public static bool bUseMainCVMonitor;         // 메인컨베어 참조

        public static int nBCDAllOffsetX;           // 바코드 전체 오프셋 X
        public static int nBCDAllOffsetY;           // 바코드 전체 오프셋 Y
        public static int nBCDbcdOffsetX;           // 바코드 오프셋 X
        public static int nBCDbcdOffsetY;           // 바코드 오프셋 Y
        public static int nBCDtextOffsetX;          // 바코드 글자 오프셋 X
        public static int nBCDtextOffsetY;          // 바코드 글자 오프셋 Y

        public static int nBCDScanStation;          // 바코드 스캔 스테이션

        public static string strMESDir = "";             // MES 데이터 저장경로
        public static string strHIPOTMESDir = "";       // 하이팟 MES 저장경로


        public static string strCMACheckDir = "";

        public static bool bUseStationReservation;

        public static bool[] bUseAutoContact = new bool[2];

        public static bool bUseStopper;

        public static bool bUseST6NgByPass;

        public static int nStation5PinMaxCount;
        public static int nStation6PinMaxCount;

        public static bool[] bLockingStationSkip = new bool[5];
        public static bool[] bTestStationSkip = new bool[2];

        public static bool bUseCMAStatusCheck;


        public static bool bUseAutoLoadingReadySw;      // 자동 스위치 기능 사용함

        public static bool[] bUseSameTimeContact = new bool[2];


        public static bool bUseNutrunnerMove;

        public static string strBCDSymbol = "";      // 바코드 구분자

        public static int nETCScanStation;

        public static int nLotClearTime;

        public static bool bUseScanSTTester;

        public static int nReturnPalletOutTime;

        public static double dbTurnSpeed;
        public static double dbTurnRev;
        public static double dbLoadingAng;


        public static double dbTurnOkXp;
        public static double dbTurnOkXn;
        public static double dbTurnOkYp;
        public static double dbTurnOkYn;



        public static bool bUseBoltSupply;

        public static double dbBoltSupply1Rev;
        public static double dbBoltSupply2Rev;
        public static double dbBoltSupply3Rev;
        public static double dbBoltSupply4Rev;


        public static string strVisionDir1;
        public static string strVisionDir2;

        public static string strLangue;

        public static bool bUseLoadingDoor;
        public static bool bUseHipotDoor;
        public static bool bUseEolDoor;


        public static int nTRTurnClampTime;
        public static int nTRStabilTime;

        public static bool bMasterModelLoad;

        public static bool bPset232Select;
        public static bool bPsetTorqueMode;


        public static bool bUseHipotFix;
        public static bool bUseEolFix;

        public static bool bHipotSkip;
        public static bool bEolSkip;


        public static bool bUseCVAutoStop;
        public static int nCVAutoStopTime;


        public static bool bUseNoProductPass;

        public static bool bUseReLiftCableSensing;

        public static bool bUseOutLiftSafty;



        public static double dbCMAMoveLoadOffset;

        public static int nBCDScanTimeOut;

        public static bool bUseReworkLineMode;

        public static bool bUseReWorkTypeBCDScan;

        public static List<string> _TipName = new List<string>();

        public static double dbLoadingUnSafePosX;
        public static double dbLoadingUnSafePosZ;

        public static int nTPCRobotCommTimeOut; // TPC 로보트 커뮤니케이션 타임아웃


        public static int nManualChannelP;              // 수동 하이팟 채널 설정 P
        public static int nManualChannelN;              // 수동 하이팟 채널 설정 N
        public static int nAutoChannelP;                // 자동 하이팟 채널 설정 P
        public static int nAutoChannelN;                // 자동 하이팟 채널 설정 N

        public static string strMESDBIP;
        public static string strMESDBID;
        public static string strMESDBPASS;
        public static string strMESDBSID;
        public static int nMESDBPort;
        public static int nStartLotNum;

        public static bool bUseMESTestCheck;


        public static bool bUseLockingStationDwStay;        // 체결 스테이션 하강 대기 기능 사용함
        public static bool bUseHipotStationDwStay;        // 체결 스테이션 하강 대기 기능 사용함

        public static double dbFirstPCSheetAngle;       // 첫번째 부착 각도
        public static double dbLastPCSheetAngle;        // 마지막 부착 각도

        public static int nDistancePort;
        public static int nDistanceBaudRate;


        public static string[] strPalletBCD = new string[20];           // 파레트 바코드

        //OmronCamera 관련
        public static double dbOmronCameraXYMoveSpeed;      // 카메라 XY 이동속도
        public static double dbOmronCameraZMoveSpeed;       // 카메라 Z 이동속도
        public static int nOmronCameraStabliTime;           // 카메라 안정화 시간

        public static string strOmronWHTesterCapCMD;
        public static string strOmronWHTesterCapSch;
        public static string strOmronWHTesterCapOpt;

        public static int nCapDealy;
        public static int nFileGetDealy;

        public static string strOmronOriginImgDir;
        public static string strOmronScreenImgDir;

        //


        // === 레이저 마킹기 관련
        public static int nLaserMarkingPort;            // 마킹기 포트
        public static int nLaserMarkingBaudRate;        // 마킹기 보레이트

        public static int nLaserBCDReaderPort;          // 마킹기 스캐너 포트
        public static int nLaserBCDReaderBaudRate;      // 마킹기 보레이트

        public static string strLaserMarkingSendMsg = "";   // 마킹기에서 송신하는 메세지

        public static bool bReverseCameraXJog = false;
   
       // ===
  
        public static double[,] dbTorqueSepcMin = new double[6, 100];           // 토크 스펙 Min
        public static double[,] dbTorqueSepcMax = new double[6, 100];           // 토크 스펙 Max

        public static int[,] nAngleSepcMin = new int[6, 100];                   // 앵글 스펙 Min
        public static int[,] nAngleSepcMax = new int[6, 100];                  // 앵글 스펙 Max


        public static bool bUseNutrunnerCommCompare;                            // 너트러너 데이터 비교기능 사용


        public static bool bReWorkMode;                                         // 남경향 리웍모드


        public static bool bUseNutrunnerEthMode;                                // 너트러너 이더넷 모드





        public static bool[] bUseNutrunner = new bool[6];               // 이더넷 타입 너트러너
        public static string[] strNutrunnerIP = new string[6];          // 이더넷 타입 너트러너
        public static int[] nNutrunnerPort = new int[6];                // 이더넷 타입 너트러너



        public static string strCountUpPassword;


        public static int nAliveCheckTime;

        // 너트러너 암 XYZ 타입
        public static int nArmXYZPort;
        public static int nArmXYZBaudRate;

        public static int nOscRetryCount = 0;

    }


    [Serializable]
    public class MODEL_INFO
    {
        public MODEL_INFO()
        {
            // 클래스 초기화
            for (int i = 0; i < _TipInfo.Length; i++) _TipInfo[i] = new TIP_INFO();
            for (int i = 0; i < _Loading.Length; i++) _Loading[i] = new LOADING_POINT_INFO();
            for (int i = 0; i < _TestInfo.Length; i++) _TestInfo[i] = new TEST_POINT_INFO();
            for (int i = 0; i < _PSet.Length; i++) _PSet[i] = new NUTRUNNER_PSET();
            for (int i = 0; i < _EtcDataScan.Length; i++) _EtcDataScan[i] = new ETC_SCAN_SET();
        }


        // 모델 명
        public string strModelName = "";
        public string strComment1 = "";
        public string strComment2 = "";
        public string strComment3 = "";
        public string strComment4 = "";

        // 개수
        public int nCmaCount;
        public int nBmsCount;
        public int nFuseCount;

        public string strCmaSymbol = "";
        public string strBmsSymbol = "";
        public string strFuseSymbol = "";

        // 팁 정보
        public TIP_INFO[] _TipInfo = new TIP_INFO[6];

        // 로딩 포인트 정보
        public LOADING_POINT_INFO[] _Loading = new LOADING_POINT_INFO[20];

        public double dbPackLoadingPointX;
        public double dbPackLoadingPointY;
        public double dbPackLoadingPointZ;

        public double dbTurnPosX;
        public double dbTurnPosY;

        // 검사 포인트 정보
        public TEST_POINT_INFO[] _TestInfo = new TEST_POINT_INFO[5];


        //public int nLotCount;
        //public int nProductCount;
        //public DateTime tLotClearTime = new DateTime();
        //public DateTime tProductClearTime = new DateTime();
        public int nLoadingStopProduct;
        public bool bUseScanSTTester;
        public bool bUnuseContactCyl;
        public bool bUnUseLineSymbol;


        public bool bST5Cyl1Use;
        public bool bST5Cyl2Use;
        public bool bST6Cyl1Use;
        public bool bST6Cyl2Use;

        // 바코드 출력 
        public int nBCDsize;
        public int nBCDStringWidth;
        public int nBCDStringHeight;

        public string strBCDSymbol = "";


        public int nBCDAllOffsetX;
        public int nBCDbcdOffsetX;
        public int nBCDAllOffsetY;
        public int nBCDbcdOffsetY;

        public NUTRUNNER_PSET[] _PSet = new NUTRUNNER_PSET[10];

        public bool[] bLockingStationSkip = new bool[5];
        public bool[] bTestStationSkip = new bool[2];

        public bool bHipotSkip;
        public bool bEolSkip;


        public double dbNoClampXYMoveSpeed;      // 클램프 안했을시 이동 속도
        public double dbNoClampZMoveSpeed;       // 클램프 안했을시 Z 이동 속도
        public double dbClampXYMoveSpeed;        // 제품 클램프시 이동 속도
        public double dbClampZMoveSpeed;         // 제품 클램프시 Z 이동 속도
        public double dbShiftMoveSpeed;          // 하강후 시프트시 이동 속도

        public bool[] bSpare = new bool[100];
        public double[] dbSpare = new double[100];
        public int[] nSpare = new int[100];

        public int nBCDPrintCount;

        public bool bUseXYZPrint;
        public bool bUseSharpPrint;


        public int nBCDOffsetX;
        public int nBCDOffsetY;
        public int nTextOffsetX;
        public int nTextOffsetY;


        public bool bPassOSCTest;
        public double dbOSCSpecOpen;
        public double dbOSCSpecShort;
        public double dbOSCgetCS;

        public bool bPassGBTest;
        public double dbGBInput;
        public double dbGBHighLimit;
        public double dbGBTestTime;

        public bool bPassPIRTest;
        public double dbPIRInput;
        public double dbPIRLowLimit;
        public double dbPIRTestTime;

        public bool bPassNIRTest;
        public double dbNIRInput;
        public double dbNIRLowLimit;
        public double dbNIRTestTime;

        public bool bPassPHIPOTTest;
        public double dbPHIPOTInput;
        public double dbPHIPOTLowLimit;
        public double dbPHIPOTTestTime;

        public bool bPassNHIPOTTest;
        public double dbNHIPOTInput;
        public double dbNHIPOTLowLimit;
        public double dbNHIPOTTestTime;

        public bool bUseHipotVision;
        public bool bUseEolVision;

        public bool bUseHipotBCDScanner;
        public bool bUseEolBCDScanner;

        public bool bPassNOSCTest;
        public double dbNOSCSpecOpen;
        public double dbNOSCSpecShort;
        public double dbNOSCgetCS;

        public bool bUseHipotContactTest;
        public bool bUseEolContactTest;

        public double dbLoadingJigTestPos1X;
        public double dbLoadingJigTestPos1Y;
        public double dbLoadingJigTestPos1Z;

        public double dbLoadingJigTestPos2X;
        public double dbLoadingJigTestPos2Y;
        public double dbLoadingJigTestPos2Z;

        public bool bUseJigTest;

        public double dbLoadingAngle;

        public bool bUseTopCamera;
        public bool bUseFrotCamera;

        public int nBCDScanStation;
        public int nETCScanStation;
        public int nStartLotNum;


        public string strETC1BCD = "";
        public string strETC2BCD = "";

        public int nUseETC1BCD;
        public int nUseETC2BCD;

        public bool bUseEolFix;
        public bool bUseHipotFix;

        public bool bUseEolAutoContact;
        public bool bUseHipotAutoContact;

        public double dbHipotRampTime;

        public bool bUseEOLSideContact;


        // 옴론향 테스트
        public bool bUseOmronHipotTest;

        // 옴론 라벨 테스트
        public bool bUseLabelFoolproof;


        public int nUseETC3BCD;
        public int nUseETC4BCD;

        public string strETC3BCD = "";
        public string strETC4BCD = "";

        public int nUseETC5BCD;                 // Rear Support Plate
        public string strETC5BCD = "";
        public int nUseETC5BCDCount;                 // Rear Support Plate 수량

        // CMA 바코드 시작 위치
        public int nCMAStartIndex;
        public int nTimeLimit;

        public bool bUseTPCRobot;
        public string strST3Model1 = "";
        public string strST3Model2 = "";
        public bool bUseST3Model2;
        public double dbST3TurnAngle;
        public double dbST3TurnSpeed;
        public int nTPCTiteSch;            // 체결 스케줄


        public bool bUseLandingPCSheet;


        public ETC_SCAN_SET[] _EtcDataScan = new ETC_SCAN_SET[5];


        public bool bUseHipot1Distance;             // HIPOT1 거리측정 사용여부
        public bool bUseEolDistance;                // EOL    거리측정 사용여부

        public double dbHipot1Distance;             // HIPOT1 거리측정 기준값
        public double dbEolDistance;                // EOL    거리측정 기준값


        public List<ST2_TIP_INFO> _ST2Tip = new List<ST2_TIP_INFO>();

        public bool bUseST2Encoder;

        // ST1 레인지
        public int nST2EncoderRange;

        public bool bUseStandAloneCanComm;
        public bool bUseResuCanComm;


        public bool bUseTwinPort;

        public bool bUseBpuScan;

        public bool bUsePalletBarcode;

        public bool bUseOmronWHTest;            // 옴론 외함측정 사용 여부
        public string strOmronWHTestCMD = "";       // 옴론 외함측정 카메라 커맨드
        public string strOmronWHTestSch = "";       // 옴론 외함측정 카메라 스케쥴
        public string strOmronWHTestSelect = "";     // 옴론 외함측정 카메라 셀렉트 

        public double dbOmronWDTestSpecWidth;   // 옴론 외함측정 스펙(폭)
        public double dbOmronWDTestSpecHight;   // 옴론 외함측정 스펙(길이)


        public double dbCamera1ReadyPosX;
        public double dbCamera1ReadyPosY;
        public double dbCamera1ReadyPosZ;
        public double dbCamera1WorkPosX;
        public double dbCamera1WorkPosY;
        public double dbCamera1WorkPosZ;

        public double dbCamera2ReadyPosX;
        public double dbCamera2ReadyPosY;
        public double dbCamera2ReadyPosZ;
        public double dbCamera2WorkPosX;
        public double dbCamera2WorkPosY;
        public double dbCamera2WorkPosZ;


        public double dbOmronWDTestSpecWidthMax;
        public double dbOmronWDTestSpecHightMax;



        public int nPreWorkCount = 0;
        public string strPreWorkSymbol = "";

        public bool bUseOmronGen3TypeBCDPrint;          // 옴론Gen3 타입 바코드 출력
        public bool bUseResuGen3TypeBCDPrint;           // Resu Gen3 타입 바코드 출력
        public bool bUseOmronGen3Type150BCDPrint;       // 옴론Gen3 150V 타입 바코드 출력


        public bool bUseCmaBizBCD;

        public List<ETC_SCAN_LIST> _ListEppScan = new List<ETC_SCAN_LIST>();


        public string strLaserMarkingSymbol = "";   // 레이저 마킹기에 추가할 심볼
        public bool bUseLaserMarking = false;               // 레이저 마킹 사용여부
        public string strLaserReadBmaSymbol = "";



        public bool bUseHipotHandReader = false;
        public bool bUseEolHandReader = false;

        public bool bUseManualContect;   //하이팟 수동 연결
        public bool bUseAutoContect;     //하이팟 자동 연결

        public bool bUseHipot1UpDwContact;

        public int nMarkingStation;


    }



    [Serializable]
    public class ST2_TIP_INFO
    {
        public int nX { get; set; }
        public int nY { get; set; }
        public int nTip { get; set; }
        public int nSch { get; set; }
        public bool bTiteOk { get; set; }
    }


    [Serializable]  // 이종품 검사 세트
    public class ETC_SCAN_SET
    {
        public List<ETC_SCAN_LIST> _List = new List<ETC_SCAN_LIST>();



        public bool CheckBarcode(string strBCD)
        {
            bool bResult = true;
            for (int i = 0; i < _List.Count; i++)
            {
                bResult = true;
                if (_List[i].strScanSymbol.Length == strBCD.Length)
                {
                    for (int nBCDLen = 0; nBCDLen < _List[i].strScanSymbol.Length; nBCDLen++)
                    {
                        if (_List[i].strScanSymbol[nBCDLen] == '*')
                        {
                            //if (_List[i].strScanSymbol[nBCDLen] != strBCD[nBCDLen])
                            //{
                            //    // 두개가 다르면
                            //    bResult = false;
                            //    break;  // 빠져나감  
                            //}
                        }
                        else if(_List[i].strScanSymbol[nBCDLen] == '@')
                        {
                            
                            if (strBCD[nBCDLen] < 0x41 || strBCD[nBCDLen] > 0x7A)
                            {
                                bResult = false;
                                break;  // 빠져나감  
                            }
                        }
                        else if (_List[i].strScanSymbol[nBCDLen] == '#')
                        {
                            if (strBCD[nBCDLen] < 0x30 || strBCD[nBCDLen] > 0x39)
                            {
                                bResult = false;
                                break;  // 빠져나감  
                            }
                        }
                        else
                        {
                            if (_List[i].strScanSymbol[nBCDLen] != strBCD[nBCDLen])
                            {
                                // 두개가 다르면
                                bResult = false;
                                break;  // 빠져나감  
                            }
                        }
                    }

                    if (bResult)
                    {
                        _List[i].nReadCount++;
                        return true;
                    }
                }
            }
            return false;
        }

        // 바코드 전보 OK 인지 체크
        public bool CheckListAllOk()
        {
            bool result = true;
            // 전체가 OK인지 확인
            for (int i = 0; i < _List.Count; i++)
            {
                if (_List[i].nReadCount < _List[i].nMaxCount)
                {
                    result = false;
                    break;
                }
            }
            return result;
        }


        public void ClearListData()
        {
            for (int i = 0; i < _List.Count; i++)
            {
                _List[i].nReadCount = 0;
            }
            // Read 카운트를 초기화
        }
    }

    [Serializable]  // 이종품 리스트 세트
    public class ETC_SCAN_LIST
    {
        public string strScanName { get; set; }          // 스캔명
        public string strScanSymbol { get; set; }         // 구분자
        public int nReadCount { get; set; }               // 수량
        public int nMaxCount { get; set; }               // 수량
    }



    public class DATA_RESULT
    {

        public void Clear()
        {
            dbOSCData = 0.0;
            dbNOSCData = 0.0;
            dbPIRData = 0.0;
            dbNIRData = 0.0;
            dbGBData = 0.0;
            dbHipotNeg = 0.0;
            dbHipotPos = 0.0;

            tr_OSC = TEST_RESULT.READY;
            tr_NOSC = TEST_RESULT.READY;
            tr_GB = TEST_RESULT.READY;
            tr_IRP = TEST_RESULT.READY;
            tr_IRN = TEST_RESULT.READY;
            tr_HIN = TEST_RESULT.READY;
            tr_HIP = TEST_RESULT.READY;
            tr_TOTAL = TEST_RESULT.READY;
        }


        public double dbOSCData = 0.0;
        public double dbNOSCData = 0.0;
        public double dbGBData = 0.0;
        public double dbPIRData = 0.0;
        public double dbNIRData = 0.0;
        public double dbHipotNeg = 0.0;
        public double dbHipotPos = 0.0;


        public TEST_RESULT tr_OSC = new TEST_RESULT();
        public TEST_RESULT tr_NOSC = new TEST_RESULT();
        public TEST_RESULT tr_GB = new TEST_RESULT();
        public TEST_RESULT tr_IRN = new TEST_RESULT();
        public TEST_RESULT tr_IRP = new TEST_RESULT();
        public TEST_RESULT tr_HIN = new TEST_RESULT();
        public TEST_RESULT tr_HIP = new TEST_RESULT();

        // 그로맷 검사 데이터
        public string strOSCData = "";
        public string strGBData = "";
        public string strIRData = "";
        public string strBCD = "";

        public TEST_RESULT tr_TOTAL = new TEST_RESULT();

        public DateTime tTestTime = new DateTime();
    }

    public class _ReadBarcodeData
    {
        public string strBCD { get; set; }
        public string strCate { get; set; }
    }

    [Serializable]
    public class LotCount
    {
        public int nLotCount;
        public int nProductCount;
        public int nSpareCount1;
        public int nSpareCount2;
        public int nSpareCount3;
        public DateTime tLotClearTime;
        public DateTime tProductClearTime;
    }

    [Serializable]  // 팁 관련 정보
    public class TIP_INFO
    {
        public int[] nTipMaxCount = new int[20];
        public int[] nTipSch = new int[20];



        public int[] nSpare_a = new int[100];
        public double[] dbSpare_b = new double[100];
    }

    [Serializable]  // 로딩 포인트 정보
    public class LOADING_POINT_INFO
    {
        public bool bUse;
        public int nType;           // Type  0 : 사용안함 , 1 : 정방향 , 2 : 역방향
        public double dbX;
        public double dbY;
        public double dbZ;
        public double dbS;

        public int[] nSpare_a = new int[100];
        public double[] dbSpare_b = new double[100];
    }

    [Serializable]  // 검사 포인트 정보
    public class TEST_POINT_INFO
    {
        public bool bUseUpDwCyl;
        public double dbContactPos1X;
        public double dbContactPos1Y;
        public double dbContactPos1Z;

        public double dbContactPos2X;
        public double dbContactPos2Y;
        public double dbContactPos2Z;


        public double dbReadyPos1X;
        public double dbReadyPos1Y;
        public double dbReadyPos1Z;
        public double dbReadyPos2X;
        public double dbReadyPos2Y;
        public double dbReadyPos2Z;

        public int[] nSpare_a = new int[100];
        public double[] dbSpare_b = new double[100];
    }


    [Serializable]  // 너트러너 세트
    public class NUTRUNNER_PSET
    {
        public int nPsetID;
        public int nTorqueMin;
        public int nTorqueMax;
        public int nTorqueTarget;

        public double dbTorqueMin;
        public double dbTorqueMax;
        public double dbTorqueTarget;

        public int nAngleMin;
        public int nAngleMax;
        public int nAngleTarget;

        public double dbAngleMin;
        public double dbAngleMax;
        public double dbAngleTarget;
    }

    #region 카운트 설정
    [Serializable]
    public class ProductCount
    {
        public int nOkCount;
        public int nNgCount;
        public int nTotalCount;
        public int nPinCount;
        public int nStation5PinCount;
        public int nStation6PinCount;
        public DateTime tLotClearTiem;
    }
    #endregion

    public static class ExtensionMethods
    {
        public static void DoubleBuffered(this DataGridView dgv, bool setting)
        {
            Type dgvType = dgv.GetType();
            PropertyInfo pi = dgvType.GetProperty("DoubleBuffered",
                BindingFlags.Instance | BindingFlags.NonPublic);
            pi.SetValue(dgv, setting, null);
        }


        public static void DoubleBuffered(this ListView dgv, bool setting)
        {
            Type dgvType = dgv.GetType();
            PropertyInfo pi = dgvType.GetProperty("DoubleBuffered",
                BindingFlags.Instance | BindingFlags.NonPublic);
            pi.SetValue(dgv, setting, null);
        }


    }

    //public static class CopyStream
    //{
    //    public static T CopyData<T>(this object src) where T : class
    //    {
    //        MemoryStream memStream = new MemoryStream();
    //        IFormatter fomater = new BinaryFormatter();
    //        fomater.Serialize(memStream, src);
    //        memStream.Seek(0, 0);
    //        return (T)fomater.Deserialize(memStream);
    //    }
    //}


    public static class CopyJson
    {
        public static T CopyJsons<T>(this object src) where T : class
        {
            string strData = JsonConvert.SerializeObject(src);
            return JsonConvert.DeserializeObject<T>(strData);
        }
    }


    public class _IniFile
    {
        [DllImport("kernel32.dll")]
        private static extern int GetPrivateProfileString(String section, String key, String def, StringBuilder retVal, int Size, String filePat);

        [DllImport("Kernel32.dll")]
        private static extern long WritePrivateProfileString(String Section, String Key, String val, String filePath);

        public static void IniWriteValue(String Section, String Key, String Value, string avaPath)
        {
            WritePrivateProfileString(Section, Key, Value, avaPath);
        }

        public static String IniReadValue(String Section, String Key, string def, string avsPath)
        {
            StringBuilder temp = new StringBuilder(2000);
            int i = GetPrivateProfileString(Section, Key, def, temp, 2000, avsPath);
            return temp.ToString();
        }
    }


}
