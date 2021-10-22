#include "CurrentM.h"
#include "Hv.h"
#include "SystemConnection_Lcfg.h"
#include "Soc.h"
#include "CellDataM.h"
#include "statistic.h"
#include "Hmi.h"
#include "RelayM.h"
#include "RelayM_Lcfg.h"

static uint16 MDBSgetTotalVoltage(const Modbus_ReadRegionType *p, uint16 addr) {
    uint16 rc;
    (void)addr;
    (void)p;

    rc = Statistic_GetBcu100mvTotalVoltage();
    if (Statistic_TotalVoltageIsValid(rc)) {
        rc = (rc + 5U) / 10U;
    }
    return rc;
}

static uint16 MDBSgetTotalCurrent(const Modbus_ReadRegionType *p, uint16 addr) {
    sint16 rc;
    (void) addr;
    (void)p;

    rc =  (sint16)CurrentM_GetCurrentCalibrated(CURRENTM_CHANNEL_MAIN);

    if (CurrentM_IsValidCurrent(rc)) {
        if (rc < 0) {
            rc = (rc - 5) / 10;
        } else {
            rc = (rc + 5) / 10;
        }
    } else {

    }

    return (uint16)rc;
}

static uint16 MDBSgetSOC(const Modbus_ReadRegionType *p, uint16 addr) {
    uint16 rc;
    (void) addr;
    (void)p;

    rc = Soc_Get();
    rc = (uint16)((rc + 5U) / 10U);
    return rc;
}

static uint16 MDBSgetCellNum(const Modbus_ReadRegionType *p, uint16 addr) {
    (void) addr;
    (void)p;

    return (uint16)SYSTEM_BATTERY_CELL_NUM;
}

static uint16 MDBSgetTempSensorNum(const Modbus_ReadRegionType *p, uint16 addr) {
    (void) addr;
    (void)p;

    return (uint16)SYSTEM_TEMP_CELL_NUM;
}

static uint16 MDBSgetHeatSensorNum(const Modbus_ReadRegionType *p, uint16 addr) {
    (void) addr;
    (void)p;

    return (uint16)SYSTEM_HEAT_TEMP_NUM;
}

static uint16 MDBSgetPoleTempNum(const Modbus_ReadRegionType *p, uint16 addr) {
    (void) addr;
    (void)p;

    return (uint16)SYSTEM_POLE_TEMP_NUM;
}
static uint16 MDBSgetDeltaVoltage(const Modbus_ReadRegionType *p, uint16 addr)
{
    uint16 val16;
    (void) p;
    (void) addr;
    val16 = Statistic_GetBcuDeltaVoltage();
    return val16;
}
static uint16 MDBSgetDeltaTemperature(const Modbus_ReadRegionType *p, uint16 addr)
{
    sint16 rc;
    (void) p;
    (void) addr;
    rc = (sint16)Statistic_GetBcuDeltaTemperature();
    if (CellDataM_TemperatureIsValid((uint16)rc)) {
        rc -= 50;
    } else {

    }
    return (uint16)rc;
}
static uint16 MDBSgetRelaystate(const Modbus_ReadRegionType *p, uint16 addr)
{
    RelayM_FunctionType fn;
    RelayM_DiagnosisStatusType diag;
    HLSS_ForceDriveType force;
    HLSS_ChannelType hlss;
    uint16 val16 = 0U;
    (void) p;
    if (addr >= 1050U)
    {
        fn = (RelayM_FunctionType)(addr - 1050U);
        if ((uint16)fn < RELAYM_FN_NUM)
        {
            diag = RelayM_GetDiagnosisStatus(fn);
            if (RELAYM_DIAGNOSIS_IS_DRIVER_ERR(diag)) {
                val16 = 0x04U;
            } else if (RELAYM_DIAGNOSIS_IS_ADHESIVE(diag)) {
                val16 = 0x05U;
            } else if (RELAYM_DIAGNOSIS_IS_OPEN(diag)) {
                val16 = 0x06U;
            } else if (RELAYM_DIAGNOSIS_IS_AUX_CONTACT_ERR(diag)) {
                val16 = 0x07U;
            } else {
                hlss = RelayM_GetDriveHSSChannel(fn);
                force = HLSS_GetForce(hlss);
                if (force == HLSS_FORCE_ON) {
                    val16 = 0x02U;
                } else if (force == HLSS_FORCE_OFF) {
                    val16 = 0x03U;
                } else {
                    val16 = RelayM_GetActualStatus(fn) == RELAYM_ACTUAL_ON ? 0x01U : 0x00U;
                }
            }
        }
    }
    return val16;
}

/*2000-2399*/
static uint16 MDBSget_CellDataM_GetVoltage(const Modbus_ReadRegionType *p, uint16 addr) {
    uint16 rc;
    rc = CellDataM_GetVoltage(addr - p->startaddr);
    return rc;
}

/*3000,3199*/
static uint16 MDBSget_CellDataM_GetTemperature(const Modbus_ReadRegionType *p, uint16 addr) {
    sint16 rc;

    rc = (sint16)CellDataM_GetTemperature(addr - p->startaddr);
    if (CellDataM_TemperatureIsValid((uint16)rc)) {
        rc -= 50;
    } else {

    }
    return (uint16)rc;
}

