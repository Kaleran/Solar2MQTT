bool PI_Serial::PIXX_QID()
{
    if (!(isPi30LikeProtocol(protocol) || protocol == PI30_SML))
    {
        return false;
    }
    // QID - 14 char serial
    {
        String ans = this->requestData("QID");
        get.raw.qid = ans;
        if (ans != DESCR_req_NAK && ans != DESCR_req_NOA && ans != DESCR_req_ERCRC && ans.length() > 0)
        {
            String s = ans;
            s.trim();
            staticData[DESCR_Device_Serial_Number] = s;
        }
        else if (ans == DESCR_req_ERCRC)
        {
            return false;
        }
    }
    // QSID - long serial, format (NNXXXXXXXXXXXXXXXXXXXX
    {
        String ans = this->requestData("QSID");
        get.raw.qsid = ans;
        if (ans != DESCR_req_NAK && ans != DESCR_req_NOA && ans != DESCR_req_ERCRC && ans.length() > 0)
        {
            String s = ans;
            s.trim();
            // first 2 chars are length, rest is serial
            if (s.length() >= 2 && isDigit(s.charAt(0)) && isDigit(s.charAt(1)))
            {
                int len = s.substring(0, 2).toInt();
                String serial = s.substring(2);
                // trim to len
                if ((int)serial.length() > len)
                    serial = serial.substring(0, len);
                staticData[DESCR_Device_Serial_Number_Long] = serial;
                // also keep raw long form
                if (staticData[DESCR_Device_Serial_Number].isNull() || String(staticData[DESCR_Device_Serial_Number].as<const char*>()).length() < 6)
                {
                    staticData[DESCR_Device_Serial_Number] = serial;
                }
            }
            else
            {
                staticData[DESCR_Device_Serial_Number_Long] = s;
            }
        }
        else if (ans == DESCR_req_ERCRC)
        {
            return false;
        }
    }
    return true;
}
