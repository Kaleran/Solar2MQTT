bool PI_Serial::PIXX_QBOOT()
{
    if (!(isPi30LikeProtocol(protocol) || protocol == PI30_SML))
    {
        return false;
    }
    String ans = this->requestData("QBOOT");
    get.raw.qboot = ans;
    if (ans == DESCR_req_ERCRC)
        return false;
    if (ans == DESCR_req_NAK || ans == DESCR_req_NOA || ans.length() == 0)
        return true;
    // ans is "1" or "0"
    staticData[DESCR_DSP_Bootstrap] = (ans.charAt(0) == '1') ? 1 : 0;
    return true;
}
