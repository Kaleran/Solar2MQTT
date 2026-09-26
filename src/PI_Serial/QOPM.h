bool PI_Serial::PIXX_QOPM()
{
    if (!(isPi30LikeProtocol(protocol) || protocol == PI30_SML))
    {
        return false;
    }
    String ans = this->requestData("QOPM");
    get.raw.qopm = ans;
    if (ans == DESCR_req_ERCRC)
        return false;
    if (ans == DESCR_req_NAK || ans == DESCR_req_NOA || ans.length() == 0)
        return true;
    staticData[DESCR_Output_Mode_Raw] = ans;
    // also decode to text like QPIRI Output_Mode but keep raw
    // Do not overwrite existing Output_Mode, just keep raw mapping
    return true;
}
