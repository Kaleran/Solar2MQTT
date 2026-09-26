static const char *const qdi_fields[] = {
    DESCR_QDI_AC_Output_Voltage,            // BBB.B
    DESCR_QDI_AC_Output_Frequency,          // CC.C
    DESCR_QDI_Max_AC_Charging_Current,      // 00DD
    DESCR_QDI_Battery_Under_Voltage,        // EE.E
    DESCR_QDI_Battery_Float_Voltage,        // FF.F
    DESCR_QDI_Battery_Bulk_Voltage,         // GG.G
    DESCR_QDI_Battery_Recharge_Voltage,     // HH.H
    DESCR_QDI_Max_Charging_Current,         // II
    DESCR_QDI_Input_Voltage_Range,          // J
    DESCR_QDI_Output_Source_Priority,       // K
    DESCR_QDI_Charger_Source_Priority,      // L
    DESCR_QDI_Battery_Type,                 // M
    "QDI_Buzzer_Enabled",                   // N
    "QDI_Power_Saving_Enabled",             // O
    "QDI_Overload_Restart_Enabled",         // P
    "QDI_Over_Temperature_Restart_Enabled", // Q
    DESCR_QDI_Output_Mode,                  // W
    DESCR_QDI_Battery_Redischarge_Voltage,  // YY.Y
    DESCR_QDI_PV_OK_Condition,              // X
    DESCR_QDI_PV_Power_Balance,             // Z
};

bool PI_Serial::PIXX_QDI()
{
    if (!(isPi30LikeProtocol(protocol) || protocol == PI30_SML))
    {
        return false;
    }
    String ans = this->requestData("QDI");
    get.raw.qdi = ans;
    if (ans == DESCR_req_ERCRC)
        return false;
    if (ans == DESCR_req_NAK || ans == DESCR_req_NOA || ans.length() == 0)
        return true;

    // QDI has variable length; try to split and map what we can
    char buf[256];
    ans.toCharArray(buf, sizeof(buf));
    char *fields[32];
    int cnt = pi_split_fields(buf, delimiter[0], fields, 32);
    // PDF shows ~21-23 fields depending on firmware; map up to available
    // For 5K SML, expect ~19-21 fields without the "R,S,T,U,V" extras
    unsigned int mapLen = sizeof(qdi_fields) / sizeof(qdi_fields[0]);
    for (unsigned int i = 0; i < mapLen && i < (unsigned int)cnt; ++i)
    {
        if (fields[i][0] != '\0' && qdi_fields[i] != nullptr && qdi_fields[i][0] != '\0')
        {
            // numeric fields parse as float, flags as int
            if (i <= 7 || i == 16) // voltage/current fields
                staticData[qdi_fields[i]] = pi_parse_float2(fields[i]);
            else
                staticData[qdi_fields[i]] = atoi(fields[i]);
        }
    }
    // also keep raw for debug
    return true;
}
