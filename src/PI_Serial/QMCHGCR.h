bool PI_Serial::PIXX_QMCHGCR()
{
    if (!(isPi30LikeProtocol(protocol) || protocol == PI30_SML))
    {
        return false;
    }
    // QMCHGCR - selectable max charging current
    {
        String ans = this->requestData("QMCHGCR");
        get.raw.qmchgcr = ans;
        if (ans == DESCR_req_ERCRC)
            return false;
        if (ans != DESCR_req_NAK && ans != DESCR_req_NOA && ans.length() > 0)
        {
            staticData[DESCR_Selectable_Max_Charging_Current] = ans;
        }
    }
    // QMUCHGCR - selectable max utility charging current
    {
        String ans = this->requestData("QMUCHGCR");
        get.raw.qmuchgcr = ans;
        if (ans == DESCR_req_ERCRC)
            return false;
        if (ans != DESCR_req_NAK && ans != DESCR_req_NOA && ans.length() > 0)
        {
            staticData[DESCR_Selectable_Max_Utility_Charging_Current] = ans;
        }
    }
    return true;
}
