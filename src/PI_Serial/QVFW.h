bool PI_Serial::PIXX_QVFW()
{
    if (!(isPi30LikeProtocol(protocol) || protocol == PI30_SML))
    {
        return false;
    }
    // QVFW - Main CPU firmware
    {
        String ans = this->requestData("QVFW");
        get.raw.qvfw = ans;
        if (ans == DESCR_req_ERCRC)
            return false;
        if (ans != DESCR_req_NAK && ans != DESCR_req_NOA && ans.length() > 0)
        {
            String s = ans;
            s.trim();
            // expected format VERFW:00123.01 or similar
            int idx = s.indexOf(':');
            if (idx >= 0 && idx + 1 < (int)s.length())
                s = s.substring(idx + 1);
            s.trim();
            staticData[DESCR_Main_CPU_Firmware_Version] = s;
        }
    }
    // QVFW2 - Secondary CPU
    {
        String ans = this->requestData("QVFW2");
        get.raw.qvfw2 = ans;
        if (ans == DESCR_req_ERCRC)
            return false;
        if (ans != DESCR_req_NAK && ans != DESCR_req_NOA && ans.length() > 0)
        {
            String s = ans;
            s.trim();
            int idx = s.indexOf(':');
            if (idx >= 0 && idx + 1 < (int)s.length())
                s = s.substring(idx + 1);
            s.trim();
            staticData[DESCR_Secondary_CPU_Firmware_Version] = s;
        }
    }
    return true;
}