/*3500,3549,*/
static uint16 MDBSget_CellDataM_GetHeatTemperature(const Modbus_ReadRegionType *p, uint16 addr) {
    sint16 rc;

    rc = (sint16)CellDataM_GetHeatTemperature(addr - p->startaddr);
    if (CellDataM_TemperatureIsValid((uint16)rc)) {
        rc -= 50;
    } else {

    }
    return (uint16)rc;
}

/*3600,3649,*/
static uint16 MDBSget_CellDataM_GettPoleTemperature(const Modbus_ReadRegionType *p, uint16 addr) {
    sint16 rc;

    rc = (sint16)CellDataM_GetPoleTemperature(addr - p->startaddr);
    if (CellDataM_TemperatureIsValid((uint16)rc)) {
        rc -= 50;
    } else {

    }

    return (uint16)rc;
}



static uint16 MDBSgetalarm(const Modbus_ReadRegionType *p, uint16 addr) {
    uint8 i, j;
    uint16 trc, rc = 0U;

    for (i = 0U; i < 16U; i++) {
        if (Diagnosis_GetLevel((Diagnosis_ItemType)(i + addr - p->startaddr))) {
            rc = (rc | ((uint16)0x0001U << i));
        }
    }
    trc = rc & 0x00ffU;
    j = (uint8)(rc >> 8U);
    rc = (trc << 8U) | j;
    return rc;
}

static uint16 test_modbus_x01(const Modbus_ReadRegionType *p, uint16 addr) {
    (void) p;
    (void) addr;
    return 0x1234U;

}

static void modbus_ctrl_mos(const struct Modbus_WriteRegion *regs, uint16 addr, const uint8 *dat, uint16 len) {
    (void) regs;
    (void) addr;
    (void) dat;
    (void) len;
}

static const Modbus_ReadRegionType x01registerTable[] = {
    {2000U, 2399U, test_modbus_x01},
};


static const Modbus_ReadRegionType x02registerTable[] = {
    {2000U, 2399U, MDBSgetalarm},
};


static const Modbus_ReadRegionType x03registerTable[] = {
    {2000U, 2399U, test_modbus_x01},
};


static const Modbus_ReadRegionType x04registerTable[] = {
    {2000U, 2399U, MDBSget_CellDataM_GetVoltage},
    /*	{2400, 2999, get2},*/
    {3000U, 3199U, MDBSget_CellDataM_GetTemperature},
    /*	{3200,3499, getCellVolVisable},*/
    {3500U, 3549U, MDBSget_CellDataM_GetHeatTemperature},
    /*	{3550,3599, getCellVolVisable},*/
    {3600U, 3649U, MDBSget_CellDataM_GettPoleTemperature},
    /*	{3650,3699, getCellVolVisable},*/

    {1000U, 1000U, MDBSgetTotalVoltage},
    {1001U, 1001U, MDBSgetTotalCurrent},
    {1002U, 1002U, MDBSgetSOC},
    {1003U, 1003U, MDBSgetCellNum},
    {1004U, 1004U, MDBSgetTempSensorNum},
    {1005U, 1005U, MDBSgetHeatSensorNum},
    {1006U, 1006U, MDBSgetPoleTempNum},
    {1007U, 1007U, MDBSgetDeltaVoltage},
    {1008U, 1008U, MDBSgetDeltaTemperature},
    {1050U, 1080U, MDBSgetRelaystate},
};

static const Modbus_WriteRegionType x06registerTable[] = {
    {3001U, 3001U, modbus_ctrl_mos},
};

static const Modbus_WriteRegionType x16registerTable[] = {
    {3001U, 3001U, modbus_ctrl_mos},
};

const Modbus_Cfg ModbusCfg = {
    0x01U, //uint8  slaveaddr;
    0x00U, //uint8  broadcastaddr;
    0xa001U, //uint16 CRCpolynomial;
    0xffffU, //uint16 CRCInit;
    100U, //uint16 FrameTimeout
    {x01registerTable, (uint8)ARRAY_SIZE(x01registerTable), 16U}, //Modbus_RegistersTableType Modbus_X01registerTable;
    {x02registerTable, (uint8)ARRAY_SIZE(x02registerTable), 16U}, //Modbus_RegistersTableType Modbus_X02registerTable;
    {x03registerTable, (uint8)ARRAY_SIZE(x03registerTable), 1U}, //Modbus_RegistersTableType odbus_X03registerTable;
    {x04registerTable, (uint8)ARRAY_SIZE(x04registerTable), 1U}, //Modbus_RegistersTableType *Modbus_X04registerTable;
    {x06registerTable, (uint8)ARRAY_SIZE(x06registerTable), 1U}, //Modbus_RegistersTableType *Modbus_X06registerTable;
    {x16registerTable, (uint8)ARRAY_SIZE(x16registerTable), 1U}, //Modbus_RegistersTableType *Modbus_X16registerTable;
};

